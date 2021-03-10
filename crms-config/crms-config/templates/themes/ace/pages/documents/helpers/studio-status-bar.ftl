<div  class="col-xs-3 sidebar-right">
	<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
	<i class="icon-chevron-right bigger-150"></i>
	</div>	
<div class=" status-bar-content">
		<div class="col-xs-12 status-bar">
				<h2>Informazioni</h2>
				<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
					<#if userDetails.getEmeSessionId()??>
						<@TemplateFormFastUpdate "IDstudio" el userDetails editable true/>
					<#else>
						<@TemplateFormFastUpdate "IDstudio" el userDetails editable false/>
					</#if>
					<#--@TemplateFormFastUpdate "UniqueIdStudio" el userDetails editable/-->
  			</#if>
		</div>


<#if userDetails.getEmeSessionId()?? >
	<#assign objEme = (el?? && el.getInEmendamento()) />
	<#assign parentEme = (el?? && el.parent?? && userDetails.getEmeRootElementId()?? && userDetails.getEmeRootElementId() = el.parent.getId()) />
	<!-- OBJEME: ${objEme?string} - PARENTEME ${parentEme?string} -->
	<#if (objEme || parentEme) >
	<div class="col-sm-12" style="clear:both;">
		<div id="quarantena" class="alert alert-block alert-danger" style="min-height:50px;">
				<i class="fa fa-exclamation-circle red"></i> <a style="text-decoration:none;" onclick="" href="#"><span style="float:left;" >&nbsp;Emendamento in corso, id: ${userDetails.getEmeSessionId()}<br></span></a>
				<br/>
				<button title="Disattiva modifiche" class="btn btn-info btn-xs" style="margin-top:0px" onclick="
												$.ajax({
													method : 'GET',
													url : baseUrl+'/app/rest/documents/emendamento/deactivate'
												}).done(function() {
													window.location.reload();
												});" > <i class="icon icon-eraser"></i>Disattiva modifiche</button>
		</div>
	</div>
	<#else>
	<!-- Sessione emendamento attiva su altro studio.<br/> -->
	</#if>
	
</#if>


<!--div class="col-xs-12 status-bar">
<div class="row">
									<div class="col-sm-12">
										<div class="widget-box transparent">
											<div class="widget-header widget-header-flat">
												<h4 class="lighter">
													Stato Centri
												</h4>

												<div class="widget-toolbar">
													<a href="#" data-action="collapse">
														<i class="icon-chevron-up"></i>
													</a>
												</div>
											</div>

											<div class="widget-body">
												<div class="widget-main no-padding">
													<table class="table table-bordered table-striped">
														<thead class="thin-border-bottom">
															<tr>
																<th>
																	<i class="icon-caret-right blue"></i>
																	PI
																</th>

																<#--th>
																	<i class="icon-caret-right blue"></i>
																	price
																</th-->

																<th class="hidden-480">
																	<i class="icon-caret-right blue"></i>
																	Stato
																</th>
															</tr>
														</thead>

														<tbody>
															
															<#list el.getChildrenByType("Centro") as elCentro>
															
															<#assign status ="" />
															<#assign status1="" />
															<#assign status2="" />
															<#assign status3="" />
															
															<#if elCentro.getfieldData("statoValidazioneCentro", "idBudgetApproved")?? && elCentro.getfieldData("statoValidazioneCentro", "idBudgetApproved")?size gt 0>
																<#assign status1="<span class='label label-danger'>Budget</span>" />
															</#if>
															
															<#if elCentro.getfieldData("statoValidazioneCentro","fattLocale")?? && elCentro.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0>
																<#if elCentro.getFieldDataCode("statoValidazioneCentro","fattLocale")="1">
																	<#assign status2="<span class='label label-info'>Fatt. PI</span>"/>
																</#if>
																<#if elCentro.getFieldDataCode("statoValidazioneCentro","fattLocale")="2">
																	<#assign status2="<span class='label label-danger'>Fatt. PI negativa</span>"/>
																</#if>
															</#if>
															
															<#if elCentro.getfieldData("statoValidazioneCentro","valCTC")?? && elCentro.getfieldData("statoValidazioneCentro","valCTC")?size gt 0 && elCentro.getFieldDataCode("statoValidazioneCentro","valCTC")="1">
																<#assign status3="<span class='label label-success'>Valutazione CTO/TFA</span>" />
															</#if>
															
															<#if status1="" && status2="" && status3="">
																<#assign status="<span class='label label-warning'>Pending</span>"/>
															</#if>
															<#if status3!="">
																<#assign status1="" />
																<#assign status2="" />	
															</#if>
															
															<tr>
																<td>${elCentro.getFieldDataDecode("IdCentro","PI")}</td>
																<td class='hidden-480'>
																${status}
																${status1}
																${status2}
																${status3}
																</td>
															</#list>

															
																
															</tr>
														</tbody>
													</table>
												</div><!-- /widget-main -->
											</div><!-- /widget-body -->
										</div><!-- /widget-box -->
									</div>
		</div>
											</div>
		</div -->