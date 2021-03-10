<style>

	.clearfix:after {
    content: ".";
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
    }

	.clearfix {
    clear: both;
    }
    
	.vs{
		float: left;
    width: 50%;
    height:180px;
	}
	.vs label{
	width:35%;
	}

	.re{
		float: left;
    width: 40%;
	//    height:180px;
	}
	.re label{
	width:60%;
	}

	.ri{
		float: left;
    width: 80%;
	}
	.ri label{
	width:55%;
	}

	.vl{
		float: left;
    width: 90%;
	}
	.vl label{
	width:55%;
	}

	.ui-autocomplete.ui-menu{
	z-index:9999!important;
	}
	th label{
	font-weight:bold;
	}

	.select2-container{
		width:100% !important;
	}

</style>

<#include "../helpers/MetadataTemplate.ftl"/>

<div style="display: block">
	<!--div style="float: right"-->
	<div style="float: left">
	<!--#include "../helpers/information.ftl"/-->
	<!--#include "../helpers/actions.ftl"/-->
	<!--#include "../helpers/workflow.ftl"/-->
	<!--#include "../helpers/permission.ftl"/-->
	</div>
    			
  
  

	<#assign activeProcess=false/>
  <#assign disabled="disabled='disabled'"/>
  <#assign statoMilestone="pending">
  <#if model["activeProcesses"]??>
  	<#list model["activeProcesses"] as ist>
  		<#assign disabled=""/>
  		<#assign activeProcess=true/>
  		<#assign statoMilestone="Inviata">
  	</#list>
  </#if>
  
  <div id="tabs">
  	<ul>
  		<li><a id='tab0' href="#tabs-0">Scheduling</a></li>
  		<#if getUserGroups(userDetails)!='SR'>
  			<li><a id='tab1' href="#tabs-1">Richieste di fatturazione</a></li>
  		</#if> 
  		<li><a id='tab2' href="#tabs-2">Fatture</a></li>
  	</ul>
        		
    <div id="tabs-0">
    	

    	<#list el.templates as template>	<!-- ${template.name} IdCentro DatiCentro Feasibility-->
	 			<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	 				<#if template.name="scheduling">
					 <#if activeProcess>
    					 	<div id="processes" style="float:left">
									<#if userDetails.hasRole('CTC')>

							 			<button class="btn btn-warning btn-sm" onclick="javascript:saveAll();if(!stopSaving)formSubmitStd('${template.name}');" ><i class="icon-save " ></i><b>Salva</b></span></button>
									</#if>
    					 	</div>
    					 </#if>
    	<!--processo chiudi scheduling-->
    	<div id="task-Actions"> </div>	<div class="clearfix"></div>	
    	<br><br>
				    <#list el.elementTemplates as elementTemplate>
				    	<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>	
							<!--@TemplateForm template.name el userDetails editable/-->
							
							<!-- DIV IMPORTANTISSIMO PER DIFFERENZIARE I CONTENUTI NEI VARI TAB-->
							<div id="metadataTemplate-${template.name}" class="allInTemplate">
							
							<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
				    		
				    		<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
				    		<#assign stillOpen=true />
    		    			<form autocomplete="off" name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
								<#else>
								<#assign stillOpen=false />
								</#if>
								
						
							
							<#--list template.fields as field>
				    		<@SingleField template.name field.name el userDetails editable/>				
	  		   		</#list-->
	  		   		
	  		   		
											<#assign thead0="<div class=\"table-header\"> Intestatario Fattura </div><div class=\"table-responsive\"><table class=\"table table-striped table-bordered table-hover\" ><thead><tr>" />
                    
                    <#assign tbody0="<tbody><tr>" />
                    <#assign tclose0="</tr></tbody></table></div>"/>
                    <#list template.fields as field>
										<#if field.name=="DestinatarioRagSoc" || field.name=="DestinatarioPIVA" || field.name=="DestinatarioIndirizzo" >
											<#assign thead0>
												${thead0}
												<th><@SingleFieldLabel template.name field.name field.mandatory /></th>
											</#assign>
											<#assign tbody0>
												${tbody0}
												<td><@SingleFieldNoLabel template.name field.name el userDetails editable /></td>
											</#assign>
										</#if>
									</#list>
									${thead0}${tbody0}${tclose0}

									<#assign thead0="<div class=\"table-header\"> Indirizzo Fatturazione </div><div class=\"table-responsive\"><table class=\"table table-striped table-bordered table-hover\" ><thead><tr>" />

									<#assign tbody0="<tbody><tr>" />
									<#assign tclose0="</tr></tbody></table></div>"/>
									<#list template.fields as field>
										<#if field.name=="FatturazioneRagSoc" || field.name=="FatturazionePIVA" || field.name=="FatturazioneIndirizzo" >
                            <#assign thead0>
                                ${thead0}
                                <th><@SingleFieldLabel template.name field.name field.mandatory /></th>
                            </#assign>
                            <#assign tbody0>
                                ${tbody0}
                                <td><@SingleFieldNoLabel template.name field.name el userDetails editable /></td>
                            </#assign>
                        </#if>  
                    </#list>
	  		   		${thead0}${tbody0}${tclose0}
	  		   		
	  		   		<#assign thead1="<div class=\"table-header\"> Modalit&agrave; di fatturazione </div><div class=\"table-responsive\"><table class=\"table table-striped table-bordered table-hover\" ><thead><tr>" />
	  		   		
	  		   		<#assign tbody1="<tbody><tr>" />
	  		   		
	  		   		<#list template.fields as field>
				<#if field.name!="DestinatarioRagSoc" && field.name!="DestinatarioPIVA" && field.name!="DestinatarioIndirizzo" && field.name!="FatturazioneRagSoc" && field.name!="FatturazionePIVA" && field.name!="FatturazioneIndirizzo">
								<#if field.name="ValoreAssoluto">
									<#assign thead1>
										${thead1}
										<th>Pazienti totali stimati:</th>
										</tr></thead>
									</#assign>
									<#assign tbody1>
										${tbody1}
										<td>${el.getfieldData("InfoBudget","Pazienti")[0]!""}</td>
										</tr></tbody></table></div>
</#assign>
<#assign thead2="<div class=\"table-header\" id=\"startUp-head\"> Start-up </div><div class=\"table-responsive\" id=\"startUp-body\"><table class=\"table table-striped table-bordered table-hover\" ><thead><tr>" />
									<#assign tbody2="<tbody><tr>" />
								</#if>
								<#if thead2??>
									<#assign thead2>
										${thead2}
										<th><@SingleFieldLabel template.name field.name field.mandatory /></th>
									</#assign>
									<#assign tbody2>
										${tbody2}
										<td><@SingleFieldNoLabel template.name field.name el userDetails editable /></td>
									</#assign>
								<#else>
									<#assign thead1>
										${thead1}
										<th><@SingleFieldLabel template.name field.name field.mandatory /></th>
									</#assign>
									<#assign tbody1>
										${tbody1}
										<td><@SingleFieldNoLabel template.name field.name el userDetails editable /></td>
									</#assign>
								</#if>
	  					</#if>	
	  					</#list>
	  					<#assign thead2>
							${thead2}
							<th>Budget totale studio a preventivo:</th>
</tr></thead>
						</#assign>
						<#assign tbody2>
							${tbody2}
							<td><span id="prezzoBudget">${el.getfieldData("InfoBudget","Prezzo")[0]!""}</span></td>
							</tr></tbody></table></div>
</#assign>
${thead1}${tbody1}
						
<#--div style="clear:both;">
	  						<label>
	  							Budget totale studio a preventivo:
	  							<span id="prezzoBudget">${el.getfieldData("InfoBudget","Prezzo")[0]!""}</span>
	  						</label>
	  					</div-->
	  					
							
				    	
				    		
				    	<#assign tipCalc=el.getFieldDataCode("scheduling","TipologiaCalcolo")!"" />
				    	<#if stillOpen ||  tipCalc!="4">
				    		<div id="timepoint">
				    	<#else>
				    		<div>
				    	</#if>	

   								<#assign parentEl=el/>     												
    								
    								<!-- tabella visite inizio-->
    								<div class="row">
											<div class="col-xs-12">
											<div class="clearfix"></div>
											
												<div class="table-header"> Selezionare le visite al cui completamento attivare la fatturazione </div>
												<div class="table-responsive">	
    											<table id="sample-table-1" class="table table-striped table-bordered table-hover">
														<thead>
															<tr>
    														<th class="hidden-480">Descrizione</th>
    														<th class="hidden-480">Numero visita</th>
    														<th class="hidden-480">Tempi</th>
    														<th class="hidden-480">Durata</th>
    														<th class="hidden-480">Ricovero</th>
    														<th class="hidden-480">Seleziona</th>														
    													</tr>
    												</thead>
														
														<tbody>
    													<#list parentEl.getChildrenByType("TPFatt") as subEl>
    							 							<#if (subEl.id)??>
    							 								<#if (subEl.getfieldData("DatiTPFatt","TPBudget")?size>0)>
    							 									<#assign tpfatt=subEl.getfieldData("DatiTPFatt","TPBudget")[0] />
    																<tr>
    																	<td class="hidden-480">			
    																		<div id="informations-DatiTPFatt_CheckFatt">
    																			<label for="${subEl.id}">
    																				${tpfatt.getFieldDataDecode("TimePoint","DescrizioneSelect")!""}
    																			</label>
    																		</div>
    																	</td>
    																
    																	<td class="hidden-480">			
    																		<div id="informations-DatiTPFatt_CheckFatt">
    																			<label for="${subEl.id}">
    																				${tpfatt.getFieldDataString("TimePoint","NumeroVisita")}
    																			</label>
    																		</div>
    																	</td>
    																
    																	<td class="hidden-480">			
    																		<div id="informations-DatiTPFatt_CheckFatt">
    																			<label for="${subEl.id}">
    																				${tpfatt.getFieldDataString("TimePoint","Tempi")} ${tpfatt.getFieldDataDecode("TimePoint","TempiSelect")!""}
    																			</label>
    																		</div>
    																	</td>
    																
    																	<td class="hidden-480">			
    																		<div id="informations-DatiTPFatt_CheckFatt">
    																			<label for="${subEl.id}">
    																				${tpfatt.getFieldDataString("TimePoint","DurataCiclo")}  ${tpfatt.getFieldDataDecode("TimePoint","DurataSelec")!""}
    																			</label>
    																		</div>
    																	</td>
    																	
    																	<td class="hidden-480">			
    																		<div id="informations-DatiTPFatt_CheckFatt">
    																			<label for="${subEl.id}">
    																				${tpfatt.getFieldDataDecode("TimePoint","RicoveroSelect")!""}
    																			</label>
    																		</div>
    																	</td>
    																	
    																	<td class="hidden-480" align="center">
    																		<input type="checkbox" <#if !stillOpen>disabled="disabled"</#if>  data-name="DatiTPFatt_CheckFatt" id="${subEl.id}" <#if (subEl.getfieldData("DatiTPFatt","CheckFatt")?size>0 && subEl.getfieldData("DatiTPFatt","CheckFatt")[0]=='1') > checked="checked" </#if> >
    																	</td>
    																</tr>
              		    				
    															</#if>
    														</#if>
    													</#list>
    												</tbody>
													</table>
												</div>
											</div>
										</div>
										<!-- tabella visite fine-->

   							</div>
   									
   							${thead2}${tbody2}		
   							
				    	</form>
   							<div id="prestazioni">
   								<#assign parentEl=el/>
                	
									<!-- tabella prestazioni inizio-->
    							<div class="row">
										<div class="col-xs-12">
										
											<div class="table-header"> Selezionare ulteriori prestazioni/servizi in inizio/fine fattura </div>
											<div class="table-responsive">	
    										<table id="sample-table-1" class="table table-striped table-bordered table-hover">
													<thead>
														<tr>
    													<th class="hidden-480" align="left">Prestazione</th>
    													<th class="hidden-480" style="text-align:right;">Prezzo &euro;</th>
    													<th class="hidden-480">Descrizione voce in fattura</th>
    													<th class="hidden-480">Inizio</th>
    													<th class="hidden-480">Rate</th>
    													<th class="hidden-480">Fine</th>
    													<th class="hidden-480">Rimborsabile</th>
    												</tr>
    											</thead>
													
													<tbody>
    							
    												<#list parentEl.getChildrenByType("PrestazioniFatt") as subEl>
    		 											<#if (subEl.id)??>
    		 												<#if (subEl.getfieldData("DatiPrestazioniFatt","PrestazioneBudget")?size>0)>
    		 													<#assign prestfatt1=subEl.getfieldData("DatiPrestazioniFatt","PrestazioneBudget")[0] />
    		 													<#if prestfatt1.getType().getTypeId()=="PrezzoPrestazione">
    		 														<#--PREST IN BUD CLINICO-->
    		 														<#assign prestfatt=prestfatt1.getfieldData("PrezzoFinale","Prestazione")[0] />
    		 														
    		 														<#if prestfatt1.getfieldData("PrezzoFinale","Prezzo")?? && (prestfatt1.getfieldData("PrezzoFinale","Prezzo")?size>0) >
    		 															<#assign prezzo=prestfatt1.getfieldData("PrezzoFinale","Prezzo")[0] />
    		 														<#else>
    		 															<#assign prezzo=prestfatt.getfieldData("Costo","TransferPrice")[0] />
    		 														</#if>
    		 													<#else>
    		 														<#--PREST IN BUD STUDIO-->
    		 														<#assign prestfatt=subEl.getfieldData("DatiPrestazioniFatt","PrestazioneBudget")[0] />
    		 															<#if prestfatt1.getfieldData("Costo","Prezzo")?? && (prestfatt1.getfieldData("Costo","Prezzo")?size>0) >
    		 																<#assign prezzo=prestfatt1.getfieldData("Costo","Prezzo")[0]>
    		 																<#else>
    		 																<#assign prezzo=prestfatt1.getfieldData("CostoAggiuntivo","Costo")[0]>
    		 															</#if>
    		 													</#if>
            								
    															<tr>
    																<td class="hidden-480">
    																	<div id="informations-DatiPrestazioniFatt_AccontoRataSaldo" >
    																		<label for="${subEl.id}">
    																			<@elementTitle prestfatt/>
    																		</label>
    																	</div>
    																		<#--input type="checkbox" name="DatiPrestazioniFatt_AccontoRataSaldo" id="${subEl.id}" <#if (subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")?size>0 && subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")[0]=='1') > checked="checked" </#if> -->
    																</td>
    																
    																<td class="hidden-480" id="prezzoPrestazioni_${subEl.id}" style="text-align:right;">
    																	${prezzo}
    																</td>
    																
    																<td class="hidden-480">
    																	<input type="text" size="70" id="gruppo_${subEl.id}" class="gruppo" ${disabled} value="${subEl.getfieldData("DatiPrestazioniFatt","Gruppo")[0]!""}" name="DatiPrestazioniFatt_Gruppo_${subEl.id}" />
    																</td>
    																
    																<td class="hidden-480" align="center">
    																	<input type="radio" name="DatiPrestazioniFatt_AccontoRataSaldo_${subEl.id}" ${disabled} onclick="$(':checkbox[id=\'CheckRimborso_${subEl.id}\']').attr('disabled', false);" value="1" <#if (subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")?size>0 && subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")[0]=='1') > checked="checked" </#if> />
    																</td>
    																
    																<td class="hidden-480" align="center">
    																	<input type="radio" name="DatiPrestazioniFatt_AccontoRataSaldo_${subEl.id}" ${disabled} onclick="$(':checkbox[id=\'CheckRimborso_${subEl.id}\']').attr('checked', false).attr('disabled', true);" value="2" <#if (subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")?size>0 && subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")[0]=='2') > checked="checked" </#if> />
    																</td>
    																
    																<td class="hidden-480" align="center">
    																	<input type="radio" name="DatiPrestazioniFatt_AccontoRataSaldo_${subEl.id}" ${disabled} onclick="$(':checkbox[id=\'CheckRimborso_${subEl.id}\']').attr('checked', false).attr('disabled', true);" value="3" <#if (subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")?size>0 && subEl.getfieldData("DatiPrestazioniFatt","AccontoRataSaldo")[0]=='3') > checked="checked" </#if> />
    																</td>
    																
    																<td class="hidden-480" align="center">
    																	<input type="checkbox" name="DatiPrestazioniFatt_Rimborso" ${disabled} id="CheckRimborso_${subEl.id}" <#if (subEl.getfieldData('DatiPrestazioniFatt','Rimborso')?size>0 && subEl.getfieldData('DatiPrestazioniFatt','Rimborso')[0]=='1') > checked="checked" </#if> />
    																</td>
    															</tr>
            								
    													</#if>
    												</#if>
    											</#list>
    			      	
    											</tbody>
												</table>
											</div>
										</div>
									</div>
									<!-- tabella visite fine-->
   							
   							</div>        
				    		
					      <#--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
						
    					

				    			</div>
	  		 
	  		  </#if>
	  		 		</#list>
	  			</#if>
	 			</#if>		
   		</#list>	 
   		
   		<div class="clearfix"> </div>

    </div> <!-- fine div tabs-0 -->
        		
        		
    <div id="tabs-1">

    	<#assign parentEl=el/>
    	<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	  			<#if docType.typeId="RichiestaFatturazione">
	  				<#--aggiunta condizione per evitare di creare milestone prima della chiusura dello scheduling-->
	  				<#if !activeProcess>
	  					<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Crea nuova richiesta non schedulata">
	  				</#if>
	  			</#if>
    		</#list>
    	</#if>
    	<br><br>
    	<table class="table table-striped table-bordered table-hover">
    	<thead>
			<tr>
				<th>Tipo richiesta</th>
				<th>Causale</th>
				<th>Stato</th>
				<!--th>Importo</th-->
				<th>Data richieste di fattura</th>
				<th>Azioni</th>
			</tr>
		</thead>
    	<#list parentEl.getChildrenByType("RichiestaFatturazione") as subEl>
    		<#assign statoRichFatt="pending">
    		<#assign dataInvio=false>
    		<#if (subEl.getfieldData("DatiRichiestaFatturazioneWF","inviata")[0]?? && subEl.getfieldData("DatiRichiestaFatturazioneWF","inviata")[0]=='1')>	
    			<#assign statoRichFatt="Create le richieste di fattura in data">
    			<#assign dataInvio=true>
    		</#if>
    		<tr>
				<td><#if getDecode("DatiFattura","Tipologia",subEl)=="Acconto">Milestone di fatturazione tempo zero (inizio contratto) <#else>${getDecode("DatiFattura","Tipologia",subEl)}</#if></td>
				<td><#if subEl.getFieldDataDecode("DatiFattura","Causale")?? > ${subEl.getFieldDataDecode("DatiFattura","Causale")} <#else>&nbsp;</#if></td>
				<td>${statoRichFatt}</td>
				<#--td class="toMomey">${subEl.getChildren()[0].getFieldDataString("DatiSchedulingFattura_Prezzo")}</td-->
				<td><#if dataInvio??>${getFieldFormattedDate("DatiRichiestaFatturazioneWF", "dataInvio", subEl)}</#if></td>
				<td>
					<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
						<button onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';" class="btn btn-xs btn-info">
							<i class="icon-edit bigger-120"></i>
						</button>
					</div>
				</td>
			</tr>
    	</#list>
    	</table>
    </div>
        
        
        			<div id="tabs-2">
        			
        			
        			<#assign parentEl=el/>
        				
    							<table class="table table-striped table-bordered table-hover">
					    	<thead>
					    	<tr>
					    		<th>ID fattura</th>
					    		
					    		<th>Importo</th>
					    		<th>Codice Ufficio Ragioneria</th>
					    		<th>Stato</th>
					    		<th>Azioni</th>
					    	</tr>
					    	</thead>
    					<#assign parentEl=el/>
        	
    					<#list parentEl.getChildrenByType("RichiestaFatturazione") as subEl1>
    						<#list subEl1.getChildrenByType("Fattura") as subEl>
    							
    							
    							<#assign invioRagFlag=false />
    							<#assign statoTxt="pending" />
    							<#assign invioEmiFlag=false /> 
    							<#assign statoData="" />
    							<#if subEl.getfieldData("DatiFatturaWF","inviataRagioneria")[0]?? && subEl.getfieldData("DatiFatturaWF","inviataRagioneria")[0]=='1'>
    								<#assign invioRagFlag=true/>
    								<#assign statoData=getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", subEl) /> 
    								<#assign statoTxt="Inviata all'Ufficio Ragioneria in data ${statoData}"/>
    							</#if>
						<#assign invioRagFlag=true />  <#-- lo metto a true per far visualizzare anche se non è stata inviata alla ragioneria -->
    							<#if subEl.getfieldData("DatiFatturaWF","emissioneFattura")[0]?? && subEl.getfieldData("DatiFatturaWF","emissioneFattura")[0]=='1'>
    								<#assign invioEmiFlag=true/> 
    								<#assign statoData=getFieldFormattedDate("DatiFatturaWF", "DataEmissione", subEl) />
    								<#assign statoTxt="Emessa in data ${statoData}"/>
    							</#if>
    							
    							<#list subEl.getChildrenByType("FatturaFeedback") as feed>
							<#assign feedStato="">
							<#if feed?? && feed.getfieldData("DatiFatturaFeedback","Feedback")?? >
								<#assign feedStato=feed.getFieldDataDecode("DatiFatturaFeedback","Feedback") />
    								<#assign feedData=getFieldFormattedDate("DatiFatturaFeedback", "Data", feed) />
							</#if>
    								<#if feedStato!=''><#assign statoTxt="${feedStato} (${feedData})" /></#if>
    							</#list>
    							
    							<#--GC codice alternativo per sapere l'ultimo stato e l'ultima data della fattura-->
    							<#assign lastStato="Pending">
    							<#assign lastData="">
    							<#if subEl.getfieldData("DatiFatturaWF","ultimoStato")?? && subEl.getfieldData("DatiFatturaWF","ultimoStato")?size gt 0>
    								<#assign lastStato=subEl.getfieldData("DatiFatturaWF","ultimoStato")[0] />
    								<#assign lastData='in data ${getFieldFormattedDate("DatiFatturaWF", "ultimaData", subEl)}' />
    							</#if>
    							<#--${lastStato} ${lastData}-->
    							<tr>
    								<td>${subEl.id}</td>
    								
											<td id="importoTotale_${subEl.id}" class="to-money" >${subEl.getfieldData("DatiFatturaWF","realeFattura")[0]!""}</td>
    								<td><#if invioEmiFlag>${subEl.getfieldData("DatiFatturaWF","CodiceFattura")[0]!""}<#else>n.a.</#if></td>
    								<td>${statoTxt}</td>
    								<td><div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
													<button onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';" class="btn btn-xs btn-info" title="visualizza fattura" style="margin-right: 5px">
														<i class="icon-edit bigger-120"></i>
													</button>
													<#if invioRagFlag >
														<button class="btn btn-xs btn-info"  onclick="window.location.href='${baseUrl}/app/documents/pdf/fatturaPDF/${subEl.getId()}';" href="${baseUrl}/app/documents/pdf/fatturaPDF/${subEl.getId()}" title="scarica proforma fattura" style="margin-right: 5px"><i class="fa fa-file-pdf-o  bigger-120"></i></button>
													</#if>
													<#if subEl.getChildrenByType("Ribaltamento")?? && subEl.getChildrenByType("Ribaltamento")?size gt 0 ><#assign ribaltamento=true> <#else><#assign ribaltamento=false></#if>
													<#if ribaltamento>
														<#list subEl.getChildrenByType("Ribaltamento") as subEl1>
															<#if subEl1.id??>
																<#if getUserGroups(userDetails)?starts_with('CTO_') || ( subEl1.getfieldData("DatiRibaltamento","DataRichiesta")[0]?? && subEl1.getfieldData("DatiRibaltamento","DataRichiesta")[0]!="" )>
																	<button class="btn btn-xs btn-info"  href="${baseUrl}/app/documents/detail/${subEl1.id}" onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl1.id}';" title="visualizza riversamento" style="margin-right: 5px"><i class="fa fa-share  bigger-120"></i></button>
																</#if>
															</#if>
														</#list>
													</#if>
												</div>
										</td>
									</tr>
    							
    						</#list>
    					</#list>
        			</table>
        			<#--if model['getCreatableElementTypes']??>
    					<#list model['getCreatableElementTypes'] as docType>
	    				<#if docType.typeId="Fattura">
	    					
	    					
	    	  			<input type="button" class="submitButton round-button blue" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Crea fattura">
	    	  
	    	  		</#if>
    				</#list>
    			</#if-->
        			
        			</div>
        		
    		<#--include "../helpers/child-box.ftl"/-->
        <#include "../helpers/attached-file.ftl"/>
        

    </div>
    <!--#include "../helpers/comments.ftl"/-->
    <!--#include "../helpers/events.ftl"/-->