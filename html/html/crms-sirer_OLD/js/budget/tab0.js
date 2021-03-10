function creaGruppo(){
	bootbox.prompt("Inserire il nome del gruppo da creare", function(result){ 
	  if (result!=''){
	    $.post( "/dizionari/gruppiPrestazioni.php", {"CREA":true, "ID_BUDGET": elementId, "NOME": result}, function( data ) {
	      if (data.status=="OK"){
	        addGruppo(data.detail);
	      } else {
	    	  bootbox.hideAll();
	    	  bootbox.alert(data.message);
	      }
	    });
	  }
	});
}


function deletePrestazione(nomeGruppo, id_budget, id_prestazione){
	bootbox.dialog({
		message: "eliminazione in corso...",
		closeButton: false
	});
	$.post( "/dizionari/gruppiPrestazioni.php", {"DEL_PRESTAZIONE":true, "ID_BUDGET": id_budget, "GRUPPO": nomeGruppo, "ID_PRESTAZIONE": id_prestazione}, function( data ) {
		bootbox.hideAll();
  	  	if (data.status=="OK"){
	    	addGruppo(data.detail);
	    } else {
	    	bootbox.alert(data.message);
	    }
	 });
}

function applyGroup(nomeGruppo){
	$.get( "/dizionari/gruppiPrestazioni.php", {"GET_GRUPPO":nomeGruppo, "ID_BUDGET": elementId}, function( data ) {
	    if (data.status=="OK"){
	    	var prestazioniGruppo=data.detail.prestazioni;
	    	
		}
	});
}

function addGruppo(groupData){
	$('#gruppiPrestazioni ul [data-nome="'+groupData.nome+'"]').remove();
	var gruppo=$('<li>');
	gruppo.attr('data-nome', groupData.nome);
	gruppo.append(groupData.nome);
	gruppo.append("&nbsp;");
	gruppo.append('<i class="fa fa-trash red" data-nome="'+groupData.nome+'"></i>&nbsp;');
	gruppo.append('<i class="fa fa-eye-slash red" data-nome="'+groupData.nome+'"></i>&nbsp;');
	gruppo.append('<i class="fa fa-eye green" style="display:none" data-nome="'+groupData.nome+'"></i>&nbsp;');
	var applicaButton=$('<button>');
	applicaButton.addClass("btn btn-info btn-xs applicagruppo");
	applicaButton.attr('data-nome', groupData.nome);
	applicaButton.html("applica alla flowchart");
	gruppo.append(applicaButton);
	applicaButton.click(function(){
		var nomeGruppo=$(this).attr('data-nome');
		applyGroup(nomeGruppo);
	});
	gruppoContent=$('<ul>');
	
	if (groupData.prestazioni){
		for (var i=0;i<groupData.prestazioni.length;i++){
			var prestDelete=$('<a>');
			prestDelete.attr('data-gruppo-nome', groupData.nome);
			prestDelete.attr('data-element-id', elementId);
			prestDelete.attr('data-prestazione-id', groupData.prestazioni[i]['id']);
			prestDelete.attr('href','#');
			prestDelete.html("<i class='fa fa-trash'></i>&nbsp;</a>");
			var prestLi=$('<li>');
			prestLi.append(groupData.prestazioni[i]['label']);
			prestLi.append("&nbsp;");
			prestDelete.click(function(){
				deletePrestazione($(this).attr('data-gruppo-nome'), $(this).attr('data-element-id'), $(this).attr('data-prestazione-id'));
				return false;
			});
			prestLi.append(prestDelete);
			
			gruppoContent.append(prestLi);
			gruppo.append(gruppoContent);
		}
	}
	
	var addPrest=$('<a>');
	addPrest.attr('data-gruppo-nome', groupData.nome);
	addPrest.attr('data-element-id', elementId);
	addPrest.attr('href','#');
	addPrest.html("<i class='fa fa-plus'></i> aggiungi prestazione</a>");
	var addPrestLi=$('<li>');
	addPrestLi.append(addPrest);
	addPrest.click(function(){
		showSfogliaPrestazioni($(this).attr('data-gruppo-nome'), $(this).attr('data-element-id'));
		return false;
	});
	gruppoContent.append(addPrestLi);
	gruppo.append(gruppoContent);
	$('#gruppiPrestazioni ul#prestazioniList').append(gruppo);
	$('.fa-eye-slash[data-nome]').unbind('click');
	$('.fa-eye-slash[data-nome]').click(function(){
	  var nomeGruppo=$(this).attr('data-nome');
	  $('#prestazioniList > li[data-nome="'+nomeGruppo+'"] > ul').hide();
	  $('.fa-eye[data-nome="'+nomeGruppo+'"]').show();
	  $('.fa-eye-slash[data-nome="'+nomeGruppo+'"]').hide();
	});

	$('.fa-eye[data-nome]').unbind('click');
	$('.fa-eye[data-nome]').click(function(){
	  var nomeGruppo=$(this).attr('data-nome');
	  $('#prestazioniList > li[data-nome="'+nomeGruppo+'"] > ul').show();
	  $('.fa-eye[data-nome="'+nomeGruppo+'"]').hide();
	  $('.fa-eye-slash[data-nome="'+nomeGruppo+'"]').show();
	});
	
	
	$('.fa-trash[data-nome]').unbind('click');
	$('.fa-trash[data-nome]').click(function(){
	  var nomeGruppo=$(this).attr('data-nome');
	  console.log('da definire de-associazione grupo');
	});
	bootbox.hideAll();
}

function loadGruppi(){
	$.getJSON("/dizionari/gruppiPrestazioni.php?GET_GRUPPI=true&ID_BUDGET="+elementId, function(data){
		if (data.status=='OK'){
			if (budgetStatus!='open' && (!data.results || data.results.length==0)){
				$('#gruppiPrestazioni').html("<div class='alert alert-info'>Non sono presenti gruppi di prestazioni associati al budget</div>");
			}
			for(var gruppoIdx in data.results) {
				addGruppo(data.results[gruppoIdx]);
			}
		}
	});
}

function showSfogliaGruppi(){
    bootbox.dialog({
        title: 'Seleziona il gruppo da aggiungere',
        message: '<p class="cercaPrestazioniDialog"><label for="sfoglia_gruppi">Gruppo:</label><input type="text" name="sfoglia_gruppi" id="sfoglia_gruppi" value="" class="text ui-widget-content ui-corner-all" /></p>'
    }).on("shown.bs.modal", function(e) {
    	 var $that1=$( ".bootbox-body .cercaPrestazioniDialog #sfoglia_gruppi" );
    	 $( ".bootbox-body .cercaPrestazioniDialog #sfoglia_gruppi" ).autocomplete({
    	        minLength: 2,
    	        select: function( event, ui ) {
    	            $.get( "/dizionari/gruppiPrestazioni.php", {"GET_GRUPPO":ui.item.label, "ID_BUDGET": elementId}, function( data ) {
    	      	      if (data.status=="OK"){
    	      	        addGruppo(data.detail);
    	      	      }
    	      	    });
    	            
    				var request={prestazione:$( "#sfoglia_prestazioni" ).val(),term:''};
    	        },
    	        source:function( request, response ) {
    	            $that1.next('i.icon-spinner').remove();
    	            $that1.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
    	            var term = request.term;
    	            if ( term in cache ) {
    	                response( cache[ term ] );
    	                return;
    	            }
    	            $.getJSON( "/dizionari/gruppiPrestazioni.php", request, function( data, status, xhr ) {
    	                cache[ term ] = data;
    	                response( data );
    	                $that1.next('i.icon-spinner').remove();
    	            });
    	        }
    	    });
    	 $( ".bootbox-body .cercaPrestazioniDialog #sfoglia_gruppi" ).focus();
    });
       
}



function showSfogliaPrestazioni(gruppoNome, elementId){
    bootbox.dialog({
        title: 'Seleziona la prestazione da aggiungere',
        message: '<p class="cercaPrestazioniDialog"><label for="sfoglia_prestazioni">Prestazione:</label><input type="text" name="sfoglia_prestazioni" id="sfoglia_prestazioni" value="" class="text ui-widget-content ui-corner-all" /></p>'
    }).on("shown.bs.modal", function(e) {
    	 var $that1=$( ".bootbox-body .cercaPrestazioniDialog #sfoglia_prestazioni" );
    	 $( ".bootbox-body .cercaPrestazioniDialog #sfoglia_prestazioni" ).autocomplete({
    	        minLength: 2,
    	        select: function( event, ui ) {
    	            $.post( "/dizionari/gruppiPrestazioni.php", {"ADD_PRESTAZIONE":true, "ID_BUDGET": elementId, "GRUPPO": gruppoNome, "ID_PRESTAZIONE": ui.item.id}, function( data ) {
    	      	      if (data.status=="OK"){
    	      	        addGruppo(data.detail);
    	      	      }
    	      	    });
    	            
    				var request={prestazione:$( "#sfoglia_prestazioni" ).val(),term:''};
    	        },
    	        source:function( request, response ) {
    	            $that1.next('i.icon-spinner').remove();
    	            $that1.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
    	            var term = request.term;
    	            if ( term in cache ) {
    	                response( cache[ term ] );
    	                return;
    	            }
    	            $.getJSON( "/dizionari/prestazioni_nom.php", request, function( data, status, xhr ) {
    	                cache[ term ] = data;
    	                response( data );
    	                $that1.next('i.icon-spinner').remove();
    	            });
    	        }
    	    });
    	 $( ".bootbox-body .cercaPrestazioniDialog #sfoglia_prestazioni" ).focus();
    });
       
}
    

function applyGroup(nomeGruppo){
	bootbox.dialog({
        message: 'Aggiunta gruppo alla flowchart in corso...',
        closeButton: false
    });
	$.get( "/dizionari/gruppiPrestazioni.php", {"GET_GRUPPO":nomeGruppo, "ID_BUDGET": elementId}, function( data ) {
	    if (data.status=="OK"){
	    	var prestazioniGruppo=data.detail.prestazioni;
	    	for (var idx2=0;idx2<prestazioniGruppo.length;idx2++){
          prestazioniGruppo[idx2]['presente']=false;
        }
        for (var idx=0;idx<prestazioni.length;idx++){
          var prestazionePresente=prestazioni[idx];
          if (prestazionePresente.metadata && prestazionePresente.metadata['Prestazioni_Dizionario'] && prestazionePresente.metadata['Prestazioni_Dizionario'][0]!='att_pi'){
            for (var idx2=0;idx2<prestazioniGruppo.length;idx2++){
              
              if (prestazioniGruppo[idx2].id+"###"+prestazioniGruppo[idx2].label==prestazionePresente.metadata['Prestazioni_nomenclatore'][0]){
                  if (prestazionePresente.metadata['Prestazioni_Dizionario'][0]!='GRUPPO-'+nomeGruppo){
                    assocExisting(prestazionePresente.id, nomeGruppo); 
                    prestazioniGruppo[idx2]['presente']=true;
                  }else {
                    prestazioniGruppo[idx2]['presente']=true;
                  }
              }
            }
          }
        }
        for (var idx2=0;idx2<prestazioniGruppo.length;idx2++){
          if (!prestazioniGruppo[idx2]['presente']){
            addPrestazioneFromGroup(prestazioniGruppo[idx2], nomeGruppo);
          }          
        }
		}
	});
}

var ajaxCall=0;

function updateCallBack(){
  if (ajaxCall==0){
    loadFlow();
  }
}

function assocExisting(prestId, nomeGruppo){
  var url=baseUrl+"/app/rest/documents/updateField/"+prestId;
  var postBody={};
  postBody.name='Prestazioni_Dizionario';
  postBody.value="GRUPPO-"+nomeGruppo;
  ajaxCall++;
  $.post(url, postBody, function(data){
    ajaxCall--;
    updateCallBack();
  });
}


function addPrestazioneFromGroup(prestazione, nomeGruppo){
  var url=baseUrl+"/app/rest/documents/save/Prestazione";
  var postBody={};
  postBody['Prestazioni_Dizionario']="GRUPPO-"+nomeGruppo;
  postBody['Prestazioni_prestazione']=prestazione.label;
  postBody['Prestazioni_nomenclatore']=prestazione.id+"###"+prestazione.label;
  postBody['Tariffario_Solvente']=prestazione.solventi;
  postBody['Tariffario_SSN']=prestazione.ssn;
  postBody['parentId']=folderPrestazioniId;
  postBody['Prestazioni_row']=1;
  ajaxCall++;
  $.post(url, postBody, function(data){
    ajaxCall--;
    updateCallBack();
  });
}




