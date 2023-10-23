
<#assign dmSession=model['dmsession']/>

<h2>Data Management Session: ${dmSession.id}</h2>
Issue Code:&nbsp;
<#if dmSession.endDt??>
<b>${dmSession.issueCode!"n.d."}</b>
<#else>
<input type="text" data-name='issueCode' data-type="editable-fields" value="${dmSession.issueCode!"n.d."}"/>
<span data-ref='issueCode' class='status'></span>
</#if>
<br/>
Commento:&nbsp;
<#if dmSession.endDt??>
<b>${dmSession.comment!"n.d."}</b>
<#else>
<textarea data-name='comment' data-type="editable-fields">${dmSession.comment!"n.d."}</textarea>
<span data-ref='comment' class='status'></span>
</#if>
<br/>
Creata il ${dmSession.startDt.time?date?string["dd/MM/yyyy HH:mm"]}<br>
<#if dmSession.endDt??>
Chiusa il ${dmSession.endDt.time?date?string["dd/MM/yyyy HH:mm"]}<br>
</#if>

<#if !dmSession.endDt??>

<button class='dm-close btn btn-xs btn-info'><i class='fa fa-save'></i>&nbsp;Chiudi sessione</button>
<button class='dm-batch btn btn-xs btn-info'><i class='fa fa-gear'></i>&nbsp;Esegui aggiornamenti batch</button>
</#if>
<div id="myTab">
    <div class="tabbable">
        <ul id="templatesNavTab" class="nav nav-tabs">
        </ul>
        <div id="templatesTabContent"  class="tab-content">
        </div> <!--tab-content-->
    </div> <!--tabbable-->
</div>
