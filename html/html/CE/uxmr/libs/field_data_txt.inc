<?
include_once "field.inc";
/**
 * Classe per la gestione dei campi di tipo data
 *
 * @package Fields
 */
class field_data_txt extends field {
	
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	 
	 
	 
	 
	function open_($value) {
		$in = $this->session_vars;
		//print_r($in);
		$inputval = $this->db_vars;
		
		
		$mm= substr($value,2,2);
		
		$fechin=substr($inputval[$this->attributes ['VAR']],2,2);
		
		

	
	
	$mes = Array ('Jan','Feb','Mar','Apr','May','jun','agu','Sep','oct','nov','dec');
	
	// echo "MES= ".$mes[$fechin-1]."<hr>";
	
	
	
		
		if(is_numeric($in [$this->attributes ['VAR'] . 'M'])){
			
			
			
			
		if ($in [$this->attributes ['VAR'] . 'D'] != '' && $in [$this->attributes ['VAR'] . 'M'] != '' && $in [$this->attributes ['VAR'] . 'Y'] != '') {
			if ($in [$this->attributes ['VAR'] . 'D'] != '') {
				$in [$this->attributes ['VAR'] . 'D'] = '0' . $in [$this->attributes ['VAR'] . 'D'];
				$in [$this->attributes ['VAR'] . 'D'] = substr ( $in [$this->attributes ['VAR'] . 'D'], strlen ( $in [$this->attributes ['VAR'] . 'D'] ) - 2, 2 );
			}
			
			
			if ($in [$this->attributes ['VAR'] . 'M'] != '') {
				$in [$this->attributes ['VAR'] . 'M'] = '0' . $in [$this->attributes ['VAR'] . 'M'];
				$in [$this->attributes ['VAR'] . 'M'] = substr ( $in [$this->attributes ['VAR'] . 'M'], strlen ( $in [$this->attributes ['VAR'] . 'M'] ) - 2, 2 );
			}
			
			$value = $in [$this->attributes ['VAR']] = $in [$this->attributes ['VAR'] . 'D'] . $in [$this->attributes ['VAR'] . 'M'] . $in [$this->attributes ['VAR'] . 'Y'];
			$in [$this->attributes ['VAR'] . 'D'] += 0;
			$in [$this->attributes ['VAR'] . 'M'] += 0;
		}
	}
		$txt = $this->testo;
		$keys = array_keys ( $this->values );
		$value_init = $keys [0];
		if ($value_init == 'sysdate')
			$value = date ( "dmY" );
		if ($value == '')
			$value = $value_init;
	
	//	echo $value."<hr>";
		
		if (preg_match ( "/\//", $value )) {
			$dd = substr ( $value, 0, 2 );
			$mm = substr ( $value, 3, 2 );
			$yyyy = substr ( $value, 6, 4 );
	
		} else {
			$dd = substr ( $value, 0, 2 );
			$mm = substr ( $value, 2, 2 );
			$yyyy = substr ( $value, 4, 4 );
		}
		//	echo 'mes' .$mm.'<hr>';
	//		echo 'dia' .$dd.'<hr>';
	//		print ('a?o'.$yyyy).'<hr>';
		$this->validata = true;
		if (isset ( $in ['salva'] ) and $this->attributes ['SAVE'] == 'obbligatorio') {
			if (! checkdate ( $mm, $dd, $yyyy )) {
				$txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
				$this->validata = false;
			}
		}
		if (isset ( $in ['invia'] ) and $this->attributes ['SEND'] == 'obbligatorio' && $this->condition_passed) {
			
			if (! checkdate ( $mm, $dd, $yyyy )) {
				//echo "<hr>Campo non validato {$this->id}<hr>";
				$txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
				$this->validata = false;
			}
		}
		$check_onblur = '';
		if ($this->attributes ['ONBLUR'] != '') {
			$check_fn = 'onchange="' . $this->attributes ['ONBLUR'] . '"';
		}
		if ($this->attributes ['CHECK_ONBLUR'] != '') {
			$check_onblur = 'onblur="el=f.elements;specifiche=\'A=ON&L=0&F=0\';c1=\'<<fd00###' . $this->attributes ['VAR'] . '###Data errata>>\';rc=contr(c1,specifiche);if (rc) {return false}"';
		}
		$rc = $this->attributes ['VAR'] . 'RC';
		$this->input_txt = $txt;
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes') {
			$html_parser = new HTML_Parser ( );
			$html_parser->setAttribute ( "type", "hidden" );
			$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
			$html_parser->setContent ( $value );
			$html_parser->setType ( "INPUT" );
			$this->input_field = '***' . $html_parser->print_ ();
			//$this->input_field='***<input type="hidden" name="'.$this->attributes['VAR'].'"  value="'.$value.'"/>';
		} else {
			if ($this->attributes['NDAY']!='yes')
			{

				$input_html='<input type="text" '.$disabled.' name="'.$this->attributes['VAR'].'D" value="'.$dd.'" size=2 maxlength=2 '.$check_fn.'/>&nbsp;';
			}
			else
			{
				$this->check_js.="
				if (f.{$this->attributes['VAR']}M.value=='' && f.{$this->attributes['VAR']}Y.value==''){
					f.{$this->attributes['VAR']}D.value='';
				}
				else f.{$this->attributes['VAR']}D.value='15';
			";
				$input_html='<input '.$disabled.' type="hidden" name="'.$this->attributes['VAR'].'D" value="15">';
			}
			
			
		
	//		echo "variable value=".$value."<hr>"aca puse $mm por $mes;
			
			$input_html.='<input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'M" value="'.$mes[$fechin-1].'" size=3 maxlength=3 '.$check_fn.'/>
                     <input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'Y" value="'.$yyyy.'" size=4 maxlength=4 '.$check_onblur.$check_fn.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value="'.$dd.$mm.$yyyy.'"/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" />';
                     
                     
     //  echo   $input_html."<hr>";  
    //   die();          
                     
			if ($inputval[$rc]=='CONTIN')
			{
				$input_html='<input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'D" value="" size=2 maxlength=2 />
                     <input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'M" value="" size=3 maxlength=3 />
                     <input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'Y" value="CONT" size=4 maxlength=4 '.$check_onblur.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value=""/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" value="CONTIN"/>';
			}
			if ($inputval[$rc]=='NKNKNK'||$inputval[$rc]=='NANANA')
			{
				$input_html='<input type="text" name="'.$this->attributes['VAR'].'D" value="" size=2 maxlength=2 />
                     <input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'M" value="" size=3 maxlength=3 />
                     <input '.$disabled.' type="text" name="'.$this->attributes['VAR'].'Y" value="'.substr($inputval[$rc],0,2).'" size=4 maxlength=4 '.$check_onblur.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value=""/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" value="'.$inputval[$rc].'"/>';
			}
			if ($this->attributes['DEF']!='') $input_html.=$this->attributes['DEF'];
			$this->input_field=$input_html;
			
			if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
				$ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
			else if (strtolower ( $this->config_service ['lang'] ) == 'en')
				$ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '(dd mm yyyy)</td>';
			else
				$ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '(gg mm aaaa)</td>';
		}
		$this->session_vars = $in;
	}
	
	
	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
		$inputval = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$txt = $this->testo;
	//	echo "<hr>value= ".$value."<hr>";
		$dd = substr ( $value, 0, 2 );
		$mm = substr ( $value, 2, 2 );
		$yyyy = substr ( $value, 4, 4 );
		
		#aca comienzo a hacer los cambios
	//echo "<hr>date = ".$dd."-".$mm."-".$yyyy."<hr>";
		
		
		
		
		switch ($mm){ 
	  	
	  		case 1:$mes='jan'; break;
	  		case 2:$mes='Feb'; break;
	  		case 3:$mes='Mar'; break;
	  		case 4:$mes='Apr'; break;
	  		case 5:$mes='May'; break;
	  		case 6:$mes='jun'; break;
	  		case 7:$mes='Jul'; break;
	  		case 8:$mes='Agu'; break;
	  		case 9:$mes='Sep'; break;
	  		case 10:$mes='Oct'; break;
	  		case 11:$mes='Nov'; break;
	  		case 12:$mes='Dec'; break;
	  		
	  
	}
//	echo "Mes= ".$mes."<hr>";	
	$mm=$mes;	
		
		
		#hasta aca es la parte nueva del data_txt
		if ($this->attributes ['NDAY'] != 'yes') {
			$input_html = $dd . ' ' . $mm . ' ' . $yyyy;
			if (strtolower ( $this->config_service ['lang'] ) == 'en')
				$sstr = '(dd mm yyyy)';
			else
				$sstr = '(gg mm aaaa)';
		} else {
			$input_html = $mm . ' ' . $yyyy;
			if (strtolower ( $this->config_service ['lang'] ) == 'en')
				$sstr = '(mm yyyy)';
			else
				$sstr = '(mm aaaa)';
		}
		$rc = $this->attributes ['VAR'] . 'RC';
		if ($this->xml_form->tb_vals [$rc] == 'CONTIN') {
			$input_html = 'CONT';
			$sstr = ' ';
		}
		if ($this->xml_form->tb_vals [$rc] == 'NKNKNK' || $this->xml_form->tb_vals [$rc] == 'NANANA') {
			$input_html = substr ( $this->xml_form->tb_vals [$rc], 0, 2 );
			$sstr = ' ';
		}
		if ($this->xml_form->tb_vals[$rc]=='NKNKNK'||$this->xml_form->tb_vals[$rc]=='NANANA')
			{
			 $input_html=substr($this->xml_form->tb_vals[$rc],0,2);
			 $sstr=' ';
			}
		if ($this->session_vars ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes')
		{
			$input_html = '***';
			$sstr = '';
		} else
			$input_html = $input_html;
		
		$this->input_txt = $txt;
		$this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $sstr;
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $sstr . '</td></tr>';
		#return $ret;
	}
	
	/**
	 * Costruisce un array con i campi ed i valori dei campi da salvare in DB
	 *
	 * @param boolean $insert
	 */
	function insert_stmt($insert = true) {
		
		
		
		
		$in = $this->session_vars;
		$conn = $this->conn;
		if (isset ( $this->attributes ['FORMAT'] ))
			$format = $this->attributes ['FORMAT'];
		else
			$format = 'DDMMYYYY';
		$sql = new query ( $conn );
		$sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = '{$format}'" );
		$sql->ins_upd ();//non richiede binding
		if (! $insert) {
			$this->field_stmt [0] = "{$this->attributes['VAR']}";
			$this->field_stmt [1] = "{$this->attributes['VAR']}RC";
			return;
		}
		if ($this->attributes ['TB'] != 'no') {
			$this->field_stmt [0] = "{$this->attributes['VAR']}";
			$this->field_stmt [1] = "{$this->attributes['VAR']}RC";
			$this->value_stmt [0] = "{$in[$this->attributes['VAR']]}";
			$this->value_stmt [1] = $in [$this->attributes ['VAR'] . 'RC'];
		}
		return;
	}
	
	/**
	 * Costruisce un array con i campi da confrontare in DB (per allineare struttura DB a XML)
	 *
	 * @return array
	 */
	function allinea_db() {
		if ($this->attributes ['TB'] != 'no') {
			$ret [0] = "{$this->attributes['VAR']} DATE";
			$ret [1] = "{$this->attributes['VAR']}RC VARCHAR2(8)";
			return $ret;
		} else
			return;
	}
	
	/**
	 * Gestisce i controlli lato server/client del campo condizionato
	 *
	 * @param String $val
	 */
	function open_condition($val) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		$var_cond = $val;
		$this->condition_passed = false;
		$val_cond = $this->attributes ['CONDITION_VALUE'];
		if ($this->attributes ['HIDE'] == 'yes') {
			if (preg_match ( "/,/", $val_cond )) {
				$this->check_js .= "
	if (document.getElementById('tr_" . $this->id . "'))
	document.getElementById('tr_" . $this->id . "').style.display='none';
	";
				$vals = explode ( ",", $val_cond );
				foreach ( $vals as $key => $value ) {
					if (isset ( $in ['INVIOCO'] ))
						$value_to_control = $in [$var_cond];
					else
						$value_to_control = $inputval [$var_cond];
					
					if ($value_to_control == $value) {
						$this->condition_passed = true;
					}
					$this->check_js .= " \n
		value=value_of('$var_cond', '0');
		if (value=='$value')
		{
		if (document.forms[0]." . $this->id . "D.value!='') {$this->id}D_val=document.forms[0]." . $this->id . "D.value;
		if (document.forms[0]." . $this->id . "M.value!='') {$this->id}M_val=document.forms[0]." . $this->id . "M.value;
		if (document.forms[0]." . $this->id . "Y.value!='') {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;
		if (document.getElementById('tr_" . $this->id . "'))
		document.getElementById('tr_" . $this->id . "').style.display='';
		}
		";
				}
			} else {
				$op = '!=';
				if (preg_match ( "/\!/", $val_cond )) {
					$val_cond = str_replace ( "!", "", $val_cond );
					$op = '==';
				}
				if (isset ( $in ['INVIOCO'] ))
					$value_to_control = $in [$var_cond];
				else
					$value_to_control = $inputval [$var_cond];
				if ($op == '==')
					$this->condition_passed = ($value_to_control != $val_cond);
				else
					$this->condition_passed = ($value_to_control == $val_cond);
				$this->check_js = " \n
	value=value_of('$var_cond', '0');
	if (document.forms[0]." . $this->id . "D.value!='') {$this->id}D_val=document.forms[0]." . $this->id . "D.value;
	if (document.forms[0]." . $this->id . "M.value!='') {$this->id}M_val=document.forms[0]." . $this->id . "M.value;
	if (document.forms[0]." . $this->id . "Y.value!='') {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;
	if (value{$op}'$val_cond')
	{

	document.forms[0]." . $this->id . "D.value='';
	document.forms[0]." . $this->id . "M.value='';
	document.forms[0]." . $this->id . "Y.value='';
	";
				//foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->id."[".($key-1)."].checked=false;";
				$this->check_js .= " \n
	if (document.getElementById('tr_" . $this->id . "'))
	document.getElementById('tr_" . $this->id . "').style.display='none';
	}
	else{
	if (typeof({$this->id}D_val)!= \"undefined\" && {$this->id}D_val) document.forms[0]." . $this->id . "D.value={$this->id}D_val;
	if (typeof({$this->id}M_val)!= \"undefined\" && {$this->id}M_val) document.forms[0]." . $this->id . "M.value={$this->id}M_val;
	if (typeof({$this->id}Y_val)!= \"undefined\" && {$this->id}Y_val) document.forms[0]." . $this->id . "Y.value={$this->id}Y_val;
	if (document.getElementById('tr_" . $this->id . "'))
	document.getElementById('tr_" . $this->id . "').style.display='';
	}";
			}
		
		} else {
			$op = '!=';
			if (preg_match ( "/\!/", $val_cond )) {
				$val_cond = str_replace ( "!", "", $val_cond );
				$op = '==';
			}
			//echo "<li>{$in[$var_cond]} - $var_cond - $val_cond</li>";
			/*foreach ($this->xml_form->fields as $key => $val){
			if ($val['TYPE']=='checkbox') {
			foreach ($val['VALUE'] as $key => $val){
			//echo "<li>$key</li>";
			if (!isset($in[$key])) $in[$key]='0';
			}
			}
			}*/
			//echo "<li>$var_cond - {$in[$var_cond]} - {$val_cond}</li>";
			if ($op == '==')
				$this->condition_passed = ($in [$var_cond] != $val_cond);
			else
				$this->condition_passed = ($in [$var_cond] == $val_cond);
			
			$this->check_js .= " \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
			$this->check_js .= "
					if (document.forms[0]." . $this->id . "D && document.forms[0]." . $this->id . "M && document.forms[0]." . $this->id . "Y)
						{

						 	document.forms[0]." . $this->id . "D.value='';
							document.forms[0]." . $this->id . "M.value='';
							document.forms[0]." . $this->id . "Y.value='';
						}


					}
					else{
	if (document.getElementById('tr_" . $this->id . "'))
	document.getElementById('tr_" . $this->id . "').style.display='';}
	";
		}
		/*$this->check_js.="
}
if (document.getElementById('".$this->id."'))
document.getElementById('tr_".$this->id."').style.display='';";*/
		
		$this->html = "<tr id='tr_" . $this->id . "' style=\"display:none\">" . $this->html . "</tr>";
//	print ($this->check_js);
	}
	
	/**
	 * Gestisce la compilazione automatica del campo
	 *
	 * @param String $value
	 */
	function open_compila($value) {
		#echo "<hr>$value";
		$this->check_js .= "
					if (document.forms[0]." . $this->attributes ['COMPILA_CONDITION_VAR'] . ".value==" . $this->attributes ['COMPILA_CONDITION_VALUE'] . "){
						compila_value=document.forms[0]." . $this->attributes ['COMPILA'] . ".value;
						if (compila_value>0){
							document.forms[0]." . $this->id . "D.value=compila_value.substr(0,2);
							document.forms[0]." . $this->id . "M.value=compila_value.substr(2,2);
							document.forms[0]." . $this->id . "Y.value=compila_value.substr(4,4);
							document.forms[0]." . $this->id . "D.disabled=true;
							document.forms[0]." . $this->id . "M.disabled=true;
							document.forms[0]." . $this->id . "Y.disabled=true;
							document.forms[0]." . $this->id . ".value=compila_value;
						}
					}
			";
	}
	
	/**
	 * Controlli sul valore della data (maggiore o uguale)
	 *
	 * @param String $value
	 */
	function open_max_eq($value) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		if (preg_match ( "/,/", $value )) {
			$values = explode ( ",", $value );
			foreach ( $values as $key => $value ) {
				if (preg_match ( "/\[/", $value )) {
					$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
					$value = $inputval [$value_field];
					foreach ( $this->xml_form->fields as $key => $val ) {
						if ($value_field == $val ['VAR']) {
							$i = $key;
						}
					}
					$cond_obj = new field ( $this->xml_form, $i );
					$testo_var_condizione = $cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in [$value_field] != '')
						$value = $in [$value_field];
				}
				if ($value == 'today' || $value == 'sysdate')
					$value = date ( "dmY", time () );
				$value = str_replace ( "/", "", $value );
				$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
				$data = $inputval [$this->attributes ['VAR']];
				if ($in [$this->attributes ['VAR']] != '')
					$data = $in [$this->attributes ['VAR']];
				$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
				$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
				$rc = $this->attributes ['VAR'] . 'RC';
				$vrc = $inputval [$rc];
				if ($in [$rc] != '')
					$vrc = $in [$rc];
				if ($data <= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
					$this->validata = false;
					if ($data != '')
						$this->input_txt .= "<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
				}
				$giorno = substr ( $data, 6, 2 ) + 0;
				$mese = substr ( $data, 4, 2 ) - 1;
				$anno = substr ( $data, 0, 4 ) + 0;
				$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value == '' && $value_field != '') {
					$this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";
				
				} else {
					$vgiorno = substr ( $value, 6, 2 ) + 0;
					$vmese = substr ( $value, 4, 2 ) - 1;
					$vanno = substr ( $value, 0, 4 ) + 0;
					
					$this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
				}
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				elseif ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
				$testo = make_js ( $this->testo );
				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
				
				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}				
				//traduzione del messaggio di alert in inglese
				if ($this->config_service ['lang'] == "en")
					$alert_msg = "{$testo} must be after $value_txt";
				else
					$alert_msg = "La {$testo} deve essere successiva $value_txt";
				
				$this->controlli .= "

						if (data<=value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
							}
						}
					";
			}
		} else {
			if (preg_match ( "/\[/", $value )) {
				$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
				$value = $inputval [$value_field];
				foreach ( $this->xml_form->fields as $key => $val ) {
					if ($value_field == $val ['VAR']) {
						$i = $key;
					}
				}
				$cond_obj = new field ( $this->xml_form, $i );
				$testo_var_condizione = $cond_obj->testo;
				if ($in [$value_field] != '')
					$value = $in [$value_field];
			}
			if ($value == 'today' || $value == 'sysdate')
				$value = date ( "dmY", time () );
			$value = str_replace ( "/", "", $value );
			$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
			$data = $inputval [$this->attributes ['VAR']];
			if ($in [$this->attributes ['VAR']] != '')
				$data = $in [$this->attributes ['VAR']];
			$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
			$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			elseif ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$rc = $this->attributes ['VAR'] . 'RC';
			$vrc = $inputval [$rc];
			if ($in [$rc] != '')
				$vrc = $in [$rc];
			if ($data <= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
				$this->validata = false;
				if ($data != '')
					$this->input_txt .= "<br><font color=red>

				$data - $value
				La Data deve essere successiva a $value_txt&nbsp;";
			}
			$giorno = substr ( $data, 6, 2 ) + 0;
			$mese = substr ( $data, 4, 2 ) - 1;
			$anno = substr ( $data, 0, 4 ) + 0;
			$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field != '') {
				$this->controlli .= "
				{$value_field}_=document.forms[0]." . $value_field . ".value;
				{$value_field}_={$value_field}_.replace('/','');
				{$value_field}_={$value_field}_.replace('/','');
					vgiorno={$value_field}_.substr(0,2);
					vmese={$value_field}_.substr(2,2)-1;
					vanno={$value_field}_.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
					";
			
			} else {
				$vgiorno = substr ( $value, 6, 2 ) + 0;
				$vmese = substr ( $value, 4, 2 ) - 1;
				$vanno = substr ( $value, 0, 4 ) + 0;
				
				$this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
			}
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$value_txt = make_js ( $value_txt );
			$testo = make_js ( $this->testo );

			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
			if($this->attributes['LABEL_JS'] != ""){
				$testo=$this->attributes['LABEL_JS'];
			}

			if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
			}			
			//traduzione del messaggio di alert in inglese
			if ($this->config_service ['lang'] == "en")
				$alert_msg = "{$testo} must be after $value_txt";
			else
				$alert_msg = "La {$testo} deve essere successiva $value_txt";
			
			$this->controlli .= "
						if (data<=value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
						}

					}
				";
		}
	}
	
	/**
	 * Controlli sul valore della data (maggiore)
	 *
	 * @param String $value
	 */
	function open_max($value) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		if (preg_match ( "/,/", $value )) {
			$values = explode ( ",", $value );
			foreach ( $values as $key => $value ) {
				if (preg_match ( "/\[/", $value )) {
					$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
					$value = $inputval [$value_field];
					foreach ( $this->xml_form->fields as $key => $val ) {
						if ($value_field == $val ['VAR']) {
							$i = $key;
						}
					}
					$cond_obj = new field ( $this->xml_form, $i );
					$testo_var_condizione = $cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in [$value_field] != '')
						$value = $in [$value_field];
				}
				if ($value == 'today' || $value == 'sysdate')
					$value = date ( "dmY", time () );
				$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
				$data = $inputval [$this->attributes ['VAR']];
				if ($in [$this->attributes ['VAR']] != '')
					$data = $in [$this->attributes ['VAR']];
				$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
				$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
				$rc = $this->attributes ['VAR'] . 'RC';
				$vrc = $inputval [$rc];
				if ($in [$rc] != '')
					$vrc = $in [$rc];
				if ($data < $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
					$this->validata = false;
					if ($data != '')
						$this->input_txt .= "<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
				}
				$giorno = substr ( $data, 6, 2 ) + 0;
				$mese = substr ( $data, 4, 2 ) - 1;
				$anno = substr ( $data, 0, 4 ) + 0;
				$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value == '' && $value_field != '') {
					$this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";
				
				} else {
					$vgiorno = substr ( $value, 6, 2 ) + 0;
					$vmese = substr ( $value, 4, 2 ) - 1;
					$vanno = substr ( $value, 0, 4 ) + 0;
					
					$this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
				}
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
				$testo = make_js ( $this->testo );
				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
				
				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}				
				//traduzione del messaggio di alert in inglese
				if ($this->config_service ['lang'] == "en")
					$alert_msg = "{$testo} must be after $value_txt";
				else
					$alert_msg = "La {$testo} deve essere successiva $value_txt";
				
				$this->controlli .= "

						if (data<value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
							}
						}
					";
			}
		} else {
			if (preg_match ( "/\[/", $value )) {
				$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
				$value = $inputval [$value_field];
				foreach ( $this->xml_form->fields as $key => $val ) {
					if ($value_field == $val ['VAR']) {
						$i = $key;
					}
				}
				$cond_obj = new field ( $this->xml_form, $i );
				$testo_var_condizione = $cond_obj->testo;
				if ($in [$value_field] != '')
					$value = $in [$value_field];
			}
			if ($value == 'today' || $value == 'sysdate')
				$value = date ( "dmY", time () );
			$value = str_replace ( "/", "", $value );
			$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
			$data = $inputval [$this->attributes ['VAR']];
			if ($in [$this->attributes ['VAR']] != '')
				$data = $in [$this->attributes ['VAR']];
			$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
			$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$rc = $this->attributes ['VAR'] . 'RC';
			$vrc = $inputval [$rc];
			if ($in [$rc] != '')
				$vrc = $in [$rc];
			if ($data < $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
				$this->validata = false;
				if ($data != '')
					$this->input_txt .= "<br><font color=red>

				$data - $value
				La Data deve essere successiva a $value_txt&nbsp;";
			}
			$giorno = substr ( $data, 6, 2 ) + 0;
			$mese = substr ( $data, 4, 2 ) - 1;
			$anno = substr ( $data, 0, 4 ) + 0;
			$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field != '') {
				$this->controlli .= "
				{$value_field}_=document.forms[0]." . $value_field . ".value;
				{$value_field}_={$value_field}_.replace('/','');
				{$value_field}_={$value_field}_.replace('/','');
					vgiorno={$value_field}_.substr(0,2);
					vmese={$value_field}_.substr(2,2)-1;
					vanno={$value_field}_.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
					";
			
			} else {
				$vgiorno = substr ( $value, 6, 2 ) + 0;
				$vmese = substr ( $value, 4, 2 ) - 1;
				$vanno = substr ( $value, 0, 4 ) + 0;
				
				$this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
			}
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$value_txt = make_js ( $value_txt );
			$testo = make_js ( $this->testo );
			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
				
				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}			
			//traduzione del messaggio di alert in inglese
			if ($this->config_service ['lang'] == "en")
				$alert_msg = "{$testo} must be after $value_txt";
			else
				$alert_msg = "La {$testo} deve essere successiva $value_txt";
			
			$this->controlli .= "
						if (data<value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
						}

					}
				";
		}
	}

/**
 * Controllo sul valore con condizione
 *
 * @param String $value
 */
function open_max_con($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		if (preg_match("/,/",$value)){
			$values=explode(",", $value);
			foreach ($values as $key => $value){
				if (preg_match("/\[/", $value)){
					$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
					$value=$inputval[$value_field];
					foreach ($this->xml_form->fields as $key=>$val){
						if ($value_field==$val['VAR']) {
							$i=$key;
						}
					}
					$cond_obj=new field($this->xml_form, $i);
					$testo_var_condizione=$cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in[$value_field]!='') $value=$in[$value_field];
				}
				if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
				$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
				$data=$inputval[$this->attributes['VAR']];
				if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
				$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
				$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$rc=$this->attributes['VAR'].'RC';
				$vrc=$inputval[$rc];
				if ($in[$rc]!='') $vrc=$in[$rc];
				/*if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
					//$this->validata=false;
					if ($data!='')
					$this->input_txt.="<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
				}*/
				$giorno=substr($data,6,2)+0;
				$mese=substr($data,4,2)-1;
				$anno=substr($data,0,4)+0;
				$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
						mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
						anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value=='' && $value_field!='')
				{
					$this->controlli.="
					 	vgiorno=document.forms[0].".$value_field.".value.substr(0,2);
						vmese=document.forms[0].".$value_field.".value.substr(2,2)-1;
						vanno=document.forms[0].".$value_field.".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

				}
				else {
					$vgiorno=substr($value,6,2)+0;
					$vmese=substr($value,4,2)-1;
					$vanno=substr($value,0,4)+0;

					$this->controlli.="
						value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
						";
				}
				if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
				else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
				if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
				else if($this->config_service['lang']=="en") $value_txt=$value_txt;
				$testo=make_js($this->testo);

				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
	
				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}
	
				//traduzione del messaggio di alert in inglese
				if($this->config_service['lang']=="en")
				$alert_msg="Please confirm {$testo} is before $value_txt";
				else
				$alert_msg="La {$testo} deve essere successiva $value_txt";

				$this->controlli.="

						if (data<value && value) {
								if(confirm('{$alert_msg}\\nOk to confirm, Cancel to modify.')){
								}else{
									document.forms[0].".$this->attributes['VAR']."Y.focus();
									return false;
								}
							}
						}
					";
			}
		}
		else {
			if (preg_match("/\[/", $value)){
				$value_field=preg_replace("/\[(.*?)\]/", "$1", $value);
				$value=$inputval[$value_field];
				foreach ($this->xml_form->fields as $key=>$val){
					if ($value_field==$val['VAR']) {
						$i=$key;
					}
				}
				$cond_obj=new field($this->xml_form, $i);
				$testo_var_condizione=$cond_obj->testo;
				if ($in[$value_field]!='') $value=$in[$value_field];
			}
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
			$value=str_replace("/", "", $value);
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en") $value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$rc=$this->attributes['VAR'].'RC';
			$vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			/*if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
				//$this->validata=false;
				if ($data!='')
				$this->input_txt.="<br><font color=red>

				$data - $value
				La Data deve essere successiva a $value_txt&nbsp;";
			}*/
			$giorno=substr($data,6,2)+0;
			$mese=substr($data,4,2)-1;
			$anno=substr($data,0,4)+0;
			$this->controlli.=" if (document.forms[0].".$this->attributes['VAR']."D && document.forms[0].".$this->attributes['VAR']."D.value!='' && document.forms[0].".$this->attributes['VAR']."M.value!='' && document.forms[0].".$this->attributes['VAR']."Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0].".$this->attributes['VAR'].".value.substr(0,2);
					mese=document.forms[0].".$this->attributes['VAR'].".value.substr(2,2)-1;
					anno=document.forms[0].".$this->attributes['VAR'].".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value_field!='')
			{
				$this->controlli.="
				{$value_field}_=document.forms[0].".$value_field.".value;
				{$value_field}_={$value_field}_.replace('/','');
				{$value_field}_={$value_field}_.replace('/','');
					vgiorno={$value_field}_.substr(0,2);
					vmese={$value_field}_.substr(2,2)-1;
					vanno={$value_field}_.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
					";

			}
			else {
				$vgiorno=substr($value,6,2)+0;
				$vmese=substr($value,4,2)-1;
				$vanno=substr($value,0,4)+0;

				$this->controlli.="
					value.setFullYear(".$vanno.",".$vmese.",".$vgiorno.");
					";
			}
			if ($testo_var_condizione!='' && $this->config_service['lang']!="en") $value_txt="alla ".$testo_var_condizione;
			else if($this->config_service['lang']!="en")$value_txt="al ".$value_txt;
			if ($testo_var_condizione!='' && $this->config_service['lang']=="en") $value_txt=$testo_var_condizione;
			else if($this->config_service['lang']=="en") $value_txt=$value_txt;
			$value_txt=make_js($value_txt);
			$testo=make_js($this->testo);

			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
		
			if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
			}

			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
			$alert_msg="Please confirm {$testo} is before $value_txt";
			else
			$alert_msg="La {$testo} deve essere successiva $value_txt";

			$this->controlli.="
						if (data<value) {
								if(confirm('{$alert_msg}\\nOk to confirm, Cancel to modify.')){
								}else{
									document.forms[0].".$this->attributes['VAR']."Y.focus();
									return false;
								}
						}

					}
				";
		}
	}


/**
	 * Controlli sul valore della data (minore o uguale)
	 *
	 * @param String $value
	 */
function open_min_eq($value) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		if (preg_match ( "/,/", $value )) {
			$values = explode ( ",", $value );
			foreach ( $values as $key => $value ) {
				if (preg_match ( "/\[/", $value )) {
					$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
					$value = $inputval [$value_field];
					foreach ( $this->xml_form->fields as $key => $val ) {
						if ($value_field == $val ['VAR']) {
							$i = $key;
						}
					}
					$cond_obj = new field ( $this->xml_form, $i );
					$testo_var_condizione = $cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in [$value_field] != '')
						$value = $in [$value_field];
				}
				/*lato server*/
				if ($value == 'today' || $value == 'sysdate')
					$value = date ( "dmY", time () );
				$value = str_replace ( "/", "", $value );
				$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
				$data = $inputval [$this->attributes ['VAR']];
				if ($in [$this->attributes ['VAR']] != '')
					$data = $in [$this->attributes ['VAR']];
					#echo "<hr>$data";
				$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
				$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
					#echo "<hr>$value";
				$rc = $this->attributes ['VAR'] . 'RC';
				$vrc = $inputval [$rc];
				if ($in [$rc] != '')
					$vrc = $in [$rc];
				if ($data >= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
					$this->validata = false;
					#echo "<hr>$value";
					
					if ($data != ''){
						if ($this->config_service ['lang'] == "en"){
							$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
						}else{
							$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";		
						}
					}
				}
				/*lato client*/
				$giorno = substr ( $data, 6, 2 ) + 0;
				$mese = substr ( $data, 4, 2 ) - 1;
				$anno = substr ( $data, 0, 4 ) + 0;
				$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value == '' && $value_field != '') {
					$this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";
				
				} else {
					$vgiorno = substr ( $value, 6, 2 ) + 0;
					$vmese = substr ( $value, 4, 2 ) - 1;
					$vanno = substr ( $value, 0, 4 ) + 0;
					
					$this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
				}
				$testo = make_js ( $this->testo );
				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}				
				//traduzione del messaggio di alert in inglese
				if ($this->config_service ['lang'] == "en")
					$alert_msg = "{$testo} must be before $value_txt";
				else
					$alert_msg = "La {$testo} deve essere precedente $value_txt";
				
				$this->controlli .= "
						//alert (data+' - '+value);
						if (data>=value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
						}
						}
					";
			}
		} else {
			if (preg_match ( "/\[/", $value )) {
				$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
				$value = $inputval [$value_field];
				foreach ( $this->xml_form->fields as $key => $val ) {
					if ($value_field == $val ['VAR']) {
						$i = $key;
					}
				}
				$cond_obj = new field ( $this->xml_form, $i );
				$testo_var_condizione = $cond_obj->testo;
				//		echo "$testo_var_condizione<hr>";
				if ($in [$value_field] != '')
					$value = $in [$value_field];
			}
			/*lato server*/
			if ($value == 'today' || $value == 'sysdate')
				$value = date ( "dmY", time () );
			
			$value = str_replace ( "/", "", $value );
			$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
			$data = $inputval [$this->attributes ['VAR']];
			if ($in [$this->attributes ['VAR']] != '')
				$data = $in [$this->attributes ['VAR']];
				#echo "<hr>$data";
			$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
			$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$rc = $this->attributes ['VAR'] . 'RC';
			$vrc = $inputval [$rc];
			if ($in [$rc] != '')
				$vrc = $in [$rc];
			if ($data >= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
				
				//		if ($data>$value && $data!='') {
				$this->validata = false;
				#echo "<hr>$value";
				
				if ($data != ''){
					if ($this->config_service ['lang'] == "en"){
						$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
					}else{
						$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";		
					}
				}
			}
			/*lato client*/
			$giorno = substr ( $data, 6, 2 ) + 0;
			$mese = substr ( $data, 4, 2 ) - 1;
			$anno = substr ( $data, 0, 4 ) + 0;
			$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value == '' && $value_field != '') {
				$this->controlli .= "
				 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
					vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
					vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
				 	";
			
			} else {
				$vgiorno = substr ( $value, 6, 2 ) + 0;
				$vmese = substr ( $value, 4, 2 ) - 1;
				$vanno = substr ( $value, 0, 4 ) + 0;
				
				$this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
			}
			$testo = make_js ( $this->testo );

			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
						$value_txt=$this->attributes['LABEL_JS_COND'];
				}			
			//traduzione del messaggio di alert in inglese
			if ($this->config_service ['lang'] == "en")
				$alert_msg = "{$testo} must be before $value_txt";
			else
				$alert_msg = "La {$testo} deve essere precedente $value_txt";
			
			$this->controlli .= "
					if (data>=value) {
							alert('$alert_msg');
							document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
							return false;
					}
					}
				";
		}
	}
	
	/**
	 * Controlli sul valore della data (minore)
	 *
	 * @param String $value
	 */
	function open_min($value) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		if (preg_match ( "/,/", $value )) {
			$values = explode ( ",", $value );
			foreach ( $values as $key => $value ) {
				if (preg_match ( "/\[/", $value )) {
					$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
					$value = $inputval [$value_field];
					foreach ( $this->xml_form->fields as $key => $val ) {
						if ($value_field == $val ['VAR']) {
							$i = $key;
						}
					}
					$cond_obj = new field ( $this->xml_form, $i );
					$testo_var_condizione = $cond_obj->testo;
					//		echo "$testo_var_condizione<hr>";
					if ($in [$value_field] != '')
						$value = $in [$value_field];
				}
				/*lato server*/
				if ($value == 'today' || $value == 'sysdate')
					$value = date ( "dmY", time () );
				$value = str_replace ( "/", "", $value );
				$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
				$data = $inputval [$this->attributes ['VAR']];
				if ($in [$this->attributes ['VAR']] != '')
					$data = $in [$this->attributes ['VAR']];
					#echo "<hr>$data";
				$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
				$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
				if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
					$value_txt = "alla " . $testo_var_condizione;
				else if ($this->config_service ['lang'] != "en")
					$value_txt = "al " . $value_txt;
				if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
					$value_txt = $testo_var_condizione;
				else if ($this->config_service ['lang'] == "en")
					$value_txt = $value_txt;
					#echo "<hr>$value";
				$rc = $this->attributes ['VAR'] . 'RC';
				$vrc = $inputval [$rc];
				if ($in [$rc] != '')
					$vrc = $in [$rc];
				if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
					$this->validata = false;
					#echo "<hr>$value";
					
					if ($data != ''){
						if ($this->config_service ['lang'] == "en"){
							$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
						}else{
							$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";		
						}
					}
				}
				/*lato client*/
				$giorno = substr ( $data, 6, 2 ) + 0;
				$mese = substr ( $data, 4, 2 ) - 1;
				$anno = substr ( $data, 0, 4 ) + 0;
				$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
				if ($value == '' && $value_field != '') {
					$this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";
				
				} else {
					$vgiorno = substr ( $value, 6, 2 ) + 0;
					$vmese = substr ( $value, 4, 2 ) - 1;
					$vanno = substr ( $value, 0, 4 ) + 0;
					
					$this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
				}
				$testo = make_js ( $this->testo );

				/* Nicola 20/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}				
				//traduzione del messaggio di alert in inglese
				if ($this->config_service ['lang'] == "en")
					$alert_msg = "{$testo} must be before $value_txt";
				else
					$alert_msg = "La {$testo} deve essere precedente $value_txt";
				
				$this->controlli .= "
						//alert (data+' - '+value);
						if (data>value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
								return false;
						}
						}
					";
			}
		} else {
			if (preg_match ( "/\[/", $value )) {
				$value_field = preg_replace ( "/\[(.*?)\]/", "$1", $value );
				$value = $inputval [$value_field];
				foreach ( $this->xml_form->fields as $key => $val ) {
					if ($value_field == $val ['VAR']) {
						$i = $key;
					}
				}
				$cond_obj = new field ( $this->xml_form, $i );
				$testo_var_condizione = $cond_obj->testo;
				//		echo "$testo_var_condizione<hr>";
				if ($in [$value_field] != '')
					$value = $in [$value_field];
			}
			/*lato server*/
			if ($value == 'today' || $value == 'sysdate')
				$value = date ( "dmY", time () );
			$value = str_replace ( "/", "", $value );
			$value = substr ( $value, 4, 4 ) . substr ( $value, 2, 2 ) . substr ( $value, 0, 2 );
			$data = $inputval [$this->attributes ['VAR']];
			if ($in [$this->attributes ['VAR']] != '')
				$data = $in [$this->attributes ['VAR']];
				#echo "<hr>$data";
			$data = substr ( $data, 4, 4 ) . substr ( $data, 2, 2 ) . substr ( $data, 0, 2 );
			$value_txt = substr ( $value, 6, 2 ) . "/" . substr ( $value, 4, 2 ) . "/" . substr ( $value, 0, 4 );
			if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
				$value_txt = "alla " . $testo_var_condizione;
			else if ($this->config_service ['lang'] != "en")
				$value_txt = "al " . $value_txt;
			if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
				$value_txt = $testo_var_condizione;
			else if ($this->config_service ['lang'] == "en")
				$value_txt = $value_txt;
			$rc = $this->attributes ['VAR'] . 'RC';
			$vrc = $inputval [$rc];
			if ($in [$rc] != '')
				$vrc = $in [$rc];
			if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
				
				//		if ($data>$value && $data!='') {
				$this->validata = false;
				#echo "<hr>$value";
				if ($data != ''){
					if ($this->config_service ['lang'] == "en"){
						$this->input_txt .= "<br><font color=red>Date must be before $value_txt&nbsp;";
					}else{
						$this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";		
					}
				}
			}
			/*lato client*/
			$giorno = substr ( $data, 6, 2 ) + 0;
			$mese = substr ( $data, 4, 2 ) - 1;
			$anno = substr ( $data, 0, 4 ) + 0;
			$this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes ['VAR'] . ".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
			if ($value == '' && $value_field != '') {
				$this->controlli .= "
				 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
					vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
					vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
				 	";
			
			} else {
				$vgiorno = substr ( $value, 6, 2 ) + 0;
				$vmese = substr ( $value, 4, 2 ) - 1;
				$vanno = substr ( $value, 0, 4 ) + 0;
				
				$this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
			}
			$testo = make_js ( $this->testo );

			/* Nicola 20/01/2010
			 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
			 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}

				if($this->attributes['LABEL_JS_COND'] != ""){
					$value_txt=$this->attributes['LABEL_JS_COND'];
				}			
			//traduzione del messaggio di alert in inglese
			if ($this->config_service ['lang'] == "en")
				$alert_msg = "{$testo} must be before $value_txt";
			else
				$alert_msg = "La {$testo} deve essere precedente $value_txt";
			
			$this->controlli .= "
					if (data>value) {
							alert('$alert_msg');
							document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
							return false;
					}
					}
				";
		}
	}
	
	/**
	 * Controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val){
//		echo "<hr>{$this->testo}";
		$testo=make_js($this->testo);
		/* Nicola 20/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		 
		 
		 
		 
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		$dcod='00';
		if ($this->attributes['DCONT']=='yes') $dcod='16';
		if ($this->attributes['DSPEC']=='yes') $dcod='03';
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';
    if ($this->attributes ['SAVE'] != 'obbligatorio')
    {
    	$this->salva_js="
		
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
				";
		}
		else
		{
		if (!isset($this->attributes['CONDITION']) && $this->attributes ['SAVE'] == 'obbligatorio') $this->salva_js="
		
				c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
				";
				
				
				
				
		else
		{
			$oper="==";
			
			
			
			
			
			
			if (preg_match("/!/",$this->attributes['CONDITION_VALUE']))
			 {
			 	 
			 	
			 
			 	
				$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);
				
				}

		
		
		// echo $oper;

			$val_cond=$this->attributes['CONDITION_VALUE'];
			//echo "$val_cond<br>";
			$vals=explode(",",$val_cond);$loc_js="if (";
			for ($i=0;$i<count($vals);$i++){
				if ($i!=0) $loc_js.="||";
				
		//		echo "condition value del save".$this->atributes['CONDITION_VALUE']."<hr>";
				
				$loc_js.="
		      value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
			}
			$loc_js.=")";
			// echo "$loc_js<br>";
			$this->salva_js="
			$loc_js
					c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
					else {
					  c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
						c1+='<<b###".$this->attributes['VAR']."Y###".$testo.">>';
						}

				";

		}
  }
		$in=$this->session_vars;
		$insert_errors=$this->errors;
		if ($in['invia']!='' || $in['INVIOCO']=='0'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]=='') {
					$this->validata=false;
					$testo=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo ? obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='') {
					$this->validata=false;
					$testo=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
	}

	/**
	 * Controlli all'invio
	 *
	 * @param String $val
	 */
	function open_send($val){
		//		echo "<hr>{$this->testo}";
		$testo=make_js($this->testo);
		
		/* Nicola 20/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		
		$dcod='00';
		if ($this->attributes['DCONT']=='yes') $dcod='16';
		if ($this->attributes['DSPEC']=='yes') $dcod='03';
			if ($this->attributes['DCONT']=='yes'&& $this->attributes['DSPEC']=='yes') $dcod='31';
		if (!isset($this->attributes['CONDITION'])) {
			//la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
			$this->invia_js="";
			if ($this->attributes['NDAY']=='yes') {
			 $this->invia_js.="
			 if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
			 document.forms[0].{$this->attributes['VAR']}D='';
			 else
			 document.forms[0].{$this->attributes['VAR']}D='15';
			 
			 ";
			}
			$this->invia_js.="
				c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
				";
		}
		else
		{
			$oper="==";
			
			
			
			
			
			if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}

			$val_cond=$this->attributes['CONDITION_VALUE'];
			//echo "$val_cond<br>";
			$vals=explode(",",$val_cond);$loc_js="if (";
			for ($i=0;$i<count($vals);$i++){
				if ($i!=0) $loc_js.="||";
				
		//		echo "condition value del send".$this->attributes['CONDITION_VALUE']."<hr>";
				
				$loc_js.="
		      value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
			}
			$loc_js.=")";
			// echo "$loc_js<br>";
			//la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
			$this->invia_js="";
			if ($this->attributes['NDAY']=='yes') {
			 $this->invia_js.="
			 if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
			 {
			 document.forms[0].{$this->attributes['VAR']}D.value='';
			 
			 }
			 else{
			 document.forms[0].{$this->attributes['VAR']}D.value='15';
			
			 }
			 
			 ";
			}
			if($this->attributes['SEND']=='facoltativo') $facoltativo_flag='f';
			$this->invia_js.="
			$loc_js
					c1+='<<{$facoltativo_flag}d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
					else {
					  c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
						c1+='<<b###".$this->attributes['VAR']."Y###".$testo.">>';
						}

				";
//echo '<hr> esto es el javascript'. $this->invia_js ;
		}

		$in=$this->session_vars;
		$insert_errors=$this->errors;
		if (($in['invia']!='' || $in['INVIOCO']=='1') && $this->attributes['SEND']!='facoltativo' ){
			if ($this->condition_passed ){
				if ($in[$this->attributes['VAR']]=='') {
					$this->validata=false;
					$testo=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo ? obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!='') {
					$this->validata=false;
					$testo=make_js($this->testo);
					$this->errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}


	}

	function open_disabled($value){
		$this->check_js.="
				if(document.forms[0].".$this->id."D && document.forms[0].".$this->id."D.value!='')
					document.forms[0].".$this->id."D.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."M && document.forms[0].".$this->id."M.value!='')
					document.forms[0].".$this->id."M.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."Y && document.forms[0].".$this->id."Y.value!='')
					document.forms[0].".$this->id."Y.disabled=true;
			";
	}
	
	function open_block_value($value){
		if($this->db_vars[$this->attributes['VAR']]!=""){
		$this->check_js.="
				if(document.forms[0].".$this->id."D && document.forms[0].".$this->id."D.value!='')
					document.forms[0].".$this->id."D.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."M && document.forms[0].".$this->id."M.value!='')
					document.forms[0].".$this->id."M.disabled=true;
			";
		$this->check_js.="
				if(document.forms[0].".$this->id."Y && document.forms[0].".$this->id."Y.value!='')
					document.forms[0].".$this->id."Y.disabled=true;
			";
		}
	}
	
	
	/**
	 * Visualizzazione nella modalità progressiva
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	function all_in($var, $i, $row, $this_closed) {
		if ($this_closed){
			$ret['body']="
			<td class=sc4bis>
			{$row[$var]}
			</td>
			";
			return $ret;
		}
		else {
			if ($row[$var] != '') {
				if (preg_match("|(.*?)/(.*?)/(.*?)"))
				$date = explode ( "/", $row [$var] );
				else {
					$date[0]=substr($row[$var], 0,2);
					$date[1]=substr($row[$var], 2,2);
					$date[2]=substr($row[$var], 4,4);
				}
			} else
				$date = '';
			$ret['body']= "
				<td class=sc4bis>
				<input type='text' name='{$var}_PROGR_{$i}D' size=\"2\" value=\"{$date[0]}\">/
				<input type='text' name='{$var}_PROGR_{$i}M' size=\"2\" value=\"{$date[1]}\">/
				<input type='text' name='{$var}_PROGR_{$i}Y' size=\"4\" value=\"{$date[2]}\">
				<input type=\"hidden\" name=\"{$var}_PROGR_{$i}\" value=\"\"/>
	            <input type=\"hidden\" name=\"{$var}_PROGR_{$i}RC\" />
				</td>";
			$c1_agg .= "
				c1+='<<fd00###{$var}_PROGR_{$i}###>>';
			";
			$ret['c1_agg']=$c1_agg;
			return $ret;							
		}
	}
	
	/**
	 * Visualizzazione nella modalità progressiva (header)
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		$select_field .= "to_char($field,'DD/MM/YYYY') as $field,";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$onclick_action = "";
			for($i = 1; $i <= $m_p; $i ++) {
				$onclick_action .= "
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}D)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}D.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_D.value;
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}M)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}M.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_M.value;
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}Y)
					document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}Y.value=document.forms['ALL_IN_FORMS'].{$field}_TOT_Y.value;
				";
				
			}
			$field_tot .= "
					<input type='text' name='{$field}_TOT_D' size=\"2\">/
					<input type='text' name='{$field}_TOT_M' size=\"2\">/
					<input type='text' name='{$field}_TOT_Y' size=\"4\"><br>
					<!--input type='button' value='applica a tutti' onclick=\"
					$onclick_action
					\"-->
					<button class=\"btn btn-xs btn-warning\" type=\"button\" onclick=\"$onclick_action\">
						<i class=\"fa fa-floppy-o bigger-110\"></i>
						applica a tutti
					</button>
				";
				$tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
		}
		return $tr_agg;
	}
	
	function open_jcondition($val) {
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		$var_cond = $val;
		
		echo "var condition del open_jcondition=".$inputval [$var_cond]."<hr>";
		
		$this->condition_passed = false;
		$val_cond = $this->attributes ['CONDITION_VALUE'];
		if ($this->attributes ['HIDE'] == 'yes') {
			if (preg_match ( "/,/", $val_cond )) {
				$controllo= "
				$('#tr_".$this->id."').hide();
	";
				$vals = explode ( ",", $val_cond );
				foreach ( $vals as $key => $value ) {
					if (isset ( $in ['INVIOCO'] ))
						$value_to_control = $in [$var_cond];
					else
						$value_to_control = $inputval [$var_cond];
					
					if ($value_to_control == $value) {
						$this->condition_passed = true;
					}
					$controllo.= " \n
		value=value_of('$var_cond', '0');
		if (value=='$value')
		{
		if (document.forms[0]." . $this->id . "D.value!='') {$this->id}D_val=document.forms[0]." . $this->id . "D.value;
		if (document.forms[0]." . $this->id . "M.value!='') {$this->id}M_val=document.forms[0]." . $this->id . "M.value;
		if (document.forms[0]." . $this->id . "Y.value!='') {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;
		$('#tr_".$this->id."').show();
		}
		";
				}
			} else {
				$op = '!=';
				if (preg_match ( "/\!/", $val_cond )) {
					$val_cond = str_replace ( "!", "", $val_cond );
					$op = '==';
				}
				if (isset ( $in ['INVIOCO'] ))
					$value_to_control = $in [$var_cond];
				else
					$value_to_control = $inputval [$var_cond];
				if ($op == '==')
					$this->condition_passed = ($value_to_control != $val_cond);
				else
					$this->condition_passed = ($value_to_control == $val_cond);
				$controllo = " \n
	value=value_of('$var_cond', '0');
	if (document.forms[0]." . $this->id . "D.value!='') {$this->id}D_val=document.forms[0]." . $this->id . "D.value;
	if (document.forms[0]." . $this->id . "M.value!='') {$this->id}M_val=document.forms[0]." . $this->id . "M.value;
	if (document.forms[0]." . $this->id . "Y.value!='') {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;
	if (value{$op}'$val_cond')
	{

	document.forms[0]." . $this->id . "D.value='';
	document.forms[0]." . $this->id . "M.value='';
	document.forms[0]." . $this->id . "Y.value='';
	";
				//foreach ($this->values as $key => $decode) $controllo.=" \n	document.forms[0].".$this->id."[".($key-1)."].checked=false;";
				$controllo.= " \n
	$('#tr_".$this->id."').hide();
	}
	else{
	if (typeof({$this->id}D_val)!= \"undefined\" && {$this->id}D_val) document.forms[0]." . $this->id . "D.value={$this->id}D_val;
	if (typeof({$this->id}M_val)!= \"undefined\" && {$this->id}M_val) document.forms[0]." . $this->id . "M.value={$this->id}M_val;
	if (typeof({$this->id}Y_val)!= \"undefined\" && {$this->id}Y_val) document.forms[0]." . $this->id . "Y.value={$this->id}Y_val;
	if (document.getElementById('tr_" . $this->id . "'))
	$('#tr_".$this->id."').show();
	}";
			}
		
		} else {
			$op = '!=';
			if (preg_match ( "/\!/", $val_cond )) {
				$val_cond = str_replace ( "!", "", $val_cond );
				$op = '==';
			}
			//echo "<li>{$in[$var_cond]} - $var_cond - $val_cond</li>";
			/*foreach ($this->xml_form->fields as $key => $val){
			if ($val['TYPE']=='checkbox') {
			foreach ($val['VALUE'] as $key => $val){
			//echo "<li>$key</li>";
			if (!isset($in[$key])) $in[$key]='0';
			}
			}
			}*/
			//echo "<li>$var_cond - {$in[$var_cond]} - {$val_cond}</li>";
			if ($op == '==')
				$this->condition_passed = ($in [$var_cond] != $val_cond);
			else
				$this->condition_passed = ($in [$var_cond] == $val_cond);
			
			$controllo.= " \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
			$controllo.= "
					if (document.forms[0]." . $this->id . "D && document.forms[0]." . $this->id . "M && document.forms[0]." . $this->id . "Y)
						{

						 	document.forms[0]." . $this->id . "D.value='';
							document.forms[0]." . $this->id . "M.value='';
							document.forms[0]." . $this->id . "Y.value='';
						}


					}
					else{
						$('#tr_".$this->id."').show();
					}
	";
		}
		/*$controllo.="
}
if (document.getElementById('".$this->id."'))
document.getElementById('tr_".$this->id."').style.display='';";*/
		
		$this->html = "<tr id='tr_" . $this->id . "' style=\"display:none\">" . $this->html . "</tr>";
		$this->script="
				var controllo=function(){
					{$controllo}
				}
				controllo();
				$(\"[name='{$this->attributes['CONDITION']}']\").change(controllo);
				";
	}

}

?>