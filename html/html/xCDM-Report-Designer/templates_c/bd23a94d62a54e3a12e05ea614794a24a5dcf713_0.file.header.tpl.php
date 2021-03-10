<?php
/* Smarty version 3.1.30, created on 2017-02-23 15:14:50
  from "/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/header.tpl" */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '3.1.30',
  'unifunc' => 'content_58aefc6aacab79_80282849',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    'bd23a94d62a54e3a12e05ea614794a24a5dcf713' => 
    array (
      0 => '/sissprod/http/servizi/NET/ctcgemelli/html/xCDM-Report-Designer/templates/header.tpl',
      1 => 1487862887,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
  ),
),false)) {
function content_58aefc6aacab79_80282849 (Smarty_Internal_Template $_smarty_tpl) {
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <meta charset="utf-8" />
    <title><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</title>

    <meta name="description" content="overview &amp; stats" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0" />

    <!-- bootstrap & fontawesome -->
    <link rel="stylesheet" href="ace-assets/css/bootstrap.css" />
    <link rel="stylesheet" href="ace-assets/css/font-awesome.css" />

    <!-- page specific plugin styles -->

    <!-- text fonts -->
    <link rel="stylesheet" href="ace-assets/css/ace-fonts.css" />

    <!-- ace styles -->
    <link rel="stylesheet" href="ace-assets/css/ace.css" class="ace-main-stylesheet" id="main-ace-style" />

    <!--[if lte IE 9]>
    <link rel="stylesheet" href="ace-assets/css/ace-part2.css" class="ace-main-stylesheet" />
    <![endif]-->

    <!--[if lte IE 9]>
    <link rel="stylesheet" href="ace-assets/css/ace-ie.css" />
    <![endif]-->

    <!-- inline styles related to this page -->

    <?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['ace_css_added']->value, 'css_file');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['css_file']->value) {
?>
        <link rel="stylesheet" href="ace-assets/css/<?php echo $_smarty_tpl->tpl_vars['css_file']->value;?>
.css" />
    <?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>

    
    <?php
$_from = $_smarty_tpl->smarty->ext->_foreach->init($_smarty_tpl, $_smarty_tpl->tpl_vars['css_added']->value, 'css_file');
if ($_from !== null) {
foreach ($_from as $_smarty_tpl->tpl_vars['css_file']->value) {
?>
        <link rel="stylesheet" href="css/<?php echo $_smarty_tpl->tpl_vars['css_file']->value;?>
.css" />
    <?php
}
}
$_smarty_tpl->smarty->ext->_foreach->restore($_smarty_tpl);
?>


    <!-- ace settings handler -->
    <?php echo '<script'; ?>
 src="ace-assets/js/ace-extra.js"><?php echo '</script'; ?>
>

    <!-- HTML5shiv and Respond.js for IE8 to support HTML5 elements and media queries -->

    <!--[if lte IE 8]>
    <?php echo '<script'; ?>
 src="ace-assets/js/html5shiv.js"><?php echo '</script'; ?>
>
    <?php echo '<script'; ?>
 src="ace-assets/js/respond.js"><?php echo '</script'; ?>
>
    <![endif]-->
</head>

<body class="no-skin">

<div class="main-container"><?php }
}
