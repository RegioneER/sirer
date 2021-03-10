<?php 

class SideBarItem{
	
	var $link;
	var $items;
	var $active;
	
	function __construct($link, $items=null, $active=false){
		$this->link=$link;
		if (isset($items)) $this->items=$items;
		$this->active=$active;
	}
	
	function addItem($item){
		$this->items[]=$item;
	}
	
	function isActive(){
		if ($this->active) return true;
		if (count($this->items)>0){
			$active=false;
			foreach($this->items as $k=>$v) if ($v->isActive()) $active=true;
			return $active;
		}else return $this->active;
	}
	
	
	function __toString(){
		$icon="fa fa-{$this->link->icon} {$this->link->icon}-fa";
		if (preg_match("!^el!",$this->link->icon)) $icon=$this->link->icon;
		$ret="";
		if (count($this->items)>0){
			if ($this->isActive()) $active="active open";
			else $active="";
			$ret.="<li class=\"{$active}\">
							<a href=\"#\" class=\"dropdown-toggle\">
								<i class=\"{$icon}\"></i>
								<span class=\"menu-text\"> {$this->link->label} </span>
								<b class=\"arrow fa fa-angle-down\"></b>
							</a>
					<ul class=\"submenu\">";	
			foreach ($this->items as $k=>$v){
				$ret.=$v;				
			}		
			$ret.="</ul></li>";
		}else{
		if ($this->isActive()) $active="active";
		else $active="";
			$ret.="
			<li class=\"{$active}\">
			<a href=\"{$this->link->link}\" {$this->link->target}>
								<i class=\"{$icon}\"></i>
								<span class=\"menu-text\"> {$this->link->label} </span>
							</a>
			</li>		
			";
		}
		return $ret;
	}
	

	
	
}

?>