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
    
    .vs {
        float: left;
    width: 50%;
        height: 150px;
    }

    .vs label {
        width: 30%;
    }

    .re {
        float: left;
    width: 40%;
        height: 150px;
    }

    .re label {
        width: 55%;
    }

    .ri {
        float: left;
    width: 80%;
    }

    .ri label {
        width: 55%;
    }

    .vl {
        float: left;
    width: 45%;
    }

    .vl label {
        width: 55%;
    }

    .ui-autocomplete.ui-menu {
        z-index: 9999 !important;
    }

    .view-mode label {
    background-color: #FFFFFF;
    font-weight: normal !important;
    margin: 0;
    padding: 0.25em 0.5em;
    width: 15em;
    }

    .list-table a:hover {
    color: #000000;
    text-decoration: none;
    }

    .list-table a:visited {
    color: #000000;
    text-decoration: none;
    }

    .list-table a {
    color: #000000;
    text-decoration: none;
    }

    .home-fieldset {
    background-color: #DFEFFC;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    margin-bottom: 20px;
    padding: 5px;
    width: 90%;
    }

    .home-legend {
    background-color: #4084CA;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    color: #FFFFFF;
    padding: 5px;
    }

    .highlightRow {
    color: #438DD7 !important;
    font-weight: bold;
    }

    .list-table {
    }

    .list-table th {
    background-color: #FFFFFF;
    border-bottom: 1px solid #4D80B4;
    border-left: 1px ridge #4D80B4;
    color: #5D8DBE;
    font-size: 12px;
    font-weight: bold;
    text-align: left;
    }

    .list-table td {
    font-size: 12px;
    padding-left: 2px;
    padding-right: 2px;
    text-align: left;
    }

    .list-table tr:nth-child(2n+1) td {
    background-color: #F0FFFF;
    }

    .list-table tr:nth-child(2n) td {
    background-color: #F5FFFA;
    }

    .done {
        background-color: lightgreen;
        border-radius: 5px;
        padding: 2px;
        vertical-align: middle;
    }

    .pending {
        background-color: #F98F1D;
        border-radius: 5px;
        padding: 2px;
    }

</style>

<div class="row">
   		<div class="col-xs-9">

        <#include "../helpers/MetadataTemplate.ftl"/>

	<div style="display: block">

            <#if el.getChildrenByType("Ribaltamento")?? && el.getChildrenByType("Ribaltamento")?size gt 0 >
                <#assign ribaltamento=true>
                    <#else>
                        <#assign ribaltamento=false>
            </#if>
            <#assign activeProcess=false/>
            <#assign feedback=false/>

            <#if el.getfieldData("DatiFatturaWF","emissioneFattura")[0]?? && el.getfieldData("DatiFatturaWF","emissioneFattura")[0]!="">
    						 		<#assign feedback=true/>	
            </#if>

    					 		<#if model["activeProcesses"]??>
    					    <#list model["activeProcesses"] as ist>

    					    <#assign activeProcess=true/>
    					    </#list>
    					 </#if>
            <br/>
       
			 	<#assign Feed=false/>
			
    							
				<#list el.getChildrenByType("FatturaFeedback") as subEl>
					<#assign feedback=true />
                <#if subEl.id?? && subEl.getfieldData("DatiFatturaFeedback","Feedback")?? >
    					
                    <#assign statoFatt=subEl.getFieldDataCode("DatiFatturaFeedback","Feedback")/>
    					
                    <#if statoFatt=="1">
    						<#assign Feed=true/>
    				  </#if>
						</#if>
    			</#list>	
    	
            <#assign riduzione=false />
            <#list el.getChildrenByType("RiduzioneFattura") as subEl>
                <#if subEl.id??>
                    <#assign riduzione=true />
                </#if>
            </#list>
            <#assign riduzionePossibile=true />
            <#assign riduzioneNoPossibileMessaggio="" />
            <#if el.getfieldData("DatiFatturaWF","realeFattura")[0]?? && el.getfieldData("DatiFatturaWF","realeFattura")[0]=="0">
                <#assign riduzionePossibile=false/> <#--  -->
                <#assign riduzioneNoPossibileMessaggio="Impossibile inserire la riduzione: importo reale fattura pari a 0.00 €" />
            </#if>
            <#if el.getfieldData("DatiFatturaWF","inviataRagioneria")[0]?? && el.getfieldData("DatiFatturaWF","inviataRagioneria")[0]=="1">
                <#assign riduzionePossibile=false/> <#--  -->
                <#assign riduzioneNoPossibileMessaggio="Impossibile inserire la riduzione: fattura già inviata ad Ufficio Ragioneria" />
            </#if>
            <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=="3">
                <#assign riduzionePossibile=false/> <#-- -->
                <#assign riduzioneNoPossibileMessaggio="Impossibile inserire la riduzione per una fattura di saldo " />
            </#if>
            <div id="task-Actions" style="margin-bottom:10px;text-align:right;"></div>
            <div  style="margin-bottom:10px;text-align:right;">
                <#if model['getCreatableElementTypes']??>
                    <#list model['getCreatableElementTypes'] as docType>
		     	        <#if docType.typeId="FatturaFeedback" && feedback==true && Feed==false>
						
                            <button class="btn btn-primary"
                                    onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';">
                                Inserisci feedback fattura
                            </button>
			 			
		     	        </#if>
                        <#-- if docType.typeId="RiduzioneFattura" && riduzione==false >
                            <#if riduzionePossibile == true >
                                <button class="btn btn-primary"
                                        onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';">
                                    Inserisci Riduzione Fattura
                                </button>
                            <#else>
                                <button class="btn btn-primary"
                                        onclick="alert('${riduzioneNoPossibileMessaggio}');">
                                    Inserisci Riduzione Fattura
                                </button>

                            </#if>
                        </#if -->
                    </#list>
                </#if>
                <#if riduzione>
                    <#list el.getChildrenByType("RiduzioneFattura") as subEl>

                        <#if subEl.id??>
                                <button class="btn btn-primary" href="${baseUrl}/app/documents/detail/${subEl.id}"
                                        onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
                                    Visualizza Riduzione Fattura
                                </button>
                        </#if>
    				</#list>
                </#if>
                <#if ribaltamento>
     	 		    <#list el.getChildrenByType("Ribaltamento") as subEl>
	                    <#if subEl.id??>
                            <#if getUserGroups(userDetails)?starts_with('CTO_') || ( subEl.getfieldData("DatiRibaltamento","DataRichiesta")[0]?? && subEl.getfieldData("DatiRibaltamento","DataRichiesta")[0]!="" )>
                                <button class="btn btn-primary" href="${baseUrl}/app/documents/detail/${subEl.id}"
                                        onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
                                    Riversamento
                                </button>
                            </#if>
            			</#if>
		            </#list>
            	</#if>
            </div>
             <div class="row">
                 <div class="col-xs-12">
                            <div class="table-header"> Intestatario Fattura</div>
                        <div class="table-responsive">
                        <table id="sample-table-1" class="table table-striped table-bordered table-hover">
                                <thead>
                                    <tr>
                                        <th style="text-align:left;width:33%">Spett.le</th>
                                        <th style="text-align:center;width:33%">P.IVA / Codice Fiscale</th>
                                        <th style="text-align:right;width:33%">Indirizzo completo</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    <#assign intestatario="">
                                    <#assign piva="">
                                    <#assign indirizzo="">
                                    <#if el.getfieldData("DatiFatturaScheduling","DestinatarioRagSoc")[0]??>
                                        <#assign intestatario=el.getfieldData("DatiFatturaScheduling","DestinatarioRagSoc")[0] />

                                    </#if>
                                    <#if el.getfieldData("DatiFatturaScheduling","DestinatarioPIVA")[0]??>
                                        <#assign piva=el.getfieldData("DatiFatturaScheduling","DestinatarioPIVA")[0] />
                                    </#if>
                                    <#if el.getfieldData("DatiFatturaScheduling","DestinatarioIndirizzo")[0]??>
                                        <#assign indirizzo=el.getfieldData("DatiFatturaScheduling","DestinatarioIndirizzo")[0]/>
                                    </#if>
                                <tr>
                                    <td style="text-align:left;">${intestatario}</td>
                                    <td style="text-align:left;">${piva}</td>
                                    <td style="text-align:left;">${indirizzo}</td>
                                </tr>
                            </tbody>
                            </table>
                        </div>
                    </div>
             </div>
            <div class="row">
                <div class="col-xs-12">
                    <div class="table-header"> Indirizzo Fatturazione</div>
                    <div class="table-responsive">
                        <table id="sample-table-1" class="table table-striped table-bordered table-hover">
                            <thead>
                            <tr>
                                <th style="text-align:left;width:33%">Spett.le</th>
                                <th style="text-align:center;width:33%">P.IVA / Codice Fiscale</th>
                                <th style="text-align:right;width:33%">Indirizzo completo</th>
                            </tr>
                            </thead>
                            <tbody>
                            <#assign intestatario="">
                                <#assign piva="">
                                    <#assign indirizzo="">
                                        <#if el.getfieldData("DatiFatturaScheduling","FatturazioneRagSoc")[0]??>
                                            <#assign intestatario=el.getfieldData("DatiFatturaScheduling","FatturazioneRagSoc")[0] />

                                        </#if>
                                        <#if el.getfieldData("DatiFatturaScheduling","FatturazionePIVA")[0]??>
                                            <#assign piva=el.getfieldData("DatiFatturaScheduling","FatturazionePIVA")[0] />
                                        </#if>
                                        <#if el.getfieldData("DatiFatturaScheduling","FatturazioneIndirizzo")[0]??>
                                            <#assign indirizzo=el.getfieldData("DatiFatturaScheduling","FatturazioneIndirizzo")[0]/>
                                        </#if>
                                        <tr>
                                            <td style="text-align:left;">${intestatario}</td>
                                            <td style="text-align:left;">${piva}</td>
                                            <td style="text-align:left;">${indirizzo}</td>
                                        </tr>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
      <#assign parentEl=el/>
	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='1'> 
	    	<!--tabella Milestone di fatturazione tempo zero inizio-->
    		<div class="row">
                <div class="col-xs-12">
                    <div class="table-header"> Milestone di fatturazione tempo zero (inizio contratto)</div>
                    <div class="table-responsive">
                    <table id="sample-table-1" class="table table-striped table-bordered table-hover">
                            <thead>
                                <tr>
                                <th style="text-align:left;width:60%">Descrizione</th>
                                <th style="text-align:center;width:11%">Rimborsabile</th>
                                <th style="text-align:right;width:7%">Totale</th>
                            </tr>
                        </thead>
                            <tbody>
                                <#assign prezzoAcc="">
                                <#assign startUp="">
                                <#if el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0]??>
                                    <#assign prezzoAcc=el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0] />
                                    <#assign startUp="Anticipo sui pazienti" />
                                </#if>
                                <#assign rimbo="">
                                <#if el.getfieldData("DatiFatturaScheduling","StartUpRimborsabile")[0]??>
                                    <#assign rimbo=getDecode("DatiFatturaScheduling","StartUpRimborsabile",el)/>
                                </#if>
                            <tr>
                                <td style="text-align:left;">${startUp}</td>
                                <td id="totale6_${el.id}" style="text-align:center;">${rimbo}</td>
                                <td id="totale5_${el.id}" style="text-align:right;">${prezzoAcc}</td>
                            </tr>
                        </tbody>
                        </table>
                    </div>
                </div>
            </div>
			<!--tabella Milestone di fatturazione tempo zero fine-->
	    </#if>
	    
	    
	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='2' || el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='3'>
	        <!--fieldset>
	   	        <div class="table-header"> Prestazioni cliniche da protocollo</div>
	            <table  class=" table table-striped table-bordered table-hover" style="width:100%">
	                <thead>
	    	            <tr>
                            <th style="text-align:left;width:60%">Descrizione</th>
                            <th style="text-align:left;width:5%">Tipologia attivit&agrave;</th>
                            <th style="text-align:left;width:5%">Codice tariffario</th>
                            <th style="text-align:left;width:5%">Tariffa SSR</th>
                            <th style="text-align:left;width:5%">Transfer price</th>
                            <!--th style="text-align:center;width:5%">Numero Pazienti</th -- >
                            <th style="text-align:center;width:5%">Prestazioni Erogate</th>
                            <th style="text-align:right;width:7%">Totale</th>
                            <th style="text-align:center;width:11%">Visualizza dettaglio</th>
	    	            </tr>
	    	        </thead>
	    	        <tbody>
	    		    <#assign parentEl=el/>
	                <#list parentEl.getChildrenByType("LinkVoceMonitoraggioFattura") as subEl1>
	    	            <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	    	    	<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='1'>
                        <tr>
                            <td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
                            <td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","AttivitaDecode")[0]!""}</td>
                            <td style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Codice")!""}</td>
                            <td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","SSN")!""}</td>
                            <td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!""}</td>
                            <!--td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td -- >
                            <td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
                            <td id="totale1_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiMonitoraggioFattura","Totale")[0]!""}</td>
                            <td style="text-align:center;">
                                        <#if (subEl.getChildren()?? && subEl.getChildren()?size gt 0)>
                                            <a href='${subEl.getId()}'><img width="20" height="20" src="/img/details.png"></img></a>
                                        <#else>
                                            n.a.
                                        </#if>
                            </td>
                        </tr>
	    	                </#if>
            	    </#list>
	                </tbody>
	            </table>
	        </fieldset>
	        <br/-->
            <#assign vociMonitoraggio=parentEl.getChildrenByType("LinkVoceMonitoraggioFattura") />
            <#if (vociMonitoraggio?? && vociMonitoraggio?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
            <fieldset>
                <div class="table-header">Prestazioni/Attività aggiuntive</div>
	            <table class="table table-striped table-bordered table-hover" style="width:100%">
	                <thead>
	    	            <tr>
	    		            <th style="text-align:left;width:60%">Descrizione</th>
	    		            <th style="text-align:left;width:5%">Tipologia attivit&agrave;</th>
			                <th style="text-align:left;width:5%">Codice tariffario</th>
			                <th style="text-align:left;width:5%">Tariffa SSR</th>
			                <th style="text-align:left;width:5%">Transfer price</th>
                            <!--th style="text-align:center;width:10%">Numero Pazienti</th-->
                            <th style="text-align:center;width:10%">Prestazioni Erogate</th>
                            <th style="text-align:right;width:7%">Totale</th>

	    	            </tr>
	                </thead>
	                <tbody>
            	    <#list vociMonitoraggio as subEl1>
	    	            <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	            <#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='2'>
                	    	<tr>
                                <td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
                                <td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","AttivitaDecode")[0]!""}</td>
                                <td style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Codice")!""}</td>
                                <td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","SSN")!""}</td>
                                <td class="to-money" style="text-align:left;">
                                        <#if subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!=""  >
                                            ${subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!""}
                                            <#else>n.a.
                                        </#if>
                                </td>
                                <!--td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td-->
                                <td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
                                <td id="totale2_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiMonitoraggioFattura","Totale")[0]!""}</td>

	    	                </tr>
	    	            </#if>
            	    </#list>
	                </tbody>
	            </table>
	        </fieldset>
            <br/>
            </#if>
            <#assign vociPazienti=parentEl.getChildrenByType("LinkVocePazientiFattura") />
            <#if (vociPazienti?? && vociPazienti?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
            <fieldset>
                <div class="table-header">Pazienti Fatturabili</div>
                <table class="table table-striped table-bordered table-hover" style="width:100%">
                    <thead>
                    <tr>
                        <th style="text-align:left;width:40%">Descrizione</th>
                        <th style="text-align:left;width:40%">Nr. pazienti</th>
                        <th style="text-align:left;width:5%">Importo totale</th>
                    </tr>
                    </thead>
                    <tbody>
                    <#list vociPazienti as subEl1>
                    <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
                    <#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='8'>
                    <tr>
                        <td style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","Descrizione")}</td>
                        <td style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","NumPaz")}</td>
                        <td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","Totale")!""}</td>
                    </tr>
                    </#if>
                </#list>
                </tbody>
                </table>
            </fieldset>
            <br/>
            </#if>
            <#assign vociAggiuntive=parentEl.getChildrenByType("LinkVoceAggiuntivaFattura") />
            <#if (vociAggiuntive?? && vociAggiuntive?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
            <fieldset>
                <div class="table-header">Voci aggiuntive in fattura</div>
                <table class="table table-striped table-bordered table-hover" style="width:100%">
                    <thead>
                    <tr>
                        <th style="text-align:left;width:60%">Descrizione</th>
                        <th style="text-align:right;width:7%">Totale</th>
                        <th style="text-align:center;width:11%">Visualizza dettaglio</th>
                    </tr>
                    </thead>
                    <tbody>
                    <#list vociAggiuntive as subEl1>
                    <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
                    <#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='6'>
                    <tr>
                        <td style="text-align:left;">${subEl.getfieldData("DatiAggiuntivaFattura","Descrizione")[0]!""}</td>
                        <td id="totale2_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiAggiuntivaFattura","Totale")[0]!""}</td>
                        <td style="text-align:center;">
                            <#if (subEl.getChildren()?? && subEl.getChildren()?size gt 0)><a
                                href='${subEl.getId()}'><img width="20" height="20"
                                                             src="/img/details.png"></img></a>
                            <#else>n.a.
                        </#if>
                        </td>
                    </tr>
                    </#if>
                </#list>
                </tbody>
                </table>
            </fieldset>
            <br/>
            </#if>
        </#if>

        <#assign vociScheduling=parentEl.getChildrenByType("LinkVoceSchedulingFattura")>

        <#if (vociScheduling?? && vociScheduling?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
            <fieldset>

                <div class="table-header"> Prestazioni/servizi sullo studio</div>
                <table id="table_prest" class=" table table-striped table-bordered table-hover" style="width:100%">
                    <thead>
                        <tr>
                            <th style="text-align:left;width:60%">Descrizione</th>
                            <th style="text-align:left;width:30%">Tipologia attivit&agrave;</th>
                            <th style="text-align:center;width:13%">Voce in fattura</th>
                            <th style="text-align:right;width:10%">Totale rimborsabile</th>
                            <th style="text-align:right;width:7%">Totale</th>
                        </tr>
                    </thead>
                    <tbody>
                    <#list vociScheduling as subEl1>
                        <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
                        <#if (subEl.id)??>
                        <tr id="riga_${subEl.id}">
                            <td id="idDescr_${subEl.id}" style="text-align:left;">${subEl.getfieldData("DatiSchedulingFattura","Descrizione")[0]!""}</td>
                            <td id="idAtt_${subEl.id}" style="text-align:left;">${subEl.getfieldData("DatiSchedulingFattura","AttivitaDecode")[0]!""}</td>
                            <td id="idGruppo_${subEl.id}" style="text-align:center;">${subEl.getfieldData("DatiSchedulingFattura","Gruppo")[0]!""}</td>
                            <td id="idRimbo_${subEl.id}" style="text-align:right;">
                                <#if (subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")?? && subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")?size>
                                    0 &&
                                    subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")[0]=='1')>si
                                    <#else>no
                                </#if>
                            </td>
                            <td id="totale3_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiSchedulingFattura","Prezzo")[0]!""}</td>
                        </tr>
                        </#if>
                    </#list>
                    </tbody>
                </table>
            </fieldset>
            <br/>
	    </#if>

        <#assign vociRiduzione=parentEl.getChildrenByType("LinkVoceRiduzioneFattura")>

        <#if (vociRiduzione?? && vociRiduzione?size gt 0 )>
            <fieldset>
                <div class="table-header">Recupero riduzioni fattura</div>
                <table class="table table-striped table-bordered table-hover" style="width:100%">
                    <thead>
                        <tr>
                            <th style="text-align:left;width:80%">Riduzione </th>
                            <th style="text-align:left;width:20%">Importo riduzione</th>
                        </tr>
                    </thead>
                    <tbody>
                        <#list vociRiduzione as subEl1>
                            <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
                            <#assign mia_riduzione=subEl.getFieldDataElement('DatiRiduzioneFattura','LinkRiduzione')[0]/>
                            <#if subEl.id??>
                                <tr>
                                    <td style="text-align:left;">
                                        <#if mia_riduzione.getFieldDataCode("RiduzioneFattura","TipoRiduzione")?? && mia_riduzione.getFieldDataCode("RiduzioneFattura","TipoRiduzione")=="1" >
                                            riduzione del ${mia_riduzione.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} % da recuperare ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}
                                            <#else>
                                                riduzione di ${mia_riduzione.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} &euro; da recuperare ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}
                                        </#if>
                                         relativa alla fattura n.ro <a href='${mia_riduzione.getParent().getId()}'>${mia_riduzione.getParent().getId()}</a>
                                    </td>
                                    <td style="text-align:center;" class="to-money">
                                        ${subEl.getFieldDataString("DatiRiduzioneFattura","ImportoRecuperato")!""}
                                    </td>

                                </tr>
                            </#if>
                        </#list>
                    </tbody>
                </table>
            </fieldset>
            <br/>
        </#if>


	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='4'> 
	        <fieldset>
                <div class="table-header">Rimborsi a pi&egrave; di lista</div>
                <table class="table table-striped table-bordered table-hover" style="width:100%">
	                <thead>
	    	            <tr>
                            <th style="text-align:left;width:60%">Descrizione</th>
                            <th style="text-align:right;width:7%">Totale</th>
                        </tr>
                    </thead>
                    <tbody>
	                <#list parentEl.getChildrenByType("LinkVocePassThroughFattura") as subEl1>
	    	            <#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	            <#if (subEl.id)??>
                        <tr>
                            <td style="text-align:left;">${subEl.getfieldData("DatiPassThroughFattura","Descrizione")[0]!""}</td>
                            <td id="totale4_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiPassThroughPrezzo","Prezzo")[0]!""}</td>
	    	            </tr>
	    	            </#if>
            	    </#list>
	                </tbody>
                </table>
	        </fieldset>
	    </#if>

        <#assign assorb=parentEl.getChildrenByType("riassorbimentoAcconto")	/>
   		<#if (assorb?size >0)>
            <div class="table-header">Voci a credito</div>
            <table class="table table-striped table-bordered table-hover" style="width:100%">
	            <thead>
	    	        <tr>
	    		        <th style="text-align:left;width:80%">Descrizione</th>
	    		        <th style="text-align:center;width:20%">Valore a credito detratto dal totale</th>
        	    	</tr>
	            </thead>
	            <tbody>
                <#list assorb as subEl>
	    	        <tr>
	    		        <td style="text-align:left;">Quota acconto riassorbita</td>
                        <td style="text-align:center;" class="to-money">${subEl.getFieldDataString("riassorbimentoAcconto","Valore")!""}</td>
        	    	</tr>
	            </#list>
	            </tbody>
	        </table>
            <br/>
        </#if>

        <#if riduzione>
            <#list el.getChildrenByType("RiduzioneFattura") as subEl>
            <div class="table-header">Riduzione fattura</div>
            <table class="table table-striped table-bordered table-hover" style="width:100%">
                <thead>
                    <tr>
                        <th style="text-align:left;width:80%">Riduzione </th>
                        <th style="text-align:left;width:20%">Importo riduzione</th>
                    </tr>
                </thead>
                <tbody>
                    <#if subEl.id??>
                    <tr>
                        <#if subEl.getFieldDataCode("RiduzioneFattura","TipoRiduzione")?? && subEl.getFieldDataCode("RiduzioneFattura","TipoRiduzione")=="1" >
                            <td style="text-align:left;">riduzione del ${subEl.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} % da recuperare ${subEl.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}</td>
                        <#else>
                            <td style="text-align:left;">riduzione di ${subEl.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} &euro; da recuperare ${subEl.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}</td>
                        </#if>
                            <td style="text-align:center;" class="to-money">${el.getFieldDataString("DatiFatturaWF","riduzioneFattura")!""}</td>
                    </tr>
                    </#if>
                </tbody>
            </table>
            </#list>
            <br/>
        </#if>


        <button class="btn btn-primary" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.getParent().getParent().getId()}#tabs-2'">Torna all'elenco fatture</button>
        <br/><br/> <br/><br/>
    	<#include "../helpers/attached-file.ftl"/>
    </div>
</div>
 	  
    <#include "../helpers/fattura-status-bar.ftl"/>
	
</div>
