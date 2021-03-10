
function prepareMetadataForPost(inMetadata){

	var metadata=$.extend(true,{},inMetadata);
	var quickMetadata={};
	$.each(metadata,function(key,value){
		if(!$.isArray(value)){
			var tmp=value;
			value=new Array();
			value[0]=tmp;
		}
		if($.isPlainObject(value[0]) && value[0].id){
			metadata[key]=value[0].id.toString();
		}
		else{
			if($.isArray(value)){
				if(value[0]===null || value[0]===undefined) metadata[key]="";
				else metadata[key]=value[0].toString();
			}else{
				metadata[key]=value.toString();
			}
		}
		if( approvedMetadata && $.isArray(approvedMetadata) && $.inArray(key,approvedMetadata)>-1){
			quickMetadata[key]=metadata[key];
		}
	});
	if(quickSave){
		return quickMetadata;
	}
	else{
		return metadata;
	}
}
        