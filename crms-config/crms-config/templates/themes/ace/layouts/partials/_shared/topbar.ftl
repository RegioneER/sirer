<div class="navbar navbar-default" id="navbar">

 <script type="text/javascript">
	try{ace.settings.check('navbar' , 'fixed')}catch(e){}
 </script>

  <div class="navbar-container" id="navbar-container">

	<div class="navbar-header pull-left">
	<img src="/logo_rer.png" class="pull-left" style="max-height:45px;float:left"/>
		<span class="pull-right hidden-900" style="	color: white; font-size: 20px; font-family: 'logo'; padding-top: 8px; padding-left: 10px;">
			SIRER
		</span>
	</div>
	<div class="navbar-header pull-right" role="navigation">
	  <ul class="nav ace-nav">
	  		<@includeLayout layout._topbar.links />
	  		<@includeLayout layout._topbar.actions />
			<#--@includeLayout layout._topbar.tasks /-->
			<@includeLayout layout._topbar.notifications />
			<@includeLayout layout._topbar.messages />
			<@includeLayout layout._topbar.user_menu />
			<li>
			<img src="/cineca-trasp.png" class="pull-left" style="max-height:45px;padding-left: 2px;"/>
			</li>
	  </ul><!-- /.ace-nav -->
	  
	</div><!-- /.navbar-header -->
  </div><!-- /.container -->

</div>
