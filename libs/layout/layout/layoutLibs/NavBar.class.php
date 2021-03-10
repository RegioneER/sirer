<?php 

class NavBar{
	
	var $title;
	var $items;
	var $logo;
	var $isImage;
	
	
	function __construct($title,$imagePath=null, $isImage=false){
		$this->title=$title;	
		if (isset($imagePath)) $this->logo=$imagePath;
		$this->isImage=$isImage;
	}
	
	function addItem($item){
		$this->items[]=$item;
	}
	
	function __toString(){
		$ret="<div class=\"navbar-container\" id=\"navbar-container\">";
		if ($this->isImage) {
			$ret.="
			<img src=\"{$this->logo}\" style=\"max-height:45px;height:45px;float:left\">";
				
		}
		$ret.="
				<div class=\"navbar-header pull-left\">
					<a href=\"#\" class=\"navbar-brand\">
						<small>";
		if (!$this->isImage){
		$ret.="
				<i class=\"fa fa-{$this->logo}\"></i>";
		}
		
		$ret.="
							{$this->title}
						</small>
					</a>
				</div>";
		if (isset($this->items) && count($this->items)>0){	
			$ret.="<div class=\"navbar-header pull-right\" role=\"navigation\">
					<ul class=\"nav ace-nav\">";
			foreach ($this->items as $key=>$val){
				$ret.=$val;
			}
			$ret.="</ul></div>";
		}
		$ret.="
				</div>";
		return $ret;
	}
	
	
	
}


?>