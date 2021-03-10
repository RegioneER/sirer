<?php
/* Smarty version 3.1.30, created on 2017-03-06 11:16:12
  from "/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/struct.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_58bd44fca9d345_69786321',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    '36e24ab6ca676564cb602e7e56a88186fcbcf466' => 
    array (
      0 => '/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/struct.tpl',
      1 => 1488798940,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
    'file:recursive-struct.tpl' => 1,
  ),
),false)) {
function content_58bd44fca9d345_69786321 (Smarty_Internal_Template $_smarty_tpl) {
$_smarty_tpl->_assignInScope('idx', "0" ,false ,8);
$_smarty_tpl->_assignInScope('elpath', '');
?>
<form id="reportDesigner" name='reportDesigner' method='POST' action="index.php?/buildReport">
Inserisci il nome del prefisso delle viste da creare: <input type="text" name="rep_prefix" placeholder="prefisso"><br/>
<button type='submit' class='btn btn-info'>Costruisci report</button>
<?php $_smarty_tpl->_subTemplateRender("file:recursive-struct.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array('startNode'=>$_smarty_tpl->tpl_vars['struct']->value,'exploded'=>true,'elpath'=>$_smarty_tpl->tpl_vars['elpath']->value), 0, false);
?>

<button type='submit' class='btn btn-info'>Costruisci report</button>
</form><?php }
}
