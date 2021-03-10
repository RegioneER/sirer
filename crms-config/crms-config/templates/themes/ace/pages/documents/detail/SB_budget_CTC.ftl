<#assign budget=el />
<#assign budgetBase=el.getParent().getParent() />
<#assign center=el.getParent() />
<#assign tabs=[] />
<#assign tabsContent=[] />
<#include "../helpers/MetadataTemplate.ftl"/>
<div class="row">
    <div class="col-xs-9">
        <div style="text-align:right">

            <!--button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button-->
            <button class="btn btn-primary" id="clona"  onclick="openClone(${el.id},true);"><i class="icon-copy"></i> Copia</button>
            <button class="btn btn-primary" id="clona_altro_centro"  onclick="openCloneOtherStudy(${el.id},true);"><i class="icon-copy"></i> Copia budget in altro centro</button>
            <button class="btn btn-primary" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.parent.parent.id}';"> Torna al budget complessivo</button>
            <#--button class="btn btn-primary" id="nuovo" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.getParent().id}/${elType.id}';" >Crea nuovo budget</button-->
            <#--include "../helpers/budget/bracciForm.ftl"/-->
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
            <li><a id='tab1' href="#tabs-1" data-toggle="tab" >Flowchart</a></li>
            <li><a id='tab4' href="#tabs-4" data-toggle="tab" >Budget PI/Servizi</a></li>
            <li><a id='tab6' href="#tabs-6" data-toggle="tab" >Bracci</a></li>
        </ul>
        <div  class="tab-content" >
            <div id="tabs-6" class="tab-pane">
                <#assign allBudgets=el.getParent().getChildren() />
                <#include "../helpers/budget/tabellaVersioni.ftl"/>
            </div>
            <#include "../helpers/budgetRefactoring/tab1.ftl" />
            <#include "../helpers/budgetRefactoring/tab4-bb.ftl"/>
        </div>
    </div>


    <#include "../helpers/budget/cloneForms3.ftl"/>

</div>

</div>
<#include "../helpers/budgetStatusBar.ftl"/>
</div>