<?php 

$configObj=json_decode($config);



foreach ($configObj->templates as $template){
	$templates[$template->name]=$template;
}

foreach ($configObj->types as $type){
    $types[$type->typeId]=$type;
	if ($type->rootAble) $rootAble[]=$type->typeId;
	if (count($type->associatedTemplates)>0){
	    foreach ($type->associatedTemplates as $key=>$val){
	        $types[$type->typeId]->associatedTemplates[$key]->metadataTemplate=$templates[$val->metadataTemplateName];
	    }
	}
}


function processBpmn($processes, $wfkey){
	
	$processXml=base64_decode($processes[$wfkey]->content);
	
	$processXml=str_replace("activiti:", "", $processXml);
	$doc = new DOMDocument();
	$doc->loadXML($processXml);
	$xmlPath = new DOMXPath($doc);
	
	$pspec['name']=$doc->getElementsByTagName("process")->item(0)->getAttribute("name");
	
	$nodelist=$doc->getElementsByTagName("userTask");
	$nb = $nodelist->length;
	for ($idx=0;$idx<$nodelist->length;$idx++){
		$userTask=$nodelist->item($idx);
		$userTaskSpec=[];
		$userTaskSpec['name']=$userTask->getAttribute('name');
		$userTaskSpec['id']=$userTask->getAttribute('id');
		$userTaskSpec['candidateGroups']=$userTask->getAttribute('candidateGroups');
		$userTaskSpec['candidateUsers']=$userTask->getAttribute('candidateUsers');
		$extchild=$userTask->getElementsByTagName("extensionElements");
		for ($idx1=0;$idx1<$extchild->length;$idx1++){
			$extEl=$extchild->item($idx1);
			$listners=$extEl->getElementsByTagName("taskListener");
			for ($idx2=0;$idx2<$listners->length;$idx2++){
				$listener=$listners->item($idx2);
				$listnerSpec=[];
				$listnerSpec['event']=$listener->getAttribute('event');
				$listnerSpec['expression']=$listener->getAttribute('expression');
				$userTaskSpec['listners'][]=$listnerSpec;
			}
			$formProperties=$extEl->getElementsByTagName("formProperty");
			for ($idx2=0;$idx2<$formProperties->length;$idx2++){
				$formProperty=$formProperties->item($idx2);
				$formPropertySpec=[];
				$formPropertySpec['id']=$formProperty->getAttribute('id');
				$formPropertySpec['name']=$formProperty->getAttribute('name');
				$formPropertySpec['required']=$formProperty->getAttribute('required');
				$formPropertySpec['type']=$formProperty->getAttribute('type');
				$userTaskSpec['formProperties'][]=$formPropertySpec;
			}
		}
		$pspec['userTask'][]=$userTaskSpec;
	}
	
	$nodelist=$doc->getElementsByTagName("serviceTask");
	$nb = $nodelist->length;
	for ($idx=0;$idx<$nodelist->length;$idx++){
		$serviceTask=$nodelist->item($idx);
		$serviceTaskSpec=[];
		$serviceTaskSpec['name']=$serviceTask->getAttribute('name');
		$serviceTaskSpec['id']=$serviceTask->getAttribute('id');
		$serviceTaskSpec['expression']=$serviceTask->getAttribute('expression');
		
		$extchild=$serviceTask->getElementsByTagName("extensionElements");
		for ($idx1=0;$idx1<$extchild->length;$idx1++){
			$extEl=$extchild->item($idx1);
			$listners=$extEl->getElementsByTagName("taskListener");
			for ($idx2=0;$idx2<$listners->length;$idx2++){
				$listener=$listners->item($idx2);
				$listnerSpec=[];
				$listnerSpec['event']=$listener->getAttribute('event');
				$listnerSpec['expression']=$listener->getAttribute('expression');
				$serviceTaskSpec['listners'][]=$listnerSpec;
			}
			if ($serviceTask->getAttribute('type')=='mail'){
				$fields=$extEl->getElementsByTagName("field");
				for ($idx2=0;$idx2<$fields->length;$idx2++){
					$field=$fields->item($idx2);
					$fieldSpec=[];
					$fieldSpec['name']=$field->getAttribute('name');
					if ($field->getElementsByTagName("expression")->length>0){
						$value=$field->getElementsByTagName("expression")->item(0)->textContent;
					}else {
						$value=$field->textContent;
					}
					$fieldSpec['value']=$value;
					$serviceTaskSpec['fields'][]=$fieldSpec;
				}
			}
		}
		if ($serviceTask->getAttribute('type')=='mail'){
			$pspec['mailTask'][]=$serviceTaskSpec;
		}else {
			$pspec['serviceTask'][]=$serviceTaskSpec;
		}
		
	}
	if ($wfkey=='ce-gemelli-create-studio-flow' && false){
		var_dump($pspec);
		echo "<pre>";
		echo htmlentities($processXml);
		echo "</pre>";
		
		die();
	}
	return $pspec;
}

foreach ($configObj->processes as $pkey=>$process){
	$processes[$pkey]=$process;
	$processesDetails[$pkey]=processBpmn($processes,$pkey);
	
}


