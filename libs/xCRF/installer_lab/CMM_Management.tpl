<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>CMM Management</title>
<meta http-equiv=Content-Type content="text/html; charset=utf-8">
<link href="/css/hyperstudy_v01.css" type="text/css" rel="stylesheet" />
<script src="libs/js/jquery/jquery-1.6.js" type="text/javascript"></script>
<script src="libs/js/jquery/jquery-ui-1.8.min.js" type="text/javascript"></script>
<script src="libs/js/jquery/jquery.scrollTo-1.4.2-min.js" type="text/javascript"></script>
<script src="libs/js/jquery/jquery.url.js" type="text/javascript"></script>
<!--<script src="libs/js/jquery/jquery.qtip-1.0.0-rc3.min.js" type="text/javascript"></script>-->
<script src="libs/js/jquery/jquery.qtip.min.js" type="text/javascript"></script>
<link href="libs/js/jquery/jquery.qtip.min.css" type="text/css" rel="stylesheet" />
<!--<link href="libs/js/jquery/css/redmond/jquery-ui-1.8.13.custom.css" type="text/css" rel="stylesheet" />-->
<link href="libs/js/jquery/css/ui-lightness/jquery-ui-1.8.13.custom.css" type="text/css" rel="stylesheet" />
<!--<link href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.13/themes/redmond/jquery-ui.css" type="text/css" rel="stylesheet" />-->
<meta content="MSHTML 6.00.2800.1226" name=GENERATOR>
<style type="text/css">

/* 
	Web20 Table Style
	written by Netway Media, http://www.netway-media.com
*/

body {
	background: url("libs/images/body_back.jpg") repeat scroll left top #FFFFFF;
}
table {
  border-collapse: collapse;
  border: 1px solid #666666;
  font: normal 11px verdana, arial, helvetica, sans-serif;
  color: #363636;
  background: #f6f6f6;
  text-align:left;
  }
caption {
  text-align: center;
  font: bold 16px arial, helvetica, sans-serif;
  background: transparent;
  padding:6px 4px 8px 0px;
  color: #CC00FF;
  text-transform: uppercase;
}
thead, tfoot {
	background:url(bg1.png) repeat-x;
	text-align:left;
	height:30px;
}
thead th, tfoot th {
	padding:5px;
}
table a {
	color: #333333;
	text-decoration:none;
}
table a:hover {
	text-decoration: none;
}
tr.odd {
	background: #f1f1f1;
}
tbody th, tbody td {
	padding:5px;
}

a {
	text-decoration:none;
}
a:hover {
	text-decoration:underline;
}

.SenzaBordosup {
	border-right-width: thin;
	border-bottom-width: thin;
	border-left-width: thin;
	border-top-style: none;
	border-right-style: solid;
	border-bottom-style: solid;
	border-left-style: solid;
	border-top-width: 0px;
	border-top-color: #FFFFFF;
	border-right-color: #000000;
	border-bottom-color: #000000;
	border-left-color: #000000;
}

.header1 {
	background-color: #00F2FF;
}

.header2 {
	background-color: #72DBF2;
/*	background-color: #00CCFF:*/
}

.edit_user_select {
	/*background-color: #F2E7E6;*/
	background-color: #85A0CB;
}

.edit_user_selected_center {
	font-weight: bolder;
}

.center_disabled {
	background-color: #E3E3E3;
}

.user_disabled {
	background-color: #E3E3E3;
}

.centered2 {
  position: absolute;
  top: 50%;
  left: 50%;
  margin-top: -25%;
  margin-left: -25%;
  background-color: red;
  color: white;
} 

.centered {
  /*position: relative;*/
  /*left: 50%;*/
  text-align: center;
} 
.centered_img {
	display: block;
	margin-left: auto;
	margin-right: auto;
}
.tooltip_font {
	font-family: Arial, Verdana, Sans-serif;
	font-size: 0.7em;
}

/*tr.header2 td, input.text, select {
    width: auto;
    min-width: 120px;
    _width: 120px;
}*/

/*tr.header2 td.small2 {
    width: auto;
    min-width: 50px;
    _width: 50px;
}*/

/*tr.header2 td.small_edit {
    width: auto;
    min-width: 50px;
    _width: 50px;
}*/

input.text, select {
    width: 100%;
}

tr.header2 td.edit_user {
	text-align: center;
    width: 60px;
    _width: 60px;
}

tr.header2 td.edit_center {
	text-align: center;
    width: 60px;
    _width: 60px;
}

td.edit_user {
	text-align: center;
    width: auto;
    min-width: 60px;
    _width: 60px;
}

td.edit_center {
	text-align: center;
    width: auto;
    min-width: 60px;
    _width: 60px;
}

tr.user_center_selected {
	background-color: #F7AC1A;
}

tr.center_opened_top {
	border-style: solid;
	border-bottom-style: none;
}
tr.center_opened_middle {
	border-style: solid;
	border-left-style: none;
	border-right-style: none;
}
tr.center_opened_bottom {
	border-style: solid;
	border-top-style: none;
}

label.language_selector {
    display: block;
    padding-left: 15px;
    text-indent: -15px;
}
input.language_selector {
    width: 13px;
    height: 13px;
    padding-right: 6px;
    margin-right: 3px;
    vertical-align: middle;
    position: relative;
    top: -1px;
    *overflow: hidden;
}

option_enabled {
	background-color: #CCFFCC;
}

option_disabled {
	background-color: #FE2E2E;
}

select {
     width:100px;
     min-width:100px;
  }
 <!--[if IE]>
select {
     width: auto;
  }    
 <![endif]-->

.ui-dialog-buttonpane button { margin: 0 0 0 0; }
.ui-widget { font-size: 0.9em; }
.qtip { font-size: 16px; }

</style>

<script type="text/javascript">

	//CAMPI OBBLIGATORI E CON SIZE < 100 CHAR
	var mandatory_fields_user = ["NAME", "SURNAME"]; //, "EMAIL"];
	var mandatory_fields = ["CODE", "NAME"];
	//CAMPI SOLO NUMERICI CON SIZE < 50 CHAR
	var number_only_fields_user =["PHONE","FAX"];
	var number_only_fields =["PHONE","FAX"];
	//CAMPI NON OBBLIGATORI E ALFANUMERICI MA CON SIZE < 100 CHAR
	var max_lenght_fields_user =["ADDRESS"];
	var max_lenght_fields =["PI","ADDRESS"];
	//CAMPI MAIL
	var email_fields_user = ["EMAIL"];
	var email_fields = [];
	var select_to_be_triggered = ["_STATUS", "_COUNTRY", "_SIGN", "_SIGNSAE"];

	// Check di connessione per vedere se sono connesso
	function connectivityCheck() {
		$.ajax({
			type: "POST",
			url: "{$request_uri}",
			data: "ACTION=connectivity_check",
			dataType: "json",
			success: function(data) {
				if (data.sstatus == 'ko') {
					alert("{$connectivity_fail_label}");
					window.location.reload();
				}
			},
			error: function() {
				alert("{$connectivity_fail_label}");
				window.location.reload();
			}
		});
		return false;
	}
	
	// Tooltip per i campi obbligatori
	$.fn.addWarningQTip = function(message) {
		this.qtip(
		{
			content: '<img class="centered_img" src="libs/images/warning_img_small.png" /><br/><span class="tooltip_font">'+message+'</span>',
			show: {
				ready: true,
				event: false
			},
			hide: {
				event: false
			},
			position: {
				adjust: {
					x: -($(this).width() * 8/10),
					y: 2
				},
				at: "top right",
				my: "bottom left"
			},
			style: {
				tip: {
					corner: "bottomLeft",
					width: 7,
					height: 7
				}
			}
		});
	};

	// Tooltip per i campi email
	$.fn.addWarningEmailQTip = function() {
		this.qtip(
		{
			content: '<img class="centered_img" src="libs/images/warning_img_small.png" /><br/><span class="tooltip_font">{$email_field_message}</span>',
			show: {
				ready: true,
				event: false
			},
			hide: {
				event: false
			},
			position: {
				adjust: {
					x: -($(this).width() * 8/10),
					y: 2
				},
				at: "top right",
				my: "bottom left"
			},
			style: {
				tip: {
					corner: "bottomLeft",
					width: 7,
					height: 7
				}
			}
		});
	};

	// Tooltip per la selezione delle lingue
	$.fn.addLanguageSelectionQTip = function() {
		var center_id = $(this).attr("id").split("_")[1];
		var language_link = $(this);
		var image_link = $(language_link).find("img");

		if ($("#trcenter_"+center_id+"_users").is(":visible") ||
			$("#trcenter_"+center_id).hasClass("user_center_selected")) {
			return true;
		}

		if (! $(image_link).attr("src").match(/{$icon_file.edit_languages|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)) {
			return true;
		}
		// cambio icona
		$(image_link).attr("src", "{$icon_file.loading}");
		// Connectivity check
		connectivityCheck();
		// Richiedo in Ajax le lingue
		$.ajax({
			type: "POST",
			url: "{$request_uri}",
			data: "inputhiddencenter_"+center_id+"_ACTION=get_language_center&inputhiddencenter_"+center_id+"_ID_CENTER="+center_id+"",
			dataType: "json",
			success: function(data) {
				if (data.sstatus == 'ko') {
					alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
				} else {
					// Inserisco il content temporaneo
					$("#divlanguages_GENERICCENTER").after($("#divlanguages_GENERICCENTER").clone().attr("id", "divlanguages_"+center_id));
					var content = $("#divlanguages_"+center_id);

					$.each(data, function(skey, sval) {
						// Scorro tutte le lingue
						if (skey != 'sstatus') {
							var label_language = $(content).find("label:first").clone();
							$(label_language).html($(label_language).html().replace(/GENERICCENTER/g, center_id).replace(/GENERICLANGUAGE/g, sval.LANGUAGE).replace(/GENERICD_LANGUAGE/g, sval.D_LANGUAGE));
							if (sval.SELECTED == "YES") {
								$(label_language).find("input").attr("checked", "checked");
	                        }
							$(label_language).show();
							$(content).find("label:last").after(label_language);
						}
					});

					// Cambio i segnaposto del content
					$(content).children("input").each(function() {
						$(this).attr("id", $(this).attr("id").replace(/GENERICCENTER/g, center_id))
							.attr("name", $(this).attr("name").replace(/GENERICCENTER/g, center_id));
					});
					// e setto il center_id
					$(content).children("input[id$='_ID_CENTER']").val(center_id);

					$(language_link).qtip({
						content: $(content).html(),
						show: {
							ready: true,
							event: false,
							delay: 0,
							modal: {
								on: true,
								effect: function(state) {
							        /* 
							          "state" determines if its hiding/showing 
							          "this" refers to the overlay
							           0.4 and 0 are the show and hide opacities respectively.
							         */
									$(this).fadeTo(90, state ? 0.4 : 0, function() {
										if(!state) { $(this).hide(); }
									});
								}
							}
						},
						hide: {
							event: false
						},
						position: {
							my: "left center",
							at: "right center",
							target: $(language_link),
							viewport: $(window),
							adjust: {
								x: $(language_link).width() /2,
								y: 0
							}
						},
						style: {
							classes: 'ui-tooltip-blue ui-tooltip-shadow ui-tooltip-rounded'
						},
						events: {
							show: function (event, api) {
								$("#trcenter_"+center_id).addClass("edit_user_select");
								// Aggiungo la funzione click sui check dei languages
								$(this).find("input[type='checkbox']").checkAtLeastOneLanguage();
								$(this).find("input[type='submit']").setLanguagesCenter(language_link);
								// cambio icona
								$(image_link).attr("src", "{$icon_file.edit_languages}");
							},
							hide: function (event, api) {
								$("#trcenter_"+center_id).removeClass("edit_user_select");
								// Rimuovo i div in eccesso
								$("#divlanguages_"+center_id).remove();
								$("div[id^='ui-tooltip']").remove();
							}
						}
					});
				}
			}
		});

	};

	$.fn.addEditLinkCenter = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var center_id = $(this).attr("id").split("_")[1];
			if ($("#center_"+center_id+"_users").is(":visible") ||
				$("#trcenter_"+center_id).hasClass("center_disabled")) {
				return true;
			}
			//controllo che nessun altro centro o user sia in edit
			editing=false;
			$("img[id^='img_centereditlink_'], img[id^='img_usereditlink_'], ").each(
				function(){
			  		if(!$(this).attr("id").match("img_centereditlink_"+center_id)&&!$(this).attr("id").match(/img_centereditlink_NEWCENTER/i)&&!editing&&$(this).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)){
			  			editing=true;
			  		} 
			  	}
			);
			//se sto inserendo un nuovo utente o un nuovo centro
			if(!editing&&!$(this).attr("id").match("centereditlink_NEWCENTER")&&($("img[id^='img_usereditlink_NEWUSER'] ").length==1||$("img[id^='img_centereditlink_NEWCENTER'] ").length==1)){
			  //alert($(this).attr("id"));
			  editing=true;
			}
					
			if(editing){
			  	$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
	  		  	return false;
	  	  	}
			
			//controllo che non ci sia un centro o un user in inserimento
			
			if ($("#img_centereditlink_"+center_id).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/))
			{
				var can_proceed = true;
				$(mandatory_fields).each(function(key, field) {
					var inputcenter_field = $("#inputcenter_"+center_id+"_"+field);
					if ($(inputcenter_field).val() == '') {
						can_proceed = false;
					}
				});
				if($("#selectcenter_"+center_id+"_COUNTRY").val()==''){
				  alert("You have to select a Country!");
				  can_proceed=false;
				}
				if (!can_proceed) {
					return false;
				}
				
				// Salvataggio
				$("#inputhiddencenter_"+center_id+"_D_STATUS").val($("#selectcenter_"+center_id+"_STATUS option:selected").html());
				var post_data = $("tr[id$='center_"+center_id+"'] input, tr[id$='center_"+center_id+"'] select").filter(":not('#divlanguages_"+center_id+" *')").serialize();
				// Disabilito i campi
				$("input[id^='inputcenter_"+center_id+"_']").attr("disabled", true);
				$("#selectcenter_"+center_id+"_COUNTRY").attr("disabled", true);
				$("#selectcenter_"+center_id+"_STATUS").attr("disabled", true);
				$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.loading}");
				// Cancello le icone di undo
				$("#centerundolink_"+center_id).hide();
				// Connectivity check
				connectivityCheck();
				$.ajax({
					type: "POST",
					url: "{$request_uri}",
					data: post_data,
					dataType:	"json",
			  		success: function(data) {
			  			if (data.sstatus == 'ko') {
			  				alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
			  				if (center_id == "NEWCENTER") {
				  				//$("[id^='trcenter_NEWCENTER']").remove();
			  					$("input[id^='inputcenter_"+center_id+"_']").removeAttr("disabled");
			  					// Cambio l'immagine
			  					$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.save}");
			  					// visualizzo le icone di undo
			  					$("#centerundolink_"+center_id).show();
				  			} else {
			  					$("input[id^='inputcenter_"+center_id+"_']").each(function() {
									var field_name = $.trim($(this).attr("id").substr(("inputcenter_"+center_id+"_").length));
									$(this).val($("#viewcenter_"+center_id+"_"+field_name).html());
									$("#viewcenter_"+center_id+"_"+field_name).show();
									$("#editcenter_"+center_id+"_"+field_name).hide();
									$("#centerundolink_"+center_id).hide();
			  					});
				  			}
			  			} else {
							// Cambio i parametri da visualizzare
			  				$.each(data, function(skey, sval) {
			  					if (skey != 'sstatus') {
			  						$("#inputcenter_"+center_id+"_"+skey).val(sval);
									$(("#inputcenter_"+center_id+"_"+skey).replace("input","view")).html(sval);
									$(("#inputcenter_"+center_id+"_"+skey).replace("input","view")).show();
									$(("#inputcenter_"+center_id+"_"+skey).replace("input","edit")).hide();
			  					}
			  				});
				  			if (data.new_center_inserted) {
				  				$("[id*='_NEWCENTER']").each(function() {
				  					$(this).val($(this).val().replace(/NEWCENTER/g, data.ID_CENTER));
				  				});
				  				$("[name*='_NEWCENTER']").each(function() {
				  					$(this).val($(this).val().replace(/NEWCENTER/g, data.ID_CENTER));
				  				});
				  				$("[id*='_NEWCENTER']").each(function() {
				  					$(this).attr("id", $(this).attr("id").replace(/NEWCENTER/g, data.ID_CENTER));
				  				});
				  				$("[name*='_NEWCENTER']").each(function() {
				  					$(this).attr("name", $(this).attr("name").replace(/NEWCENTER/g, data.ID_CENTER));
				  				});
				  				center_id = data.ID_CENTER;
				  				$("#inputhiddencenter_"+center_id+"_ACTION").val("update_center");
				  				$("#inputhiddencenter_"+center_id+"_CODE").val(center_id);
				  				$("#inputhiddencenter_"+center_id+"_ID_CENTER").val(center_id);
				  			}
				  		
			  				// Abilito i campi
							$("input[id^='inputcenter_"+center_id+"_']").removeAttr("disabled");
			  				// Cambio l'immagine
			  				$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
							// Cancello le icone di undo
							$("#centerundolink_"+center_id).hide();
				  			// Unlocko il select status
							$("#selectcenter_"+center_id+"_STATUS").removeAttr("disabled");
							// Locko il select country
							$("#selectcenter_"+center_id+"_COUNTRY").attr("disabled", true);
							// Coloro la riga in base allo status
			  				$("#selectcenter_"+center_id+"_STATUS").closest("tr").removeClass();
							if (data.STATUS == 0) {
			  					$("#divcentereditlink_"+center_id+"_enabled").hide();
			  					$("#divcentereditlink_"+center_id+"_disabled").show();
			  					$("#divcenterialink_"+center_id+"_enabled").hide();
			  					$("#divcenterialink_"+center_id+"_disabled").show();
				  				$("#selectcenter_"+center_id+"_STATUS").closest("tr").addClass("center_disabled");
			  				} else {
			  					$("#divcentereditlink_"+center_id+"_enabled").show();
			  					$("#divcentereditlink_"+center_id+"_disabled").hide();
			  					$("#divcenterialink_"+center_id+"_enabled").show();
			  					$("#divcenterialink_"+center_id+"_disabled").hide();
			  				}
			  				// Tolgo la classe di editing
			  				$("#selectcenter_"+center_id+"_STATUS").closest("tr").removeClass("user_center_selected");
							// Cambio le icone alla selezione delle lingue
			  				$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages}");
							// Cambio le icone all'edit degli utenti del centro
			  				$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit}");
			  			}
			  		}
				});
			} else if ($("#img_centereditlink_"+center_id).attr("src").match(/{$icon_file.edit|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)) {
				// Nascondo i view
				$("div[id^='viewcenter_"+center_id+"_']").each(function() {
					$(this).hide();
				});
				// Visualizzo gli edit
				$("div[id^='editcenter_"+center_id+"_']").each(function() {
					$(this).show();
				});
				// Visualizzo i link undo
				$("#centerundolink_"+center_id).show();
				// Cambio l'icona
				$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.save}");
				// Locko il select status solo se non NEWCENTER
				if (center_id != 'NEWCENTER') {
					$("#selectcenter_"+center_id+"_STATUS").attr("disabled", true);
				}
				// Unlocko il select country
				$("#selectcenter_"+center_id+"_COUNTRY").removeAttr("disabled");
				$("#prev_selectcenter_"+center_id+"_COUNTRY").val($("#selectcenter_"+center_id+"_COUNTRY option:selected").val());
				// Aggiungo l'undo
				$("#centerundolink_"+center_id).undoChangesCenter();
				// Aggiungo la classe di editing
				$("#selectcenter_"+center_id+"_STATUS").closest("tr").addClass("user_center_selected");
				// Cambio le icone alla selezione delle lingue
  				$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages_forbidden}");
				// Cambio le icone all'edit degli utenti del centro
  				$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit_forbidden}");
			}
		});
	};
	
	// Funzione che controlla che sia checkato almeno un linguaggio
	$.fn.checkAtLeastOneLanguage = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			if ($("div.ui-tooltip-content:visible input[type='checkbox']:checked").length == 0) {
				return false;
			}
		});
	};
	
	$.fn.setLanguagesCenter = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var langs_checked = $("div.ui-tooltip-content:visible input[type='checkbox']:checked");
			if (langs_checked.length > 0) {
				var center_id = $(this).attr("id").split("_")[1];
				// Salvataggio
				var post_data = $("div.ui-tooltip-content:visible input[type!='submit']").serialize();
				// Disabilito i campi
				$("div[id^='ui-tooltip']:visible input").attr("disabled", "disabled");
				// Connectivity check
				connectivityCheck();
				$.ajax({
					type: "POST",
					url: "{$request_uri}",
					data: post_data,
					dataType: "json",
			  		success: function(data) {
			  			if (data.sstatus == 'ko') {
			  				alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
			  			} else {
							// Azzero i campi
							$("div[id^='ui-tooltip']:visible input[type='checkbox']").removeAttr("checked");
							$("div[id='divlanguages_"+center_id+"'] input[type='checkbox']").removeAttr("checked");
			  				$.each(data, function(skey, sval) {
			  					if (skey != 'sstatus') {
									$("div[id^='ui-tooltip']:visible input[id='"+skey+"']").attr("checked", "checked");
									$("div[id='divlanguages_"+center_id+"'] input[id='"+skey+"']").attr("checked", "checked");
			  					}
			  				});
				  		}
		  				// Abilito i campi
						$("div[id^='ui-tooltip']:visible input").removeAttr("disabled");
			  		}
				});
			}
			return false;
		});
	};
	
	$.fn.undoChangesCenter = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var center_id = $(this).attr("id").split("_")[1];
			// Visualizzo i view
			$("div[id^='viewcenter_"+center_id+"_']").each(function() {
				$(this).show();
			});
			// Nascondo e resetto gli edit
			$("div[id^='editcenter_"+center_id+"_']").each(function() {
				var field_name = $(this).attr("id").split("_")[2];
				$("#inputcenter_"+center_id+"_"+field_name).val($("#viewcenter_"+center_id+"_"+field_name).html());
				//$("#inputcenter_"+center_id+"_"+field_name).trigger('change');
				// Aggiungo il change per i valori non nulli
				$(mandatory_fields).each(function() {
					$("#inputcenter_"+center_id+"_"+this).trigger('change');
				});
				$(this).hide();
			});
			// Cambio l'icona
			$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
			// Nascondo i link undo
			$("#centerundolink_"+center_id).hide();
			// Locko il select country
			$("#selectcenter_"+center_id+"_COUNTRY").val($("#prev_selectcenter_"+center_id+"_COUNTRY").val());
			$("#selectcenter_"+center_id+"_COUNTRY").attr("disabled", true);
			// Tolgo la classe di editing
			$("#selectcenter_"+center_id+"_STATUS").closest("tr").removeClass("user_center_selected");
			// Unlocko lo status
			$("#selectcenter_"+center_id+"_STATUS").removeAttr("disabled");
			if (center_id == 'NEWCENTER') {
				$("#trcenter_"+center_id).remove();
				$("#trcenter_"+center_id+"_users").remove();
			}
			// Cambio le icone alla selezione delle lingue
			$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages}");
			// Cambio le icone all'edit degli utenti del centro
			$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit}");
		});
	};

	$.fn.addEnableDisableCenter = function() {
		//$(this).unbind('change');
		$(this).bind('change', function() {
			var mySelect = this;
			var center_id = $(this).attr("id").split("_")[1];
			if ($("#img_centereditlink_"+center_id).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)) {
				return true;
			}
			// Chiedo conferma
			$("#dialog").dialog("destroy");
			var confirm_change_status = '{$confirm_center_change_status_message}';
			if ($(this).val() == 0) {
				confirm_change_status +='{$confirm_center_disable_message}';
			}
			confirm_change_status +='{$confirm_center_change_status_question}';
			$('<div title="CMM Management"><p style="text-align: center;">'+confirm_change_status.replace(/##CENTER_CODE##/, $("#inputcenter_"+center_id+"_CODE").val())+'</p></div>')
			.dialog({
				modal: true,
				resizable: false,
				draggable: false,
				buttons: {
					'{$confirm_center_change_status_yes_label}': function() {
						$(this).dialog('close');
						// Passo al prossimo passo
						$(mySelect).addEnableDisableCenterConfirmed()
					},
					'{$confirm_center_change_status_no_label}': function() {
						$(this).dialog('close');
						//alert(mySelect);
						$(mySelect).val($("#prev_"+$(mySelect).attr("id")).val());
					}
				}
			});
		});
	};	

	$.fn.addEnableDisableCenterConfirmed = function() {
		// Cambio lo stato del centro partendo dalla select
		var center_id = $(this).attr("id").split("_")[1];
		if (center_id == 'NEWCENTER') {
			return false;
		}
		// Salvataggio 
		$("#inputhiddencenter_"+center_id+"_D_STATUS").val($("#selectcenter_"+center_id+"_STATUS option:selected").html());
		var post_data = $("tr[id$='center_"+center_id+"'] input:hidden, tr[id$='center_"+center_id+"'] select[id$='_STATUS']").filter(":not('#divlanguages_"+center_id+" *')").serialize()
		// Annullo tutti gli editing
		$("#center_"+center_id+"_users a[id^='userundolink_']").trigger('click');
		// Disabilito tutto
		$("#selectcenter_"+center_id+"_STATUS").attr("disabled", true);
		// Disabilito i links
		$("#centereditlink_"+center_id).attr("disabled", true);
		$("#centereditlanguagelink_"+center_id).attr("disabled", true);
		$("#centerialink_"+center_id).attr("disabled", true);
		// cambio le immagini
		$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit_forbidden}");
		$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages_forbidden}");
		$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit_forbidden}");

		// Connectivity check
		connectivityCheck();
		$.ajax({
			type:		"POST",
			url: "{$request_uri}",
			data:	post_data,
			dataType:	"json",
	  		success: function(data) {
		    	// Rimuovo
				$("#selectcenter_"+center_id+"_STATUS").removeAttr("disabled");
				$("#centereditlanguagelink_"+center_id).removeAttr("disabled");
				$("#centereditlink_"+center_id).removeAttr("disabled");
				$("#centerialink_"+center_id).removeAttr("disabled");

				if (data.sstatus == 'ko') {
	  				alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
	  				if ($("#selectcenter_"+center_id+"_STATUS").val() == 1) {
	  					$("#selectcenter_"+center_id+"_STATUS").val(0);
	  				} else {
	  					$("#selectcenter_"+center_id+"_STATUS").val(1);
	  				}
	  			} else {
	  				
	  				$("#selectcenter_"+center_id+"_STATUS").closest("tr").removeClass();
	  				if (data.STATUS == 1) {
	  					$("#divcentereditlink_"+center_id+"_enabled").show();
	  					$("#divcentereditlink_"+center_id+"_disabled").hide();
	  					$("#divcenterialink_"+center_id+"_enabled").show();
	  					$("#divcenterialink_"+center_id+"_disabled").hide();
	  					$("#divcentereditlanguagelink_"+center_id+"_enabled").show();
	  					$("#divcentereditlanguagelink_"+center_id+"_disabled").hide();
	  					$("tr[id^='trcenter_"+center_id+"_user'] select[id^='selectuser_'][id$='_STATUS'][value=0]:not([id*='_CMM_USERID_'])").each(function() {
							// Metto la disabilitazione degli utenti lato server
							//$(this).trigger('change');
							// Quindi eseguo solo gli effetti
							var tr_user = $(this).closest("tr");
							$(tr_user).find("select").attr("disabled", true);
							$(tr_user).removeClass();
			  				$(tr_user).addClass("user_disabled");
			  				var user_id = $(this).attr("id").split("_")[1];
				  			$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit_forbidden}");
						});
	  					// ricambio l'immagine
	  					$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
	  					$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages}");
	  					$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit}");
	  				} else {
	  					$("#divcentereditlink_"+center_id+"_enabled").hide();
	  					$("#divcentereditlink_"+center_id+"_disabled").show();
	  					$("#divcenterialink_"+center_id+"_enabled").hide();
	  					$("#divcenterialink_"+center_id+"_disabled").show();
	  					$("#divcentereditlanguagelink_"+center_id+"_enabled").hide();
	  					$("#divcentereditlanguagelink_"+center_id+"_disabled").show();
		  				//$("#selectcenter_"+center_id+"_STATUS").closest("tr").addClass("center_disabled");
						// ricambio l'immagine
						$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
						$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages}");
						$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit}");
						// Disabilito tutti gli utenti
						if ($("#center_"+center_id+"_users").not(":visible")) {
							$("a[id^='centerialink_"+center_id+"']:visible").trigger('click');
						}
						$("tr[id^='trcenter_"+center_id+"_user'] select[id^='selectuser_'][id$='_STATUS']:not([id*='_CMM_USERID_'])").each(function() {
							$(this).val(0);
							// Metto la disabilitazione degli utenti lato server
							//$(this).trigger('change');
							// Quindi eseguo solo gli effetti
							var tr_user = $(this).closest("tr");
							$(tr_user).find("select").attr("disabled", true);
							$(tr_user).removeClass();
			  				$(tr_user).addClass("user_disabled");
			  				var user_id = $(this).attr("id").split("_")[1];
				  			$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit_forbidden}");
						});
						$("a[id^='centerialink_"+center_id+"']:visible").trigger('click');
	  				}
	  				$("#selectcenter_"+center_id+"_STATUS").val(data.STATUS);

	  				$("#trcenter_"+center_id).removeClass("center_disabled");
	  				if (data.STATUS == 0) {
	  					$("#trcenter_"+center_id).addClass("center_disabled");
	  				}
		  		}
			}
	  	});
	};

	$.fn.addOpenUsersTableLink = function() {
		$(this).unbind('click');
	    $(this).bind('click', function() {
		    var center_id = $(this).attr("id").split("_")[1];
			if ($("#trcenter_"+center_id).hasClass("user_center_selected")) {
				return true;
			}
		    if ($("#trcenter_"+center_id+"_users").is(":visible")) {
			    // Triggo gli undo per gli utenti
		    	$("#trcenter_"+center_id+"_users img[id^='img_userundolink_']:visible").trigger('click');
	            $("#trcenter_"+center_id+"_users").hide();
	            $("#trcenter_"+center_id).removeClass("edit_user_select edit_user_selected_center");
	            $("#trcenter_"+center_id+"_users").removeClass("edit_user_select");
		    	$("#img_centerialink_"+center_id).attr("src", "{$icon_file.edit}");
		    	$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit}");
		    	$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages}");
		    	$("#selectcenter_"+center_id+"_STATUS").removeAttr("disabled");
	            $("#trcenter_"+center_id).removeClass("center_opened_top center_opened_bottom");
	            $("#trcenter_"+center_id+"_users").removeClass("center_opened_top center_opened_bottom");
            } else {
            	// Chiudo gli altri
            	$("tr[id^='trcenter_'][id$='_users']:visible").each(function() {
				    var center_id_link = $(this).attr("id").split("_")[1];
				    $("#centerialink_"+center_id_link+"_enabled").trigger('click'); 
            	});
            	$("#trcenter_"+center_id+"_users").show();
                $("#trcenter_"+center_id).addClass("edit_user_select edit_user_selected_center");
                $("#trcenter_"+center_id+"_users").addClass("edit_user_select");
		    	$("#img_centerialink_"+center_id).attr("src", "{$icon_file.up}");
		    	$("#img_centereditlink_"+center_id).attr("src", "{$icon_file.edit_forbidden}");
		    	$("#img_centereditlanguagelink_"+center_id).attr("src", "{$icon_file.edit_languages_forbidden}");
		    	$("#selectcenter_"+center_id+"_STATUS").attr("disabled", "disabled");
	            $("#trcenter_"+center_id).addClass("center_opened_top");
	            $("#trcenter_"+center_id+"_users").addClass("center_opened_bottom");
            }
        });
    };

	// USERS
	$.fn.addEditLinkUser = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var user_id = $(this).attr("id").split("_")[1];
			var center_id = $(this).closest("tr").attr("id").split("_")[1];
			if (($("#selectcenter_"+center_id+"_STATUS").val() == 0
				&& $("#selectcenter_"+center_id+"_STATUS").is(":disabled"))
				|| ($("#selectuser_"+user_id+"_STATUS").val() == 0
				&& $("#selectuser_"+user_id+"_STATUS").is(":disabled"))
			   ) {
				
				return false;
			}
			//controllo che nessun altro centro o user sia in edit
			editing=false;
			$("img[id^='img_centereditlink_'], img[id^='img_usereditlink_'] ").each(
				function(){
			  		if(!$(this).attr("id").match("img_usereditlink_"+user_id)&&!$(this).attr("id").match(/img_usereditlink_NEWUSER/i)&&!editing&&$(this).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)){
			  			editing=true;
			  		} 
			  	}
			);
			//se sto inserendo un nuovo utente o un nuovo centro
			if(!editing&&!$(this).attr("id").match("usereditlink_NEWUSER")&&($("img[id^='img_usereditlink_NEWUSER'] ").length==1||$("img[id^='img_centereditlink_NEWCENTER'] ").length==1)){
			  editing=true;
			}
			if(editing){
			  	$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit}");
	  		  	return false;
	  	  	}
			if ($("#img_usereditlink_"+user_id).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/))
			{
				var can_proceed = true;
				$(mandatory_fields_user).each(function(key, field) {
					var inputuser_field = $("#inputuser_"+user_id+"_"+field);
					if ($(inputuser_field).val() == ''||$(inputuser_field).val().length>100) {
						can_proceed = false;
					}
				});
				if (!can_proceed) {
					return false;
				}
				// Salvataggio
				$("input[id^='inputuser_"+user_id+"_']").removeAttr("disabled");
				$("select[id^='selectuser_"+user_id+"_']").removeAttr("disabled");
				
				// Post data
				var post_data = $("tr[id$='user_"+user_id+"'] *").filter("input, select").serialize();
				// Disabilito i campi
				$("input[id^='inputuser_"+user_id+"_']").attr("disabled", true);
				$("select[id^='selectuser_"+user_id+"_']").attr("disabled", true);
			  	$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.loading}");
				// Cancello le icone di undo
				$("#userundolink_"+user_id).hide();
				
				
				// Connectivity check
				connectivityCheck();
				$.ajax({
					type: "POST",
					url: "{$request_uri}",
					data: post_data,
					dataType:	"json",
			  		success: function(data) {
			  			if (data.sstatus == 'ko') {
			  				alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
			  				if(data.error=='Center is disabled'){
			  					$("#userundolink_"+user_id).trigger('click'); //faccio partire undoChangesUser per non far visualizzare i dati dell'utente che si stava inserendo
			  				}
			  				$("input[id^='selectuser_"+user_id+"_']").each(function() {
								var field_name = $.trim($(this).attr("id").substr(("selectuser_"+user_id+"_").length));
								$(this).val($("#viewuser_"+user_id+"_"+field_name).html());
								$("#viewuser_"+user_id+"_"+field_name).show();
								$("#edituser_"+user_id+"_"+field_name).hide();
			  				});
							// Cambio l'icona
							$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.save}");
							// Visualizzo i link undo
							$("#userundolink_"+user_id).show();
							// Aggiungo l'undo
							$("#userundolink_"+user_id).undoChangesUser();
			  			} else {
			  				// Cambio i parametri da visualizzare
							$("#viewuser_"+user_id+"_CMM_USERID").html(data.CMM_USERID);
							$("#edituser_"+user_id+"_CMM_USERID").html(data.CMM_USERID);
			  				$.each(data, function(skey, sval) {
			  					if (skey != 'sstatus') {
									$("#inputuser_"+user_id+"_"+skey).val(sval);
									$(("#inputuser_"+user_id+"_"+skey).replace("input","view")).html(sval);
									$(("#inputuser_"+user_id+"_"+skey).replace("input","view")).show();
									$(("#inputuser_"+user_id+"_"+skey).replace("input","edit")).hide();
			  					}
			  				});
			  				
			  				// Cambio l'immagine
			  				$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit}");
							// Mostro l'info
							$("#userinfolink_"+user_id).hide();
							// Cancello le icone di undo
							$("#userundolink_"+user_id).hide();
							
				  			if (data.new_user_inserted) {
					  			// Inserimento nuovo utente
				  				$("[id*='_NEWUSER']").each(function() {
				  					$(this).attr("id", $(this).attr("id").replace(/NEWUSER/g, data.CMM_USERID));
				  				});
				  				$("[name*='_NEWUSER']").each(function() {
				  					$(this).attr("name", $(this).attr("name").replace(/NEWUSER/g, data.CMM_USERID));
				  				});
				  				user_id = data.CMM_USERID;
				  				$("#inputhiddenuser_"+user_id+"_ACTION").val("update_user");
				  				$("#inputhiddenuser_"+user_id+"_CMM_USERID").val(user_id);
				  				$("#inputhiddenuser_"+user_id+"_CODE").val(center_id);

				  				$("#trcenter_"+center_id+"_user_"+user_id).stop().css("background-color", "#FFFF9C");

								//  Mostro il messaggio
								$("#dialog").dialog("destroy");
								var user_creation_info_label = '{$user_creation_info_label}';
								$('<div title="CMM Management"><p style="text-align: center;">'+user_creation_info_label+'</p></div>')
								.dialog({
									modal: true,
									resizable: false,
									draggable: false,
									buttons: {
										'OK': function() {
											$(this).dialog('close');
											// Passo al prossimo passo
											$("#trcenter_"+center_id+"_user_"+user_id).animate({ backgroundColor: "#F6F6F6"},
								  				{ duration: 2500, complete: function() { $(this).css("background-color"); } });
											$("#userinfolink_"+user_id).trigger('click');
										}
									}
								});
				  			}
				  		}
			  			// Abilito i campi
						$("input[id^='inputuser_"+user_id+"_']").removeAttr("disabled");
						// Unlocko lo status
						$("#selectuser_"+user_id+"_STATUS").removeAttr("disabled");
						// Abilito le varie firme
						$("#selectuser_"+user_id+"_ROLE").trigger('change');
						
						// Se lo status è disabilitato
						if (data.STATUS == 0) {
			  				$("#selectuser_"+user_id+"_STATUS").closest("tr").addClass("user_disabled");
							$("#selectuser_"+user_id+"_STATUS").attr("disabled", true);
							$("#selectuser_"+user_id+"_SIGN").attr("disabled", true);
							$("#selectuser_"+user_id+"_SIGNSAE").attr("disabled", true);
		  					$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit_forbidden}");
						}

						// Abilito il link alle user info
						$("#userinfolink_"+user_id).show();
						$("#userinfolink_"+user_id).addUserInfo();

						$("#trcenter_"+center_id+"_user_"+user_id).removeClass().animate({ backgroundColor: "#F6F6F6"},
				  				{ duration: 2500, complete: function() {
					  				$(this).css("background-color");
									// Coloro la riga in base allo status
					  				$(this).delay(1500);
									if (data.STATUS == 0) {
										$(this).addClass("user_disabled");
						  				$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit_forbidden}");
					  				}
								}
				  			}
		  				);
			  		}
				});
				
			} else if ($("#img_usereditlink_"+user_id).attr("src").match(/{$icon_file.edit|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)) {
				// Nascondo i view
				$("div[id^='viewuser_"+user_id+"_']").each(function() {
					$(this).hide();
				});
				// Visualizzo gli edit
				$("div[id^='edituser_"+user_id+"_']").each(function() {
					$(this).show();
				});
				// Visualizzo i link undo
				$("#userundolink_"+user_id).show();
				// Nascondo L'info
				$("#userinfolink_"+user_id).hide();
				// Cambio l'icona
				$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.save}");
				// Locko il select status e sign solo se non NEWUSER
				if (user_id != 'NEWUSER') {
					$("select[id^='selectuser_"+user_id+"']").attr("disabled", true);
				} else {
					$("#selectuser_"+user_id+"_ROLE").removeAttr("disabled");
					$("#prev_selectuser_"+user_id+"_ROLE").val($("#selectuser_"+user_id+"_ROLE").val());
				}
				// Aggiungo l'undo
				$("#userundolink_"+user_id).undoChangesUser();
				// Triggo la funzione per il disable/enable della firma
				$("#selectuser_"+user_id+"_ROLE").trigger('change');
			}
		});
	};
	
	$.fn.undoChangesUser = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var user_id = $(this).attr("id").split("_")[1];
			// Visualizzo i view
			$("div[id^='viewuser_"+user_id+"_']").each(function() {
				$(this).show();
			});
			// Nascondo e resetto gli edit
			$("div[id^='edituser_"+user_id+"_']").each(function() {
				var field_name = $(this).attr("id").split("_")[2];
				$("#inputuser_"+user_id+"_"+field_name).val($("#viewuser_"+user_id+"_"+field_name).html());
				//$("#inputuser_"+user_id+"_"+field_name).trigger('change');
				// Aggiungo il change per i valori non nulli
				$(mandatory_fields_user).each(function() {
					$("#inputuser_"+user_id+"_"+this).trigger('change');
				});
				$(this).hide();
			});
			// Cambio l'icona
			$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit}");
			// Nascondo i link undo
			$("#userundolink_"+user_id).hide();
			// Abilito il link alle user info
			$("#userinfolink_"+user_id).show();
			$("#userinfolink_"+user_id).addUserInfo();
			// Unlocko lo status
			$("#selectuser_"+user_id+"_STATUS").removeAttr("disabled");
			// Aggiorno l'abilitazione alle firme
			$("#selectuser_"+user_id+"_ROLE").trigger('change');
			if (user_id == 'NEWUSER') {
				$("tr[id^='tr'][id$='_user_"+user_id+"']").remove();
			}
		});
	};

	$.fn.addEnableDisableStatusAndSignUser = function() {
		//$(this).unbind('change');
		$(this).bind('change', function() {
			var user_id = $(this).attr("id").split("_")[1];
			if (user_id == 'NEWUSER') {
				
				return false;
			}
			/**
			* NUOVO SVILUPPO 20/01/2012
			* Al momento in cui viene disabilitata la firma eCRF deve essere disabilitata in automatico anche la firma eSAE e viceversa.
			* L'abilitazione di una firma eCRF, comporta in automatico l'abilitazione della firma eSAE, e viceversa.
			* 
			* V. Mazzeo
			**/
			var this_is_sign='selectuser_'+user_id+'_SIGN';
			var this_is_signsae='selectuser_'+user_id+'_SIGNSAE';
			var this_is_status='selectuser_'+user_id+'_STATUS';
			if($(this).attr("id")==this_is_sign)
			{
				//alert($("#"+this_is_sign).val());
				$("#selectuser_"+user_id+"_SIGNSAE").val($("#"+this_is_sign).val());
				//alert($("#selectuser_"+user_id+"_SIGNSAE").attr("disabled"));
			}
			else if($(this).attr("id")==this_is_signsae)
			{
				//alert($("#"+this_is_signsae).val());
				$("#selectuser_"+user_id+"_SIGN").val($("#"+this_is_signsae).val());
				//alert($("#selectuser_"+user_id+"_SIGNSAE").attr("disabled"));
			}
			else if($(this).attr("id")==this_is_status){
				//alert($(this).attr("id")+" "+$(this).val());
				if($(this).val()=='0'){ //se sto disabilitando
					var user_confirm_disable_label = '{$user_confirm_disable_label}';
					var answer=confirm(user_confirm_disable_label);
					if(!answer){
						$(this).val('1');
						return false;
					}
				}			
			}
			/** FINE NUOVO SVILUPPO 20/01/2012 **/
			
			
			
			
			// Salvo i dati
			$("#inputhidden_"+user_id+"_D_STATUS").val($("#selectuser_"+user_id+"_STATUS option:selected").html());
			$("#inputhidden_"+user_id+"_D_SIGN").val($("#selectuser_"+user_id+"_SIGN option:selected").html());
			$("#inputhidden_"+user_id+"_D_SIGNSAE").val($("#selectuser_"+user_id+"_SIGNSAE option:selected").html());

			// Hack sporco per far scrivere il valore del select role
			$("tr[id$='user_"+user_id+"'] select[id$='_ROLE']").removeAttr("disabled");
			var post_data = $("tr[id$='user_"+user_id+"'] *")
				.filter("input[id^='inputhiddenuser_'], select[id$='_ROLE'], select[id$='_STATUS'], select[id*='_SIGN']").serialize();
			$("tr[id$='user_"+user_id+"'] select[id$='_ROLE']").attr("disabled", "disabled");

			$("#selectuser_"+user_id+"_STATUS").attr("disabled", true);
			$("#selectuser_"+user_id+"_SIGN").attr("disabled", true);
			$("#selectuser_"+user_id+"_SIGNSAE").attr("disabled", true);
			$("#usereditlink_"+user_id).attr("disabled", true);
			$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.loading}");
			
			
			// Connectivity check
			connectivityCheck();

			$.ajax({
				type:		"POST",
				url: "{$request_uri}",
				data:	post_data,
				dataType:	"json",
		  		success: function(data) {
		  			if (data.sstatus == 'ko') {
		  				alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
						$("#selectuser_"+user_id+"_STATUS").val($("#prev_selectuser_"+user_id+"_STATUS").val());
						$("#selectuser_"+user_id+"_SIGN").val($("#prev_selectuser_"+user_id+"_SIGN").val());
						$("#selectuser_"+user_id+"_SIGNSAE").val($("#prev_selectuser_"+user_id+"_SIGNSAE").val());
			  			} else {
		  				// Esito positivo
		  				$("#selectuser_"+user_id+"_STATUS").closest("tr").removeClass();
		  				$("#selectuser_"+user_id+"_STATUS").val(data.STATUS);
						$("#prev_selectuser_"+user_id+"_STATUS").val($("#selectuser_"+user_id+"_STATUS").val());
						$("#prev_selectuser_"+user_id+"_SIGN").val($("#selectuser_"+user_id+"_SIGN").val());
						$("#prev_selectuser_"+user_id+"_SIGNSAE").val($("#selectuser_"+user_id+"_SIGNSAE").val());
		  				// Aggiorni gli eventuali parametri
		  				$.each(data, function(skey, sval) {
		  					if (skey != 'sstatus') {
								$("#inputuser_"+user_id+"_"+skey).val(sval);
								$(("#inputuser_"+user_id+"_"+skey).replace("input","view")).html(sval);
								$.each(mandatory_fields_user, function(svalue2) {
									if (skey == svalue2) {
										$(("#inputuser_"+user_id+"_"+skey).replace("input","edit")).html(sval);
									}
								});
								$(("#inputuser_"+user_id+"_"+skey).replace("input","view")).show();
								$(("#inputuser_"+user_id+"_"+skey).replace("input","edit")).hide();
		  					}
		  				});
			  		}
					// Rimuovo attributi disabled
					$("#selectuser_"+user_id+"_STATUS").removeAttr("disabled");
					switch(data.ROLE){
						
						case "13":
							// Co Principal Investigator
							$("#selectuser_"+user_id+"_SIGNSAE").removeAttr("disabled");
							break;
						case "12":
							// Principal Investigator
							$("#selectuser_"+user_id+"_SIGNSAE").removeAttr("disabled");
							$("#selectuser_"+user_id+"_SIGN").removeAttr("disabled");
							break;
						case "11":
							// Investigator
							break;
					}
					
					
					// Abilito o meno le firme
					//$("#selectuser_"+user_id+"_ROLE").trigger('change');
					$("#usereditlink_"+user_id).removeAttr("disabled");
	  				$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit}");
					// Se lo stato è negativo
	  				if (data.STATUS == 0) {
		  				$("#selectuser_"+user_id+"_STATUS").closest("tr").addClass("user_disabled");
						$("#selectuser_"+user_id+"_STATUS").attr("disabled", true);
						$("#selectuser_"+user_id+"_SIGN").attr("disabled", true);
						$("#selectuser_"+user_id+"_SIGNSAE").attr("disabled", true);
		  				$("#img_usereditlink_"+user_id).attr("src", "{$icon_file.edit_forbidden}");
	  				}
			  	}
		  	});
		});
	};
	
	// Aggiungo il change per i valori non nulli
	$.fn.addInputChange = function() {
	  	$(this).unbind('change');
		$(this).change(function() {
		  var img_editlink_id, 
				temp_mandatory_fields,
				temp_email_fields,
				temp_number_only_fields,
				temp_max_lenght_fields,
				inputelement_id;
			var element_id = $(this).attr("id").split("_")[1];
			if ($(this).attr("id").match(/inputcenter/i)) {
				// Input change dei centri
				img_editlink_id = "#img_centereditlink_";
				temp_mandatory_fields = mandatory_fields;
				temp_email_fields = email_fields;
				temp_number_only_fields = number_only_fields;
				temp_max_lenght_fields = max_lenght_fields;
				inputelement_id = "#inputcenter_";
			}
			if ($(this).attr("id").match(/inputuser/i)) {
				// Input change degli utenti
				img_editlink_id = "#img_usereditlink_";
				temp_mandatory_fields  = mandatory_fields_user;
				temp_email_fields = email_fields_user;
				temp_number_only_fields = number_only_fields_user;
				temp_max_lenght_fields = max_lenght_fields_user;
				inputelement_id = "#inputuser_";
			}
			// Aggiungo il tooltip
			if ($(this).val() == ''||($(this).attr("id").match(/CODE/)&&$(this).val().length>{$siteid_lenght})||$(this).val().length>100) {
			  	if($(this).attr("id").match(/CODE/)&&{$siteid_lenght}!=''){
			  		$(this).addWarningQTip('{$siteid_length_message}');
			  	}
			  	else{
			  		$(this).addWarningQTip('{$mandatory_field_message}');  
			  	}
				
				$(this).css("border", "1px #C2D6F3 solid");
				// Cambio l'icona
				$(img_editlink_id+element_id).attr("src", "{$icon_file.save_forbidden}");
			}else if ($(this).val() != ''&&$(this).attr("id").match(/CODE/)&&$(this).val().length>{$siteid_lenght}) {
				$(this).addWarningQTip('{$siteid_length_message}');
				$(this).css("border", "1px #C2D6F3 solid");
				// Cambio l'icona
				$(img_editlink_id+element_id).attr("src", "{$icon_file.save_forbidden}");
			} else {
				$(this).qtip('destroy');
				$(this).css("border", "");
				// Cambio l'icona
				var can_proceed = true;
				$(temp_number_only_fields).each(function(key, field) {
				  	//alert("CHECK temp_number_only_fields "+field);
				  	var numbercheck = new RegExp("^[0-9]*$");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&!numbercheck.test($(inputelement_field).val())||$(inputelement_field).val().length>50) {
						can_proceed = false;
					}
				});
				$(temp_max_lenght_fields).each(function(key, field) {
				  	//alert("CHECK temp_max_lenght_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_email_fields).each(function(key, field) {
				    //alert("CHECK temp_email_fields"+field);
				  	var mailcheck = new RegExp(".+@(.+\\.)+.+");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if (!mailcheck.test($(inputelement_field).val())||$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_mandatory_fields).each(function(key, field) {
				    //alert("CHECK temp_mandatory_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val() == '') {
						can_proceed = false;
					}
				});
				if (can_proceed) {
					$(img_editlink_id+element_id).attr("src", "{$icon_file.save}");
				}
			}
		});
	};
	
	// Aggiungo il change per i valori non numerici
	$.fn.addCheckNumber = function() {
		$(this).unbind('change');
		$(this).change(function() {
		  	
			var img_editlink_id, 
			temp_mandatory_fields,
			temp_email_fields,
			temp_number_only_fields,
			temp_max_lenght_fields,
			inputelement_id;
			var element_id = $(this).attr("id").split("_")[1];
			if ($(this).attr("id").match(/inputcenter/i)) {
				// Input change dei centri
				img_editlink_id = "#img_centereditlink_";
				temp_mandatory_fields = mandatory_fields;
				temp_email_fields = email_fields;
				temp_number_only_fields = number_only_fields;
				temp_max_lenght_fields = max_lenght_fields;
				inputelement_id = "#inputcenter_";
			}
			if ($(this).attr("id").match(/inputuser/i)) {
				// Input change degli utenti
				img_editlink_id = "#img_usereditlink_";
				temp_mandatory_fields  = mandatory_fields_user;
				temp_email_fields = email_fields_user;
				temp_number_only_fields = number_only_fields_user;
				temp_max_lenght_fields = max_lenght_fields_user;
				inputelement_id = "#inputuser_";
			}
			// Aggiungo il tooltip
			var numbercheck = new RegExp("^[0-9]*$");
			// Aggiungo il tooltip
			//alert($(this).attr("id")+" "+$(this).val()+" MATCH? "+numbercheck.test($(this).val()));
			if ($(this).val()!=''&&!numbercheck.test($(this).val())||$(this).val().length>50) {
			
			  $(this).addWarningQTip('{$only_number_field_message}');
				$(this).css("border", "1px #C2D6F3 solid");
				// Cambio l'icona
				$(img_editlink_id+element_id).attr("src", "{$icon_file.save_forbidden}");
			} else {
				$(this).qtip('destroy');
				$(this).css("border", "");
				// Cambio l'icona
				var can_proceed = true;
				$(temp_number_only_fields).each(function(key, field) {
				  	//alert("CHECK temp_number_only_fields "+field);
				  	var numbercheck = new RegExp("^[0-9]*$");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&!numbercheck.test($(inputelement_field).val())||$(inputelement_field).val().length>50) {
						can_proceed = false;
					}
				});
				$(temp_max_lenght_fields).each(function(key, field) {
				  	//alert("CHECK temp_max_lenght_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_email_fields).each(function(key, field) {
				    //alert("CHECK temp_email_fields"+field);
				  	var mailcheck = new RegExp(".+@(.+\\.)+.+");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if (!mailcheck.test($(inputelement_field).val())||$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_mandatory_fields).each(function(key, field) {
				    //alert("CHECK temp_mandatory_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val() == '') {
						can_proceed = false;
					}
				});
				if (can_proceed) {
					$(img_editlink_id+element_id).attr("src", "{$icon_file.save}");
				}
			}
		});
	};

	
	// Aggiungo il change per i valori alfanumerici ma con size <100
	$.fn.addCheckSize = function() {
	  	//alert($(this).attr("id"));
		$(this).unbind('change');
		$(this).change(function() {
		  	
		  	var img_editlink_id, 
			temp_mandatory_fields,
			temp_email_fields,
			temp_number_only_fields,
			temp_max_lenght_fields,
			inputelement_id;
			var element_id = $(this).attr("id").split("_")[1];
			if ($(this).attr("id").match(/inputcenter/i)) {
				// Input change dei centri
				img_editlink_id = "#img_centereditlink_";
				temp_mandatory_fields = mandatory_fields;
				temp_email_fields = email_fields;
				temp_number_only_fields = number_only_fields;
				temp_max_lenght_fields = max_lenght_fields;
				inputelement_id = "#inputcenter_";
			}
			if ($(this).attr("id").match(/inputuser/i)) {
				// Input change degli utenti
				img_editlink_id = "#img_usereditlink_";
				temp_mandatory_fields  = mandatory_fields_user;
				temp_email_fields = email_fields_user;
				temp_number_only_fields = number_only_fields_user;
				temp_max_lenght_fields = max_lenght_fields_user;
				inputelement_id = "#inputuser_";
			}
			// Aggiungo il tooltip
			// Aggiungo il tooltip
			//alert($(this).attr("id")+" "+$(this).val()+" MATCH? "+numbercheck.test($(this).val()));
			if ($(this).val()!=''&&$(this).val().length>100) {
			
			  $(this).addWarningQTip('{$max_lenght_fields_message}');
				$(this).css("border", "1px #C2D6F3 solid");
				// Cambio l'icona
				$(img_editlink_id+element_id).attr("src", "{$icon_file.save_forbidden}");
			} else {
				$(this).qtip('destroy');
				$(this).css("border", "");
				// Cambio l'icona
				var can_proceed = true;
				$(temp_number_only_fields).each(function(key, field) {
				  	//alert("CHECK temp_number_only_fields "+field);
				  	var numbercheck = new RegExp("^[0-9]*$");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&!numbercheck.test($(inputelement_field).val())||$(inputelement_field).val().length>50) {
						can_proceed = false;
					}
				});
				$(temp_max_lenght_fields).each(function(key, field) {
				  	//alert("CHECK temp_max_lenght_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_email_fields).each(function(key, field) {
				    //alert("CHECK temp_email_fields"+field);
				  	var mailcheck = new RegExp(".+@(.+\\.)+.+");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if (!mailcheck.test($(inputelement_field).val())||$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_mandatory_fields).each(function(key, field) {
				    //alert("CHECK temp_mandatory_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val() == '') {
						can_proceed = false;
					}
				});
				if (can_proceed) {
					$(img_editlink_id+element_id).attr("src", "{$icon_file.save}");
				}
			}
		});
	};
	// Aggiungo il change per icampi email
	$.fn.addEmailInputChange = function() {
		$(this).unbind('change');
		$(this).change(function() {
		  	var img_editlink_id, 
			temp_mandatory_fields,
			temp_email_fields,
			temp_number_only_fields,
			temp_max_lenght_fields,
			inputelement_id;
			var element_id = $(this).attr("id").split("_")[1];
			if ($(this).attr("id").match(/inputcenter/i)) {
				// Input change dei centri
				img_editlink_id = "#img_centereditlink_";
				temp_mandatory_fields = mandatory_fields;
				temp_email_fields = email_fields;
				temp_number_only_fields = number_only_fields;
				temp_max_lenght_fields = max_lenght_fields;
				inputelement_id = "#inputcenter_";
			}
			if ($(this).attr("id").match(/inputuser/i)) {
				// Input change degli utenti
				img_editlink_id = "#img_usereditlink_";
				temp_mandatory_fields  = mandatory_fields_user;
				temp_email_fields = email_fields_user;
				temp_number_only_fields = number_only_fields_user;
				temp_max_lenght_fields = max_lenght_fields_user;
				inputelement_id = "#inputuser_";
			}
			//var filter = '([a-zA-Z0-9_\.\-])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9])+';
			var mailcheck = new RegExp(".+@(.+\\.)+.+");
			//var mailcheck = new RegExp(filter);
			// Aggiungo il tooltip
			if (!mailcheck.test($(this).val())||$(this).val().length>100) {
			//if (!filter.test($(this).val())) {
				//Stringa non è una mail
				$(this).addWarningEmailQTip();
				$(this).css("border", "1px #C2D6F3 solid");
				// Cambio l'icona
				$(img_editlink_id+element_id).attr("src", "{$icon_file.save_forbidden}");
			} else {
				$(this).qtip('destroy');
				$(this).css("border", "");
				// Cambio l'icona
				var can_proceed = true;
				$(temp_number_only_fields).each(function(key, field) {
				  	//alert("CHECK temp_number_only_fields "+field);
				  	var numbercheck = new RegExp("^[0-9]*$");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&!numbercheck.test($(inputelement_field).val())||$(inputelement_field).val().length>50) {
						can_proceed = false;
					}
				});
				$(temp_max_lenght_fields).each(function(key, field) {
				  	//alert("CHECK temp_max_lenght_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val()!=''&&$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_email_fields).each(function(key, field) {
				    //alert("CHECK temp_email_fields"+field);
				  	var mailcheck = new RegExp(".+@(.+\\.)+.+");
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if (!mailcheck.test($(inputelement_field).val())||$(inputelement_field).val().length>100) {
						can_proceed = false;
					}
				});
				$(temp_mandatory_fields).each(function(key, field) {
				    //alert("CHECK temp_mandatory_fields"+field);
					var inputelement_field = $(inputelement_id+element_id+"_"+field);
					if ($(inputelement_field).val() == '') {
						can_proceed = false;
					}
				});
				if (can_proceed) {
					$(img_editlink_id+element_id).attr("src", "{$icon_file.save}");
				}
			}
		});
	};

	// Trigger per il cambio ruolo
    $.fn.addChangeRoleUser = function() {
		$(this).unbind('change');
		$(this).bind('change', function() {
			var center_id;
			var user_id = $(this).attr("id").split("_")[1];
			if ($("#selectuser_"+user_id+"_STATUS").val() != 1) {
				// Disabilito tutto se l'utente è disabilitato
				$("select[id^='selectuser_"+user_id+"_SIGN']").attr("disabled", true);
				return true;
			}

			if ($(this).val() > 10 && $(this).closest("table[id$='_users']").attr("id").match(/center/)) {
				// Investigator o Principal Investigator
				center_id = $(this).closest("tr[id^='trcenter_']").attr("id").split("_")[1];
			} else if ($(this).val() <= 10 && $(this).closest("table[id$='_users']").attr("id").match(/global/)) {
				// Utenti globali
				center_id = '99'+$(this).val();
			}
			if (center_id !== undefined) {
				$(this).siblings("input[type='hidden'][id^='inputhiddenuser_'][id$='_ID_CENTER']").val(center_id);
				$(this).siblings("input[type='hidden'][id^='inputhiddenuser_'][id$='_CODE']").val($("inputcenter_"+center_id+"_CODE").val());
			}
			// Abilitazione o meno dei select sulle firme
			$("select[id^='selectuser_"+user_id+"_SIGN']").attr("disabled", true);
			switch($(this).val()){
				
				case "13":
					// Co Principal Investigator
					$("#selectuser_"+user_id+"_SIGNSAE").removeAttr("disabled");
					if(user_id=="NEWUSER"){ //metto i valodi di default solo nel caso in cui � un nuovo utente altrimenti restano quelli presi dalla select in db
						$("#selectuser_"+user_id+"_SIGNSAE").val(1);
						$("#selectuser_"+user_id+"_SIGN").val(0);
					}
					break;
				case "12":
					// Principal Investigator
					$("#selectuser_"+user_id+"_SIGNSAE").removeAttr("disabled");
					$("#selectuser_"+user_id+"_SIGN").removeAttr("disabled");
					if(user_id=="NEWUSER"){ //metto i valodi di default solo nel caso in cui � un nuovo utente altrimenti restano quelli presi dalla select in db
						$("#selectuser_"+user_id+"_SIGNSAE").val(1);
						$("#selectuser_"+user_id+"_SIGN").val(1);	
					}
					break;
				case "11":
					// Investigator
					if(user_id=="NEWUSER"){ //metto i valodi di default solo nel caso in cui � un nuovo utente altrimenti restano quelli presi dalla select in db
						$("#selectuser_"+user_id+"_SIGNSAE").val(0);
						$("#selectuser_"+user_id+"_SIGN").val(0);	
					}
					break;
			}
			// Copio i valori negli hidden
			$("#inputhiddenuser_"+user_id+"_D_SIGN").val($("#selectuser_"+user_id+"_SIGN").find("option:selected").text());
			$("#inputhiddenuser_"+user_id+"_D_SIGNSAE").val($("#selectuser_"+user_id+"_SIGNSAE").find("option:selected").text());
			$("#inputhiddenuser_"+user_id+"_D_ROLE").val($(this).find("option:selected").text());
		});
	};

	// Apro il report dell'utente in una nuova pagina
	$.fn.addUserInfo = function () {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var center_id;
			var user_id = $(this).attr("id").split("_")[1];
			// Mostro l'icona di loading
			$("#img_userinfolink_"+user_id).attr("src", "{$icon_file.loading}");

			// Connectivity check
			connectivityCheck();

			$.ajax({
				type: "POST",
				url: "{$request_uri}",
				data: "ACTION=get_user_info&CMM_USERID="+user_id,
				dataType:	"json",
				success: function(data) {
					if (data.sstatus == 'ko') {
						alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
					} else {
						// Visualizzo le info dell'utente
						var divuserinfo = $("#divuserinfo").clone();
						// Sostiuisco i vari dati
						$(divuserinfo).find("#divurl").html($(divuserinfo).find("#divurl").html().replace(/#URL#/, $.url().attr('base')));
						$(divuserinfo).find("#divusername").html($(divuserinfo).find("#divusername").html().replace(/#USERNAME#/, data.CMM_USERID));
						//alert("FIRST PWD: "+data.FIRST_PASSWORD);
						//$(divuserinfo).find("#divpassword").html().replace(/#PASSWORD#/, data.FIRST_PASSWORD);
						$(divuserinfo).find("#divpassword").html($(divuserinfo).find("#divpassword").html().replace(/#PASSWORD#/, data.FIRST_PASSWORD));
						$(divuserinfo).find("#divpassword").html(data.FIRST_PASSWORD);//setto cos� l'html perch� altrimenti perde caratteri finali della stringa
						//alert("FIRST PWD div: "+$(divuserinfo).find("#divpassword").html());
						$(divuserinfo).find("#divfirstname").html($(divuserinfo).find("#divfirstname").html().replace(/#FIRSTNAME#/, data.NAME));
						$(divuserinfo).find("#divlastname").html($(divuserinfo).find("#divlastname").html().replace(/#LASTNAME#/, data.SURNAME));
						$(divuserinfo).find("#divemail").html($(divuserinfo).find("#divemail").html().replace(/#EMAIL#/, data.EMAIL));
						$(divuserinfo).find("#divrole").html($(divuserinfo).find("#divrole").html().replace(/#ROLE#/, data.D_ROLE));
						$(divuserinfo).find("#divcreationdate").html($(divuserinfo).find("#divcreationdate").html().replace(/#CREATION_DATE#/, data.CREATEDT));
						if (data.MAIL_SENT != "Y") {
							$(divuserinfo).find("#divemailtable").show();
							$(divuserinfo).find("a[id^='aemailtable_']").attr("id", "aemailtable_"+data.CMM_USERID);
							/// PROVO A CAMBIARE HREF MAILTO
							var service_name=$.url().attr('base').substring(($.url().attr('base').indexOf("/",0)+2),$.url().attr('base').indexOf(".",0));
							$(divuserinfo).find("a[id^='sendmail_info']").attr("href", 	"mailto:"+data.EMAIL+"?subject="+service_name+" registration&body=User Info%0A"+"url:"+$.url().attr('base')+"%0AUsername: "+data.CMM_USERID+"%0ARole: "+data.D_ROLE+"%0ACreation date: "+data.CREATEDT+"%0AName: "+data.NAME+"%0ASurname: "+data.SURNAME+"%0Aemail: "+data.EMAIL);
							$(divuserinfo).find("a[id^='sendmail_pwd']").attr("href", 	"mailto:"+data.EMAIL+"?subject="+service_name+" registration&body=First Password: "+escape(data.FIRST_PASSWORD));
							$(divuserinfo).find("#img_senduserinfolink_spinning").hide();
						} else {
							$(divuserinfo).find("#divemailtable").hide();
						}

						var html = "<html><head><title>Print User info</title></head><body><div id=\"divuserinfo\">"+$(divuserinfo).html()+"</div></body></html>";

						var windowuserinfo =  window.open('','UserInfoWindow','width=500,height=600');
						if (!windowuserinfo || windowuserinfo.closed || windowuserinfo == null || typeof(windowuserinfo)=='undefined') {  
							//  Mostro il messaggio
							if (!$("#dialog").is(':visible')) {
								$("#dialog").dialog("destroy");
								var popup_block_info_label = '{$popup_block_info_label}';
								$('<div title="CMM Management"><p style="text-align: center;"><span class="ui-icon ui-icon-alert" style="float:left; margin:0 7px 50px 0;"></span>'+popup_block_info_label+'</p></div>')
								.dialog({
									modal: true,
									resizable: false,
									draggable: false,
									buttons: {
										'OK': function() {
											$(this).dialog('close');
										}
									}
								});
							} 
						} else {
							windowuserinfo.document.open();
							windowuserinfo.document.write(html);
							windowuserinfo.document.close();
							//ABILITO LA CHIAMATA A addSendUserInfo(windowuserinfo) per far aprire client di posta (vedi sotto c'� mailto)
							$(windowuserinfo.document).find("#aemailtable_"+data.CMM_USERID).addSendUserInfo(windowuserinfo);
							//DISABILITO LA CHIAMATA A setmailSent(windowuserinfo) per far aprire client di posta (vedi sotto c'� mailto)
							//$(windowuserinfo.document).find("#check_mail_sent").setMailSent(windowuserinfo);
						}

						// Mostro l'icona di info
						$("#img_userinfolink_"+user_id).attr("src", "{$icon_file.info}");
					}
				}
			});

		    return false;
		});
	};

	// Aggiungo il link per mandare l'email
	$.fn.addSendUserInfo = function (windowuserinfo) {
		$(this).unbind('click');
		$(this).bind('click', function() {
			
			var user_id = $(this).attr("id").split("_")[1];
			var image_info = $(windowuserinfo.document).find("[id='img_senduserinfolink_spinning']");
			var link_info = $(windowuserinfo.document).find("a[id^='aemailtable_']");
			var link_send_info = $(windowuserinfo.document).find("[id='sendmail_info']");
			var link_send_pwd = $(windowuserinfo.document).find("[id='sendmail_pwd']");
			// Mostro l'icona di loading
			$(image_info).show();

			// Connectivity check
			connectivityCheck();

			$.ajax({
				type: "POST",
				url: "{$request_uri}",
				data: "ACTION=send_user_info&CMM_USERID="+user_id,
				dataType:	"json",
				success: function(data) {
					if (data.sstatus == 'ko') {
						alert("ERRORE\n"+data.error+"\n"+data.detail.toString());
					} else {
						$(image_info).attr("src", "{$icon_file.ok}").stop(true,true).delay(3000).fadeOut('slow', function() {  $(image_info).attr("src", "{$icon_file.loading}"); $(link_send_info).hide();$(link_send_pwd).hide();$(link_info).hide(); $("#img_usersentmail_"+user_id).show();});
						
					}
				}
			});
		    return false;
		});
	};
	// Function per lo switch del country
	$.fn.addSelectCountryHiddenCopy = function() {
		$(this).bind('change', function() {
			$("#inputhiddencenter_"+$(this).attr("id").split("_")[1]+"_D_COUNTRY").val($("#"+$(this).attr("id")+" option:selected").text());
		});
	};
	
	// Function per lo switch dei select dello user
	$.fn.addSelectStatusSignUserHiddenCopy = function() {
		$(this).bind('change', function() {
			if ($("#"+$(this).attr("id").split("_")[0].replace(/select/, 'inputhidden')
				+"_"+$(this).attr("id").split("_")[1]
				+"_D_"+$(this).attr("id").split("_")[2]).length > 0) {
				$("#"+$(this).attr("id").split("_")[0].replace(/select/, 'inputhidden')
					+"_"+$(this).attr("id").split("_")[1]
					+"_D_"+$(this).attr("id").split("_")[2]).val($("#"+$(this).attr("id")+" option:selected").text());
			}

/*			// Coloro le select
			$(this).removeClass();
			if ($(this).val() == 1) {
				$(this).addClass("option_enabled");
			} else if ($(this).val() == 0) {
				$(this).addClass("option_disabled");
			}
*/		});
	};

	// Aggiungo la funzione per aggiungere gli utenti ai centri
	$.fn.addAddUserToCenter = function() {
		$(this).unbind("click");
		$(this).bind("click", function() {
			var center_id = $(this).closest("table").attr("id").split("_")[1];
			if ($("#selectcenter_"+center_id+"_STATUS").val() == 0
				&& $("#selectcenter_"+center_id+"_STATUS").is(":disabled")) {
				return false;
			}
			var tr_to_copy, users_table, new_tr_id;
			if ($(this).attr("id").match(/global/i)) {
				// Utenti globali
				tr_to_copy = "#trglobal_user_to_copy";
				users_table = "#global_users";
				new_tr_id = "trglobal_user_NEWUSER";
			} else {
				// Utenti dei vari centri (Investigator o Principal Investigator)
				var center_id = $(this).attr("id").split("_")[3];
				tr_to_copy = "#trcenter_"+center_id+"_user_to_copy";
				users_table = "#center_"+center_id+"_users";
				new_tr_id = "trcenter_"+center_id+"_user_NEWUSER";
			}
			//controllo che nessun altro centro o user sia in edit
			editing=false;
			$("img[id^='img_centereditlink_'], img[id^='img_usereditlink_'] ").each(
				function(){
			  		if(!$(this).attr("id").match(/img_centereditlink_NEWCENTER/i)&&!editing&&$(this).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)){
			  			editing=true;
			  		} 
			  	}
			);
			if (!editing&&$("#viewcenter_NEWCENTER_CODE").length == 0 && $("#viewedituser_NEWUSER_ROLE").length == 0) {
  				var new_tr = $(tr_to_copy).html()
  					.replace(/CMM_USERID/g, "NEWUSER")
  					.replace(/NEWUSER_NEWUSER/g, "NEWUSER_CMM_USERID");
				// Copio il tr	  				
				$(users_table+" > tbody:last").append('<tr id="'+new_tr_id+'">'+new_tr+'</tr>');
				// Aggiungo il link per l'edit dell'utente
				$("#usereditlink_NEWUSER").addEditLinkUser();
				// Aggiungo il select per lo status
				$("#selectuser_NEWUSER_STATUS").addSelectStatusSignUserHiddenCopy();
				$("#selectuser_NEWUSER_STATUS").addEnableDisableStatusAndSignUser();
				
				$("#selectuser_NEWUSER_STATUS").val(1);
				$("#selectuser_NEWUSER_STATUS").trigger('change');
				$("#selectuser_NEWUSER_STATUS").attr("disabled",true);//NON FACCIO SELEZIONARE LO STATUS DISABLED PER IL NUOVO UTENTE INSERITO
				// Aggiungo il select per lo firma elettronica della crf
				$("#selectuser_NEWUSER_SIGN").addSelectStatusSignUserHiddenCopy();
				$("#selectuser_NEWUSER_SIGN").addEnableDisableStatusAndSignUser();
				$("#selectuser_NEWUSER_SIGN").val(0);
				$("#selectuser_NEWUSER_SIGN").trigger('change');	
				// Aggiungo il select per la firma elettronica del sae
				$("#selectuser_NEWUSER_SIGNSAE").addSelectStatusSignUserHiddenCopy();
				$("#selectuser_NEWUSER_SIGNSAE").addEnableDisableStatusAndSignUser();
				$("#selectuser_NEWUSER_SIGNSAE").val(0);
				$("#selectuser_NEWUSER_SIGNSAE").trigger('change');
				// Aggiungo il select per il change del ruolo
    			$("#selectuser_NEWUSER_ROLE").addChangeRoleUser();
				$("#selectuser_NEWUSER_ROLE").trigger('change');
				$("#userundolink_NEWUSER").undoChangesUser();
				$("#usereditlink_NEWUSER").trigger('click');
			}
			$("#selectuser_NEWUSER_ROLE").focus();
			$(mandatory_fields_user).each(function() {
				$("input[id$='NEWUSER_"+this+"']").addInputChange();
				$("input[id$='NEWUSER_"+this+"']").trigger('change');
			});
			$(number_only_fields_user).each(function() {
				$("input[id$='NEWUSER_"+this+"']").addCheckNumber();
				$("input[id$='NEWUSER_"+this+"']").trigger('change');
			});
			$(max_lenght_fields_user).each(function() {
				$("input[id$='NEWUSER_"+this+"']").addCheckSize();
				$("input[id$='NEWUSER_"+this+"']").trigger('change');
			});
			$(email_fields_user).each(function() {
				$("input[id$='NEWUSER_"+this+"']").addEmailInputChange();
				$("input[id$='NEWUSER_"+this+"']").trigger('change');
			});
		});
	};	

	
	// Ready functions
	$(document).ready(function () {
		// Bindo i change delle select
		$(select_to_be_triggered).each(function() {
			$("select[id^='select'][id$='"+this+"']").addSelectStatusSignUserHiddenCopy();
			//$("select[id^='select'][id$='"+this+"']").trigger('change');
		});
	
		// Nascondo gli edit box
		$("div[id^='editcenter_']").hide();

		// Nascondo i link undo
		$("[id^='centerundolink_']").hide();

		// Nascondo le tabelle degli users
		$("tr[id^='trcenter_'][id$='_users']").hide();

		// Abilito i campi
		$("input[id^='inputcenter_']").removeAttr("disabled");
		$("select[id^='selectcenter_'][id$='_STATUS']").removeAttr("disabled");

		// Disabilito la select del country
		$("select[id^='selectcenter_'][id$='_COUNTRY']").attr("disabled", true);
		$("select[id^='selectcenter_'][id$='_COUNTRY']").addSelectCountryHiddenCopy();

		// Aggiungo la funzione di visualizzazione
		$("[id^='centereditlink_']").addEditLinkCenter();
		
		// Aggiungo la funzione di edit dei languages
		$("[id^='centereditlanguagelink_']").unbind('click');
		$("[id^='centereditlanguagelink_']").bind('click', function() {
			$(this).addLanguageSelectionQTip();
		});
		
		// Aggiungo la funzione di abilitazione o meno dei centri
		$("select[id^='selectcenter_'][id$='_STATUS']").addEnableDisableCenter();

		// Aggiungo la funzione di visualizzazione degli utenti
		$("[id^='centerialink_']").addOpenUsersTableLink();

		$("tr[id^='trcenter_']").each(function() {
			$(this).removeClass("edit_user_select");
		});
		
		// Aggiungo la funzione per aggiungere i centri
		$("#link_addcenter").bind("click", function() {
		{if $isAdmin == TRUE or $isPM == TRUE}
			//controllo che nessun altro centro o user sia in edit
			editing=false;
			$("img[id^='img_centereditlink_'], img[id^='img_usereditlink_'] ").each(
				function(){
			  		if(!$(this).attr("id").match(/img_centereditlink_NEWCENTER/i)&&!editing&&$(this).attr("src").match(/{$icon_file.save|regex_replace:"/\//":"\/"|regex_replace:"/\./":"\."}/)){
			  			editing=true;
			  		} 
			  	}
			);
			if (!editing&&$("#viewcenter_NEWCENTER_CODE").length == 0 && $("#viewedituser_NEWUSER_ROLE").length == 0) {
	  			var new_tr = $("#tr_to_copy").html().replace(/IDCENTER/g, "NEWCENTER");
	  			var new_tr_users = $("#tr_to_copy_users").html().replace(/IDCENTER/g, "NEWCENTER");
				$('#centers > tbody:last').append('<tr id="trcenter_NEWCENTER">'+new_tr+'</tr>');
				$('#centers > tbody:last').append('<tr id="trcenter_NEWCENTER_users" style="display: none;">'+new_tr_users+'</tr>');
				$("#centereditlink_NEWCENTER").addEditLinkCenter();
				$("#centereditlanguagelink_NEWCENTER").unbind('click');
				$("#centereditlanguagelink_NEWCENTER").bind('click', function() {
					$(this).addLanguageSelectionQTip();
				});
				$("#selectcenter_NEWCENTER_COUNTRY").addSelectCountryHiddenCopy();
				$("#selectcenter_NEWCENTER_STATUS").addEnableDisableCenter();
				$("#centerundolink_NEWCENTER").undoChangesCenter();
				$("#centereditlink_NEWCENTER").trigger('click');
				// Aggiungo la funzione di visualizzazione degli utenti (centro abilitato)
				$("#centerialink_NEWCENTER_enabled").addOpenUsersTableLink();
				// Aggiungo la funzione di visualizzazione degli utenti (centro disabilitato)
				$("#centerialink_NEWCENTER_disabled").addOpenUsersTableLink();
				// Aggiungo la funzione per aggiungere gli utenti ai centri
				$("#link_adduser_center_NEWCENTER").addAddUserToCenter();
				$.scrollTo("100%", 800);
				$("#inputcenter_NEWCENTER_CODE").focus();
				$(mandatory_fields).each(function() {
					$("input[id$='NEWCENTER_"+this+"']").addInputChange();
					$("input[id$='NEWCENTER_"+this+"']").trigger('change');
				});
				$(number_only_fields).each(function() {
					$("input[id$='NEWCENTER_"+this+"']").addCheckNumber();
					$("input[id$='NEWCENTER_"+this+"']").trigger('change');
				});
				$(max_lenght_fields).each(function() {
					$("input[id$='NEWCENTER_"+this+"']").addCheckSize();
					$("input[id$='NEWCENTER_"+this+"']").trigger('change');
				});
				$(email_fields).each(function() {
					$("input[id$='NEWCENTER_"+this+"']").addEmailInputChange();
					$("input[id$='NEWCENTER_"+this+"']").trigger('change');
				});		
			}
		{else}
			return false;
		{/if}
		});	

		// Aggiungo il change per i valori non nulli dei center
		$(mandatory_fields).each(function() {
			$("input[id^='inputcenter_'][id$='"+this+"']").addInputChange();
		});
		$(number_only_fields).each(function() {
		  $("input[id^='inputcenter_'][id$='"+this+"']").addCheckNumber();
		});
		$(max_lenght_fields).each(function() {
		  $("input[id^='inputcenter_'][id$='"+this+"']").addCheckSize();
		});
		$(email_fields).each(function() {
			$("input[id^='inputcenter_'][id$='"+this+"']").addEmailInputChange();
		});
			
		// USERS
		// Nascondo gli edit box degli user
		$("div[id^='edituser_']").each(function() {
			$(this).hide();
		});

		// Disabilito la select del ruolo dell'utente
		$("select[id^='selectuser_'][id$='_ROLE']").attr("disabled", true);

		// Aggiungo la funzione di visualizzazione
		$("a[id^='usereditlink_']").addEditLinkUser();
		
		// Aggiungo la funzione di abilitazione o meno degli utenti
		$("select[id^='selectuser_'][id$='_STATUS']").addEnableDisableStatusAndSignUser();

		// Aggiungo la funzione di abilitazione o meno all'electronic signature della CRF o dell'ESAE da parte degli utenti
		$("select[id^='selectuser_'][id*='_SIGN']").addEnableDisableStatusAndSignUser();
		
		// Nascondo i link undo per gli utenti
		$("a[id^='userundolink_']").each(function() {
			$(this).hide();
		});
		
		// Aggiungo la funzione per aggiungere gli utenti ai centri
		$("a[id^='link_adduser_']").addAddUserToCenter();

		// Aggiungo il link al popup con le informazioni dell'utente
		$("a[id^='userinfolink_']").addUserInfo();
		
		// Aggiungo il change per i valori non nulli degli user
		$(mandatory_fields_user).each(function() {
			$("input[id^='inputuser_'][id$='"+this+"']").addInputChange();
		});
		$(max_lenght_fields_user).each(function() {
		  $("input[id^='inputuser_'][id$='"+this+"']").addCheckSize();
		});
		$(number_only_fields_user).each(function() {
		  $("input[id^='inputuser_'][id$='"+this+"']").addCheckNumber();
		});
		$(email_fields_user).each(function() {
			$("input[id^='inputuser_'][id$='"+this+"']").addEmailInputChange();
		});
		
		// Aggiungo la width per tutti gli input
		$("input[id^='input']").css("width", "100%");
		// Aggiungo la funzione per mostrare o meno gli utenti globali nel caso di admin
	    $("#link_showhide_global_user").bind("click", function() {
	      if ($("#trglobal_users").is(":visible")) {
			    // Faccio l'undo dell'eventuale inserimento di un nuovo utente globale
		    	$("#trglobal_users img[id^='img_userundolink_']:visible").trigger('click');
		    	$(this).closest("tr").children("td:first").attr("colspan", 11);
		    	$(this).closest("tr").children("td:last").hide();
	            $("#trglobal_users").hide();
	            $(this).html($(this).html().replace(/-/, "+"));
            } else {
		    	$(this).closest("tr").children("td:first").attr("colspan", 10);
		    	$(this).closest("tr").children("td:last").show();
                $("#trglobal_users").show();
	            $(this).html($(this).html().replace(/\+/, "-"));
            }
        });
    
        // Aggiungo il trigger per il cambio di tipologia che influenza il centro (nel caso utenti globali
    	$("select[id^='selectuser_'][id$='_ROLE']").addChangeRoleUser();
    	$("select[id^='selectuser_'][id$='_ROLE']").trigger('change');

	});	
</script>
</head>

<body>
<center>
  <form id="cmm_managment" name="form1" method="post">
  <div id="tooltip_new_user" style="display: none;"><span style="font-family: Arial; font-size: 8pt;">username: <span style="font-weight: bolder;">#username#</span><br/>password: <span style="font-weight: bolder;">#password#</span></span></div>
    <table id="centers" border="1" cellpadding="2" cellspacing="0" bordercolor="#000000">
      <tbody>
      {if $isAdmin == TRUE or $isPM == TRUE}
        <tr> 
          <td colspan="11" align="center" style="vertical-align: middle;"><a id="link_showhide_global_user" href="javascript:void(0);"><strong>Global users [+]</strong></a></td>
          <td colspan="3" width="80" align="center" style="vertical-align: middle; display: none;"><a id="link_adduser_global" href="javascript:void(0);"><strong>Add User&nbsp;<img id="img_adduser_global" src="{$icon_file.new}" width="18" height="18" border="0" /></strong></a></td>
        </tr>
		<tr id="trglobal_users" style="display: none;">
			<td colspan="13">
			<table id="global_users" border="1" cellpadding="2" cellspacing="0" bordercolor="#000000" width="100%">
		      <tbody>
		        <tr class="header2"> 
		          <td>ROLE</td>
		          <td class="small2">USERID</td>
		          <td>NAME</td>
		          <td>SURNAME</td>
		          <td>EMAIL</td>
		          <td>PHONE</td>
		          <td>FAX</td>
		          <td>ADDRESS</td>
		          <td class="small2">CREATION DATE</td>
		          <td class="small2">EXPIRE DATE</td>
		          <td class="small2">FIRST ACCESS DATE</td>
		          <td class="small2">LAST ACCESS DATE</td>
		          <td class="small2">END DATE</td>
		          <td class="small_edit">STATUS</td>
		          <td class="edit_user">EDIT ACCOUNT</td>
		        </tr>
	        	{foreach $global_users as $userval}
				<tr id="trglobal_user_{if $userval.CMM_USERID == "CMM_USERID"}to_copy{else}{$userval.CMM_USERID}{/if}"{if $userval.CMM_USERID == "CMM_USERID"} style="display: none;"{elseif $userval.STATUS != "1"} class="user_disabled"{/if}>
					<td class="small">
						<div id="viewedituser_{$userval.CMM_USERID}_ROLE">
							<select id="selectuser_{$userval.CMM_USERID}_ROLE" name="selectuser_{$userval.CMM_USERID}_ROLE">
							{foreach $user_roles as $role_element}
								{if $role_element@key<10}
								<option value="{$role_element@key}"{if $userval.ROLE == $role_element@key} selected="selected"{/if}{if $role_element@key>10} disabled="disabled"{/if}>{$role_element}</option>
								{/if}
							{/foreach}
							</select>
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_ROLE" name="inputhiddenuser_{$userval.CMM_USERID}_D_ROLE" value="{$userval.ROLE}" />
							<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_ROLE" name="prev_selectuser_{$userval.CMM_USERID}_ROLE" value="" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_ID_CENTER" name="inputhiddenuser_{$userval.CMM_USERID}_ID_CENTER" value="" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_CODE" name="inputhiddenuser_{$userval.CMM_USERID}_CODE" value="" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_CMM_USERID" name="inputhiddenuser_{$userval.CMM_USERID}_CMM_USERID" value="{$userval.CMM_USERID}" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_ACTION" name="inputhiddenuser_{$userval.CMM_USERID}_ACTION" value="{if $userval.CMM_USERID == "CMM_USERID"}insert{else}update{/if}_user" />
						</div>
					</td>
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_CMM_USERID">{if $userval.CMM_USERID == "CMM_USERID"}******{else}{$userval.CMM_USERID}{/if}</div>
						<div id="edituser_{$userval.CMM_USERID}_CMM_USERID">{if $userval.CMM_USERID == "CMM_USERID"}******{else}{$userval.CMM_USERID}{/if}</div>
					</td>
	        		{foreach $user_textbox_editable_field as $textbox_editable_field}
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_{$textbox_editable_field}">{$userval.$textbox_editable_field}</div>
						<div id="edituser_{$userval.CMM_USERID}_{$textbox_editable_field}">
			          		<input id="inputuser_{$userval.CMM_USERID}_{$textbox_editable_field}" name="inputuser_{$userval.CMM_USERID}_{$textbox_editable_field}" type="textbox" value="{$userval.$textbox_editable_field}">
						</div>
					</td>
					{/foreach}
	        		{foreach $user_textbox_not_editable_field as $textbox_not_editable_field}
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_{$textbox_not_editable_field}">{$userval.$textbox_not_editable_field}</div>
						<div id="edituser_{$userval.CMM_USERID}_{$textbox_not_editable_field}">{$userval.$textbox_not_editable_field}</div>
					</td>
					{/foreach}
					<td class="small">
			        	<div id="viewuserstatus_{$userval.CMM_USERID}_STATUS">
			          		<select id="selectuser_{$userval.CMM_USERID}_STATUS" name="selectuser_{$userval.CMM_USERID}_STATUS"{if $userval.STATUS != "1" && $userval.CMM_USERID != "CMM_USERID"} disabled="disabled"{/if}>
			          			<option value="1" class="option_enabled" {if $userval.STATUS == "1"} selected="selected"{/if}>Enabled</option>
			          			<option value="0" class="option_disabled" {if $userval.STATUS == "0"} selected="selected"{/if}>Disabled</option>
			          		</select>
			          		<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_STATUS" name="prev_selectuser_{$userval.CMM_USERID}_STATUS" value="{$userval.STATUS}" />
			          		<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_STATUS" name="inputhiddenuser_{$userval.CMM_USERID}_D_STATUS" value="{$userval.D_STATUS}" />
						</div>
					</td>
			        <td class="small" align="center" width="40">
						<div id="divusereditlink_{$userval.CMM_USERID}">
							<a id="usereditlink_{$userval.CMM_USERID}" href="javascript:void(0);">
								<img id="img_usereditlink_{$userval.CMM_USERID}" src="{if $userval.STATUS != "1" && $userval.CMM_USERID != "CMM_USERID"}{$icon_file.edit_forbidden}{else}{$icon_file.edit}{/if}" width="18" height="18" border="0" />
							</a>
							<a id="userundolink_{$userval.CMM_USERID}" href="javascript:void(0);" style="display: none;">
								<img id="img_userundolink_{$userval.CMM_USERID}" src="{$icon_file.undo}" width="18" height="18" border="0" />
							</a>
							<a id="userinfolink_{$userval.CMM_USERID}" href="javascript:void(0);" {if $userval.FIRST_PASSWORD == ""} style="display: none;"{/if}>
								<img id="img_userinfolink_{$userval.CMM_USERID}" src="{$icon_file.info}" width="18" height="18" border="0" />
							</a>
							<img id="img_usersentmail_{$userval.CMM_USERID}" src="{$icon_file.sent_mail}" width="18" height="18" border="0" style="{if $userval.MAIL_SENT != "Y"}display: none;{/if}"/>
						</div>
					</td>
				</tr>
				{/foreach}
			</tbody>
			</table></td>
		</tr>
      	{/if}
        <tr> 
          <td colspan="8" align="center" style="vertical-align: middle;"><strong>Centres</strong></td>
          <td colspan="3" align="center" style="vertical-align: middle;"><a id="link_addcenter" href="javascript:void(0);" ><strong>Add Center&nbsp;<img id="img_addcenter" src="{$icon_file.new}" width="18" height="18" border="0" /></strong></a></td>
        </tr>
        <tr class="header2"> 
          <td class="small2">SITEID</td>
          <td>NAME (CENTER)</td>
          <td>P.I. (NAME/SURNAME)</td>
          <td>ADDRESS (CENTER)</td>
          <td>PHONE (CENTER)</td>
          <td>FAX (CENTER)</td>
          <td>COUNTRY (CENTER)</td>
          <td align="center">STATUS (CENTER)</td>
          <td class="edit_center">EDIT CENTER</td>
          <td class="edit_center">EDIT LANGUAGE</td>
          <td class="edit_center">INVESTIGATOR ACCOUNTS</td>
        </tr>
		{foreach $db_centers as $db_center}
		<tr id="{if $db_center.ID_CENTER == "IDCENTER"}tr_to_copy{else}trcenter_{$db_center.ID_CENTER}{/if}"{if $db_center.ID_CENTER == "IDCENTER"} style="display: none;"{elseif $db_center.STATUS != "1"} class="center_disabled"{/if}> 
          <td class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_CODE">{$db_center.CODE}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_CODE" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_CODE" name="inputcenter_{$db_center.ID_CENTER}_CODE" type="textbox" value="{$db_center.CODE}" />
				<input type="hidden" id="inputhiddencenter_{$db_center.ID_CENTER}_ID_CENTER" name="inputhiddencenter_{$db_center.ID_CENTER}_ID_CENTER" value="{$db_center.ID_CENTER}" />
				<input type="hidden" id="inputhiddencenter_{$db_center.ID_CENTER}_ACTION" name="inputhiddencenter_{$db_center.ID_CENTER}_ACTION" value="{if $db_center.ID_CENTER == "IDCENTER"}insert{else}update{/if}_center" />
          	</div>
          </td>
          <td class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_NAME">{$db_center.NAME}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_NAME" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_NAME" name="inputcenter_{$db_center.ID_CENTER}_NAME" type="textbox" value="{$db_center.NAME}" />
          	</div>
          </td>
          <td class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_PI">{$db_center.PI}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_PI" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_PI" name="inputcenter_{$db_center.ID_CENTER}_PI" type="textbox" value="{$db_center.PI}" />
          	</div>
          </td>
          <td  class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_ADDRESS">{$db_center.ADDRESS}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_ADDRESS" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_ADDRESS" name="inputcenter_{$db_center.ID_CENTER}_ADDRESS" type="textbox" value="{$db_center.ADDRESS}" />
          	</div>
          </td>
          <td  class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_PHONE">{$db_center.PHONE}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_PHONE" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_PHONE" name="inputcenter_{$db_center.ID_CENTER}_PHONE" type="textbox" value="{$db_center.PHONE}" />
          	</div>
          </td>
          <td  class="small">
          	<div id="viewcenter_{$db_center.ID_CENTER}_FAX">{$db_center.FAX}</div>
          	<div id="editcenter_{$db_center.ID_CENTER}_FAX" style="display: none;">
          		<input id="inputcenter_{$db_center.ID_CENTER}_FAX" name="inputcenter_{$db_center.ID_CENTER}_FAX" type="textbox" value="{$db_center.FAX}" />
          	</div>
          </td>
          <td class="small">
          	<div id="viewcountry_{$db_center.ID_CENTER}_COUNTRY">
          		<select id="selectcenter_{$db_center.ID_CENTER}_COUNTRY" name="selectcenter_{$db_center.ID_CENTER}_COUNTRY" disabled="disabled">
          		<option value=""></option>
          		{foreach $iso_country_list as $country_element}
				<option value="{$country_element@key}"{if $db_center.COUNTRY == $country_element@key} selected="selected"{/if}>{$country_element}</option>
          		{/foreach}
          		</select>
          		<input type="hidden" id="prev_selectcenter_{$db_center.ID_CENTER}_COUNTRY" name="prev_selectcenter_{$db_center.ID_CENTER}_COUNTRY" value="{$db_center.COUNTRY}" />
          		<input type="hidden" id="inputhiddencenter_{$db_center.ID_CENTER}_D_COUNTRY" name="inputhiddencenter_{$db_center.ID_CENTER}_D_COUNTRY" value="{$db_center.D_COUNTRY}" />
          	 </div>
		  </td>
          <td class="small">
          	<div id="viewcenterstatus_{$db_center.ID_CENTER}_STATUS">
          		<select id="selectcenter_{$db_center.ID_CENTER}_STATUS" name="selectcenter_{$db_center.ID_CENTER}_STATUS">
          			<option value="1" class="option_enabled" {if $db_center.STATUS == "1"} selected="selected"{/if}>Enabled</option>
          			<option value="0" class="option_disabled" {if $db_center.STATUS == "0"} selected="selected"{/if}>Disabled</option>
          		</select>
          		<input type="hidden" id="prev_selectcenter_{$db_center.ID_CENTER}_STATUS" name="prev_selectcenter_{$db_center.ID_CENTER}_STATUS" value="{$db_center.STATUS}" />
          		<input type="hidden" id="inputhiddencenter_{$db_center.ID_CENTER}_D_STATUS" name="inputhiddencenter_{$db_center.ID_CENTER}_D_STATUS" value="{$db_center.D_STATUS}" />
          	 </div>
		   </td>
	        <td class="small edit_center">
	        	<div id="divcentereditlink_{$db_center.ID_CENTER}_enabled"{if $db_center.STATUS != "1" && $db_center.ID_CENTER != "IDCENTER"} style="display: none;"{/if}>
	        		<a id="centereditlink_{$db_center.ID_CENTER}" href="javascript:void(0);">
	        			<img id="img_centereditlink_{$db_center.ID_CENTER}" src="{$icon_file.edit}" width="18" height="18" border="0" />
	        		</a>
					<a id="centerundolink_{$db_center.ID_CENTER}" href="javascript:void(0);" style="display: none;">
						<img id="img_centerundolink_{$db_center.ID_CENTER}" src="{$icon_file.undo}" width="18" height="18" border="0" />
					</a>
	        	</div>
	        	<div id="divcentereditlink_{$db_center.ID_CENTER}_disabled"{if $db_center.STATUS != "0"} style="display: none;"{/if}>
	        		&nbsp;
	        	</div>
			</td>
	        <td class="small edit_center">
	        	<div id="divcentereditlanguagelink_{$db_center.ID_CENTER}_enabled"{if $db_center.STATUS != "1" && $db_center.ID_CENTER != "IDCENTER"} style="display: none;"{/if}>
	        		<a id="centereditlanguagelink_{$db_center.ID_CENTER}" href="javascript:void(0);">
	        			<img id="img_centereditlanguagelink_{$db_center.ID_CENTER}" src="{$icon_file.edit_languages}" width="18" height="18" border="0" />
	        		</a>
	        	</div>
	        	<div id="divcentereditlanguagelink_{$db_center.ID_CENTER}_disabled"{if $db_center.STATUS != "0"} style="display: none;"{/if}>
	        		&nbsp;
	        	</div>
			</td>
	        <td class="small edit_center" align="center">
	        	<div id="divcenterialink_{$db_center.ID_CENTER}_enabled"{if $db_center.STATUS != "1" && $db_center.ID_CENTER != "IDCENTER"} style="display: none;"{/if}>
		        	<a id="centerialink_{$db_center.ID_CENTER}_enabled" href="javascript:void(0);">
	        			<img id="img_centerialink_{$db_center.ID_CENTER}" src="{$icon_file.edit}" width="18" height="18" border="0" />
        			</a>
	        	</div>
	        	<div id="divcenterialink_{$db_center.ID_CENTER}_disabled"{if $db_center.STATUS != "0"} style="display: none;"{/if}>
		        	<a id="centerialink_{$db_center.ID_CENTER}_disabled" href="javascript:void(0);">
	        			<img id="img_centerialink_{$db_center.ID_CENTER}" src="{$icon_file.explore}" width="18" height="18" border="0" />
	        		</a>
	        	</div>
			 </td>
			</tr>
			<tr id="{if $db_center.ID_CENTER == "IDCENTER"}tr_to_copy_users{else}trcenter_{$db_center.ID_CENTER}_users{/if}" style="display: none;">
			<td colspan="12">
			<table id="center_{$db_center.ID_CENTER}_users" border="1" cellpadding="2" cellspacing="0" bordercolor="#000000" width="100%">
		      <tbody>
				<tr>
		      	  <td colspan="16" align="center" style="vertical-align: middle;"><strong>{$db_center.CODE} Users</strong></td>
		          <td width="80" align="center" style="vertical-align: middle;"><a id="link_adduser_center_{$db_center.ID_CENTER}" href="javascript:void(0);" ><strong>Add User&nbsp;<img id="img_adduser_center_{$db_center.ID_CENTER}" src="{$icon_file.new}" width="18" height="18" border="0" /></strong></a></td>
		        </tr>
		        <tr class="header2"> 
		          <td>ROLE</td>
		          <td class="small2">USERID</td>
		          <td>NAME</td>
		          <td>SURNAME</td>
		          <td>EMAIL</td>
		          <td>PHONE</td>
		          <td>FAX</td>
		          <td>ADDRESS</td>
		          <td class="small2">CREATION DATE</td>
		          <td class="small2">EXPIRE DATE</td>
		          <td class="small2">FIRST ACCESS DATE</td>
		          <td class="small2">LAST ACCESS DATE</td>
		          <td class="small2">END DATE</td>
		          <td class="small_edit">STATUS</td>
		          <td class="small_edit">SIGN eCRF</td>
		          <td class="small_edit">SIGN eSAE</td>
		          <td class="edit_user">EDIT ACCOUNT</td>
		        </tr>
	        	{foreach $db_center.USERS as $userval}
				<tr id="trcenter_{$db_center.ID_CENTER}_user_{if $userval.CMM_USERID == "CMM_USERID"}to_copy{else}{$userval.CMM_USERID}{/if}"{if $userval.CMM_USERID == "CMM_USERID"} style="display: none;"{elseif $userval.STATUS != "1"} class="user_disabled"{/if}>
					<td class="small">
						<div id="viewedituser_{$userval.CMM_USERID}_ROLE">
							<select id="selectuser_{$userval.CMM_USERID}_ROLE" name="selectuser_{$userval.CMM_USERID}_ROLE">
							{foreach $user_roles as $role_element}
							{if $role_element@key>10}
								<option value="{$role_element@key}"{if $userval.ROLE == $role_element@key} selected="selected"{/if}{if $role_element@key<10} disabled="disabled"{/if}>{$role_element}</option>
							{/if}
							{/foreach}
							</select>
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_ROLE" name="inputhiddenuser_{$userval.CMM_USERID}_D_ROLE" value="{$userval.ROLE}" />
							<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_ROLE" name="prev_selectuser_{$userval.CMM_USERID}_ROLE" value="" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_ID_CENTER" name="inputhiddenuser_{$userval.CMM_USERID}_ID_CENTER" value="{$db_center.ID_CENTER}" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_CODE" name="inputhiddenuser_{$userval.CMM_USERID}_CODE" value="{$db_center.CODE}" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_CMM_USERID" name="inputhiddenuser_{$userval.CMM_USERID}_CMM_USERID" value="{$userval.CMM_USERID}" />
							<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_ACTION" name="inputhiddenuser_{$userval.CMM_USERID}_ACTION" value="{if $userval.CMM_USERID == "CMM_USERID"}insert{else}update{/if}_user" />
						</div>
					</td>
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_CMM_USERID">{if $userval.CMM_USERID == "CMM_USERID"}******{else}{$userval.CMM_USERID}{/if}</div>
						<div id="edituser_{$userval.CMM_USERID}_CMM_USERID" style="display: none;">{if $userval.CMM_USERID == "CMM_USERID"}******{else}{$userval.CMM_USERID}{/if}</div>
					</td>
	        		{foreach $user_textbox_editable_field as $textbox_editable_field}
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_{$textbox_editable_field}">{$userval.$textbox_editable_field}</div>
						<div id="edituser_{$userval.CMM_USERID}_{$textbox_editable_field}" style="display: none;">
			          		<input id="inputuser_{$userval.CMM_USERID}_{$textbox_editable_field}" name="inputuser_{$userval.CMM_USERID}_{$textbox_editable_field}" type="textbox" value="{$userval.$textbox_editable_field}">
						</div>
					</td>
					{/foreach}
	        		{foreach $user_textbox_not_editable_field as $textbox_not_editable_field}
					<td class="small">
						<div id="viewuser_{$userval.CMM_USERID}_{$textbox_not_editable_field}">{$userval.$textbox_not_editable_field}</div>
						<div id="edituser_{$userval.CMM_USERID}_{$textbox_not_editable_field}" style="display: none;">{$userval.$textbox_not_editable_field}</div>
					</td>
					{/foreach}
					<td class="small">
			        	<div id="viewuserstatus_{$userval.CMM_USERID}_STATUS">
			          		<select id="selectuser_{$userval.CMM_USERID}_STATUS" name="selectuser_{$userval.CMM_USERID}_STATUS"{if ($db_center.STATUS != "1" || $userval.STATUS != "1") && $userval.CMM_USERID != "CMM_USERID"} disabled="disabled"{/if}>
			          			<option value="1" class="option_enabled"{if $userval.STATUS == "1"} selected="selected"{/if}>Enabled</option>
			          			<option value="0" class="option_disabled"{if $userval.STATUS == "0"} selected="selected"{/if}>Disabled</option>
			          		</select>
			          		<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_STATUS" name="prev_selectuser_{$userval.CMM_USERID}_STATUS" value="{$userval.STATUS}" />
			          		<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_STATUS" name="inputhiddenuser_{$userval.CMM_USERID}_D_STATUS" value="{$userval.D_STATUS}" />
						</div>
					</td>
					<td class="small">
			        	<div id="viewusersign_{$userval.CMM_USERID}_SIGN">
			          		<select id="selectuser_{$userval.CMM_USERID}_SIGN" name="selectuser_{$userval.CMM_USERID}_SIGN"{if ($db_center.STATUS != "1" || $userval.STATUS != "1" || $userval.ROLE != "12") && $userval.CMM_USERID != "CMM_USERID"} disabled="disabled"{/if}>
			          			<option value="1" class="option_enabled"{if $userval.SIGN == "1"} selected="selected"{/if}>Enabled</option>
			          			<option value="0" class="option_disabled"{if $userval.SIGN == "0"} selected="selected"{/if}>Disabled</option>
			          		</select>
			          		<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_SIGN" name="prev_selectuser_{$userval.CMM_USERID}_SIGN" value="{$userval.SIGN}" />
			          		<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_SIGN" name="inputhiddenuser_{$userval.CMM_USERID}_D_SIGN" value="{$userval.D_SIGN}" />
						</div>
					</td>
					<td class="small">
			        	<div id="viewusersign_{$userval.CMM_USERID}_SIGNSAE">
			          		<select id="selectuser_{$userval.CMM_USERID}_SIGNSAE" name="selectuser_{$userval.CMM_USERID}_SIGNSAE"{if ($db_center.STATUS != "1" || $userval.STATUS != "1" || $userval.ROLE != "11" || $userval.ROLE != "12") && $userval.CMM_USERID != "CMM_USERID"} disabled="disabled"{/if}>
			          			<option value="1" class="option_enabled"{if $userval.SIGNSAE == "1"} selected="selected"{/if}>Enabled</option>
			          			<option value="0" class="option_disabled"{if $userval.SIGNSAE == "0"} selected="selected"{/if}>Disabled</option>
			          		</select>
			          		<input type="hidden" id="prev_selectuser_{$userval.CMM_USERID}_SIGNSAE" name="prev_selectuser_{$userval.CMM_USERID}_SIGNSAE" value="{$userval.SIGNSAE}" />
			          		<input type="hidden" id="inputhiddenuser_{$userval.CMM_USERID}_D_SIGNSAE" name="inputhiddenuser_{$userval.CMM_USERID}_D_SIGNSAE" value="{$userval.D_SIGNSAE}" />
						</div>
					</td>
			        <td class="small edit_center">
						<div id="divusereditlink_{$userval.CMM_USERID}">
							<a id="usereditlink_{$userval.CMM_USERID}" href="javascript:void(0);">
								<img id="img_usereditlink_{$userval.CMM_USERID}" src="{if (($db_center.STATUS != "1" || $userval.STATUS != "1") && $userval.CMM_USERID != "CMM_USERID")}{$icon_file.edit_forbidden}{else}{$icon_file.edit}{/if}" width="18" height="18" border="0" />
							</a>
							<a id="userundolink_{$userval.CMM_USERID}" href="javascript:void(0);" style="display: none;">
								<img id="img_userundolink_{$userval.CMM_USERID}" src="{$icon_file.undo}" width="18" height="18" border="0" />
							</a>
							<a id="userinfolink_{$userval.CMM_USERID}" href="javascript:void(0);" {if $userval.FIRST_PASSWORD == ""} style="display: none;"{/if}>
								<img id="img_userinfolink_{$userval.CMM_USERID}" src="{$icon_file.info}" width="18" height="18" border="0" />
							</a>
							<img id="img_usersentmail_{$userval.CMM_USERID}" src="{$icon_file.sent_mail}" width="18" height="18" border="0" style="{if $userval.MAIL_SENT != "Y"}display: none;{/if}"/>
						</div>
					</td>
				</tr>
				{/foreach}
			</tbody>
			</table></td></tr>
		{/foreach}		
      </tbody>
    </table>
  </form>
	        	<div id="divlanguages_GENERICCENTER" style="display: none;">
	        	<input type="hidden" id="inputhiddencenter_GENERICCENTER_ACTION" name="inputhiddencenter_GENERICCENTER_ACTION" value="update_language_center" />
	        	<input type="hidden" id="inputhiddencenter_GENERICCENTER_ID_CENTER" name="inputhiddencenter_GENERICCENTER_ID_CENTER" value="" />
	        	<div style="text-align: center; border-bottom: 1px dotted; margin-bottom: 3px;">Languages:</div>
			        <label class="language_selector" style="display: none;"><input type="checkbox" class="language_selector"
			        	id="checkboxlang_GENERICLANGUAGE_center_GENERICCENTER"
		        		name="checkboxlang_GENERICLANGUAGE_center_GENERICCENTER"/>GENERICD_LANGUAGE
					</label>
		        	<div style="text-align: center; border-top: 1px dotted; margin-top: 3px; padding-top: 3px;">
		        		<input id="submitlang_GENERICCENTER" type="submit" value="Update" />
					</div>
	        	</div>
	        	<div id="divuserinfo" style="display: none;">
					<div style="text-align: center; border-bottom: 1px dotted; margin-bottom: 20px; padding-bottom: 3px; font-weight: bold; font-size: large;">
						User Info
					</div>
		        	<div id="divuserinfotable" style="display: table;">
		        		<div id="divurltext" style="text-align: left; width: 120px; display: table-cell;">url:</div>
	        			<div id="divurl" style="text-align: left; display: table-cell; font-weight: bold;">#URL#</div>
	        		</div>
		        	<div id="divusernametable" style="display: table;">
		        		<div id="divusernametext" style="text-align: left; width: 120px; display: table-cell;">Username:</div>
	        			<div id="divusername" style="text-align: left; display: table-cell; font-weight: bold;">#USERNAME#</div>
	        		</div>
		        	<div id="divpasswordtable" style="display: table;">
		        		<div id="divpasswordtext" style="text-align: left; width: 120px; display: table-cell;">First password:</div>
	        			<div id="divpassword" style="text-align: left; display: table-cell; font-weight: bold;">#PASSWORD#</div>
	        		</div>
		        	<div id="diveroletable" style="display: table;">
		        		<div id="diveroletext" style="text-align: left; width: 120px; display: table-cell;">Role:</div>
	        			<div id="divrole" style="text-align: left; display: table-cell; font-weight: bold;">#ROLE#</div>
	        		</div>
		        	<div id="divecreationdatetable" style="display: table;">
		        		<div id="divecreationdatetext" style="text-align: left; width: 120px; display: table-cell;">Creation date:</div>
	        			<div id="divcreationdate" style="text-align: left; display: table-cell; font-weight: bold;">#CREATION_DATE#</div>
	        		</div>
		        	<div id="divfirstnametable" style="display: table;">
		        		<div id="divfirstnametext" style="text-align: left; width: 120px; display: table-cell;">Name:</div>
	        			<div id="divfirstname" style="text-align: left; display: table-cell; font-weight: bold;">#FIRSTNAME#</div>
	        		</div>
		        	<div id="divlastnametable" style="display: table;">
		        		<div id="divlastnametext" style="text-align: left; width: 120px; display: table-cell;">Surname:</div>
	        			<div id="divlastname" style="text-align: left; display: table-cell; font-weight: bold;">#LASTNAME#</div>
	        		</div>
		        	<div id="divemailtable" style="display: table;">
		        		<div id="divemailtext" style="text-align: left; width: 120px; display: table-cell;">email:</div>
	        			<div id="divemail" style="text-align: left; display: table-cell; font-weight: bold;">#EMAIL#</div>
	        			<div id="divemailtable">&nbsp;&nbsp;<a id="sendmail_info" href="mailto:">send user info</a>&nbsp;&nbsp;<a id="sendmail_pwd" href="mailto:">send user password</a>&nbsp;&nbsp;<a id="aemailtable_#USERNAME#" href="javascript:void(0);"><img src="{$icon_file.sent_mail}" alt="email sent"></a>
	        			&nbsp;&nbsp;<img id="img_senduserinfolink_spinning" src="{$icon_file.loading}" width="18" height="18" border="0" style="display: none;"/></div>
	        			
	        		</div>
					<div style="text-align: center; border-top: 1px dotted; margin-top: 20px; padding-top: 3px;">
						<input id="printuserinfo" type="button" value="Print Info" onclick="javascript:window.print();"/>
					</div>
				</div>
  <p> 
  </p>  
</center>
    <div style="bottom: 40px;" ><span style="text-align: left;font-weight: bold;font-family: arial;font-size: 11px;color:darkRed; background-color:white;border:1px solid black;padding:5px">version 1.0</span></div>
</body>
</html>
