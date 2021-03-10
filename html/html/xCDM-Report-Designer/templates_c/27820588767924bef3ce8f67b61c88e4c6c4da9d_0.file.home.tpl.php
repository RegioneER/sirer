<?php
/* Smarty version 3.1.30, created on 2020-01-13 11:49:59
  from "/http/servizi/siss-bundle-01/sirer.progetto-sole.it/html/xCDM-Report-Designer/templates/home.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_5e1c4b5765e3f5_09496298',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    '27820588767924bef3ce8f67b61c88e4c6c4da9d' => 
    array (
      0 => '/http/servizi/siss-bundle-01/sirer.progetto-sole.it/html/xCDM-Report-Designer/templates/home.tpl',
      1 => 1544698024,
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
function content_5e1c4b5765e3f5_09496298 (Smarty_Internal_Template $_smarty_tpl) {
$_smarty_tpl->_subTemplateRender("file:header.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>

<h1 style="text-align: center"><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</h1>

<?php $_smarty_tpl->_subTemplateRender("file:struct.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


<?php $_smarty_tpl->_subTemplateRender("file:footer.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
}
}
