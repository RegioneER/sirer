<li style="background-color: #011e62; !important">
	<a data-toggle="dropdown" class="dropdown-toggle" href="#">
		<i class="icon-bell-alt icon-animated-bell"></i>
		<span class="badge badge-important">${layout._topbar_notifications.count}</span>
	</a>
	<ul class="pull-right dropdown-navbar navbar-pink dropdown-menu dropdown-caret dropdown-close">
		<li class="dropdown-header">
			<i class="icon-warning-sign"></i> ${layout._topbar_notifications.count} Notifications
		</li>

		<#list layout._topbar_notifications.latest as notification >
		<li>
			<a href="#">
				<#if notification.badge?? >
				<div class="clearfix">
					<span class="pull-left"><i class="btn btn-xs no-hover ${notification.icon_class} ${notification.icon}"></i> ${notification.title}</span>
					<span class="pull-right badge ${notification.badge_class}">${notification.badge}</span>					
				</div>
				<#else>
					<i class="btn btn-xs ${notification.icon_class} ${notification.icon}"></i> ${notification.title}
				</#if>
			</a>
		</li>
		</#list>

		<li>
			<a href="#">
				See all notifications
				<i class="icon-arrow-right"></i>
			</a>
		</li>
	</ul>
</li>