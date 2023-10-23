$(document).ready(function() {
	$('.msghover').mouseenter(function() {
		$(this).css('background-color', '#FFFFD7');
	}).mouseleave(function() {
		$(this).css('background-color', '#FFFFFF');
	});
});

function inbox_nuovomessaggio() {
	$('#inbox-tabs').find('.active').removeClass('active');
	$('.cl_message').remove();
	$('.li-new-mail').toggleClass('active');
	$.get("index.php", {
		inbox : 'yes',
		ajax : "yes",
		operazione : "new_mail"
	}).done(function(data) {
		$('.message-footer').html('');
		$('#messaggi').html(data);
		setTimeout("inbox_chosen();", 200);
		setTimeout("applyEditor();", 1000);
	});
}

function inbox_chosen() {
	$("#form-field-recipient").chosen();
	$("#form-field-recipient").addClass('tag-input-style');
	$(".chosen-choices").css('min-height', '35px');
	$('.chosen-choices').find('li').find('input').css('color', '#BDBDBD').css('min-height', '30px');
}

function inbox_send() {

	var destinatari = inbox_getSelezionati();
	var oggetto = $('#form-field-subject').val();
	var messaggio = $('#bootbox_editor_content').html();
	$.get("index.php", {
		inbox : 'yes',
		ajax : "yes",
		operazione : "send_mail",
		destinatari : destinatari,
		oggetto : oggetto,
		messaggio : messaggio
	}).done(function(data) {
		if (data.substr(0, 4) == 'ERR:') {
			alert(data.substr(4, data.length));
		} else {
			$('.cl_message').remove();
			$('#inbox-tabs').find('.active').removeClass('active');
			$('.cl_bacheca').toggleClass('active');
			$('#messaggi').html(data);

		}
	});
}

function inbox_getSelezionati() {
	var selezionati = "";
	$("[name='to'] :selected").each(function(i, data) {
		selezionati += (i != 0 ? ";" : "") + $(data).val().charAt(0) + ":" + $(data).val().substring(1, $(data).val().length);
	});
	return selezionati;
}

function inbox_pannello(pannello) {
	if (pannello != 'message') {
		$.get("index.php", {
			inbox : 'yes',
			ajax : "yes",
			operazione : "pannello_" + pannello
		}).done(function(data) {
			$('.cl_message').remove();

			$('#inbox-tabs').find('.active').removeClass('active');
			$('.cl_' + pannello).toggleClass('active');
			$('#messaggi').html(data);
		});
	}
}
