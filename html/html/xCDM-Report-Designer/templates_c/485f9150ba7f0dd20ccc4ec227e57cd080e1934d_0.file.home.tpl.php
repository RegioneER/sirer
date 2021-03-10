<?php
/* Smarty version 3.1.30, created on 2018-05-18 11:28:27
  from "/http/servizi/siss-bundle-01/sirer-test.sissprep.cineca.it/html/xCDM-Report-Designer/templates/home.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_5afe9cbb5b1a79_67265991',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    '485f9150ba7f0dd20ccc4ec227e57cd080e1934d' => 
    array (
      0 => '/http/servizi/siss-bundle-01/sirer-test.sissprep.cineca.it/html/xCDM-Report-Designer/templates/home.tpl',
      1 => 1487862107,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
    'file:header.tpl' => 1,
    'file:struct.tpl' => 1,
    'file:footer.tpl' => 1,
  ),
),false)) {
function content_5afe9cbb5b1a79_67265991 (Smarty_Internal_Template $_smarty_tpl) {
$_smarty_tpl->_subTemplateRender("file:header.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>

<h1 style="text-align: center"><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</h1>

<?php $_smarty_tpl->_subTemplateRender("file:struct.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


<?php $_smarty_tpl->_subTemplateRender("file:footer.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
}
}
