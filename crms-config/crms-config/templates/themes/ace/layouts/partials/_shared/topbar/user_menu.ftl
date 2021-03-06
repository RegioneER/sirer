<li>
	<a data-toggle="dropdown" href="#" class="dropdown-toggle">
		<i class="icon-large icon-user" title="User menu" ></i>
		<#assign dmSessionActive=false>
		<#if model['requestCookies']??>
		<#assign keys = model['requestCookies']?keys>
	    <#list keys as key>
	      <#if key=="xcdm.dm.session">
	       <#assign dmSessionActive=true>
	      </#if>
		</#list>
		</#if>
		<@security.authorize ifAnyGranted="DATAMANAGER">
            <#if dmSessionActive>
                <i class="red fa fa-2x fa-exclamation-circle" title="Data Management Session active" ></i>
            </#if>
        </@security.authorize>
		<span class="user-info" title="${user.name}">
			${user.name!}<br/>${getUserGroups(userDetails)}<small></small> 
		</span>
		<i class="icon-caret-down"></i>
	</a>
	<ul class="user-menu pull-right dropdown-menu dropdown-yellow dropdown-caret dropdown-close">
		<@security.authorize ifAnyGranted="tech-admin"> 
		<li><a href="${baseUrl}/app/admin"><i class="icon-cog"></i> Settings</a></li>
		<li class="divider"></li>
		</@security.authorize>
		<@security.authorize ifAnyGranted="DATAMANAGER">
			<#if dmSessionActive>
		    	<li><a href="${baseUrl}/app/documents/dm/session"><i class="icon-edit"></i> Data Management session details</a></li>
		    	<#if el??>
		    	<li><a href="${baseUrl}/app/documents/dm/edit/${el.id}"><i class="icon-edit"></i> Edit Element</a></li>
				</#if>
			<#else>
				<li><a href="#" id="dmsession-start"><i class="icon-edit"></i> Start Data Management session</a></li>
			</#if>
	    </@security.authorize>
		<#if el??>
		<#if templates?? && templates?size gt 1>
			<li class="divider"></li>
			<#assign keys = templates?keys>
		    <#list keys as key>
		    	<#if key!=selectedTemplate>
					<li><a href="${baseUrl}/app/documents/detail/${el.id}?t=${key}"><i class="icon-eye-open"></i>
					 <@msg "ftl."+elType.typeId+"."+key/></a></li>    	
		    	</#if>
		    </#list>
		</#if>
		</#if>
		</li>
		<li><a href="/change_password"><i class="icon-key"></i> Cambio password</a></li>
		<li><a href="/ShibLogOut"><i class="icon-off"></i> Logout</a></li>
	</ul>
</li>


<@script>

$('#dmsession-start').click(function(){
	bootbox.dialog({
  		message: "Codice issue: <input type='text' id='dm-issueCode' size='40'><br/>Commento:<br/><textarea cols='48' id='dm-comment'></textarea>",
  		title: "Crea nuova sessione di data-management",
  		 buttons: {
		    success: {
		      label: "Crea sessione",
		      className: "btn-success",
		      callback: function() {
		      	$.post( "${baseUrl}/app/rest/dm/startSession", { comment: $('#dm-comment').val(), issueCode: $('#dm-issueCode').val() })
		      		.done(function( data ) {
				    	window.location.reload();
				 	}); 
		      }
      	},
		      cancel: {
		      	label: "Annulla",
		      	className: "btn-cancel"
		      }
      }
});
	return false;
});


</@script>