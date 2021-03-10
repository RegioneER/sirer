<#assign el=element/>
<#setting number_format="0.##" />
<#setting locale="it_IT">
<#assign UncheckedCheckbox>
<img src="images/Unchecked-Checkbox-icon.png" width="10" height="10" />
</#assign>

<#assign CheckedCheckbox>
<img src="images/Checked-Checkbox-icon.png" width="10" height="10" />
</#assign>
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
        height:150px;
    }
    .vs label{
        width:30%;
    }

    .re{
        float: left;
        width: 40%;
        height:150px;
    }
    .re label{
        width:55%;
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
        width: 45%;
    }
    .vl label{
        width:55%;
    }

    .ui-autocomplete.ui-menu{
        z-index:9999!important;
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

    .done{
        background-color: lightgreen;border-radius: 5px;padding:2px;
        vertical-align:middle;
    }
    .pending{
        background-color: #F98F1D;border-radius: 5px;padding:2px;
    }
    table td {
        padding: 10px;
    }
</style>

<div class="row">
    <div class="col-xs-9">

        <!--#include "../helpers/MetadataTemplate.ftl"/-->
        <div style="display: block">
            <#assign scarico=el />
            <#assign depot=el.getParent()/>
            <#assign centro=el.getParent().getParent() />
            <#assign studio=centro.getParent() />

            <#assign sponsor="" />
            <#assign croString="" />
            <#assign codice="" />
            <#assign titolo="" />
            <#assign DenCentro="" />
            <#assign DenIstituto="" />
            <#assign DenDipartimento="" />
            <#assign DenUnitaOperativa="" />
            <#assign DenPrincInv="" />
            <#assign eudraCT="N.D."/>
            <#assign tipoStudio=""/>

            <#assign idStudio = studio.getFieldDataString("UniqueIdStudio", "id") />
            <#if (studio.getFieldDataElement("datiPromotore", "promotore")?? && studio.getFieldDataElement("datiPromotore", "promotore")?size>0) >
            <#assign sp = studio.getFieldDataElement("datiPromotore", "promotore")[0] />
            <#assign sponsor = sp.getFieldDataString("DatiPromotoreCRO","denominazione") />
        </#if>
        <#if (studio.getFieldDataElement("datiCRO", "denominazione")?? && studio.getFieldDataElement("datiCRO", "denominazione")?size>0) >
        <#assign cro = studio.getFieldDataElement("datiCRO", "denominazione")[0] />
        <#assign croString = cro.getFieldDataString("DatiPromotoreCRO","denominazione") />
    </#if>
    <#if (studio.getfieldData("IDstudio","CodiceProt")?? && studio.getfieldData("IDstudio","CodiceProt")?size>0) >
    <#assign codice=studio.getFieldDataString("IDstudio","CodiceProt") />
</#if>
<#if (studio.getfieldData("IDstudio","TitoloProt")?? && studio.getfieldData("IDstudio","TitoloProt")?size>0) >
<#assign titolo=studio.getFieldDataString("IDstudio","TitoloProt") />
</#if>
<#if (studio.getFieldDataString("datiStudio","eudractNumber")?? && studio.getFieldDataString("datiStudio","eudractNumber")!="" ) >
<#assign eudraCT=studio.getFieldDataString("datiStudio","eudractNumber")/>
</#if>
<#if (studio.getFieldDataDecode("datiStudio","tipoStudio")?? && studio.getFieldDataDecode("datiStudio","tipoStudio")!="" ) >
<#assign tipoStudio=studio.getFieldDataDecode("datiStudio","tipoStudio")/>
</#if>


<#assign DenCentro = centro.getFieldDataDecode("IdCentro","Struttura") />
<!--#assign DenIstituto = centro.getFieldDataDecode("IdCentro","Istituto") /-->
<!--#assign DenDipartimento = centro.getFieldDataDecode("IdCentro","Dipartimento") /-->
<#assign DenUnitaOperativa = centro.getFieldDataDecode("IdCentro","UO") />
<#assign DenPrincInv = centro.getFieldDataDecode("IdCentro","PI") />
<#assign dataParere="" />
<#list centro.getChildrenByType("ParereCe") as parere>
<#if parere.getFieldDataString("ParereCe","esitoParere")=="Parere favorevole" && parere.getFieldDataFormattedDates("ParereCe", "dataParere", "dd/MM/yyyy")?size>0 >
<#assign dataParere=parere.getFieldDataFormattedDates("ParereCe", "dataParere", "dd/MM/yyyy")[0] />
</#if>
</#list>
<#assign deliberaProt="" />
<#list centro.getChildrenByType("Contratto") as contratto>
<#list contratto.getChildrenByType("AllegatoContratto") as allegato>
<#if allegato.getFieldDataCode("tipologiaContratto","TipoContratto")=="7" >
<#assign deliberaProt=allegato.getFieldDataString("tipologiaContratto","numeroProtocollo") />
</#if>
</#list>
</#list>

<#assign info>
<table>
    <tr style="text-align: left"> <th>PROTOCOLLO DI STUDIO:</th><td> ${codice}</td></tr>
    <tr style="text-align: left"> <th>Titolo:</th><td> ${titolo}</td></tr>
    <tr style="text-align: left"> <th>Numero Studio: </th><td> ${idStudio}</td></tr>
    <tr style="text-align: left"> <th>Approvazione CE del</th><td> ${dataParere} </td></tr>
    <tr style="text-align: left"> <th>Delibera Aziendale: n</th><td> ${deliberaProt}</td></tr>
</table>
</#assign>

<table border="1" cellspacing="10" cellpadding="10" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">
    <thead>
    <tr>
        <td style="text-align:center"><h2>MODULO DI CONSEGNA PRODOTTI FARMACEUTICI IN SPERIMENTAZIONE CLINICA</h2></td>
    </tr>
    </thead>
    <tbody>
    <tr>
        <td>EUDRACT: ${eudraCT}</td>
    </tr>
    <tr>
        <td><b>PRODOTTO IN SPERIMENTAZIONE (IMP):</b>  ${depot.getFieldDataElement("depotFarmaco","linkFarmaco")[0].titleString}  <br/>
            <b>T&deg; conservazione:</b> ${depot.getFieldDataDecode("depotFarmaco","temperaturaConservazione")}</td>
    </tr>
    <tr>
        <td>
            ${info}
        </td>
    </tr>
    <tr>
        <td>
            <div style="float: left;">${UncheckedCheckbox} per quantit&agrave; complessiva</div>
            <div style="float: right;">${UncheckedCheckbox} consegna personalizzata<br/>CODICE PZ. N._____</div>
        </td>
    </tr>
    </tbody>
</table>
<br/>
<table border="1" cellspacing="10" cellpadding="10" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">
    <thead>
    <tr>
        <td style="text-align:left">QUANTIT&Agrave; CONSEGNATA</td>
    </tr>
    </thead>
    <tbody>
    <tr>
        <td>
            N&deg; DI CONFEZIONI: ${scarico.getChildrenByType("DepotFarmacoScaricoDistr")?size}
            <br/>
            <#list scarico.getChildrenByType("DepotFarmacoScaricoDistr") as distr >
            <#if distr.getFieldDataElement("depotFarmacoScaricoDistr","barcode")?? && distr.getFieldDataElement("depotFarmacoScaricoDistr","barcode")[0]?? >
            <#assign barcode=distr.getFieldDataElement("depotFarmacoScaricoDistr","barcode")[0] />
            <#assign lotto=barcode.getParent() />
            <#assign carico=lotto.getParent() />
        </#if>
        <b>Lotto/Barcode:</b> ${lotto.getFieldDataString("depotFarmacoLotto","numeroLotto")}/${barcode.getId()} <b>Scad:</b> ${lotto.getFieldDataFormattedDates("depotFarmacoLotto", "scadenza", "dd/MM/yyyy")[0]} <b>Arrivati il: </b> ${carico.getFieldDataFormattedDates("depotFarmacoCarico", "dataCarico", "dd/MM/yyyy")[0]}
        <br/>
    </#list>
    </td>
    </tr>
    <tr>
        <td><b>DATA DI CONSEGNA:</b> ${scarico.getFieldDataFormattedDates("depotFarmacoScarico", "dataScarico", "dd/MM/yyyy")[0]}<br/>
            <b>ORARIO DI PARTENZA:</b> ${scarico.getFieldDataFormattedDates("depotFarmacoScarico", "dataScarico", "hh:mm")[0]}<br/>
            <b>ORARIO DI CONSEGNA:</b> ${scarico.getFieldDataFormattedDates("depotFarmacoScarico", "dataScarico", "hh:mm")[0]}
            <div style="float:right"> Firma Sperimentatore Principale o Co-Sperimentatore<br/>(Delegato alla consegna)<br/>_________________________________</div>
        </td>
    </tr>
    <tr>
        <td><br/>Firma del Farmacista _____________________________________________</td>
    </tr>
    </tbody>
</table>
</div>
</div>
</div>