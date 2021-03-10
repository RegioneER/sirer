<?php 

class NavBarItem{
	
	var $title;
	var $icon;
	var $links;
	var $badge;
	var $caret;
	var $href;
	var $addIconHtml;
	var $staticAddHtml;
	
	
	function __construct($title, $icon, $color="blue", $badge=null, $caret=false){
		$this->title=$title;
		$this->icon=$icon;
		$this->color=$color;
		if (isset($badge)) $this->badge=$badge;
		$this->caret=$caret;
		$this->href="#";
	}
	
	function addHref($href){
		$this->href=$href;
	}
	
	function addLink($link){
		$this->links[]=$link;
	}
	
	function addRawHtml($html){
		$this->links[]=$html;
	}
	
	
	
	function __toString(){
		$icon="icon-large fa fa-{$this->icon} {$this->icon}-fa";
		if (preg_match("!^el!",$this->icon)) $icon=$this->icon;
		
		if ($this->href=="#"){
			$aAdd="data-toggle=\"dropdown\" class=\"dropdown-toggle\"";
		}else $aAdd="" ;
		$ret="<li class=\"{$this->color}\">
							<a $aAdd href=\"{$this->href}\">
								<i class=\"{$icon}\">{$this->addIconHtml}</i>";
		if (count($this->links)>0){
			$this->caret=true;
		}
		if ($this->caret) $ret.="<span class=\"user-info hidden-sm hidden-xs\"> {$this->title}</span><i class=\"icon-caret-down\"></i>";
		else $ret.="<span class=\"hidden-sm hidden-xs\"> {$this->title}</span>";
		if (isset($this->badge)){
			$ret.="<span class=\"badge badge-success\">{$this->badge}</span>";
		}
		$ret.="</a>
				<ul class=\"user-menu pull-right dropdown-menu dropdown-yellow dropdown-caret dropdown-close\">
		";
		
		if (isset($this->badge)){
			$ret.="
					<li class=\"dropdown-header\">
						<i class=\"{$icon}-alt\"></i> {$this->badge} {$this->title}
					</li>";
		}
		if (isset($this->links) && count($this->links)>0){
			foreach ($this->links as $key=>$val){
				$ret.="<li>".$val."</li>";
			}
		}
		if (isset($this->staticAddHtml) && $this->staticAddHtml!=""){
			$ret.=$this->staticAddHtml;
		}
		/*
		$ret.="
				<li>
					<a href=\"#\">
						<div class=\"clearfix\"></div>
					</a>
				</li>";
				*/
		$ret.="
			</ul>
		</li>";
		
		return $ret;
		
	}
	
	
}


?>