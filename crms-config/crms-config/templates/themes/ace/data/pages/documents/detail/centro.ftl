<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/form.css","jqgrid"],
	"scripts" : ["xCDM-modal","jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","token-input","jqgrid","pages/home.js"],
	"inline_scripts":[],
	"title" : "Dettaglio centro",
 	"description" : "Dettaglio centro" 
} />
<#assign elStudio=el.getParent() />

<#assign profit=elStudio.getFieldDataCode("datiStudio","Profit")/>
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />

<@script>
loadedJSON=${loadedJson};
function executeFormTask(taskId,domElement){

            var task;
            if(gtasks[taskId]){
                task=gtasks[taskId];
            }else{
                task=gtasksById[taskId];
            }
            $.ajax({
                    dataType: "json",
                    url: "${baseUrl}/process-engine/runtime/tasks/"+taskId+"/variables",
                    success: function(variables){
                    
                        $.ajax({
                            dataType: "json",
                            url: "${baseUrl}/process-engine/form/form-data?taskId="+taskId,
                            success: function(data){
                                console.log(variables);
                                var form = $("<form id='taskForm_"+taskId+"' name='taskForm_"+taskId+"'/>", { action:'/myaction' });
                                form.attr('id','taskForm_'+taskId);
                                for (v=0;v<variables.length;v++){
                                    console.log(v+" - "+variables[v]);
                                    
                                    //GC 20-12-13// Commento perche' printa il message nella task-form (chissa' qual'era la ratio...)
                                    //if (variables[v].name=='message' && variables[v].value!=null){
                                    //  form.append("<b>"+variables[v].value+"</b>");
                                    //}
                                    
                                }
                                for (f=0;f<data.formProperties.length;f++){
                                    value="";   
                                    required=data.formProperties[f].required;
                                    addClass="";
                                    if (required) addClass="required";
                                    if (data.formProperties[f].value!=null) value=data.formProperties[f].value
                                    if (data.formProperties[f].type=="string"){
                                    
                                        if(data.formProperties[f].id.indexOf("note")==0){
                                            form.append(data.formProperties[f].name+": <br/><textarea class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'>"+value+"</textarea><br/>");
                                        }
                                        
                                        //GIULIO CE-VENETO
                                        else if(data.formProperties[f].id.indexOf("selectStudio")==0){
                                            form.append(data.formProperties[f].name+": <br/><select class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'></select><br/>");
                                        }
                                        
                                        else{
                                            form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/><br/>");
                                        }
                                
                                    }
                                    if (data.formProperties[f].type=="enum"){
                                        options="";
                                        for (ev=0;ev<data.formProperties[f].enumValues.length;ev++){
                                            console.log(data.formProperties[f].enumValues[ev].id);
                                            console.log(data.formProperties[f].enumValues[ev].name);
                                            options+='<option value="'+data.formProperties[f].enumValues[ev].id+'">'+data.formProperties[f].enumValues[ev].name+'</option>';
                                        }
                                        form.append(data.formProperties[f].name+": <select class='taskForm_"+taskId+" "+addClass+"' name='"+data.formProperties[f].id+"'>"+options+"</select><br/>");
                                    }
                                    if (data.formProperties[f].type=="date"){
                                            addClass+= " ";                                 
                                          addClass+= "datePicker";
                                            form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/><br/>");
                                        
                                
                                    }
                                    
                                    form.append('<br/>');
                                }
                                title=task.name; 
                                width=800;
                                height=500;
                                form.dialog({
                                     title: title,
                                     width: width,
                                     height: height,
                                     buttons: {
                                        "Invia": function() {
                                            
                                            var goon=true;
                                            $('.required').each(function(){
                                                if ($(this).val()=='') {
                                                alert('Compilare il campo "'+$(this).attr('label')+'"');
                                                goon=false;
                                                }
                                            });
                                            if (!goon) return false;
                                            var properties=new Array();
                                            var idx=0;
                                            $('.taskForm_'+taskId).each(function(){
                                                prop=new Object();
                                                prop['id']=$(this).attr('name');
                                                prop['value']=$(this).val();
                                                properties[idx]=prop;
                                                idx++;
                                                
                                            });
                                            taskForm=document.forms["taskForm_"+taskId];
                                            //console.log(form);
                                            //return;
                                            var formData=new FormData(taskForm);
                                            //data=new Object();
                                            //data['taskId']=taskId;
                                            //data['properties']=properties;
                                            $(domElement).addClass('disabled');
                                            loadingScreen("Invio in corso", "loading");
                                            $.ajax({
                                                type: "POST",
                                                url: "${baseUrl}/app/rest/documents/submitTask/"+taskId,
                                                data: formData,
                                                contentType:false,
                                                processData:false,
                                                async:false,
                                                cache:false,
                                                 success: function(obj){
                                                    console.log(obj);
                                                    if (obj.result=="OK") {
                                                        //loadingScreen("Operazione terminata", "${baseUrl}/int/images/task.png",1000);//TOSCANA-189
                                                        //form.dialog("close");//TOSCANA-189
                                                        window.location.reload(true);
                                                    }else {
                                                        alert("Errore");
                                                        form.dialog("close");
                                                
                                                    }
                                                }
                                            });
                                            
                                        }
                                    },
                                    close: function( event, ui ) {
                                        $('#taskForm_'+taskId).remove();
                                        
                                    },
                                     open:function(event,ui){
                                     
                                        $(this).find('.datePicker').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
                                        //$(this).find('.datePicker').datepicker('setDate',new Date());
                                        $(this).find('.datePicker:focus').click(function(){
                                            $(this).focus();
                                        });
                                     }
                                    });
                                form.dialog("open");
                                
                                
                                
                                
                                
                                //GC 30-06-2016 Collegamento con studio in CE

								if(domElement.innerText=="Invia dati al CE"){ //TOSCANA-185
                                console.log(variables);
                                var idStud="${elStudio.getFieldDataString('UniqueIdStudio','id')}";
                                var eudractNumber="${elStudio.getFieldDataString('datiStudio','eudractNumber')}";
                                var codiceProt="${elStudio.getFieldDataString('IDstudio','CodiceProt')}";
                                var id_str="${el.getFieldDataCode('IdCentro','Struttura')}";//HDCRPMS-630
								var id_uo="${el.getFieldDataCode('IdCentro','UO')}";//HDCRPMS-630
								var id_pi="${el.getFieldDataCode('IdCentro','PI')}";//HDCRPMS-630
								var ajax_call="yes";
                                $.ajax({
                                  type: "POST",
                                  url: "/checkStudiCE.php",
                                  //data: "eudract="+eudractNumber+"&codice="+codiceProt+"&id="+idStud, //passo i parametri tramite stringa
                                  data: {"eudract":eudractNumber, "codice":codiceProt, "id":idStud,"id_str":id_str,"id_uo":id_uo,"id_pi":id_pi,"ajax_call":ajax_call},   //passo i parametri tramite oggetto json
                                    async:false,
                                    dataType: "json",
                                    
                                  success: function(dato){            
                                      //Ciclare l'array di oggetti con .each
	                                  if(dato.sstatus===undefined){//HDCRPMS-630
                                      $.each( dato, function( key, value ) {
                                          $("select[name='selectStudio']").append('<option value="'+value.code+'">'+value.decode+'</option>');
                                        });
									  }
									  else{
										bootbox.alert(dato.detail,function(){
										setTimeout(function(){form.dialog("close");},0);
										});
                                  }
                                  }
                                });
                                
                                
                                /*
                                url="/checkStudiCE.php?eudract="+eudractNumber;
                                $.getJSON( url, function( data ) {
                            console.log(data);
                            for (i=0;i<data.length;i++){
                                if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==1){
                                    <#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
                                    else selected="";-->
                                    selected="";
                                    $("select[name$='selectStudio']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
                                    if (data[i].auditFiles!=null){
                                        for (a=0;a<data[i].auditFiles.length;a++){
                                            <#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
                                            else selected="";-->
                                            selected="";
                                            $("select[name$='selectStudio']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');        
                                        }
                                    }
                                }
                            }
                            });
                                */
								}
                                
                                
                                
                                
                                
                                
                                
                                $('.datePicker').datepicker({autoclose:true,  format: 'dd/mm/yyyy' });
                                return false;
                            }
                        });
                    }
                });
    }
    
    
    /*
     * TOSCANA-79 VMAZZEO 24.11.2016
     */
    function getDocCeCentro(id){
        $.ajax({
            type: "POST",
            dataType: "html",
            cache: false,
            url: "/getDocCeCentro.php",
            data: "codice="+id ,
            success: function(msg){
            $('#dialog').html(msg);
            $( document ).ready(function() {
                $( "#dialog" ).dialog({minWidth: 700, minHeight: 200});
                });
            }
        });
    }
	//TOSCANA-193 vmazzeo 06.11.2017 download documentazione centro in zip
	function getDocCeCentroZip(id){
		window.location.href="/getDocCeCentro.php?codice="+id+"&zip=true";
		return false;
	}
/*
STSANSVIL-1257 visualizzare nome e cognome utente che ha creato il documento
*/
$( document ).ready(function() {
	$("td[user-allegato]").each(function(){
		userCreator=$(this).html();
		(function(userCreator){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userCreator,
				success: function(data){
					console.log("Chiamata per "+userCreator);
					$(data).each(function(k,result){
						if(result.username===userCreator){
							$("td[user-allegato='"+userCreator+"']").html(result.firstName+" "+result.lastName+" "+userCreator);
						}
					});
				}
			});
		})(userCreator);
	});
	$("td[user-fattpi]").each(function(){
		userFattPI=$(this).html();
		(function(userFattPI){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userFattPI,
				success: function(data){
					console.log("Chiamata per "+userFattPI);
					$(data).each(function(k,result){
						if(result.username===userFattPI){
							$("td[user-fattpi='"+userFattPI+"']").html(result.firstName+" "+result.lastName+" "+userFattPI);
						}
					});
				}
			});
		})(userFattPI);
	});
	$("td[user-fattctc]").each(function(){
		userFattCTC=$(this).html();
		(function(userFattCTC){
		$.ajax({
			type: "GET",
			cache: false,
			url: baseUrl+"/uService/rest/user/searchUser?term="+userFattCTC,
			success: function(data){
				console.log("Chiamata per "+userFattCTC);
				$(data).each(function(k,result){
					if(result.username===userFattCTC){
						$("td[user-fattctc='"+userFattCTC+"']").html(result.firstName+" "+result.lastName+" "+userFattCTC);
					}
				});
			}
		});
		})(userFattCTC);
	});


$("td[user-budgetCreator]").each(function(){
		userBudget=$(this).html();
		(function(userBudget){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userBudget,
				success: function(data){
					console.log("Chiamata per "+userBudget);
					$(data).each(function(k,result){
						if(result.username===userBudget){
							$("td[user-budgetCreator='"+userBudget+"']").html(result.firstName+" "+result.lastName+" "+userBudget);
						}
					});
				}
			});
		})(userBudget);
	});

	/*$("td[user-budgetVersione]").each(function(){
		userBudget=$(this).attr("user-budgetVersione");
		(function(userBudget){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userBudget,
				success: function(data){
					console.log("Chiamata per "+userBudget);
					$(data).each(function(k,result){
						if(result.username===userBudget){
							$("td[user-budgetVersione='"+userBudget+"']").html(result.firstName+" "+result.lastName);
						}
					});
				}
			});
		})(userBudget);
	});*/

	$("td[user-budgetCreatorBB]").each(function(){
		userBudgetBB=$(this).html();
		(function(userBudgetBB){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userBudgetBB,
				success: function(data){
					console.log("Chiamata per "+userBudgetBB);
					$(data).each(function(k,result){
						if(result.username===userBudgetBB){
							$("td[user-budgetCreatorBB='"+userBudgetBB+"']").html(result.firstName+" "+result.lastName+" "+userBudgetBB);
						}
					});
				}
			});
		})(userBudgetBB);
	});

	/*$("td[user-budgetVersioneBB]").each(function(){
		userBudgetBB=$(this).attr("user-budgetVersioneBB");
		(function(userBudgetBB){
			$.ajax({
				type: "GET",
				cache: false,
				url: baseUrl+"/uService/rest/user/searchUser?term="+userBudgetBB,
				success: function(data){
					console.log("Chiamata per "+userBudgetBB);
					$(data).each(function(k,result){
						if(result.username===userBudgetBB){
							$("td[user-budgetVersioneBB='"+userBudgetBB+"']").html(result.firstName+" "+result.lastName);
						}
					});
				}
			});
		})(userBudgetBB);
	});*/
});

function getNomeCognome(user){
	nomeCognome="";
	$.ajax({
		type: "GET",
		cache: false,
		url: baseUrl+"/uService/rest/user/searchUser?term="+userCreator,
		success: function(data){
			$(data).each(function(k,result){
				if(result.username==user){
					nomeCognome=result.firstName+" "+result.lastName;
				}
			});
		}
	});
	return nomeCognome;
}
</@script>  


<@script>
var loadedElement=${loadedJson};
var dummy=${json};
var empties=new Array();

empties[dummy.type.id]=dummy;
</@script>

<#assign json=type.getDummyJson() />
<#assign tipoStudio=elStudio.getFieldDataCode("datiStudio","tipoStudio")/>
<@script>

	var tipoStudio='${tipoStudio}';
	$("#informations-Feasibility_Fase").hide();
	if(tipoStudio=='1'){//Interventistico
		$("#informations-Feasibility_Fase").show();
	}
	$('label.col-sm-3').removeClass('col-sm-3');
	$('.col-sm-9').removeClass('col-sm-9');
	$('.col-sm-12').removeClass('col-sm-12');
 	var dummy=${json};
 	var empties=new Array();
 	empties[dummy.type.id]=dummy;
	$(document).ready(function(){

	var my_tr=$("<tr>");
	var my_td=$("<td>");
	my_td.prop("colspan","2");
	my_td.css("background-color","#DDD");
	my_td.html("<b>STUDIO IN REGIME</b>");
	$("#informations-Feasibility_regimeTerr").before(my_td);

	my_tr=$("<tr>");
	my_td=$("<td>");
	my_td.prop("colspan","2");
	my_td.css("background-color","#DDD");
	my_td.html("<b>COINVOLGIMENTO DELLA FARMACIA</b>");
	$("#informations-Feasibility_FC1").before(my_td);

	my_tr=$("<tr>");
	my_td=$("<td>");
	my_td.prop("colspan","2");
	my_td.css("background-color","#DDD");
	my_td.html("<b>FORNITURA DI BENI IN COMODATO</b>");
	$("#informations-Feasibility_FC27").before(my_td);

	my_tr=$("<tr>");
	my_td=$("<td>");
	my_td.prop("colspan","2");
	my_td.css("background-color","#DDD");
	my_td.html("<b>ESITO VALUTAZIONE</b>");
	$("#informations-Feasibility_ValLocale").before(my_td);

	//TOSCANA-106 vmazzeo 05.05.2017
	$('#informations-IdCentro_inviatoCE').hide();
	$("#IdCentro-IdCentro_inviatoCE").hide();
    
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 2 INIZIO*/
	//VOLONTARI SANI
	var myFeasibility_volSani;
	<#if el.getFieldDataCode('Feasibility','volSani')?? && el.getFieldDataCode('Feasibility','volSani')!="">
		myFeasibility_volSani=${el.getFieldDataCode('Feasibility','volSani')};
	</#if>
	$('#informations-Feasibility_volSaniNr').hide();
	$('#informations-Feasibility_volSaniSpec').hide();
	if(($('#Feasibility_volSani:checked').val()!==undefined && $('#Feasibility_volSani:checked').val().split("###")[0]==1) || (myFeasibility_volSani!==undefined && myFeasibility_volSani==1)){
		$('#informations-Feasibility_volSaniNr').show();
		$('#informations-Feasibility_volSaniSpec').show();
	}
	
	$("[name=Feasibility_volSani]").on('change',function(){
		if($('#Feasibility_volSani:checked').val()!==undefined && $('#Feasibility_volSani:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_volSaniNr').show();
			$('#informations-Feasibility_volSaniSpec').show();
		}
		else{
			$('#informations-Feasibility_volSaniNr').hide();
			$('#informations-Feasibility_volSaniSpec').hide();
			$('#Feasibility_volSaniNr').val("");
			$('#Feasibility_volSaniSpec').val("");//se nascondo sbianco il valore!
		}
	});
	//PEDIATRICI
	var myFeasibility_pediatrici;
	<#if el.getFieldDataCode('Feasibility','pediatrici')?? && el.getFieldDataCode('Feasibility','pediatrici')!="">
		myFeasibility_pediatrici=${el.getFieldDataCode('Feasibility','pediatrici')};
	</#if>

	$('#informations-Feasibility_pediatriciNr').hide();
	if(($('#Feasibility_pediatrici:checked').val()!==undefined && $('#Feasibility_pediatrici:checked').val().split("###")[0]==1) || (myFeasibility_pediatrici!==undefined && myFeasibility_pediatrici==1)){
		$('#informations-Feasibility_pediatriciNr').show();
	}
	
	$("[name=Feasibility_pediatrici]").on('change',function(){
		if($('#Feasibility_pediatrici:checked').val()!==undefined && $('#Feasibility_pediatrici:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_pediatriciNr').show();
		}
		else{
			$('#informations-Feasibility_pediatriciNr').hide();
			$('#Feasibility_pediatriciNr').val("");//se nascondo sbianco il valore!
		}
	});
	//ADULTI
	var myFeasibility_adulti;
	<#if el.getFieldDataCode('Feasibility','adulti')?? && el.getFieldDataCode('Feasibility','adulti')!="">
		myFeasibility_adulti=${el.getFieldDataCode('Feasibility','adulti')};
	</#if>
	$('#informations-Feasibility_adultiNr').hide();
	if(($('#Feasibility_adulti:checked').val()!==undefined && $('#Feasibility_adulti:checked').val().split("###")[0]==1) || (myFeasibility_adulti!==undefined&& myFeasibility_adulti==1)){
		$('#informations-Feasibility_adultiNr').show();
	}
	
	$("[name=Feasibility_adulti]").on('change',function(){
		if($('#Feasibility_adulti:checked').val()!==undefined && $('#Feasibility_adulti:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_adultiNr').show();
		}
		else{
			$('#informations-Feasibility_adultiNr').hide();
			$('#Feasibility_adultiNr').val("");//se nascondo sbianco il valore!
		}
	});
	//REGIME OSPEDALIERO
	$('#informations-Feasibility_regimeAmb').hide();
	$('#informations-Feasibility_regimeDHS').hide();
	$('#informations-Feasibility_regimeRicovero').hide();
	$('#informations-Feasibility_regimeDS').hide();
	$('#informations-Feasibility_regimeSpec').hide();
	var myFeasibility_regimeOsp;
	<#if el.getFieldDataCode('Feasibility','regimeOsp')?? && el.getFieldDataCode('Feasibility','regimeOsp')!="">
		myFeasibility_regimeOsp=${el.getFieldDataCode('Feasibility','regimeOsp')};
	</#if>
	if(($('#Feasibility_regimeOsp:checked').val()!==undefined && $('#Feasibility_regimeOsp:checked').val().split("###")[0]==1) || (myFeasibility_regimeOsp!==undefined && myFeasibility_regimeOsp==1)){
		$('#informations-Feasibility_regimeAmb').show();
		$('#informations-Feasibility_regimeDHS').show();
		$('#informations-Feasibility_regimeRicovero').show();
		$('#informations-Feasibility_regimeDS').show();
		$('#informations-Feasibility_regimeSpec').show();
	}
	
	$("[name=Feasibility_regimeOsp]").on('change',function(){
		if($('#Feasibility_regimeOsp:checked').val()!==undefined && $('#Feasibility_regimeOsp:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_regimeAmb').show();
			$('#informations-Feasibility_regimeDHS').show();
			$('#informations-Feasibility_regimeRicovero').show();
			$('#informations-Feasibility_regimeDS').show();
			$('#informations-Feasibility_regimeSpec').show();
		}
		else{
			$('#informations-Feasibility_regimeAmb').hide();
			$('#informations-Feasibility_regimeDHS').hide();
			$('#informations-Feasibility_regimeRicovero').hide();
			$('#informations-Feasibility_regimeDS').hide();
			$('#informations-Feasibility_regimeSpec').hide();
			$('[name=Feasibility_regimeAmb]').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_regimeDHS]').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_regimeRicovero]').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_regimeDS]').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_regimeSpec]').val('');//se nascondo sbianco il valore!
		}
	});
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 2 FINE*/
	
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 3 INIZIO*/
	$('#se_si_coinvolgimento').hide();
	$('#tutte_le_attivita').hide();
	$('#informations-Feasibility_FC31').hide();
	$('#informations-Feasibility_FC2').hide();
	$('#informations-Feasibility_FC3').hide();
	$('#informations-Feasibility_FC4').hide();
	$('#informations-Feasibility_FC4bis').hide();
	$('#informations-Feasibility_FC5').hide();
	$('#informations-Feasibility_FC6').hide();
	$('#informations-Feasibility_FC6bis').hide();
	$('#informations-Feasibility_FC7').hide();
	$('#informations-Feasibility_FC7bis').hide();
	$('#informations-Feasibility_FC7ter').hide();
	$('#informations-Feasibility_FC8').hide();
	$('#informations-Feasibility_noteFC8').hide();
	$('#informations-Feasibility_FC29').hide();
	$('#informations-Feasibility_FC29bis').hide();
	$('#informations-Feasibility_FC30').hide();
	$('#informations-Feasibility_FC9').hide();
	$('#informations-Feasibility_FC10').hide();
	$('#informations-Feasibility_FC10').hide();
	$('#informations-Feasibility_noteFC10').hide();
	$('#informations-Feasibility_FC27bis').hide();
	$('#informations-Feasibility_FC27ter').hide();
	$('#informations-Feasibility_FC27quar').hide();
	$('[id^=informations-Feasibility_FIN]').hide();
	var myFeasibility_FC1;
	<#if el.getFieldDataCode('Feasibility','FC1')?? && el.getFieldDataCode('Feasibility','FC1')!="">
	myFeasibility_FC1=${el.getFieldDataCode('Feasibility','FC1')};
	</#if>
	if(($('#Feasibility_FC1:checked').val()!==undefined && $('#Feasibility_FC1:checked').val().split("###")[0]==1) ||(myFeasibility_FC1!==undefined && myFeasibility_FC1==1)){
		$('#se_si_coinvolgimento').show();
		$('#tutte_le_attivita').show();
		$('#informations-Feasibility_FC31').show();
		$('#informations-Feasibility_FC2').show();
		$('#informations-Feasibility_FC3').show();
		if($('#Feasibility_FC3:checked').val()!==undefined && $('#Feasibility_FC3:checked').val().split("###")[0]==1){
            $('#informations-Feasibility_FC4').show();
			$('#informations-Feasibility_FC4bis').show();
            $('#informations-Feasibility_FC5').show();
            $('#informations-Feasibility_FC6').show();
			$('#informations-Feasibility_FC6bis').show();
            $('#informations-Feasibility_FC7').show();
            $('#informations-Feasibility_FC7bis').show();
            $('#informations-Feasibility_FC7ter').show();
            $('#informations-Feasibility_FC8').show();
            $('#informations-Feasibility_noteFC8').show();
        }
        else{
            $('#informations-Feasibility_FC4').hide();
			$('#informations-Feasibility_FC4bis').hide();
            $('#informations-Feasibility_FC5').hide();
            $('#informations-Feasibility_FC6').hide();
			$('#informations-Feasibility_FC6bis').hide();
            $('#informations-Feasibility_FC7').hide();
            $('#informations-Feasibility_FC7bis').hide();
            $('#informations-Feasibility_FC7ter').hide();
            $('#informations-Feasibility_FC8').hide();
            $('#informations-Feasibility_noteFC8').hide();
        }
		
		$('#informations-Feasibility_FC29').show();
		$('#informations-Feasibility_FC29bis').show();
		$('#informations-Feasibility_FC30').show();
		$('#informations-Feasibility_FC9').show();
		$('#informations-Feasibility_FC10').show();
		
		if($('#Feasibility_FC10:checked').val()!==undefined && $('#Feasibility_FC10:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_noteFC10').show();
		}
		else {
			$('#informations-Feasibility_noteFC10').hide();
			$('[name=Feasibility_noteFC10').val('');//se nascondo sbianco il valore!
		}
			
	}
	if(($('#Feasibility_FC27:checked').val()!==undefined && $('#Feasibility_FC27:checked').val().split("###")[0]==1) ){
		$('#informations-Feasibility_FC27bis').show();
		$('#informations-Feasibility_FC27ter').show();
		$('#informations-Feasibility_FC27quar').show();
	}
	if(($('#Feasibility_contributoEconomico:checked').val()!==undefined && $('#Feasibility_contributoEconomico:checked').val().split("###")[0]==1) ){
		$('[id^=informations-Feasibility_FIN]').show();
	}
	
	$("[name=Feasibility_FC3]").on('change',function(){
		if($('#Feasibility_FC3:checked').val()!==undefined && $('#Feasibility_FC3:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_FC4').show();
			$('#informations-Feasibility_FC4bis').show();
			$('#informations-Feasibility_FC5').show();
			$('#informations-Feasibility_FC6').show();
			$('#informations-Feasibility_FC6bis').show();
			$('#informations-Feasibility_FC7').show();
			$('#informations-Feasibility_FC7bis').show();
			$('#informations-Feasibility_FC7ter').show();
			$('#informations-Feasibility_FC8').show();
			$('#informations-Feasibility_noteFC8').show();
		}
		else{
			$('#informations-Feasibility_FC4').hide();
			$('#informations-Feasibility_FC4bis').hide();
			$('#informations-Feasibility_FC5').hide();
			$('#informations-Feasibility_FC6').hide();
			$('#informations-Feasibility_FC6bis').hide();
			$('#informations-Feasibility_FC7').hide();
			$('#informations-Feasibility_FC7bis').hide();
			$('#informations-Feasibility_FC7ter').hide();
			$('#informations-Feasibility_FC8').hide();
			$('#informations-Feasibility_noteFC8').hide();
			$('[name=Feasibility_FC4').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC4bis').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC5').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC6').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC6bis').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC7').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC7bis').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC7ter').val('');//se nascondo sbianco il valore!
            $('[name=Feasibility_FC8').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            $('[name=Feasibility_noteFC8').val('');//se nascondo sbianco il valore!
		}
	});
	
	$("[name=Feasibility_FC1]").on('change',function(){
		if($('#Feasibility_FC1:checked').val()!==undefined && $('#Feasibility_FC1:checked').val().split("###")[0]==1){
			$('#se_si_coinvolgimento').show();
			$('#tutte_le_attivita').show();
			$('#informations-Feasibility_FC31').show();
			$('#informations-Feasibility_FC2').show();
			$('#informations-Feasibility_FC3').show();
			//$('#informations-Feasibility_FC4').show();
			//$('#informations-Feasibility_FC5').show();
			//$('#informations-Feasibility_FC6').show();
			//$('#informations-Feasibility_FC7').show();
			//$('#informations-Feasibility_FC7bis').show();
			//$('#informations-Feasibility_FC7ter').show();
			//$('#informations-Feasibility_FC8').show();
			//$('#informations-Feasibility_noteFC8').show();
			$('#informations-Feasibility_FC29').show();
			$('#informations-Feasibility_FC29bis').show();
			$('#informations-Feasibility_FC30').show();
			$('#informations-Feasibility_FC9').show();
			$('#informations-Feasibility_FC10').show();
		}
		else{
			$('#se_si_coinvolgimento').hide();
			$('#tutte_le_attivita').hide();
			$('#informations-Feasibility_FC31').hide();
			$('#informations-Feasibility_FC2').hide();
			$('#informations-Feasibility_FC3').hide();
			$('#informations-Feasibility_FC4').hide();
			$('#informations-Feasibility_FC5').hide();
			$('#informations-Feasibility_FC6').hide();
			$('#informations-Feasibility_FC7').hide();
			$('#informations-Feasibility_FC7bis').hide();
			$('#informations-Feasibility_FC7ter').hide();
			$('#informations-Feasibility_FC8').hide();
			$('#informations-Feasibility_noteFC8').hide();
			$('#informations-Feasibility_FC29').hide();
			$('#informations-Feasibility_FC29bis').hide();
			$('#informations-Feasibility_FC30').hide();
			$('#informations-Feasibility_FC9').hide();
			$('#informations-Feasibility_FC10').hide();
			$('#informations-Feasibility_noteFC10').hide();
			$('[name=Feasibility_FC31').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC2').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC3').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC4').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC5').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC6').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC7').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC7bis').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC7ter').val('');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC8').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_noteFC8').val('');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC29').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC29bis').val('');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC30').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC9').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_FC10').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
			$('[name=Feasibility_noteFC10').val('');//se nascondo sbianco il valore!
		}
	});
	
	$("[name=Feasibility_FC10]").on('change',function(){
		if($('#Feasibility_FC10:checked').val()!==undefined && $('#Feasibility_FC10:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_noteFC10').show();
		}
		else {
			$('#informations-Feasibility_noteFC10').hide();
			$('[name=Feasibility_noteFC10').val('');//se nascondo sbianco il valore!
		}
	});
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 3 FINE*/
	
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 5 INIZIO*/
	//COPERTURA ASSICURATIVA
	$('#copAssNoProfit').hide();
	$('#informations-Feasibility_CopAssA').hide();
	$('#informations-Feasibility_CopAssB').hide();
	$('#informations-Feasibility_CopAssC').hide();
	$('#informations-Feasibility_CopAssPrezzo').hide();
	$('#informations-Feasibility_CopAssNrPolizza').hide();
	$('#informations-Feasibility_CopAssRCT').hide();
	var studioNoProfit=false;
	<#if profit=="2" >
       studioNoProfit=true;
    </#if>
	var myFeasibility_CopAss;
	<#if el.getFieldDataCode('Feasibility','CopAss')?? && el.getFieldDataCode('Feasibility','CopAss')!="">
		myFeasibility_CopAss=${el.getFieldDataCode('Feasibility','CopAss')};
	</#if>
	if(($('#Feasibility_CopAss:checked').val()!==undefined && $('#Feasibility_CopAss:checked').val().split("###")[0]==1) || (myFeasibility_CopAss!==undefined && myFeasibility_CopAss==1)){
		if(studioNoProfit){
    		$('#copAssNoProfit').show();
    		$('#informations-Feasibility_CopAssA').show();
    		$('#informations-Feasibility_CopAssB').show();
    		$('#informations-Feasibility_CopAssC').show();
        }
        $('#informations-Feasibility_CopAssPrezzo').show();
        $('#informations-Feasibility_CopAssNrPolizza').show();
        $('#informations-Feasibility_CopAssRCT').show();
	}
	
	$("[name=Feasibility_CopAss]").on('change',function(){
		if($('#Feasibility_CopAss:checked').val()!==undefined && $('#Feasibility_CopAss:checked').val().split("###")[0]==1){
			if(studioNoProfit){
                $('#copAssNoProfit').show();
    			$('#informations-Feasibility_CopAssA').show();
    			$('#informations-Feasibility_CopAssB').show();
    			$('#informations-Feasibility_CopAssC').show();
            }
			$('#informations-Feasibility_CopAssPrezzo').show();
			$('#informations-Feasibility_CopAssNrPolizza').show();
			$('#informations-Feasibility_CopAssRCT').show();
		}
		else{
		    if(studioNoProfit){
        
                $('#copAssNoProfit').hide();
    			$('#informations-Feasibility_CopAssA').hide();
    			$('#informations-Feasibility_CopAssB').hide();
    			$('#informations-Feasibility_CopAssC').hide();
    			$('[name=Feasibility_CopAssA').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
    			$('[name=Feasibility_CopAssB').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
    			$('[name=Feasibility_CopAssC').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
    		}
			$('#informations-Feasibility_CopAssPrezzo').hide();
            $('[name=Feasibility_CopAssPrezzo').val('');//se nascondo sbianco il valore!
            $('#informations-Feasibility_CopAssNrPolizza').hide();
            $('[name=Feasibility_CopAssNrPolizza').val('');//se nascondo sbianco il valore!
            $('#informations-Feasibility_CopAssRCT').hide();
            $('[name=Feasibility_CopAssRCT').prop('checked', false).trigger('change');//se nascondo sbianco il valore!
            
		}
	});
	
	$("[name=Feasibility_FC27]").on('change',function(){
		if($('#Feasibility_FC27:checked').val()!==undefined && $('#Feasibility_FC27:checked').val().split("###")[0]==1){
			$('#informations-Feasibility_FC27bis').show();
			$('#informations-Feasibility_FC27ter').show();
			$('#informations-Feasibility_FC27quar').show();
		}
		else{
            $('#informations-Feasibility_FC27bis').hide();
			$('#informations-Feasibility_FC27ter').hide();
			$('#informations-Feasibility_FC27quar').hide();
			$('[id=Feasibility_FC27bis]').val('');//se nascondo sbianco il valore!
			$('[id=Feasibility_FC27ter').prop('checked', false);//se nascondo sbianco il valore!
		}
	});
	
	
	$("[name=Feasibility_contributoEconomico]").on('change',function(){
		if($('#Feasibility_contributoEconomico:checked').val()!==undefined && $('#Feasibility_contributoEconomico:checked').val().split("###")[0]==1){
			$('[id^=informations-Feasibility_FIN]').show();
		}
		else{
            $('[id^=informations-Feasibility_FIN]').hide();
			$('[id^=Feasibility_FIN]').val('');//se nascondo sbianco il valore!
		}
	});
	
	$("[id^=Feasibility_FIN]").on('blur',function(){
		var totale = Number($('#Feasibility_FINEntita').val()) + Number($('#Feasibility_FINCoordinamento').val()) + Number($('#Feasibility_FINPersonale').val()) + Number($('#Feasibility_FINAttrezzature').val()) + Number($('#Feasibility_FINServizi').val()) + Number($('#Feasibility_FINMateriale').val()) + Number($('#Feasibility_FINMeeting').val()) + Number($('#Feasibility_FINGenerali').val());
		
		$('#Feasibility_FINTotale').val(totale);
	});
	
	
	
	/*TOSCANA-63 vmazzeo 30.08.2016 - PUNTO 5 FINE*/
	
	/*TOSCANA-74 vmazzeo 20.10.2016 - PUNTO 4 INIZIO*/
    //PREVISIONE IMPIEGO FINANZIAMENTO
    $('#informations-Feasibility_valorePerc6').hide();
    $('#informations-Feasibility_compensiDirigente').hide();
    $('#informations-Feasibility_compensiReparto').hide();
    $('#informations-Feasibility_valorePerc1').hide();
    $('#informations-Feasibility_valorePerc2').hide();
    $('#informations-Feasibility_valorePerc3').hide();
    $('#informations-Feasibility_valorePerc4').hide();
    $('#informations-Feasibility_valorePerc7').hide();
    $('#informations-Feasibility_valorePerc5').hide();
    $('#informations-Feasibility_notePerc5').hide();
    $('#informations-Feasibility_valorePercFarmacologia').hide();//TOSCANA-164
    $('#informations-Feasibility_valorePercUniversitario').hide();//TOSCANA-164
    $('#informations-Feasibility_noteCompensiDirigente').hide();//TOSCANA-164
    $('#informations-Feasibility_noteCompensiReparto').hide();//TOSCANA-164
	$('#informations-Feasibility_valorePerc1Note').hide();//TOSCANA-164
	var myFeasibility_impiegoApplicabile;
	<#if el.getFieldDataCode('Feasibility','impiegoApplicabile')?? && el.getFieldDataCode('Feasibility','impiegoApplicabile')!="">
		myFeasibility_impiegoApplicabile=${el.getFieldDataCode('Feasibility','impiegoApplicabile')};
	</#if>
    if(($('#Feasibility_impiegoApplicabile:checked').val()!==undefined && $('#Feasibility_impiegoApplicabile:checked').val().split("###")[0]==1) || (myFeasibility_impiegoApplicabile!==undefined && myFeasibility_impiegoApplicabile==1)){
        $('#informations-Feasibility_valorePerc6').show();
        $('#informations-Feasibility_compensiDirigente').show();
        $('#informations-Feasibility_compensiReparto').show();
        $('#informations-Feasibility_valorePerc1').show();
        $('#informations-Feasibility_valorePerc2').show();
        $('#informations-Feasibility_valorePerc3').show();
        $('#informations-Feasibility_valorePerc4').show();
        $('#informations-Feasibility_valorePerc7').show();
        $('#informations-Feasibility_valorePerc5').show();
        $('#informations-Feasibility_notePerc5').show();
        $('#informations-Feasibility_valorePercFarmacologia').show(); //TOSCANA-164
    	$('#informations-Feasibility_valorePercUniversitario').show();//TOSCANA-164
        $('#informations-Feasibility_noteCompensiDirigente').show();//TOSCANA-164
    	$('#informations-Feasibility_noteCompensiReparto').show();//TOSCANA-164
		$('#informations-Feasibility_valorePerc1Note').show();//TOSCANA-164

	}
    
    $("[name=Feasibility_impiegoApplicabile]").on('change',function(){
        if($('#Feasibility_impiegoApplicabile:checked').val()!==undefined && $('#Feasibility_impiegoApplicabile:checked').val().split("###")[0]==1){
            $('#informations-Feasibility_valorePerc6').show();
            $('#informations-Feasibility_compensiDirigente').show();
            $('#informations-Feasibility_compensiReparto').show();
            $('#informations-Feasibility_valorePerc1').show();
            $('#informations-Feasibility_valorePerc2').show();
            $('#informations-Feasibility_valorePerc3').show();
            $('#informations-Feasibility_valorePerc4').show();
            $('#informations-Feasibility_valorePerc7').show();
            $('#informations-Feasibility_valorePerc5').show();
            $('#informations-Feasibility_notePerc5').show();
            $('#informations-Feasibility_valorePercFarmacologia').show();//TOSCANA-164
    		$('#informations-Feasibility_valorePercUniversitario').show();//TOSCANA-164
    		$('#informations-Feasibility_noteCompensiDirigente').show();//TOSCANA-164
    		$('#informations-Feasibility_noteCompensiReparto').show();//TOSCANA-164
			$('#informations-Feasibility_valorePerc1Note').show();//TOSCANA-164

	}
        else{
            $('#informations-Feasibility_valorePerc6').hide();
            $('#informations-Feasibility_compensiDirigente').hide();
            $('#informations-Feasibility_compensiReparto').hide();
            $('#informations-Feasibility_valorePerc1').hide();
            $('#informations-Feasibility_valorePerc2').hide();
            $('#informations-Feasibility_valorePerc3').hide();
            $('#informations-Feasibility_valorePerc4').hide();
            $('#informations-Feasibility_valorePerc7').hide();
            $('#informations-Feasibility_valorePerc5').hide();
            $('#informations-Feasibility_notePerc5').hide();
            $('#informations-Feasibility_valorePercFarmacologia').hide();//TOSCANA-164
    		$('#informations-Feasibility_valorePercUniversitario').hide();//TOSCANA-164
        	$('#informations-Feasibility_noteCompensiDirigente').hide();//TOSCANA-164
    		$('#informations-Feasibility_noteCompensiReparto').hide();//TOSCANA-164
			$('#informations-Feasibility_valorePerc1Note').hide();//TOSCANA-164
            $('#Feasibility_valorePerc6').val('');//se nascondo sbianco il valore!
            $('#Feasibility_compensiDirigente').val('');//se nascondo sbianco il valore!
            $('#Feasibility_compensiReparto').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc1').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc2').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc3').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc4').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc7').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePerc5').val('');//se nascondo sbianco il valore!
            $('#Feasibility_notePerc5').val('');//se nascondo sbianco il valore!
            $('#Feasibility_valorePercFarmacologia').val('');//se nascondo sbianco il valore!//TOSCANA-164
            $('#Feasibility_valorePercUniversitario').val('');//se nascondo sbianco il valore!//TOSCANA-164
            $('#Feasibility_noteCompensiDirigente').val('');//se nascondo sbianco il valore!//TOSCANA-164
            $('#Feasibility_noteCompensiReparto').val('');//se nascondo sbianco il valore!//TOSCANA-164
			$('#Feasibility_valorePerc1Note').val('');//se nascondo sbianco il valore!//TOSCANA-164
        }
    });
    /*TOSCANA-74 vmazzeo 20.10.2016 - PUNTO 4 FINE*/
    
    
	$('#document-form-submit').closest('.btn').click(function(){
	     
			        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
				    <#list type.associatedTemplates as assocTemplate>
					<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
					<#if assocTemplate.enabled && templatePolicy.canCreate>
						<#assign template=assocTemplate.metadataTemplate/>
						<#if template.fields??>
			                            <#list template.fields as field>
			                                    <#if field.mandatory>
			                                    	<#assign label=getLabel(template.name+"."+field.name)/>
			                                    	if ($('#${template.name}_${field.name}').val()==""){
			                                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
			                                    			setTimeout(function(){$('#${template.name}_${field.name}').focus();},0);
			                                    		});
														
														return false;
			                                    	}
			                                    </#if>
			                            </#list>
			                         </#if>
						
				        </#if>
				    </#list>
				</#if>
				<#if model['docDefinition'].hasFileAttached>
			        if ($('#file').val()==""){
			        	bootbox.alert("Bisogna allegare un file",function(){
			        		setTimeout(function(){$('#file').focus();},0);
			        	});
			        	
						return false;
			        }
			        <#if !model['docDefinition'].noFileinfo>
			        if ($('#version').val()==""){
			        	bootbox.alert("Il campo versione deve essere compilato",function(){
			        		$('#version').focus();
			        	});
						
						return false;
			        }
			        if ($('#data').val()==""){
			        	bootbox.alert("Il campo data deve essere compilato",function(){
			        		$('#data').focus();
			        	});
						
						return false;
			        }
			        </#if>
		        </#if>
            bootbox.alert('Salvataggio in corso <i class="icon-spinner icon-spin"></i>');
            dummy=formToElement('document-form',dummy);
            saveElement(dummy).done(function(data){
            	bootbox.hideAll();
            	if (data.result=="OK") {
                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');
                    if (data.redirect){
                        window.location.href=data.redirect;
                    }
                }else {
					var errorMessage="Errore salvataggio! <i class='icon-warning-sign red'></i>";
					if(data.errorMessage.includes("RegexpCheckFailed: ")){
						var campoLabel="";
						campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
						campoLabel=messages[campoLabel];
						errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
					}
                	bootbox.alert(errorMessage);
                }
            }).fail(function(){
            	bootbox.hideAll();
                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
           
            });
            
       
    });

// STSANSVIL-4704
//IdCentro_universitario* (RADIO)
if ( loadedElement.metadata.IdCentro_universitario && loadedElement.metadata.IdCentro_universitario[0].split("###")[0] == 2 ) {
$('[id=informations-IdCentro_convenzioni]').hide();
$('[id=informations-IdCentro_convenzioniSpecifica]').hide();
$('[id=informations-IdCentro_aziende]').hide();
}

//IdCentro_convenzioni (RADIO)
if ( loadedElement.metadata.IdCentro_convenzioni && (loadedElement.metadata.IdCentro_convenzioni[0] == undefined || loadedElement.metadata.IdCentro_convenzioni[0].split("###")[0] == 2) ) {
$('[id=informations-IdCentro_convenzioniSpecifica]').hide();
}

$('[id=IdCentro_universitario]').change(function(){gestUniversitario();});
$('[id=IdCentro_convenzioni]').change(function(){gestConvenzioni();});

function gestUniversitario() {
value=$('#IdCentro_universitario[value="1###Si"]').is(':checked');

if (value==true && $('#IdCentro_universitario').is(':visible')){
$('[id=informations-IdCentro_convenzioni]').show();
$('[id=informations-IdCentro_aziende]').show();
}
else {
$('[id=informations-IdCentro_convenzioni]').hide();
$('[id=IdCentro_convenzioni]').prop('checked', false);
$('[id=informations-IdCentro_aziende]').hide();
$('[id=IdCentro_aziende]').prop('checked', false);
$('[id=informations-IdCentro_convenzioniSpecifica]').hide();
$('[id=IdCentro_convenzioniSpecifica]').val('');
}
}

function gestConvenzioni() {
value=$('#IdCentro_convenzioni[value="1###Si"]').is(':checked');

if (value==true && $('#IdCentro_convenzioni').is(':visible')){
$('[id=informations-IdCentro_convenzioniSpecifica]').show();
}
else {
$('[id=informations-IdCentro_convenzioniSpecifica]').hide();
$('[id=IdCentro_convenzioniSpecifica]').val('');
}
}

}); // FINE document ready

</@script>

<@style>
		.ui-jqgrid tr.jqgrow td {
			white-space:normal;
		}
		.ui-jqgrid .ui-jqgrid-htable th div {
			white-space:normal;
			height:auto;
			margin-bottom:3px;
		}
	
		

		
		tr.jqgrow{
			cursor:pointer;
		}
		

		.infobox {
			cursor:pointer;
		}
		.infobox{
		    width: 150px;
		    height: 103px;
		    text-align: center;
				//background-image: -moz-linear-gradient(bottom, #F2F2F2 0%, #FFFFFF 100%);
		}
		
		.infobox > .infobox-data {
		    text-align: center;
		    padding-left: 0px;
		}

</@style>
<@script>
	var $path_base = "${path.base}";//this will be used in gritter alerts containing images
</@script>
<@script>
     function DateFmt(fstr) {
        this.formatString = fstr

        var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
        var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
        var zeroPad = function(number) {
            return ("0"+number).substr(-2,2);
        }

        var twoDigit= function(string){
            return (string+'').substr(2,2);
        }
        var fourDigit= function(string){
            return (string+'').substr(0,4);
        }

        var dateMarkers = {
            d:['getDate',function(v) { return zeroPad(v)}],
            m:['getMonth',function(v) { return zeroPad(v+1)}],
            n:['getMonth',function(v) { return mthNames[v]; }],
            w:['getDay',function(v) { return dayNames[v]; }],
            y:['getFullYear',function(v) { return fourDigit(v)}],
            H:['getHours',function(v) { return zeroPad(v)}],
            M:['getMinutes',function(v) { return zeroPad(v)}],
            S:['getSeconds',function(v) { return zeroPad(v)}],
            i:['toISOString']
        };

        this.format = function(date) {
            var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
                var rv = date[(dateMarkers[p])[0]]()

                if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

                return rv

            });

            return dateTxt
        }

    }
    function stdString(str){
    	if(str && str!="") return str;
    	else return "Valore mancante";
    }
    
    function statoVisite(metadata){
    	if(metadata && metadata.DatiCustomMonitoraggioAmministrativo_VisiteFatturate){
    		return metadata.DatiCustomMonitoraggioAmministrativo_VisiteFatturabili[0]+'/'+metadata.DatiCustomMonitoraggioAmministrativo_VisiteTot[0];
    	}else{
    		return 'Informazione non disponibile';
    	}
    }
    
    function TSToDate2(date){
		if(!date)return "Valore mancante";
		var fmt = new DateFmt("%d/%m/%y");
		return fmt.format(new Date(date));
	}
	 function decode(select){
		if(!select)return "Valore mancante";
		var decode = select.split('###')[1];
		return decode;
	}
	
	function fileLink(file){
		return "<a href='../getAttach/"+file+"'><i class='icon icon-download bigger-160'></i></a> ";
	}
	
	function patList(){
		var grid_selector = "#home-grid-table";
		var pager_selector = "#home-grid-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/MonitoraggioAmministrativo?parent_obj_id_eq=${el.getId()}";
		var colNames=['Data Monitoraggio','Periodo riferimento DA','A','Pazienti arruolati','Pazienti completati e fatturabili','Pazienti completati non fatturabili'];
		var colModel=[
					{name:'codice1',index:'DatiMonitoraggioAmministrativo_dataMonitoraggio', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_dataMonitoraggio.0"},
					{name:'codice2',index:'DatiMonitoraggioAmministrativo_periodoRiferimentoDa', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_periodoRiferimentoDa.0"},
					{name:'codice3',index:'DatiMonitoraggioAmministrativo_periodoRiferimentoA', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_periodoRiferimentoA.0"},
					{name:'codice4',index:'DatiMonitoraggioAmministrativo_numeroArruolati', formatter:stdString, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_numeroArruolati.0"},
					{name:'codice5',index:'DatiMonitoraggioAmministrativo_numeroCompletatiFatturabili', formatter:stdString, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_numeroCompletatiFatturabili.0"},
					{name:'codice5',index:'DatiMonitoraggioAmministrativo_numeroNONCompletatiFatturabili', formatter:stdString, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioAmministrativo_numeroNONCompletatiFatturabili.0"},
				];
		var caption = "Schede Monitoraggio Amministrativo";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
		var DataGrid = $(grid_selector);
 		DataGrid.jqGrid('setGridWidth', '1100');
	}

	function monClinList(){
		var grid_selector = "#grid-monitoraggioclinico-table";
		var pager_selector = "#grid-monitoraggioclinico-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/MonitoraggioClinico?parent_obj_id_eq=${el.getId()}";
		var colNames=['Periodo di riferimento DAL','AL','Data della relazione'];
		var colModel=[
		{name:'codice',index:'DatiMonitoraggioClinico_dataRiferimentoDa', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioClinico_dataRiferimentoDa.0"},
		{name:'codice1',index:'DatiMonitoraggioClinico_dataRiferimentoA', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioClinico_dataRiferimentoA.0"},
		{name:'codice2',index:'DatiMonitoraggioClinico_dataRelazione', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DatiMonitoraggioClinico_dataRelazione.0"},
		];
		var caption = "Schede Monitoraggio Clinico";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
		var DataGrid = $(grid_selector);
		DataGrid.jqGrid('setGridWidth', '1100');
	}
	function safeList(){
		var grid_selector = "#grid-safety";
		var pager_selector = "#grid-safety-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/Safety?parent_obj_id_eq=${el.getId()}";
		var colNames=['Codice evento','Paziente','Insorgenza', 'Gravit&agrave;','Categoria','Evento','Grado'];
		var colModel=[		
		  			{name:'id',index:'id', formatter:stdString, width:30, sorttype:"string",jsonmap:"id"},
		  			{name:'codice1',index:'Safety_Paziente', formatter:decode, width:30, sorttype:"string",jsonmap:"metadata.Safety_Paziente.0"},
		  			{name:'codice2',index:'Safety_DataInsorgenza', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.Safety_DataInsorgenza.0"},
		  			{name:'codice2',index:'Safety_Gravita', formatter:decode, width:30, sorttype:"string",jsonmap:"metadata.Safety_Gravita.0"},
		  			{name:'codice2',index:'Safety_ClassificazioneCTCAECategoria', formatter:decode, width:30, sorttype:"string",jsonmap:"metadata.Safety_ClassificazioneCTCAECategoria.0"},
		  			{name:'codice2',index:'Safety_ClassificazioneCTCAETerm', formatter:decode, width:30, sorttype:"string",jsonmap:"metadata.Safety_ClassificazioneCTCAETerm.0"},
		  			{name:'codice2',index:'Safety_ClassificazioneCTCAEGrado', formatter:decode, width:30, sorttype:"string",jsonmap:"metadata.Safety_ClassificazioneCTCAEGrado.0"},
		  		
		  			
				];
		var caption = "Eventi avversi";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
		var DataGrid = $(grid_selector);
 		DataGrid.jqGrid('setGridWidth', '1100');
	}
	function dsurList(){
		var grid_selector = "#grid-dsur";
		var pager_selector = "#grid-dsury-pager";
		var url=baseUrl+"/app/rest/documents/jqgrid/advancedSearch/DSUR?parent_obj_id_eq=${el.getId()}";
		var colNames=['Titolo','Periodo di riferimento dal','al', 'Data relazione','Scarica'];
		var colModel=[		
		  			{name:'codice',index:'DSUR_Titolo', formatter:stdString, width:30, sorttype:"string",jsonmap:"metadata.DSUR_Titolo.0"},
		  			{name:'codice1',index:'DSUR_PeriodoDal', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DSUR_PeriodoDal.0"},
		  			{name:'codice2',index:'DSUR_PeriodoAl', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"metadata.DSUR_PeriodoAl.0"},
		  			{name:'codice2',index:'DSUR_DataRelazione', formatter:TSToDate2, width:30, sorttype:"string",jsonmap:"file.date"},
		  			{name:'id',index:'id', formatter:fileLink, width:30, jsonmap:"id"},
		  			
				];
		var caption = "DSUR";
		setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
		var DataGrid = $(grid_selector);
 		DataGrid.jqGrid('setGridWidth', '1100');
	}
	
	$(window).bind('hashchange', function(e) {
		if(window.location.hash=='#MonitoraggioAmministrativo-tab2'){
			patList();
		}
		else if(window.location.hash=='#Safety-tab' || window.location.hash=='#sub-safety'){
			if($('#Safety-tab:visible').size()==0){
				$('a[href=#Safety-tab]').click();
				$('a[href=#sub-safety]').click();
			}
			safeList();
		}
		else if(window.location.hash=='#sub-dsur'){
			if($('#Safety-tab:visible').size()==0){
				$('a[href=#Safety-tab]').click();
				$('a[href=#sub-dsur]').click();
			}
			dsurList();
		}
		else if(window.location.hash=='#MonitoraggioClinico-tab2'){
			monClinList();
		}
		
	});
	
	setTimeout(patList,100);
	setTimeout(monClinList,100);


	function processTask(){

		if (!document.getElementById('task-Actions')) return;
		$('#task-Actions').html("");
		gtasks=new Object();
		for(var pKey in globalTasks) {
			console.log(pKey+" - "+globalTasks[pKey].processName);
			for (var pInst in globalTasks[pKey].instances){
				console.log(pInst);
				tasks=globalTasks[pKey].instances[pInst];
				for (tt=0;tt<tasks.length;tt++){
					task=tasks[tt];
					if (task.type=="Alert"){
						alert(task.processVariables.message);
						data=new Object();
						data['taskId']=task.id;
						$.ajax({
								type: "POST",
								contentType: "application/json; charset=utf-8",
								url: "${baseUrl}/process-engine/form/form-data",
								data: JSON.stringify(data),
								success: function(data, textStatus, xhr){
									if (xhr.status==200){
										loadTasks();
									}else alert("Errore!!!");
							}
						});
					}
					if (task.type=="Confirm"){
						gtasks[task.id]=task;
						console.log(task);
						
						if(task.taskKey=="InvioFeasibilityServizi"){ //GC 12/11/2015 - Aggiungo confirm all'invio ai servizi 
							$('#task-Actions').append(' <button class="btn btn-primary btn-sm btn-spaced"  onclick="if(confirm(\'Attenzione! Inviando la richiesta la scheda dei servizi coinvolti non sara\\\' piu\\\' modificabile.\')){executeConfirmTask('+task.id+',this)}"> '+task.name+'</button> ');						
						}/*
						  * TOSCANA-76 abilito visualizzazione task InvioDatiCE 
						  else if(task.taskKey!="InvioDatiCE"){ //GC 30/01/2015 - Per evitare di dover attaccare il processo al pregresso, per il momento oscuro il processo di Invio dati al CE
						  */
						else if(task.name=="Chiudi feasibility PI"){ //GC 12/11/2015 - Aggiungo confirm all'invio ai servizi
						$('#task-Actions').append(' <button class="btn btn-primary btn-sm btn-spaced"  onclick="if(confirm(\'Attenzione l\\\'operazione comporterà la chiusura delle schede dati dello studio, centro e fattibilità che non saranno pertanto più modificabili\')){executeConfirmTask('+task.id+',this)}"> '+task.name+'</button> ');
						}
						else {
							$('#task-Actions').append(' <button class="btn btn-primary btn-sm btn-spaced"  onclick="executeConfirmTask('+task.id+',this);"> '+task.name+'</button> ');						
						}
						
					}
					if (task.type=="Form"){
						gtasks[task.id]=task;
						console.log(task);
						/*GC 07/09/2016 commentato in attesa dei requisiti relativi alle attivita' pre/post cesc in toscana (se applicabili)
						//GC 30/01/2015 - CRPMS-237 - Mostro il bottone di Inserimento valutazione RI se le singole aree sono positive o negative
						var OkPerValutRI=0;
						OkPerValutRI=$('#OkPerValutRI').val();
						console.log(OkPerValutRI);
						if(task.taskKey=="ValutazioneRI" && OkPerValutRI==0){}
						else
						*/
						
						$('#task-Actions').append(' <button class="btn btn-primary btn-sm btn-spaced"  onclick="executeFormTask('+task.id+',this);"> '+task.name+'</button> ');						
					}
				}
			}
		}
	}
	

function deleteElement(element) {
	if(!((typeof element)=='object') && !$.isArray(element)){
		if(isNaN(parseInt(element))){
			bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
			return;
		}else{
		return $.ajax({
			url : '../../rest/documents/delete/' + element,

		}).done(function() {
			console.log('DELETED');
			window.location.reload();
		});
	}
		
	}else if (!element || !element.id){
		bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
		return;
	}
	else{
		return $.ajax({
			url : '../../rest/documents/delete/' + element.id,

		}).done(function() {
			console.log('DELETED');
			window.location.reload();
		});
	}
}
	
</@script>


<@script>

	/*Se seleziono NESSUN SERVIZIO -> sbianco tutti gli altri*/
	$('#ServiziCoinvolti_NessunServizio').click(function(){
		if($('#ServiziCoinvolti_NessunServizio').prop('checked')){
			$("input[id^='ServiziCoinvolti_SERV']").prop('checked',false);
		}
	});
	
	/*Se seleziono un servizio -> sbianco NESSUN SERVIZIO*/
	if($("input[id^='ServiziCoinvolti_SERV']")){
		$("input[id^='ServiziCoinvolti_SERV']").click(function(){
			$('#ServiziCoinvolti_NessunServizio').prop('checked',false)
		});
	}
	
</@script>

<@script>
//SIRER-18 crea nuovo budget con un click (non passa da budgetForm) vmazzeo 22.03.2018
function nuovoBudget(){
	loadingScreen("Creazione in corso", "loading");
	var postUrl = baseUrl + "/app/rest/documents/save/1054"; //1054 typeId Budget
	var postData = new Object();
	postData['parentId'] = ${el.id};
	$.post(postUrl, postData).done(function (data) {
		if (data.result != 'OK') {
			bootbox.alert('Attenzione!!! Errore nel salvataggio');
		}
		else {
			location.href=data.redirect;
			//bootbox.hideAll();
		}
	});
	return false;
}
$( document ).ready(function() {
 	$("#nuovoBudget").unbind("click").bind("click",function(){
		nuovoBudget();
	});
//SIRER-60
//TEMPLATE AVVIO CENTRO
	$("#DatiAvvioCentro-DatiAvvioCentro_dataAperturaCentro div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
	$("#DatiAvvioCentro-DatiAvvioCentro_dataPrimoArr div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
	$("[name=DatiAvvioCentro_aperto]").on('change',function(){
		if($('#DatiAvvioCentro_aperto:checked').val()!==undefined && $('#DatiAvvioCentro_aperto:checked').val().split("###")[0]==1){
			$('#informations-DatiAvvioCentro_dataAperturaCentro').show();
		}
		else if($('#DatiAvvioCentro_aperto:checked').val()===undefined || ($('#DatiAvvioCentro_aperto:checked').val()!==undefined && $('#DatiAvvioCentro_aperto:checked').val().split("###")[0]==2)){
			$('#informations-DatiAvvioCentro_dataAperturaCentro').hide();
			$('#DatiAvvioCentro_dataAperturaCentro').val("");
		}
	});
	$("[name=DatiAvvioCentro_aperto]").trigger("change");
	$("[name=DatiAvvioCentro_arrPrimoPaz]").on('change',function(){
		if($('#DatiAvvioCentro_arrPrimoPaz:checked').val()!==undefined && $('#DatiAvvioCentro_arrPrimoPaz:checked').val().split("###")[0]==1){
			$('#informations-DatiAvvioCentro_dataPrimoArr').show();
		}
		else if($('#DatiAvvioCentro_arrPrimoPaz:checked').val()===undefined || ($('#DatiAvvioCentro_arrPrimoPaz:checked').val()!==undefined && $('#DatiAvvioCentro_arrPrimoPaz:checked').val().split("###")[0]==2)){
			$('#informations-DatiAvvioCentro_dataPrimoArr').hide();
			$('#DatiAvvioCentro_dataPrimoArr').val("");
		}
	});
	$("[name=DatiAvvioCentro_arrPrimoPaz]").trigger("change");
	
	
	
	$('#salvaForm-DatiAvvioCentro').off('click').on('click',function(){
		var $form=$($(this).data('rel'));
    if($(this).attr('id')){
    var formName=$(this).attr('id').replace("salvaForm-", "");
    }
    else{
    formName="formNonEsistente"
    }
	
	//LUIGI controllo ad-hoc sulla sequenzialità date
	date_split1=$('#DatiAvvioCentro_dataAperturaCentro').val().split("/");
	date1= new Date(date_split1[2], date_split1[1]-1, date_split1[0], 0, 0, 0, 0);
	date_split2=$('#DatiAvvioCentro_dataPrimoArr').val().split("/");
	date2= new Date(date_split2[2], date_split2[1]-1, date_split2[0], 0, 0, 0, 0);
	if (date2<date1){
		alert ('la data di arurolamento primo soggetto non può essere precedente alla data di apertura centro');
		return false;
    }
	
    var goon=true;
    if (eval("typeof "+formName+"Checks == 'function'")){
    eval("goon="+formName+"Checks()");
    }
    if (!goon) return false;
    loadingScreen("Salvataggio in corso...", "loading");

    try{
    var myElement={};
    myElement.id=loadedElement.id;
    myElement.type=loadedElement.type;
    myElement.metadata={};
    myElement=formToElement($form,myElement,'Farmaco');
    saveElement(myElement).done(function(data){
    bootbox.hideAll();
    if (data.result=="OK") {
    loadingScreen("Salvataggio effettuato", "green_check");


    //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
    window.setTimeout(function(){
    bootbox.hideAll();
    }, 3000);

    if (data.redirect){
    window.location.href=data.redirect;
    }
    }else {
		var errorMessage="Errore salvataggio! <i class='icon-warning-sign red'></i>";
		if(data.errorMessage.includes("RegexpCheckFailed: ")){
			var campoLabel="";
			campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
			campoLabel=messages[campoLabel];
			errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
		}
		bootbox.alert(errorMessage);
    }
    }).fail(function(){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");


    });
    }catch(err){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");
    console.log(err);
    }
	});

	
	
	
	
//TEMPLATE FINE CENTRO
	$("#DatiChiusuraCentro-DatiChiusuraCentro_dataConclusioneCentro div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
	$("#DatiChiusuraCentro-DatiChiusuraCentro_dataConclusioneArr div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
	$("#DatiChiusuraCentro-DatiChiusuraCentro_dataFineTrattamento div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
	$("[name=DatiChiusuraCentro_conclusioneAnticipataRadio]").on('change',function(){
		if($('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val()!==undefined && $('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val().split("###")[0]==1){
			$('#informations-DatiChiusuraCentro_conclusioneAnticipata').show();
		}
		else if($('#DatiAvvioCentro_aperto:checked').val()===undefined || ($('#DatiAvvioCentro_aperto:checked').val()!==undefined && $('#DatiAvvioCentro_aperto:checked').val().split("###")[0]==2)){
			$('#informations-DatiChiusuraCentro_conclusioneAnticipata').hide();
			$("#DatiChiusuraCentro_conclusioneAnticipata:checked").each(function(){
				$(this).prop("checked",false)
			});
		}
	});
	$("[name=DatiChiusuraCentro_conclusioneAnticipataRadio]").trigger("change");

});

function DatiChiusuraCentroChecks(){

	//LUIGI controllo ad-hoc sulla sequenzialità date
	date_split1=$('#DatiChiusuraCentro_dataConclusioneArr').val().split("/");
	date1= new Date(date_split1[2], date_split1[1]-1, date_split1[0], 0, 0, 0, 0);
	date_split2=$('#DatiChiusuraCentro_dataConclusioneCentro').val().split("/");
	date2= new Date(date_split2[2], date_split2[1]-1, date_split2[0], 0, 0, 0, 0);
	if (date2<date1){
	alert ('la data di conclusione centro non può essere precedente alla data di conclusione arruolamento');
	return false;
	}
	return true;
}
</@script>


<@script>
function protocollaElement(elementId, docFileName, studioId, fascicoloStudio,templateName,centroId,userMittente,codiceProtStudio,PICognome,tipoDoc) {
	<#assign userCF = userDetails.username />
	<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
		<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
	</#if>
	var userCF = '${userCF}';
	<#if userDetails.hasRole("CTC") || userDetails.hasRole("SEGRETERIA") || userDetails.hasRole("UFFAMM") >
	var profileProtocollo=true;
	<#else>
	var profileProtocollo=false;
	</#if>

	if(!profileProtocollo){
		alert("Attenzione: la tua utenza non � abilitata all'invio di documenti al protocollo aziendale");
		return false;
	}

	<#assign userPROTOCOLLO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
		<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
	</#if>
	var userPROTOCOLLO = '${userPROTOCOLLO}';

	<#assign userAZI = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
		<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
	</#if>
	var userAZI = '${userAZI}';

	<#assign userREGISTRO = "" />
	<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
		<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
	</#if>
	var userREGISTRO = '${userREGISTRO}';

	if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
		alert('Attenzione: la procedura di integrazione con protocollo aziendale non è attiva per questo centro');
		return false;
	}


	<#assign userAZI_DESCR = "" />
	<#if userDetails.getSiteDataValue('DESCR')?? >
	<#assign userAZI_DESCR = userDetails.getSiteDataValue('DESCR') />
	</#if>
	var userAZI_DESCR = '${userAZI_DESCR}';



	var anno = new Date();
	var post_data="AZIENDA="+userAZI+"&AZIENDA_DESCR="+userAZI_DESCR+"&REGISTRO="+userREGISTRO+"&ANNO="+anno.getFullYear()+"&USERCF="+userCF+"&STUDIO_CODE="+studioId+"&STUDIO_PROT_CODE="+codiceProtStudio+"&PICognome="+PICognome;

	<#if userPROTOCOLLO=="Babel">
		<#assign INTEGRAZIONE_STRUTTURA = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_STRUTTURA')?? >
			<#assign INTEGRAZIONE_STRUTTURA = userDetails.getSiteDataValue('INTEGRAZIONE_STRUTTURA')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_STRUTTURA = '${INTEGRAZIONE_STRUTTURA}';
		post_data+="&INTEGRAZIONE_STRUTTURA="+INTEGRAZIONE_STRUTTURA.replace(/(\r\n|\n|\r)/gm, "");

		<#assign INTEGRAZIONE_ASSEGNATARI = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_ASSEGNATARI')?? >
			<#assign INTEGRAZIONE_ASSEGNATARI = userDetails.getSiteDataValue('INTEGRAZIONE_ASSEGNATARI')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_ASSEGNATARI = '${INTEGRAZIONE_ASSEGNATARI}';
		post_data+="&INTEGRAZIONE_ASSEGNATARI="+INTEGRAZIONE_ASSEGNATARI.replace(/(\r\n|\n|\r)/gm, "");

		<#assign INTEGRAZIONE_CLASSIFICAZIONE = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_CLASSIFICAZIONE')?? >
			<#assign INTEGRAZIONE_CLASSIFICAZIONE = userDetails.getSiteDataValue('INTEGRAZIONE_CLASSIFICAZIONE')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_CLASSIFICAZIONE = '${INTEGRAZIONE_CLASSIFICAZIONE}';
		post_data+="&INTEGRAZIONE_CLASSIFICAZIONE="+INTEGRAZIONE_CLASSIFICAZIONE.replace(/(\r\n|\n|\r)/gm, "");


		<#assign INTEGRAZIONE_TIPOFASCICOLO = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_TIPOFASCICOLO')?? >
			<#assign INTEGRAZIONE_TIPOFASCICOLO = userDetails.getSiteDataValue('INTEGRAZIONE_TIPOFASCICOLO')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_TIPOFASCICOLO = '${INTEGRAZIONE_TIPOFASCICOLO}';
		post_data+="&INTEGRAZIONE_TIPOFASCICOLO="+INTEGRAZIONE_TIPOFASCICOLO.replace(/(\r\n|\n|\r)/gm, "");

		<#assign INTEGRAZIONE_RESPONSABILE = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_RESPONSABILE')?? >
			<#assign INTEGRAZIONE_RESPONSABILE = userDetails.getSiteDataValue('INTEGRAZIONE_RESPONSABILE')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_RESPONSABILE = '${INTEGRAZIONE_RESPONSABILE}';
		post_data+="&INTEGRAZIONE_RESPONSABILE="+INTEGRAZIONE_RESPONSABILE.replace(/(\r\n|\n|\r)/gm, "");

		<#assign INTEGRAZIONE_VICARI = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_VICARI')?? >
			<#assign INTEGRAZIONE_VICARI = userDetails.getSiteDataValue('INTEGRAZIONE_VICARI')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_VICARI = '${INTEGRAZIONE_VICARI}';
		post_data+="&INTEGRAZIONE_VICARI="+INTEGRAZIONE_VICARI.replace(/(\r\n|\n|\r)/gm, "");

		<#assign INTEGRAZIONE_PERMESSI = "" />
		<#if userDetails.getSiteDataValue('INTEGRAZIONE_PERMESSI')?? >
			<#assign INTEGRAZIONE_PERMESSI = userDetails.getSiteDataValue('INTEGRAZIONE_PERMESSI')?trim?replace("(\r\n)+", "",'r') />
		</#if>
		var INTEGRAZIONE_PERMESSI = '${INTEGRAZIONE_PERMESSI}';
		post_data+="&INTEGRAZIONE_PERMESSI="+INTEGRAZIONE_PERMESSI.replace(/(\r\n|\n|\r)/gm, "");

		var NOME_COGNOME = '';
		$.ajax({
			type : "GET",
			cache: false,
			url : baseUrl+'/uService/rest/user/searchUser?term='+userMittente
		}).done(function(content) {
			NOME_COGNOME=content[0].firstName+" "+content[0].lastName;
			post_data+="&NOME_COGNOME="+NOME_COGNOME.replace(/(\r\n|\n|\r)/gm, "");
		});

	</#if>

	bootbox.alert('Invio in corso <i class="gear blue" ></i>');
	if (!fascicoloStudio){
		$.ajax({
			type : "POST",
			cache: false,
			data : post_data,
			url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/createFolder.php',
			async:false,
		}).done(function(result) {
			console.log(result);
			//alert(result);
			if(result.includes('"code" : "500"') || !result.match(/^[a-zA-Z0-9\/.-]+$/)){
				bootbox.hideAll();
				alert("ERRORE INSERIMENTO FASCICOLO: "+result);
			}else{
				//Aggiorna oggetto studio
				$.ajax({
					type: "POST",
					cache: false,
					url: baseUrl+"/app/rest/documents/update/"+centroId,
					data: "IdCentro_ProtocolloFascicolo="+result ,
					async: false,
					success: function(msg){
						//window.location.reload();
						fascicoloStudio = result;
					}
				});
				//window.location.reload();
			}
		});
	}
	//Inserisci documento effettivo
	if (fascicoloStudio){
		var attach="";
		$.ajax({
			type : "GET",
			cache: false,
			url : baseUrl+'/app/documents/getAttachBase64/'+elementId
		}).done(function(content) {
			//alert(content);
			if (content){
				//var attach=b64EncodeUnicode(content); //btoaUTF16(content); // Base64.encode(content); //window.btoa(content); //$.base64.encode(content); //Base64.encode(content);
				//var decode = Base64.decode(attach);
				//attach = php_base64_encode(content);
				//return;
				var attach = content;
				$.ajax({
					type : "POST",
					cache: false,
					data : post_data+"&TIPO_DOC="+tipoDoc+"&STUDIO_FASCICOLO="+fascicoloStudio+"&DOCUMENTO_CODE="+elementId+"&DOCUMENTO_FILENAME="+docFileName+"&DOCUMENTO_BODY="+attach,
					url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/sendFileContentPEBody.php',

				}).done(function(result) {
					console.log(result);
					//alert(result);
					if(result.includes('"code" : "500"') || result.includes('"code" : "404"') || !result.match(/^(\d+)\/(\d+)$/)){
						bootbox.hideAll();
						alert("ERRORE INSERIMENTO DOCUMENTO: "+result);
					}else{
						//Aggiorna oggetto studio
						$.ajax({
							type: "POST",
							cache: false,
							url: baseUrl+"/app/rest/documents/update/"+elementId,
							data: templateName+"_ProtocolloNumero="+result+"&"+templateName+"_ProtocolloRegistro="+userREGISTRO+"&"+templateName+"_ProtocolloAzienda="+userAZI ,
							success: function(msg){
								window.location.reload();
							}
						});
						//window.location.reload();
					}
				});
			}else{
				bootbox.hideAll();
				alert("Contenuto file non disponibile.");
			}
		});
	}else{
		bootbox.hideAll();
		alert("Fascicolo per lo studio non presente.");
	}

	return false;
}

function vediProtocollo(codiceProtocollo) {
<#assign userCF = userDetails.username />
<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
</#if>

var userCF = '${userCF}';

<#assign userPROTOCOLLO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
</#if>
var userPROTOCOLLO = '${userPROTOCOLLO}';

<#assign userAZI = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
</#if>
var userAZI = '${userAZI}';

<#assign userREGISTRO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
</#if>
var userREGISTRO = '${userREGISTRO}';

if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
alert('Attenzione: la procedura di integrazione con protocollo aziendale non è attiva per questo centro');
return false;
}
	//alert(codiceProtocollo);
	if (codiceProtocollo){
		var codiceSplit = codiceProtocollo.split('/');
		<#if userPROTOCOLLO=="Babel">

		$.ajax({
			type : "POST",
			dataType: "json",
			cache: false,
			data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF,
			url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileList.php',
		}).done(function(result) {
			if(result.code!==undefined && (result.code=="500" || result.code== "404" || !result.code.match(/^[a-zA-Z0-9\/.-]+$/))){
				alert("ERRORE RECUPERO FASCICOLO: "+result.message);
			}else{

					/*$(result).each(function(myFile,info){
						alert(info.id);
					});*/
					var file_id=result[0].id;
					var file_name=result[0].nome;
					window.open('/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileContent.php?'+"AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF+"&ID_FILE="+file_id+"&NOME_FILE="+file_name);
					/*
					$.ajax({
						type : "GET",
						cache: false,
						async: false,
						data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF+"&ID_FILE="+file_id+"&NOME_FILE="+file_name,
						url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileContent.php',
						}).done(function(response) {
						alert(response);
					});
					*/
			}
		});
		</#if>
		<#if userPROTOCOLLO=="Docsuite">
			$.ajax({
				type : "GET",
				cache: false,
				data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF,
				url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileContent.php'
			}).done(function(result) {
				console.log(result);
				window.open(result);
			});
		</#if>
		<#if userPROTOCOLLO=="Iride">
			/*$.ajax({
				type : "GET",
				cache: false,
				data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF,
				url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileContent.php'
			}).done(function(result) {
				console.log(result);
				window.open(result);
			});*/
			window.open('/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileContent.php?'+"ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]);
		</#if>
	}
}
</@script>
