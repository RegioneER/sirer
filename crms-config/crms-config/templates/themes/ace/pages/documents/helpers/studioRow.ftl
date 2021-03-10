<#assign deletable=true>
<td><a href="${detailLink}">${element.getfieldData("UniqueIdStudio","id")[0]!""}</a></td>
<td><a href="${detailLink}">${element.getfieldData("IDstudio","CodiceProt")[0]!""}</a></td>
<td><a href="${detailLink}">${element.getfieldData("IDstudio","TitoloProt")[0]!""}</a></td>
<td><#if element.getfieldData("datiPromotore","promotore")?size gt 0>${element.getfieldData("datiPromotore","promotore")[0].getfieldData("DatiPromotoreCRO","denominazione")[0]}</#if></td>
<td><#assign piList=element.getChildrenByType("Centro") ><#if (piList?? && piList?size gt 0 )><ul style="padding:5px;"><#list piList as piItem>
<#if (piItem.getfieldData("ValiditaCTC","val")?? && (piItem.getfieldData("ValiditaCTC","val")?size gt 0))>
<#assign deletable=false>
</#if>
<li style="white-space:nowrap;list-style: none;padding-top:3px;">${piItem.getFieldDataDecode("IdCentro","PINomeCognome")}</li>
</#list></ul></#if></td>
<td><#if (deletable && element.getUserPolicy(userDetails).isCanDelete())><a href="#" onclick="if(confirm('Sei sicuro di voler eliminare lo studio?')) {deleteElement('${element.getId()}')};return false;" > <img width="30px" height="30px" src="/img/trash.png" alt="Elimina"></a></#if></td>