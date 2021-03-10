<div class="breadcrumbs" id="breadcrumbs">
	<script type="text/javascript">
	try{ace.settings.check('breadcrumbs' , 'fixed')}catch(e){}
	</script>

	<ul class="breadcrumb">
		<li><i class="icon-home home-icon"></i> <a href="${baseUrl}/app/documents/">Home</a></li>
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
			<span id="no-search-result" class="label label-warning"></span>
			<span class="input-icon">
				<input type="text" placeholder="Search ..." class="nav-search-input typeahead" id="nav-search-input"/>
				<i id="search-icon" class="icon-search nav-search-icon"></i>
			</span>
		</form>
	</div><!--#nav-search-->

</div>
<#assign userSitesList=[] />
<#if userDetails.getSitesID()??>
<#assign userSitesList=userDetails.getSitesID() />
</#if>

<#assign userSitesCodesList=[] />
<#if userDetails.getSitesCodes()??>
<#assign userSitesCodesList=userDetails.getSitesCodes() />
</#if>

<@script>
var currentUserGroups="${getUserGroups(userDetails)}";
var flagPI = currentUserGroups.indexOf("PI");
var flagSP = currentUserGroups.indexOf("SP");
var flagDIR = currentUserGroups.indexOf("DIR");//STSANSVIL-712 DIR vede sempre e solo i suoi anche in BOX Studi in BD Regionale
var prependSite=''; //OK?!
var prependStudio='';
<#assign userCF = userDetails.username />
	<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
		<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
	</#if>
	if (flagPI>=0){
		prependSite='{"or":['+
		<#assign first=true/>
		<#list userSitesCodesList as site>
		'   {"match": {"metadata.IdCentro.values.PINomeCognome_CODESTRING": "${userCF}"}},'+
		'   {"match": {"createdBy": "${userDetails.username}"}},'+
		</#list>
		'  ]},';
	}
	else if (flagSP>=0){ //STSANSVIL-742
		prependSite='{"match": {"createdBy": "${userDetails.username}"}},';
	}
	else{
		<#if userSitesCodesList?? && userSitesCodesList?size gt 0>
			prependSite='{"or":['+
			<#assign first=true/>
			<#list userSitesCodesList as site>
			'   {"match": {"metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}<#if !site?is_last>,</#if>'+
			</#list>
			'  ]},';
		</#if>
	}
	if(flagSP>=0){
		prependStudio='{"match": {"createdBy": "${userDetails.username}"}},';
	}
	else{
		<#if userSitesCodesList?? && userSitesCodesList?size gt 0>
			prependStudio='{"or":['+
			<#assign first=true/>
			<#list userSitesCodesList as site>
				'   {"match": {"children.Centro.metadata.IdCentro.values.Struttura_CODESTRING": "${site}.0"}}<#if !site?is_last>,</#if>'+
			</#list>
			'  ]},';
		</#if>
	}
$('#nav-search-input').autocomplete({
		minLength: 2,
		response: function(event, ui) {
            console.log('callback response');
            if (ui.content.length === 0) {
            	$('#no-search-result').html('<i class="icon-warning-sign bigger-120"></i> Nessun risultato!');
               	$('#search-icon').removeClass('icon-spin');
				$('#search-icon').removeClass('icon-spinner');
				$('#search-icon').addClass('icon-search');
				$('#search-icon').addClass('nav-search-icon');
				setTimeout(function(){$("#no-search-result").empty();},2000);                
            } else {
                $("#no-search-result").empty();
            }
        },
		source: function(request,response){
			$('#search-icon').removeClass('icon-search');
			$('#search-icon').removeClass('nav-search-icon');
			$('#search-icon').addClass('icon-spin');
			$('#search-icon').addClass('icon-spinner');


			var filter=prependStudio;
			if(flagDIR>=0){
				var studiInsRegFilter='';
				studiInsRegFilter+='{"and" : [{"match_all":{}}]}'; //+'{"query": {"bool": {"must": [{ "wildcard": {"metadata.UniqueIdStudio.values.cto_NOTANALYZED": "'+userGroup+'"}}]}}}';
				if(filter!=""){
					filter+=',';
				}
				filter+=studiInsRegFilter;
			}
			else if(flagSP>=0){
				prependStudio=prependStudio.replace(",","");
				filter+=prependStudio;
			}
			if(filter!=""){//<< porta in -ctms
				filter+=',';
			}
			filter+='{"or":[';
			filter+='{"match":{"metadata.UniqueIdStudio.values.id_NOTANALYZED":"'+request.term+'"}}';
			filter+=',{"match":{"metadata.IDstudio.values.CodiceProt":"'+request.term+'"}}';
			filter+=',{"match":{"metadata.IDstudio.values.TitoloProt":"'+request.term+'"}}';
			filter+='  ]}';
                        filter=filter.replace("}{", "},{");
                        filter=filter.replace(",]", "]");
			filter=filter.replace(",,",",");
			$.ajax({
              url: "${baseUrl}/app/rest/elk/query/jqgrid/full/studio",
	          dataType: "json",
              type: "POST",
	          data: {
	            filter: filter
	          },
	          success: function( data ) {
	            response( data.root);
	          }
	        });
		}
	}).data( "ui-autocomplete" )._renderItem = function( ul, item ) {
			$('#search-icon').removeClass('icon-spin');
			$('#search-icon').removeClass('icon-spinner');
			$('#search-icon').addClass('icon-search');
			$('#search-icon').addClass('nav-search-icon');
			var label=item.title;
			if (item.type=='Centro') label=item.parents.Studio.title+"<br/>"+item.title;
			return $( "<p class='alert-success'>" ).append( "<a href=\"${baseUrl}/app/documents/detail/"+item.id+"\"> "+label+ "</a>" ).appendTo( ul );
		};



</@script>
