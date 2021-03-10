<?php
/* Smarty version 3.1.30, created on 2017-03-04 18:12:12
  from "/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/recursive-struct.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_58bb037c19a5e8_34992134',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    'f71420b24f324cbbd1ceb19b34c4e646f66fba7c' => 
    array (
      0 => '/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/recursive-struct.tpl',
      1 => 1488651128,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
    'file:recursive-struct.tpl' => 2,
  ),
),false)) {
function content_58bb037c19a5e8_34992134 (Smarty_Internal_Template $_smarty_tpl) {
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['startNode']->value, 'element');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['element']->value) {
?>
	<?php if ($_smarty_tpl->tpl_vars['elpath']->value == '') {?>
		<?php $_smarty_tpl->smarty->ext->_capture->open($_smarty_tpl, 'default', 'thispath', null);
echo $_smarty_tpl->tpl_vars['elpath']->value;
echo $_smarty_tpl->tpl_vars['element']->value['name'];
$_smarty_tpl->smarty->ext->_capture->close($_smarty_tpl);
?>

	<?php } else { ?>
		<?php $_smarty_tpl->smarty->ext->_capture->open($_smarty_tpl, 'default', 'thispath', null);
echo $_smarty_tpl->tpl_vars['elpath']->value;?>
.<?php echo $_smarty_tpl->tpl_vars['element']->value['name'];
$_smarty_tpl->smarty->ext->_capture->close($_smarty_tpl);
?>

	<?php }?>
	<?php $_smarty_tpl->_assignInScope('idx', $_smarty_tpl->tpl_vars['idx']->value+1 ,false ,8);
?>
	<li id="unique_el_list_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
">
	<span  data-caret-container="true" data-caret-container-element="unique_el_list_detail_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
">Elemento: <b><?php echo $_smarty_tpl->tpl_vars['element']->value['name'];?>
</b></span> 
    <a <?php if (!$_smarty_tpl->tpl_vars['expoloded']->value) {?>style="display: ;"<?php }?> href="#" data-caret="down" data-rel="unique_el_list_detail_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-down"></i></a>
    <a <?php if (!$_smarty_tpl->tpl_vars['expoloded']->value) {?>style="display: none;"<?php }?> href="#" data-caret="up" data-rel="unique_el_list_detail_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-up"></i></a>
    <ul>
  	<div id="unique_el_list_detail_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
" <?php if (!$_smarty_tpl->tpl_vars['expoloded']->value) {?>style="display: none;"<?php }?> >
    											
   		<?php if (!empty($_smarty_tpl->tpl_vars['element']->value['fields'])) {?>
   			<b href="#" data-caret-container="true" data-caret-container-element="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
">Campi</b>
   			<a href="#" data-caret="down" data-rel="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-down"></i></a>
  			<a style="display: none;" href="#" data-caret="up" data-rel="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-up"></i></a>
   			<ul id="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
" style="display: none;">
			<?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['element']->value['fields'], 'fields', false, 'template');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['template']->value => $_smarty_tpl->tpl_vars['fields']->value) {
?>
				<li>
					<span data-caret-container="true" data-caret-container-element="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
">
					<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
</span>
					<a href="#" data-caret="down" data-rel="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
"><i class="fa fa-chevron-down"></i></a>
  					<a style="display: none;" href="#" data-caret="up" data-rel="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
"><i class="fa fa-chevron-up"></i></a>
   					<ul id="unique_el_list_detail_fields_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
" style="display: none;">
					<?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['fields']->value, 'field');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['field']->value) {
?>
						<li>
							<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>

							<?php if ($_smarty_tpl->tpl_vars['field']->value['type'] == 'ELEMENT_LINK') {?>
								<label>
									<input name="fields[]" class="ace field_linked" type="checkbox" data-elpath="<?php echo $_smarty_tpl->tpl_vars['thispath']->value;?>
" data-elTypeName="<?php echo $_smarty_tpl->tpl_vars['element']->value['name'];?>
" data-templateName="<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
" data-fieldName="<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
" value="<?php echo $_smarty_tpl->tpl_vars['thispath']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
.<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
">
									<span class="lbl"></span>
								</label>
								collegamento a elemento di tipo <?php echo $_smarty_tpl->tpl_vars['element']->value['name'];?>

								<ul id="nested_el<?php echo $_smarty_tpl->tpl_vars['idx']->value;
echo $_smarty_tpl->tpl_vars['template']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
" data-idx="<?php echo $_smarty_tpl->tpl_vars['thispath']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
.<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
"></ul>
							<?php } else { ?>
								<label>
									<input name="fields[]" class="ace field_check" type="checkbox" value="<?php echo $_smarty_tpl->tpl_vars['thispath']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
.<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
">
									<span class="lbl"></span>
								</label>
								<input type="textbox" name="<?php echo $_smarty_tpl->tpl_vars['thispath']->value;?>
_<?php echo $_smarty_tpl->tpl_vars['template']->value;?>
.<?php echo $_smarty_tpl->tpl_vars['field']->value['name'];?>
" placeholder="nome colonna ..." size="20" disabled/>
							<?php }?>
						</li>
					<?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>

					</ul>
				</li>
			<?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>
   
			</ul>
			<br/>
			<?php }?>
   			<?php if (!empty($_smarty_tpl->tpl_vars['element']->value['children'])) {?>
   			<b href="#" data-caret-container="true" data-caret-container-element="unique_el_list_detail_children_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
">Figli</b>
   			<a style="display: none;" href="#" data-caret="down" data-rel="unique_el_list_detail_children_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-down"></i></a>
  			<a  href="#" data-caret="up" data-rel="unique_el_list_detail_children_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
"><i class="fa fa-chevron-up"></i></a>
  	 		<ul id="unique_el_list_detail_children_<?php echo $_smarty_tpl->tpl_vars['idx']->value;?>
" style="display: ;"><?php $_smarty_tpl->_subTemplateRender("file:recursive-struct.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array('startNode'=>$_smarty_tpl->tpl_vars['element']->value['children'],'exploded'=>false,'elpath'=>$_smarty_tpl->tpl_vars['thispath']->value), 0, true);
?>
</ul>
  		<?php }?>
  	</div>
   	</ul>
   </li>

<?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
}
}
