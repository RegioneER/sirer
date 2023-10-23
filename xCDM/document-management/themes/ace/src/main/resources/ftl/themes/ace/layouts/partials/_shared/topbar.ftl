<div class="navbar navbar-default navbar-fixed-top" id="navbar">
 <script type="text/javascript">
	try{ace.settings.check('navbar' , 'fixed')}catch(e){}
 </script>

  <div class="navbar-container" id="navbar-container">

	<div class="navbar-header pull-left">
	  <a href="#" class="navbar-brand">
	  	<i class="fa fa-sitemap green"></i><@msg "base.title"/>
	  </a><!-- /.brand -->
	</div><!-- /.navbar-header -->

	<div class="navbar-header pull-right" role="navigation">
	  <ul class="nav ace-nav">
	  		<@includeLayout layout._topbar.links />
	  		<@includeLayout layout._topbar.actions />
			<@includeLayout layout._topbar.notifications />
			<@includeLayout layout._topbar.messages />
			<@includeLayout layout._topbar.user_menu />
	  </ul><!-- /.ace-nav -->
	</div><!-- /.navbar-header -->

  </div><!-- /.container -->

</div>