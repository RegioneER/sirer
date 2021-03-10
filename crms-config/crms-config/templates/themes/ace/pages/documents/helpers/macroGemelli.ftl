<#macro select2singleCheck id name label selectedValues size=30 noLabel=true fieldDef=null>
    <#assign selectableValue="">
    <#list fieldDef.availableValuesMap?keys as prop>
        <#assign selectableValue=prop+"###"+fieldDef.availableValuesMap[prop]>
    </#list>
<@script>
    $('#${id}-select').change(function () {
        console.log($(this));
        if ($('#${id}-select')[0].checked) {
            $('#${id}').val("${selectableValue?html}");
        } else {
            $('#${id}').val("");
        }
    });

</@script>
<input type="hidden" id="${id}" name="${name}" value="${selectedValues}"/>
<input type="checkbox" id="${id}-select" <#if selectedValues!="">checked</#if>>
</#macro>


<#macro hiddenElementLink id name label searchScript searchValue selectedValues=[]  searchId="" selectedIds=[] aMap={} fieldDef=null editable=true>
    <#assign usedTokenInput=usedTokenInput+1/>
<#assign theme=true/>
<#assign single=true/>
<#assign autoCompleteField=""/>
	 	<@script>
	 		
 	$('.field-component').has('form').addClass('to-edit');
 	
 	var selected_id_${id}=null;
 	var selected_item_${id}=new Object();
 	var selected_${id}=false;
 	
 	
	<#list aMap?keys as prop>
	console.log('${prop}');
		<#if autoCompleteField="" && (prop?contains("Nome")  || prop?contains("nome"))>
			<#assign autoCompleteField=prop/>
			$('#${prop}').change(function(){if (!selected_${id}) {selected_id_${id}=null;selected_item_${id}=new Object();$('#${id}').val("");}check_${id}();});
			<#else>
			$('#${prop}').change(function(){check_${id}();});
		</#if>
		selected_item_${id}.${prop}=$('#${prop}').val();
	</#list>
	
	<#list selectedIds as sid>
		var selected_id_${id}=${sid};
	</#list>	
	
	function check_${id}(){
		console.log("Effettuo i controlli");
		if ($('#update_dictionary_${id}')){
			$('#update_dictionary_${id}').remove();			
		}
		if ($('#add_dictionary_${id}')){
			$('#add_dictionary_${id}').remove();
		}
		if (selected_id_${id}!=null && selected_id_${id}!=""){
		//Collegamento presente	
			console.log("Collegamento presente - "+selected_id_${id});
			var changed=false;
			<#list aMap?keys as prop>
				if ($('#${prop}').val()!=selected_item_${id}.${prop}) changed=true;
			</#list>
			if (changed) $('#informations-${autoCompleteField}').parent().append("<button class=\"btn btn-xs btn-warning\"  onClick='updateDictionary_${id}();' id='update_dictionary_${id}'><i class='icon-refresh'></i> Aggiorna il dizionario</button>");
		}else {
		//Collegamento non presente
			console.log("Collegamento non presente - "+selected_id_${id});
			$('#informations-${autoCompleteField}').parent().append("<button class=\"btn btn-xs btn-warning\" onClick='addDictionary_${id}();' id='add_dictionary_${id}'><i class='icon-plus'></i> Aggiungi al dizionario</button>");
			
		}
	}
	
	function addDictionary_${id}(){
		var typeId="${fieldDef.typefilters}";
		var formData=new FormData();
		formData.append('parentId', valueOfField('${fieldDef.addFilterFields}'));
		<#list aMap?keys as prop>
			formData.append("${aMap[prop]}", $('#${prop}').val()); 
		</#list>
		$.ajax({
                url: '${baseUrl}/app/rest/documents/save/'+typeId,
                type: 'POST',
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        $('#${id}').val(obj.ret);
                        selected_id_${id}=obj.ret;
                        <#list aMap?keys as prop>
						selected_item_${id}.${prop}=$('#${prop}').val();
						</#list>
						$('#add_dictionary_${id}').remove();
                    }else {
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
               });
	}
	
	function updateDictionary_${id}(){
		var formData=new FormData();
		<#list aMap?keys as prop>
			formData.append("${aMap[prop]}", $('#${prop}').val()); 
		</#list>
		$.ajax({
                url: '${baseUrl}/app/rest/documents/update/'+$('#${id}').val(),
                type: 'POST',
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        $('#${id}').val(obj.ret);
                        selected_id_${id}=obj.ret;
                        <#list aMap?keys as prop>
						selected_item_${id}.${prop}=$('#${prop}').val();
						</#list>
						$('#update_dictionary_${id}').remove();
						
                    }else {
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
               });
	}
	
	</@script>
    <input type="hidden" id="${id}" name="${name}" value="${selectedIds[0]!""}"/>
    <@script>

        	$( "#${autoCompleteField}" ).autocomplete({
			source: function( request, response ) {
				$.ajax({
					url: "${searchScript}?parent="+valueOfField('${fieldDef.addFilterFields}'),
					dataType: "json",
					data: {
					term: request.term
					},
					success: function( data ) {
					selected_${id}=false;
					console.log(data);
						response( $.map( data, function( item ) {
							return {
								label: item.title,
								id: item.id,
								<#list aMap?keys as prop>
								${prop}: item.metadata.${aMap[prop]}[0],
								</#list>
								value: item.title 
							}
						}));
						}
					});
					},
					minLength: 1,
					select: function( event, ui ) {
						selected_${id}=true;
						console.log(ui.item);	
						$('#${id}').val(ui.item.id);
						<#list aMap?keys as prop>
							$('#${prop}').val(ui.item.${prop});
						
						</#list>
						selected_id_${id}=ui.item.id;
						selected_item_${id}=ui.item;
					},
					open: function() {
					$( this ).removeClass( "ui-corner-all" ).addClass( "ui-corner-top" );
					},
					close: function() {
					$( this ).removeClass( "ui-corner-top" ).addClass( "ui-corner-all" );
				}
		});
        
            
  
    </@script>
</#macro>