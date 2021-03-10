<@script>
 
	$('#elId').change(function(){
		$.getJSON( "${baseUrl}/app/rest/admin/type/get/"+$(this).val(), function( data ) {
			$('#startField').html("");
			$('#endField').html("");
			$('#endField').append("<option></option>");
			for (i=0;i<data.associatedTemplates.length;i++){
				for (f=0;f<data.associatedTemplates[i].metadataTemplate.fields.length;f++){
					if (data.associatedTemplates[i].metadataTemplate.fields[f].type=='DATE'){
						field=data.associatedTemplates[i].metadataTemplate.fields[f];
						$('#startField').append('<option value="'+field.id+'">'+field.extendedName+'</option>');			
						$('#endField').append('<option value="'+field.id+'">'+field.extendedName+'</option>');			
					}
				}
			}
		});	
	}); 

 
 function calendarPostPopulate(jsonRow){
    	console.log(jsonRow);
    	$.getJSON( "${baseUrl}/app/rest/admin/type/get/"+jsonRow.elementType.id, function( data ) {
    		$('#startField').html("");
			$('#endField').html("");
			$('#endField').append("<option></option>");
			for (i=0;i<data.associatedTemplates.length;i++){
				for (f=0;f<data.associatedTemplates[i].metadataTemplate.fields.length;f++){
					if (data.associatedTemplates[i].metadataTemplate.fields[f].type=='DATE'){
						field=data.associatedTemplates[i].metadataTemplate.fields[f];
						$('#startField').append('<option value="'+field.id+'">'+field.extendedName+'</option>');			
						$('#endField').append('<option value="'+field.id+'">'+field.extendedName+'</option>');			
					}
				}
			}
    		$('#elId').val(jsonRow.elementType.id);
    		if (jsonRow.endDateField) $('#endField').val(jsonRow.endDateField.id);
	    	$('#startField').val(jsonRow.startDateField.id);
	    	$('#backgroundColor').css("background-color", "#"+jsonRow.backgroundColor);
    	});
    	
    }


</@script>
<#assign calendarModal>
        <form id="calendar-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/calendar/save" enctype="multipart/form-data">
        <@hidden "id" "id" ""/>
        <div class="form-group">
        <@textbox "name" "name" "Nome" "" 40/>
        </div>
        <div class="form-group">
        <@textbox "titleRegex" "titleRegex" "Espressione titolo" "" 40/>
		</div>
        <div class="form-group">
        <@selectHash "elId" "elId" "Tipo di elemento"/>
        </div>
        <div class="form-group">
        <@selectHash "startField" "startField" "Data inizio"/>
        </div>
        <div class="form-group">
        <@selectHash "endField" "endField" "Data fine"/>
        </div>
        <div class="form-group">
        <@colorPicker "backgroundColor" "backgroundColor" "Colore" ""/>
        </div>
        <button class="round-button btn btn-sm btn-warning" type="button" id="calendar-form-submit">
        	<i class="fa fa-save"></i> Salva
        </button>
        </form>
</#assign>


<@modalbox "calendar-dialog" "Aggiungi/modifica calendario" calendarModal/>