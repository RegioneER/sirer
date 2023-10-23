<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_ora extends field{

	function insert_stmt(){
		global $in;
		//echo "<hr>";
//		print_r($in);
		if ($this->attributes['TB']!='no'){

			$this->field_stmt[0]=$this->attributes['VAR']."_H";
			$this->field_stmt[1]=$this->attributes['VAR']."_M";
			if(strtoupper($in[$this->attributes['VAR']."_H"])=='NK'||strtoupper($in[$this->attributes['VAR']."_H"])=='NA'){
				if(strtoupper($in[$this->attributes['VAR']."_H"])=='NK'){
					$this->value_stmt[0]='-9922';
					$this->value_stmt[1]='-9922';
				}
				else{
				$this->value_stmt[0]='-9911';
				$this->value_stmt[1]='-9911';
				}
			}
			else{
				$this->value_stmt[0]=$in[$this->attributes['VAR']."_H"];	
				if(strtoupper($in[$this->attributes['VAR']."_M"])=='NK'||strtoupper($in[$this->attributes['VAR']."_M"])=='NA')
						if(strtoupper($in[$this->attributes['VAR']."_M"])=='NK')
								$this->value_stmt[1]='-9922';//ES NK
						else
								$this->value_stmt[1]='-9911';//ES NA
				else
						$this->value_stmt[1]=$in[$this->attributes['VAR']."_M"];
			}

		}
		//print_r($this->value_stmt);
		return;
	}

	/**
	 * Alliena_db
	 * Costruisce la stringa di inserimento del campo nella tabella quando non presente
	 *
	 * @return string
	 */
	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']}_H number";
			$ret[1]="{$this->attributes['VAR']}_M number";
			return $ret;
		}
		else return ;
	}


	function open_($value,$mock=false){
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		if($mock){
			$this->input_field.="\"<div class=\'col-sm-6\'>\\n<input type=\'text\' maxlength=\'2\' size=\'2\'/>&nbsp;\\n:&nbsp;<input type=\'text\' maxlength=\'2\' size=\'2\' />\\n</div>\"";
		}
		else{
			$txt=$this->testo;
			if ($inputval[$this->attributes['VAR']."_H"]!='') $value_h=$inputval[$this->attributes['VAR']."_H"];
			if ($in[$this->attributes['VAR']."_H"]!='') $value_h=$in[$this->attributes['VAR']."_H"];
			if ($inputval[$this->attributes['VAR']."_M"]!='') $value_m=$inputval[$this->attributes['VAR']."_M"];
			if ($in[$this->attributes['VAR']."_M"]!='') $value_m=$in[$this->attributes['VAR']."_M"];
			$keys=array_keys($this->values);
			if($value_h==-9922) $value_h='NK';
			if($value_h==-9911) $value_h='NA';
			if($value_m==-9922) $value_m='NK';
			if($value_m==-9911) $value_m='NA';
			if ($value_h <10 && is_numeric($value_h)) $value_h = "0". $value_h;
			if ($value_m <10 && is_numeric($value_m)) $value_m = "0". $value_m;
			if (isset($this->values[$keys[0]]) && $this->values[$keys[0]]!=''){
				
				$values_=explode(":", $this->values[$keys[0]]);
				if ($value_h=='') $value_h=$values_[0];
				if ($value_m=='') $value_m=$values_[1];
				
				//if ($value_h <10) $value_h = "0". $value_h;
				//if ($value_m <10) $value_m = "0". $value_m;
			}
			$disabled="";
			if ($this->attributes['DISABLED']!='' && $value!='') $disabled="disabled";
			$action="";
			if ($this->attributes['CALL_CF']!='') $cf_call="cf();";
			if ($this->attributes['ON_BLUR']!='') {
				$var=$this->id;
				$js_on_blur=$this->attributes['ON_BLUR'];
				$cf_call.="{$js_on_blur};";
			}
			
			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
				$alert_msg_ora="Hour not valid  ";
			else
				$alert_msg_ora="Ora non valida ";
				
			/* Nicola 11/02/2011
			 * Aggiunto isNaN
			 */
			if($this->attributes['FM_CODE']=='03')
				{
					//echo "<hr> entra aqui";
				$on_blur_h="
					if (!isNaN(this.value) && (this.value>24 || this.value<0)) 
					{
						alert('".$alert_msg_ora."');
						this.value='';
						this.focus();
						return false;
					}
					else
					{
						if(isNaN(this.value) && (this.value.toUpperCase()!='NK' && this.value.toUpperCase()!='NA'))
						{
							alert('".$alert_msg_ora."');
							this.value='';
							this.focus();
							return false;
						}
					}
				";	
				}
			else
				{
			$on_blur_h="
				if (this.value>24 || this.value<0 || isNaN(this.value)) {
					alert('".$alert_msg_ora."');
					this.value='';
					this.focus();
					return false;
				}
			";
				}
				
			
			//traduzione del messaggio di alert in inglese
			if($this->config_service['lang']=="en")
				$alert_msg_min="Minute not valid  ";
			else
				$alert_msg_min="Minuto non valido ";
				
			/* Nicola 11/02/2011
			 * Aggiunto isNaN
			 */
			if($this->attributes['FM_CODE']=='03')
				{
					$on_blur_m="
				if (!isNaN(this.value) && (this.value>60 || this.value<0)) {
					alert('".$alert_msg_min."');
					this.value='';
					this.focus();
					return false;
				}
				else
				{
					if(isNaN(this.value) && (this.value.toUpperCase()!='NK' && this.value.toUpperCase()!='NA'))
						{
							alert('".$alert_msg_min."');
							this.value='';
							this.focus();
							return false;
						}
				}
				";	
				}
			else
				{
			$on_blur_m="
				if (this.value>60 || this.value<0 || isNaN(this.value)) {
					alert('".$alert_msg_min."');
					this.value='';
					this.focus();
					return false;
				}
			";
				}
			$html_parser_h=new HTML_Parser();
			$html_parser_h->setAttribute("type", "text");
			$html_parser_h->setAttribute("maxlength", 2);
			$html_parser_h->setAttribute("size", 2);
			$html_parser_h->setAttribute("name", $this->attributes['VAR']."_H");
			$html_parser_h->setAttribute("onblur", $on_blur_h.$cf_call);
			$html_parser_h->setAttribute($disabled, "");
			$html_parser_h->setAttribute($action,"");
			$html_parser_h->setContent($value_h);
			$html_parser_h->setType("INPUT");
			$html_parser_m=new HTML_Parser();
			$html_parser_m->setAttribute("type", "text");
			$html_parser_m->setAttribute("maxlength", 2);
			$html_parser_m->setAttribute("size", 2);
			$html_parser_m->setAttribute("name", $this->attributes['VAR']."_M");
			$html_parser_m->setAttribute("onblur", $on_blur_m.$cf_call);
			$html_parser_m->setAttribute($disabled, "");
			$html_parser_m->setAttribute($action,"");
			$html_parser_m->setContent($value_m);
			$html_parser_m->setType("INPUT");
			
			/* Nicola 29/06/2010
			 * Gestione dell'attributo def
			 */
			if ($this->attributes['DEF']!=''){
				$input_def=$this->attributes['DEF'];
			}
			
			$this->input_field=$html_parser_h->print_().":".$html_parser_m->print_().$input_def;
			$this->input_txt=$txt;
		}
		
		
	}

    function open_condition($val) {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $var_cond = $val;
        $this->condition_passed = false;
        $val_cond = $this->attributes ['CONDITION_VALUE'];
        if ($this->attributes ['HIDE'] == 'yes') {
            if (preg_match("/,/", $val_cond)){
            $this->check_js.="
            if (document.getElementById('tr_".$this->id."')){
               document.getElementById('tr_".$this->id."').style.display='none';
            }
            ";
            $vals=explode(",",$val_cond);
            foreach ($vals as $key => $value){
                if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
                else $value_to_control=$inputval[$var_cond];
                if ($value_to_control==$value) {
                    $this->condition_passed=true;
                }
                $this->check_js.=" \n
                value=value_of('$var_cond', '0');
                if (value=='$value')
                {
                
                if (document.getElementById('tr_".$this->id."'))
                document.getElementById('tr_".$this->id."').style.display='';
                }
                ";
            }
            $this->check_js.="
            if (document.getElementById('tr_".$this->id."').style.display=='none'){
               
               document.forms[0].".$this->id."_H.value='';
               document.forms[0].".$this->id."_M.value='';
              
            }
            ";
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
    if (document.forms[0]." . $this->id . "_H.value!='') {$this->id}_H_val=document.forms[0]." . $this->id . "_H.value;
    if (document.forms[0]." . $this->id . "_M.value!='') {$this->id}_M_val=document.forms[0]." . $this->id . "_M.value;
    
    if (value{$op}'$val_cond')
    {

    document.forms[0]." . $this->id . "_H.value='';
    document.forms[0]." . $this->id . "_M.value='';
    ";
                //foreach ($this->values as $key => $decode) $this->check_js.=" \n  document.forms[0].".$this->id."[".($key-1)."].checked=false;";
                $this->check_js .= " \n
    if (document.getElementById('tr_" . $this->id . "'))
    document.getElementById('tr_" . $this->id . "').style.display='none';
    }
    else{
    if (typeof({$this->id}_H_val)!= \"undefined\" && {$this->id}_H_val) document.forms[0]." . $this->id . "_H.value={$this->id}_H_val;
    if (typeof({$this->id}_M_val)!= \"undefined\" && {$this->id}_M_val) document.forms[0]." . $this->id . "_M.value={$this->id}_M_val;
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
                    if (document.forms[0]." . $this->id . "_H && document.forms[0]." . $this->id . "_M )
                        {

                            document.forms[0]." . $this->id . "_H.value='';
                            document.forms[0]." . $this->id . "_M.value='';                         
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
    
    }

	function close_($value){
		global $in;
		global $inputval;
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
//  echo $txt;
//	print_r($inputval);
		
		$value_h=$inputval[$this->id."_H"];
		$value_m=$inputval[$this->id."_M"];
		//echo $value_h;
		//echo $value_m;
		if($value_h==-9922) $value_h='NK';
		if($value_h==-9911) $value_h='NA';
		if($value_m==-9922) $value_m='NK';
		if($value_m==-9911) $value_m='NA';
		
		if ($value_h <10 && is_numeric($value_h)) $value_h = "0". $value_h;
		if ($value_m <10 && is_numeric($value_m)) $value_m = "0". $value_m;
		$input_html="{$value_h}:{$value_m}";
		if ($input_html=='') $input_html='&nbsp;';
		$this->input_txt=$txt;
		$this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
		#return $ret;
	}
	
	function open_send($val){
		//echo "<li>{$this->id}</li>";
		
		$testo_js=make_js($this->input_txt);
		$fm="00";$f='';
		if ($this->attributes['FM_CODE']!='') $fm=$this->attributes['FM_CODE'];
		$this->invia_js="
				c1+='<<".$f."xp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
				c1+='<<".$f."xp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n";
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
								c1+='<<xp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
								c1+='<<xp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
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
						c1+='<<xp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<xp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n						
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {
						c1+='<<b###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<b###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
						}
				";
		}
		global $in;
		//print_r($in);
		//echo "<hr>{$in['invia']}!='' || {$in['INVIOCO']}=='1'<hr>";
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']."_H"]=='' || $in[$this->attributes['VAR']."_M"]=='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo è obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']."_H"]!='' || $in[$this->attributes['VAR']."_M"]!='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
	}

	function open_save($val){
		//echo "<li>{$this->id}</li>";
		
		$testo_js=make_js($this->input_txt);
		$fm="00";
		if ($this->attributes['FM_CODE']!='') $fm=$this->attributes['FM_CODE'];
		$this->salva_js="
				c1+='<<fxp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
				c1+='<<fxp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->salva_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<fxp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
								c1+='<<fxp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<fxp".$fm."###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<fxp".$fm."###".$this->attributes['VAR']."_M###".$testo_js.">>';\n						
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->salva_js.="
					if (!".$this->attributes['CONDITION']."_setted) {
						c1+='<<b###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<b###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
						}
				";
		}
		global $in;
		//print_r($in);
		//echo "<hr>{$in['invia']}!='' || {$in['INVIOCO']}=='1'<hr>";
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']."_H"]=='' || $in[$this->attributes['VAR']."_M"]=='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo è obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']."_H"]!='' || $in[$this->attributes['VAR']."_M"]!='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
	}
	
	function builder_js(){
		$field_description['field']="ora";
		$field_description['order']=25;
		/*$field_description['view']= <<< EOT
			"<div class='input-line'>\\n  <span class='hours'>\\n    <input type=\"text\" />\\n    <label>HH</label>\\n  </span>\\n\\n  <span class='above-line'>:</span>\\n\\n  <span class='minutes'>\\n    <input type=\"text\" />\\n    <label>MM</label>\\n  </span>\\n\\n  \\n</div>"
EOT;*/
		$this->open_('',true);
		$field_description['view']="\"<div class=\'form-group\' style=\'height:50px\'><div><label class=\'col-sm-5 control-label no-padding-right\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></label><div class='col-sm-7'>\"+
		".$this->input_field."+".
		"\"&nbsp;<%= rf.get(Formbuilder.options.mappings.DEF) %></div></div></div>\"";
		$field_description['edit'][]='edit/db_info';
		$field_description['edit'][]='edit/bytb';
		$field_description['edit'][]='edit/main_sub';
		$field_description['edit'][]='edit/condition';
		$field_description['edit'][]='edit/formatting';
		$field_description['edit'][]='edit/save_send';
		$field_description['addButton']['class']='fa fa-clock-o';
		$field_description['addButton']['label']='Time';
		
		return $field_description;
		
	}




}

?>