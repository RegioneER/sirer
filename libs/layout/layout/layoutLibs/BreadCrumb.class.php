<?php 

class BreadCrumb{
	
	var $paths;
	
	function __construct($paths){
		$this->paths=$paths;
		
	}
	
	function __toString(){
		$ret="
				<ul class=\"breadcrumb\">
				";
		$i=0;
		foreach ($this->paths as $key=>$val){			
			$i++;
			$icon="fa fa-{$val[0]} {$val[0]}-fa";
			if (preg_match("!^el!",$val[0])) $icon=$val[0];
			if ($i<count($this->paths)){
			$ret.="			
				<li>
								<i class=\"$icon\"></i>
								<a href=\"{$val[2]}\">{$val[1]}</a>
							</li>";
			}else {
				$icon="fa fa-{$this->paths[count($this->paths)-1][0]}";
				if (preg_match("!^el!",$this->paths[count($this->paths)-1][0])) $icon=$this->paths[count($this->paths)-1][0];
				$ret.="
				<li class=\"active\"><i class=\"$icon\"></i> {$this->paths[count($this->paths)-1][1]}</li>
				";
			}
		}
		$ret.="		</ul>
						";
		return $ret;
	}
	
}

?>