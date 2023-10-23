<div class="breadcrumbs breadcrumbs-fixed" id="breadcrumbs">
	<script type="text/javascript">
	try{ace.settings.check('breadcrumbs' , 'fixed')}catch(e){}
	</script>

	<ul class="breadcrumb">
		<li><i class="icon-home home-icon"></i> <a href="${baseUrl}/app/documents/"><@msg "system.home"/></a></li>
		<#list breadcrumbs.links as link >
		<#if link.link??>
		<li><a href="${link.link}">${link.title}</a></li>
		<#else>
			<li class="active">${link.title}</li>
		</#if>
		</#list>
		<#if breadcrumbs.title!="" ><li class="active">${breadcrumbs.title}</li></#if>
	</ul><!--.breadcrumb-->

	<div class="nav-search" id="nav-search">
		<form class="form-search">
			<span class="input-icon">
				<input type="text" placeholder="Search ..." class="nav-search-input" id="nav-search-input"/>
				<i id="search-icon" class="icon-search nav-search-icon"></i>
			</span>
		</form>
	</div><!--#nav-search-->

</div>
<@script>
$('#nav-search-input').autocomplete({
		minLength: 2,
		source: function(request,response){
			$('#search-icon').removeClass('icon-search');
			$('#search-icon').removeClass('nav-search-icon');
			$('#search-icon').addClass('icon-spin');
			$('#search-icon').addClass('icon-spinner');
			 $.getJSON("${baseUrl}/app/rest/documents/fullSearch", { pattern: request.term }, response);
		}
	}).data( "ui-autocomplete" )._renderItem = function( ul, item ) {
			$('#search-icon').removeClass('icon-spin');
			$('#search-icon').removeClass('icon-spinner');
			$('#search-icon').addClass('icon-search');
			$('#search-icon').addClass('nav-search-icon');
			return $( "<p class='alert-success'>" ).append( "<a href=\"${baseUrl}/app/documents/detail/"+item.id+"\"> " + item.titleString+ "</a>" ).appendTo( ul );
		};



</@script>