
<#-- QUI VERIFICO L'APPARTENENZA ALLA STRUTTURA! -->
<#assign userCF = userDetails.username /> <#-- qui ho username mio o del delegante -->
<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
    <#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
</#if>
<#assign listaCentriInseriti = el.getChildrenByType("Centro") />
<#assign userHasSite = false />
<#assign userHasPI = false />
<#assign userHasUO = false />
<#assign userCreatedCenter = false />
<#list listaCentriInseriti as stCentro>
    <!-- CReATO DA ${stCentro.getCreateUser()} usrloggato ${userCF}-->
    <#assign piCF=(stCentro.getFieldDataCode("IdCentro","PINomeCognome"))!"" />
    <#assign strutturaCODE=(stCentro.getFieldDataCode("IdCentro","Struttura"))!"" />
    <#assign UOCODE=[] />
        <#list el.getChildrenByType("Centro") as centro>
            <#assign UOCODE=[(centro.getFieldDataCode("IdCentro","UO"))!""] + UOCODE/>
        </#list>
    <#if userSitesCodesList?size gt 0 >
        <#list userSitesCodesList as site>
            <#if site==strutturaCODE>
                <#assign userHasSite = true />
            </#if>
        </#list>
    <#else>
        <#assign userHasSite = true />
    </#if>
    <#if userCF==piCF || userDetails.username==piCF >
        <#assign userHasPI = true />
    </#if>
    <#if userUOCodesList?size gt 0 >
        <#list userUOCodesList as uo>
            <#list UOCODE as code>
                <#if uo==code>
                    <#assign userHasUO = true />
                </#if>
            </#list>
        </#list>
    <#else>
        <#assign userHasUO = true />
    </#if>
    <#-- if stCentro.getCreateUser()==userCF > <#-- non lo uso più perchè togliamo vincolo visibilità su chi ha creato il centro
    (in caso poi si sposta su un'altra Azienda non può continuare a vedere questo centro) -->
        <#assign userCreatedCenter = true />
    </ # if -->
</#list>
<!-- userCreatedCenter ${userCreatedCenter?string} -->
<#-- userDetails.hasRole("CTC") && true -->
<#--if ( userDetails.hasRole("tech-admin") || (el.getCreateUser()==userDetails.username) || (userHasSite) || (userDetails.hasRole("PI") && userHasPI) )-->
<#assign canAccess = true /> <#-- possono entrare tutti-->
<#assign canAccessTab = true /> <#-- STSANSVIL-712 Richiesta modifica permessi di visualizzazione profili utente -->
<#--if userDetails.hasRole("SP") && el.getCreateUser()!=userDetails.username  >
    <#assign canAccess = false /> <! -- commento perchè con la STSANSVIL-1258 anche lo sponsor può vedere gli studi per i quali ha i permessi dati tramite Datamamanagement -- >
</#if-->
<#if canAccess >
<!-- HAS PI: ${userHasPI?string}-->
<!-- HAS SITE: ${userHasSite?string}-->
<!-- HAS UO: ${userHasUO?string} - IS UO: ${userDetails.hasRole("COORD")?string}-->
    <#assign forceRO = false />
    <#if (!userDetails.hasRole("tech-admin") && el.getCreateUser()!=userDetails.username ) >
        <#if ( (userDetails.hasRole("SEGRETERIA") && !userHasSite) ||  ( userDetails.hasRole("PI") &&  !userHasPI)  || (userDetails.hasRole("CTC") && !userHasSite)  )>
            <#assign editable = false />
            <#assign forceRO = true />
        </#if>
    </#if>
    <#if ( userDetails.hasRole("PI") &&  !userHasPI && userDetails.hasRole("COORD") && !userHasUO)  || (userDetails.hasRole("CTC") && !userHasSite) >
        <#--
        STSANSVIL-712 Richiesta modifica permessi di visualizzazione profili utente -
        accesso alle sezioni CRO, FARMACI, Emendamenti, Documenti, Prodotti avviene solo quando
        il PI o CTC hanno inserito un centro di loro competenza
        -->
        <#assign canAccessTab = false />
    </#if>
    <!-- EDITABLE: ${editable?string}-->
    <!-- FORCE RO: ${forceRO?string}-->
    <!-- CANACCES: ${canAccess?string} - CANACCESTAB: ${canAccessTab?string}-->
    <script>
        bootbox.dialog({
            message: '<div class="text-center"><i class="fa fa-spin fa-spinner"></i> Caricamento in corso...</div>',
            closeButton: false,
            onEscape: false
        });
    </script>
    <@script>
	    $.ajaxSetup({async:false});
        bootbox.hideAll();
    </@script>
    <div class="row">
   		<div class="col-xs-9">
			<#include "../helpers/studioInformation.ftl"/>
		</div>
		<#include "../helpers/studio-status-bar.ftl"/>
    </div>
<#else>

    <#--assign editable=false /-->
	<h1>Studio non visibile per l'utente/profilo corrente</h1>
    <#-- ${dipartCODE} - ${userDetails.anaData.RESP_DIP_DID} -->

</#if>
