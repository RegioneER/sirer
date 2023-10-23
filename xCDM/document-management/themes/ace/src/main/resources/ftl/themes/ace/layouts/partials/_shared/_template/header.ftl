<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<title>${page.title!} - ${site.title!}</title>
	<meta name="description" content="${page.description!}" />

	<meta name="viewport" content="width=device-width, initial-scale=1.0" />

	<!-- basic styles -->
	<link href="${path.assets}/css/bootstrap.min.css" rel="stylesheet" />
	<link rel="stylesheet" href="${path.assets}/css/font-awesome.min.css" />

    <link rel="stylesheet" href="${path.assets}/css/font-awesome-4.6.2.min.css" />

	<!--[if IE 7]>
	  <link rel="stylesheet" href="${path.assets}/css/font-awesome-ie7.min.css" />
	<![endif]-->



	<!-- page specific plugin styles -->
	<#list page.styles as style>
	<#if css_map[style]?? >
	<link rel="stylesheet" href="${path.assets}/css/${css_map[style]}" />
	<#elseif css_custom_map[style]??>
		<#list css_custom_map[style] as subCss>
		<link rel="stylesheet" href="${path.custom.assets}/css/${subCss}" />
		</#list>
	<#else>
	<link rel="stylesheet" href="${path.custom.assets}/css/${style}" />
	</#if>
	</#list>

	<!-- fonts -->
	<@includeLayout layout._template.fonts />
	<!-- ace styles -->
	<link rel="stylesheet" href="${path.assets}/css/ace.min.css" />
	<link rel="stylesheet" href="${path.assets}/css/ace-rtl.min.css" />
	<link rel="stylesheet" href="${path.assets}/css/ace-skins.min.css" />
	<!--[if lte IE 8]>
	  <link rel="stylesheet" href="${path.assets}/css/ace-ie.min.css" />
	<![endif]-->
	<link rel="stylesheet" href="${path.custom.assets}/css/${page.layout}.css" />

	<!-- inline styles related to this page -->
	<#if page.inline_styles?? >
	<style>
		<#list page.inline_styles as inline_style >
		${inline_style}
		</#list>
	</style>
	</#if>


    <!-- basic scripts -->
<@includeLayout layout._template.jquery />
    <script src="${path.assets}/js/bootstrap.min.js"></script>
    <script src="${path.assets}/js/typeahead-bs2.min.js"></script>
    <script src="${path.assets}/js/bootbox.min.js"></script>
	<!-- ace settings handler -->
	<script src="${path.assets}/js/ace-extra.min.js"></script>


	<!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->
	<!--[if lt IE 9]>
	<script src="${path.assets}/js/html5shiv.js"></script>
	<script src="${path.assets}/js/respond.min.js"></script>
	<![endif]-->

</head>
<#assign userSitesList=[] />
<#if userDetails.getSitesID()??>
	<#assign userSitesList=userDetails.getSitesID() />
</#if>

<#assign userSitesCodesList=[] />
<#if userDetails.getSitesCodes()??>
    <#assign userSitesCodesList=userDetails.getSitesCodes() />
</#if>
<#assign userUOCodesList=[] />
<#if userDetails.getUoCodes()??>
	<#assign userUOCodesList=userDetails.getUoCodes() />
</#if>

<@script>
	var emendamentoId = ${userDetails.getEmeSessionId()!0};
</@script>