<h1>Edit reports</h1>
<div class="col-sm-6">
	<div class="dd dd-draghandle">
		<ol class="dd-list" id="reportsArea-list">
		<!--
			<li class="dd-item dd2-item" data-id="1" data-group="1">
				<div class="dd-handle dd2-handle">
					<i class="normal-icon icon-comments blue bigger-130"></i>
					<i class="drag-icon icon-move bigger-125"></i>
				</div>
				<div class="dd2-content">Click on an icon to start dragging</div>
			</li>
			
			<li class="dd-item dd2-item" data-id="2" data-group="1">
				<div class="dd-handle dd2-handle">
					<i class="normal-icon icon-time pink bigger-130"></i>
					<i class="drag-icon icon-move bigger-125"></i>
				</div>
				<div class="dd2-content">Recent Posts</div>
				<ol class="dd-list">
					<li class="dd-item item-orange" data-id="6" data-group="2">
						<div class="dd-handle"> Item 6 </div>
					</li>
					<li class="dd-item item-red" data-id="7" data-group="2">
						<div class="dd-handle">Item 7</div>
					</li>
					<li class="dd-item item-blue2" data-id="8" data-group="2">
						<div class="dd-handle">Item 8</div>
					</li>
				</ol>
			</li>
			-->
		</ol>
	</div>
</div>

<button class="btn btn-primary addArea"><i class="icon-plus"></i> Aggiungi nuova area</button>


<div id='AreaForm' class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
        <h4 class="modal-title">Area</h4>
      </div>
      <div class="modal-body">
       	<form id="AreaForm-id" method="POST">
			<input id="parentId" type="hidden" value="${el.id}" name="parentId">
			<div id="reportsAreaTemplate-reportsAreaTemplate_nome" class="form-group field-component field-editable">
				<label for="reportsAreaTemplate_nome">
				Nome area<sup style="color:red">*</sup>:
				</label>
				<input id="reportsAreaTemplate_nome" type="text" size="10" value="" name="reportsAreaTemplate_nome">
			</div>
		</form>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary saveArea">Save changes</button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->



<div id='ReportForm' class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
        <h4 class="modal-title">Area</h4>
      </div>
      <div class="modal-body">
       	<form name="reportForm-form" id="ReportForm-id" method="POST">
      		<input type="hidden"  name="parentId" id="report_form_parentId" value=""/>
       		<div class="form-group field-component  field-editable" id="report-report_nome">
       			<label for="report_nome">nome<sup style="color:red">*</sup>:</label>
				<input type="text"  name="report_nome" id="report_nome" value="" size="10"/>
	  		</div>
	  		<div class="form-group field-component  field-editable" id="report-report_url">		        
				<label for="report_url">url<sup style="color:red">*</sup>:</label>
				<textarea cols="40" rows="2" type="text" name="report_url" id="report_url"></textarea>
			</div>
			<div class="form-group field-component  field-editable" id="report-report_default">
				<label for="report_default">report.default<sup style="color:red">*</sup>:</label>
        		<span class="x-radio-input x-field-report_default">
		        	<div class="radio">
						<label>
							<input type="radio" class="ace" id="report_default" name="report_default" value="1###Si"  title="Si"><span class="lbl"> Si</span>
						</label>
					</div>
        		</span>
		        <span class="x-radio-input x-field-report_default">
		        	<div class="radio">
						<label>
							<input type="radio" class="ace" id="report_default" name="report_default" value="0###No"  title="No"><span class="lbl"> No</span>
						</label>
					</div>
		        </span>
			</div>
		</form>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary saveReport">Save changes</button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->
<div class='col-sm-6 pull-right policy-area' style="display:none">
	<h4>Visibilit&agrave; report: <span></span></h4>
	<table  class="table table-striped table-bordered table-hover">
		<thead>
			<tr>
				<th>Gruppo</th>
				<th>Visibile</th>
				<th>Elimina</th>
			</tr>
		</thead>
		<tbody>
		</tbody>
	</table>
	<button class="btn btn-sm btn-primary add-rule"><i class="icon-plus"></i> Aggiungi nuovo permesso</button>
</div>



<div id='RuleForm' class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
        <h4 class="modal-title">Seleziona il gruppo da abilitare</h4>
      </div>
      <div class="modal-body">
       	<input type="text" id="authoritySelect"/>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary addRule-to-group">Save changes</button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->

