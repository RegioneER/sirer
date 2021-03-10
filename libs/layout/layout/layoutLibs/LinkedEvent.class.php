<?php 


class LinkedEvent{

	var $event;
	var $time;
	var $link;
	var $icon;

	function __construct($event, $time=null, $link, $icon=null){
		if (isset($time)) $this->time=$time;
		$this->event=$event;
		if (isset($link)) $this->link=$link;
		else $this->link="#";
		if (isset($icon)) $this->icon=$icon;
	}

	function __toString(){
		if (isset($this->icon) && $this->icon!="") $icon="<i class=\"fa fa-{$this->icon}\"></i> ";
		else $icon="";
		$ret="
		<a href=\"{$this->link}\">{$icon}
										<span class=\"msg-body\">
											<span class=\"msg-title\">
												{$this->event}
											</span>";
		if (isset($this->time))$ret.="
											<br/><span class=\"msg-time\">
												<i class=\"fa fa-time\"></i>
												<span>{$this->time}</span>
											</span>
										</span>";
		$ret.="
									</a>";
		return $ret;
	}


}

?>