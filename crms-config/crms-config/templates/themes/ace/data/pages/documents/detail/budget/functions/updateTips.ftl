
function updateTips(t) {
	var tips=$('.validateTips');
	tips.text(t).addClass("ui-state-highlight").show();
	tips.parent().animate({
        scrollTop : 10
    }, 500);
	setTimeout(function() {
		tips.removeClass("ui-state-highlight", 1500);
	}, 500);
}
		