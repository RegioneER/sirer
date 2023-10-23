$(document).ready(function() {
	initBuilder();
});
/**NON VIENE RICHIAMATO! vai su utils.js**/
function initBuilder() {
	
	
	var fields=$('#form_fields').html();
	fb = new Formbuilder({
		selector : '.xmr_builder',
		bootstrapData :  fields
	});
	
	fb.on('save', function(payload) {
		console.log(payload);
	});
} 

function leggiForm() {
	return JSON.stringify(fb.mainView.bootstrapData);
}
