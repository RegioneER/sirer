<?php
/* Smarty version 3.1.30, created on 2017-03-06 11:14:19
  from "/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/footer.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_58bd448b265840_47138376',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    '450e7e5d797b2f80225c61366460010b23b87075' => 
    array (
      0 => '/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/footer.tpl',
      1 => 1488798854,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
  ),
),false)) {
function content_58bd448b265840_47138376 (Smarty_Internal_Template $_smarty_tpl) {
?>
</div>
<!-- basic scripts -->

<!--[if !IE]> -->
<?php echo '<script'; ?>
 src="ace-assets/js/jquery.js"><?php echo '</script'; ?>
>

<!-- <![endif]-->

<!--[if IE]>
<?php echo '<script'; ?>
 src="ace-assets/js/jquery1x.js"><?php echo '</script'; ?>
>
<![endif]-->
<?php echo '<script'; ?>
 type="text/javascript">
    if('ontouchstart' in document.documentElement) document.write("<?php echo '<script'; ?>
 src='ace-assets/js/jquery.mobile.custom.js'>"+"<"+"/script>");
<?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/bootstrap.js"><?php echo '</script'; ?>
>

<!-- page specific plugin scripts -->

<!--[if lte IE 8]>
<?php echo '<script'; ?>
 src="ace-assets/js/excanvas.js"><?php echo '</script'; ?>
>
<![endif]-->
<?php echo '<script'; ?>
 src="ace-assets/js/jquery-ui.custom.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/jquery.ui.touch-punch.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/jquery.easypiechart.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/jquery.sparkline.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/flot/jquery.flot.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/flot/jquery.flot.pie.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/flot/jquery.flot.resize.js"><?php echo '</script'; ?>
>

<!-- ace scripts -->
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.scroller.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.colorpicker.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.fileinput.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.typeahead.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.wysiwyg.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.spinner.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.treeview.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.wizard.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.aside.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.ajax-content.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.touch-drag.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.sidebar.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.sidebar-scroll-1.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.submenu-hover.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.widget-box.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.settings.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.settings-rtl.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.settings-skin.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.widget-on-reload.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.searchbox-autocomplete.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/bootbox.min.js"><?php echo '</script'; ?>
>

<?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['ace_js_added']->value, 'js_file');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['js_file']->value) {
?>
    <?php echo '<script'; ?>
 src="ace-assets/js/<?php echo $_smarty_tpl->tpl_vars['js_file']->value;?>
.js"><?php echo '</script'; ?>
>
<?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>


<?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['js_added']->value, 'js_file');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['js_file']->value) {
?>
    <?php echo '<script'; ?>
 src="js/<?php echo $_smarty_tpl->tpl_vars['js_file']->value;?>
.js"><?php echo '</script'; ?>
>
<?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>

<!-- inline scripts related to this page -->
<?php echo '<script'; ?>
 type="text/javascript">
    <?php echo $_smarty_tpl->tpl_vars['js_inline']->value;?>

<?php echo '</script'; ?>
>

<!-- the following scripts are used in demo only for onpage help and you don't need them -->
<link rel="stylesheet" href="ace-assets/css/ace.onpage-help.css" />

<?php echo '<script'; ?>
 type="text/javascript"> ace.vars['base'] = '..'; <?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/elements.onpage-help.js"><?php echo '</script'; ?>
>
<?php echo '<script'; ?>
 src="ace-assets/js/ace/ace.onpage-help.js"><?php echo '</script'; ?>
>
</body>
</html>
<?php }
}
