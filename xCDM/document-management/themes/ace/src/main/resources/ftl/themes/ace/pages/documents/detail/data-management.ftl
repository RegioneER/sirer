

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


    </#if>