<div  class="col-xs-3 sidebar-right">
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>
<div class=" status-bar-content">

        <div class="col-xs-12 status-bar">
            <h2>Informazioni</h2>
            <div>
            <#if userDetails.hasRole("CTC") || userDetails.hasRole("PI")  || userDetails.hasRole("COORD")>
                <a style="text-decoration:none;" href="${baseUrl}/app/documents/pdf/Fattibilita_Locale/${el.getId()}"><img style="float:left;" width="40" height="40" src="/pdf.jpg"><span style="float:left;" >&nbsp;Genera documentazione<br/>&nbsp;centro-specifica</span></a>
                <!--a style="text-decoration:none;" href="${baseUrl}/../ModCE.pdf"><img style="float:left;" width="40" height="40" src="/pdf.jpg"><span style="float:left;" >&nbsp;Genera documentazione<br/>&nbsp;centro-specifica pdf sample</span></a-->
            </#if>
            </div>
            <div style="clear:both" />
            <div id="ritiro">
                <p data-id="dataRitiro"></p>
                <p data-id="noteRitiro"></p>
            </div>

		<#if el.getFieldDataCode("statoValidazioneCentro","idIstruttoriaCEPositiva")=="">
			<#assign istruttoriaInCompilazione=false />
			<#if el.getChildrenByType("IstruttoriaCE")?? && el.getChildrenByType("IstruttoriaCE")?size gt 0 >

				<#list el.getChildrenByType("IstruttoriaCE") as istruttoria>
					<#if !istruttoriaInCompilazione && istruttoria.getFieldDataString("IstruttoriaCE","istruttoriaWFinviata")=="" >
						<#assign istruttoriaInCompilazione=true />
					</#if>
				</#list>

				<#--istruttoria in compilazione? ${istruttoriaInCompilazione?c}
				valCTC? ${el.getFieldDataCode("statoValidazioneCentro","valCTC")}
				inviatoCE? ${el.getFieldDataCode("statoValidazioneCentro","inviatoCE")}
				idIstruttoriaCEPositiva? ${el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")}-->

				<#if (el.getFieldDataCode("statoValidazioneCentro","fattLocale")=="" && el.getFieldDataString("statoValidazioneCentro","inviatoCE")=="") && el.getFieldDataCode("statoValidazioneCentro","idIstruttoriaCEPositiva")=="" && !istruttoriaInCompilazione>
					<div class="col-sm-12" style="clear:both;">
						<div id="quarantena" class="alert alert-block alert-danger" style="">
							<i class="fa fa-exclamation-circle red"></i> <a style="text-decoration:none;" onclick="" href="#"><span style="float:left;" >&nbsp;Centro in fase di richiesta integrazioni</span></a>
						</div>
					</div>
				</#if>

			</#if>
		</#if>


        <#if userDetails.getEmeSessionId()??  >
            <#assign objEme = (el?? && el.getInEmendamento()) />
            <#assign parentEme = (el?? && el.parent?? && userDetails.getEmeRootElementId()?? && userDetails.getEmeRootElementId() = el.parent.getId()) />
            <!-- OBJEME: ${objEme?string} - PARENTEME ${parentEme?string} -->
            <#if (objEme || parentEme) >
            <div class="col-sm-12" style="clear:both;">
                <#--IN EME: ${el.getInEmendamento()}-->
                <div id="quarantena" class="alert alert-block alert-danger" style="min-height:50px;">
                        <i class="fa fa-exclamation-circle red"></i> <a style="text-decoration:none;" onclick="" href="#"><span style="float:left;" >&nbsp;Emendamento in corso, id: ${userDetails.getEmeSessionId()}<br></span></a>
                    <br/>
                    <button title="Disattiva modifiche" class="btn btn-info btn-xs" style="margin-top:0px" onclick="
                                                    $.ajax({
                                                        method : 'GET',
                                                        url : baseUrl+'/app/rest/documents/emendamento/deactivate'
                                                    }).done(function() {
                                                        window.location.reload();
                                                    });" > <i class="icon icon-eraser"></i>Disattiva modifiche</button>
                </div>
            </div>
            <#else>
            <!--Sessione emendamento attiva in altro studio. <br/>-->
            </#if>
		</#if>

        </div>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status0=statusGrey status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey status9=statusGrey />

<#--
<#setting number_format="0.##">
<#setting locale="en_US">
<#assign percentuale=0>
<#assign totSteps=9>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey status9=statusGrey />




<#assign percentuale=percentuale*100/totSteps>


                -->
<#assign percentuale=0/>
<#assign totSteps=8>
<#assign dataFirmaContr="" /> <#-- TOSCANA-162 + HDCRPMS-619 ho messo questa porzione di codice fuori dallo script -->
<#list el.getChildrenByType("Contratto") as conEl>
    <#list conEl.getChildrenByType("ContrattoFirmaDG") as childDG>
        <#if childDG.id??>
            <#assign status4=statusGreen/>
            <#assign percentuale=percentuale+1>
                <#assign dataFirmaContr=getFieldFormattedDate("DatiContrattoFirmaDG", "dataFirma", childDG) />
        </#if>
    </#list>
</#list>
<@script>

function formatDate(ts) {
    var dt = new Date(ts);
    var months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12'];
    var days = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
    var curWeekDay = days[dt.getDay()];
    var curDay = dt.getDate();
    var curMonth = months[dt.getMonth()];
    var curYear = dt.getFullYear();
    if (curDay<10) curDay="0"+curDay;
    var date = curDay+"/"+curMonth+"/"+curYear; //curWeekDay+", "+
    return date;
}


var elJsonElk=null;
function loadElkElementCentro(){
    $.getJSON('${baseUrl}/app/rest/elk/getElement/centro/${el.id}').done(function(data){
        elJsonElk=data;
        buildAvanzamento(data);
    });
}

function buildAvanzamento(elJsonElk){
    var percentuale=${percentuale};
    var totSteps=${totSteps};

    if (
        elJsonElk.metadata.statoValidazioneCentro &&
        elJsonElk.metadata.statoValidazioneCentro.values &&
        elJsonElk.metadata.statoValidazioneCentro.values.fattLocale_CODE==1
        ){
        $('#avanzamentoCentro ._step_1 i.my-timeline').removeClass('${statusGrey}');
        $('#avanzamentoCentro ._step_1 i.my-timeline').addClass('${statusGreen}');
        if (elJsonElk.metadata.statoValidazioneCentro.values.dataFattLocale_TS){
            dataFattLoc=new Date(elJsonElk.metadata.statoValidazioneCentro.values.dataFattLocale_TS[0]);
            dataFattLocString=formatDate(dataFattLoc);
            $('#avanzamentoCentro ._step_1 .timeline-body span.timeline-date').html(dataFattLocString);
        }
        percentuale++;
    }
    if (
        elJsonElk.metadata.RichiestaSponsor &&
        elJsonElk.metadata.RichiestaSponsor.values &&
        elJsonElk.metadata.RichiestaSponsor.values.statoRichiesta==1
    ){
        $('#avanzamentoCentro ._step_0 i.my-timeline').removeClass('${statusGrey}');
        $('#avanzamentoCentro ._step_0 i.my-timeline').addClass('${statusGreen}');
        if (elJsonElk.metadata.RichiestaSponsor.values.dataInvioRichiesta_TS){
            dataInvioRichiesta=new Date(elJsonElk.metadata.RichiestaSponsor.values.dataInvioRichiesta_TS[0]);
            dataInvioRichiesta=formatDate(dataInvioRichiesta);
            $('#avanzamentoCentro ._step_0 .timeline-body span.timeline-date').html(dataInvioRichiesta);
        }
        percentuale++;
    }
    else{
        $('#avanzamentoCentro ._step_0 i.my-timeline').hide();
    }


    if (
        elJsonElk.metadata.statoValidazioneCentro &&
        elJsonElk.metadata.statoValidazioneCentro.values &&
        elJsonElk.metadata.statoValidazioneCentro.values.idBudgetApproved &&
        elJsonElk.metadata.statoValidazioneCentro.values.idBudgetApproved!=''
    ){
        var idBudgetApproved=elJsonElk.metadata.statoValidazioneCentro.values.idBudgetApproved-0;
        $('#avanzamentoCentro ._step_2 i.my-timeline').removeClass('${statusGrey}');
        $('#avanzamentoCentro ._step_2 i.my-timeline').addClass('${statusGreen}');
        if (elJsonElk.children.Budget){
            for (var i=0; i<elJsonElk.children.Budget.length;i++){
                if (elJsonElk.children.Budget[i].id==idBudgetApproved){
                    if (elJsonElk.children.Budget[i].metadata.ChiusuraBudget.values.Data_TS){
                        dataChiusuraBudget=new Date(elJsonElk.children.Budget[i].metadata.ChiusuraBudget.values.Data_TS[0]);
                        dataChiusuraBudget=formatDate(dataChiusuraBudget);
                        $('#avanzamentoCentro ._step_2 .timeline-body span.timeline-date').html(dataChiusuraBudget);
                    }
                }
            }
        }
        if (elJsonElk.children.BudgetBracci){
            for (var i=0; i<elJsonElk.children.BudgetBracci.length;i++){
                if (elJsonElk.children.BudgetBracci[i].id==idBudgetApproved){
                    if (elJsonElk.children.BudgetBracci[i].metadata.ChiusuraBudget.values.Data_TS){
                        dataChiusuraBudget=new Date(elJsonElk.children.BudgetBracci[i].metadata.ChiusuraBudget.values.Data_TS[0]);
                        dataChiusuraBudget=formatDate(dataChiusuraBudget);
                        $('#avanzamentoCentro ._step_2 .timeline-body span.timeline-date').html(dataChiusuraBudget);
                    }
                }
            }
        }
        percentuale++;
    }



    if (
        elJsonElk.metadata.statoValidazioneCentro &&
        elJsonElk.metadata.statoValidazioneCentro.values &&
        elJsonElk.metadata.statoValidazioneCentro.values.valCTC_CODE==1
        ){
        $('#avanzamentoCentro ._step_3 i.my-timeline').removeClass('${statusGrey}');
        $('#avanzamentoCentro ._step_3 i.my-timeline').addClass('${statusGreen}');
        if (elJsonElk.metadata.statoValidazioneCentro.values.dataValCTC_TS){
            dataValCTC=new Date(elJsonElk.metadata.statoValidazioneCentro.values.dataValCTC_TS[0]);
            dataValCTC=formatDate(dataValCTC);
            $('#avanzamentoCentro ._step_3 .timeline-body span.timeline-date').html(dataValCTC);
        }
        percentuale++;
    }


    if (elJsonElk.children.ParereCe ){
        for (var i=0;i<elJsonElk.children.ParereCe.length;i++){
            parereNode=elJsonElk.children.ParereCe[i];
            var found=false;
            var dataParere=null;
            if (
            parereNode.metadata.ParereCe.values.esitoParere_CODE=='1'){//TOSCANA-162 modificato valore di controllo
                found=true;
                if (parereNode.metadata.ParereCe.values.dataSeduta_TS){
                    dataParere=new Date(parereNode.metadata.ParereCe.values.dataSeduta_TS[0]);
                    dataParere=formatDate(dataParere);
                }
            }

        }
        if (found){
            $('#avanzamentoCentro ._step_5 i.my-timeline').removeClass('${statusGrey}');
            $('#avanzamentoCentro ._step_5 i.my-timeline').addClass('${statusGreen}');
            $('#avanzamentoCentro ._step_5 .timeline-body span.timeline-date').html(dataParere);
            percentuale++;
        }
    }
    if (elJsonElk.children.IstruttoriaCE ){
        var found=false;
        var dataIstruttoria=null;
        for (var i=0;i<elJsonElk.children.IstruttoriaCE.length;i++){
            istruttoriaNode=elJsonElk.children.IstruttoriaCE[i];
            if (istruttoriaNode.metadata && istruttoriaNode.metadata.IstruttoriaCE && istruttoriaNode.metadata.IstruttoriaCE.values.DocCompleta_CODE==1 && istruttoriaNode.metadata.IstruttoriaCE.values.istruttoriaWFinviata==1){
                if (istruttoriaNode.metadata.IstruttoriaCE.values.DataRicDoc_TS){
                    found=true;
                    dataIstruttoria=new Date(istruttoriaNode.metadata.IstruttoriaCE.values.DataRicDoc_TS[0]);
                    dataIstruttoria=formatDate(dataIstruttoria);
                }
            }
        }

        if (found){
            $('#avanzamentoCentro ._step_8 i.my-timeline').removeClass('${statusGrey}');
            $('#avanzamentoCentro ._step_8 i.my-timeline').addClass('${statusGreen}');
            $('#avanzamentoCentro ._step_8 .timeline-body span.timeline-date').html(dataIstruttoria);
            percentuale++;
        }
    }







    if (elJsonElk.children.ChiusuraCentro){
        var found=false;
        var dataChiusura=null;
        for (var i=0;i<elJsonElk.children.ChiusuraCentro.length && !found;i++){
            parereNode=elJsonElk.children.ChiusuraCentro[i];
            if (parereNode.metadata.DatiChiusuraCentro && parereNode.metadata.DatiChiusuraCentro.values.dataConclusioneCentro){
                found=true;
                dataChiusura=new Date(parereNode.metadata.DatiChiusuraCentro.values.dataConclusioneCentro_TS[0]);
                dataChiusura=formatDate(dataChiusura);
            }
        }
        if (found){
            $('#avanzamentoCentro ._step_6 i.my-timeline').removeClass('${statusGrey}');
            $('#avanzamentoCentro ._step_6 i.my-timeline').addClass('${statusGreen}');
            $('#avanzamentoCentro ._step_6 .timeline-body span.timeline-date').html(dataChiusura);
            percentuale++;
        }
    }



    if (elJsonElk.children.AvvioCentro){
        var found=false;
        var dataApertura=null;
        for (var i=0;i<elJsonElk.children.AvvioCentro.length && !found;i++){
             parereNode=elJsonElk.children.AvvioCentro[i];
             if (parereNode.metadata.DatiAvvioCentro.values.dataAperturaCentro_TS){
                 found=true;
                 dataApertura=new Date(parereNode.metadata.DatiAvvioCentro.values.dataAperturaCentro_TS[0]);
                 dataApertura=formatDate(dataApertura);
             }
        }
        if (found){
            $('#avanzamentoCentro ._step_9 i.my-timeline').removeClass('${statusGrey}');
            $('#avanzamentoCentro ._step_9 i.my-timeline').addClass('${statusGreen}');
            $('#avanzamentoCentro ._step_9 .timeline-body span.timeline-date').html(dataApertura);
            percentuale++;
        }
    }
    if (
        elJsonElk.metadata.RitiroCentroWF &&
        elJsonElk.metadata.RitiroCentroWF.values &&
        elJsonElk.metadata.RitiroCentroWF.values.dataChiusuraAmm
        ){
        $('#avanzamentoCentro ._step_8 i.my-timeline').removeClass('${statusGrey}');
        $('#avanzamentoCentro ._step_8 i.my-timeline').addClass('${statusGreen}');
        dataCloseOut=new Date(elJsonElk.metadata.RitiroCentroWF.values.dataChiusuraAmm_TS[0]);
        dataCloseOut=formatDate(dataCloseOut);
        $('#avanzamentoCentro ._step_8 .timeline-body span.timeline-date').html(dataCloseOut);
        percentuale++;
    }



    var dataRitiro='';
    var noteRitiro='';
    if (elJsonElk.metadata.RitiroCentroWF && elJsonElk.metadata.RitiroCentroWF.values.dataRitiro && elJsonElk.metadata.RitiroCentroWF.values.dataRitiro.length>0){
            dt=new Date(elJsonElk.metadata.RitiroCentroWF.values.dataRitiro_TS[0]);
            dt=formatDate(dt);
            dataRitiro='<br/><h2>Centro Ritirato</h2><span style="color:red; font-weight: bold;">Data ritiro:</span>&nbsp;<span style="font-weight: bold;">'+dt+'</span>';


            if (elJsonElk.metadata.RitiroCentroWF && elJsonElk.metadata.RitiroCentroWF.values.noteRitiro){
                    nt=elJsonElk.metadata.RitiroCentroWF.values.noteRitiro;
                    noteRitiro='<span style="color:red; font-weight: bold;">Note ritiro:</span>&nbsp;<span style="font-weight: bold;">'+nt+'</span>';
            }

            $('#ritiro p[data-id="dataRitiro"]').html(dataRitiro);
            $('#ritiro p[data-id="noteRitiro"]').html(noteRitiro);
    }
    else{
        $('#ritiro').hide();
    }

    percentuale=percentuale*100/totSteps;
    $('#avanzamentoCentro .progress').attr('data-percent', percentuale.toFixed(2)+'%');
    $('#avanzamentoCentro .progress .progress-bar').css('width', percentuale+'%');


}

loadElkElementCentro();
</@script>

        <div id='avanzamentoCentro' class="col-xs-12 status-bar">
        <h2>Avanzamento</h2>
        <div id="creatoDaSponsor" >

            <#assign creatoDaSponsor=false />
            <#list el.templates as template>
                <#if template.name="RichiestaSponsor">
                    <h4 style="color:red"><b>Centro inserito da Sponsor</b></h4>
                    <#assign creatoDaSponsor=true />
                    <#assign totSteps=totSteps+1 />
                </#if>
            </#list>
        </div>


        <div class="progress pos-rel" data-percent="">
            <div class="progress-bar"></div>
        </div>
        <div class="timeline-container timeline-style2">
            <div class="timeline-items">
                <#if creatoDaSponsor>
                <div class="timeline-item clearfix _step_0">
                    <div class="timeline-info">
                        <span class="timeline-date">Studio inviato al centro dallo Sponsor</span>
                        <i class="my-timeline ${status0}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>
                </#if>
                <div class="timeline-item clearfix _step_1">
                    <div class="timeline-info">
                                <span class="timeline-date">Fattibilit&agrave; PI</span>
                            <i class="my-timeline ${status1}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="timeline-item clearfix _step_2">
                    <div class="timeline-info">
                                <span class="timeline-date">Chiusura budget (ultima versione)</span>
                            <i class="my-timeline ${status2}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="timeline-item clearfix _step_3">
                    <div class="timeline-info">
                            <span class="timeline-date">Valutazione Aziendale</span>
                            <i class="my-timeline ${status3}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="timeline-item clearfix _step_8">
                    <div class="timeline-info">
                        <span class="timeline-date">Istruttoria CE</span>
                        <i class="my-timeline ${status8}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>

                    </div>
                </div>
                <div class="timeline-item clearfix _step_5">
                    <div class="timeline-info">
                                <span class="timeline-date">Valutazione CE</span>
                            <i class="my-timeline ${status5}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="timeline-item clearfix _step_4">
                    <div class="timeline-info">
                                <span class="timeline-date">Firma contratto</span>
                            <i class="my-timeline ${status4}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date">${dataFirmaContr}</span>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="timeline-item clearfix _step_9">
                    <div class="timeline-info">
                                <span class="timeline-date">Apertura centro</span>
                            <i class="my-timeline ${status9}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>

                    </div>
                </div>

                <div class="timeline-item clearfix _step_6">
                    <div class="timeline-info">
                                <span class="timeline-date">Chiusura centro</span>
                            <i class="my-timeline ${status6}"></i>
                    </div>
                    <div class="timeline-body widget-box transparent">
                        <div class="widget-body">
                            <div class="widget-main no-padding">
                                <span class="timeline-date"></span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        </div>
        </div>
        </div>
