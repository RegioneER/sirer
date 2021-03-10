{foreach from=$startNode item=element}
	{if $elpath==""}
		{capture assign=thispath}{$elpath}{$element.name}{/capture}
	{else}
		{capture assign=thispath}{$elpath}.{$element.name}{/capture}
	{/if}
	{assign var=idx value=$idx+1 scope="root"}
	<li id="unique_el_list_{$idx}">
	<span  data-caret-container="true" data-caret-container-element="unique_el_list_detail_{$idx}">Elemento: <b>{$element.name}</b></span> 
    <a {if !$expoloded }style="display: ;"{/if} href="#" data-caret="down" data-rel="unique_el_list_detail_{$idx}"><i class="fa fa-chevron-down"></i></a>
    <a {if !$expoloded }style="display: none;"{/if} href="#" data-caret="up" data-rel="unique_el_list_detail_{$idx}"><i class="fa fa-chevron-up"></i></a>
    <ul>
  	<div id="unique_el_list_detail_{$idx}" {if !$expoloded }style="display: none;"{/if} >
    											
   		{if !empty($element.fields)}
   			<b href="#" data-caret-container="true" data-caret-container-element="unique_el_list_detail_fields_{$idx}">Campi</b>
   			<a href="#" data-caret="down" data-rel="unique_el_list_detail_fields_{$idx}"><i class="fa fa-chevron-down"></i></a>
  			<a style="display: none;" href="#" data-caret="up" data-rel="unique_el_list_detail_fields_{$idx}"><i class="fa fa-chevron-up"></i></a>
   			<ul id="unique_el_list_detail_fields_{$idx}" style="display: none;">
			{foreach from=$element.fields key=template item=fields}
				<li>
					<span data-caret-container="true" data-caret-container-element="unique_el_list_detail_fields_{$idx}_{$template}">
					{$template}</span>
					<a href="#" data-caret="down" data-rel="unique_el_list_detail_fields_{$idx}_{$template}"><i class="fa fa-chevron-down"></i></a>
  					<a style="display: none;" href="#" data-caret="up" data-rel="unique_el_list_detail_fields_{$idx}_{$template}"><i class="fa fa-chevron-up"></i></a>
   					<ul id="unique_el_list_detail_fields_{$idx}_{$template}" style="display: none;">
					{foreach from=$fields item=$field}
						<li>
							{$field.name}
							{if $field.type=='ELEMENT_LINK'}
								<label>
									<input name="fields[]" class="ace field_linked" type="checkbox" data-elpath="{$thispath}" data-elTypeName="{$element.name}" data-templateName="{$template}" data-fieldName="{$field.name}" value="{$thispath}_{$template}.{$field.name}">
									<span class="lbl"></span>
								</label>
								collegamento a elemento di tipo {$element.name}
								<ul id="nested_el{$idx}{$template}_{$field.name}" data-idx="{$thispath}_{$template}.{$field.name}"></ul>
							{else}
								<label>
									<input name="fields[]" class="ace field_check" type="checkbox" value="{$thispath}_{$template}.{$field.name}">
									<span class="lbl"></span>
								</label>
								<input type="textbox" name="{$thispath}_{$template}.{$field.name}" placeholder="nome colonna ..." size="20" disabled/>
							{/if}
						</li>
					{/foreach}
					</ul>
				</li>
			{/foreach}   
			</ul>
			<br/>
			{/if}
   			{if !empty($element.children)}
   			<b href="#" data-caret-container="true" data-caret-container-element="unique_el_list_detail_children_{$idx}">Figli</b>
   			<a style="display: none;" href="#" data-caret="down" data-rel="unique_el_list_detail_children_{$idx}"><i class="fa fa-chevron-down"></i></a>
  			<a  href="#" data-caret="up" data-rel="unique_el_list_detail_children_{$idx}"><i class="fa fa-chevron-up"></i></a>
  	 		<ul id="unique_el_list_detail_children_{$idx}" style="display: ;">{include file="recursive-struct.tpl" startNode=$element.children exploded=false elpath=$thispath}</ul>
  		{/if}
  	</div>
   	</ul>
   </li>

{/foreach}