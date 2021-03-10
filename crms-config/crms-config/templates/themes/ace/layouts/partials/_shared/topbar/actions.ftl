<#if getUserGroups(userDetails)!='REGIONE'><#--TOSCANA-188-->
<li style="background-color: #931410; !important">
	<a style="background-color: #931410; !important" data-toggle="dropdown" class="dropdown-toggle" href="#">
		<i class="icon-plus"></i>
		<span class="topbar-button-text hidden-900">Aggiungi</span>
		<i class="icon-caret-down"></i>
	</a>

	<ul class="pull-right dropdown-navbar dropdown-menu dropdown-caret dropdown-close">
		<li class="dropdown-header">
			Aggiungi
			<span class="help-button" data-rel="tooltip" data-trigger="hover" data-placement="left"  title="Menu degli oggetti registrabili nel servizio">?</span>
		</li>

		<#if getUserGroups(userDetails)=='DATAMANAGER'>
		<li>
			<a href="${baseUrl}/app/documents/addChild/3490624/1142" class="no-hover dark-blue" >
				<div class="clearfix">
					<span class="pull-left">
						<i class="no-hover icon-edit"></i> Promotore </span>
				</div>
			</a>
		</li>
		<li>
			<a href="${baseUrl}/app/documents/addChild/3490303/1066" class="no-hover dark-blue" >
				<div class="clearfix">
					<span class="pull-left">
						<i class="no-hover icon-edit"></i> CRO </span>
				</div>
			</a>
		</li>
		</#if>
		<#list layout._topbar_actions.list as action >
		<#if action.title!="type.reports" && action.title?trim!="Centri"  && action.title?trim!="Area Documentale">
		<li>
			<a href="${action.link}" class="no-hover dark-blue" >
				<div class="clearfix">
					<span class="pull-left">
						<i class="no-hover ${action.icon}"></i> ${action.title}</span>
					</div>
			</a>
		</li>
		</#if>
		
		<#if action.title=="Centri">
		<li>
			<a href="#" class="addCenter" class="no-hover dark-blue" >
				<div class="clearfix">
					<span class="pull-left">
						<i class="no-hover ${action.icon}"></i> ${action.title}</span>
					</div>
			</a>
		</li>
		</#if>
		
		</#list>
		<li>
			
		</li>
		
	</ul>
</li>
</#if>
<li style="background-color: #931410; !important">
	<a style="background-color: #931410; !important" href="${baseUrl}/app/documents/custom/search">
		<i class="icon-search"></i> 
		<span class="topbar-button-text hidden-900">Ricerca avanzata</span>
	</a>
</li>
<li style="background-color: #931410; !important">
    <a style="background-color: #931410; !important" href="${baseUrl}/app/documents/custom/help">
    <span class="help-button2">?</span>
    <span class="topbar-button-text hidden-900">Help</span>
    </a>
</li>
<style>
    .help-button2 {
    border: 2px solid #fff;
    border-radius: 100%;
    box-shadow: 0 1px 0 1px rgba(0, 0, 0, 0.2);
    color: #fff;
    cursor: default;
    display: inline-block;
    font-size: 12px;
    font-weight: bold;
    height: 20px;
    line-height: 17px;
    margin-left: 4px;
    padding: 0;
    text-align: center;
    width: 20px;
}
</style>
<script>
	$('#addCenter').click(function(){AddCenter();});
	/*
	$('#select_study').modal();
	*/
	function AddCenter(){
		$('#modalAddCenter').modal();
	    setTimeout("$('#select_study').select2(\"open\");",500); 
	}
    if($.isFunction('select2')){
    $('#select_study').select2({
			minimumInputLength: 1,
			maximumSelectionSize: 1,
            containerCssClass: 'select2-ace',
			allowClear: true,
			ajax: { 
                url: '${baseUrl}/app/rest/documents/advancedSearch/Studio',
					dataType: 'json',
					quietMillis: 1000,
					cache: true,
					data: function (term, page) {
								return {
									'IDstudio_CodiceProt_like': term
								};
							},
					results: function (data, page) { 
                    var length = data.length;
                    var results = new Array();
                    for (var i = 0; i < length; i++) {
                        results[i] = {id: data[i].id, text: data[i].titleString};
						}
						return {results: results, more: false};
					}
				}
	});
    }
	</script>