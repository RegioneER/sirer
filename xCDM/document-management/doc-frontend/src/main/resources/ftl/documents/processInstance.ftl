<#assign pInst=model["pInst"]/>
<#assign pLogs=model["pLogs"]/>
<#assign el=model["element"]/>

<script type="text/javascript" src="${baseUrl}/int/js/storyjs-embed.js"></script>
<script>

storyjs_jsonp_data = {
    "timeline":
    {
        "headline":"Dettagli processo ${pInst.definition.name}",
        "text":"Processo ${pInst.definition.name} avviato <b>${pInst.startDT.time?datetime?string.medium}</b> da <b>${pInst.startedBy}</b><br/>"+
                "Stato corrente: <b>${pInst.currentStep.name}</b>",
        "type":"default",
        "startDate":"${pInst.startDT.time?datetime?string("yyyy,dd,MM,HH,mm,ss")}",
        "date": [
        <#list pLogs as log>
            {
            <#assign title=""/>
                <#assign description=""/>
                <#if log.step??>
                    <#assign title="Step: "+log.step.currentStep.name/>
                    <#if log.step.assignees??>
                        <#assign description=description+"<ul>Utente abilitati: <b>"/>
                        <#list log.step.assignees as assignee>
                            <#assign description=description+"<br>&nbsp;<b>"+assignee.username+"</b>"/>
                        </#list>
                    </#if>
                <#else>
                    <#assign title="Transizione: "+log.flow.flow.name/>
                    <#if log.flow.data??>
                        <#list log.flow.data as data>
                            <#assign description=description+"<ul>Utente: <b>"+data.assignee+"</b>"/>
                            <#if data.fields??>
                                <#list data.fields as field>
                                    <#assign vals=field.getVals()/>
                                    <#assign labelId=pInst.definition.name+"."+field.field.name/>
                                    <#assign label=messages[labelId]!labelId/>
                                    <#assign value=viewData(field.field.type, vals)/>
                                    <#assign description=description+"<br>&nbsp;"+label+":&nbsp;<b>"+value+"</b>"/>

                                </#list>
                            </#if>
                            <#assign description=description+"</ul>"/>
                        </#list>
                    </#if>

                </#if>
                "startDate":"${log.logDT.time?datetime?string("yyyy,dd,MM,HH,mm,ss")}",
                "endDate":"${log.logDT.time?datetime?string("yyyy,dd,MM,HH,mm,ss")}",
                "headline":"${title}",
                "text":"<p>${description?js_string}</p><img style='width:800px' src='${baseUrl}/app/documents/${el.id}/graph/${pInst.id}/${log.id}'>"
            }
            <#if log!=pLogs?last>,</#if>
        </#list>
        ]
    }
}

$(document).ready(function() {
    createStoryJS({
        type:		'timeline',
        width:		'1000',
        height:		'600',
        source:		storyjs_jsonp_data,
        embed_id:	'my-timeline',
        debug:		true
    });
});
</script>

<div class="mainContent">

<span class="info-detail">
    Creato <b>${el.creationDt.time?datetime?string.full}</b> da <b>${el.createUser}</b>
<#if el.lastUpdateUser??>
    <br/>Ultima modifica di <b>${el.lastUpdateDt.time?datetime?string.full}</b> da <b>${el.lastUpdateUser}</b>
</#if>
</span>
    <h1 class="element-title"><@breadCrumb el/><img width="30px" src="${el.type.imageBase64!}"/><a href="${baseUrl}/app/documents/detail/${el.id}">
    <#if el.type.titleField??>
        <b><@printMetadata el.type.titleField el/>
    </#if></a>
        &gt;Processo ${pInst.definition.name} n.ro ${pInst.id}</h1>

    <fieldset>
    <legend>Processo ${pInst.definition.name} n.ro ${pInst.id}</legend>
        <div id="my-timeline"></div>
      </fieldset>
</div>