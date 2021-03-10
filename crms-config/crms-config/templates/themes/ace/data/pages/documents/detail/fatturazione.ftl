<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dettaglio studio",
 	"description" : "Dettaglio studio" 
} />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<@script>
<#assign elementJson=model['element'].getElementCoreJsonToString(userDetails) /> <!--TOSCANA-177-->
var loadedElement=${elementJson};<!--TOSCANA-177-->
var sidebarDefault="${el.getParent().getId()}#Fatturazione-tab2";
//SIRER-67 INIZIO
$("#scheduling_ValoreAssoluto").val(0);
$("#scheduling_ValorePerc").val(0);

$("#startUp-head").hide();
$("#startUp-body").hide();
//SIRER-67 FINE
var oldExecuteConfirmTask=window.executeConfirmTask;
var oldExecuteFormTask=window.executeFormTask;
var stopSavig=false;
var executeConfirmTask= function(taskId){	
	stopSaving=false;
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
		
		if(!stopSaving){
			toggleLoadingScreen();
			formSubmitStd('scheduling');
			return oldExecuteConfirmTask(taskId);
		}	
	});
}

function executeFormTask(taskId){
	stopSaving=false;	
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
		
		if(!stopSaving){
			toggleLoadingScreen();
			formSubmitStd('scheduling');
			return oldExecuteFormTask(taskId);	
		}
	});
}


 	console.log("Sono qui: - ready");
 	
 	//alert('qui');
 	var i=0;
 	$('[data-replace=order]').each(function(){
 		i++;
 		$(this).html(i);
 	});
 	var prezzoBudget=$("#prezzoBudget").html();
	if(prezzoBudget) prezzoBudget=prezzoBudget.formatMoney();
	$("#prezzoBudget").html(prezzoBudget);
	
	var valoreAssoluto=$("#scheduling_ValoreAssoluto_value").html();
	if(valoreAssoluto) {valoreAssoluto=valoreAssoluto.formatMoney();}
	$("#scheduling_ValoreAssoluto_value").html(valoreAssoluto);

	$("td[id^='prezzoPrestazioni']").each(function(){
		var tdid=$(this).attr("id");
		var prezzoPrestazioni=$("#"+tdid).html();
		if(prezzoPrestazioni) {prezzoPrestazioni=prezzoPrestazioni.formatMoney();}
		$("#"+tdid).html(prezzoPrestazioni);
	});
	
	$("span[id^='importoTotale']").each(function(){
		var tdid=$(this).attr("id");
		var prezzoPrestazioni=$("#"+tdid).html();
		if(prezzoPrestazioni) {prezzoPrestazioni=prezzoPrestazioni.formatMoney();}
		$("#"+tdid).html(prezzoPrestazioni);
	});

	

 	/*
 	 *TOSCANA-88 vmazzeo 21.04.2017  eliminare dalla scheda l'obbligatorietà del dato sull'anticipo pazienti
 	*/
	$("#scheduling_ValoreAssoluto").blur(function(){
		if(this.value!=""){
			val1=parseFloat(this.value);
			if(val1>=0){
				val1=parseFloat(val1*100);
				val2=parseFloat('${el.getfieldData("InfoBudget","Prezzo")[0]!0}');
				val3=parseFloat(val1/val2).toFixed(2);
				if(!isNaN(val3)){
					$("#scheduling_ValorePerc").val(val3);
				}
			}
			else{
				alert('Attenzione! Inserire un valore reale maggiore o uguale a zero.');
				$("#scheduling_ValoreAssoluto").val(0);
			}
		}
		else{
			$("#scheduling_ValoreAssoluto").val(0);
		}
	});

 	$("#scheduling_ValorePerc").blur(function(){
		if(this.value!=""){
			val1=parseFloat(this.value);
			if(val1>=0){
				val2=parseFloat('${el.getfieldData("InfoBudget","Prezzo")[0]!0}');
				val3=parseFloat(val1*val2);
				val3=parseFloat(val3/100).toFixed(2);
				$("#scheduling_ValoreAssoluto").val(val3);
			}
			else{
				alert('Attenzione! Inserire un valore reale maggiore o uguale a zero.');
				$("#scheduling_ValorePerc").val(0);
			}
		}
		else{
			$("#scheduling_ValorePerc").val(0);
		}
	});
 	$( ".gruppo" ).autocomplete({ minLength: 0, source: autoCompleteSource });
 	
 	$( ".gruppo" ).click(function(){
       $( this ).autocomplete('search','');
   });
 	
 	$('#scheduling_ModalitaFatturazione-select').change(function(){gestModFatt();});
 	gestModFatt("${el.getfieldData("scheduling", "ModalitaFatturazione")[0]!""}");
 	
 	$('#scheduling_TipologiaCalcolo-select').change(function(){gestTipCalc();});
 	gestTipCalc("${el.getfieldData("scheduling", "TipologiaCalcolo")[0]!""}");
 	
 	$('#tabs').tabs();
 	
 	$('#tabs a[id^=tab]').on('click',function(){
   var hash=this.href;
   hash=hash.replace(/^[^#]*/,'');
   window.location.hash=hash;
  });		
 	
 	$("input[type=radio][checked]").each(function() {
	       var identificativo=this.name.split('DatiPrestazioniFatt_AccontoRataSaldo_')[1];
	       var valore='';
	       var valore=this.value;

	       if(valore==2 || valore==3){
	       	$(':checkbox[id=CheckRimborso_'+identificativo+']').attr('checked', false).attr('disabled', true);
	       }
	    });
 	
 	


Number.prototype.formatMoney = function(c, d, t, v){
	var n = this, 
    c = isNaN(c = Math.abs(c)) ? 2 : c, 
    d = d == undefined ? "," : d, 
    t = t == undefined ? "." : t, 
    v = v == undefined ? "&euro;" : v, 
    s = n < 0 ? "-" : "", 
    i = parseInt(n = Math.abs(+n || 0).toFixed(c)) + "", 
    j = (j = i.length) > 3 ? j % 3 : 0;
    //if(n==Math.floor(n))c=0;
   return s + (j ? i.substr(0, j) + t : "") + i.substr(j).replace(/(\d{3})(?=\d)/g, "$1" + t) + (c ? d + Math.abs(n - i).toFixed(c).slice(2) : "")+" "+v;
 };
 
 String.prototype.formatMoney = function(c, d, t, v){
	   var n = parseFloat(this);		
	   if(isNaN(n)) return this;
	   return n.formatMoney(c, d, t, v);
};

function SbiancaTP(){
	
	$(':checkbox[data-name=DatiTPFatt_CheckFatt]').each(function(){
		console.log('g');
		this.checked='';
		});
		$('#timepoint').hide();
	
	}

function gestModFatt(value){
console.log("Sono qui prima: - gestModFatt "+value);
	if (value==null) value=$('#scheduling_ModalitaFatturazione-select').val();
	console.log("Sono qui dopo: - gestModFatt "+value);
	$('#informations-scheduling_Periodicita').hide();
	$('#informations-scheduling_DataInizioFatt').hide();
	$('#informations-scheduling_TipologiaCalcolo').hide();
	$('#informations-scheduling_NumPaz').hide();
	$('#informations-scheduling_PercPaz').hide();
	$('#timepoint').hide();
	
	if (value.indexOf("1###")==0){
		$('#informations-scheduling_Periodicita').show();
		$('#informations-scheduling_DataInizioFatt').show();
		SbiancaTP();
	}
	if (value.indexOf("2###")==0){
		$('#informations-scheduling_TipologiaCalcolo').show();
		gestTipCalc();
	}
}

function gestTipCalc(value){
	console.log("Sono qui prima: - gestTipCalc "+value);
	if (value==null) value=$('#scheduling_TipologiaCalcolo-select').val();
	$('#informations-scheduling_NumPaz').hide();
	$('#informations-scheduling_PercPaz').hide();
	console.log("Sono qui dopo: - gestTipCalc "+value);
	
	if($('#scheduling_ModalitaFatturazione-select').val()){
		if (value.indexOf("4###")==0 && $('#scheduling_ModalitaFatturazione-select').val().split('###')[0]==2){$('#timepoint').show();}
		else {SbiancaTP();}
	
		if (value.indexOf("2###")==0 && $('#scheduling_ModalitaFatturazione-select').val().split('###')[0]==2){
			$('#informations-scheduling_NumPaz').hide();
			$('#informations-scheduling_PercPaz').show();}
		else {}
			
		if ((value.indexOf("1###")==0 || value.indexOf("3###")==0 || value.indexOf("4###")==0) && $('#scheduling_ModalitaFatturazione-select').val().split('###')[0]==2){
			$('#informations-scheduling_NumPaz').show();
			$('#informations-scheduling_PercPaz').hide();}
		else {}
	}
	$('span[id$=_value]:not(:empty)').parent().parent().show();
 	}

function update(id,metadata){
		return $.ajax({
  	method : 'POST',
  	async : false,
  	url : '../../rest/documents/update/' + id,
  	data : metadata
 		});
	}

function saveAll(){
		stopSaving=false;
		$('[name^=DatiPrestazioniFatt_AccontoRataSaldo_]').each(function(){
			var identificativo=this.name.split('DatiPrestazioniFatt_AccontoRataSaldo_')[1];
			var name=this.name;
			if($('[name='+name+']:checked').size()==0){
				stopSaving=true;
				bootbox.alert('Attenzione selezionare la tipologia di rata per le prestazioni/servizi ulteriori');
				return false;
			}
		});
		if(stopSaving){
			return false;
		}
		$('.gruppo').each(function(){
				var metadata={};
				metadata[this.name]='';
				var identificativo=this.id.split('gruppo_')[1];

				metadata[this.name]=this.value;

				console.log(this.name);
				console.log(identificativo);
				console.log(this.value);
				
				update(identificativo, metadata);
			});
		
		$(':checkbox[data-name=DatiTPFatt_CheckFatt]').each(function(){
				var metadata={};
				var name=$(this).data("name");
				metadata[name]='';
				
				if ($('#scheduling_TipologiaCalcolo-select').val()!==undefined && $('#scheduling_TipologiaCalcolo-select').val().split('###')[0]==4 && $('#scheduling_ModalitaFatturazione-select').val().split('###')[0]==2){
				metadata[name]=this.checked ? 1 : '';
				}
				console.log('DatiTPFatt_CheckFatt');
				update(this.id, metadata);
			});
			
		$(':checkbox[name=DatiPrestazioniFatt_Rimborso]').each(function(){
				var metadata={};
				metadata[this.name]='';
				
				metadata[this.name]=this.checked ? 1 : '';
				
				var identificativo=this.id.split('CheckRimborso_')[1];
				
				console.log('DatiPrestazioniFatt_Rimborso');
				update(identificativo, metadata);
			});
		
		$(':radio:checked').not("[name=scheduling_StartUpRimborsabile]").each(function(){
			
			var metadata={};
			var valore=$("input[name='"+this.name+"']:checked").val();
			
			metadata[this.name]='';
			//console.log($("input[name='"+this.name+"']:checked").val());
			//console.log(this.name.split('DatiPrestazioniFatt_AccontoRataSaldo_')[1]);
			
			var identificativo=this.name.split('DatiPrestazioniFatt_AccontoRataSaldo_')[1];
			
			if(!valore){valore='';}
			metadata[this.name]=valore;
			
			console.log('radio');
			update(identificativo, metadata);
			
			});
		
	}

function autoCompleteSource(request, response){
	
		var data=[];
		var duplicated={};
		
		$('.gruppo').each(function(){
			
			var value=$(this).val();
			if(value.match('.*'+request.term+'.*') && value!='' && !duplicated[value]) {
				
				duplicated[value]=true;
				
				data[data.length]=value;
			}
			
			});
			
	response(data);
	
	}
	$('#tabs-0 .col-sm-9').removeClass('col-sm-9');
	
</@script>