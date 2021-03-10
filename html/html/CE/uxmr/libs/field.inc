<?
/**
 * Classe Field
 *
 * @package Fields
 */
class field extends field_prototype {

	function field($xml_form, $i, $conn=null, $inputval=null, $in=null, $service=null, $errors=null) {
		if (!isset($conn)) global $conn;
		if (!isset($inputval)) global $inputval;
		if (!isset($in)) global $in;
		if (!isset($service)) global $service;
		if (!isset($errors)) global $errors;
		parent::field_prototype($conn, $xml_form, $i, $in, $inputval, $service, $errors);
	}

}


/**
 * Classe prototipo
 *
 */
class field_prototype{

	var $attributes;
	var $values;
	var $cols_form;
	var $testo;
	var $html;
	var $field_stmt;
	var $values_stmt;
	var $id;
	var $validata=true;
	var $condition_passed=true;
	var $xml_form;
	var $input_txt;
	var $input_field;
	var $session_vars;
	var $db_vars;
	var $errors;
	var $service;
	var $conn;
	var $onload;
	var $check_js;
	var $invia_js;
	var $salva_js;
	var $inrevisione_js;
	var $config_service;
	var $edit_tag;
	var $script;
	var $class;
	/**
	 * Costruttore
	 *
	 * @param dbcon $conn
	 * @param String $xml_form
	 * @param number $i
	 * @param array $session_vars
	 * @param array $db_vars
	 * @param String $service
	 * @param array $errors
	 * @return field_prototype
	 */
	function field_prototype($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors){
		$this->session_vars=$session_vars;
		$this->db_vars=$db_vars;
		$this->errors=$this->errors;
		$this->xml_form=$xml_form;
		$this->service=$service;
		$this->conn=$conn;
		$this->cols_form=$xml_form->form['COLS'];
		$this->config_service=$this->xml_form->config_service;
		foreach ($xml_form->fields[$i] as $key => $val){
			switch($key):
			case "TESTO":
				$this->testo=$val;
				break;
			case "VALUE":
				$this->values=$val;
				break;
			default:
				$this->attributes[$key]=$val;
				endswitch;
		}

		if ($this->attributes['BYTB']!='' && !$this->session_vars['avoidBytb']) $this->fields_value_bytb($this->attributes['BYTB']);
		if ($this->attributes['VAR']) $this->id=$this->attributes['VAR'];
		else {
			$this->id=$this->attributes['NAME'];
			$this->attributes['TB']='no';
		}
		if($this->attributes['SEND_MATCH']!='' && $this->attributes['SEND']!=''){
			if(!preg_match("{$this->attributes['SEND_MATCH_EXPR']}",$this->session_vars[$this->attributes['SEND_MATCH']])) unset($this->attributes['SEND']);
		}
		if (strtolower(trim($this->attributes['SEND']))=='obbligatorio' && ($this->attributes['CONDITION']=='' || $this->attributes['ASTERISCO']=='yes' || ($this->config_service['SHOW_MANDATORY_ON_HIDE']!='' && $this->attributes['HIDE']=='yes'))) $this->testo.="<font color=red>*</font>";
		$this->errors=$this->errors;
		if (isset($this->errors[$this->id])) $this->testo.="<br><font color=red>".$this->errors[$this->id]."</font>";
        if($this->config_service['auto_facoltativi'] && $this->attributes['TB']!='no' && $this->attributes['SAVE']=='' && $this->attributes['VAR_TYPE']=='number'  && $this->attributes['VAR']!='' && $this->attributes['TYPE']!='hidden'){
            $this->attributes['SAVE']='facoltativo';
        }
        if($this->config_service['auto_facoltativi'] && $this->attributes['TB']!='no' && $this->attributes['SEND']=='' && $this->attributes['VAR_TYPE']=='number'  && $this->attributes['VAR']!=''  && $this->attributes['TYPE']!='hidden'){
            $this->attributes['SEND']='facoltativo';

        }
        if($this->attributes['NO_DM_CHANGE']!='' && $this->attributes['SEND']!='' && $this->session_vars['USER_TIP']=='DM'){
        	unset($this->attributes['SEND']);
        
        }
        $this->attributes['DEF'].=$this->audit_trail_txt();  
	}

	/**
	 * Costruisce ill codice html del campo in compilazione
	 *
	 * @param boolean $equery
	 */
	function make_open_html($equery=false){
		$function_to_call='open_';
		$in=$this->session_vars;
		$inputval=$this->db_vars;

		if(strtolower($this->config_service['lang'])=='en'){
			$testi['Valore Cambiato']="Changed value (old selection: ";
			$testi['Valore Aggiunto']="Added value ";
		}
		else{
			$testi['Valore Cambiato']="Valore Cambiato (vecchia selezione:";
			$testi['Valore Aggiunto']="Valore Aggiunto";
		}

		if (isset($this->values) and !is_array($this->values)) $value=$this->values;
		if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
		if (isset($in[$this->attributes['VAR']])) $value=$in[$this->attributes['VAR']];
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		$value=htmlentities($value,ENT_QUOTES,'UTF-8');
		if ($this->attributes['PRIORITY_BYTB'] == 'yes' ){
			if(is_array($this->values)){
				foreach ($this->values as  $curValue) {
					$value=$curValue;
				}
			}else if($this->values!=''){
				$value=$this->values;
			}
		}
		if ($in ['USER_TIP'] == 'DM' && $this->attributes['NO_DM_CHANGE']!=''){
			$function_to_call_no_dm="close_";
			$this->{$function_to_call_no_dm}($value);
		}
		else if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
		$cols=$this->attributes['COLS']+0;
		if ($cols==0) $cols=1;

		if ($equery){

			if ($this->input_field!='' && $this->attributes['TYPE']!='hidden'){

				$testo_changed='';
				$img_eq='';
				if ($this->xml_form->old_values[$this->id]!=$this->xml_form->tb_vals[$this->id]){
					if($this->attributes['TYPE']=='file_doc' || $this->attributes['TYPE']=='file_cme') {
						if($this->attributes['TYPE']=='file_cme'){
							$prev=$this->CMELayer->queryPrevious($this->inputval[$this->attributes['VAR']]);	
							$this->xml_form->old_values_docs_nomi[$this->id]=$prev['NOME_FILE'];
						}
						if($this->xml_form->old_values_docs_nomi[$this->id]!="")
						$old_spec="<br /><a class=\"normal_link\" href=\"WCA/download.php?id={$this->xml_form->old_values[$this->id]}\"><span><img src=\"../images/word.gif\" alt=\"documento vecchio \" />{$this->xml_form->old_values_docs_nomi[$this->id]}</span></a>";
						else
						$old_spec="<h3 style=\"display:inline;text-decoration:underline;\">Valore aggiunto: Non era presente un allegato</h3>";
					}else if($this->attributes['TYPE']=='checkbox') {
						if($this->xml_form->old_values[$this->id]=="1")
							$old_spec="Selezionato";
						else $old_spec="Non selezionato";
					} else	
					
					if (isset($this->xml_form->old_values['D_'.$this->id])){
						$old_spec=$this->xml_form->old_values['D_'.$this->id];
					}
					else $old_spec=$this->xml_form->old_values[$this->id];

					$img_eq="<img src=\"images/eq_img.png\">";

					$str_testo_agg=$testi['Valore Aggiunto'];
					$str_testo_change="({$testi['Valore Cambiato']} $old_spec)";

					if ($old_spec==''){
						$testo_changed="<br/><p style='color:blue;font-weight:bold;'>$str_testo_agg</p>";
					} else {
						$testo_changed="<br/><p style='color:red;font-weight:bold;'>$str_testo_change</p>";
					}
				}

				$this->close_($value);
				$close_field=$this->input_field;
				$this->open_($value);
				$this->input_field="
			<table width=\"100%\" border=0>
				<tr>
					<td valign=top>
			<span id='view_field_{$this->id}'>$close_field</span>
			<span id='mod_field_{$this->id}' style=\"display:none\">{$this->input_field}</span>
					</td>
					<td valign=top align=right>
					$img_eq
					</td>
				</tr>
			</table>
			";
					$this->input_txt.="&nbsp; <a href=\"#\" onclick=\"
			show_hide('view_field_{$this->id}');
			show_hide('mod_field_{$this->id}');
			return false;
		\"><img src=\"images/edit.png\"></a>$testo_changed";
					$this->input_txt="
		    <table width=\"100%\" border=0>
				<tr>
					<td valign=top align=left>
					$img_eq
					</td>
					<td valign=top align=right>
					{$this->input_txt}
					</td>
				</tr>
			</table>
		    ";
			}

		}
		if ($this->attributes['TYPE']=='hidden') {
			$colspan=$cols*2;
			$this->html=$this->input_field;
		}
		if ($this->attributes['CONDITION']!=''){
			$function_to_call='open_condition';
			if (method_exists($this,$function_to_call)) $this->{$function_to_call}($this->attributes['CONDITION']);
		}
		$inputClass="input";
		$txtClass="destra";

		if (isset($this->xml_form->form['INPUTCLASS'])){
			$inputClass=$this->xml_form->form['INPUTCLASS'];
		}
		if (isset($this->xml_form->form['TXTCLASS'])){
			$txtClass=$this->xml_form->form['TXTCLASS'];
		}
		if (count($this->attributes)>0)
		foreach($this->attributes as $key => $val){
			if ($key!='CONDITION'){
				if(false && $this->config_service['jquery2'] && method_exists($this,'open_j'.$key))$function_to_call='open_j'.$key;
				else $function_to_call='open_'.$key;
				if ($function_to_call!='open_condition' && method_exists($this,$function_to_call)) $this->{$function_to_call}($val);
			}
		}
		if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else {
				$html_parser=new HTML_Parser();
				$html_parser->setAttribute("colspan", $colspan);
				if (isset($this->attributes['TXTWIDTH'])){
					$content="
					<table border=0 cellspacing=3 cellpadding=0 width=100%><tr>
					<td valign=top class='$txtClass' width=\"{$this->attributes['TXTWIDTH']}\">$this->input_txt</td>
					<td valign=top class='$inputClass'>$this->input_field</td>
					</tr>
					</table>";
					$html_parser->setContent($content);
				}
				else {
					$html_parser->setAttribute("class", $inputClass);
					//					$html_parser->setAttribute("align", "right");
					$html_parser->setContent($this->input_txt.$this->input_field);
				}
				$html_parser->setType("TD");
				$this->html=$html_parser->print_();
			}
		}
		else
		{
			if ($this->attributes['TYPE']!='hidden') {
				
				
				$html_parser_1=new HTML_Parser();
				$html_parser_1->setAttribute("class", $txtClass);
				$html_parser_1->setAttribute("colspan", $cols);
				$html_parser_1->setAttribute("id", 'cell_'.$this->attributes['VAR']);

				$html_parser_1->setContent($this->input_txt);
				$html_parser_1->setType("TD");
				$html_parser_2=new HTML_Parser();
				$html_parser_2->setAttribute("class", $inputClass);
				$html_parser_2->setAttribute("colspan", $cols);

				if(isset($this->attributes['ALIGN']))
				$html_parser_2->setAttribute("align", $this->attributes['ALIGN']);

				$html_parser_2->setAttribute("id", 'cell_input_'.$this->attributes['VAR']);
				$html_parser_2->setContent($this->input_field);
				$html_parser_2->setType("TD");

				$this->html=$html_parser_1->print_().$html_parser_2->print_();
			}
		}
		if ($this->attributes['TYPE']=='data' && $this->salva_js=='')
		{
			$dcod='00';
			if ($this->attributes['DCONT']=='yes') $dcod='16';
			if ($this->attributes['DSPEC']=='yes') $dcod='03';
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';
			$this->salva_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
		}
		if ($this->attributes['TYPE']=='data' && $this->invia_js=='')
		{
			$dcod='00';
			if ($this->attributes['DCONT']=='yes') $dcod='16';
			if ($this->attributes['DSPEC']=='yes') $dcod='03';
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';
			$this->invia_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
		}
		if ($this->attributes['DISABLED']!=''){
			$onload=$this->onload;
			$onload.=$this->check_js;
			//Compatibilita a ritroso:
			$GLOBALS['onload']=$onload;
		}
	}


	/**
	 * Restituisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value){
		$this->input_txt=$txt;
		$in=$this->session_vars;
		$txt=$this->testo;
		$this->input_txt=$txt;
		if ($this->attributes['ONLY_AF']!='' && $in['make_appl_form']=='') $this->input_txt='';
		//if($this->attributes['PARSE_TXT_VALUE']!='')$this->input_txt=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $this->input_txt);
		if($this->attributes['PARSE_TXT_VALUE']!='') $this->input_txt=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $this->input_txt );
		return;
	}

	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		//$ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
		$txt=$this->testo;
		if ($inputval[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE'])
		$this->input_txt=$txt;
		if ($this->attributes['NO_VIS']!='')$this->input_txt='';
		if ($this->attributes['ONLY_AF']!=''  && $in['make_appl_form']=='') $this->input_txt='';
		//if($this->attributes['PARSE_TXT_VALUE']!='') $this->input_txt=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $this->input_txt);
		if($this->attributes['PARSE_TXT_VALUE']!='') $this->input_txt=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $this->input_txt );
		return;
	}


	/**
	 * Costruisce un array con i valori da inserire in DB
	 *
	 */
	function insert_stmt(){
		//verifica per crypto
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
			return;
		}
		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE']){
				$fm=$this->attributes['FM_CODE'];
                if(strtoupper($this->config_service['lang'])=='IT'){
    				if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
    				if (strtoupper($in[$this->attributes['VAR']])=='NN') $in[$this->attributes['VAR']]=-9922;
    				if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
    				if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
    				//if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
    				//if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                }
                else{
                    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
                    if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
                    if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
                    if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
                    if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
                }
			}

			else
			$fm="00";

			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]=$this->attributes['VAR'];
			$value=$in[$this->attributes['VAR']];
			$value=str_replace("\\\"", "\"", $value);
			$value=str_replace("&quot;", "\"", $value);
			//$value=$in[$this->attributes['VAR']];
			//$value=str_replace("\\\"", "\"", $value);
			$this->value_stmt[0]=$value;
		}
		return;
	}

	/**
	 * Controlla se il campo in tb Ã¨ allineanto con quello definito nell'XML
	 *
	 * @return array
	 */
	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			if ($this->attributes['VAR_TYPE']=='number') $type_field='NUMBER';
			else $type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
			$ret[0]="{$this->attributes['VAR']} {$type_field}";
			return $ret;
		}
		else return ;
	}

	/**
	 * Effettua i controlli lato server e costruisce i controlli lato client sul campo condizionato
	 *
	 * @param String $val
	 */
	function open_condition($val){
		if($this->config_service['jquery'] && method_exists($this,"open_jcondition")) return $this->open_jcondition($val);
		$var_cond=$val;
		$this->condition_passed=false;
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$val_cond=$this->attributes['CONDITION_VALUE'];
		if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
	        	valore=document.forms[0].".$var_cond.".value;
				  if (document.getElementById('tr_".$this->id."'))
					 document.getElementById('tr_".$this->id."').style.display='none';
					";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value){
					if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
					else $value_to_control=$inputval[$var_cond];

					if ($value_to_control==$value) {
						$this->condition_passed=true;
					}
					$this->check_js.=" \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  	if (document.getElementById('tr_".$this->id."'))
								document.getElementById('tr_".$this->id."').style.display='';
						}
						";
				}
				$this->check_js.="
				if (document.getElementById('tr_".$this->id."') && document.getElementById('tr_".$this->id."').style.display=='none' && document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}
				";
			}
			else {
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
				else $value_to_control=$inputval[$var_cond];
				if (is_numeric($val_cond)) $value_to_control-=0;
				
				if ($op=='==') $this->condition_passed=($value_to_control!=$val_cond);
				else $this->condition_passed=($value_to_control==$val_cond);

				$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
				$this->check_js.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else {
							if (document.forms[0].".$this->id."[0] && !document.forms[0].".$this->id.".selectedIndex){
								           radioclear('{$this->id}');
							}
						else document.forms[0].".$this->id.".value='';
						}
						}

				  if (document.getElementById('tr_".$this->id."'))	{

				     document.getElementById('tr_".$this->id."').style.display='none';

				  	}
					}
					else {

				  if (document.getElementById('tr_".$this->id."'))
					  document.getElementById('tr_".$this->id."').style.display='';
					}
					";
			}
		}
		else {

			if ($this->attributes['HIDE_THIS']=='yes') {

				if (preg_match("/,/", $val_cond)){
					$this->check_js.="
	        valore=document.forms[0].".$this->id.".value;
					document.forms[0].".$this->id.".value='';
				  	if (document.getElementById('cell_".$this->id."'))
					 	document.getElementById('cell_".$this->id."').style.display='none';
					if (document.getElementById('cell_input".$this->id."'))
					 	document.getElementById('cell_input".$this->id."').style.display='none';
					";
					$vals=explode(",",$val_cond);
					//$this->condition_passed=false;
					foreach ($vals as $key => $value){
						if ($in[$var_cond]==$value) $this->condition_passed=true;
						$this->check_js.=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			if (document.getElementById('cell_".$this->id."'))
								document.getElementById('cell_".$this->id."').style.display='';
							if (document.getElementById('cell_input".$this->id."'))
								document.getElementById('cell_input".$this->id."').style.display='';
						    document.forms[0].".$this->id.".value=valore;

						}
							";
					}
				}
				else {

					$op ='!=';
					if (preg_match("/\!/", $val_cond)) {
						$val_cond=str_replace("!", "",$val_cond);
						$op='==';
					}
					if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
					else $this->condition_passed=($in[$var_cond]==$val_cond);
					//echo "<hr>$op - $var_cond - $val_cond - {$this->attributes['VAR']}<hr>";
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
					$this->check_js.="
					if (document.forms[0].".$this->id.")
						document.forms[0].".$this->id.".value='';
				  	if (document.getElementById('cell_".$this->id."'))
					   document.getElementById('cell_".$this->id."').style.display='none';
					if (document.getElementById('cell_input".$this->id."'))
					   document.getElementById('cell_input".$this->id."').style.display='none';
					}
					else{
					  if (document.getElementById('cell_".$this->id."'))
						  document.getElementById('cell_".$this->id."').style.display='';
					  if (document.getElementById('cell_input".$this->id."'))
					  	document.getElementById('cell_input".$this->id."').style.display='';
					}
					";
				}
			}
			else {
				if (preg_match("/,/", $val_cond)){
					$this->check_js.="
	        valore=document.forms[0].".$this->id.".value;
	        document.forms[0].".$this->id.".value='';

						";
					$vals=explode(",",$val_cond);
					foreach ($vals as $key => $value){
						if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
						else $value_to_control=$inputval[$var_cond];
						if ($value_to_control==$value) {
							$this->condition_passed=true;
						}
						$this->check_js.=" \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			document.forms[0].".$this->id.".value=valore;
						}
						";

					}
				}else{
					$op ='!=';
					if (preg_match("/\!/", $val_cond)) {
						$val_cond=str_replace("!", "",$val_cond);
						$op='==';
					}
					foreach ($this->xml_form->fields as $key => $val){
						if ($val['TYPE']=='checkbox') {
							foreach ($val['VALUE'] as $key => $val){
								//echo "<li>$key</li>";
								if (!isset($in[$key])) $in[$key]='0';
							}
						}
					}
					if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
					else $this->condition_passed=($in[$var_cond]==$val_cond);

					$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
					$this->check_js.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}

				  if (document.getElementById('tr_".$this->id."'))	{

				     document.getElementById('tr_".$this->id."').style.display='none';

				  	}
					}
					else {

				  if (document.getElementById('tr_".$this->id."'))
					  document.getElementById('tr_".$this->id."').style.display='';
					}
					";
				}
			}
		}
		$this->html="<tr id='tr_".$this->id."' style=\"display:\">".$this->html."</tr>";
	}


	/**
	 * Gestisce la disabilitazione del campo
	 *
	 * @param String $value
	 */
	function open_disabled($value){
		$this->check_js.="
				if(document.forms[0].".$this->id." && document.forms[0].".$this->id.".value!='')
					document.forms[0].".$this->id.".disabled=true;
			";
	}

	/**
	 * Gestisce la disabilitazione del campo
	 *
	 * @param String $value
	 */
	function open_disabled_always($value){
		$this->check_js.="
				if(document.forms[0].".$this->id.")
					document.forms[0].".$this->id.".disabled=true;
			";
	}
	function open_block_value($value){
		if($this->db_vars[$this->attributes['VAR']]!="")
		$this->check_js.="
				if(document.forms[0].".$this->id.")
					document.forms[0].".$this->id.".disabled=true;
			";
	}


	/**
	 * Controlli sul valore del campo (maggiore di )
	 *
	 * @param String $value
	 */
	function open_max($value){
		if (preg_match("/\[/",$campi[$i])){
			//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
			$campo=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i] );
			$this->controlli.="
						value=value_of('".$campo."', '0');
						";
		}
		else {
			$this->controlli.="value=$val;\n";
		}
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
		$alert_msg="Warning the value must be greater than ";
		else
		$alert_msg="Attenzione il valore deve essere maggiore di ";

		$this->controlli.="
				if (document.forms[0].".$this->id.".value>value) {
					alert('".$alert_msg."'+value);
					document.forms[0].".$this->id.".focus();
					return false;
				}
		";
	}

	/**
	 * Controlli sul valore del campo (minore di )
	 *
	 * @param String $value
	 */
	function open_min($value){
		if (preg_match("/\[/",$campi[$i])){
			//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
			$campo=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i] );
			$this->controlli.="
						value=value_of('".$campo."', '0');
						";
		}
		else {
			$this->controlli.="value=$val;\n";
		}
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
		$alert_msg="Warning the value must be less than ";
		else
		$alert_msg="Attenzione il valore deve essere minore di ";

		$this->controlli.="
				if (document.forms[0].".$this->id.".value<=value) {
					alert('".$alert_msg."'+value);
					document.forms[0].".$this->id.".focus();
					return false;
				}
		";
	}

	/**
	 * Costruisce i controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val){

		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE']){
				$fm=$this->attributes['FM_CODE'];
                if(strtoupper($this->config_service['lang'])=='IT'){
                    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
                    if (strtoupper($in[$this->attributes['VAR']])=='NN') $in[$this->attributes['VAR']]=-9922;
                    if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
                    if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                }
                else{
    				if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
    				if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
    				if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
    				if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
    				if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
    				if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
                }
			}

			else
			$fm="00";

			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		/*else
		 {
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
			}*/
		$testo_js=make_js($this->testo);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||($this->attributes['VAR_TYPE']!='text' && $val=='facoltativo')){

			$this->salva_js.="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";

			$this->inrevisione_js.="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
		/*aggiorno con la possibilità di utilizzare più valori divisi da virgola in condition_value da testare approfonditamente (Giorgio Delsignore 14/06/2010)
		 if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
			var value_{$this->attributes['CONDITION']}=value_of('{$this->attributes['CONDITION']}','0');
			if(value_{$this->attributes['CONDITION']}=='{$this->attributes['CONDITION_VALUE']}')c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
			";

			}*/
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
				".$this->attributes['CONDITION']."_setted=false;
				";
			$this->inrevisione_js.="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
				$this->inrevisione_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$condition_value=$this->attributes['CONDITION_VALUE'];
				$oper="==";
				if (preg_match("/!/",$condition_value)) {$oper="!=";$condition_value=substr($condition_value, 1);}
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$condition_value."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
				$this->inrevisione_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->salva_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
			$this->inrevisione_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$this->session_vars=$in;
	}
	
	/**
	 * Funzione che costruisce i controlli javascript per controllare che le condizioni specificate nell'xml
	 * siano verificate
	 *
	 * @return unknown
	 */
	function verifyConditions(){
		if ($this->attributes['CONDITION']!=''){
			$verifyConditions='
				'.$this->attributes['CONDITION'].'_setted=false;
				';
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value){
					$verifyConditions.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='{$value}') {
							{$this->attributes['CONDITION']}_setted=true;
						}
						";
				}
			}
			else{
				$condition_value=$this->attributes['CONDITION_VALUE'];
				$oper="==";
				if (preg_match("/!/",$condition_value)) {
					$oper="!=";
					$condition_value=substr($condition_value, 1);
				}
				$verifyConditions.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'{$condition_value}') {
							{$this->attributes['CONDITION']}_setted=true;
						}
					";
			}
			$verifyConditions.="if({$this->attributes['CONDITION']}_setted)";
		}
		else{
			$verifyConditions='if(true)';
		}
		return $verifyConditions;
	}
	
	/**
	 * Funzione che aggiunge il controllo sul fatto che le condizioni per compilare il campo siano verificate, 
	 * prima di eseguire altri azioni/controlli javascript
	 *
	 * @param unknown_type $js
	 * @return unknown
	 */
	function addConditions($js){
		if($js!='' && $this->attributes['CONDITION']!=''){
			$verifyConditions=$this->verifyConditions();
			$finalJs.="
			{$verifyConditions}{
				{$js}
			}
			";
			return $finalJs;
		}
		else{
			return $js;
		}
	}

	

	/**
	 * Costruisce i controlli all'invio
	 *
	 * @param String $val
	 */
	function open_send($val){
	    if($this->session_vars ['USER_TIP'] != 'DE' && $this->attributes ['CRYPTO'] == 'yes'){
	        return;
	    }
		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE']){
				$fm=$this->attributes['FM_CODE'];
                if(strtoupper($this->config_service['lang'])=='IT'){
                    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
                    if (strtoupper($in[$this->attributes['VAR']])=='NN') $in[$this->attributes['VAR']]=-9922;
                    if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
                    if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                }
                else{
    				if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
    				if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
    				if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
    				if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
    				if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
    				if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
                }
			}
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else
			$controllo="xp".$fm;
		}
		/*else
		{
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else
			$controllo="xp".$fm;
		}*/
		if ($val=='facoltativo') $controllo="f".$controllo;
		$testo_js=make_js($this->input_txt);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		$this->invia_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->invia_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$condition_value=$this->attributes['CONDITION_VALUE'];
				$oper="==";
				if (preg_match("/!/",$condition_value)) {
					$oper="!=";
					$condition_value=substr($condition_value, 1);
				}
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$condition_value."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$in=$this->session_vars;
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]=='') {
					if ($val=='obbligatorio'){
						$this->validata=false;
						$this->errors=$this->errors;
						$testo_js=make_js($this->testo);
						$this->errors[$this->attributes['VAR']]="Il campo ï¿½ obbligatorio";
					}
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='' && $val=='obbligatorio') {
					$this->validata=false;
					$this->errors=$this->errors;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
		$this->session_vars=$in;
	}
	
	function open_jsend($val){
	return
		$this->class.="required,";
		if ( $this->attributes['VAR_TYPE']=='text') return;
		else if ($this->attributes['VAR_STYPE']=='int') $this->class.="isInteger,";
		else if($this->attributes['VAR_STYPE']=='real') $this->class.="isReal,";
		else $this->class.="isReal";
		//return;
		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
	else
		{
			if ($this->attributes['FM_CODE']){
				$fm=$this->attributes['FM_CODE'];
                if(strtoupper($this->config_service['lang'])=='IT'){
                    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
                    if (strtoupper($in[$this->attributes['VAR']])=='NN') $in[$this->attributes['VAR']]=-9922;
                    if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
                    if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                }
                else{
				  if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
			      if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
			      if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
			      if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
			      if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
			      if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
			    }
			}
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else
			$controllo="xp".$fm;
		}
		/*else
		{
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else
			$controllo="xp".$fm;
		}*/
		if ($val=='facoltativo') $controllo="f".$controllo;
		$testo_js=make_js($this->input_txt);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		$this->invia_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->invia_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$in=$this->session_vars;
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]=='') {
					if ($val=='obbligatorio'){
						$this->validata=false;
						$this->errors=$this->errors;
						$testo_js=make_js($this->testo);
						$this->errors[$this->attributes['VAR']]="Il campo ï¿½ obbligatorio";
					}
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='' && $val=='obbligatorio') {
					$this->validata=false;
					$this->errors=$this->errors;
					$testo_js=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
		$this->session_vars=$in;
	}

	/**
	 * Recupera i possibili valori del campo da una query di decodifica
	 *
	 * @param String $value
	 */
	function fields_value_bytb($value){
		if ($this->xml_form->no_field_value_by_tb){
			return;
		}
		if ($this->xml_form->form['NO_LOAD_TB']!='' && $this->xml_form->closed) return;
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		//if ($this->xml_form->closed){// && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
		//	$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
		//	return ;
		//}
		$code=$this->attributes['BYTBCODE'];
		$decode=$this->attributes['BYTBDECODE'];
		$where=$this->attributes['BYTBWHERE'];
		$order_by=$this->attributes['BYTBORDERBY'];
		$where=str_replace("min_of","<",$where);
		$where=str_replace("max_of",">",$where);
		
		//nel caso in cui mi riferisca a ANA_UTENTI oppure abbia settato ANCHE il parametro bytbnoprefix="yes", 
		//allora NON metto il prefisso del servizio davanti
		if (!preg_match("/ana_utenti/i",$value) && $this->attributes['BYTBNOPREFIX']=="")	
			$value=$this->service."_".$value;
		$decode=str_replace("#BR#", "<br>", $decode);
		$decode=str_replace("#i#", "<i>", $decode);
		$decode=str_replace("#/i#", "</i>", $decode);
		$replaceRet=query::varGlobReplace($where);
		//$value=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $value);
		$value=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $value );
		
		$where=$replaceRet['sql'];
		foreach ($replaceRet['binded'] as $key=>$val){
			$binded_vars[$key]=$val;
		}
		/*
		if (preg_match_all("!'(.*?)'!", $where, $matches)){
			foreach ($matches[1] as $k=>$v){
				if (preg_match_all("!\[(.*?)\]!", $v, $matches_1)){
					foreach ($matches_1[1] as $m1=>$v1){
						$v2=str_replace("[$v1]", "'||:global_{$v1}||'", $v );
						$where=str_replace($v, $v2, $where);
						$binded_vars["global_{$v1}"]=var_glob($v1);
					}
				}
			}
		}

		if (preg_match_all("/\[(.*?)\]/", $where, $matches)){
			foreach ($matches[1] as $k=>$v){
				$where=preg_replace("!\[$v\]!", ":global_{$v}", $where);
				$binded_vars["global_{$v}"]=var_glob($v);
			}
		}
		
		*/
		
		//$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$decode=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $decode );
		//$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		$code=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $code );
		//$order_by=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $order_by);
		$order_by=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $order_by );
		$conn=$this->conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		if ($order_by!='') $query.=" from $value $where order by $order_by";
		else if(strtolower($this->attributes['VAR_TYPE'])=='clob' || $this->attributes['TYPE']=='file_doc') $query.=" from $value $where";
		else $query.=" from $value $where order by decode asc";
		$sql=new query($conn);
		//$sql->set_sql($query);
//echo "\n<!--$query-->";
		$sql->exec($query, $binded_vars);//fatto!!!
		$in=$this->session_vars;
		while ($sql->get_row()) {
			if ($decode!='') {
				$this->values[$sql->row['CODE']]=$sql->row['DECODE'];
				if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE']=='hidden') {
					global $in;
					$in[$this->attributes['VAR']]=$sql->row['DECODE'];
				}
			}
			else {
				global ${$this->attributes['BYVAR']};
				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			}
			//EDO experimental
			if($this->attributes['TYPE']=='file_doc' || $this->attributes['TYPE']=='file_cme')
			$this->id_bytd=$this->values[$sql->row['CODE']];
//			echo($this->id_bytd);
//			if($this->attributes['TYPE']=='file_doc') $this->id=${$this->attributes['BYVAR']}[$sql->row['CODE']];
		}

	}

	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param boolean $equery
	 */
	function make_close_html($equery=false, $eq_int=null){
		if (isset($this->attributes['VAR'])) $this->html='<tr id='.$this->attributes['VAR'].' style="display:">';
		$function_to_call='close_';
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		if($this->config_service['lang']=="en")
		{
			$value_changed_msg="Value is changed ";
			$old_sel_msg="old selection/value ";
		}
		else
		{
			$value_changed_msg="Il valore è cambiato ";
			$old_sel_msg="vecchia selezione/valore ";
		}
		if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
		$value=htmlentities($value,ENT_QUOTES,'UTF-8');
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
		$cols=$this->attributes['COLS']+0;
		if ($cols==0) $cols=1;
		
		if($this->attributes['LINK'] != "true"){
			$this->input_txt=preg_replace("/<a(.*?)<\/a>/","",$this->input_txt);
		}
		if(!$this->config_service['KEEP_ASTERISK'])$this->input_txt=str_replace("<font color=red>*</font>", "", $this->input_txt);
		if ($this->attributes['ONLY_AF']!='') $this->attributes['COLSPAN']="2";

		if ($equery){
			if (!isset($eq_int))
			$query="select STATO,EQUERY_INT from {$this->service}_eq where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and equery_int=(select max(equery_int) from {$this->service}_eq where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]})";
			else $query="select STATO,EQUERY_INT from {$this->service}_eq where 
			{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} 
			and equery_int=$eq_int";
			
			$sql=new query($this->conn);
			$sql->get_row($query);
			$stato=$sql->row['STATO'];
			$eq_int=$sql->row['EQUERY_INT'];

			if ($this->input_field!='' && $this->attributes['TYPE']!='hidden'){
				$testo_changed='';
				$img_eq='';

//				if($this->attributes['TYPE']=="file_doc" && $eq_int!="") {
//					$query="select count(*) as C from {$this->service}_eqfield where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and eq_int=$eq_int
//					and progr={$in['PROGR']} and esam={$in['ESAM']} and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and FIELD='{$this->id}'";
//					$sql=new query($this->conn);
//					$sql->get_row($query);
//					if($sql->row['C']>0) {
//						$img_eq_file_doc="<img src=\"images/eq_img.png\">";
//						$testo_changed="<br/><span style='color:red;font-weight:bold;'>$img_eq_file_doc Valore cambiato/aggiunto</span>";
//						//$str_testo_change="<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";
//					}
//
//				} 
//				else 
//				if((count($this->xml_form->old_values[$this->id])==0)) {
//					$testo_changed="";
//				} else 
//if($this->service=="CP_VI") {

//}
				if ($this->xml_form->old_values[$this->id]!=$this->xml_form->tb_vals[$this->id] && $stato==2){

					if($this->attributes['TYPE']=='file_doc' || $this->attributes['TYPE']=='file_cme') {
						if($this->attributes['TYPE']=='file_cme'){
							$prev=$this->CMELayer->queryPrevious($this->inputval[$this->attributes['VAR']]);	
							$this->xml_form->old_values_docs_nomi[$this->id]=$prev['NOME_FILE'];
						}
						if($this->xml_form->old_values_docs_nomi[$this->id]!="")
						$old_spec="<br /><a class=\"normal_link\" href=\"WCA/download.php?id={$this->xml_form->old_values[$this->id]}\"><span><img src=\"../images/word.gif\" alt=\"documento vecchio \" />{$this->xml_form->old_values_docs_nomi[$this->id]}</span></a>";
						else
						$old_spec="<h3 style=\"display:inline;text-decoration:underline;\">Valore aggiunto: Non era presente un allegato</h3>";
					} else				
					
					if (isset($this->xml_form->old_values['D_'.$this->id])){
						$old_spec=$this->xml_form->old_values['D_'.$this->id];
					}
					else $old_spec=$this->xml_form->old_values[$this->id];

					$img_eq="<img src=\"images/eq_img.png\">";
					$str_testo_agg="Valore aggiunto";
					$str_testo_change="<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";

//					if ($this->xml_form->old_values[$this->id]!=$this->xml_form->tb_vals[$this->id]  && $this->xml_form->old_values[$this->id]=="" && $this->attributes['TYPE']=='file_doc') {
//						$testo_changed="<br/><span style='color:blue;font-weight:bold'><br/>FILE AGGIUNTO</span>";
//					} else 
					if ($old_spec==''){
						$testo_changed="<br/><span style='color:blue;font-weight:bold'><br/>$str_testo_agg</span>";
					} else {
						$testo_changed="<br/><span style='color:red;font-weight:bold'><br/>$str_testo_change</span>";
					}
				} else if($this->xml_form->old_values[$this->id]==$this->xml_form->tb_vals[$this->id]) {
					$testo_changed="";
				}

//				$sql_query_docs="SELECT field FROM CP_VI_EQ E,CP_VI_EQFIELD F WHERE E.ID_PRAT = 188 AND E.EQUERY_INT=F.EQ_INT AND E.STATO=2";
//				$sql_docs=new query($this->conn);
//				$sql_docs->exec($sql_query_docs);
//				while($sql_docs->get_row()) {
//					$field=$sql_docs->row['FIELD'];
//					if($field==$this->attributes['VAR']) {
//						$old_sel_msg="Il documento Ã¨ stato revisionato";
//						$img_eq="<img width=\"24px\" height=\"24px\" src=\"images/eq_img.png\">";
//						$str_testo_change="<h3 style=\"display:inline;text-decoration:underline;\">$old_sel_msg:</h3>";
//						//ora c'Ã¨ lo stesso,lo deve prendere l'old
//						$old_doc=$this->input_field_rev;
//						$testo_changed="<br/><span style='color:red;font-weight:bold'><br/>$str_testo_change</span>$old_doc";
//					}
//				}

//			$sql=new query($this->conn);
//			$sql_query="select equery_int from {$this->service}_eq where stato in (0,2) and {$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}";
//			echo $sql_query;
//			if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
//print_R($this->xml_form);
			//check stato eq - solo se abilitato?
//			$sql_query="select * from {$this->service}_eq where
//				equery_int={$equery_int} and {$this->session_vars['PK_SERVICE']}={$_GET[$this->PK_SERVICE]}
//				";
//			echo $sql_query;
//			$sql->exec($sql_query);
//			while ($sql->get_row()){
//				$stato_eq=$sql->row['STATO'];
//			}
//			if($stato_eq==2) {

				//TROVARE PK SERVICE
//PERCHE' DUE CLOSE!!!
			$this->close_($value, $equery);
			$this->input_txt.=$testo_changed;

		    $this->input_txt="
		    <table width=\"100%\" border=0>
				<tr>
					<td valign=top align=left>
					$img_eq
					</td>
					<td valign=top align=right>
					{$this->input_txt}
					</td>
				</tr>
			</table>
		    ";

//			}

			}

		}

		if ((isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) && $this->attributes['HIDEVIS']!='yes') {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else {
				if ($this->input_txt!='') $this->input_txt.=":";
				$this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.$this->input_field.'</td>';
			}
		}
		else
		if ($this->attributes['TYPE']!='hidden') {
			if (
			(( $this->attributes['HIDEVIS']!='yes' && ($this->condition_passed || $this->attributes['HIDE']!='yes' )) || $this->attributes['SHOW_VIS']=='yes')
			){

				$this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
			}
			if ($this->attributes['HIDE_THIS']!='' && $inputval[$this->attributes['VAR']]=='') $this->html='';
		}
		if ($this->attributes['TYPE']=='hidden') $this->html='';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';
	}

	/**
	 * Gestisce il confirm sul campo
	 *
	 * @param String $value
	 */
	function open_confirm($value){
		$testo_js=make_js($value);
		$confirm_js="
			if (!confirm('$testo_js')) {
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;
			}
		";
	$vars=explode("|", $this->attributes['CONFIRM_COND_VAR']);
	$values=explode("|", $this->attributes['CONFIRM_COND_VALUE']);
	if (count($vars)>0){
		foreach($vars as $key => $val){
			if ($values[$key]=='null')  $values[$key]='';
			if ($this->attributes['CONFIRM_OP']=='and') $op="&&";
			if ($this->attributes['CONFIRM_OP']=='or') $op="||";
			$condition.="(value_of('{$val}')=='{$values[$key]}') {$op} ";
		}
		$condition=rtrim($condition, " $op ");
		$condition_check="
				if ($condition)
			";
		$confirm_js=$condition_check.$confirm_js;
	}
	$this->invia_js.=$confirm_js;
}

/**
 * Gestisce l'invocazione di js all'onchange del campo
 *
 * @param String $value
 */
function open_on_change($value){
	$this->salva_js.="
	$value
			";
	$this->invia_js.="
	$value
			";
}

function XML_PRINT_($values){
	$search = array ("'<script[^>]*?>.*?</script>'si",  // Rimozione del javascript
		"'<[\/\!]*?[^<>]*?>'si",           // Rimozione dei tag HTML
		"'([\r\n])[\s]+'",                 // Rimozione degli spazi bianchi
		"'&(quot|#34);'i",                 // Sostituzione delle entitï¿½ HTML
		"'&(amp|#38);'i",
		"'&(lt|#60);'i",
		"'&(gt|#62);'i",
		"'&(nbsp|#160);'i",
		"'&(iexcl|#161);'i",
		"'&(cent|#162);'i",
		"'&(pound|#163);'i",
		"'&(copy|#169);'i",
		"'&#(\d+);'e");                    // Valuta come codice PHP

	$replace = array ("",
		"",
		"\\1",
		"\"",
		"&",
		"<",
		">",
		" ",
	chr(161),
	chr(162),
	chr(163),
	chr(169),
		"chr(\\1)");

	$this->testo = preg_replace($search, $replace, $this->testo);
	$this->testo = str_replace("Ricerca nella banca dati...","", $this->testo);
	return $this->XML_OUTPUT($values);
}

function XML_OUTPUT($values){
	if (isset($this->attributes['VAR'])) $tag="VAR";
	else $tag="LABEL".$this->id;
	if (isset($this->attributes['VAR'])){
		$out="
		<$tag NAME=\"{$this->id}\">";
	}
	else {
		$out="
		<$tag>";
	}
	if ($this->testo!='') $out.= "
			<TESTO><![CDATA[{$this->testo}]]></TESTO>";
	if ($this->attributes['TB']!='no')
	$out.= "
			<VALORE><![CDATA[{$values[$this->id]}]]></VALORE>";
	$out.= "
		</$tag>
		";
	return $out;
}

function open_jcondition($val){
	$var_cond=$val;
	$this->condition_passed=false;
	$in=$this->session_vars;
	$inputval=$this->db_vars;
	$val_cond=$this->attributes['CONDITION_VALUE'];
	if ($this->attributes['HIDE']=='yes') {
		if (preg_match("/,/", $val_cond)){
			$controllo="
	        	valore=document.forms[0].".$var_cond.".value;
					$('#tr_".$this->id."').hide();

					";
			$vals=explode(",",$val_cond);
			foreach ($vals as $key => $value){
				if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
				else $value_to_control=$inputval[$var_cond];

				if ($value_to_control==$value) {
					$this->condition_passed=true;
				}

				$controllo.=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{

							$('#tr_".$this->id."').show();

						}
						";
			}
			$controllo.="
				if (document.getElementById('tr_".$this->id."') && document.getElementById('tr_".$this->id."').style.display=='none' && document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}
				";
		}
		else {
			$op ='!=';
			if (preg_match("/\!/", $val_cond)) {
				$val_cond=str_replace("!", "",$val_cond);
				$op='==';
			}
			if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
			else $value_to_control=$inputval[$var_cond];
			if ($op=='==') $this->condition_passed=($value_to_control!=$val_cond);
			else $this->condition_passed=($value_to_control==$val_cond);

			$controllo.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
			$controllo.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else {
							if (document.forms[0].".$this->id."[0] && !document.forms[0].".$this->id.".selectedIndex){
								           radioclear('{$this->id}');
							}
						else document.forms[0].".$this->id.".value='';
						}
					}

					$('#tr_".$this->id."').hide();
					}
					else {
					$('#tr_".$this->id."').show();
					}
					";
		}
	}
	else {

		if ($this->attributes['HIDE_THIS']=='yes') {

			if (preg_match("/,/", $val_cond)){
				$controllo.="
	        valore=document.forms[0].".$this->id.".value;
				document.forms[0].".$this->id.".value='';
					$('#cell_".$this->id."').hide();
					$('#cell_input".$this->id."').hide();
					";
				$vals=explode(",",$val_cond);
				//$this->condition_passed=false;
				foreach ($vals as $key => $value){
					if ($in[$var_cond]==$value) $this->condition_passed=true;
					$controllo.=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
							$('#cell_".$this->id."').show();
							$('#cell_input".$this->id."').show();
						    document.forms[0].".$this->id.".value=valore;

						}
							";
				}
			}
			else {

				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
				else $this->condition_passed=($in[$var_cond]==$val_cond);
				//echo "<hr>$op - $var_cond - $val_cond - {$this->attributes['VAR']}<hr>";
				$controllo.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
				$controllo.="
					if (document.forms[0].".$this->id.")
						document.forms[0].".$this->id.".value='';
					  	$('#cell_".$this->id."').hide();
					  	$('#cell_input".$this->id."').hide();
					}
					else{
						$('#cell_".$this->id."').show();
						$('#cell_input".$this->id."').show();
					}
					";
			}
		}
		else {
			if (preg_match("/,/", $val_cond)){
				$controllo.="
	        valore=document.forms[0].".$this->id.".value;
	        document.forms[0].".$this->id.".value='';

						";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value){
					if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
					else $value_to_control=$inputval[$var_cond];
					if ($value_to_control==$value) {
						$this->condition_passed=true;
					}
					$controllo.=" \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			document.forms[0].".$this->id.".value=valore;
						}
						";

				}
			}else{
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				foreach ($this->xml_form->fields as $key => $val){
					if ($val['TYPE']=='checkbox') {
						foreach ($val['VALUE'] as $key => $val){
							//echo "<li>$key</li>";
							if (!isset($in[$key])) $in[$key]='0';
						}
					}
				}
				if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
				else $this->condition_passed=($in[$var_cond]==$val_cond);

				$controllo.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
				$controllo.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}
					 $('#tr_".$this->id."').hide();
					}
					else {
				  		$('#tr_".$this->id."').show();
					}
					";
			}
		}
	}
	$this->html="<tr id='tr_".$this->id."' style=\"display:\">".$this->html."</tr>";
	$this->script="
				var controllo=function(){
				{$controllo}
				}
				controllo();
				$(\"[name='{$this->attributes['CONDITION']}']\").change(controllo);
				";
	}


    function audit_trail_txt(){
        if(class_exists("audit_trail_core")){
            $audit_trail =  new audit_trail_core($this->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);          
            return $audit_trail->audit_trail_txt($this->session_vars);
        }
        else{
            return '';
        }
    }

	/**
	 * Enter description here...
	 *
	 * @param object $object
	 * @return boolean
	 */
	function equals($object){
		unset($this->attributes['BYTB']);
		$this->insert_stmt();
		$object->insert_stmt();		
		foreach ($this->field_stmt as $key => $currField){
			if($this->field_stmt[$key]!=$object->field_stmt[$key] || $this->db_vars[$this->field_stmt[$key]]!=$object->db_vars[$object->field_stmt[$key]]) {
				return false;
			}
		}
		return true;
	}
	/**
	 * Crea campo input per la risoluzione delle discrepanze
	 *
	 * @return string
	 */
	function decision_form($index){
		unset($this->attributes['BYTB']);
		unset($this->session_vars);
		unset($this->db_vars);
		$this->make_open_html();
		$this->input_field=str_replace("document.forms[0]","document.forms[{$index}]",$this->input_field);
		$this->input_field=preg_replace("/radioclear\(([^\)]*)\)/","radioclear(\\1,{$index})",$this->input_field);
		$this->input_field=preg_replace("/_cal_anchor/","_cal_anchor_{$index})",$this->input_field);
		return $this->input_field;
	}
	/**
	 * Crea campo input per la risoluzione delle discrepanze
	 *
	 * @return string
	 */
	function comparison_form($index){
		unset($this->attributes['BYTB']);
		$this->attributes['SHOW_SELECTED']='yes';
		$this->make_close_html();
		//$matches=preg_match_all('/<!--dde_start\[(.[^]]*)]\|(.[^|]*)\|-->/',$this->input_field,$match);
		$this->input_field=preg_replace("/<!--dde_start\[(.[^]]*)]\|(.[^|]*)\|-->/","<span class='compareElement' onclick='$(\"[name=\\1]\").val(\"\\2\");'>",$this->input_field);
		$this->input_field=preg_replace("/<!--dde_end-->/","</span>",$this->input_field);
		//$this->input_field=preg_replace("/<!--dde_complete-->/",'<a href="#" onclick="$(this).closest(\'td\').find(\'.compareElement\').click();return false; " ><img alt="Select value" src="images/icon_right2_18x18.png" width="15" /></a>',$this->input_field);
		$this->input_field.=' <a href="#" onclick="$(this).closest(\'td\').find(\'.compareElement\').click();return false; " ><img alt="Select value" src="images/icon_right_18x18.png" width="15" /></a>';
		
		return $this->input_field;
	}
	
	/**
	 * Prepara le informazioni sul valore per il log del DDE
	 *
	 * @return array
	 */
	function getDDELogInfo(){
		if(count($this->value_stmt)==0)$this->insert_stmt();
		$val['VALDE']=$this->value_stmt[0];
		$val['D_VALDE']=$this->value_stmt[1];
		return $val;
	}
	
}


?>
