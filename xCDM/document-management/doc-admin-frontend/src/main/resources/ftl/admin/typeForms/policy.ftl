
<div id="policy-dialog" title="Aggiungi policy">
    <fieldset>
        <form id="policy-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@hidden "id" "id" ""/>
        <@textbox "name" "name" "Nome" "" 40/>
        <@textbox "description" "description" "Descrizione" "" 40/>
            <br/>
            <table class="pSchema">
                <thead>
                <tr>
                    <th style="display: none"></th>
                    <#include "../helpers/permission-tb-header.ftl"/>
                    <th style="display: none"></th>
                </tr>
                </thead>
                <tbody>
                <tr>
                    <td style="display: none"></td>
                    <td><@checkBox "view" "view" "" {"1":""} /></td>
                    <td><@checkBox "create" "create" "" {"1":""} /></td>
                    <td><@checkBox "update" "update" "" {"1":""} /></td>
                    <td><@checkBox "addComment" "addComment" "" {"1":""} /></td>
                    <td><@checkBox "moderate" "moderate" "" {"1":""} /></td>
                    <td><@checkBox "delete" "delete" "" {"1":""} /></td>
                    <td><@checkBox "changePermission" "changePermission" "" {"1":""} /></td>
                    <td><@checkBox "addChild" "addChild" "" {"1":""} /></td>
                    <td><@checkBox "removeCheckOut" "removeCheckOut" "" {"1":""} /></td>
                    <td><@checkBox "launchProcess" "launchProcess" "" {"1":""} /></td>
                    <td><@checkBox "enableTemplate" "enableTemplate" "" {"1":""} /></td>
                    <td><@checkBox "canBrowse" "canBrowse" "" {"1":""} /></td>
                    <td style="display: none"></td>
                </tr>
                </tbody>
            </table>
            <input class="round-button blue" type="button" value="Salva" id="policy-form-submit"/>
        <br/>
            <#include "../helpers/permission-legend.ftl"/>
        </form>
    </fieldset>
</div>