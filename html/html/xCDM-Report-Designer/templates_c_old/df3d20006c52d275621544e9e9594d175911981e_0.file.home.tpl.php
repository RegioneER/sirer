<?php
/* Smarty version 3.1.30, created on 2017-02-23 15:02:33
  from "/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/home.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_58aef98911d1b6_16569697',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    'df3d20006c52d275621544e9e9594d175911981e' => 
    array (
      0 => '/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/home.tpl',
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
function content_58aef98911d1b6_16569697 (Smarty_Internal_Template $_smarty_tpl) {
$_smarty_tpl->_subTemplateRender("file:header.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>

<h1 style="text-align: center"><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</h1>

<?php $_smarty_tpl->_subTemplateRender("file:struct.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


<?php $_smarty_tpl->_subTemplateRender("file:footer.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
}
}
