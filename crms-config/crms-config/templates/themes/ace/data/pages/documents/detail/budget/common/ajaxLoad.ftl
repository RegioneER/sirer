				if(loadedElement && groupItems && groupItems.length>0){
					parseElement(loadedElement);
				}
				else{
					Pace.restart();
					(function(){
						$.ajax({
							dataType: "json",
							contentType: "application/json; charset=utf-8",
							url:'${baseUrl}/app/rest/documents/'+id+'/getGrouppedElements'
						}).done(function(data){
								groupItems=data;
								parseElement(loadedElement);
							}
							).fail(alertError);
					})();
				}