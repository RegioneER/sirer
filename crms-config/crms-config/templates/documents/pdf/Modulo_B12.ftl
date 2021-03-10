<#ftl encoding="utf-8">
	<#include "../../themes/ace/macros.ftl">
		<#setting number_format="0.##">
			<#assign el=element/>
			<#assign elStudio=element.getParent()/>
			<#assign budgetId=el.getFieldDataString("statoValidazioneCentro","idBudgetApproved") />

			<#assign personeCoinvolte={}   />
			<#assign costiAggiuntivi=[]  />
			<#assign farmacologico=[]   />
			<#assign dispositivo=[]   />
			<#assign beni=[]   />
			<#assign materiali=[]   />
			<#assign attrezzature=[]   />
			<#assign altro=[]   />
			<#assign attivitaServizi={} />


			<#-- VERSIONE E DATA -->
				<#assign versione=0 />
				<#assign uploadDt=0 />
				<#assign data_prot=""/>
				<#list elStudio.getChildrenByType("allegato") as allegato >

					<#if allegato.getFieldDataCode("DocGenerali","DocGen")=="4" >

						<#if (uploadDt==0) > <#-- uploadDt non ancora assegnato -->
							<#assign versione=allegato.file.version />
							<#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
							<#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
							<#elseif (allegato.file.uploadDt.getTimeInMillis() > uploadDt) /> <#-- prendo sempre il documento piu' recente -->
								<#assign versione=allegato.file.version />
								<#assign uploadDt=allegato.file.uploadDt.getTimeInMillis() />
								<#assign data_prot=allegato.file.date.time?date?string("dd/MM/yyyy") />
						</#if>
					</#if>
				</#list>


				<#-- FARMACI DISPOSITIVI E MATERIALI -->
					<#assign farmaci_disp_cat1_list=[] />
					<#assign farmaci_disp_cat2_list=[] />
					<#assign farmaci_disp_cat3_list=[] />
					<#assign materiali_comodato_list=[] />
					<#assign costo_cat1=0 />
					<#assign costo_cat2=0 />
					<#assign costo_cat3=0 />
					<#assign costo_comodato=0 />
					<#list elStudio.getChildrenByType("Farmaco") as farmaco >
						<#if farmaco.getFieldDataCode("Farmaco","tipo")=="1" > <#-- FARMACI -->
							<#if farmaco.getFieldDataCode("Farmaco","categoria")=="1" >
								<#assign farmaci_disp_cat1_list=farmaci_disp_cat1_list+[farmaco] />
								<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore") != "" >
									<#assign costo_cat1=costo_cat1+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
								</#if>
								<#elseif farmaco.getFieldDataCode("Farmaco","categoria")=="2" >
									<#assign farmaci_disp_cat2_list=farmaci_disp_cat2_list+[farmaco] />
									<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore") != "" >
										<#assign costo_cat2=costo_cat2+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
									</#if>
									<#elseif farmaco.getFieldDataCode("Farmaco","categoria")=="3" >
										<#assign farmaci_disp_cat3_list=farmaci_disp_cat3_list+[farmaco] />
										<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
											<#assign costo_cat3=costo_cat3+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
										</#if>
							</#if>
							<#elseif farmaco.getFieldDataCode("Farmaco","tipo")=="2" > <#-- DISPOSITIVI -->
								<#if farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="1" >
									<#assign farmaci_disp_cat1_list=farmaci_disp_cat1_list+[farmaco] />
									<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
										<#assign costo_cat1=costo_cat1+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
									</#if>
									<#elseif farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="2" >
										<#assign farmaci_disp_cat2_list=farmaci_disp_cat2_list+[farmaco] />
										<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
											<#assign costo_cat2=costo_cat2+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
										</#if>
										<#elseif farmaco.getFieldDataCode("Farmaco","categoriaDisp")=="3" >
											<#assign farmaci_disp_cat3_list=farmaci_disp_cat3_list+[farmaco] />
											<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
												<#assign costo_cat3=costo_cat3+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
											</#if>
								</#if>
								<#elseif farmaco.getFieldDataCode("Farmaco","tipo")=="3" > <#-- MATERIALI IN COMODATO -->
									<#assign materiali_comodato_list=materiali_comodato_list+[farmaco] />
									<#if farmaco.getFieldDataString("Farmaco","totaleValore")?? && farmaco.getFieldDataString("Farmaco","totaleValore")!="" >
										<#assign costo_comodato=costo_comodato+farmaco.getFieldDataString("Farmaco","totaleValore")?number />
									</#if>
						</#if>
					</#list>





					<#-- FASE -->
						<#assign fase="" />
						<#if elStudio.getFieldDataCode("datiStudio","tipoStudio")=="1" >
							<#assign fase=elStudio.getFieldDataDecode("datiStudio","fase") />
							<#elseif elStudio.getFieldDataCode("datiStudio","tipoStudio")=="3">
								<#assign fase=elStudio.getFieldDataDecode("datiStudio","faseDisp") />
						</#if>

						<#-- PROMOTORE -->
							<#assign promotore="" />
							<#assign ente_conduzione_studio=""/>
							<#assign referenteLegalePromotore="" />
							<#assign pmPromotore="" />
							<#assign datiPromotoreCRO="" />
							<#assign referenteLegaleCRO="" />
							<#assign pmCRO="" />
							<#if elStudio.getFieldDataElement("datiPromotore","promotore")?? && elStudio.getFieldDataElement("datiPromotore","promotore")[0]?? >
								<#assign promotore=elStudio.getFieldDataElement("datiPromotore","promotore")[0] />
								<#assign ente_conduzione_studio=promotore.getFieldDataString("DatiPromotoreCRO","denominazione") >
									<#assign referenteLegalePromotore=elStudio.getFieldDataString("datiPromotore","RefNomeCognomeL")+ " Tel: " +elStudio.getFieldDataString("datiPromotore","RefTelL")+ " Fax: " +elStudio.getFieldDataString("datiPromotore","RefFaxL")+ " Email: " +elStudio.getFieldDataString("datiPromotore","RefEmailL") />
									<#assign pmPromotore=elStudio.getFieldDataString("datiPromotore","RefNomeCognomePM")+ " Tel: " +elStudio.getFieldDataString("datiPromotore","RefTelPM")+ " Fax: " +elStudio.getFieldDataString("datiPromotore","RefFaxPM")+ " Email: " +elStudio.getFieldDataString("datiPromotore","RefEmailPM") />
									<#assign datiPromotoreCRO=promotore.getFieldDataString("DatiPromotoreCRO","denominazione") >
							</#if>


							<#assign profit=elStudio.getFieldDataCode("datiStudio","Profit")>
								<#if profit=="2" > <#-- NO PROFIT -->
									<#assign finanziato_da_ente=elStudio.getFieldDataCode("datiStudio","fonteFinTerzi")>
										<#assign fonteFin="">
											<#assign fonteFin2="">
												<#if finanziato_da_ente=="1">
													<#assign fonteFin=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec") />
													<#assign fonteFin2=elStudio.getFieldDataDecode("datiStudio","fonteFinSpec2") />
													<#assign ente_conduzione_studio= fonteFin+ " - "+ fonteFin2>
												</#if>
								</#if>


								<#-- CRO -->

									<#if elStudio.getFieldDataElement("datiCRO","denominazione")?? && elStudio.getFieldDataElement("datiCRO","denominazione")[0]?? >
										<#assign cro=elStudio.getFieldDataElement("datiCRO","denominazione")[0] />
										<#assign referenteLegaleCRO=elStudio.getFieldDataString("datiCRO","NomeReferenteL")+ " Tel: " +elStudio.getFieldDataString("datiCRO","telefonoL")+ " Fax: " +elStudio.getFieldDataString("datiCRO","FaxL")+ " Email: " +elStudio.getFieldDataString("datiCRO","emailL") />
										<#assign pmCRO=elStudio.getFieldDataString("datiCRO","NomeReferentePM")+ " Tel: " +elStudio.getFieldDataString("datiCRO","telefonoPM")+ " Fax: " +elStudio.getFieldDataString("datiCRO","FaxPM")+ " Email: " +elStudio.getFieldDataString("datiCRO","emailPM") />
									</#if>

									<#-- PERSONALE -->
										<#assign personale_dipendente=[]/>
										<#assign personale_non_dipendente=[]/>
										<#list el.getChildrenByType("TeamDiStudio") as currTeam >
											<#if currTeam.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="1" >
												<#assign personale_dipendente = personale_dipendente + [ currTeam ] />
												<#else>
													<#assign personale_non_dipendente = personale_non_dipendente + [ currTeam ] />
											</#if>


										</#list>


										<#-- PRESTAZIONI -->



											<#if budgetId?? && budgetId!="" >

												<#list el.getChildrenByType("Budget") as currBudget >
													<#if currBudget.id?string==budgetId >
														<#assign budget=currBudget />
														<#list budget.getChildrenByType("FolderBudgetStudio")[0].getChildren() as currBudgetStudio >
															<#if (currBudgetStudio.getFieldDataString("BudgetCTC","Definitivo")=="1") >
																<#assign budgetStudio=currBudgetStudio/>
															</#if>
														</#list>
													</#if>
												</#list>
												<#assign totalePaziente=budgetStudio.getFieldDataString("BudgetCTC","TotalePazienteCTC")?number />
												<#attempt>

													<#assign numeroPazienti=budgetStudio.getFieldDataString("BudgetCTC","NumeroPazienti")?number />
													<#assign totaleStudio=budgetStudio.getFieldDataString("BudgetCTC","TotaleStudioCTC")?number />
													<#recover>

														<#assign numeroPazienti=0 />
														<#assign totaleStudio=0 />
												</#attempt>
												<#assign targetPaziente="0" />
												<#if budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente")?? && budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente")?string !="" >
													<#assign targetPaziente=budgetStudio.getFieldDataString("BudgetCTC","TargetPaziente") />
												</#if>
												<#assign totaleFlow= (totalePaziente * numeroPazienti)  />
												<#assign sommeAggiuntive=(totaleStudio - totaleFlow)  />
												<#assign rowsFlowchart=[] + budget.getChildrenByType("FolderPrestazioni")[0].getChildren()  />
												<#assign colsFlowchart=[] + budget.getChildrenByType("FolderTimePoint")[0].getChildren()  />
												<#assign prestazioniFlowchart=[] + budget.getChildrenByType("FolderTpxp")[0].getChildren()  />
												<#assign prestazioniCliniche=[] + budget.getChildrenByType("FolderPXP")[0].getChildren()  />
												<#assign prestazioniCTC=[] + budgetStudio.getChildrenByType("FolderPXPCTC")[0].getChildren()  />
												<#assign passthrough=[] + budgetStudio.getChildrenByType("FolderPassthroughCTC")[0].getChildren()  />
												<#assign prestazioni=[] + prestazioniCliniche + prestazioniCTC  />
												<#assign personale=[] + prestazioniFlowchart + prestazioni + passthrough   />
												<#assign personeCoinvolte={}   />
												<#assign costiAggiuntivi=[] + budget.getChildrenByType("FolderCostiAggiuntivi")[0].getChildren()  />
												<#assign farmacologico=[]   />
												<#assign dispositivo=[]   />
												<#assign beni=[]   />
												<#assign materiali=[]   />
												<#assign attrezzature=[]   />
												<#assign altro=[]   />
												<#assign attivitaServizi={} />
												<#assign prestazioniRoutine=[] />
												<#assign totaleRoutine=0 />
												<#assign totaleExtraRoutine=0 />
												<#assign prestazioniExtraRoutine=[] />
												<#assign coperture=["A","B","C","D"] />
												<#assign totaleVisite=0 />
												<#assign totaleCostiAggiuntivi=0 />
												<#list rowsFlowchart as currPrestazione>

													<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumSSNRoutine")?number gt 0 >
														<#assign prestazioniRoutine = prestazioniRoutine + [ currPrestazione ] />
													</#if>


													<#if currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")!='' && currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine")?number gt 0 >
														<#assign prestazioniExtraRoutine = prestazioniExtraRoutine + [ currPrestazione ] />
													</#if>





													<#--assign currServ=currPrestazione.getFieldDataString("Prestazioni","UOC") />
													<#if (currServ?contains("SERV")) >
														<#if attivitaServizi[currServ]?? >
															<#assign attivitaServizi=attivitaServizi+{currServ:attivitaServizi[currServ]+[currPrestazione]} />
															<#else>
																<#assign attivitaServizi=attivitaServizi+{currServ:[]+[currPrestazione]} />
														</#if>
														</#if-->

												</#list>

												<#list personale as persona>
													<#assign currPersona={"Nome":"","Matricola":"","TempoMinTot":0,"Tempo":"0:00"} />
													<#assign currNome=persona.getFieldDataDecode("Costo","Personale")!"" />
													<#assign currMatricola=persona.getFieldDataString("Costo","PersonaleMatricola") />
													<#if (currNome!="") >
														<#if personeCoinvolte[currNome]?? >
															<#assign currPersona=personeCoinvolte[currNome] />
															<#else>
																<#assign currPersona=currPersona+{"Nome":currNome,"Matricola":currMatricola} />

														</#if>
														<#assign currMin=0 />
														<#assign currOre=0 />
														<#assign currMinStr=persona.getFieldDataString("Costo","MinutiUomo") />
														<#assign currOreStr=persona.getFieldDataString("Costo","OreUomo") />
														${currOreStr} giorgio
														<#attempt>
															<#assign currMin=currMinStr?number />
															<#recover>
														</#attempt>
														<#attempt>
															<#assign currOre=currOreStr?number />
															<#assign currMin=(currMin+(currOre*60)) />
															<#recover>
														</#attempt>
														<#assign personaTotMin=currMin+currPersona.TempoMinTot />
														<#assign personaPartOre=(personaTotMin/60)?floor />
														<#assign personaPartMin=personaTotMin-(personaPartOre*60) />
														<#assign personaTempoStr=personaPartOre?string+":" />
														<#if (personaPartMin < 10 ) >
														<#assign personaTempoStr=personaTempoStr+"0" />
													</#if>
													<#assign personaTempoStr=personaTempoStr+personaPartMin />
													<#assign currPersona=currPersona+{"Tempo":personaTempoStr} />


													<#assign personeCoinvolte=personeCoinvolte+{currNome:currPersona} />
											</#if>
											</#list>

											<#list costiAggiuntivi as currCostoAgg >
												<#switch currCostoAgg.getFieldDataCode("CostoAggiuntivo","Tipologia") >
													<#case "1">
														<#assign farmacologico=farmacologico+[currCostoAgg]   />
														<#break>
															<#case "2">
																<#assign dispositivo=dispositivo+[currCostoAgg]   />
																<#break>
																	<#case "3">
																		<#assign beni=beni+[currCostoAgg]   />
																		<#break>
																			<#case "4">
																				<#assign materiali=materiali+[currCostoAgg]   />
																				<#break>
																					<#case "5">
																						<#assign attrezzature=attrezzature+[currCostoAgg]   />
																						<#break>
																							<#default>
																								<#assign altro=altro+[currCostoAgg]   />
												</#switch>
											</#list>
											<#assign varie=beni+materiali+attrezzature+altro   />
											<#else>
												<#assign totalePaziente="0" />
												<#assign numeroPazienti="0" />
												<#assign totaleStudio="0" />
												<#assign sommeAggiuntive="0"  />
												<#assign totaleFlow="0"  />
												</#if>


												<#assign UncheckedCheckbox>
													<img src="images/Unchecked-Checkbox-icon.png" width="10" height="10" />
												</#assign>

												<#assign CheckedCheckbox>
													<img src="images/Checked-Checkbox-icon.png" width="10" height="10" />
												</#assign>

												<#function setCheckbox templateName fieldName fieldVal element>
													<#assign dataVal=getCode(templateName,fieldName,element) />
													<#assign checkImage=UncheckedCheckbox />
													<#if dataVal==fieldVal>
														<#assign checkImage=CheckedCheckbox />
													</#if>
													<#return checkImage />
												</#function>


												<#assign servizioCoinvolto="" />
												<#assign listaServiziCoinvolti="" />
												<#assign x=39>
													<#list 1..x as i>
														<#assign currServ="FeasibilitySERV"+i />
														<#assign currServAtt="SERV"+i />
														<#list el.getChildrenByType(currServ) as elFeasServ>
															<#assign servizioCoinvolto>
																<tr>
																	<td class="txtleft"   style="border: 1px solid black;">${elFeasServ.getTitleString()}</td>
																	<td class="txtcenter" style="border: 1px solid black;">

																		<#if (attivitaServizi[currServAtt]??)>
																			<#list attivitaServizi[currServAtt] as currPrestazione >
																				${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<br/>
																			</#list>
																		</#if>
																		&nbsp;</td>
																	<td class="txtcenter" style="border: 1px solid black;">&nbsp;</td>
																</tr>
															</#assign>
															<#assign listaServiziCoinvolti=listaServiziCoinvolti+servizioCoinvolto />
														</#list>
													</#list>


													<style>

														td{
															padding: 5px;
															text-align:left;
															vertical-align:middle;
														}

														table{
															padding-top:10px;
															padding-bottom:10px;
															vertical-align:middle;
															width:100%;
															font-size: 10px;
															font-family: Tahoma;
															text-align: justify;
														}

														.border1{
															border: 1px solid black;
														}

														.txtcenter{
															text-align:center;
														}

														.txtleft{
															text-align:left;
														}

														.txtright{
															text-align:right;
														}
														ul {
															margin: 0;
														}
														ul.dashed {
															list-style-type: none;
														}
														ul.dashed > li {
															text-indent: -5px;
														}
														ul.dashed > li:before {
															content: "-";
															text-indent: -5px;
															margin-right: 5px;
														}
													</style>

													<!--INIZIO HTML-->
													<!doctype html>
													<html>
													<head>
														<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
														<title>SCHEMA RIASSUNTIVO PER GLI ASPETTI ECONOMICI-AMMINISTRATIVI</title>
													</head>

													<body style="font-size: 12pt; font-family: times new roman, verdana, sans-serif; text-align: justify;">

													<table>
														<tr>
															<td style="width:2%;"></td>
															<td style="width:96%;">

																<!--tutto qui dentro INIZIO-->
																<table>
																	<tr>
																		<td class="txtleft" style="width:30%">
																			<b>Mod. B12</b><br/>Vers_20160118
																		</td>
																		<td>&nbsp;</td>
																		<td class="txtright" style="width:30%">
																			Allegato A
																		</td>
																	</tr>
																	<tr>
																		<td class="txtcenter" colspan="3" style="padding-bottom: 10px; padding-top: 20px;">
																			<b>SCHEMA RIASSUNTIVO PER GLI ASPETTI ECONOMICI-AMMINISTRATIVI<br/>(Budget allegato alla convenzione economica)</b>
																		</td>
																	</tr>
																</table>

																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Titolo Protocollo</b>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			${elStudio.getFieldDataString("IDstudio","TitoloProt")}
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero Eudract</b> <em>(se applicabile)</em>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			${elStudio.getFieldDataString("datiStudio","eudractNumber")}
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Fase dello studio</b> <em>(se applicabile)</em>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			${fase}
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Codice Protocollo</b>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			${elStudio.getFieldDataString("IDstudio","CodiceProt")}
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Versione e data</b>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<#if data_prot!="">
																				v. ${versione}&nbsp;del&nbsp;${data_prot}
																			</#if>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Promotore</b>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<#if promotore?? >
																				<b>${ente_conduzione_studio}</b><br/>
																				<b>Referente Legale:</b> ${referenteLegalePromotore}<br/>
																				<b>Project Manager:</b> ${pmPromotore}
																			</#if>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>CRO</b> <em>(se applicabile)</em>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<#if cro?? >
																				<b>${cro.getFieldDataString("DatiPromotoreCRO","denominazione")}</b><br/>
																				<b>Referente Legale:</b> ${referenteLegaleCRO}<br/>
																				<b>Project Manager:</b> ${pmCRO}
																			</#if>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Sperimentatore Principale</b>
																		</td>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			${el.getFieldDataDecode("IdCentro","PI")}<br/>
																			${el.getFieldDataDecode("IdCentro","Struttura")}<br/>
																			${el.getFieldDataDecode("IdCentro","UO")}<br/>
																			${el.getFieldDataString("IdCentro","emailPI")}<br/>
																			${el.getFieldDataString("IdCentro","telefonoPI")}<br/>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero di pazienti previsti nel centro*</b>
																		</td>
																		<td class="txtleft" style="padding:0;border: 1px solid black; width: 1000px; ">
																			&nbsp;<b>
																			<#if numeroPazienti?? && numeroPazienti?number gt 0>
																				${numeroPazienti}<#else>${el.getFieldDataString("Feasibility","nrPazCentro")}
																			</#if>
																		</b>
																			<!-- &nbsp;Arruolamento competitivo: &nbsp;
                                                                            <#if el.getFieldDataCode("Feasibility","arruolamentoCompetitivo")?? && el.getFieldDataCode("Feasibility","arruolamentoCompetitivo")=="1" >
                                                                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${CheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${UncheckedCheckbox}
                                                                                <#else>
                                                                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SI&nbsp;${UncheckedCheckbox}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NO&nbsp;${CheckedCheckbox}
                                                                            </#if>
                                                                            <br/><span style="color:red"> ARRUOLAMENTO NAZIONALE/INTERNAZIONALE</span> -->
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																			<b>Durata dello studio</b>
																		</td>
																		<td class="txtleft" style="padding:0;border: 1px solid black; width: 1000px; ">
																			&nbsp;&nbsp;${elStudio.getFieldDataString("datiStudio","durataTot")}&nbsp;${elStudio.getFieldDataDecode("datiStudio","durataTotSelect")}
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" colspan="2" style="border: 1px solid black; width: 1000px; ">
																			<b>* Un eventuale aumento del numero di pazienti da arruolare presso il centro sperimentale dell'Ente dovr&agrave; essere preventivamente concordato tra le parti, sentito il parere dello Sperimentatore, e successivamente notificato dallo Sperimentatore al Comitato Etico. Resta inteso che le condizioni economiche per paziente pattuite nella Convenzione si applicheranno a tutti i pazienti aggiuntivi.</b>
																		</td>
																	</tr>
																</table>

																<div style="page-break-before: always">&nbsp;</div>
																<table>
																	<tr>
																		<td class="txtright" style="padding-bottom: 10px; padding-top: 20px;">
																			<b>ASPETTI ECONOMICI</b>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;">
																			<b>Parte 1</b>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>Fornitura del/i Medicinale/i  Sperimentale e/o di ogni altro materiale in sperimentazione o necessario allo svolgimento della stessa affinch&eacute; non vi sia aggravio di costi a carico del S.S.N. (kit diagnostici, dispositivi medici, etc..)</b><br/>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>DETTAGLIO FARMACI O DISPOSITIVI MEDICI SPERIMENTALI</b> (<em>in studio, di confronto, compreso placebo</em>)<br/>
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Unit&agrave; di misura</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore se quantificabile</b><br/>(Euro)
																		</th>

																	</tr>
																	<#if farmaci_disp_cat1_list?? && farmaci_disp_cat1_list?size gt 0 >
																		<#list farmaci_disp_cat1_list as currFarmaco >
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; font-family:monospace;">
																					<#if currFarmaco.getFieldDataString("Farmaco","totaleValore")?? && currFarmaco.getFieldDataString("Farmaco","totaleValore")!= "">
																						&nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
																					</#if>
																				</td>
																			</tr>
																		</#list>
																		<#else>
																			<tr>
																				<td class="txtleft" colspan="5" style="border: 1px solid black; width: 1000px;background-color:#eee; ">
																					&nbsp;NESSUN FARMACO O DISPOSITIVO INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>
																		<td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
																			<b><em>Totale</em></b>
																		</td>
																		<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px; background-color:#eee;font-family:monospace;">
																			<b><em><#if costo_cat1?? >&nbsp;${costo_cat1?string("##0.00")}</#if></em></b>
																		</td>

																	</tr>
																</table>
																<!--div style="page-break-before:always">&nbsp;</div-->
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>DETTAGLIO FARMACI O DISPOSITIVI MEDICI NON OGGETTO DI SPERIMENTAZIONE </b> (<em>previsti  dal protocollo ma non dalla pratica clinica: PeIMP</em>)<br/>
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Unit&agrave; di misura</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore se quantificabile</b><br/>(Euro)
																		</th>

																	</tr>
																	<#if farmaci_disp_cat2_list?? && farmaci_disp_cat2_list?size gt 0 >
																		<#list farmaci_disp_cat2_list as currFarmaco >
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
																					<#if currFarmaco.getFieldDataString("Farmaco","totaleValore")?? && currFarmaco.getFieldDataString("Farmaco","totaleValore")!="" >
																						&nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
																					</#if>
																				</td>
																			</tr>
																		</#list>
																		<#else>
																			<tr>
																				<td class="txtleft" colspan="5" style="border: 1px solid black; width: 1000px;background-color: #eee; ">
																					&nbsp;NESSUN FARMACO O DISPOSITIVO INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>
																		<td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
																			<b><em>Totale</em></b>
																		</td>
																		<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
																			<b><em>&nbsp;${costo_cat2?string("##0.00")}</em></b>
																		</td>

																	</tr>
																</table>
																<!--div style="page-break-before:always">&nbsp;</div>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>DETTAGLIO FARMACI O DISPOSITIVI MEDICI NON OGGETTO DI SPERIMENTAZIONE</b> (<em>previsti dal protocollo e dalla pratica clinica: ReTNIMP</em>)<br/>
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione</b><br/><em>(Indicare dosaggio e forma farmaceutica del farmaco/dettagli del dispositivo)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Unit&agrave; di misura</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore se quantificabile</b><br/>(Euro)
																		</th>

																	</tr>
																	<#list farmaci_disp_cat3_list as currFarmaco >
																		<tr>
																			<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																				&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","princAtt")}${currFarmaco.getFieldDataDecode("Farmaco","dispMed")}&nbsp;-&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
																			</td>
																			<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																				&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
																			</td>
																			<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																				&nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
																			</td>
																			<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																				&nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
																			</td>
																			<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
																				<#attempt>
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
																					<#recover>
																						&nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")}
																				</#attempt>
																			</td>
																		</tr>
																	</#list>
																	<tr>
																		<td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
																			<b><em>Totale</em></b>
																		</td>
																		<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
																			<b><em>&nbsp;${costo_cat3?string("##0.00")}</em></b>
																		</td>

																	</tr>
																</table>
																<div style="page-break-before:always">&nbsp;</div-->
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>DETTAGLIO MATERIALI IN COMODATO D'USO </b><br/>
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter"  style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Costo compreso nel costo della prestazione</b><br/>(Si/No/n.a.)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Unit&agrave; di misura</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Numero unit&agrave; a paziente</b><br/><em>(stima)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore se quantificabile</b><br/>(Euro)
																		</th>

																	</tr>
																	<#if materiali_comodato_list?? && materiali_comodato_list?size gt 0 >
																		<#list materiali_comodato_list as currFarmaco >
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","descrizione")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataDecode("Farmaco","costo")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","unitaMisura")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","numUnitaPaz")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
																					&nbsp;${currFarmaco.getFieldDataString("Farmaco","totaleValore")?number?string("##0.00")}
																				</td>
																			</tr>
																		</#list>
																		<#else>
																			<tr>
																				<td class="txtleft" colspan="5" style="border: 1px solid black; width: 1000px;background-color:#eee; ">
																					&nbsp;NESSUN MATERIALE IN COMODATO D'USO INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>
																		<td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
																			<b><em>Totale</em></b>
																		</td>
																		<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace; background-color:#eee;">
																			<b><em>&nbsp;${costo_comodato?string("##0.00")}</em></b>
																		</td>

																	</tr>
																</table>
																<!--div style="page-break-before:always">&nbsp;</div-->
																<#assign visiteTable>
																	<table cellspacing="0" style="border-collapse: collapse;">
																		<tr style="background-color:#eee;">
																			<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																				<b>Visita</b>
																			</th>
																			<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																				<b>Compenso/paziente</b>
																			</th>
																		</tr>
																		<#if colsFlowchart??>
																			<#list colsFlowchart as currTimePoint>
																				<tr>
																					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																						Visita ${currTimePoint.getFieldDataString("TimePoint","NumeroVisita")}
																					</td>
																					<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
																						<#if currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")!=''>
																							<#assign totaleVisite=totaleVisite + currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")?number />
																							&euro;&nbsp;${currTimePoint.getFieldDataString("InfoBudgetPDF","TotPrezzoExtraRoutine")?number?string("##0.00")} + iva
																							<#else>
																								<#assign totaleVisite=totaleVisite/>
																						</#if>
																					</td>
																				</tr>
																			</#list>
																			<#else>
																				<tr>
																					<td class="txtleft" colspan="2" style="border: 1px solid black; width: 1000px;background-color: #eee; ">
																						&nbsp;NESSUNA VISITA INSERITA
																					</td>
																				</tr>
																		</#if>
																		<tr>
																			<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																				<b>TOTALE</b>
																			</td>
																			<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px;font-family:monospace;">
																				<b><#if totaleVisite??>&euro; ${totaleVisite?number?string("##0.00")} + iva</#if></b>
																			</td>
																		</tr>
																	</table>
																</#assign>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="width:100%; padding:4px;width:100%;">
																			<br/><br/>
																			<b>Compenso per il Centro sperimentale a paziente completato:</b>
																			&nbsp;<#if totaleVisite??> &euro;${totaleVisite?number?string("##0.00")}+ iva</#if>
																			<br/>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="width:100%; padding:4px;width:100%;">
																			<br/><br/>
																			<b>Fasi economiche intermedie:</b><br/>
																			<em>Nel caso in cui i pazienti non completino l'iter sperimentale:</em><br/>
																		</td>
																	</tr>
																</table>
																${visiteTable}
																<div style="page-break-before:always">&nbsp;</div>
																<table>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 10px;">
																			<b>Parte 2</b>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 10px;">
																			<b><em>Dettaglio dei costi aggiuntivi per esami strumentali e/o di laboratorio da effettuarsi sulla base del Tariffario</em></b><br/>
																			<em>(gli importi indicati relativi alle prestazioni potranno subire aggiornamenti e revisioni a seguito di atti/disposizioni adottati dalla Regione e che trovano applicazione dalla data di decorrenza dagli stessi atti): </em>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Codice tariffario e descrizione della prestazione </b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Quantit&agrave;/paziente</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale prestazioni previste</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Tariffa</b><br/>
																			(Nomenclatore Regionale)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore + IVA</b><br/>(Euro)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Copertura oneri finanziari</b><br/>(A, B, C, D)
																		</th>
																	</tr>
																	<#if prestazioniExtraRoutine?? && prestazioniExtraRoutine?size gt 0 && prestazioni?? && prestazioni?size gt 0 >
																		<#if prestazioniExtraRoutine?? && prestazioniExtraRoutine?size gt 0 >
																			<#list prestazioniExtraRoutine as currPrestazione >
																				<#list coperture as currCopertura >
																					<#assign conteggioCorrente=currPrestazione.getFieldDataString("InfoBudgetPDF","NumExtraRoutine"+currCopertura) />
																					<#if conteggioCorrente?? && conteggioCorrente!="0" && conteggioCorrente!="" >
																						<tr>
																							<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																								&nbsp;${currPrestazione.getFieldDataString("Prestazioni","prestazione")}<#if currPrestazione.getFieldDataString("Prestazioni","prestazione")?length == 100>...</#if>
																							</td>
																							<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																								&nbsp;${conteggioCorrente}
																							</td>
																							<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																								<#assign per_paziente= conteggioCorrente?number * numeroPazienti/>
																								&nbsp;${per_paziente}
																							</td>
																							<td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
																								<#if currPrestazione.getFieldDataString("Tariffario","SSN")?? && currPrestazione.getFieldDataString("Tariffario","SSN")!="" >
																									&euro;&nbsp;${currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number?string("##0.00")}
																									<#else>
																										&euro;&nbsp;
																								</#if>
																							</td>
																							<td class="txtright" style="border: 1px solid black; width: 1000px;font-family: monospace; ">
																								<#attempt>
																									<#assign tariffario=currPrestazione.getFieldDataString("InfoBudgetPDF","TotCostoExtraRoutine"+currCopertura)?number />
																									<#recover>
																										<#assign tariffario=0>
																								</#attempt>

																								<#if currPrestazione.getFieldDataString("Tariffario","SSN")?? && currPrestazione.getFieldDataString("Tariffario","SSN")!="" >
																									<#assign tariffario=currPrestazione.getFieldDataString("Tariffario","SSN")?replace(',','.')?number />
																								</#if>
																								<#assign tariffa= numeroPazienti?number * tariffario  />
																								<#assign totaleExtraRoutine= totaleExtraRoutine + tariffa />
																								&euro;&nbsp;${tariffa?string("##0.00")}
																							</td>
																							<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																								&nbsp;${currCopertura?replace("NumExtraRoutine","")}
																							</td>
																						</tr>
																					</#if>
																				</#list>
																			</#list>
																		</#if>
																		<#if prestazioni??>
																			<#list prestazioni as currPrestazione >
																				<tr>
																					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																						&nbsp;${currPrestazione.getFieldDataString("Base","Nome")}<#if currPrestazione.getFieldDataString("Base","Nome")?length == 100>...</#if>
																					</td>
																					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																						&nbsp;${currPrestazione.getFieldDataString("Costo","Quantita")}
																					</td>
																					<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																						<#assign prestazioneTotale="0" />
																						<#assign prestazioneTotaleNA="0" />
																						<#if currPrestazione.getFieldDataString("Costo","Quantita")?? && currPrestazione.getFieldDataString("Costo","Quantita") != "" >
																							<#assign prestazioneTotale= currPrestazione.getFieldDataString("Costo","Quantita")?number * numeroPazienti/>
																							<#elseif currPrestazione.getFieldDataString("Costo","QuantitaNA")=="1">
																								<#assign prestazioneTotaleNA="1" />
																						</#if>
																						&nbsp;${prestazioneTotale}
																					</td>
																					<td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
																						<#assign costoUnitario=0 />
																						<#if currPrestazione.getFieldDataString("Tariffario","SSN")?? &&  currPrestazione.getFieldDataString("Tariffario","SSN") != "" >
																							<#assign costoUnitario=currPrestazione.getFieldDataString("Tariffario","SSN")?replace(",",".")?number />
																						</#if>
																						&euro;&nbsp;${costoUnitario?string("##0.00")}
																					</td>
																					<td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
																						<#if costoUnitario== 0 && currPrestazione.getFieldDataString("Costo","TransferPrice") != "" >
																							<#assign costoUnitario=currPrestazione.getFieldDataString("Costo","TransferPrice")?replace(",",".")?number />
																							<#elseif costoUnitario== 0 && currPrestazione.getFieldDataString("Costo","Costo") != "" >
																								<#assign costoUnitario=currPrestazione.getFieldDataString("Costo","Costo")?replace(",",".")?number />
																						</#if>
																						<#if prestazioneTotaleNA=="1">
																							<#assign costoTotale=costoUnitario/>
																							<#else>
																								<#assign costoTotale=prestazioneTotale?number*costoUnitario/>
																						</#if>

																						<#assign totaleExtraRoutine=totaleExtraRoutine + costoTotale />
																						&nbsp;${costoTotale?string("##0.00")}
																					</td>
																					<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																						&nbsp;${currPrestazione.getFieldDataDecode("Costo","Copertura")?string[0..0]}
																					</td>
																				</tr>
																			</#list>
																		</#if>
																		<#else>
																			<tr>
																				<td class="txtleft" colspan="6" style="border: 1px solid black; width: 1000px; background-color: #eee;">
																					&nbsp;NESSUN COSTO AGGIUNTIVO INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>
																		<td class="txtleft" colspan="4" style="border: 1px solid black; width: 1000px; ">
																			<b><em>TOTALE</em></b>
																		</td>
																		<td class="txtright" colspan="1" style="border: 1px solid black; width: 1000px; background-color:#eee;font-family: monospace;">
																			<b><#if totaleExtraRoutine??>&euro;&nbsp;${totaleExtraRoutine?string("##0.00")}</#if></b>
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; border: 1px solid black;width: 2000px;">
																			<b>A</b> = fondi della struttura sanitaria a disposizione dello Sperimentatore/Promotore <br/>
																			<b>B</b> = finanziamento proveniente da terzi, da dettagliare nella Sezione B<br/>
																			<b>C</b> = il costo di tali prestazioni si propone in carico al fondo aziendale non alimentato dal SSN, in dotazione all'Azienda Sanitaria <br/>
																			<b>D</b> = a carico del Promotore Profit
																		</td>
																	</tr>
																</table>
																<!-- div style="page-break-before:always">&nbsp;</div-->
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;"><br/>
																			<b>MATERIALI DI CONSUMO, ATTREZZATURE, SERVIZI E SPESE PER IL PERSONALE NECESSARI PER LO SVOLGIMENTO DELLO STUDIO</b><br/>
																			<span style="text-align: justify">
																			<em>Elencare ed indicare la quantit&agrave; e le modalit&agrave; proposte per la copertura del costo dei materiali/attrezzature/servizi studio-specifici, <b>non rientranti nel costo delle prestazioni</b>, come da codici indicati di seguito:</em>
																			</span>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter" colspan="2" style="border: 1px solid black; width: 1000px; ">
																			<b>Tipologia</b><br/><em>(1=materiale di consumo; 2=attrezzature; 3=servizi*; 4=personale**; 5=altro***)</em>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Quantit&agrave;</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore + IVA</b><br/>(Euro)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Copertura oneri finanziari</b><br/>(A, B, C, D)
																		</th>
																	</tr>
																	<tr>
																		<td class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>CODICE</b>
																		</td>
																		<td class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione</b>
																		</td>
																		<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																			&nbsp;
																		</td>
																		<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																			&nbsp;
																		</td>
																		<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																			&nbsp;
																		</td>
																	</tr>
																	<#if costiAggiuntivi?? && costiAggiuntivi?size gt 0 >
																		<#list costiAggiuntivi as currCosto>
																			<tr>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currCosto.getFieldDataCode("CostoAggiuntivo","Tipologia")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currCosto.getFieldDataString("CostoAggiuntivo","OggettoPrincipale")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currCosto.getFieldDataString("CostoAggiuntivo","Quantita")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace; ">
																					<#assign currTotale=0 />
																					<#if currCosto.getFieldDataString("CostoAggiuntivo","Costo")?? && currCosto.getFieldDataString("CostoAggiuntivo","Costo")!="" && currCosto.getFieldDataString("CostoAggiuntivo","Quantita")?? && currCosto.getFieldDataString("CostoAggiuntivo","Quantita")!="" >
																						<#assign currTotale=currCosto.getFieldDataString("CostoAggiuntivo","Quantita")?number * currCosto.getFieldDataString("CostoAggiuntivo","Costo")?number />
																					</#if>
																					<#assign totaleCostiAggiuntivi= totaleCostiAggiuntivi + currTotale />
																					&nbsp;${currTotale?string("##0.00")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currCosto.getFieldDataDecode("CostoAggiuntivo","Copertura")?string[0..0]}
																				</td>
																			</tr>
																		</#list>
																		<#else>
																			<tr>
																				<td class="txtcenter" colspan="5" style="border: 1px solid black; width: 1000px; background-color: #eee;">
																					&nbsp;NESSUN MATERIALE DI CONSUMO, ATTREZZATURA, SERVIZIO E/O SPESA PER IL PERSONALE INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>
																		<td class="txtright" colspan="3" style="border: 1px solid black; width: 1000px; ">
																			<b><em>Totale</em></b>
																		</td>
																		<td class="txtright" style="border: 1px solid black; width: 1000px;font-family:monospace;background-color:#eee;">
																			<b><em><#if totaleCostiAggiuntivi??>&nbsp;${totaleCostiAggiuntivi?string("##0.00")}</#if></em></b>
																		</td>
																		<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																			&nbsp;
																		</td>
																	</tr>
																</table>
																<br/>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px;"><br/>
																			<em>
																				*   Nella voce servizi devono essere inseriti e quantificati (stima) anche l'organizzazione o la partecipazione a convegni, corsi di formazione o altre iniziative formative.<br/>
																				**  Nella voce personale specificare descrivendo distintamente i costi relativi alle spese per il personale dipendente, quello non dipendente in forza allo studio mediante convenzioni o contratti o distacchi da altre pubbliche amministrazioni, per l'attivazione di borse di studio.<br />
																				*** Per altro si intende tutto ci&ograve; che non pu&ograve; essere ricompreso nelle specifiche precedenti, come somministrazione di questionari, interviste, diari, scale di valutazione etc.<br />
																			</em>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; border: 1px solid black;">
																			<b>A</b> = fondi della struttura sanitaria a disposizione dello Sperimentatore/Promotore <br/>
																			<b>B</b> = finanziamento proveniente da terzi, da dettagliare nella Sezione B<br/>
																			<b>C</b> = il costo di tali prestazioni si propone in carico al fondo aziendale non alimentato dal SSN, in dotazione all'Azienda Sanitaria <br/>
																			<b>D</b> = a carico del Promotore Profit
																		</td>
																	</tr>
																</table>
																<table>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;text-align: justify">
																			<b><u>Rimborsi spese per i pazienti/accompagnatori arruolati nello studio clinico: </u></b>(<em>Se applicabile</em>)
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 10px; padding-top: 20px;text-align: justify">
																			Il paziente dovr&agrave; conservare i giustificativi (biglietti di viaggio/ricevute/fatture) o, quando applicabile, farsi rilasciare una ricevuta/fattura. Il paziente consegner&agrave; la documentazione di cui al punto precedente, in originale, allo Sperimentatore Principale, comprensiva di nota riepilogativa e coordinate bancarie del paziente. Lo Sperimentatore Principale attestata la regolarit&agrave; della documentazione presentata dal paziente trasmette la stessa alla U.O.<br/>
																			<br/>&nbsp;__________________________________________________________________________________________________________________________<br/>
																			Al ricevimento di tutta la documentazione, l'Azienda provveder&agrave; all'emissione della relativa fattura al Promotore, addebitando quanto desunto dai giustificativi di spesa che verranno altres&igrave; allegati alla stessa.<br/>
																			Solo al momento dell'incasso della suddetta fattura, l'Azienda potr&agrave; procedere con il relativo rimborso in favore del paziente/accompagnatore, che potr&agrave; avvenire mediante accredito sul conto corrente o altra modalit&agrave; che il paziente riterr&agrave; idonea.<br/>
																			<em>(Elenco tipologia di rimborso spese di viaggio/pernottamento dietro presentazione di giustificativi).</em>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr style="background-color:#eee;">
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Descrizione </b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Quantit&agrave;/paziente</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale prestazioni previste</b>
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Costo</b><br/>

																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Totale valore + IVA</b><br/>(Euro)
																		</th>
																		<th class="txtcenter" style="border: 1px solid black; width: 1000px; ">
																			<b>Copertura oneri finanziari</b><br/>(A, B, C, D)
																		</th>
																	</tr>
																	<#if passthrough?? && passthrough?size gt 0 >
																		<#list passthrough as currPrestazione >
																			<tr>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currPrestazione.getFieldDataString("Base","Nome")}<#if currPrestazione.getFieldDataString("Base","Nome")?length == 100>...</#if>
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currPrestazione.getFieldDataString("Costo","Quantita")}
																				</td>
																				<td class="txtleft" style="border: 1px solid black; width: 1000px; ">
																					<#assign prestazioneTotale= currPrestazione.getFieldDataString("Costo","Quantita")?number * numeroPazienti />
																					&nbsp;${prestazioneTotale}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
																					<#assign costoUnitario=0 />
																					<#if currPrestazione.getFieldDataString("Costo","Costo")?? &&  currPrestazione.getFieldDataString("Costo","Costo") != "" >
																						<#assign costoUnitario=currPrestazione.getFieldDataString("Costo","Costo")?replace(",",".")?number />
																					</#if>
																					&euro;&nbsp;${costoUnitario?string("##0.00")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; font-family: monospace;">
																					<#assign costoTotale=prestazioneTotale*costoUnitario/>
																					<#assign totaleExtraRoutine=totaleExtraRoutine + costoTotale />
																					&euro;&nbsp;${costoTotale?string("##0.00")}
																				</td>
																				<td class="txtright" style="border: 1px solid black; width: 1000px; ">
																					&nbsp;${currPrestazione.getFieldDataDecode("Costo","Copertura")?string[0..0]}
																				</td>
																			</tr>
																		</#list>
																		<#else>
																			<tr>
																				<td class="txtleft" colspan="6" style="border: 1px solid black; width: 1000px; background-color: #eee;">
																					&nbsp;NESSUN RIMBORSO INSERITO
																				</td>
																			</tr>
																	</#if>
																	<tr>

																	</tr>

																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="text-align: justify">
																			<br/><br/>
																			<b>Lo studio non comporter&agrave; aggravio di costi a carico del SSN</b>
																		</td>
																	</tr>
																	<tr>
																		<td class="txtleft" style="padding-bottom: 5px; padding-top: 10px;"><br/>
																			<u><b>Copertura assicurativa:</b></u><br/>
																		</td>
																	</tr>
																</table>
																<table cellspacing="0" style="border-collapse: collapse;">
																	<tr>
																		<td class="txtleft" style="width:100%; padding:4px;">
																			<#if el.getFieldDataCode("Feasibility","CopAss")?? && el.getFieldDataCode("Feasibility","CopAss")=="1" >
																				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PREVISTA&nbsp;${CheckedCheckbox}
																				&nbsp;<b>nr. polizza:</b>&nbsp;<#if el.getFieldDataCode("Feasibility","CopAssNrPolizza")??>${el.getFieldDataString("Feasibility","CopAssNrPolizza")}</#if>
																				&nbsp;<b>importo del premio:</b>&nbsp; <#if el.getFieldDataCode("Feasibility","CopAssPrezzo")?? && el.getFieldDataCode("Feasibility","CopAssPrezzo")!= "">&euro;${el.getFieldDataString("Feasibility","CopAssPrezzo")?number?string("##0.00")}</#if>
																				<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NON PREVISTA&nbsp;${UncheckedCheckbox}
																				<#else>
																					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PREVISTA&nbsp;${UncheckedCheckbox}
																					<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NON PREVISTA&nbsp;${CheckedCheckbox}
																			</#if>
																		</td>
																	</tr>
																</table>
																<!--tutto qui dentro FINE-->
															</td>
														</tr>
													</table>
													</body>
													</html>
