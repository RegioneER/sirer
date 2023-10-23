<#assign budget=el />
<#assign center=el.getParent() />
<#assign tabs=[] />
<#assign tabsContent=[] />
<#include "../helpers/MetadataTemplate.ftl"/>
<#assign budgetStudio=budget.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0] />
<#assign elementJson=el.getElementCoreJsonToString(userDetails) />
<#assign budgetJson=budget.getElementCoreJsonToString(userDetails) />
<#assign budgetStudioJson=budgetStudio.getElementCoreJsonToString(userDetails) />
<#assign readonly=false />
<#if el.getFieldDataString("ChiusuraBudget","Chiuso")?? && el.getFieldDataString("ChiusuraBudget","Chiuso")=="1">
    <#assign readonly=true />
</#if>
<@script>
var elementId=${el.id};
var centroId=${el.getParent().id};
var baseUrl='${baseUrl}';
var folderPrestazioniId=${el.getChildrenByType('FolderPrestazioni')[0].id};
var folderBudgetStudioId=${el.getChildrenByType('FolderBudgetStudio')[0].id};
var folderBudgetStudio=folderBudgetStudioId;
var folderCostiAggiuntivi=${el.getChildrenByType('FolderPrestazioni')[0].id};
var budgetStudioId=${el.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0].id};
var folderBudgetStudioTypeId=${el.getChildrenByType('FolderBudgetStudio')[0].type.id};
var folderTimePointId=${el.getChildrenByType('FolderTimePoint')[0].id};
var folderTpxpId=${el.getChildrenByType('FolderTpxp')[0].id};
var budgetReadonly=${readonly?c};
var budgetChiuso=-1;
<#if el.getFieldDataString("ChiusuraBudget","Chiuso")?? && el.getFieldDataString("ChiusuraBudget","Chiuso")!="">
budgetChiuso=${el.getFieldDataString("ChiusuraBudget","Chiuso")};
</#if>

</@script>
<div class="row">
    <div class="col-xs-9">
        <div style="text-align:right">
            <#if !readonly >
                <button class="btn btn-primary" id="clona"  onclick="openClone(${el.id},true);"><i class="icon-copy"></i> Copia</button>
                <!--button class="btn btn-primary" id="clona_altro_centro"  onclick="openCloneOtherStudy(${el.id},true);"><i class="icon-copy"></i> Copia budget in altro centro</button-->
            </#if>
            <#include "../helpers/budget/bracciFormView.ftl"/>
            <#include "../helpers/budgetActions.ftl"/>
            <#assign approvazione=budget.getChildrenByType("FolderApprovazione") />
            <#if approvazione?? && (approvazione?size > 0) >
                <#assign approvazioneDetails=approvazione[0].getChildren() />
                <#if !(approvazioneDetails?? && (approvazioneDetails?size > 0)) >
                    <button class="btn btn-primary" id="clona"  onclick="inviaServizi(${el.id},true);">Invia ai servizi</button>
                </#if>
            </#if>

</div>

<div style="display: block">



    <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
    <div id="tabs" class="tabbable">
        <ul style='height:27px'  class="nav nav-tabs">
            <!-- li><a id='tab0' href="#tabs-0" data-toggle="tab" >Gruppi di prestazioni</a></li -->
            <!--li><a id='tab1' href="#tabs-1" data-toggle="tab" >Flowchart</a></li-->
            <li><a id='tab4' href="#tabs-4" data-toggle="tab" >Prestazioni/Servizi aggiuntivi</a></li>
            <li><a id='tab5' href="#tabs-5" data-toggle="tab" >Grant / Finanziamento</a></li>
            <li><a id='tab6' href="#tabs-6" data-toggle="tab" >Controllo versioni</a></li>
        </ul>
        <div  class="tab-content" >
            <#-- include "../helpers/budgetRefactoring/tab0.ftl" / -->
            <#-- include "../helpers/budgetRefactoring/tab1.ftl" / -->
            <#include "../helpers/budgetRefactoring/tab4.ftl"/>
            <#assign canCopyStudio=false />
            <#include "../helpers/budgetRefactoring/tab5.ftl"/>
            <#include "../helpers/budgetRefactoring/tab6.ftl" />
        </div>
    </div>
    <#include "../helpers/budget/cloneForms.ftl"/>
</div>
</div>
<#include "../helpers/budgetStatusBar.ftl"/>
</div>


