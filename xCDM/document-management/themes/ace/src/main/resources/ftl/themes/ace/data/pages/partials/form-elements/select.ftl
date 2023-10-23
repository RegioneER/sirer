<#global page=page + {"scripts": page.scripts + ["select2"], "styles": page.styles + ["select2"]} />
<@script>
$('select').select2({containerCssClass:'select2-ace',allowClear: true});
</@script>
