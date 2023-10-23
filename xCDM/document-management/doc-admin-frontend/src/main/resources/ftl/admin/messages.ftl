<script>

$(document).ready(function(){
	 $('.updateProp').change(function(){
             loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
             var formData=new FormData();
             var actionUrl="${baseUrl}/app/rest/admin/messages/it_IT";
             formData.append("propName", $(this).attr('name'));
             formData.append("value", $(this).val());
             $.ajax({
                 type: "POST",
                 url: actionUrl,
                 contentType:false,
                 processData:false,
                 async:false,
                 cache:false,
                 data: formData,
                 success: function(obj){
                     if (obj.result=="OK") {
                         loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",500);
                         if (obj.redirect){
                             window.location.href=obj.redirect;
                         }
                     }else {
                         loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 2000);
                     }
                 },
                 error: function(){
                     loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 2000);
                 }
             });
         });

});


</script>
<div class="admin-home-main">
<#assign showedLabel={}/>
<#assign props=model['props']/>
<table class="propTable">
	<tr>
		<th colspan="3">Tipologie</th>
	</tr>
<#list model['elTypes'] as type>
    <tr>
    		<th colspan="2">${type.typeId}</th>
    </tr>
	<tr>
		<td>${type.typeId}</td>
		<td><input type="textbox" size=100 name="type.${type.typeId}" class="updateProp" value="${model['props']['type.${type.typeId}']!""}">
		<#assign showedLabel=showedLabel+{"type.${type.typeId}":true}/>
	</td>
	</tr>
	<tr>
    	<td>${type.typeId}</td>
    		<td><input type="textbox" size=100 name="type.create.${type.typeId}" class="updateProp" value="${model['props']['type.create.${type.typeId}']!""}">
    		<#assign showedLabel=showedLabel+{"type.create.${type.typeId}":true}/>
    	</td>
    	</tr>
		<#list type.getFtlTemplates() as typeFtl >
		 <tr>
		 <td>${typeFtl}</td>
         		<td><input type="textbox" size=100 name="${type.typeId}.ftl.${typeFtl}" class="updateProp" value="${model['props']['${type.typeId}.ftl.${typeFtl}']!""}">
         		<#assign showedLabel=showedLabel+{"${type.typeId}.ftl.${typeFtl}":true}/>
         </td>
         </tr>
		</#list>

</#list>
	
<#list model['templates'] as template>
	<tr>
		<th colspan="2">Template metadati: ${template.name}</th>
	</tr>
	<tr>	
		<td>nome template</td>
		<td><input type="textbox" size=100 name="template.${template.name}" class="updateProp" value="${model['props']['template.${template.name}']!""}">
		<#assign showedLabel=showedLabel+{"template.${template.name}":true}/>
	</td>
	</tr>
	<#list template.fields as field>
	<tr>
		<td>${template.name}.${field.name}</td>
		<td><input type="textbox" size=100 name="${template.name}.${field.name}" class="updateProp" value="${model['props']['${template.name}.${field.name}']!""}">
		<#assign showedLabel=showedLabel+{"${template.name}.${field.name}":true}/>
		</td>
	</tr>	
	</#list>
</#list>
<tr>
		<th colspan="2">Generali</th>
	</tr>


<#list props?keys as prop>
	<#if showedLabel[prop]?? && showedLabel[prop]>
	<#else>
	<tr>
		<td>${prop}</td>
		<td><input type="textbox" size=100 name="${prop}" class="updateProp" value="${model['props'][prop]!""}">
		</td>
	</tr>	
	</#if>
</#list>
</table>
</div>