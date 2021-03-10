$("a[data-type='show_hide']").click(function(){
	console.log("Mostro/nascondo");
	elId=$(this).attr('data-id-ref');
	el=$('#'+elId);
	if (el.is(":visible")) el.hide();
	else el.show();
	return false;
});

$("a[data-type='show_hide_ref']").click(function(){
	console.log("Mostro/nascondo");
	elId=$(this).attr('data-id-ref');
	el=$('tr[data-ref-id="'+elId+'"]');
	if (el.is(":visible")) el.hide();
	else el.show();
	return false;
});