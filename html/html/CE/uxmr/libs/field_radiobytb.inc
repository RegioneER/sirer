<?
/**
 * @package Fields
 */

include_once "field_code_decode.inc";

class field_radiobytb extends field_code_decode{

	function open_($value){
//		global $inputval;
		global $in;
		$inputval=$this->db_vars;
		$in=$this->session_vars;
		$inputval=$this->db_vars;

		#$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$vars=explode("|", $this->attributes['VAR']);
		//echo "<hr>{$this->attributes['VARDECODE']}<hr>";
		$vardecode=explode("|", $this->attributes['VARDECODE']);
		//print_r($vardecode);
		$cols=count($vars);
		$cols++;
		$txt=$this->testo;
		$input_html='
      <table border=1 bordercolor="#fff" cellpadding=0 cellspacing=0><tr style="display:none">
      	<tr class=int>
      		<td>'.$txt.'</td>
      ';
		foreach($vardecode as $key =>$val){
			$input_html.="<td>$val</td>";
		}
		$input_html."</tr>";
		$col=0;
		foreach ($this->values as $val => $decode) {
			//echo "$val - $decode<hr>";
			$input_html.="
      		<tr>
      		";
			$col++;
			$checked="";
//			if ($inputval[$this->attributes['VAR']]==$val||$this->attributes['CHECKED']==$val) $checked="checked";
//			if ($in[$this->attributes['VAR']]==$val) $checked="checked";
			$input_html.='
      		<td class=input>'.$decode.'</td>';
			foreach($vars as $vkey =>$val_f){
				if (preg_match("/\[code\]/",$val_f)) $val_f=str_replace("[code]", $val, $val_f);
				//echo "<li>$val_f</li>";
				$array_var_{$vkey}[count($array_var_{$vkey})]=$val_f;
				$checked="";
				//echo  "<li> $val_f - {$inputval[$val_f]} - </li>";
				if ($inputval[$val_f]==$val) $checked="checked";
				if ($in[$val_f]==$val) $checked="checked";
				
				$input_html.="
			<td>
				<input type=\"radio\" value=\"{$val}\" name=\"{$val_f}\" {$checked} onclick=\"cf();\"/>
				<br><a href=\"#\" onclick=\"
					if (document.forms[0].$val_f.length) for (i=0;i<document.forms[0].$val_f.length;i++) document.forms[0].{$val_f}[i].checked=false;
					else document.forms[0].$val_f.checked=false;
					return false;
					\">(annulla)</a></td>
      		";

			}

			$input_html.="</tr>";
		}
		$this->input_field=$input_html;
		foreach($vars as $key => $val){
			$array_var_{$key}=array_unique($array_var_{$key});
		}
		foreach($array_var_{'0'} as $key => $val){
			
	    //traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning! Is not possible to select both ";
		else
			$alert_msg="Attenzione non e\\' possibile selezionare entrambe ";


			foreach ($array_var_{'1'} as $key_2=>$val_2) {
				$this->salva_js.="
				 //alert('$val - $val_2');
					if (document.forms[0].{$val}.length){
						for (i=0;i<document.forms[0].{$val}.length;i++){
							if (document.forms[0].{$val_2}.length)
							{
								for (c=0;c<document.forms[0].{$val_2}.length;c++){
									if (document.forms[0].{$val_2}[c].checked && document.forms[0].{$val_2}[c].value==document.forms[0].{$val}[i].value && document.forms[0].{$val}[i].checked) {
										alert('".$alert_msg."');
										document.forms[0].{$val_2}[c].focus();
										return false;
									}
								}
							}
							else {
							if (document.forms[0].{$val_2}.checked && document.forms[0].{$val_2}.value==document.forms[0].{$val}[i].value && document.forms[0].{$val}[i].checked) {
										alert('".$alert_msg."');
										document.forms[0].{$val_2}.focus();
										return false;
									}
							}
						}
					}
					else {
						if (document.forms[0].{$val_2}.length){
							for (c=0;c<document.forms[0].{$val_2}.length;c++){
								if (document.forms[0].{$val_2}[c].checked && document.forms[0].{$val_2}[c].value==document.forms[0].{$val}.value  && document.forms[0].{$val}.checked) {
									alert('".$alert_msg."');
									document.forms[0].{$val_2}[c].focus();
									return false;
								}
							}
						}
						else {
							if (document.forms[0].{$val_2}.checked && document.forms[0].{$val_2}.value==document.forms[0].{$val}.value  && document.forms[0].{$val}.checked) {
								alert('".$alert_msg."');
								document.forms[0].{$val_2}.focus();
								return false;
							}
						}
					}
				 ";

			}
		}
		$this->invia_js=$this->salva_js;
		//		/echo "<hr>{$this->check_js}<hr>";
	}

	function close_($value){
		global $inputval;
		global $in;
		$inputval=$this->inputval;
		$in=$this->session_var;
		#$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$vars=explode("|", $this->attributes['VAR']);
		//echo "<hr>{$this->attributes['VARDECODE']}<hr>";
		$vardecode=explode("|", $this->attributes['VARDECODE']);
		//print_r($vardecode);
		$cols=count($vars);
		$cols++;
		$txt=$this->testo;
		$input_html='
      <table border=1 bordercolor="#fff" cellpadding=0 cellspacing=0><tr style="display:none">
      	<tr class=int>
      		<td>'.$txt.'</td>
      ';
		foreach($vardecode as $key =>$val){
			$input_html.="<td>$val</td>";
		}
		$input_html."</tr>";
		$col=0;
		foreach ($this->values as $val => $decode) {
			
			$display=false;
			foreach($vars as $vkey =>$val_f){
				if (preg_match("/\[code\]/",$val_f)) $val_f=str_replace("[code]", $val, $val_f);
				if ($inputval[$val_f]==$val) $display=true;
				if ($in[$val_f]==$val) $display=true;
			
			}
			if ($display)
			$input_html.="
      		<tr>
      		";
			$col++;
			$checked="";
			//if ($inputval[$this->attributes['VAR']]==$val||$this->attributes['CHECKED']==$val) $checked="checked";
			//if ($in[$this->attributes['VAR']]==$val) $checked="checked";
			if ($display) $input_html.='
      		<td class=input>'.$decode.'</td>';
			if ($display) foreach($vars as $vkey =>$val_f){

				if (preg_match("/\[code\]/",$val_f)) $val_f=str_replace("[code]", $val, $val_f);
				$array_var_{$vkey}[count($array_var_{$vkey})]=$val_f;
				$checked="";
				if ($inputval[$val_f]==$val) $checked="checked";
				if ($in[$val_f]==$val) $checked="checked";
				if ($checked=="checked") $input_html.="
					<td><img src=\"images/checkedradio.gif\"></td>
      				";
				else $input_html.="
					<td><img src=\"images/uncheckedradio.gif\"></td>
      				";

			}

			if ($display) $input_html.="</tr>";
		}
		//$input_html.='</tr></table><br/>(<a href="#" onclick="radioclear(\''.$this->attributes['VAR'].'\'); cf(); return false">deseleziona</a>)';
		$this->input_field=$input_html;
	}

	function allinea_db(){
		$i=0;
		if ($this->attributes['TB']!='no'){
			$vars=explode("|", $this->attributes['VAR']);
			foreach ($vars as $vk => $var){
				if (preg_match("/\[code\]/", $var))
				foreach ($this->values as $key => $val){
					$var_name=str_replace("[code]", $key,$var);
					$ret[$i++]="{$var_name} NUMBER";
				}
				else $ret[$i++]="{$var} NUMBER";
			}
			return $ret;
		}
		else return ;
	}

	function insert_stmt(){
		global $in;
		$i=0;
		if ($this->attributes['TB']!='no'){
			$vars=explode("|", $this->attributes['VAR']);
			foreach ($vars as $vk => $var){
				if (preg_match("/\[code\]/", $var))
				foreach ($this->values as $key => $val){
					$var_name=str_replace("[code]", $key,$var);
					$this->field_stmt[$i]="{$var_name}";
					$this->value_stmt[$i]=$in[$var_name];
					$i++;
				}
				else {
					$this->field_stmt[$i]="{$var}";
					$this->value_stmt[$i]=$in[$var];
					$i++;
				}
			}
			//print_r($in);
			//die();
			return $ret;
		}
		return;
	}

	function open_mandatory_var($value){
		global $in;
		//echo "<hr>$value mandatory on send $value - {$in['MC']}<hr>";
		//print_r($in);
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($in[$value]==''){
				global $insert_errors;
				$this->validata=false;
				$insert_errors[$value]='Selezione obbligatoria';
			}
		}
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning!! It's necessary to select a Main Change ";
		else
			$alert_msg="Attenzione!!! E\' necessario selezionare una Main Change ";
			
		$this->invia_js="
			c=0;
			for (i=0;i<document.forms[0].$value.length;i++){
				if (document.forms[0].{$value}[i].checked) c++;
			}
			if (c!=1) {
				alert('".$alert_msg."');
				document.forms[0].{$value}[0].focus();
				return false;
			}
			//alert (c);
		";
	}
	
	
		function XML_OUTPUT($values){
		
			//da fare
		return "";
	}
}


?>