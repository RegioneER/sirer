if (jQuery("#Prestazioni_prestazione").data('autocomplete')) {
  jQuery("#Prestazioni_prestazione").autocomplete("destroy");
  jQuery("#Prestazioni_prestazione").removeData('autocomplete');
}
var $that1=$( "#Prestazioni_prestazione" );
$( "#Prestazioni_prestazione" ).autocomplete({
								
	minLength: 2,
	select: function( event, ui ) {
				var request={prestazione:$( "#Prestazioni_prestazione" ).val(),term:''};
				
				$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
					if(data.length==1){
						valorizzaCDC($( "#Prestazioni_CDC" ),data[0]);
					}
				});
				$( "#Prestazioni_Codice" ).val(ui.item.id);
				$('#Tariffario_Solvente').val(ui.item.solvente);
				$('#Tariffario_SSN').val(ui.item.ssn);
				$(this).off('keypress').on('keypress',function(){
					$( "#dizionario" ).val('');
					hidebutton();
					if($(this).val()!=ui.item.value){
						$( "#Prestazioni_Codice" ).val('');
						$( "#Prestazioni_CDC" ).val('');
						$( "#Prestazioni_CDC" ).keypress();
						$( "#dizionario" ).val('');
						$(this).off('keypress');
					}
				});
			},
	source:function( request, response ) {
				$that1.next('i.icon-spinner').remove();
				$that1.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;top:-29px;left:370px' ></i>");
				var term = request.term;
				if ( term in cache ) {
					response( cache[ term ] );
					return;
				}
				$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
					cache[ term ] = data;
					response( data );
					$that1.next('i.icon-spinner').remove();
				});
			}
	
});

$( "#Prestazioni_prestazione" ).change(function(){
	var request={prestazione:$( "#Prestazioni_prestazione" ).val(),term:''};
	$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
		if(data.length==1){
			valorizzaCDC($( "#Prestazioni_CDC" ),data[0]);
		}
	});
});
$( "#Prestazioni_CDC" ).off('click').click(function(){
    $( this ).autocomplete('search','');
});
$( "#Prestazioni_CDC2" ).off('click').click(function(){
    $( this ).autocomplete('search','');
});

if (jQuery("#Prestazioni_CDC").data('autocomplete')) {
  jQuery("#Prestazioni_CDC").autocomplete("destroy");
  jQuery("#Prestazioni_CDC").removeData('autocomplete');
}
var $that2=$( "#Prestazioni_CDC" );
$( "#Prestazioni_CDC" ).autocomplete({
	
	minLength: 0,
	source:function( request, response ) {
				$that2.next('i.icon-spinner').remove();
				$that2.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;top:-29px;left:370px' ></i>");
				request.prestazione=$( "#Prestazioni_prestazione" ).val();
				$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
					//cache[ term ] = data;
					response( data );
					$that2.next('i.icon-spinner').remove();
				});
			},
	 select: function( event, ui ) {
				valorizzaCDC(this,ui.item);
			}
	
});
if (jQuery("#Prestazioni_CDC2").data('autocomplete')) {
  jQuery("#Prestazioni_CDC2").autocomplete("destroy");
  jQuery("#Prestazioni_CDC2").removeData('autocomplete');
}
var $that3=$( "#Prestazioni_CDC2" );
$( "#Prestazioni_CDC2" ).autocomplete({
	
	minLength: 0,
	source:function( request, response ) {
				$that3.next('i.icon-spinner').remove();
				$that3.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;top:-29px;left:370px' ></i>");
				request.prestazione=$( "#Prestazioni_prestazione" ).val();
				$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
					//cache[ term ] = data;
					response( data );
					$that3.next('i.icon-spinner').remove();
				});
			},
	 select: function( event, ui ) {
				valorizzaCDC(this,ui.item);
			}
	
});
$("#prestazione-diz-dialog").dialog({
    autoOpen : false,
    height : 400,
    width : 450,
    modal : true,
    position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
    buttons:[
	    {
			text:"Aggiungi prestazione", 
			click: function() {
	        	 
	
	        },
			"class" : "btn btn-primary btn-xs"
		},
		{
			text: "Annulla", 
			click:function() {
				$(this).dialog("close");
			},
			"class" : "btn btn-xs"
		}
	],
   
    open:function(){
        
    }

});
$("#prestazione-diz-button").button().click(function() {$("#prestazione-diz-dialog").dialog("open");});
						    