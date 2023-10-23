

<#assign dmSessionActive=false>
<#if model['requestCookies']??>
<#assign keys = model['requestCookies']?keys>
<#list keys as key>
<#if key=="xcdm.dm.session">
<#assign dmSessionActive=true>
</#if>
</#list>
</#if>
<#if !dmSessionActive>
    <h1>Sessione non attiva</h1>
<#else>

    <#assign userHasSite = true />
<!-- userSitesCodesList ____ ${userSitesCodesList?size}-->
    <#if userSitesCodesList?size gt 0 >
    <#-- faccio il check di visibilità se ho dei centri associati (se non ne ho vuol dire che posso vederli tutti -->

        <#if model["element"].getTypeName()=="Studio" || model["element"].getTypeName()=="Centro"  >
            <#assign elementoRadice=model["element"] />
<!--h1>22 elementoRadice: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
        <#elseif  model["element"].getAncient()?? >
            <#assign elementoRadice=model["element"].getAncient() />
    <!--h1>24 elementoRadice: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
        <#elseif model["element"].getParent().getParent()??>
            <#assign elementoRadice=model["element"].getParent().getParent() />
        <#else>
            <#assign elementoRadice=model["element"].getParent() />
<!--h1>28 elementoRadice: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
        </#if>

        <#assign userHasSite = false />
        <#if elementoRadice.getTypeName()=="Centro"> <#-- la ricerca degli antenati potrebbe fermarsi al centro, controllo qui la visibilità -->
            <!--h1> 26 ancient: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
            <#assign piCF=(elementoRadice.getFieldDataCode("IdCentro","PINomeCognome"))!"" />
            <#assign strutturaCODE=(elementoRadice.getFieldDataCode("IdCentro","Struttura"))!"" />
            <#list userSitesCodesList as site>
                <#if site==strutturaCODE>
                    <#assign userHasSite = true />
                </#if>
            </#list>
        <#else>
            <!--h1>ancient: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
            <#if elementoRadice.getTypeName()=="Emendamento">
                <#assign elementoRadice=elementoRadice.getParent() />
            <!--h1>45 elementoRadice: ${elementoRadice.getId()} - ${elementoRadice.getTypeName()}</h1-->
            </#if>
            <#assign listaCentriInseriti = elementoRadice.getChildrenByType("Centro") />
            <#list listaCentriInseriti as stCentro>
                <#assign piCF=(stCentro.getFieldDataCode("IdCentro","PINomeCognome"))!"" />
                <#assign strutturaCODE=(stCentro.getFieldDataCode("IdCentro","Struttura"))!"" />
                <#list userSitesCodesList as site>
                    <#if site==strutturaCODE>
                        <#assign userHasSite = true />
                    </#if>
                </#list>
            </#list>
        </#if>
    </#if>
<!-- userHasSite ${userHasSite?c} -->
    <#if userHasSite >
    <div id="myTab">
    <div class="tabbable">
        <ul id="templatesNavTab" class="nav nav-tabs padding-12 tab-color-blue background-blue">
        </ul>
        <div id="templatesTabContent"  class="tab-content">
            <div id="POLICY_TAB" class="tab-pane" >
                <input type="button" name="add-policy" id="add-policy" value="Aggiungi Policy" class="submitButton btn btn-sm btn-info">
                <table class="table table-striped table-bordered table-hover">
                    <thead>
                    <tr>
                        <th>Policy</th>
                        <th>Container</th>
                        <#include "../helpers/permission-tb-header.ftl"/>
                        <th title="Template ad-hoc">Template</th>
                        <th>Action</th>
                    </tr>
                    </thead>
                    <tbody id="policy-list-availables"></tbody>
                </table>
            </div>
        </div> <!--tab-content-->
    </div> <!--tabbable-->
    </div>

    <div id="permission-div" style="display:none; font-size:14px;">
    <div id="permission-dialog" title="Aggiungi/modifica permessi" >
        <fieldset>
            <div class="field-component">
                <@checkBox "allUsers" "allUsers" "Tutti gli utenti" {"1":""} />
            </div>
            <div class="field-component">
                <@checkBox "cuser" "cuser" "Owner" {"1":""} />
            </div>
            <div class="field-component">
                <@multiAutoCompleteFB "groups" "groups" "Gruppi" "${baseUrl}/uService/rest/user/searchAuth" "authority"/>
            </div>
            <div class="field-component">
                <@multiAutoCompleteFB "users" "users" "Utenti" "${baseUrl}/uService/rest/user/searchUser" "username"/>
                <@hidden "id" "id"/>
            </div>
        </fieldset>
    </div>
    </div>
    <#else>
    <h1>Informazioni non modificabili se tale oggetto non è di competenza dell'�utente collegato</h1>
    </#if>

</#if>