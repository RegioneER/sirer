$('#pdta-cmp tr[data-fold-l2-id]').hide();
$('#pdta-cmp tr[data-fold-l1-id]').hide();

$('#pdta-cmp tr[data-fold-target-l1]').click(function(){
    trElement=$(this);
    foldId=trElement.attr("data-fold-target-l1");
    folded=trElement.attr("data-fold-l1-folded");
    console.log(folded);
    if (folded=="false") {
        $('#pdta-cmp tr[data-fold-l1-id="'+foldId+'"]').hide();
        trElement.attr("data-fold-l1-folded","true");
        trElement.find('.expand_collapse').html("[+]");
    }else {
        $('#pdta-cmp tr[data-fold-l1-id="'+foldId+'"]').not('#pdta-cmp tr[data-fold-l2-id]').show();
        trElement.attr("data-fold-l1-folded","false");
        trElement.find('.expand_collapse').html("[-]");
    }
});


$('#pdta-cmp tr[data-fold-target-l2]').click(function(){
    trElement=$(this);
    foldId=trElement.attr("data-fold-target-l2");
    folded=trElement.attr("data-fold-l2-folded");
    console.log(folded);
    if (folded=="false") {
        $('#pdta-cmp tr[data-fold-l2-id="'+foldId+'"]').hide();
        trElement.attr("data-fold-l2-folded","true");
        trElement.find('.expand_collapse').html("[+]")
    }else {
        $('#pdta-cmp tr[data-fold-l2-id="'+foldId+'"]').show();
        trElement.attr("data-fold-l2-folded","false");
        trElement.find('.expand_collapse').html("[-]");
    }
});
var shown={};
shown['veneto']=true;
shown['er']=true;
shown['toscana']=true;
shown['lazio']=true;
shown['sicilia']=true;

$('#tbl-check td').click(function(){
    elIn=$(this).find('input');
    tg=elIn.attr('data-reg-target');
    if (shown[tg]){
        $('[data-reg="'+tg+'"]').hide();
        elIn.prop("checked",false);
        shown[tg]=false;
    }else{
        $('[data-reg="'+tg+'"]').show();
        elIn.prop("checked",true);
        shown[tg]=true;
    }
});

$('[data-bootbox]').click(function(){
    id=$(this).attr('data-bootbox');
    contentDiv=$('#'+id);
    bootbox.alert(contentDiv.html());
    return false;
});

$('th .scroll-compare').parent().each(function(){
    console.log($(this));
    console.log($(this).width());
    $(this).find('.scroll-compare').css('width',$(this).width()+'px');
    $(this).find('.scroll-compare').css('text-align','center');
});



(function ($) {
   
    
    $('[data-toggle="tooltip"]').tooltip({placement: 'right'});   
})(jQuery);

$(document).scroll(function(){

    var distance=$(window).scrollTop()-$('#pdta-cmp').offset().top;
    console.log(distance);
    if (distance>0){
        //$('.scroll-compare').show();
        $('.scroll-compare').css('opacity',1);

    }else{
        //$('.scroll-compare').hide();
        $('.scroll-compare').css('opacity',0);
    }
    
    
});