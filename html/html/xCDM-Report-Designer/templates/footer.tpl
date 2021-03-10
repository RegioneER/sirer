</div>
<!-- basic scripts -->

<!--[if !IE]> -->
<script src="ace-assets/js/jquery.js"></script>

<!-- <![endif]-->

<!--[if IE]>
<script src="ace-assets/js/jquery1x.js"></script>
<![endif]-->
<script type="text/javascript">
    if('ontouchstart' in document.documentElement) document.write("<script src='ace-assets/js/jquery.mobile.custom.js'>"+"<"+"/script>");
</script>
<script src="ace-assets/js/bootstrap.js"></script>

<!-- page specific plugin scripts -->

<!--[if lte IE 8]>
<script src="ace-assets/js/excanvas.js"></script>
<![endif]-->
<script src="ace-assets/js/jquery-ui.custom.js"></script>
<script src="ace-assets/js/jquery.ui.touch-punch.js"></script>
<script src="ace-assets/js/jquery.easypiechart.js"></script>
<script src="ace-assets/js/jquery.sparkline.js"></script>
<script src="ace-assets/js/flot/jquery.flot.js"></script>
<script src="ace-assets/js/flot/jquery.flot.pie.js"></script>
<script src="ace-assets/js/flot/jquery.flot.resize.js"></script>

<!-- ace scripts -->
<script src="ace-assets/js/ace/elements.scroller.js"></script>
<script src="ace-assets/js/ace/elements.colorpicker.js"></script>
<script src="ace-assets/js/ace/elements.fileinput.js"></script>
<script src="ace-assets/js/ace/elements.typeahead.js"></script>
<script src="ace-assets/js/ace/elements.wysiwyg.js"></script>
<script src="ace-assets/js/ace/elements.spinner.js"></script>
<script src="ace-assets/js/ace/elements.treeview.js"></script>
<script src="ace-assets/js/ace/elements.wizard.js"></script>
<script src="ace-assets/js/ace/elements.aside.js"></script>
<script src="ace-assets/js/ace/ace.js"></script>
<script src="ace-assets/js/ace/ace.ajax-content.js"></script>
<script src="ace-assets/js/ace/ace.touch-drag.js"></script>
<script src="ace-assets/js/ace/ace.sidebar.js"></script>
<script src="ace-assets/js/ace/ace.sidebar-scroll-1.js"></script>
<script src="ace-assets/js/ace/ace.submenu-hover.js"></script>
<script src="ace-assets/js/ace/ace.widget-box.js"></script>
<script src="ace-assets/js/ace/ace.settings.js"></script>
<script src="ace-assets/js/ace/ace.settings-rtl.js"></script>
<script src="ace-assets/js/ace/ace.settings-skin.js"></script>
<script src="ace-assets/js/ace/ace.widget-on-reload.js"></script>
<script src="ace-assets/js/ace/ace.searchbox-autocomplete.js"></script>
<script src="ace-assets/js/bootbox.min.js"></script>

{foreach from=$ace_js_added  item="js_file"}
    <script src="ace-assets/js/{$js_file}.js"></script>
{/foreach}

{foreach from=$js_added  item="js_file"}
    <script src="js/{$js_file}.js"></script>
{/foreach}
<!-- inline scripts related to this page -->
<script type="text/javascript">
    {$js_inline}
</script>

<!-- the following scripts are used in demo only for onpage help and you don't need them -->
<link rel="stylesheet" href="ace-assets/css/ace.onpage-help.css" />

<script type="text/javascript"> ace.vars['base'] = '..'; </script>
<script src="ace-assets/js/ace/elements.onpage-help.js"></script>
<script src="ace-assets/js/ace/ace.onpage-help.js"></script>
</body>
</html>
