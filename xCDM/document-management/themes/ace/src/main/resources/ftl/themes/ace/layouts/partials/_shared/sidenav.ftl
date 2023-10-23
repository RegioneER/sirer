<a class="menu-toggler" id="menu-toggler" href="#"><span class="menu-text"></span></a>

<div class="sidebar sidebar-fixed sidebar-scroll" id="sidebar">
	<script type="text/javascript">
	try{ace.settings.check('sidebar' , 'fixed')}catch(e){}
	</script>
	
	<@includeLayout layout._sidenav.shortcuts />

	<ul class="nav nav-list">

		<#list layout.sidenav_navList as currItem >
			<#global item=currItem />
			<@includeLayout layout._sidenav.items />
		</#list>

	</ul><!--/.nav-list-->

	<div class="sidebar-collapse" id="sidebar-collapse">
		<i class="icon-double-angle-left" data-icon1="icon-double-angle-left" data-icon2="icon-double-angle-right"></i>
	</div>

	<script type="text/javascript">
	try{ace.settings.check('sidebar' , 'collapsed')}catch(e){}
	</script>
</div>
