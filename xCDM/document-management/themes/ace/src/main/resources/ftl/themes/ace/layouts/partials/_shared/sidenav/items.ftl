<li <#if item.class?? > class="${item.class}"</#if> ><#-- print class name (active, open, etc) if it exists -->
  <a <#if item.id??>id="${item.id}"</#if> <#if item.target??>target="${item.target}"</#if> href="<#if item.link?? ><@createLinkFunction item.link /><#else>#</#if>"<#if item.submenu?? > class="dropdown-toggle"</#if>>
	<#if (item.icon?? && item.icon.icon?? &&  item.icon.icon!="")><i class="${item.icon.icon}"></i></#if>
	<#if item.level_1?? >
	 <span class="menu-text">
	</#if>

	 <#if item.level_2?? ><#-- if level-2 and no icon assigned, use this icon-->
		<#if (!item.icon?? || !item.icon.icon?? ||  item.icon.icon=="" ) ><i class="icon-double-angle-right"></i></#if>
	 </#if>

	  ${item.icon.title}
	  <#if item.badge?? > 
			<span class="badge ${item.badge_class} ${item.tooltip_class}"<#if item.tooltip?? > title="${item.tooltip}"</#if>>${item.badge}</span>
	  </#if>
	  <#if item.label?? >
			<span class="label ${item.label_class}"<#if item.label_title?? > title="${item.label_title}"</#if>>${item.label}</span>
	  </#if>
	<#if item.level_1?? >
	 </span>
	</#if>

	<#if item.submenu?? ><b class="arrow icon-angle-down"></b></#if>
  </a>
  
  <#if item.submenu?? ><#-- if we have submenu items, print them recursively -->
  	<#assign submenu=[]+item.submenu />
	<ul class="submenu">
	<#list submenu as newItem >
	<#global item=newItem />
		<@includeLayout layout._sidenav.items />
	</#list>
	</ul>
	
  </#if>
</li>