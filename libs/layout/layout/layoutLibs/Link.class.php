<?php 

class Link{

	var $label;
	var $icon;
	var $link;
	var $color;
	var $target;
    var $onclick;
	function __construct($label, $icon, $link=null, $color=false, $target=null, $onclick=false){
		$this->icon=$icon;
		$this->label=$label;
		if (isset($link)){
			 $this->link=$link;
		}
		else{
			 $this->link="#";
		}
		if (isset($target)){
			$this->target="target=\"".$target."\"";
		}
		else{
			$this->target="";
		}
		$this->color = $color;
        if ($onclick){
            $this->onclick="onclick=\"".$onclick."\"";
        }
        else{
            $this->onclick="";
        }
	}
	
	function __toString(){
		$icon="fa fa-{$this->icon} {$this->icon}-fa";
		if (preg_match("!^el!",$this->icon)) $icon=$this->icon;

        $ret="
		<a href=\"{$this->link}\" alt=\"{$this->label}\" {$this->target} ".($this->color?'style="color: '.$this->color.'"':'')." ".$this->onclick." >
		<div class=\"clearfix\">
		<i class=\"{$icon}\"></i> {$this->label}
		</div>
		</a>";
		return $ret;
	}
	
	
}

?>