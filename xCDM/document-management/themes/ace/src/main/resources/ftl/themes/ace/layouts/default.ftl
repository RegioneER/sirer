<!DOCTYPE html>
<html lang="it-IT">
	<@includeLayout layout._template.header />
<style>

.metadata-template-block{

}


.labelEditSpan{
    border: 1px solid #ccc;
    border-radius: 5px;
    color: #222;
    display: none;
    font-size: 14px;
    padding: 2px;
    position: absolute;
}

.label-anchor{
    vertical-align: super;
    font-size:10px;
}

span a.pen-selected{
    vertical-align: super;
    font-size:3px;
}

</style>
	<body>
		
		<@includeLayout layout.topbar />
		
		<div class="main-container" id="main-container">
		 <script type="text/javascript">
		 try{ace.settings.check('main-container' , 'fixed')}catch(e){}
		 </script>
		 <div class="main-container-inner">

		 <@includeLayout layout.sidenav />

			<div class="main-content">
				<div class="main-content-inner">
					<@includeLayout layout.breadcrumbs />

					<div class="page-content">
						<#if page.no_header!false ><!--if no such thing as "no-header", then print header-->
						<div class="page-header">
							<h1>${page.title!} <#list page.description as description ><small><i class="icon-double-angle-right"></i> ${page.description}</small></#list></h1>
						</div><!--/.page-header-->
						</#if>
	
						<div class="row">
						 <div class="col-xs-12">
	<!-- PAGE CONTENT BEGINS -->
	
	<@includeLayout page.content  />
	
	<!-- PAGE CONTENT ENDS -->
						 </div><!--/.col-->
						</div><!--/.row-->
	
					</div><!--/.page-content-->
				</div><!--/.main-content-inner-->

			</div><!--/.main-content -->

			<@includeLayout layout.settings />
			
		 </div><!--/.main-container-inner-->

		 <a href="#" id="btn-scroll-up" class="btn-scroll-up btn btn-sm btn-inverse">
			<i class="icon-double-angle-up icon-only bigger-110"></i>
		 </a>
		</div><!--/.main-container-->

		<@includeLayout layout._template.footer />

		<div align="center"  style="position:absolute ; bottom:10px;width:100%">
			<hr>
			<img src="${baseUrl}/int/images/logo_cineca.jpg" style="width: 50px; height: 54px;">
			
		</div>
		<div class="clearfix" style="height:80px;"></div>
	</body>
</html>