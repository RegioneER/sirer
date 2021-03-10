<#if layout._topbar_messages.count gt 0 >
<li class="green">
	<a data-toggle="dropdown" class="dropdown-toggle" href="#">
		<i class="icon-envelope<#if layout._topbar_messages.count gt 0 > icon-animated-vertical</#if>"></i>
		<#if layout._topbar_messages.count gt 0 ><span class="badge badge-success">${layout._topbar_messages.count}</span></#if>
	</a>
	<ul class="pull-right dropdown-navbar dropdown-menu dropdown-caret dropdown-close">
		<li class="dropdown-header">
			<i class="icon-envelope-alt"></i> ${layout._topbar_messages.count} Messages
		</li>
		
		<#list layout._topbar_messages.latest as message >
		<li>
			<a href="#">
				<img src="${path.assets}/avatars/${message.img}" class="msg-photo" alt="${message.name}'s Avatar">
				<span class="msg-body">
					<span class="msg-title">
						<span class="blue">${message.name}:</span>
						${message.summary}
					</span>
					<span class="msg-time">
						<i class="icon-time"></i> <span>${message.time}</span>
					</span>
				</span>
			</a>
		</li>
		</#list>
		
		<li>
			<a href="<@createLinkFunction inbox />">
				See all messages
				<i class="icon-arrow-right"></i>
			</a>
		</li>

	</ul>
</li>
</#if>