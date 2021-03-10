<?
/**
 * @package FileAllegati
 */

class CMELayerPrototype {
	var $configuration;
	var $connection;
	var $session_vars;
	function __construct($connection,$configuration=null,$session_vars=null,$config_service=null){
		$this->connection=$connection;
		$this->configuration=$configuration;
		$this->session_vars=$session_vars;
		$this->config_service=$config_service;
		if(!is_array($this->config_service)){
			global $config_service;
			$this->config_service=$config_service;
		}
	}
	function createStore(){}
	function getStores(){}
	function query(){}
	function queryChildren(){}
	function queryParents(){}
	function fetchMore(){}
	function update(){}
	function describe(){}
	function get(){}

	function save(){}
	function delete(){}
	function createFolder(){}
	function deleteFolder(){}
	function folderExist(){}
	function retrieveFolder(){}
	function move(){}
	function copy(){}
	function link(){}
	function viewFolder(){}
	function uploadForm($store,$folder,$keywords,$edit){

	}

}

class CMELayerWCAPrototype extends CMELayerPrototype {
	function controller(){
		
		switch($this->session_vars['CMELAction']){
			default:
				case'folder':
				if(preg_match("/\//",$this->session_vars['CMELFolder'])){

					$folders=explode("/",$this->session_vars['CMELFolder']);
					$topic=array_pop($folders);
					$pk=$folders[0];
					$baseFolder=implode('/',$folders);

					$query[0]['TYPE']='SIMPLE';
					$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
					$query[0]['OPERATOR']='=';
					$query[0]['VALUE']=':pk_service';
					$query[1]['JOIN']='and';
					$query[1]['TYPE']='SIMPLE';
					$query[1]['PARAM']='TOPIC';
					$query[1]['OPERATOR']='=';
					$query[1]['VALUE']=':topic';
					$bind['pk_service']=$pk;
					$bind['TOPIC']=$topic;
					$queryResultSet=array();
					//Logger::send($this->configuration['queryNames']);
					foreach ($this->configuration['queryNames'] as $queryName){
						//Logger::send($queryName);
						$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
						if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);
						//Logger::send($currQueryResultSet);
					}
					$html=$this->show_area_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$baseFolder);

				} else {
					$query[0]['TYPE']='SIMPLE';
					$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
					$query[0]['OPERATOR']='=';
					$query[0]['VALUE']=':'.$this->configuration['PK_SERVICE'];
					/*$query[1]['TYPE']='SIMPLE';
					$query[1]['PARAM']='TOPIC';
					$query[1]['OPERATOR']='in';
					$query[1]['VALUE']='(:1,:2,:3)';
					$bind['1']='topic1';
					$bind['2']='topic2';
					$bind['3']='topic3';*/
					//				$bind[$this->configuration['PK_SERVICE']]=$this->configuration[$this->configuration['PK_SERVICE']];
					$bind[$this->configuration['PK_SERVICE']]=$this->session_vars['CMELFolder'];
					$queryResultSet=array();
					foreach ($this->configuration['queryNames'] as $queryName){
						$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
						$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);
					}
					$html=$this->folder_doc_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$this->session_vars['CMELFolder']);
				}
				break;
				case'detail':
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']='ID';
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':id';
				$bind['ID']=$this->session_vars['CMELRequestRef'];
				$bind['pk_service']=$this->session_vars[$this->configuration['PK_SERVICE']];
				$queryResultSet=$this->query($this->configuration['SERVICE'],$this->session_vars['CMELQueryName'],$query,$bind);
				$html=$this->show_doc_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$this->session_vars['CMELRequestRef']);
			break;
			case 'download':
				$this->download($this->configuration['SERVICE'],$this->session_vars['CMELRequestRef']);
			break;
			
		}
		$this->html=$html;
	}


	function createStore($store){
		return $store;
	}
	function getStores(){}
	
	function getOjectSpec($pk_value){
		$ret['profilo']=$this->session_vars['WFact'];
		$sql_query="select prefix from workflow where descr=:descr";
		$bind['descr']=$this->config_service['WF_NAME'];
		$sql=new query($this->connection);
		$sql->get_row($sql_query, $bind);
		$WFprefix=$sql->row['PREFIX'];
		$sql_query_2="select ID_STATO from {$WFprefix}_STATO where pk_service=:pk_service";
		$bind=null;
		$bind['pk_service']=$pk_value;
		$sql->get_row($sql_query_2, $bind);

		$ret['stato']=$sql->row['ID_STATO'];
		
		$ret['USER_TIP']=$this->session_vars['USER_TIP'];
		$ret['hasInteg']=false;
		if ($this->config_service['eQuery']){
			$sql_query="select count(*) as c from {$this->config_service['service']}_EQ where {$this->config_service['PK_SERVICE']}=$pk_value and stato in (0,2,5)";
			$sql->get_row($sql_query);
			if($sql->row['C']>0) {
				$ret['hasInteg']=true;
			}
			$_GET[$this->config_service['PK_SERVICE']]=$pk_value;
			$int=new Integrazioni($this->config_service, $this->connection, $ret['userid'], $ret['profilo'], $ret['USER_TIP'],$this->session_vars);
			if ($int->eq_int==''){
				$sql_query="select * from {$this->config_service['service']}_EQ where equery_int=(select max(equery_int) from {$this->config_service['service']}_EQ
				where {$this->config_service['PK_SERVICE']}=$pk_value and stato in (0,2,5)
				)";
				if ($sql->get_row($sql_query)){
					$int->eq_int=$sql->row['EQUERY_INT'];
					$int->stato=$sql->row['STATO'];
				}
			}
			$ret['int']=$int;
		}
		//Logger::send($ret);
		return $ret;
	}
	
	function query($store,$queryName,$query,$bind){
		if (isset($bind[$this->config_service['PK_SERVICE']])) $objectSpecification=$this->getOjectSpec($bind[$this->config_service['PK_SERVICE']]);
		else $objectSpecification=$this->getOjectSpec($bind['pk_service']);
		$where="";
			foreach ($query as $filter){
				if(!isset($filter['SELECTIVE_QUERY']) || $filter['SELECTIVE_QUERYNAMES'][$queryName] ){
				switch($filter['TYPE']){
					case 'STANDARD SQL':
						if($where!='') $where.=" ".$filter['JOIN'];
						$where.=" ".$filter['FILTER'];
						break;
					default:
					case 'SIMPLE':
						if($where!='') $where.=" ".$filter['JOIN'];
						$where.=" ".$this->buildWhere($filter);
						break;
					case 'COMPLEX':
						if($where!='') $where.=" ".$filter['JOIN'];
						$subWhere="";
						foreach ($filter as $subFilter){
							if($subWhere!='') $subWhere.=" ".$subFilter['JOIN'];
							$subWhere.=" ".$this->buildWhere($subFilter);
						}
						$where.=" ".$subWhere;
						break;
				}
			}
		}
		$dati_str="select * from {$store}_{$queryName} ";
		if($where!='') $dati_str.="where ".$where;
		$addWhere="";
		//Logger::send($objectSpecification['USER_TIP']);
		if ($objectSpecification['USER_TIP']!='DE'){
			//Logger::send("non � DE");
			$addWhere=" and t1.approved=1 ";
			if ($objectSpecification['hasInteg']){
					//Logger::send("c'� un integrazione");
				if ($objectSpecification['int']->role==$objectSpecification['profilo']){
					$addWhere="	and (t1.approved=1 or (keywords in (
					select 
					case 
						when visitnum_progr=0 and progr=1 then field
						when visitnum_progr=0 and progr>1 then field||'_'||progr
						else field||'_'||progr||'_'||visitnum_progr
					end as field
					from {$this->config_service['service']}_eqfield where {$this->configuration['PK_SERVICE']}=:pk_service
					and eq_int='{$objectSpecification['int']->eq_int}') and t1.approved is null))";
				}
				else{
						//Logger::send('non pu� creare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->role);
				}
				if (($objectSpecification['int']->isObserverRole($objectSpecification['profilo']) || $objectSpecification['int']->isApprovRole($objectSpecification['profilo'])) &&
				($objectSpecification['int']->stato==2 || $objectSpecification['int']->stato==5)
				){
					$addWhere="	and (t1.approved=1 or (keywords in (
									select 
									case 
										when visitnum_progr=0 and progr=1 then field
										when visitnum_progr=0 and progr>1 then field||'_'||progr
										else field||'_'||progr||'_'||visitnum_progr
									end as field
									from {$this->config_service['service']}_eqfield where {$this->configuration['PK_SERVICE']}=:pk_service
									and eq_int='{$objectSpecification['int']->eq_int}') and t1.approved is null))";
				}
					else{
						//Logger::send('non pu� approvare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->approv_role);
						//Logger::send('non pu� osservare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->observer_role);
				}

			}
		}else {
			if ($objectSpecification['hasInteg']){
		
				if ($objectSpecification['int']->stato==0 && $objectSpecification['int']->role!=$objectSpecification['profilo']){
					$addWhere="and not(keywords in (
				select 
				case 
					when visitnum_progr=0 and progr=1 then field
					when visitnum_progr=0 and progr>1 then field||'_'||progr
					else field||'_'||progr||'_'||visitnum_progr
				end as field
				from {$this->config_service['service']}_eqfield where {$this->configuration['PK_SERVICE']}=:pk_service
				and eq_int='{$objectSpecification['int']->eq_int}'
				) and t1.approved is null) ";
				}
				if (($objectSpecification['int']->stato==5 || $objectSpecification['int']->stato==2) &&
				!$objectSpecification['int']->isApprovRole($objectSpecification['profilo'])
				){
					$addWhere="and not(keywords in (
				select 
				case 
					when visitnum_progr=0 and progr=1 then field
					when visitnum_progr=0 and progr>1 then field||'_'||progr
					else field||'_'||progr||'_'||visitnum_progr
				end as field
				from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
				and eq_int='{$objectSpecification['int']->eq_int}'
				) and t1.approved is null) ";
				}
			}
			else {
				$addWhere="and (t1.approved is null or t1.approved=1)";
			}
		}
		
		$addField="";
		if ($objectSpecification['hasInteg'] && (
			(
				($objectSpecification['int']->isObserverRole($objectSpecification['profilo']) || $objectSpecification['int']->isApprovRole($objectSpecification['profilo'])) &&	($objectSpecification['int']->stato==2 || $objectSpecification['int']->stato==5)
			) || (
				$objectSpecification['int']->role==$objectSpecification['profilo'] && $objectSpecification['int']->eq_enabled
			)
		)
		
		){
			$addField=",(select eq_int from {$this->config_service['service']}_eqfield eq where {$this->configuration['PK_SERVICE']}=:pk_service
			and t1.keywords=case 
					when eq.visitnum_progr=0 and eq.progr=1 then eq.field
					when eq.visitnum_progr=0 and eq.progr>1 then eq.field||'_'||eq.progr
					else eq.field||'_'||eq.progr||'_'||eq.visitnum_progr
		      end			
			and eq.eq_int='{$objectSpecification['int']->eq_int}') as eq_int,
			(select action from {$this->config_service['service']}_eqfield eq where {$this->configuration['PK_SERVICE']}=:pk_service
			and t1.keywords=case 
					when eq.visitnum_progr=0 and eq.progr=1 then eq.field
					when eq.visitnum_progr=0 and eq.progr>1 then eq.field||'_'||eq.progr
					else eq.field||'_'||eq.progr||'_'||eq.visitnum_progr
		      end			
			and eq.eq_int='{$objectSpecification['int']->eq_int}') as action";
		}
		$str="select t2.*,t1.*{$addField} from docs t1, ($dati_str) t2 where t1.id_ref=t2.id_ref and t1.tipo_doc='Doc_Area' $addWhere order by t1.id desc";
		$sql=new query($this->connection);
		if (!isset($bind['pk_service'])) $bind['pk_service']=$bind[$this->config_service['PK_SERVICE']];
		$sql->exec($str,$bind); //binded
		Logger::send($str);
		Logger::send($bind);
		$thread=array();
		while($sql->get_row()){
			$sql->row['QUERYNAME']=$queryName;
			$thread[$sql->row['ID_REF']][]=$sql->row;
		}

		return $thread;
	}
	
	function buildWhere($filter,$index){
		$where="";
		//foreach ($query as $filter){
			
		
			switch(trim(strtolower($filter['OPERATOR']))){
				case 'in':
					
					
				case 'not in':
					$where.=$filter['PARAM'].' '.$filter['OPERATOR']." ({$filter['VALUE']})"; 
					break;
				case '>':
				case '>=':
					
				case '<':
					
				case '<=':
				
				case '=':
				
				case '!=':
					
				case 'like':
					
					$where.=$filter['PARAM'].' '.$filter['OPERATOR'];
					
					
					$where.=" {$filter['VALUE']}";
						
						
					break;
			}
		//}
		return $where;
	}
	
	function queryPrevious($id_doc){
		$str="select * from docs where id=(select max(id) from docs where id_ref=(select id_ref from docs where id=:id_doc) and id<:id_doc and approved=1)";
		$query=new query($this->connection);
		$bind['ID_DOC']=$id_doc;
		$query->get_row($str,$bind);
		return $query->row;
	}
	
	
	function queryLastVersion($store,$folder,$queryName,$PWC=false,$id_doc=0){
		//PWC = Private Working Copy
		//per le WCA $store non è interessante
		//inizio aggiunta where
		//Logger::send($this->config_service);
		//Logger::send($this->session_vars);
		//Logger::send('PWC:');
		//Logger::send($PWC);
		
		//Logger::send($this->session_vars);
		if(!$PWC){
		if (isset($this->session_vars[$this->config_service['PK_SERVICE']])) $objectSpecification=$this->getOjectSpec($this->session_vars[$this->config_service['PK_SERVICE']]);
		elseif($_POST[$this->config_service['PK_SERVICE']]) $objectSpecification=$this->getOjectSpec($_POST[$this->config_service['PK_SERVICE']]);
		elseif($_GET[$this->config_service['PK_SERVICE']]) $objectSpecification=$this->getOjectSpec($_GET[$this->config_service['PK_SERVICE']]);
		else $objectSpecification=$this->getOjectSpec($this->session_vars['pk_service']);
		$addWhere="";
		//Logger::send($objectSpecification['USER_TIP']);
		if ($objectSpecification['USER_TIP']!='DE'){
				//Logger::send("non � DE");
			$addWhere=" and t1.approved=1 ";
			if ($objectSpecification['hasInteg'] && !$objectSpecification['int']->isExcludedFromEquery($this->session_vars['VISITNUM'])){
				//Logger::send("c'� un integrazione");
				if ($objectSpecification['int']->role==$objectSpecification['profilo']){
					$addWhere="	and (t1.approved=1 or (keywords in (
					select 
					case 
						when visitnum_progr=0 and progr=1 then field
						when visitnum_progr=0 and progr>1 then field||'_'||progr
						else field||'_'||progr||'_'||visitnum_progr
					end as field
					from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
					and eq_int='{$objectSpecification['int']->eq_int}') and t1.approved is null))";
				}
				else{
						//Logger::send('non pu� creare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->role);
				}
				if (($objectSpecification['int']->isObserverRole($objectSpecification['profilo']) || $objectSpecification['int']->isApprovRole($objectSpecification['profilo'])) &&
				($objectSpecification['int']->stato==2 || $objectSpecification['int']->stato==5)
				){
					$addWhere="	and (t1.approved=1 or (keywords in (
									select 
									case 
										when visitnum_progr=0 and progr=1 then field
										when visitnum_progr=0 and progr>1 then field||'_'||progr
										else field||'_'||progr||'_'||visitnum_progr
									end as field
									from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
									and eq_int='{$objectSpecification['int']->eq_int}') and t1.approved is null))";
				}
				else{
						//Logger::send('non pu� approvare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->approv_role[$objectSpecification['int']->stato_obj]);
						//Logger::send('non pu� osservare equery perche � : '.$objectSpecification['profilo'].' invece di '.$objectSpecification['int']->observer_role[$objectSpecification['int']->stato_obj]);
				}

			}
		}else {
			if ($objectSpecification['hasInteg'] && !$objectSpecification['int']->isExcludedFromEquery($this->session_vars['VISITNUM'])){
				//Logger::send("Girogio disse");
				//Logger::send($objectSpecification['int']->stato);
				if ($objectSpecification['int']->stato==0 && $objectSpecification['int']->role!=$objectSpecification['profilo']){
					$addWhere="and not(keywords in (
				select 
				case 
					when visitnum_progr=0 and progr=1 then field
					when visitnum_progr=0 and progr>1 then field||'_'||progr
					else field||'_'||progr||'_'||visitnum_progr
				end as field
				from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
				and eq_int='{$objectSpecification['int']->eq_int}'
				) and t1.approved is null) ";
				}
				if ($objectSpecification['int']->role==$objectSpecification['profilo']){
					$addWhere="	and (t1.approved=1 or (keywords in (
					select 
					case 
						when visitnum_progr=0 and progr=1 then field
						when visitnum_progr=0 and progr>1 then field||'_'||progr
						else field||'_'||progr||'_'||visitnum_progr
					end as field
					from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
					and eq_int='{$objectSpecification['int']->eq_int}') and t1.approved is null))";
				}
				if (($objectSpecification['int']->stato==5 || $objectSpecification['int']->stato==2) &&
				!$objectSpecification['int']->isApprovRole($objectSpecification['profilo'])
				){
					$addWhere="and not(keywords in (
				select 
				case 
					when visitnum_progr=0 and progr=1 then field
					when visitnum_progr=0 and progr>1 then field||'_'||progr
					else field||'_'||progr||'_'||visitnum_progr
				end as field
				from {$this->config_service['service']}_eqfield where {$this->config_service['PK_SERVICE']}=:pk_service
				and eq_int='{$objectSpecification['int']->eq_int}'
				) and t1.approved is null) ";
				}
			}
			else {
				$addWhere="and (t1.approved is null or t1.approved=1    )";
			}
		}
		}
		else{
			$addWhere="and (t1.approved is null or t1.approved=1)";
		}
		unset($bind);
		if($id_doc>0) {
			$addWhere.=" and id=:id_doc";
			$bind['ID_DOC']=$id_doc;
		}
		//Logger::send('addwhere:');
		//Logger::send($addWhere);
		//Logger::send('ObjectSpec:');
		//Logger::send($objectSpecification);
		//fine aggiunta where
		$id_area=$folder;
		$keywords=$queryName;
		$sql=new query($this->connection);

		$sql_query="select * from docs  where id =
			(select max(id) from docs t1 where tipo_doc='Doc_Area' and id_tipo_ref=:id_area and keywords=:keywords  $addWhere)";
//		echo "<hr>".$sql_query."<hr>";
		//Logger::send($sql_query);
		
		$bind['ID_AREA']=$id_area;
		$bind['KEYWORDS']=$keywords;
		$bind['PK_SERVICE']=$this->session_vars[$this->config_service['PK_SERVICE']];
		//Logger::send($bind);
		//Logger::send($this->config_service['PK_SERVICE']);
		$sql->exec($sql_query,$bind); //binded
		if($sql->get_row()){
			return $sql->row;
		}
		else {
			return ;
		}
	}
	function docToArray($docObj){
		return $docObj;
	}
	function queryChildren($node){}
	function queryParents(){}
	function fetchMore(){}
	function update(){}
	function describe(){}
	function get(){}


	function save($store,$folder,$queryName){
		// list of valid extensions, ex. array("jpeg", "xml", "bmp")
		$allowedExtensions = array();
		// max file size in bytes
		$sizeLimit = 10 * 1024 * 1024;
		include_once "WCA/wom_config.inc";

		$splits=explode(",", $testo_config['doc_ext_list']);
		foreach ($splits as $key=>$val){
			if ($val!='') $ExtAllowed[strtolower($val)]=true;
		}
		if (!isset($_GET['qqfile']))
		$fileName=$_FILES['qqfile']['name'];
		else $fileName=$_GET['qqfile'];
		$splits=explode(".", $fileName);
		$ext=$splits[count($splits)-1];
		$ext=strtolower($ext);
		if ($ExtAllowed[".".$ext]){

		}else if(count($ExtAllowed)>0) {
			die('{error: '.json_encode("Estensione \"$ext\" non supportata").'}');
		}
		//die('{success: true, fileName: '.json_encode($fileName).', keywords: '.json_encode($_GET['keywords']).', txtmsg: '.json_encode($txtmsg).'}');

		$conn=new dbconn();
		$sql=new query($conn);
		$lastDoc=$this->queryLastVersion($store,$folder,$queryName,true);
		$lastDocArray=$this->docToArray($lastDoc);
		$id_ref=$lastDocArray['ID_REF'];


		$id_area=$folder;

		$sql_query_user="select nome, cognome from ana_utenti where userid='{$_SERVER['REMOTE_USER']}'";
		$sql->get_row($sql_query_user);
		$autore=$sql->row['NOME']." ".$sql->row['COGNOME'];


		$sql_query_id="select docs_id.nextval as id_doc from dual";
		$sql->get_row($sql_query_id);
		$id=$sql->row['ID_DOC'];
		if ($id_ref=='') $id_ref=$id;

		$values['ID']=$id;
		$values['EXT']=$ext;
		$values['USERID']=$_SERVER['REMOTE_USER'];
		$values['ID_REF']=$id_ref;
		$values['TIPO_DOC']="Doc_Area";
		$values['DATA']="sysdate";
		$values['NOME_FILE']=str_replace(" ", "_", $fileName);
		$values['AUTORE']=$autore;
		$values['PRJ']=$prj;
		$values['ID_TIPO_REF']=$id_area;
		$values['KEYWORDS']=$_GET['keywords'];
		$values['TOPIC']=$_GET['topic'];
		$values['TITOLO']=$_GET['thread'];
		$sql_query_update="update docs set TIPO_DOC='Trash' where ID_REF=$id_ref and approved is null";
		$sql->ins_upd($sql_query_update);
		$pk=null;
		$sql->insert($values, "DOCS", $pk);

		$conn->commit();

		if (isset($_GET['qqfile'])) $_GET['qqfile']="Doc_Area{$id}.{$ext}";
		else $_FILES['qqfile']['name']="Doc_Area{$id}.{$ext}";
		
		$uploader = new qqFileUploader($allowedExtensions, $sizeLimit);
		$result = $uploader->handleUpload('WCA/docs/');


		$txtmsg="<a href='#'>pippo</a>";

		$result['fileName']=$fileName;
		$result['keywords']=$_GET['keywords'];

		$result['txtmsg']=field_file_cme::getAttachedDoc($conn,$store, $folder, $queryName);

		echo htmlspecialchars(json_encode($result), ENT_NOQUOTES);
		die();

	}
	function delete($id){
		include_once "WCA/wom_config.inc";
		$conn=new dbconn();
		$sql=new query($conn);
		$sql_query="select id_tipo_ref, keywords from docs where id='{$id}'";
		$sql->get_row($sql_query);
		$id_area=$sql->row['ID_TIPO_REF'];
		$keywords=$sql->row['KEYWORDS'];
		$result['success']=true;
		$result['div']=$keywords."_TEXT";
		$result['txtmsg']="ciao";
		//sql-injection CARLO
		//$sql_update="update docs set tipo_doc='Trash', delete_date=sysdate, delete_user='{$_SERVER['REMOTE_USER']}' where id='{$_GET['DeleteIdDoc']}'";

		$sql_update="update docs set tipo_doc='Trash', delete_date=sysdate, delete_user=:delete_user where id=:deleteIdDoc";
		$bindVars['delete_user']=$_SERVER['REMOTE_USER'];
		$bindVars['deleteIdDoc']=$id;
		$sql->ins_upd($sql_update, $bindVars);//binded
		$conn->commit();
		$result['success']=true;
		$result['div']=$keywords."_TEXT";
		if (class_exists("field_file_cme")){
			$result['txtmsg']=field_file_cme::getAttachedDoc($conn,$this->service, $id_area, $keywords);
			echo htmlspecialchars(json_encode($result), ENT_NOQUOTES);
			die();
		}
		
	}
	function createFolder(){}
	function deleteFolder(){}
	function folderExist(){}
	function retrieveFolder(){}
	function move(){}
	function copy(){}
	function link(){}
	function viewFolder($queryResultSet){}

	function viewThread(){}
	static function downloadHref($id,$baseUri=null){
		return self::generalHref('download', $id, $baseUri);
	}
    static function detailHref($id,$queryName,$baseUri=null){
        return self::generalHref('detail', $id, $baseUri)."&CMELQueryName={$queryName}";
    }
    static function generalHref($action,$id,$baseUri=null){
        if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
        $href="{$baseUri}&CMELayer=true&CMELAction={$action}&CMELRequestRef={$id}";
        return $href;
    }

    static function approveDocument($id,$conn){
        $query=new query($conn);
        $str="update docs set approved=1 where tipo_doc=:tipo_doc and id=:id";
        $bind['TIPO_DOC']='Doc_Area';
        $bind['ID']=$id;
        $query->ins_upd($str,$bind);
    }
	function folder_doc_mini($nome_area,$queryResultSet,$baseUri,$folder,$folder_type='TOPIC'){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		global $config_document;
		global $testo_config;
		$this->tipo_doc="Doc_Area";
		$this->id_tipo_ref=$id_area;
		$sql=new query($this->connection);
		//sql-injection non necessaria CARLO
		$sql->ins_upd("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");//non richiede binding
		
		$folder_img="<img src=\"images/cme/folder-doc-mo.gif\" width=30 border=0>";
		/*$sql_query="
			select
				count(*) as n_r_thread,
				topic,
				max(data) as last_ins_dt
			from docs
				where tipo_doc='{$this->tipo_doc}'
				and id_tipo_ref='{$this->id_tipo_ref}'
				and id_ref=id
			group by topic";
//		echo $sql_query;
		$sql->set_sql($sql_query);
		$sql->exec(); //commentata */
		$c=0;
		global $userid_ins;
		$html.="<table border=0 width=100%><tr><td valign=top width=80%>
		<fieldset><legend class=mttl>$nome_area</legend>
		<table border=0 cellpadding=4 width=100% align=center bgcolor=white><tr align=center>
			<tr>
				<td class=mttl2>&nbsp;</td>
				<td class=mttl2>Tipo Documento</td>
				<td class=mttl2>N. documenti</td>
			</tr>
			";
		//Logger::send($queryResultSet);
		foreach ($queryResultSet as $thread){
			$topics[$thread[0][$folder_type]]['COUNT']++;
			$topics[$thread[0][$folder_type]]['ID_AREA']=$thread[0]['ID_TIPO_REF'];
		}
		//Logger::send($topics);
		foreach ($topics as $topic => $info){
			$last_doc=$thread[0];
			/*if ($last_doc['TOPIC']=='') $html.=$this->folder_inner_doc_mini("", $c, "", $_GET['VAR'],$_GET['SERVICE'],$_GET['PRJ'],$_GET['USER_TIP']);
			else {*/
			$html.="
				<tr>
				<td>
					<a href=\"{$baseUri}&CMELayer=true&CMELAction=folder&CMELFolder={$folder}/{$topic}\" title=''>$folder_img</a></td>
				<td><a href=\"{$baseUri}&CMELayer=true&CMELAction=folder&CMELFolder={$folder}/{$topic}\" title=''>{$topic}</b></a></td>
				<td><b>{$info['COUNT']}</b></td>
				</tr>
				";
			/*}*/
			$c++;
		}
		if (count($topics)==0){
			$html.="
				<tr>
					<td colspan=2 align=center><b><font size=3>Non sono presenti documenti</font></b></td>
					<td><b><font size=3>0</font></b></td>
				</tr>
			";
		}
		$html.="</table></fieldset>";
		//aggiunta di Edo Gargano per aggiungere link scarica tutti gli allegati
		if (count($queryResultSet)>0){
			
			$html.="<br />&nbsp;&nbsp;&nbsp;<a href=\"{$baseUri}CMELayer=true&CMELAction=downloadAll&CMELFolder={$folder}\">Scarica tutti i documenti in formato .zip</a>";
		}
		return $html;
	}

	function folder_inner_doc_mini($areaName,$queryResultSet,$baseUri){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		$c_idx=0;
		global $onload;
		global $incolla;
		global $config_document;
		global $userid_ins;
		global $userid_ins_nome;
		global $testo_config;
		global $in;
		$in=$this->session_vars;
		$topic=$areaName;
		if($in['language']) $lingua="<input type='hidden' name='language' value='{$in['language']}'>";
		$sql=new query($this->connection);
		//sql-injection non necessaria CARLO
		$sql->ins_upd("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");//non richiede binding
		$topic=preg_replace("/'/", "''", $topic);
		$thread=$in['thread'];
		$thread=preg_replace("/'/", "''", $thread);

		$thread=str_replace("à","%",$thread);
		$thread=str_replace("è","%",$thread);
		$thread=str_replace("ì","%",$thread);
		$thread=str_replace("ò","%",$thread);
		$thread=str_replace("ù","%",$thread);
		$bind_array['TITOLO']=$thread;

		$prj_get=$prj_get*100000;
		$id_prat=$this->id_tipo_ref-$prj_get;

		if($service_xmr!="") {
			$select_eq_table="select count(*) conto from user_tables where table_name=:table_name";
			$sql_eq_table=new query($this->connection);
			unset($bind_service);
			$bind_service['TABLE_NAME']=strtoupper($service_xmr)."_EQ";
			$sql_eq_table->exec($select_eq_table,$bind_service);//binded
			$sql_eq_table->get_row();
			$sql2=new query($this->connection);
			if($sql_eq_table->row['CONTO']>0){
		$query_eq="select id_prat,stato,equery_int from {$service_xmr}_eq where equery_int =(SELECT max(EQUERY_INT) 
		FROM {$service_xmr}_EQFIELD field, {$service_xmr}_eq eq
		WHERE eq.id_prat=field.id_prat(+)
		and EQ.{$this->config_service['PK_SERVICE']}  = :pk_service
		and EQ.EQUERY_INT=field.EQ_INT(+)
		AND field.FIELD =:var_xmr)";
//		echo $query_eq;
		unset($bind);
		$bind['PK_SERVICE']=$this->session_vars[$this->config_service['PK_SERVICE']];
		$bind['VAR_XMR']=$var_xmr;
		$sql2->exec($query_eq,$bind); //binded
		$sql2->get_row();
			}
		}
//		print_r($in);
		if($sql2->row['STATO']=='0' && $user_tip=="DE" || ($equery_int!="" && $stato=="")) {
		//PENULTIMO!!!
		$penultimo=true;
	
		} 

		$c=$c_idx;
		$empty=true;

		foreach ($queryResultSet as $thread){
			if($penultimo){
				array_shift($thread);
			}
			$empty=false;
			if ($c==4){
				$html.="</tr><tr>";
				$c=0;
			}

			$i=0;
			$revisioni="";
			$content_menu=null;
			$img_delete=null;
			
				$id_last_version=$thread[0]['ID'];
				$n_rev=count($thread)-$i-1;
				$version="Revisione n.ro $n_rev";
				if ($i==0) {
					$doc_img=$single_doc_img;
					$version="Last version";
					$move_to="";
					if ($topic!='') $move_to.="<li><a class=\"link_menu\" href=\"index.php?id_area={$this->id_tipo_ref}&move_doc_to_topic={$sql->row['ID']}&topic=\"><b>Nessuno</b></a></li>";
					foreach($topics as $key=>$val){
						if ($val!='') $move_to.="<li><a href=\"index.php?id_area={$this->id_tipo_ref}&move_doc_to_topic={$sql->row['ID']}&topic={$val}\" class=\"link_menu\">$val</a></li>";
					}
					//print_r($sql2->row);
					$img_download='<img src="images/cme/download_2.gif" border=0 width=15>';
					if ($thread[0]['APPROVED']=='' && $in['AF']!=2) $img_delete="<img src=\"images/cme/ics.gif\" alt=\"Elimina\" title=\"Elimina\" border=0 width=15>";
					if ($thread[0]['EXT']=='doc' || $thread[0]['EXT']=='rtf'|| $thread[0]['EXT']=='docx') $img_download="<img src=\"images/cme/doc.jpg\" border=0 width=15>";
					if ($thread[0]['EXT']=='pdf') $img_download="<img src=\"images/cme/pdf.jpg\" border=0 width=15>";
					if((strtoupper($thread[0]['EXT'])=='PPS' || strtoupper($sql2->row['EXT'])=='PPT')) $img_download="<img src=\"images/cme/pps.jpg\" border=0 height=15>";
					if(strtoupper($thread[0]['EXT'])=='XLS') $img_download="<img src=\"images/cme/excel-icona.gif\" border=0 height=15>";
				}
				else {
					$img_download='<img src="images/cme/download_2.gif" border=0 width=15>';
					if ($thread[0]['EXT']=='doc' || $thread[0]['EXT']=='rtf'|| $thread[0]['EXT']=='docx') $img_download="<img src=\"images/cme/doc.jpg\" border=0 width=15>";
					if ($thread[0]['EXT']=='pdf') $img_download="<img src=\"images/cme/pdf.jpg\" border=0 width=15>";
					if((strtoupper($thread[0]['EXT'])=='PPS' || strtoupper($thread[0]['EXT'])=='PPT')) $img_download="<img src=\"images/cme/pps.jpg\" border=0 height=15>";
					if(strtoupper($thread[0]['EXT'])=='XLS') $img_download="<img src=\"images/cme/excel-icona.gif\" border=0 height=15>";
				}
				$i++;
			
			global $in;
			global $Superuser;
			$publish="";
			if ($in['remote_userid']==$userid_ins || $Superuser) $publish="<li><a onclick=\"if (!confirm('".$this->testi('Doc_Area_publish_confirm')."')) return false;\" href=\"index.php?id_area={$this->id_tipo_ref}&tab=3&publish={$sql->row['ID']}\">".$this->testi('Colonna_publish')."</a></li>";
			//echo "<hr>$publish<hr>";
			if ($thread[0]['APPROVED']=='1'){
				$approved="<li>".$this->testi('Doc_Area_approved_by')." $userid_ins_nome<br>{$thread[0]['APPROV_DT']}</li>";
				$approve_cell="<br>".$this->testi('Doc_Area_approved_by')." $userid_ins_nome<br>{$thread[0]['APPROV_DT']}";
			}
			else {
				global $prj;
				$curr_id=$in['id_area']-($prj*1000);


				if ($in['remote_userid']==$userid_ins ) $approved="<li><a onclick=\"if (!confirm('".$this->testi('Doc_Area_approv_confirm')."')) return false;\" href=\"index.php?id_area={$this->id_tipo_ref}&tab=3&approv={$sql->row['ID']}\">".$this->testi('Approvazioni_area_approva')."</a></li>";
				else $approved="<li>da approvare</li>";
				$approve_cell="<br>da approvare";
			}
			if ($img_delete!=''){
				if($config_document['rimuovi_text']) $img_delete.="<span style=\"font-size:9px;\">{$testo_config['Button_remove_file']}eliminaa</span>";
				//print_r($_SERVER['REQUEST_URI']);
				$param=null;
				foreach ($_GET as $key=>$val){
					$param.="$key=$val&";
				}
				//$param=rtrim($param, "&");
				//aggiunta di Verri per eliminare la X rossa per la rimozione
				if($config_document['nodelete'] !=true){
					$param.="&DeleteIdDoc={$sql->row['LAST_VER']}";
					$add_delete="<a href=\"{$_SERVER['PHP_SELF']}?$param\">$img_delete</a>";
				}
			}
			if(true) {
				$table.="
				<tr>
					<td id='doc_id_{$thread[0]['ID']}' align=center> 
						<a target=\"_new\" href=\"".(self::downloadHref($thread[0]['ID'],$baseUri))."\">$img_download</a>
						$add_delete
					</td>
				
	
				
					<td>
						E' stato allegato il file <a target=\"_new\" id=\"file_link\" href=\"".(self::downloadHref($thread[0]['ID'],$baseUri))."\">{$thread[0]['NOME_FILE']}</a> in data: <b>{$thread[0]['DATA']}</b><br><br>
					</td>
				</tr>";
			}

			if ($_GET['AF']==1 || true) $table.="
			<tr>
				<td colspan=6>
					$lingua ".'$this->mini_form(\'Doc_Area\', $this->id_tipo_ref,$sql->row[\'ID\'], false,$topic)'."
				</td>
			</tr>";
			$c++;
		}
		//if ($empty && $_GET['AF']==1) $html=$this->mini_form('Doc_Area', $this->id_tipo_ref,null, false,$topic);
		//else {
		if ($table=='') $table="nessun allegato presente";
		$html="
				<table border=0 cellpadding=0 cellspacing=1 width=100% align=center>
					<!--tr>
						<td class=mttl2>&nbsp;</td>
						<td class=mttl2>Dettagli</td>
						<td class=mttl2>Autore</td>
						<td class=mttl2>Nome file</td>
						<td class=mttl2>Data</td>
						<td class=mttl2>N.ro revisioni</td>
					</tr-->
					$table
				</table>
				";
		//	}
		if($c!=0) $html.="</tr><tr>";
		return $html;
	}

	function show_area_mini($nomeArea,$queryResultSet,$baseUri,$baseFolder,$xmr_tip=null){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		//field_file_doc vecchia maniera usa questa EDO
		global $in;
		global $conn;
		global $config_document;
		global $config_buttons;
		global $sid;
		$this->id_tipo_ref=$id_area;
		$this->tipo_doc='Doc_Area';
		$this->connection=$conn;
		$sql=new query($conn);

		$nome_area=$nomeArea;
		$html.="<fieldset>
				<table border=0 cellpadding=4  width=100% align=center bgcolor=white>

				<tr align=center><td>";
			
			if ($in['thread']=='' || true)  {
				$html.=$this->folder_inner_doc_mini_no_title($nomeArea,$queryResultSet,$baseUri,$baseFolder);
			} else {
				//non mi interessa
				$html.=$this->folder_inner_doc_mini($nomeArea,$queryResultSet,$baseUri);
			}
			$html.="</td></tr></table></fieldset>";
		
		return $html;
	}

	function folder_inner_doc_mini_no_title($areaName,$queryResultSet,$baseUri,$baseFolder){
		$c_idx=0;
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		//Logger::send("folder_inner_doc_mini_no_title");
		global $onload;
		global $incolla;
		global $config_document;
		global $userid_ins;
		global $userid_ins_nome;
		global $in;
		$in=$this->session_vars;
		$topic=$areaName;
		$sql=new query($this->connection);
		//sql-injection non necessaria CARLO
		$sql->ins_upd("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");//non richiede binding
		$topic_=preg_replace("/'/", "''", $topic);


		$sql->set_sql($sql_query);
		$sql->exec(); //non richiede binding
		$c=$c_idx;
		$empty=true;
		//while ($sql->get_row()){
		foreach ($queryResultSet as $thread){
			$empty=false;
			if ($c==4){
				$html.="</tr><tr>";
				$c=0;
			}

			$img_download='<img src="images/cme/download_2.gif" border=0 width=15>';
			$img_dettagli='<img src="images/cme/copia.gif" border=0 width=15>';
			if ($thread[0]['EXT']=='doc' || $thread[0]['EXT']=='rtf'|| $thread[0]['EXT']=='docx') $img_download="<img src=\"images/cme/doc.jpg\" border=0 width=15>";
			if ($thread[0]['EXT']=='pdf') $img_download="<img src=\"images/cme/pdf.jpg\" border=0 width=15>";
			if((strtoupper($thread[0]['EXT'])=='PPS' || strtoupper($thread[0]['EXT'])=='PPT')) $img_download="<img src=\"images/cme/pps.jpg\" border=0 height=15>";
			if(strtoupper($thread[0]['EXT'])=='XLS') $img_download="<img src=\"images/cme/excel-icona.gif\" border=0 height=15>";
			$i++;

			global $in;
			global $Superuser;
			$publish="";
			if ($in['remote_userid']==$userid_ins || $Superuser) $publish="<li><a onclick=\"if (!confirm('".$this->testi('Doc_Area_publish_confirm')."')) return false;\" href=\"index.php?id_area={$this->id_tipo_ref}&tab=3&publish={$sql->row['ID']}\">".$this->testi('Colonna_publish')."</a></li>";
			//echo "<hr>$publish<hr>";
			if ($thread[0]['APPROVED']=='1'){
				$approved="<li>".$this->testi('Doc_Area_approved_by')." $userid_ins_nome<br>{$sql->row['APPROV_DT']}</li>";
				$approve_cell="<br>".$this->testi('Doc_Area_approved_by')." $userid_ins_nome<br>{$sql->row['APPROV_DT']}";
			}
			else {
				global $prj;
				$curr_id=$in['id_area']-($prj*1000);

				if ($in['remote_userid']==$userid_ins ) $approved="<li><a onclick=\"if (!confirm('".$this->testi('Doc_Area_approv_confirm')."')) return false;\" href=\"index.php?id_area={$this->id_tipo_ref}&tab=3&approv={$sql->row['ID']}\">".$this->testi('Approvazioni_area_approva')."</a></li>";
				else $approved="<li>aa</li>";
				$approve_cell="<br>bb";
			}
			$addTD="";
			$infoArray=var_export($thread[0],true);
			foreach ($this->configuration['ADD_INFO'] as $currInfo){
				//$currInfoValue=preg_replace ( "/\[(.*?)\]/e", "CMELInfoReplace('\\1',{$infoArray})", $currInfo['VALUE'] );
				$currInfoValue=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return CMELInfoReplace($matches[1],$infoArray);}, $currInfo['VALUE'] );
				
				$addTD.="<td class=mttl2>{$currInfoValue}</td>";
			}
			if ($thread[0]['EQ_INT']!=''){
				$addImg="<img src='images/eq_img.png' height='15'/>";
				if ($thread[0]['ACTION']==2) $addImg="<img src='images/iphone_delete_icon.png' height='15'/>";
				if ($thread[0]['ACTION']==1) $addImg="<img src='images/plus-icon.png' height='15'/>";
			}else $addImg="";
			$table.="
			<tr>
				<td id='doc_id_{$thread[0]['ID']}' align=center>
			$addImg
					<a target=\"_new\" href=\"".(self::downloadHref($thread[0]['ID'],$baseUri))."\">$img_download</a>
				</td>
				<td id='doc_id_{$thread[0]['ID']}' align=center>
					<a href=\"{$baseUri}&CMELayer=true&CMELAction=detail&CMELQueryName={$thread[0]['QUERYNAME']}&CMELRequestRef={$thread[0]['ID']}\">$img_dettagli</a>
				</td>
				<td>
					<b>{$thread[0]['TITOLO']}</b>
				</td>
				{$addTD}
				<!--td  align=center>
					<a class=\"link_menu\" href=\"index.php?tab=3&id_area={$this->id_tipo_ref}&id_doc={$thread[0]['LAST_VER']}&id_ref={$sql->row['ID']}\">
					<img src=\"images/cme/copia.gif\" border=0>
					</a>
				</td-->
				<td>
					<a target=\"_new\" href=\"".(self::downloadHref($thread[0]['ID'],$baseUri))."\">{$thread[0]['NOME_FILE']}&nbsp;&nbsp;</a>
				</td>
				<td>
					<b>{$thread[0]['DATA']}</b>
				</td>
				<td>
					<b>".(count($thread)-1)."</b>
				</td>
			</tr>
			";
			$c++;
		}

		$nome_area=$nomeArea;
		foreach ($this->configuration['ADD_INFO'] as $currInfo){
			$addTH.="<td class=mttl2>{$currInfo['TITLE']}</td>";
		}
		$html="
			<a href=\"{$baseUri}&CMELayer=true&CMELAction=folder&CMELFolder={$baseFolder}\">Torna all'indice della documentazione</a><br><br><br>
				<legend class=mttl> $areaName</legend>

				<table border=0 cellpadding=0 cellspacing=1 width=100% align=center>
					<tr>
						<td class=mttl2>Download&nbsp;&nbsp;</td>
						<td class=mttl2>Dettagli&nbsp;&nbsp;</td>
						<td class=mttl2>Titolo</td>
						{$addTH}
						<!--td class=mttl2>Dettagli</td-->
						<td class=mttl2>Nome file</td>
						<td class=mttl2>Data</td>
						<td class=mttl2>N.ro revisioni</td>
					</tr>
					$table
				</table>

				";
		return $html;
	}

	function doc_details_mini($row, $baseUri, $n_row,$tot,$selected=null){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		global $in;
		global $conn;
		global $config_document;
		$image="<img src=\"images/cme/download_2.gif\" border=0 height=15>";
		if (strtoupper($row['EXT'])=='DOC' || strtoupper($row['EXT'])=='RTF' || strtoupper($row['EXT'])=='DOCX' ) $image="<img src=\"images/cme/doc.jpg\" border=0 height=20>";
		if (strtoupper($row['EXT'])=='PDF') $image="<img src=\"images/cme/pdf.jpg\" border=0 height=20>";
		if((strtoupper($row['EXT'])=='PPS' ||strtoupper($row['EXT'])=='PPT') && $config_document['nuove_icone']) $image="<img src=\"images/cme/pps.jpg\" border=0 height=20>";
		if(strtoupper($row['EXT'])=='XLS' && $config_document['nuove_icone']) $image="<img src=\"images/cme/excel-icona.gif\" border=0 height=20>";

		/*		$viewed_list="<table border=0 width=98%><tr><th class=mttl>".$this->testi('Nome')."</th><th class=mttl>".$this->testi('Data')."</th></tr>";*/
		/*while ($sql->get_row()){
		$viewed_list_rows.="<tr><td>{$sql->row['NOME']}</td><td>{$sql->row['DATA']}<br>".$this->testi('GMT')."</td></tr>";
		}*/
		//if ($viewed_list_rows=='') $viewed_list='<b>'.$this->testi('nessuno').'</b>';
		//else $viewed_list.="$viewed_list_rows</table>";

		/*$downloaded_list="<table border=0 width=98%><tr><th class=mttl>".$this->testi('Nome')."</th><th class=mttl>".$this->testi('Data')."</th></tr>";*/
		/*while ($sql->get_row()){
		$downloaded_list_rows.="<tr><td>{$sql->row['NOME']}</td><td>{$sql->row['DATA']}<br>".$this->testi('GMT')."</td></tr>";
		}*/
		/*	if ($downloaded_list_rows=='') $downloaded_list='<b>'.$this->testi('nessuno').'</b>';
		else $downloaded_list.="$downloaded_list_rows</table>";*/
		$colspan[]=8;
		$colspan[]=4;
		$colspan[]=3;
		//$usr_o=new user_gest();
		if (!$selected) $bgcolor="#E6EBEC";
		else $bgcolor="#FEC158";
		$rev=$tot-$n_row;
		$version="$rev<sup>th</sup> rev";
		if ($rev==1) $version="$rev<sup>st</sup> rev";
		if ($rev==2) $version="$rev<sup>nd</sup> rev";
		if ($rev==3) $version="$rev<sup>rd</sup> rev";
		if ($n_row==1) $version='Ultima Versione';
		if ($n_row==$tot) $version='Versione Originale';

		$html="
					<tr bgcolor=$bgcolor>
						<th colspan={$colspan[0]} align=left><a name='{$row['ID']}'></a>$version</th>
					</tr>
					<tr>
						
						<th class=mttl2 colspan={$colspan[1]}>
							<table border=0 width=100% >
								<tr>
									<td><b>Inserito da</b>: {$row['AUTORE']}</td>";
		//print_r($row);
		if($row['TIPO_DOC']=='Doc_Area' || $row['TIPO_DOC']=='Riunioni')$html.="<td align=center><b>Data</b>: {$row['DATA']}</td>
												<td align=right><a href=\"".(self::downloadHref($row['ID'],$baseUri))."\" title=''>{$image}&nbsp;{$row['NOME_FILE']}</a></td>";
		$html.="

								</tr>
							</table>
						</th>
						</tr>
						";
		/*	if(!isset($config_document['no_view_list']) || !$config_document['no_view_list'])
		$html.="
		<tr>
		<td colspan=2 width=20%>
		<b><a href=\"#\" onclick=\"show_hide('viewed_{$row['ID']}');return false;\" title=''>(".$this->testi('visto')." ".$this->testi('by').")</a></b><br>

		</td>
		<td colspan=2 width=20%>
		<b><a href=\"#\" onclick=\"show_hide('downloaded_{$row['ID']}');return false;\" title='".$this->testi('link_scaricato_da')."'>(".$this->testi('scaricato')." ".$this->testi('by').")</a></b><br>

		</td>

		</tr>
		<tr>
		<td colspan=2 valign=top><fieldset id='viewed_{$row['ID']}' style=\"display:none\" title='".$this->testi('link_visto_da')."'><legend>".$this->testi('visto')." ".$this->testi('by')."</legend>
		$viewed_list
		</fieldset></td>
		<td colspan=2 valign=top><fieldset  id='downloaded_{$row['ID']}' style=\"display:none\" title='".$this->testi('link_scaricato_da')."'><legend>".$this->testi('scaricato')." ".$this->testi('by')."</legend>
		$downloaded_list
		</fieldset></td>



		</tr>";*/
		return $html;

	}
	function show_doc_mini($areaName,$queryResultSet,$baseUri,$id_doc, $intestazione=null){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		global $in;
		global $conn;
		global $Super_User;
		global $config_document;

		$coord_name=$sql->row['NOME'];

		$i=0;
		$thread=array_pop($queryResultSet);
		$tot=count($thread);
		foreach ($thread as $doc){
			$thread_name=$doc['TITOLO'];
			$topic=$doc['TOPIC'];
			$i++;

			if ($i==1) $selected=true;
			else $selected=false;
			$body.=$this->doc_details_mini($doc, $baseUri, $i,$tot,$selected);
		}


		$nome_area=$sql2->row['NOME_AREA'];
		$link_back="javascript:history.back();";
		if ($intestazione!='') global $link_stampa;
		$new_rev="";
		$html="
			<fieldset><legend class=mttl> &lt; <a href=\"$link_back\">$topic</a></legend>
			<p class=titolo>{$thread_name}</p>
				<table border=0 width=100% cellpadding=6>
					$body
				</table>
			</fieldset>
			<a href=\"$link_back\">&lt; Indietro</a>
		";
		return $html;
	}

	function downloadable(){
		//le regole sono da definire per servizio segue esempio non ancora testato probabilmente non funzionante :D
		return true;
	}
	function testi($keyword) {

		require_once("CMELayer_testi.inc");
		//		die($testo_config['Menu_principale_riunione']);
		$txt=$testo_config[$keyword];

		return $txt;
	}
		/*esempio
	function downloadable($store,$docId){
		global $conn;
		global $in;
		$id=$docId;
		$tipo_doc='Doc_Area';
		//if($tipo_doc="APF_Result") return true;
		$sql_query="select rule from users_group where userid='{$in['remote_userid']}' and id_group is null";
		$sql=new query($conn);
		$sql->set_sql($sql_query);
		$sql->exec();//commentata
		$sql->get_row();
		//if ($sql->row['RULE']>2) return true;
		//if ($in['remote_userid']==$userid_ins) return true;
		if ($tipo_doc=='Doc_Area'){
			$sql_query="select count(*) as conto from ".txt('wom_user_ref')." where tipo_ref='Doc_Area' and USERID='{$in['remote_userid']}' and id_ref='$id_tipo_ref'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//commentata
			$sql->get_row();
			if ($sql->row['CONTO']>0) return true;
			//L'utente non � abilitato all'area, quindi controllo che non sia un documento linkato da un forum a cui l'utente ha accesso
			$sql_query="select count(*) as conto from forum where id_forum in (select id_ref from ".txt('wom_user_ref')." where userid='{$in['remote_userid']}' and tipo_ref='Forum') and doc_link='{$id}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//commentata
			$sql->get_row();
			if ($sql->row['CONTO']>0) return true;
		}
		
		return false;
	}
	*/
	function download($store,$docId){
		ob_clean();
		$id=$docId;
		$query="select tipo_doc,id_tipo_ref,userid,ext, nome_file from docs where id=:id";
		$bind['ID']=$id;
		//echo $query;
		$sql=new query($this->connection);
		$sql->set_sql($query);
		$sql->exec($query,$bind);//binded
		$sql->get_row();
		$tipo_doc=$sql->row['TIPO_DOC'];
		$id_tipo_ref=$sql->row['ID_TIPO_REF'];
		$userid_ins=$sql->row['USERID'];
		$ext=$sql->row['EXT'];
		$nome_file=$sql->row['NOME_FILE'];
		if ($this->downloadable($store,$docId)){
			//echo "here";
			$dir=$_SERVER['PATH_TRANSLATED'];
			$dir=preg_replace("/\/index.php/", "", $dir);
			$nome_real_file=$tipo_doc.$id.".".$ext;
			$dir.="/WCA/docs/$nome_real_file";
			if($ext!='eml'){
				
				header("Content-type:*");
				$nome_file=str_replace(";", "", $nome_file);
				header("Content-Disposition: attachment; filename=".$nome_file);
				readfile($dir);

			}
			else{
				$html_str=file_get_contents("docs/".$nome_real_file);


				$html_str=preg_replace("'^.*(<html.*>.*?</html>).*'si","\\1",$html_str);

				echo $html_str;
				die();
			}
			exit;
		}
		else {
			$html_str=file_get_contents("template.html");
			$body=$testo_config['Impossibile_scaricare_il_file'];
			$body="
<table border=0 cellpadding=0 cellspacing=0 width=100% align=center style=\"background-color:$bgcolor;\">
<tr bgcolor=white>
		<td align=center><a href='/'><img src=\"images/banner.jpg\" border=\"0\"></a></td>
				</tr><tr>
        <td valign=bottom><br>$Navigation_icon</td>
    </tr>
   </table> 
	<table border=0 id=t_1 cellpadding=0 cellspacing=2  width=95% align=center style=\"background-color:$bgcolor;\">
	<tr><td><fieldset><font size=5 color=red><b>$body</b></font></fieldset></td></tr></table>";
			$html_str=str_replace("<!--body-->", $body, $html_str);
			$html_str=str_replace("ajax_call('user_online', 'useronline=yes');setInterval('ajax_call(\'user_online\', \'useronline=yes\')', 28000);", "", $html_str);
			die($html_str);
		}
	}
	
	
	function download_all($queryResultSet,$folder){
		//Logger::send("download_all");
		global $in;
		global $conn;
		global $config_document;
		global $config_buttons;
		global $sid;
		$this->id_tipo_ref=$id_area;
		$this->tipo_doc='Doc_Area';
		$this->connection=$conn;
		ob_clean();
		system("mkdir -p faldoni/{$folder} > /dev/null",$retval);

		$dir="faldoni/".$folder;
		


		foreach($queryResultSet as $thread) {
			$nome_f="WCA/docs/Doc_Area".$thread[0]['ID_REF'].".".$thread[0]['EXT'];
			$nome_originale="faldoni/{$folder}/".$thread[0]['NOME_FILE'];
			$nome_originale=str_replace("'","",$nome_originale);
			$nome_originale=str_replace(" ","_",$nome_originale);
			$nome_originale=str_replace ("..", ".",$nome_originale);
			$nome_originale = strtolower ($nome_originale);

			// Match any character that is not in our whitelist
			preg_match_all ("/[^0-9^a-z^_^.\/]/", $nome_originale, $matches);

			// Loop through the matches with foreach
			foreach ($matches[0] as $value) {
				$nome_originale = str_replace($value, "", $nome_originale);
			}
			
			system("cp $nome_f $nome_originale > /dev/null",$retval);
			
			$files.="$nome_originale ";

		}
		
		
		$suffissi=explode("/",$folder);
		$suffisso=$suffissi[0];
		
		$nome_zip="faldoni/{$folder}/Faldone_$suffisso.zip";
		$nome_zip_nodir="Faldone_$suffisso.zip";
		
		
		$zip=system("zip -j $nome_zip faldoni/{$folder}/*",$retval);
		header("Content-type: application/zip");
		header("Content-Disposition: attachment; filename=$nome_zip_nodir");
		header("Content-Length: ".filesize($nome_zip));
		ob_clean();
		readfile($nome_zip);
		system("rm -fr faldoni/{$folder} > /dev/null",$retval);
		
		
		die();

	}
	


}

function txt() {
	//		var_dump(debug_backtrace());
	//		die("<h1>chiamo txt()</h1>");

}
function CMELInfoReplace($index,$infoArray){
	return $infoArray[$index];
}
?>
