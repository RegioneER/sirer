<?php

class ODMtoXMR {

    function __construct($file, $path) {

        $this -> odm = simplexml_load_file($file);
        $this -> path = $path;
        if (!$this -> odm) {
            throw new Exception("The file you have chosen doesn't seem to be a valid CDISC File.", ERROR);
            //return null;//$this->displayError("The file you chose doesn't seem to be a valid CDISC File.");
        }
        if (function_exists($this -> odm -> attributes()) && $this -> odm -> attributes() -> FileType != 'Snapshot') {
            throw new Exception("The file you have chosen doesn't seem to be a valid CDISC Snapshot File.", ERROR);
            //$this->displayError("");
            //die();
        }
        if ($this -> odm -> attributes() -> ODMVersion > '1.3.1') {
            throw new Exception("Please be aware that the document you submitted may contains features not yet supported.", ERROR);
        }
    }

    function parse() {
        $dateODM = $this -> odm -> attributes() -> CreationDateTime;
        $dateODMArr = explode('T', $dateODM);
        $visite_exams_dom = $this -> generateVisitExam($dateODMArr[0]);
        $this -> save_dom('visite_exams.xml', $visite_exams_dom, $this -> path);
        foreach ($this -> odm-> Study -> MetaDataVersion -> FormDef as $formDef => $form) {
            $this -> save_dom($this -> cleanVar($form -> attributes() -> OID, 'F', $dateODMArr[0]) . ".xml", $this -> generateExam($form -> attributes() -> OID, $dateODMArr[0]), $this -> path);
        }
    }

    function generateVisitExam($dateVer = '') {
        $namespaces = $this -> odm -> getNameSpaces(true);
        $StudyEventDef = $this -> odm -> Study -> MetaDataVersion -> Xpath("//*[local-name()='StudyEventDef']");
        $FormDef = $this -> odm -> Study -> MetaDataVersion -> Xpath("//*[local-name()='FormDef']");
        $Protocol = $this -> odm -> Study -> MetaDataVersion -> Protocol;
        $Protocol -> registerXPathNamespace('sdm', '');
        $dom = new DomDocument('1.0', 'utf-8');
        $visit_exam = $dom -> createElement('visit_exam');
		$group = $dom -> createElement('group');
		$group-> setAttribute('text', 'PAZIENTE');
        $v = 0;
        if ($StudyEventDef) {
            foreach ($StudyEventDef as $key => $value) {
                $visit[$v] = $dom -> createElement('visit');
                $visit[$v] -> setAttribute('number', $v);
                if ($value -> Description -> TranslatedText == '') {
                    $titolo = $value -> attributes() -> Name;
                } else {
                    $titolo = $value -> Description -> TranslatedText;
                }
                $visit[$v] -> setAttribute('text', $titolo);
                $visit[$v] -> setAttribute('short_txt', $value -> attributes() -> Name);
                // $visit[$v] -> setAttribute('short_txt', cleanVar($value -> attributes() -> OID, 'SE'));
                if ($value -> attributes() -> Repeating == 'Yes') {
                    $visit[$v] -> setAttribute('progr', 'yes');
                }
                $v++;
            }
        } else {
            // creo una visita di default
            $visit[$v] = $dom -> createElement('visit');
            $visit[$v] -> setAttribute('number', '0');
            $visit[$v] -> setAttribute('text', 'Registration');
            $visit[$v] -> setAttribute('short_txt', 'Registration');
        }
        $e = 0;
        if (!$FormDef) {
            $this -> displayError("The file you chose doesn't cointain any form.");
        }
        foreach ($FormDef as $key => $value) {
            $exam = $dom -> createElement('exam');
            $exam -> setAttribute('xml', $this -> cleanVar($value -> attributes() -> OID, 'F', $dateVer) . '.xml');
            if ((String)$value -> attributes() -> Repeating == 'Yes') {
                $exam -> setAttribute('progr', 'yes');
            }
            $text = $dom -> createElement('text');
            if ($this -> verifCDATA($value -> attributes() -> Name)) {
                $funz = 'createCDATASection';
            } else {
                $funz = 'createTextNode';
            }
            $text -> appendChild($dom -> $funz($value -> attributes() -> Name));
            $exam -> appendChild($text);

            if ($StudyEventDef) {
                // Inserisco gli esami da StudyEventDef
                $s = 0;
                foreach ($StudyEventDef as $s_key => $s_value) {
                    // dalle definizioni globali (Protocol)
                    $activities = $s_value -> children($namespaces['sdm']);
                    foreach ($activities as $act_key => $act_value) {
                        $act_OID = $act_value -> attributes() -> ActivityOID;
                        $act_result = $value -> xpath("//sdm:Structure//sdm:ActivityDef[@OID='{$act_OID}']");
                        foreach ($act_result as $act_el_key => $act_el_value) {
                            if ($act_el_value -> FormRef) {
                                foreach ($act_el_value -> FormRef as $f_key => $f_value) {
                                    if (((string)$act_el_value -> FormRef -> attributes() -> FormOID) == $value -> attributes() -> OID) {
                                        $exams[$s] = $exam -> cloneNode(true);
                                        $exams[$s] -> setAttribute('number', $e++);
                                        $visit[$s] -> appendChild($exams[$s]);
                                    }
                                }
                            }
                        }
                    }
                    // dalle definizioni locali (StudyEventDef)
                    if ($s_value -> FormRef) {
                        foreach ($s_value -> FormRef as $f_key => $f_value) {
                            if (((string)$f_value -> attributes() -> FormOID) == $value -> attributes() -> OID) {
                                $exams[$s] = $exam -> cloneNode(true);
                                $exams[$s] -> setAttribute('number', $e++);
                                $visit[$s] -> appendChild($exams[$s]);
                            }
                        }
                    }
                    $s++;
                }
            } else {
                $exam -> setAttribute('number', $e++);
                $visit[0] -> appendChild($exam);
            }
        }
        foreach ($visit as $data) {
            $group -> appendChild($data);
        }
		$visit_exam-> appendChild($group);
        $dom -> appendChild($visit_exam);
        return $dom;
    }

    function generateExam($formID, $dateVer = '') {
        $formSel = $this -> odm -> Xpath("//*[local-name()='FormDef'][@OID='{$formID}']");
        $dom = new DomDocument('1.0', 'utf-8');
        $form = $dom -> createElement('form');
        $form -> setAttribute('fname', $this -> cleanVar($formID, 'FORM', $dateVer));
        $form -> setAttribute('titolo', $formSel[0] -> attributes() -> Name);
        $form -> setAttribute('table', $this -> cleanVar($formID, 'FORM', $dateVer));
        $form -> setAttribute('link_to', 'index.php?CENTER=[CENTER]|and|CODPAT=[CODPAT]|and|exams=visite_exams.xml');
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'CODPAT', 'var_type' => 'number', 'pk' => 'yes'))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'USERID_INS', 'bytb' => 'yes', 'var_type' => 'text', 'var_size' => '40', 'bytb' => 'ana_utenti', 'bytbcode' => 'userid', 'bytbdecode' => 'userid', 'bytbwhere' => "userid='[remote_userid]'"))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'ESAM', 'var_type' => 'number', 'pk' => 'yes'))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'VISITNUM', 'var_type' => 'number', 'pk' => 'yes'))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'VISITNUM_PROGR', 'var_type' => 'number', 'pk' => 'yes'))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'INVIOCO', 'var_type' => 'number'))));
        $form -> appendChild($dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'CENTER', 'var_type' => 'number'))));
        $progr = $dom -> importNode($this -> addField(array('type' => 'hidden', 'var' => 'PROGR', 'var_type' => 'number', 'pk' => 'yes')));
        //$progr_val = $dom -> importNode($this -> addField(array('val' => '1'), 'value'));
        //$progr -> appendChild($progr_val);
        $form -> appendChild($progr);
        foreach ($formSel[0] as $key => $value) {
            if ($value -> attributes() -> ItemGroupOID) {
                if ($value -> attributes() && $value -> attributes() -> Mandatory) {
                    $mand = true;
                } else {
                    $mand = false;
                }
                $groups[] = array('el' => $this -> odm -> Xpath("//*[local-name()='ItemGroupDef'][@OID='{$value->attributes()->ItemGroupOID}']"), 'mandatory' => ($mand));
            }
        }
        if (count($groups) > 0) {

            foreach ($groups as $i => $group) {

                $secAttrList[] = array('type' => 'text', 'tb' => 'no', 'var' => $this -> cleanVar($group['el'][0] -> attributes() -> OID, 'IG', $dateVer, 'SEC'));
                if ($group['el'][0] -> attributes() -> Repeating == 'Yes') {
                    $secAttrList[] = array('sec_progr' => 'yes');
                }
                if ($group['mandatory'][0]) {
                    $secAttrList[] = array('sec_mandatory' => 'yes');
                }
                $secAttr = array();
                foreach ($secAttrList as $key => $value) {
                    $secAttr = array_merge($secAttr, $value);
                }
                $el = $dom -> importNode($this -> addField($secAttr));
                $txt_value = $dom -> importNode($this -> addField(array(), 'txt_value'));
                if ($this -> verifCDATA($group['el'][0] -> attributes() -> Name)) {
                    $funz = 'createCDATASection';
                } else {
                    $funz = 'createTextNode';
                }
                $txt_value -> appendChild($dom -> $funz($group['el'][0] -> attributes() -> Name));

                $el -> appendChild($txt_value);
                // come gestire l'obbligatorietà/la ripetibilità per il gruppo di elementi?
                $form -> appendChild($el);
                foreach ($group['el'][0]->ItemRef as $j => $item) {
                    unset($attributesList);
                    $itemSel = $item -> attributes() -> ItemOID;
                    $itemFromODM = $this -> odm -> Xpath("//*[local-name()='ItemDef'][@OID='{$itemSel}']");
                    // nome
                    if ($itemFromODM[0] -> Alias) {
                        $nVar = $this -> cleanVar($itemFromODM[0] -> Alias -> attributes() -> Name);
                    } else {
                        $nVar = $this -> cleanVar($itemFromODM[0] -> attributes() -> Name);
                    }
                    $cVar = $this -> cleanVar($itemFromODM[0][0] -> attributes() -> OID, 'ID', $dateVer);
                    $varName = $cVar;//($nVar ? $nVar : $cVar);
                    $attributesList[] = array('var' => $varName);
                    // obbligatorietà
                    $mandatory = ($item -> attributes() -> Mandatory == 'Yes' ? true : false);
                    if ($mandatory) {
                        $attributesList[] = array('send' => 'obbligatorio');
                    }
                    // tipo variabile
                    $varType = $itemFromODM[0] -> attributes() -> DataType;
                    // verifico se è select
                    unset($elSelect);
                    if ($itemFromODM[0] -> CodeListRef) {
                        $varType = 'select';
                    }
                    // dimensione
                    $varLen = $itemFromODM[0] -> attributes() -> Length;
                    if ($varLen && $varType != 'select') {
                        $attributesList[] = array('var_size' => $varLen);
						$attributesList[] = array('size' => $varLen);
                    }
                    if ($varType == 'text' || $varType == 'select' || $varType == 'string' || $varType == 'URI') {
                        // va trattato come testo o lista
                        $attributesList[] = array('type' => ($varType == 'select' ? 'select' :  'textbox'), 'var' => $varName, 'send' => ($mandatory ? 'obbligatorio' : 'facoltativo'));
                        if ($varType == 'select') {
                            $list = $itemFromODM[0] -> CodeListRef -> attributes() -> CodeListOID;
                            $listFromODM = $this -> odm -> Xpath("//*[local-name()='CodeList'][@OID='{$list}']");
                            $k = 1;
                            foreach ($listFromODM[0] as $key => $value) {
                            	$codedValue = (array)$value -> attributes();
								$codedValue = $codedValue['@attributes'];
                                $codedValue=$codedValue['CodedValue'];
								//die($value -> attributes() -> CodedValue);
                                $elSelect[$codedValue] = $dom -> importNode($this -> addField(array('val' => $codedValue), 'value'));
                                if ($this -> verifCDATA($value -> Decode -> TranslatedText)) {
                                    $funz = 'createCDATASection';
                                } else {
                                    $funz = 'createTextNode';
                                }
                                $elSelect[$codedValue] -> appendChild($dom -> $funz($value -> Decode -> TranslatedText));
                            }
                        }
                        
                    }
					elseif ($varType == 'boolean') {
						//gestione temporanea tipi boolean (visualizzo con radio, yes/no e annulla)   	
						$attributesList[] = array('type' => 'radio', 'var' => $varName, 'send' => ($mandatory ? 'obbligatorio' : 'facoltativo'));
						$elSelect['1'] = $dom -> importNode($this -> addField(array('val' => '1'), 'value'));
                       	$elSelect['1'] -> appendChild($dom -> createTextNode('Yes'));
						$elSelect['0'] = $dom -> importNode($this -> addField(array('val' => '0'), 'value'));
						$elSelect['0'] -> appendChild($dom -> createTextNode('No'));
					}
					elseif ($varType == 'date' || $varType == 'time' || $varType == 'datetime' || $varType == 'partialDate' || $varType == 'partialDate' || $varType == 'partialTime' || $varType == 'partialDatetime' || $varType == 'durationDatetime' || $varType == 'intervalDatetime' || $varType == 'incompleteDatetime' || $varType == 'incompleteDate' || $varType == 'incompleteTime') {
                        // vanno trattati come date
                        $attributesList[] = array('type' => 'date_cal');
                    } elseif ($varType == 'integer' || $varType == 'float' || $varType == 'double') {
                        // vanno trattati come number
                        $attributesList[] = array('type' => 'textbox');
                        $attributesList[] = array('var_type' => 'number');
                    }
                    // collego attributi
                    $attributes = array();
                    foreach ($attributesList as $key => $value) {
                        $attributes = array_merge($attributes, $value);
                    }
                    $subEl = $dom -> importNode($this -> addField($attributes));
                    // inserisco testo
                    $txt_value = $dom -> importNode($this -> addField(array(), 'txt_value'));
					if($itemFromODM[0] -> attributes() -> Name){
						$txt_val=$itemFromODM[0] -> attributes() -> Name;
					}
					else if ($itemFromODM[0][0] -> Question -> TranslatedText) {
                        $txt_val = $itemFromODM[0][0] -> Question -> TranslatedText;
                    }
					elseif ($itemFromODM[0][0] -> attributes() -> Comment) {
                        $txt_val = $itemFromODM[0][0] -> attributes() -> Comment;
                    }
                    if ($this -> verifCDATA($txt_val)) {
                        $funz = 'createCDATASection';
                    } else {
                        $funz = 'createTextNode';
                    }
                    $translatedText = $dom -> $funz($txt_val);
                    $translatedText -> nodeValue = str_replace("\n", ' ', $translatedText -> nodeValue);
                    $txt_value -> appendChild($translatedText);
                    $subEl -> appendChild($txt_value);
                    // inserisco options
                    if (count($elSelect) > 0) {
                        foreach ($elSelect as $key => $value) {
                            $subEl -> appendChild($value);
                        }
                    }
                    $form -> appendChild($subEl);
                    if ($itemFromODM[0] -> MeasurementUnitRef) {
                        unset($measures);
                        $unitVar = $this -> cleanVar($nVar, '', '', 'UNIT');
                        $elMeasure = $dom -> importNode($this -> addField(array('type' => 'select', 'var' => $unitVar)));
                        $txt_value = $dom -> importNode($this -> addField(array(), 'txt_value'));
                        $txt_value -> appendChild($dom -> createTextNode($translatedText -> nodeValue . ' Unit'));
                        $elMeasure -> appendChild($txt_value);
                        $m = 1;
                        foreach ($itemFromODM[0]->MeasurementUnitRef as $m_key => $m_value) {
                            $measure = $this -> odm -> Xpath("//*[local-name()='MeasurementUnit'][@OID='{$m_value -> attributes() -> MeasurementUnitOID}']");
                            $elMeasureSelect[$m] = $dom -> importNode($this -> addField(array('val' => $m), 'value'));
                            if ($this -> verifCDATA($measure[0] -> Symbol -> TranslatedText)) {
                                $funz = 'createCDATASection';
                            } else {
                                $funz = 'createTextNode';
                            }
                            $elMeasureSelect[$m] -> appendChild($dom -> $funz($measure[0] -> Symbol -> TranslatedText));
                            $elMeasure -> appendChild($elMeasureSelect[$m++]);
                        }
                        $form -> appendChild($elMeasure);
                    }
					//GENHD-19 GESTISCRO import anche dei RangeCheck - vmazzeo 04.12.2014
					if ($itemFromODM[0] -> RangeCheck ) {
						// echo "<pre>";							
						// print_r($itemFromODM[0] -> RangeCheck );
						
						$comparator="";
						$level="";
						$rangecheck_attributes=array();
						
	                    if($itemFromODM[0] -> RangeCheck -> attributes() -> Comparator){
							$rangecheck_attributes['comparator']=(string)($itemFromODM[0] -> RangeCheck ->attributes() -> Comparator);
						}
						
						if($itemFromODM[0] -> RangeCheck -> attributes() -> SoftHard){
							$rangecheck_attributes['level']=(string)$itemFromODM[0] -> RangeCheck -> attributes() -> SoftHard;
						}
						$rangecheck = $dom -> importNode($this -> addField($rangecheck_attributes, 'rangecheck'));
	                   
					    $checkValue = $dom -> createElement('checkValue');//TODO: GESTIRE MULTI checkValue (caso comparator="IN" o "NOT_IN")
        				$checkValue -> appendChild($dom -> createTextNode($itemFromODM[0] -> RangeCheck -> CheckValue));
	                   	$rangecheck->appendChild($checkValue);
	                    
						$message = $dom -> createElement('message');
        				$message -> appendChild($dom -> createTextNode($itemFromODM[0] -> RangeCheck -> ErrorMessage->TranslatedText));
	                   	$rangecheck->appendChild($message);
						
	                    $subEl -> appendChild($rangecheck);
						// print_r($rangecheck);
						// echo "</pre>";
						// //die();
						
	                }			
                    // rimangono da gestire hexBinary | base64Binary | hexFloat | base64Float
                }
            }
        }
        $save = $dom -> createElement('save');
        $save -> appendChild($dom -> createTextNode('Save'));
        $form -> appendChild($save);
		$send = $dom -> createElement('send');
        $send -> appendChild($dom -> createTextNode('Send'));
        $form -> appendChild($send);
        $cancel = $dom -> createElement('cancel');
        $cancel -> appendChild($dom -> createTextNode('Cancel'));
        $form -> appendChild($cancel);
        $dom -> appendChild($form);
        return $dom;
    }

    function addField($options = array(), $varType = 'field') {
        $dom = new DOMDocument('1.0', 'utf-8');
        $element = $dom -> createElement($varType);
        foreach ($options as $key => $value) {
            $element -> setAttribute($key, $value);
        }
        $dom -> appendChild($element);
        return $element;
    }

    function cleanVar($var, $type = '', $date = '', $suff = '') {
        $subst['.'] = '_';
        $subst[' '] = '';
        $subst['?'] = '';
        $subst['%'] = '';
        $subst['/'] = '';
        $var = str_replace('_' . $date, '', $var);
        $var = str_replace($type . '.', '', $var);
        foreach ($subst as $key => $value) {
            $var = str_replace($key, $value, $var);
        }
        $var = substr($var, 0, (30 - (strlen($suff) + 1)));
        $var .= ($suff ? '_' : '') . $suff;
        return strtoupper($var);
    }

    function verifCDATA($data) {
        $needsCDATA = (strpos($data, '[') !== false || strpos($data, ']') !== false || strpos($data, '<') !== false || strpos($data, '>') !== false || strpos($data, '&') !== false);
        return $needsCDATA;
    }

    function save_dom($fileName, $dom, $path = "../../cdisc-upload/") {
        return $dom -> save($path . $fileName);
    }

    function printArea($fileName, $dom, $path = "../../cdisc-upload/") {
        $output = "";
        $dom -> formatOutput = true;
        $dom -> preserveWhiteSpace = false;
        $descr = $_POST['study_root'];
        $prefix = $_POST['study_prefix'];
        //printf("<pre>%s</pre>", htmlentities($dom -> saveXML()));
        $dom -> save($path . $fileName);

        $fileXSD = "form.xsd";
        if ($fileName == 'visite_exams.xml') {
            $fileXSD = "visite_exams.xsd";
        }
        $output .= $this -> printTitle($fileName, "");
        //$path.$fileName
        $output .= $this -> printTitle('<i class="fa fa-download"></i> Download file', $path . $fileName);

        $output .= "<form class=\"form-horizontal\" name=\"validation\" action=\"" . url_for('/study/builder') . "/" . $prefix . "/validate\" method=\"POST\">
	    <i class=\"fa fa-thumbs-up\"></i> <input type=\"submit\" value=\"Validate file\">
	    <input type=\"hidden\" name=\"file_xml\" value=\"{$fileName}\" >
	    <input type=\"hidden\" name=\"file_xsd\" value=\"{$fileXSD}\" >
	    <input type=\"hidden\" name=\"study_root\" value=\"{$descr}\"/>
	    <input type=\"hidden\" name=\"study_prefix\" value=\"{$prefix}\"/>
	    <input type=\"hidden\" name=\"validation\" value=\"true\" >
	    <input type=\"hidden\" name=\"tab\" value=\"2\" >
	    </form>";
        //$output.=$this->printTitle('<br/><i class="fa fa-thumbs-up">Validate file</i>',$path.$fileName);
        //$output.="<hr/>";
        return $output;
    }

    function printAttributes($source, $title = "", $eol = '<hr/>') {
        $output = "";
        $output .= $this -> printTitle($title);
        $output .= "<pre>";
        foreach ($source->attributes() as $key => $value) {
            $output .= $this -> printLine($key, $value);
        }
        $output .= "</pre>";
        $output .= $eol;
        return $output;
    }

    function printElements($source, $elements, $title = "") {
        $output = "";
        $output .= $this -> printTitle($title);
        foreach ($elements as $key) {
            $output .= $this -> printLine($key, $source -> $key);
        }
        $output .= "<hr/>";
        return $output;
    }

    function printLine($key, $value, $eol = '<br/>') {
        $output = "{$key}: <b>{$value}</b>{$eol}";
        return $output;
    }

    function printTitle($title, $path = "") {
        $output = "";
        if ($path != "") {
            $path = ' href="' . $path . '" target="_blank" ';
            $output .= '<a ' . $path . ' >' . $title . '</a>';
        } else {
            $output .= '<h5>' . $title . '</h5>';
        }
        return $output;
    }

    function displayError($error, $warning = false) {
        $output = "";
        if ($warning) {
            $output .= "Warning: " . $error;
        } else {
            die($error);
        }
        return $output;
    }

}
?>