<#assign showedLabel={}/>
<#assign props=model['props']/>
<div class="mainContent">
<div class="documentMainContent">
     <div class="page-header">
		<h1>Localizzazione</h1>
	</div>
	<div class="tabbable">
		<ul id="myTab4" class="nav nav-tabs padding-12 tab-color-blue background-blue">
			<li class="active">
				<a href="#types" data-toggle="tab">Tipologie</a>
			</li>
			<li>
				<a href="#template" data-toggle="tab">Template metadati</a>
			</li>
			<li>
				<a href="#generali" data-toggle="tab">Generali</a>
			</li>
		</ul>
		<div class="tab-content">
			<div id="types" class="tab-pane in active">
				<form class="form-horizontal">
				<div class="panel panel-default">
					<#list model['elTypes'] as type>
						<div class="panel-heading">
							<h4 class="panel-title">
								<a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion" href="#${type.typeId}_TYPE_panel">
									<i class="icon-angle-down bigger-110" data-icon-hide="icon-angle-down" data-icon-show="icon-angle-right"></i>
									&nbsp;${type.typeId}
								</a>
							</h4>
						</div>
						<div class="panel-collapse collapse" id="${type.typeId}_TYPE_panel">
							<div class="panel-body">
								 <div class="form-group">
							    	<label class="col-sm-3 control-label no-padding-right" for="id_type_${type.typeId}">${type.typeId}</label>
									<div class="col-sm-9">
									<span class="input-icon">
										<input type="text" id="id_type_${type.typeId}" name="type.${type.typeId}" class="updateProp" value="${model['props']['type.${type.typeId}']!""}"/>
										<i id="icon_id_type_${type.typeId}"></i>
									</span>
									</div>
									<#assign showedLabel=showedLabel+{"type.${type.typeId}":true}/>
								</div>
								<div class="form-group">
							    	<label class="col-sm-3 control-label no-padding-right" for="id_type_create_${type.typeId}">${type.typeId}</label>
							    	<div class="col-sm-9">
							    		<span class="input-icon">
							    		<input type="text" id="id_type_create_${type.typeId}" name="type.create.${type.typeId}" class="updateProp" value="${model['props']['type.create.${type.typeId}']!""}"/>
							    		<#assign showedLabel=showedLabel+{"type.create.${type.typeId}":true}/>
							    			<i id="icon_id_type_create_${type.typeId}"></i>
							    		</span>
							    	</div>
							    </div>
							<#list type.getFtlTemplates() as typeFtl >
								<div class="form-group">
							    	<label class="col-sm-3 control-label no-padding-right" for="id_${type.typeId}_ftl_${typeFtl}">${typeFtl}</label>
							       	<div class="col-sm-9">
							       		<span class="input-icon">
							    		<input type="text" id="id_${type.typeId}_ftl_${typeFtl}" name="${type.typeId}.ftl.${typeFtl}" class="updateProp" value="${model['props']['${type.typeId}.ftl.${typeFtl}']!""}"/>
							        	<#assign showedLabel=showedLabel+{"${type.typeId}.ftl.${typeFtl}":true}/>
							        	<i id="icon_id_${type.typeId}_ftl_${typeFtl}"></i>
							        	</span>
							        </div>
							    </div>	
						    </#list>
						</div>
					</div>
					</#list>
				</div>
			</form>	
			</div>
			<div id="template" class="tab-pane">
				<form class="form-horizontal">
					<div class="panel panel-default">
					<#list model['templates'] as template>
						<div class="panel-heading">
							<h4 class="panel-title">
								<a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion" href="#${template.name}_panel">
									<i class="icon-angle-down bigger-110" data-icon-hide="icon-angle-down" data-icon-show="icon-angle-right"></i>
									&nbsp;${template.name}
								</a>
							</h4>
						</div>
						<div class="panel-collapse collapse" id="${template.name}_panel">
							 <div class="form-group">
							    	<label class="col-sm-3 control-label no-padding-right" for="id_template_${template.name}">Nome template</label>
									<div class="col-sm-9">
										<span class="input-icon">
											<input type="text" id="id_template_${template.name}" name="template.${template.name}" class="updateProp" value="${model['props']['template.${template.name}']!""}"/>
											<i id="icon_id_template_${template.name}"></i>
										<span>
									</div>
									<#assign showedLabel=showedLabel+{"template.${template.name}":true}/>
								</div>
						
						
						<#list template.fields as field>
						<div class="form-group">
						   	<label class="col-sm-3 control-label no-padding-right" for="id_${template.name}_${field.name}">${template.name}.${field.name}</label>
							<div class="col-sm-9">
								<span class="input-icon">
								<input type="text" id="id_${template.name}_${field.name}" name="${template.name}.${field.name}" class="updateProp" value="${model['props']['${template.name}.${field.name}']!""}"/>
								<i id="icon_id_${template.name}_${field.name}"></i>
								</span>
							</div>
							<#assign showedLabel=showedLabel+{"${template.name}.${field.name}":true}/>
						</div>	
						</#list>
						</div>
					</#list>
					</div>
				</form>	            	
			</div>
			<div id="generali" class="tab-pane">
				<form class="form-horizontal">
						<#list props?keys as prop>
							<#if showedLabel[prop]?? && showedLabel[prop]>
							<#else>
							<div class="form-group">
							   	<label class="col-sm-3 control-label no-padding-right" for="id.${prop}">${prop}</label>
								<div class="col-sm-9">
									<span class="input-icon">
										<input type="text" id="id_${prop?replace(".", "_")}" name="${prop}" class="updateProp" value="${model['props'][prop]!""}"/>
										<i id="icon_id_${prop?replace(".", "_")}"></i>
									</span>
								</div>
							</div>	
							</#if>
						</#list>
					</div>
				</form>
			</div>
		</div>
	</div>