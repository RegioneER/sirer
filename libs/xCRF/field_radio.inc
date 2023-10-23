<?


include_once "field_code_decode.inc";
/**
 * Gestione del campo tipo radio
 *
 * @package Fields
 */
class field_radio extends field_code_decode {


    //Ridefinisco il costruttore
    function __construct($conn=null, $xml_form=null,$i=null,$session_vars=null, $db_vars=null, $service=null, $errors=null){
        parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		if($this->attributes['SHOW_CRF']=='yes' && isset($_GET['CRF_BLANK'])){
			unset($this->attributes['HIDE']);
		}
		if(!isset($this->attributes['VAR_SIZE'])){
			$this->attributes['VAR_SIZE']="10";
		}
    }
        /**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value,$mock=false) {
		if($this->config_service['lang']=='it'){
            $deseleziona_txt="deseleziona";
        }else{
            $deseleziona_txt="deselect";
        }
		$inputval = $this->db_vars;
		$in = $this->session_vars;
		$cols = $this->attributes ['SUBTBCOL'];
		$cols -= 0;
		if ($cols == 0)
			$cols = 1;
		$txt = $this->testo;
		$input_html = '';
		if($mock){
			$input_html .= '"';
			$input_html .= '<table border=\'0\' cellpadding=\'0\' cellspacing=\'0\' ><tr style=\'display:none\'><td colspan=\'<%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.SUBTBCOL)) %>\'>&nbsp;</td>';
		}else{
			$input_html .= '<table border=\'0\' cellpadding=\'0\' cellspacing=\'0\' ><tr style=\'display:none\'><td colspan=\'' . $cols . '\'>&nbsp;</td>';
		}
		if($mock){
			$input_html .= '</tr><tr>"+';
		}
		$col = 0;
		
		$onclick_rubber=$this->attributes ['ONCLICK_RUBBER'];
		if($mock){
			$radio_desel ='<a href=\'#\' onclick=\'return false;\' ><i class=\'fa fa-eraser\' style=\'font-size: 1.2em;\'></i></a>';
		}else{
			$radio_desel ="<a href=\"#\" onclick=\"{$onclick_rubber}radioclear('{$this->attributes ['VAR']}');cf();return false;\" ><i class=\"fa fa-eraser\" style=\"font-size: 1.2em;\"></i></a>";
		}
		
		$disabled = "";
		if ($this->attributes ['DISABLED'] == 'yes') {
			$disabled = "disabled='disabled'";
			$radio_desel='';
		}
		
		 
		if($mock){
			$input_html.='"<% col=0; %>\\n "+
						  "<% for (i in (rf.get(Formbuilder.options.mappings.VALUES) || [])) { %>\\n "+';
			$input_html .= '
	      		"<% if(col==rf.get(Formbuilder.options.mappings.SUBTBCOL)){ col=0; } %>\\n "+
	      		"<% if(col==0){%>\\n</tr><tr> <% } %>\\n "+
	      		"<% col++; %>\\n"+
				"<td><input type=\'radio\' value=\'<%= rf.get(Formbuilder.options.mappings.VALUES)[i].value %>\'  <%= rf.get(Formbuilder.options.mappings.VALUES)[i].checked && \'checked\' %> <%= rf.get(Formbuilder.options.mappings.VALUES)[i].disabled_val && \'disabled\' %> onclick=\'javascript: return false;\' /> <label><%= rf.get(Formbuilder.options.mappings.VALUES)[i].label %>&nbsp;\\n</label></td>"+
	      		"\\n&nbsp; <% } %>\\n\\n"+
					';		
			
		}
		else{
            $found = false;
			foreach ( $this->values as $val => $decode ) {
				#echo "$val - $decode";
				if ($this->attributes ['DISABLED'] != 'yes') {
					if($this->attributes['DISABLED_VAL']==$val ){$disabled = "disabled='disabled'";}
					else{$disabled="";}
				}
				if(isset($_GET['debug']))echo "$val - $decode";
				if ($col == $cols)
					$col = 0;
				if ($col == 0)
					$input_html .= "
	      		</tr>
	      		<tr>
	      		";
				$col ++;
				$checked = "";
				
				/* Nicola 02/02/2011
				 * gestione evento onchange e onclick
				 */
				if($this->attributes ['ONCHANGE'] != ""){
					$onchange_radio = "onchange=\"".$this->attributes ['ONCHANGE']."\"";
				}else{
					$onchange_radio = "";
				}
				
				if($this->attributes ['ONCLICK'] != ""){
					$onclick_radio = $this->attributes ['ONCLICK'];
				}else{
					$onclick_radio = "";
				}

                if (!$found) {
                    //Domina il dato corrente
                    if (!$inputval [$this->attributes ['VAR']]) {
                        //Non ho dato da DB
                        if ($this->attributes ['CHECKED']."" === $val."") {
                            $checked = "checked=\"checked\"";
                        }
                    } else {
                        //Ho dato da DB
                        if ($inputval [$this->attributes ['VAR']]."" === $val."") {
                            $checked = "checked=\"checked\"";
                        }
                    }
                }
				if ($in [$this->attributes ['VAR']]."" === $val."")
				{
                    $found = true;
					$checked = "checked=\"checked\"";
				}
				$input_html .= '
	      		<td><input type="radio" value="' . $val . '" name="' . $this->attributes ['VAR'] . '" ' . $checked . ' '.$onchange_radio.' onclick="'.$onclick_radio.'cf();" '.$disabled.' /> <label>' . $decode . '&nbsp;</label></td>';
			}
		}
		if($mock){
			$input_html .= '"</tr>';
		}else{
			$input_html .= '</tr></table>';
		}
        $input_html .= '<div >'; // style="float:left;"
        if($mock){
        	$input_html .= '<tr><td>(<a href=\'#\' onclick=\'return false\'>'.$deseleziona_txt.'</a>)';
        	$input_html .= "&nbsp;$radio_desel</td></tr></table><div class=\'col-sm-5\'></div><div class=\'col-sm-5\'><%= rf.get(Formbuilder.options.mappings.DEF) %></div>";
        }else{
        	$input_html .= '(<a href="#" onclick="radioclear(\'' . $this->attributes ['VAR'] . '\'); cf(); return false">'.$deseleziona_txt.'</a>)';
        	$input_html .= "&nbsp;$radio_desel";
        }
		
        $input_html .= '</div>';
		
		$input_html .= '</table>'.$this->attributes['DEF'];
		if($mock){
			$input_html .= '"';
		}
		$this->input_field = $input_html;
		$this->input_txt = $txt;
	}
	
	function open_tablista_sql($value){
		$value=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $value);
		$sql=new query($this->conn);
		$tbHeaders=explode("|", $this->attributes['TABLISTA_HEADERS']);
		$sql->exec($value);//complessa Carlo var_glob
		$tb="<br/><table border=\"0\" cellpadding=\"0\" cellspacing=\"2\" align=\"left\" ><tr>";
		foreach ($tbHeaders as $key=>$val){
			$tb.="<td class=int>$val</td>";
		}
		$tb.="</tr>";
		while ($sql->get_row()){
			$tb.="<tr>";
			foreach ($sql->row as $key=>$val){
				$tb.="<td class=sc4bis>$val</td>";
			}
			$tb.="</tr>";
		}
		$tb.="</table>";
		$this->input_txt.=$tb;
	}

	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
		$inputval = $this->db_vars;
		$in = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$cols = $this->attributes ['SUBTBCOL'];
		$txt = $this->testo;
		$input_html = '
      <table border="0" cellpadding="0" cellspacing="0" ><tr style="display:none"><td colspan="' . $cols . '">&nbsp;</td>
      ';
		$col = 0;
		$input_html = '
      <table border="0" cellpadding="3" cellspacing="0" ><tr style="display:none"><td colspan="' . $cols . '">&nbsp;</td>
      ';
		foreach ( $this->values as $val => $decode ) {
			if($val!=''){
				if ($col == $cols)
					$col = 0;
				if ($col == 0)
					$input_html .= "
	      		</tr>
	      		<tr>
	      		";
				$col ++;
				$checked = "";
				if ($inputval [$this->attributes ['VAR']] == "$val") {
					$checked = "checked=\"checked\"";
				}
				if ($in [$this->attributes ['VAR']] == "$val") {
					$checked = "checked=\"checked\""; #echo "<hr>".$inputval[$this->attributes['VAR']]." - ".$in[$this->attributes['VAR']]." - $val";
				}
				if ($checked == "checked=\"checked\"") {
					$input_html .= "<td><i class='fa fa-dot-circle-o'></i>";
				} else {
					$input_html .= "<td><i class='fa fa-circle-o'></i>";
				}
				$input_html .= $decode . "</td>";
			}
		}
		$input_html .= "</table>";
		$this->input_txt = $txt;
		
		if($this->deleted==2 && $this->attributes['MAIN']!="yes"){
			$input_html="<span style='text-decoration:line-through;'>$input_html</span>";
		}
		if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL']!='') {
			$audit_trail =  new audit_trail($this->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
			$input_html.= $audit_trail->audit_trail_popup($in);
	
		}
		
		
		if(isset ( $_GET ['CRF_ANNOTE'] )){
			$input_html .= '<span class="textfield"><b><i><font color="#333300"><u>' .$this->xml_form->form['TABLE'].'.'.$this->attributes['VAR']. '</span></u></font></i></b>';
		}
		
		$this->input_field = $input_html;
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1){
			$ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
		}else{
			$ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '</td></tr>';
		}
		#return $ret;
		
		// Per fare un eQ su campo direttamente dalla form , dipende dal parametro MOSTRAEQ , che viene
		// valorizzat osolo quando premo il link invia eQ su campo , che si trova sotto invia eQ su questa scheda 
		// compare un linketto affianco ad ogni field che mi porta alla schermata di una nuova eQ con valorizzati 
		// tutti i campi incluso variabile
		if (isset($in['MOSTRAEQ']) && $in['MOSTRAEQ']!='') {
			$input_html.='<a href="index.php?CENTER='.$in['CENTER'].'&CODPAT='.$in['CODPAT'].'&REGISTRY='.$in['REGISTRY'].'&ESAM='.$in['ESAM'].'&PROGR='.$in['PROGR'].'&VISITNUM='.$in['VISITNUM'].'&VISITNUM_PROGR='.$in['VISITNUM_PROGR'].'&FIELD='.$this->attributes['DESCRIPTION'].'&eQuery&eform" ><img width=\'15\' height=\'14\' src=\'/images/img_to_be_defined.jpg\'>eQ &nbsp;&nbsp;</a>';
			$this->input_field = $input_html;
		}
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
						  for (i=0;i<document.forms[0]." . $this->attributes ['VAR'] . ".length;i++){
						  	//alert (document.forms[0]." . $this->attributes ['VAR'] . "[i].value);
						  	if (document.forms[0]." . $this->attributes ['VAR'] . "[i].value==compila_value) document.forms[0]." . $this->attributes ['VAR'] . "[i].checked=true;
						  }
							document.forms[0]." . $this->attributes ['VAR'] . ".disabled=true;
						}
					}
			";
	}

	/**
	 * Controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val) {
		if ($val == 'obbligatorio') {
            $testo = $this->input_txt;
            $testo = make_js($this->input_txt);
            /* Andrea 26/01/2010
             * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
             */
            if ($this->attributes['LABEL_JS'] != "") {
                $testo = $this->attributes['LABEL_JS'];
            }
            if ($this->attributes ['CONDITION'] != '') {
                $var_cond = $this->attributes ['CONDITION'];
                $val_cond = $this->attributes ['CONDITION_VALUE'];
                $this->salva_js = "
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n
			  	";
            } else
                $this->salva_js = "c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n";
        }
	}

	/**
	 * Controlli all'invio
	 *
	 * @param String $val
	 */
	function open_send($val) {
        $or_condition='';
		if ($val == 'obbligatorio' && $this->session_vars ['INVIOCO'] == 1) {
			$this->condition_passed = true;
				if ($this->attributes ['CONDITION'] != '') {
					$var_cond = $this->attributes ['CONDITION'];
					if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
						/**
						 * CONTROLLO LATO SERVER.
						 * Modifica Colabufalo 02/03/2011 , gestione della condition_passed 
						 * per i campi radio condizionati da piu' valori (CONDITION_VALUE).
						 * In questo caso di reimposta $this->condition_passed = false;
						 * si splitta CONDITION_VALUE e si effettua un foreach , mettendo 
						 * le condizioni in OR. Alla prima condizione passata si setta
						 * $this->condition_passed = true; e si esce con un break.
						 * Il caso con CONDITION_VALUE singolo e' gestito nell'else.
						 */
						$vals_cond=explode(",", $this->attributes['CONDITION_VALUE']);
						$this->condition_passed = false;
						foreach ($vals_cond as $key => $val_split_cond){
							if(trim($val_split_cond)!=""){
								if ($this->session_vars [$var_cond] == $val_split_cond){
									$this->condition_passed = true;
									break;
								}
							}
						}
					}else{
						$val_cond = $this->attributes ['CONDITION_VALUE'];
                        if (preg_match("/\!/", $val_cond)) {
                            $val_cond=str_replace("!", "",$val_cond);
                            //Condizione diverso, controllo uguaglianza
                            if ($this->session_vars [$var_cond] == $val_cond) {
                                $this->condition_passed = false;
                            }
                        }else{
                            //Condizione uguale, controllo diversita'
                            if ($this->session_vars [$var_cond] != $val_cond) {
                                $this->condition_passed = false;
                            }
                        }
					}
					
				}
			//$this->validata=false;
			if ($this->condition_passed && $this->session_vars[$this->id]==''){
                $this->validata=false;
                $this->errors[$this->attributes['VAR']]="The field is mandatory";
            }
			if (!$this->condition_passed && $this->session_vars[$this->id]!=''){
                $this->validata=false;
                $this->errors[$this->attributes['VAR']]="The field must be empty (condition not passed)";
            }
        }

        if ($val == 'obbligatorio'){
            $testo = $this->testo;
            $testo = make_js ( $this->input_txt );
            /* Colabufalo 26/01/2010
             * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
             */
            if($this->attributes['LABEL_JS'] != ""){
                $testo=$this->attributes['LABEL_JS'];
            }
            if ($this->attributes ['CONDITION'] != '') {
                if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
                    /**
                     * CONTROLLO LATO CLIENT.
                     * Colabufalo 02/03/2011 , gestione del controllo js
                     * per i campi radio condizionati da piè valori (CONDITION_VALUE).
                     * si splitta CONDITION_VALUE e si effettua un foreach , mettendo
                     * le condizioni in OR.
                     * Il caso con CONDITION_VALUE singolo è gestito nell'else.
                     */
                    $vals_cond=explode(",", $this->attributes['CONDITION_VALUE']);
                    foreach ($vals_cond as $key => $val_split_cond){
                        if(trim($val_split_cond)!=""){
                            if($or_condition==""){$or_condition="value=='".$val_split_cond."'";}
                            else{$or_condition.="|| value=='".$val_split_cond."'";}
                            $this->invia_js = "
                                value=value_of('{$this->attributes['CONDITION']}', '0');
                                if (".$or_condition."){
                                c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n
                            }";
                        }
                    }
                }
                else{
                    $var_cond = $this->attributes ['CONDITION'];
                    $val_cond = $this->attributes ['CONDITION_VALUE'];
                    $this->invia_js .= "
                    value=value_of('$var_cond', '0');
                        if (value=='$val_cond')
                    c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n

                    ";
                }
            } else
                $this->invia_js = "c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n";
        }
		

	}
	
	function fields_value_bytb($value){
		global $in;
		global $inputval;
		global $init_service;
		if($init_service)return ;
		//		print_r($inputval);
		if ($this->xml_form->closed && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
			$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
			
			return ;
		}
		
		$code=$this->attributes['BYTBCODE'];
		$decode=$this->attributes['BYTBDECODE'];
		$where=$this->attributes['BYTBWHERE'];
		$order_by=$this->attributes['BYTBORDERBY'];
		$where=str_replace("min_of","<",$where);
		$where=str_replace("max_of",">",$where);
		if (!preg_match("/ana_utenti/i",$value)){	$value=$GLOBALS['service']."_".$value;}
		$decode=str_replace("#BR#", "<br>", $decode);
		$decode=str_replace("#i#", "<i>", $decode);
		$decode=str_replace("#/i#", "</i>", $decode);
		//ridondanza richiesta a causa di problematiche riscontrate in ADCARE. Giorgio Delsignore 15/12/2007 (A - Allineamento)
		$where=preg_replace("/\[VISITNUM_PROGR\]/e",$in['VISITNUM_PROGR'] , $where);
		$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		$order_by=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $order_by);
		//echo "<hr>{$inputval['PROV_CP']} - {$in['PROV_CP']} - {$_GLOBALS['PROV_CP']}<hr>$where";
		global $conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		if ($order_by!='') $query.=" from $value $where order by $order_by";
		else $query.=" from $value $where order by decode asc";
		
//		echo $query; 		print_r($value);echo "-";die();
		$sql=new query($conn);
		$sql->set_sql($query);
        //if($this->attributes['VAR']=='PROVINCIA_NSC')	echo "<li>$query</li>";
		//$querys_[count($query_)]=
		$sql->exec();
		global $in;
//		echo $query;
		while ($sql->get_row()) {
			if ($decode!='') {
				$this->values[$sql->row['CODE']]=$sql->row['DECODE'];
				if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE']=='hidden') {
					$in[$this->attributes['VAR']]=$sql->row['DECODE'];
				}
			}
			else {
				global ${$this->attributes['BYVAR']};
				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			}
			$this->db_vars[$this->attributes['VAR']]=$sql->row['CODE'];
		}
	}
	
	
	/**
	 * Visualizzazione nella modalitè  progressiva (header)
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	function all_in($var, $i, $row, $this_closed){
        $eQ_content=null;
		$val=$this->attributes;
		$radio_html = "";
		$radio_html .= "
			<td class=sc4bis id=".$var.'_PROGR_'.$i."><span id='view_field_{$var}_PROGR_{$i}'>";
			
		foreach ( $this->values as $k => $v ) {
			if(!(isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM']))){
				if ($row [$val ['VAR']] == $k )
					$checked = "checked=\"checked\"";
				else
					$checked = "";
			}
			if (! $this_closed){
				$radio_desel ="<a href=\"#\" onclick=\"radioclear('{$var}_PROGR_{$i}');return false;\" ><i class=\"fa fa-eraser\" style=\"font-size: 1.2em;\"></i></a>";
				$radio_html .= "
					<input type='radio' value=\"$k\" name=\"{$var}_PROGR_{$i}\" $checked >$v <br> 
				";
			}
			else {
				if($this->config_service['eQuery']=='1' && (isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM'])) ){
					$eQ_desel ="<a href=\"#\" onclick=\"radioclear('{$var}_PROGR_{$i}');return false;\" ><i class=\"fa fa-eraser\" style=\"font-size: 1.2em;\"></i></a>";
					$eQ_content.="<input type='radio' value=\"$k\" name=\"{$var}_PROGR_{$i}\" $checked >$v <br> ";
					
					$eQ= $this->eQ_all_in($var, $i, $row, $this_closed);
					
					if ($this->xml_form->tb_vals[$this->id] == $k ) {
						$checked = "checked=\"checked\"";
					}
					if( $this->xml_form->tb_vals[$this->id]=='' && !isset($this->xml_form->tb_vals[$this->id])){
						$checked = "";
					}
				}
				if (isset($this->session_vars['AUDIT_TRAIL']) && $this->session_vars['AUDIT_TRAIL']!='') {
					$audit_trail =  new audit_trail($this->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
					$at = $audit_trail->audit_trail_popup($this->session_vars, $i);
				}
				elseif(isset($_GET['CRF_ANNOTE'])){
					$db=$this->attributes['VAR'];
					$table=$this->xml_form->form['TABLE'];
					$annote = "<b><br><u>$table.$db</u></b>";
				}
				if ($checked == "checked=\"checked\"") {
					$radio_html .= "
						<i class='fa fa-dot-circle'></i>$v<br>
					";
				} else{
					$radio_html .= "
						<i class='fa fa-dot-circle-o'></i>$v<br>
					";
				}
			}
		}
		$radio_html .="</span>";
		$radio_html = rtrim ( $radio_html, "<br>" );
		$body = "$radio_html $radio_desel $at $annote 
			<span id='mod_field_{$var}_PROGR_{$i}' style=\"display:none\">$eQ_content $eQ_desel</span> <br>$eQ</td>";
		
		$ret['body']=$body;
		return $ret;
	}


	/**
	 * Visualizzazione nella modalitè  progressiva (header)
	 *
	 * @param field_radio $field
	 * @param number $m_p
	 * @param form $xml_form
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
        $field_tot=null;
        $tr_agg=null;
		foreach($xml_form->fields as $key => $value) {
			if($xml_form->fields[$key]['VAR']==$field) {
				$val=$value;
			}
		}

		$select_field = $field . ",";
		$onclick_action = "";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$i = 0;
			foreach ( $val ['VALUE'] as $k => $v ) {
				$posval [$i] = $k;
				$i ++;
			}
			for($i = 1; $i <= $m_p; $i ++) {
				$onclick_action .= "
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i})
						document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_tot.value;
					";
				foreach ( $posval as $pk => $pv ) {
					$onclick_action .= "
						if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i})
						document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}[$pk].checked=document.forms['ALL_IN_FORMS'].{$field}_tot[$pk].checked;
						";
				}
			}
			foreach ( $val ['VALUE'] as $k => $v ) {
				$field_tot .= "
						<input type='radio' value=\"$k\" name=\"{$field}_tot\">$v<br>
					";
			}
			
			if($val['NOTE']!="")
			$note="<br /><span style=\"font-size:9px;color:red;\">".$val['NOTE']."</span>";
			
			$field_tot = rtrim ( $field_tot, "<br>" );
			$tr_agg .= "<td class=int valign=bottom >$field_tot
					<input type='button' value='applica a tutti'
					 onclick=\"
					 $onclick_action
					\">$note
					</td>";
		}
		return $tr_agg;
	}
	
	function builder_js(){
		$field_description['field']="radio";
		$field_description['order']=15;

		$this->open_('',true);
		$field_description['view']="\"<div class=\'form-group\'><div><label class=\'col-sm-5 control-label no-padding-right\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></label><div class='build-col-sm-5'>\"+
		".$this->input_field."+".
		"\"&nbsp;</div></div></div></div>\"";
		
		$field_description['edit'][]='edit/db_info'; 	
		$field_description['edit'][]='edit/radio_values';
		$field_description['edit'][]='edit/bytb';
		$field_description['edit'][]='edit/main_sub';
		$field_description['edit'][]='edit/condition';
		$field_description['edit'][]='edit/javascript';
		$field_description['edit'][]='edit/formatting';
		$field_description['edit'][]='edit/save_send';
		$field_description['addButton']['class']='fa fa-circle-o';
		$field_description['addButton']['label']='Radio button';
		
		
		return $field_description;
		
	}

}




?>