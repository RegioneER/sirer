
$('#tabs a[id^=tab]').on('click',function(){
	var hash=this.href;
	hash=hash.replace(/^[^#]*/,'');
	window.location.hash=hash;
});