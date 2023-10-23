<?php 

/**
 * Git Repository Interface Class
 *
 * This class enables the creating, reading, and manipulation
 * of a git repository
 *
 * @class  GitRepo
 */
class Git {

	protected $repo_path = null;
	protected $bare = false;
	protected $envopts = array();
	private $bin = 'git';
	private static $instance ;

	//Added
	public function setBinFile($pathToBin){
		$this->bin = $pathToBin;
		global $newFarm;
		if ($newFarm){
			$this->bin = "/usr/bin/git";
		}
	}
	
	/**
	 * Create a new git repository
	 *
	 * Accepts a creation path
	 *
	 * @access  public
	 * @param   string  repository path
	 * @param   string  is it bare server
	 * @return  GitRepo
	 */
	public static function create($path, $bare = false) {
		$realPath = realpath($path);
		
		//If the folder does not exist, try to create one.
		if(!file_exists($realPath))
			mkdir($realPath);
		
		if (file_exists($repo_path."/.git") && is_dir($repo_path."/.git")) {
			throw new \Exception('"'.$repo_path.'" is already a git repository.', 409);
		} else {
			self::$instance = new self;
			
			if($bare){
				self::$instance->run('init --bare');
			} else{
				self::$instance->run('init');
			}
		}
		
		return self::$instance;
	}
	
	public static function open($path){		
		$realPath = realpath($path);	
		if(file_exists($realPath)){
			if (self::$instance === null)
	            self::$instance = new self;	
	            
			if (is_dir($realPath)) {
				// Is this a work tree?
				if (file_exists($realPath."/.git") && is_dir($realPath."/.git")) {
					self::$instance->repo_path = $realPath;
					self::$instance->bare = false;
				// Is this a bare repo?
				} else if (is_file($realPath."/config")) {
				  $parse_ini = parse_ini_file($realPath."/config");
					if ($parse_ini['bare']) {
						self::$instance->repo_path = $realPath;
						self::$instance->bare = true;
					}
				} else {
					throw new \Exception('"'.$repo_path.'" is not a git repository.', 406);
				}
			} else {
				throw new \Exception('"'.$repo_path.'" is not a directory.', 404);
			}
			return self::$instance;
		} else {
			throw new \Exception('Repository folder '.$realPath.' does not exists.', 404);
		}
	}
	
	public function lastCommit(){
		$status = self::$instance->run("show --'format={\"hash\": \"%H\", \"author\": \"%an\", \"message\": \"%s\"}'");
		return json_decode(substr($status, 0, strpos($status, 'diff --git')));
	}

	/**
	 * Tests if git is installed
	 *
	 * @access  public
	 * @return  bool
	 */
	public function test() {
		$descriptorspec = array(
			1 => array('pipe', 'w'),
			2 => array('pipe', 'w'),
		);
		$pipes = array();
		$resource = proc_open(Git::get_bin(), $descriptorspec, $pipes);

		$stdout = stream_get_contents($pipes[1]);
		$stderr = stream_get_contents($pipes[2]);
		foreach ($pipes as $pipe) {
			fclose($pipe);
		}

		$status = trim(proc_close($resource));
		return ($status != 127);
	}

	/**
	 * Run a command in the git repository
	 *
	 * Accepts a shell command to run
	 *
	 * @access  protected
	 * @param   string  command to run
	 * @return  string
	 */
	protected function run($command) {
		$descriptorspec = array(
			1 => array('pipe', 'w'),
			2 => array('pipe', 'w'),
		);
		$pipes = array();
		/* Depending on the value of variables_order, $_ENV may be empty.
		 * In that case, we have to explicitly set the new variables with
		 * putenv, and call proc_open with env=null to inherit the reset
		 * of the system.
		 *
		 * This is kind of crappy because we cannot easily restore just those
		 * variables afterwards.
		 *
		 * If $_ENV is not empty, then we can just copy it and be done with it.
		 */
		if(count($_ENV) === 0) {
			$env = NULL;
			foreach($this->envopts as $k => $v) {
				putenv(sprintf("%s=%s",$k,$v));
			}
		} else {
			$env = array_merge($_ENV, $this->envopts);
		}
		$cwd = $this->repo_path;
		//echo "WORKING ON: {$cwd}, command:{$this->bin} {$command}<br/>";
		$resource = proc_open($this->bin.' '.$command, $descriptorspec, $pipes, $cwd, $env);

		$stdout = stream_get_contents($pipes[1]);
		$stderr = stream_get_contents($pipes[2]);
		foreach ($pipes as $pipe) {
			fclose($pipe);
		}

		$status = trim(proc_close($resource));
		if ($status) throw new \Exception($stderr);

		return $stdout;
	}

	/**
	 * Runs a 'git status' call
	 *
	 * Accept a convert to HTML bool
	 * 
	 * @access public
	 * @param bool  return string with <br />
	 * @return string
	 */
	public function status($html = false) {
		$msg = $this->run("status");
		if ($html == true) {
			$msg = str_replace("\n", "<br />", $msg);
		}
		return $msg;
	}
	public function statusArray() {
		//Parse modified or added files to handle add (and commit)
		$msg = $this->run("status");
		$spl = explode("\n",$msg);
		$retval = array();
		$retval['MOD'] = array(); //File modificati
		$retval['NEW'] = array(); //File nuovi
		$retval['ADD'] = array(); //File da committare (staged for commit)
		$status = 0;
		foreach ($spl as $line){
			//Parso le linee dello status per recuperare i files
			if (stristr($line,"Changes not staged for commit")!==FALSE){
				//attiva parsing file modificati
				$status = 1;
			}else if (stristr($line,"Untracked files")!==FALSE){
				//attiva parsing file aggiunti
				$status = 2;
			}else if (stristr($line,"no changes added to commit")!==FALSE){
				//Ignoro la riga, sto finendo il comando
			}else if (stristr($line,"Changes to be committed")!==FALSE){
				$status = 3;			
			}else{
				$line = trim(str_replace("#","",$line));
				if ($line && !$this->common_beginsWith($line,"(")){
					switch ($status){
						case 1:
							$retval['MOD'][] = trim(str_replace("modified:","",$line));
							break;
						case 2:
							$retval['NEW'][] = trim($line);
							break;
						case 3:
							$retval['ADD'][] = trim($line);
							break;
						default:
							//Non gestito
							break;
					}
				}
			}
		}
		return $retval;
	}
	
	/**
	 * Runs a `git add` call
	 *
	 * Accepts a list of files to add
	 *
	 * @access  public
	 * @param   mixed   files to add
	 * @return  string
	 */
	public function add($files = "*") {
		if (is_array($files)) {
			$files = '"'.implode('" "', $files).'"';
		}
		return $this->run("add $files -v");
	}
	
	/**
	 * Runs a `git rm` call
	 *
	 * Accepts a list of files to remove
	 *
	 * @access  public
	 * @param   mixed    files to remove
	 * @param   Boolean  use the --cached flag?
	 * @return  string
	 */
	public function rm($files = "*", $cached = false) {
		if (is_array($files)) {
			$files = '"'.implode('" "', $files).'"';
		}
		return $this->run("rm ".($cached ? '--cached ' : '').$files);
	}


	/**
	 * Runs a `git commit` call
	 *
	 * Accepts a commit message string
	 *
	 * @access  public
	 * @param   string  commit message
	 * @param   boolean  should all files be committed automatically (-a flag)
	 * @return  string
	 */
	public function commit($message = "", $commit_all = true) {
		$flags = $commit_all ? '-av' : '-v';
		return $this->run("commit ".$flags." -m ".escapeshellarg($message));
	}

	/**
	 * Runs a `git clone` call to clone the current repository
	 * into a different directory
	 *
	 * Accepts a target directory
	 *
	 * @access  public
	 * @param   string  target directory
	 * @return  string
	 */
	public function cloneTo($target) {
		return $this->run("clone --local ".$this->repo_path." $target");
	}

	/**
	 * Runs a `git clone` call to clone a different repository
	 * into the current repository
	 *
	 * Accepts a source directory
	 *
	 * @access  public
	 * @param   string  source directory
	 * @return  string
	 */
	public function cloneFromRepo($source) {
		return $this->run("clone --local $source ".$this->repo_path);
	}

	/**
	 * Runs a `git clone` call to clone a remote repository
	 * into the current repository
	 *
	 * Accepts a source url
	 *
	 * @access  public
	 * @param   string  source url
	 * @return  string
	 */
	public function cloneFromURL($source) {
		return $this->run("clone $source ".$this->repo_path);
	}

	/**
	 * Runs a `git clean` call
	 *
	 * Accepts a remove directories flag
	 *
	 * @access  public
	 * @param   bool    delete directories?
	 * @param   bool    force clean?
	 * @return  string
	 */
	public function clean($dirs = false, $force = false) {
		return $this->run("clean".(($force) ? " -f" : "").(($dirs) ? " -d" : ""));
	}

	/**
	 * Runs a `git branch` call
	 *
	 * Accepts a name for the branch
	 *
	 * @access  public
	 * @param   string  branch name
	 * @return  string
	 */
	public function createBranch($branch) {
		return $this->run("branch $branch");
	}

	/**
	 * Runs a `git branch -[d|D]` call
	 *
	 * Accepts a name for the branch
	 *
	 * @access  public
	 * @param   string  branch name
	 * @return  string
	 */
	public function deleteBranch($branch, $force = false) {
		return $this->run("branch ".(($force) ? '-D' : '-d')." $branch");
	}

	/**
	 * Runs a `git branch` call
	 *
	 * @access  public
	 * @param   bool    keep asterisk mark on active branch
	 * @return  array
	 */
	public function listBranches($keep_asterisk = false) {
		$branchArray = explode("\n", $this->run("branch"));
		foreach($branchArray as $i => &$branch) {
			$branch = trim($branch);
			if (! $keep_asterisk) {
				$branch = str_replace("* ", "", $branch);
			}
			if ($branch == "") {
				unset($branchArray[$i]);
			}
		}
		return $branchArray;
	}

	/**
	 * Lists remote branches (using `git branch -r`).
	 *
	 * Also strips out the HEAD reference (e.g. "origin/HEAD -> origin/master").
	 *
	 * @access  public
	 * @return  array
	 */
	public function listRemoteBranches() {
		$branchArray = explode("\n", $this->run("branch -r"));
		foreach($branchArray as $i => &$branch) {
			$branch = trim($branch);
			if ($branch == "" || strpos($branch, 'HEAD -> ') !== false) {
				unset($branchArray[$i]);
			}
		}
		return $branchArray;
	}

	/**
	 * Returns name of active branch
	 *
	 * @access  public
	 * @param   bool    keep asterisk mark on branch name
	 * @return  string
	 */
	public function activeBranch($keep_asterisk = false) {
		$branchArray = $this->list_branches(true);
		$active_branch = preg_grep("/^\*/", $branchArray);
		reset($active_branch);
		if ($keep_asterisk) {
			return current($active_branch);
		} else {
			return str_replace("* ", "", current($active_branch));
		}
	}

	/**
	 * Runs a `git checkout` call
	 *
	 * Accepts a name for the branch
	 *
	 * @access  public
	 * @param   string  branch name
	 * @return  string
	 */
	public function checkout($branch) {
		return $this->run("checkout $branch");
	}


	/**
	 * Runs a `git merge` call
	 *
	 * Accepts a name for the branch to be merged
	 *
	 * @access  public
	 * @param   string $branch
	 * @return  string
	 */
	public function merge($branch) {
		return $this->run("merge $branch --no-ff");
	}


	/**
	 * Runs a git fetch on the current branch
	 *
	 * @access  public
	 * @return  string
	 */
	public function fetch() {
		return $this->run("fetch");
	}

	/**
	 * Add a new tag on the current position
	 *
	 * Accepts the name for the tag and the message
	 *
	 * @param string $tag
	 * @param string $message
	 * @return string
	 */
	public function addTag($tag, $message = null) {
		if ($message === null) {
			$message = $tag;
		}
		return $this->run("tag -a $tag -m $message");
	}

	/**
	 * List all the available repository tags.
	 *
	 * Optionally, accept a shell wildcard pattern and return only tags matching it.
	 *
	 * @access	public
	 * @param	string	$pattern	Shell wildcard pattern to match tags against.
	 * @return	array				Available repository tags.
	 */
	public function listTags($pattern = null) {
		$tagArray = explode("\n", $this->run("tag -l $pattern"));
		foreach ($tagArray as $i => &$tag) {
			$tag = trim($tag);
			if ($tag == '') {
				unset($tagArray[$i]);
			}
		}

		return $tagArray;
	}

    /**
     * Push specific branch to a remote
     *
     * Accepts the name of the remote and local branch
     *
     * @param string $remote
     * @param string $branch
     * @return string
     */
    public function pushSimple() {
        return $this->run("push");
    }
	/**
	 * Push specific branch to a remote
	 *
	 * Accepts the name of the remote and local branch
	 *
	 * @param string $remote
	 * @param string $branch
	 * @return string
	 */
	public function push($remote, $branch) {
		return $this->run("push --tags $remote $branch");
	}

	/**
	 * Pull specific branch from remote
	 *
	 * Accepts the name of the remote and local branch
	 *
	 * @param string $remote
	 * @param string $branch
	 * @return string
	 */
	public function pull($remote, $branch) {
		return $this->run("pull $remote $branch");
	}

	/**
	 * Sets the project description.
	 *
	 * @param string $new
	 */
	public function setDescription($new) {
		file_put_contents($this->repo_path."/.git/description", $new);
	}

	/**
	 * Gets the project description.
	 *
	 * @return string
	 */
	public function getDescription() {
		return file_get_contents($this->repo_path."/.git/description");
	}

	/**
	 * Sets custom environment options for calling Git
	 *
	 * @param string key
	 * @param string value
	 */
	public function setenv($key, $value) {
		$this->envopts[$key] = $value;
	}
	
	public function isServer(){
		return $this->bare;
	}

	
	private function common_beginsWith( $str, $sub ) {
	   return ( substr( $str, 0, strlen( $sub ) ) === $sub );
	}

	private function  common_endsWith( $str, $sub ) {
	   return ( substr( $str, strlen( $str ) - strlen( $sub ) ) === $sub );
	}


    //Aggiunto recupero hash
    public function getCurrentHash(){
        return $this->run("rev-parse HEAD");
    }
	
}
