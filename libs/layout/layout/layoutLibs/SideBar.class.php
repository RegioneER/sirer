<?php 

class SideBar{
	
	var $items;
	
	function __construct($items=null){		
		if(isset($items)) $this->items=$items;	
	}
	
	function addItem($item){
		$this->items[]=$item;
	}
	
	function __toString(){
		$ret="";
		
		if (count($this->items)>0){
			$ret="<div class=\"sidebar\" id=\"sidebar\">
			<script type=\"text/javascript\">
try{ace.settings.check('sidebar' , 'fixed')}catch(e){}
</script>
			";
			$ret.="<ul class=\"nav nav-list\">";
			foreach ($this->items as $key=>$val){
				$ret.=$val;
			}
			
			$ret.="</ul>";
			$ret.="	<div class=\"sidebar-collapse\" id=\"sidebar-collapse\">
					<i class=\"icon-double-angle-left\" data-icon2=\"icon-double-angle-right\" data-icon1=\"icon-double-angle-left\"></i>
							</div>
				    <script type=\"text/javascript\">
                        try{ace.settings.check('sidebar' , 'collapsed')}catch(e){}
                    </script>
							</div>
			";
		}
		return $ret;
	}
	
}

?>