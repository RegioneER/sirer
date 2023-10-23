
<li style="background-color: #3F437E; !important">
	<a style="background-color: #3F437E; !important" data-toggle="dropdown" class="dropdown-toggle" href="#">
		<i class="icon-plus"></i>
		<span class="topbar-button-text hidden-900"><@msg "system.add_shortcut"/></span>
		<i class="icon-caret-down"></i>
	</a>

	<ul class="pull-right dropdown-navbar dropdown-menu dropdown-caret dropdown-close">
		<li class="dropdown-header">
			<@msg "system.add_shortcut"/>
			<span class="help-button" data-rel="tooltip" data-trigger="hover" data-placement="left"  title="Menu degli oggetti registrabili nel servizio">?</span>
		</li>

		<#list layout._topbar_actions.list as action >
		<#if action.title!="type.reports">
		<li>
			<a href="${action.link}" class="no-hover dark-blue" >
			<div class="clearfix">
			<span class="pull-left">
					<i class="no-hover ${action.icon}"></i> ${action.title}</span>
					
			</div>
			</a>
		</li>
		</#if>
		</#list>
		<li>
			
		</li>
		
	</ul>
</li>
