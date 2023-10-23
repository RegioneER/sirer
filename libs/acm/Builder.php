<?php
require_once 'dbconfig.php';
require_once 'database.php';

class Builder {

    function Builder($prefix,$descr) {
        $this -> prefix = $prefix;
        $this -> descr = $descr;
    }

    function getHome() {
        $titolo = 'Builder';
        $builderHeader = '<link rel="stylesheet" href="builder/vendor/css/vendor.css" />
        <link rel="stylesheet" href="builder/dist/formbuilder.css" />
        <script src="builder/vendor/js/vendor.js"></script>
        <script src="builder/dist/formbuilder.js"></script>
        <link rel="stylesheet" href="builder/xmrbuilder.css" />
        <script src="builder/xmrbuilder.js"></script>';
        $uim = UIManager::getInstance();
        $output = file_get_contents("container.html");
        $output = str_replace("<!--title-->", $titolo, $output);
        $output = str_replace("<!--page_title-->", $this -> prefix, $output);
        $output = str_replace("<!--sidebar-->", $uim -> dsp_sidebar(), $output);
        $output = str_replace("<!--navbar-->", $uim -> dsp_navbar(), $output);
        $output = str_replace("<!--sidebar-->", $sideBar, $output);
        $output = str_replace("<!--breadcrumb-->", $uim -> dsp_breadcrumb(), $output);
        $output = str_replace("<!--page_content-->", $this->builder_page_content(), $output);
        $output = str_replace("<!--builder_header-->", $builderHeader, $output);
        //$output=str_replace("<!--system_messages-->",$mstr,$output);
        return $output;
    }

    
    
    function builder_page_content(){
    	$uim = UIManager::getInstance();
    	$output="";
    	$output.='<div class="xmr_builder"></div>';
    	return $output;
    }
}
?>