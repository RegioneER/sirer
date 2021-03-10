<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <meta charset="utf-8" />
    <title>{$title}</title>

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

    {foreach from=$ace_css_added  item="css_file"}
        <link rel="stylesheet" href="ace-assets/css/{$css_file}.css" />
    {/foreach}
    
    {foreach from=$css_added  item="css_file"}
        <link rel="stylesheet" href="css/{$css_file}.css" />
    {/foreach}

    <!-- ace settings handler -->
    <script src="ace-assets/js/ace-extra.js"></script>

    <!-- HTML5shiv and Respond.js for IE8 to support HTML5 elements and media queries -->

    <!--[if lte IE 8]>
    <script src="ace-assets/js/html5shiv.js"></script>
    <script src="ace-assets/js/respond.js"></script>
    <![endif]-->
</head>

<body class="no-skin">

<div class="main-container">