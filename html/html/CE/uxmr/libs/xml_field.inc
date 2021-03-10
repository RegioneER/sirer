<?

###class field###
/*
<b>Autore Carlo Contino</b>
    Data 26/04/2006
    Questa libreria è costruita sul prototipo di form xml concepito e utilizzato per il servizio di Protocol Development;
    quindi un file xml con struttura radicalmente diversa da tale prototipo risulta inutilizzabile.
    Per trovare i riferimenti sulla struttura xml dei file di form leggere il documento "<a href='/docs/struttura_xml.htm' target='blank'>Struttura file di configurazione</a>" presente nell'area documentale

    <b>Sintassi costruttore:</b>
        $nome_oggetto=new <b>field</b>($xml_form_field as xml_form object, $i as integer)
    <b>Variabili:</b>
        <b>$attributes:</b> attributi del campo field;
        <b>$values:</b>Valori del campo;
        <b>$testo:</b>Testo;
        <b>$salva js:</b>Stringa controlli javascript;
        <b>$invia_js:</b>Stringa controlli javascript;
        <b>$check:js:</b>Stringa controlli javascript;
        <b>$html:</b>Stinga codice html;
        <b>$validata:</b>Mi indicata se i valori passati tramite GET o POST rispettano i controlli;
    <b>Metodi:</b>
        <b>field($xml_form as xml_form object, $i as integer) as void:</b>   inizializza le variabili interne leggendo il contenuto dell'oggetto xml_form a l'indice del field realtivo;
        <b>open_tipocampo($value as mixed) as string:</b> Restituisce il codice HTML relativo al campo in compilazione;
        <b>open_tipocampo_CONDITION($val as mixed) as void:</b> Restituisce il codice javascript per la visualizzazione a scomparsa in base al campo condizionante;
        <b>open_tipocampo_salva() as void:</b>Restituisce il codice javascript per i controlli form manager (salvataggio);
        <b>open_tipocampo_invia() as void:</b>Restituisce il codice javascript per i controlli form manager (invio);

*/
###endclass###

class field{

    var $attributes;
    var $cols_form;
    var $values;
    var $testo;
    var $salva_js;
    var $invia_js;
    var $check_js;
    var $html;
    var $input_txt;
    var $input_field;
    var $controlli;
    var $validata=true;
    var $xml_form;

###sub field($xml_formas xml_form object, $i as integer) as void###
    function field($xml_form,$i){
    	$this->xml_form=$xml_form;
        $this->cols_form=$xml_form->form['COLS'];
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
//        if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
    }
###endsub###

###sub open_field() as string###
    function open_field(){
        $function_to_call='open_'.$this->attributes['TYPE'];
        global $in;
        global $inputval;
        if (isset($this->values) and !is_array($this->values)) $value=$this->values;
        if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
        if (isset($in[$this->attributes['VAR']])) $value=$in[$this->attributes['VAR']];
        if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
        if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
        $cols=$this->attributes['COLS']+0;
        if ($cols==0) $cols=1;

        #Tag field con definizione mancante di tipologa=>deve essere stampato solo il valore testuale#

        #se la tipologia è hidden creo un TR non visualizzabile#
        if ($this->attributes['TYPE']=='hidden') $this->html='<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';
        # Per ogni attributo chiamo la funzione apposita (open_{tipologia campo}_{nome attributo})#
        if (count($this->attributes)>0) foreach($this->attributes as $key => $val){
        	$function_to_call='open_'.$this->attributes['TYPE']."_".$key;
        	if (method_exists($this,$function_to_call)) $this->{$function_to_call}($val);
        }
        if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
        	$colspan=$cols*$this->attributes['COLSPAN'];
        	if ($this->input_field=='') $this->html=$this->input_txt;
        	else $this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.$this->input_field.'</td>';
        }
        else
        	#Se è presente una tipologia diversa da hidden creo la cella#
        	{
        		if ($this->input_txt!='') $this->input_txt.=":";
        		if ($this->attributes['TYPE']!='hidden') $this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
        	}
        #Aggiungo le stringe di controlli javascript relativa al campo in questione#
        if ($this->attributes['TYPE']=='data' && $this->salva_js=='')
        {
			  $dcod='00';
			  if ($this->attributes['DCONT']=='yes') $dcod='16';
        $this->salva_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
			  }
			  if ($this->attributes['TYPE']=='data' && $this->invia_js=='')
			  {
			  $dcod='00';
			  if ($this->attributes['DCONT']=='yes') $dcod='16';
			  $this->invia_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
        }
    }
###endsub###

###sub close_field() as string###
    function close_field(){
//        if (isset($this->attributes['VAR'])) $this->html='<tr id='.$this->attributes['VAR'].' style="display:">';
//        else $this->html='<tr>';
        $function_to_call='close_'.$this->attributes['TYPE'];
        global $in;
        global $inputval;
        if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
        if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
        if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
        $cols=$this->attributes['COLS']+0;
        if ($cols==0) $cols=1;
        #Tag field con definizione mancante di tipologa=>deve essere stampato solo il valore testuale#
        if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
        	$colspan=$cols*$this->attributes['COLSPAN'];
        	if ($this->input_field=='') $this->html=$this->input_txt;
        	else $this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.":".$this->input_field.'</td>';
        }
        else
        	#Se è presente una tipologia diversa da hidden creo la cella#
//        	if($this->attributes['HIDEVIS']=='yes') $this->attributes['HIDE']='yes' ;
        	if ($this->attributes['TYPE']!='hidden') {
        		if ($this->input_txt!='') $this->input_txt.=':';
       		if (($this->attributes['HIDE']!='yes'&&$this->attributes['HIDEVIS']!='yes') || ($inputval[$this->attributes['VAR']]!='' || $inputval[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))
        		 $this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
        	}
        #se la tipologia è hidden creo un TR non visualizzabile#
        if ($this->attributes['TYPE']=='hidden') $this->html='';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';
        #$this->html=$input_html;
    }
###endsub###


###sub fields_value_bytb() as VOID###
function fields_value_bytb($value){
	$code=$this->attributes['BYTBCODE'];
	$decode=$this->attributes['BYTBDECODE'];
	$where=$this->attributes['BYTBWHERE'];
	$where=str_replace("min_of","<",$where);
	$where=str_replace("max_of",">",$where);
	if (!preg_match("/ana_utenti/i",$value))	$value=$GLOBALS['service']."_".$value;
	if(preg_match_all("/\[(.*?)\]/e",$where,$matches))
	{
		Logger::send("matches");
		Logger::send($matches);
		//$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
	}
	else{
	Logger::send("sdasdasd");	
	}

	//$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
	$decode=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $decode );
	//$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
	$code=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $code );
	global $conn;
	if ($where!='') $where="where $where";
	$query="select $code as code";
	if ($decode!='') $query.=", $decode as decode";
	$query.=" from $value $where order by decode asc";
	$sql=new query($conn);
	$sql->set_sql($query);
	$sql->exec();//obsoleto trovare dove testare
	#echo "<hr>$query";
	while ($sql->get_row()) {
		if ($decode!='') $this->values[$sql->row['CODE']]=$sql->row['DECODE'];
		else {
			global ${$this->attributes['BYVAR']};
			$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
		}
	}
	#print_r($this->values);
}
###endsub###


############################
# 			HIDDEN     			 #
############################

	function open_hidden_rand($value){
		#echo "<hr>$value - {$this->attributes['RAND_VAR']}<hr>";
		$value-=1;
		$this->invia_js.="
			if (value_of('{$this->attributes['RAND_VAR']}')=='1') document.forms[0].{$this->attributes['VAR']}.value=Math.round({$value}*Math.random())+1;
			//alert ( document.forms[0].{$this->attributes['VAR']}.value);
			//return false;
		";
	}

	function open_hidden_compila($value){
		$condition_var=$this->attributes['COMPILA_CONDITION_VAR'];
		$condition_val=$this->attributes['COMPILA_CONDITION_VALUE'];
		$operatore=$this->attributes['COMPILA_OP'];
    $operatore=str_replace("AND","&&",$operatore);
//echo "$operatore<hr>";
		$vars=explode("|", $condition_var);
		$valuess=explode("|", $condition_val);
//		print_r($vars);
//		print_r($valuess);
		foreach ($vars as $key=> $var){
			$valore_var.="value_{$var}=value_of('{$var}','0');\n";
			$values=explode(",",$valuess[$key]);
			$condizioni="";
//			print_r($values);
			foreach ($values as $kv=>$val) {
				if ($condizioni!='') $condizioni.=" || ";
				$condizioni.="value_{$var}=='{$val}'";
//				echo "$condizioni<hr>";
			}
			if ($condizioni_tot!='') $condizioni_tot.=" $operatore ";
			$condizioni_tot.="($condizioni)";
		}
		$js_cond="
		$valore_var
		if ($condizioni_tot) document.forms[0].{$this->attributes['VAR']}.value='$value';
		else document.forms[0].{$this->attributes['VAR']}.value='';
//		alert(document.forms[0].{$this->attributes['VAR']}.value);
		";
		$this->check_js.=$js_cond;
	}

	function open_hidden_controll($value){
		$param=explode("=",$value);
		$vars=$param[0];
		$vals=$param[1];
		$vars=explode(",",$vars);
		$vals=explode(",",$vals);
		for ($i=0;$i<count($vars);$i++){
			if ($check!='') $check.=" && ";
			$check.="document.forms[0].{$vars[$i]}.value=='{$vals[$i]}'";
		}
		$this->invia_js.="
			document.forms[0].{$this->attributes['VAR']}.value='0';
			if ($check) document.forms[0].{$this->attributes['VAR']}.value='1';
			//alert (document.forms[0].{$this->attributes['VAR']}.value);
			//return false;
			";
	}

###sub open_hidden($value as mixed) as string###
    function open_hidden($value){
    	global $inputval;
    	global $in;
//    echo $this->attributes['VAR'].":".$value."<hr>";
   	if ($value=='sysdate'){
    		$value=date("dmY");
    	}
    		if ($value=='') {
    			if (count($this->values)>0)
    				foreach($this->values as $key => $val) {
	    				$value=$key;
	    				$inputval[$this->attributes['VAR']]=$value;
	    				#echo "<hr> ".$this->attributes['VAR']." ==$value";
	    			}
    			}
    			if ($in[$this->attributes['VAR']]!='') $value=$in[$this->attributes['VAR']];
    		#	echo $this->attributes['VAR']." - $value<hr>";
       if (isset($in['TB_COLL']) && $in['TB_COLL']!='') $this->input_field='<input type="hidden" name="TB_COLL_'.$in['ID_REF'].'_'.$this->attributes['VAR'].'" value="'.$value.'"/>';
       else $this->input_field='<input type="hidden" name="'.$this->attributes['VAR'].'" value="'.$value.'"/>';

    }
###endsub###
	function open_hidden_sum($val){
			global $in;
			$campi=explode(",",$val);
			$minval=$this->attributes['SUM_MAGGIORE']+0;
			$maxval=$this->attributes['SUM_MINORE']+0;
			$check="if (value >= $minval)";
			if ($maxval>0) $check="if (value >= $minval && value <= $maxvalue)";
			$somma=0;
			for ($i=0;$i<count($campi);$i++){
				if ($i==0) $this->check_js.=" \n
					document.forms[0].".$this->attributes['VAR'].".value='';
				";
				if (preg_match("/\[/",$campi[$i])){
					//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
					$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i] );
					$somma+=$in[$campo];
					$this->check_js.="
						value=value_of('".$campo."', '0');
						value=value-0;
						//alert (value);
						";
						}
					else {
						$somma+=$campi[$i];
						$this->check_js.="
						value=".$campi[$i].";
						";
					}
					$this->check_js.="
						$check {
						somma=document.forms[0].".$this->attributes['VAR'].".value - 0;
						somma+=value;
						document.forms[0].".$this->attributes['VAR'].".value=somma;
						}
					";
				}
				$in[$this->attributes['VAR']]=$somma;
			}

			function open_hidden_dividendo($val){
			global $in;
			$dividendo=$this->attributes['DIVIDENDO'];
				if (preg_match("/\[/", $dividendo)) {
					//$dividendo=preg_replace("/\[(.*?)\]/e", "$1" , $dividendo);
					$dividendo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $dividendo );
					$this->check_js.="
				value=value_of('$dividendo', '0');
				value=value-0;
					";
					$dividendo=$in[$dividendo]+0;
				}
				else $this->check_js.="
				value=$dividendo;
				";
			$divisore=$this->attributes['DIVISORE'];
			#echo "<hr>$divisore<hr>";
				if (preg_match("/\[/", $divisore)) {
					//$divisore=preg_replace("/\[(.*?)\]/e", "$1" , $divisore);
					$divisore = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $divisore );
					$this->check_js.="
				divisore=value_of('$divisore', '0');
				divisore=divisore-0;
					";
					$divisore=$in[$divisore]+0;
				}
				else $this->check_js.="
				divisore=$divisore;
				";
			$this->check_js.=" \n
				//value=value_of('$dividendo', '0');
				//value=value-0;
				valore=value/divisore;

				if (isNaN(parseInt(valore)) || isNaN(valore)) valore=0;
				//alert (valore);
				document.forms[0].".$this->attributes['VAR'].".value=valore;
				";
				$valore=$dividendo/$divisore;
				$in[$this->attributes['VAR']]=$valore;
		}


############################
# 			TUMOR_SIZE   			 #
############################

function open_tumor_size($value){
	global $in;
	$txt=$this->testo;
	$input_html="<input type=\"text\" name=\"{$this->attributes['VAR']}1\" value=\"$val_1\" size=\"3\"/>x<input type=\"text\" name=\"{$this->attributes['VAR']}2\" value=\"$val_1\" size=\"3\"/>x<input type=\"text\" name=\"{$this->attributes['VAR']}3\" value=\"$val_1\" size=\"3\"/>=<input type=\"text\" name=\"{$this->attributes['VAR']}4\" value=\"$val_1\" size=\"3\"/>";
	$this->input_txt=$txt;
	$this->input_field=$input_html;
}

function close_tumor_size($value){
	global $in;
	$txt=$this->testo;
	#$vals="{$in[$this->attributes['VAR']}.'1']}x${in[$this->attributes['VAR']}.'2']}x{$in[$this->attributes['VAR']}.'3']}={$in[$this->attributes['VAR']}.'4']}";
	$input_html='<b><i><font color="#333300"><span class="textfield">'.$vals.'</span></font></i></b>';
	$this->input_txt=$txt;
	$this->input_field=$input_html;
}

function open_file($value){
	global $in;
	global $inputval;
	$file_uploaded="";
  if ($value!=''){
  	 $file_name=$inputval['D_'.$this->attributes['VAR']];
  	 $file_uploaded="<br>Download file: <a href=\"download.php?nome_file=$file_name&nome_real_file=$value\">$file_name</a>";
  	}
	$txt=$this->testo;
	$input_html="<input type=\"file\" name=\"{$this->attributes['VAR']}\"/>$file_uploaded";
	$this->input_txt=$txt;
	$this->input_field=$input_html;
}

function close_file($value){
	global $in;
	global $inputval;
	$file_uploaded="";
  if ($value!=''){
  	 $file_name=$inputval['D_'.$this->attributes['VAR']];
  	 $file_uploaded="Download file: <a href=\"download.php?nome_file=$file_name&nome_real_file=$value\">$file_name</a>";
  	}
	$txt=$this->testo;
	$input_html="$file_uploaded";
	$this->input_txt=$txt;
	$this->input_field=$input_html;
}

############################
# 			TIME		     			 #
############################

	function open_time($value){
		 if ($inputval[$this->attributes['VAR'].'_H']!='') $valueH=$inputval[$this->attributes['VAR'].'_H'];
     if ($in[$this->attributes['VAR'].'_H']!='') $valueH=$in[$this->attributes['VAR'].'_M'];
     if ($inputval[$this->attributes['VAR'].'_M']!='') $valueM=$inputval[$this->attributes['VAR'].'_M'];
     if ($in[$this->attributes['VAR'].'_M']!='') $valueM=$in[$this->attributes['VAR'].'_M'];
     $this->input_txt=$this->testo;
     $this->input_field="<input type=\"text\" name=\"{$this->attributes['VAR']}_H\" value=\"$valueH\" size=\"2\"/>:<input type=\"text\" name=\"{$this->attributes['VAR']}_M\" value=\"$valueM\" size=\"2\"/>";
	}

	function close_time($value){
		 if ($inputval[$this->attributes['VAR'].'_H']!='') $valueH=$inputval[$this->attributes['VAR'].'_H'];
     if ($in[$this->attributes['VAR'].'_H']!='') $valueH=$in[$this->attributes['VAR'].'_M'];
     if ($inputval[$this->attributes['VAR'].'_M']!='') $valueM=$inputval[$this->attributes['VAR'].'_M'];
     if ($in[$this->attributes['VAR'].'_M']!='') $valueM=$in[$this->attributes['VAR'].'_M'];
     $this->input_txt=$this->testo;
     $this->input_field="<b>$valueH:$valueM</b>";
	}


############################
# 			TEXTBOX     			 #
############################

###sub open_textbox($value as mixed) as string###
    function open_textbox($value){
    		global $in;
        $txt=$this->testo;
        if ($this->attributes['CHECK']=='') $this->attributes['CHECK']="text";
        #echo "<hr>CHECK {$this->attributes['CHECK']} - <hr>";
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CHECK']=='text') {
        		if ($in[$this->attributes['VAR']]=='') {
        			#echo "<hr>CAMPO VUOTO<hr>";
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Error!!!Field can't be blank</font>";
        		}
        	}
        	if ($this->attributes['CHECK']=='number') {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Error!!!Field must be numeric</font>";
        	}
        }
         if ($in['salva']!='' && $this->attributes['SEND']=='obbligatorio' && $this->attributes['CONDITION']!=''&& $in[$this->attributes['CONDITION']]!=$this->attributes['CONDITION_VALUE'] && $in[$this->attributes['VAR']]!=''){
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere vuoto</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $this->attributes['CONDITION']!=''&& $in[$this->attributes['CONDITION']]!=$this->attributes['CONDITION_VALUE'] && $in[$this->attributes['VAR']]!=''){
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere vuoto</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CHECK']=='text') {
        		if ($in[$this->attributes['VAR']]=='') {
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Error!!!Field can't be blank</font>";
        		}
        	}
        	if ($this->attributes['CHECK']=='number' && !is_numeric($in[$this->attributes['VAR']])) {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Error!!!Field must be numeric</font>";
        	}
        }
        #print_r($this->values);
        if ($this->attributes['SIZE']=='') $this->attributes['SIZE']='20';
        foreach ($this->values as $key => $val) $value=$val;
        if ($inputval[$this->attributes['VAR']]!='') $value=$inputval[$this->attributes['VAR']];
        if ($in[$this->attributes['VAR']]!='') $value=$in[$this->attributes['VAR']];
        $disabled="";
        if ($this->attributes['DISABLED']!='') $disabled="disabled";
        $action="";
//        echo "{$this->attributes['ON_ACTION']}<hr>";
        if ($this->attributes['ON_ACTION']!='' && $this->attributes['ACTION_TYPE']!='') {
        $action=$this->attributes['ACTION_TYPE']."=\"".$this->attributes['ON_ACTION']."\"";
//         echo "$action<hr>";
        }

        if ($in['USER_TIP']!='DE' and $this->attributes['CRYPTO']=='yes') $this->input_field='***<input type="hidden" name="'.$this->attributes['VAR'].'"  value="'.$value.'"/>';
        else {
        	if ($this->attributes['EMAIL']!='') {
        		$val_email=explode("@",$value);
        		$this->input_field="<input type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
        	}
        	else
        	 {
//          echo "$action<hr>";
       	  $this->input_field='<input  type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" size="'.$this->attributes['SIZE'].'" name="'.$this->attributes['VAR'].'" value="'.$value.'" onblur="cf()" '. $disabled. $action.'>'.$this->attributes['DEF'].'';
           }
        	}
        $this->input_txt=$txt;
        if ($this->attributes['TEXTONLY']=="yes") {
        		$this->input_txt=$value;
        		$this->input_field='';
        }
      }
###endsub###
     function open_text($value){
    		global $in;
        $txt=$this->testo;
        foreach ($this->values as $key => $val) $value=$val;
        $this->input_field="<b>".$value."</b>";
        $this->input_txt=$txt;
    }


		function open_text_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
		 if ($this->attributes['HIDE']=='yes') {
				$this->check_js.="
 			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
					value=value_of('$var_cond', '0');
					if (value=='$val_cond')
					{
			  	if (document.getElementById('".$this->attributes['VAR']."'))
							document.getElementById('".$this->attributes['VAR']."').style.display='';
					}
						";
			}
		}






		function open_textbox_sfoglia($value){
			$tip_sfo=explode(";",$value);
      for ($f=0;$f<count($tip_sfo);$f++){
//         echo "$f--$tip_sfo[$f]<hr>";
       $but=explode(",",$tip_sfo[$f]);
        $but_text=$but[0];$but_file=$but[1];
        if ($but_text=='cancella')
	      $agg="&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
        else
	      $agg="&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
//         echo "$but_text -- $but_file<hr>";
			 $this->input_field.=$agg;
		}
}

		function open_textbox_disabled($value){
			$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".disabled=true;
			";
		}

		function open_textbox_on_change($value){
			$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".value=document.forms[0].".$this->attributes['VAR'].".value.".$value.";";
		}

		function open_textbox_execute($value){
			$this->check_js.="
      $value".";";
 		}


###sub open_textbox_CONDITION($val) as void###
		function open_textbox_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
		if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
        valore=document.forms[0].".$this->attributes['VAR'].".value;
				document.forms[0].".$this->attributes['VAR'].".value='';
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
				";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');
					if (value=='$value')
					{
			  	if (document.getElementById('".$this->attributes['VAR']."'))
							document.getElementById('".$this->attributes['VAR']."').style.display='';
					    document.forms[0].".$this->attributes['VAR'].".value=valore;

					}
						";
			}
			else {
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					#echo "<hr>$val_cond";
					$val_cond=str_replace("!", "",$val_cond);
					#echo "<hr>$val_cond";
					$op='==';
				}
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value $op '$val_cond')
				{
					";
//				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
				$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".value='';
			  if (document.getElementById('".$this->attributes['VAR']."'))
				   document.getElementById('".$this->attributes['VAR']."').style.display='none';
				}
				else
			  if (document.getElementById('".$this->attributes['VAR']."'))
				  document.getElementById('".$this->attributes['VAR']."').style.display='';
				";
			}
		}
			else $this->check_js.="
			if (document.getElementById('".$this->attributes['VAR']."'))
				document.getElementById('".$this->attributes['VAR']."').style.display='';";
			$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:\">".$this->html."</tr>";
		}
###endsub###

		function open_textbox_min($val){
			if (preg_match("/\[/",$campi[$i])){
					//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
					$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i]);
					$this->invia_js.="
						value=value_of('".$campo."', '0');
						";
				}
			else {
				$this->invia_js.="value=$val;\n";
			}
		$this->invia_js.="
				if (document.forms[0].".$this->attributes['VAR'].".value<=value) {
					alert('Attenzione il valore deve essere maggiore di '+value);
					document.forms[0].".$this->attributes['VAR'].".focus();
					return false;
				}
		";
		}

		function open_textbox_equals($val){
			$t=str_replace("*", "",$this->testo);
			$this->invia_js.="value=$val;\n";
			$this->invia_js.="
				if (document.forms[0].".$this->attributes['VAR'].".value!=value) {
					alert('{$t} deve essere '+value);
					document.forms[0].".$this->attributes['VAR'].".focus();
					return false;
				}
		";

		}

		function open_textbox_max($val){
			if (preg_match("/\[/",$campi[$i])){
					//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
					$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i] );
					$this->invia_js.="
						value=value_of('".$campo."', '0');
						";
				}
			else {
				$this->invia_js.="value=$val;\n";
			}
		$this->invia_js.="
				if (document.forms[0].".$this->attributes['VAR'].".value>value) {
					alert('Attenzione il valore deve essere minore di '+value);
					document.forms[0].".$this->attributes['VAR'].".focus();
					return false;
				}
		";
		}

###sub open_textbox_CONDITION($val) as void###
		function open_textbox_sum($val){
			global $in;
			$campi=explode(",",$val);
			$minval=$this->attributes['SUM_MAGGIORE']+0;
			$maxval=$this->attributes['SUM_MINORE']+0;
			$check="if (value >= $minval)";
			if ($maxval>0) $check="if (value >= $minval && value <= $maxvalue)";
			$somma=0;
			for ($i=0;$i<count($campi);$i++){
				if ($i==0) $this->check_js.=" \n
					document.forms[0].".$this->attributes['VAR'].".value='';
				";
				if (preg_match("/\[/",$campi[$i])){
					//$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
					$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi[$i] );
					$somma+=$in[$campo];
					$this->check_js.="
						value=value_of('".$campo."', '0');
						value=value-0;
						//alert (value);
						";
						}
					else {
						$somma+=$campi[$i];
						$this->check_js.="
						value=".$campi[$i].";
						";
					}
					$this->check_js.="
						//$check {
						somma=document.forms[0].".$this->attributes['VAR'].".value - 0;
						somma+=value;
						document.forms[0].".$this->attributes['VAR'].".value=somma;
						//}
					";
				}
				$in[$this->attributes['VAR']]=$somma;
			}

###endsub###

###sub open_textbox_CONDITION($val) as void###
		function open_textbox_dividendo($val){
			global $in;
			$dividendo=$this->attributes['DIVIDENDO'];
				if (preg_match("/\[/", $dividendo)) {
					//$dividendo=preg_replace("/\[(.*?)\]/e", "$1" , $dividendo);
					$dividendo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $dividendo );
					$this->check_js.="
				value=value_of('$dividendo', '0');
				value=value-0;
					";
					$dividendo=$in[$dividendo]+0;
				}
				else $this->check_js.="
				value=$dividendo;
				";
			$divisore=$this->attributes['DIVISORE'];
			#echo "<hr>$divisore<hr>";
				if (preg_match("/\[/", $divisore)) {
					//$divisore=preg_replace("/\[(.*?)\]/e", "$1" , $divisore);
					$divisore = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $divisore );
					$this->check_js.="
				divisore=value_of('$divisore', '0');
				divisore=divisore-0;
					";
					$divisore=$in[$divisore]+0;
				}
				else $this->check_js.="
				divisore=$divisore;
				";
			$this->check_js.=" \n
				//value=value_of('$dividendo', '0');
				//value=value-0;
				valore=value/divisore;
				document.forms[0].".$this->attributes['VAR'].".value=valore;
				";
				$valore=$dividendo/$divisore;
				$in[$this->attributes['VAR']]=$valore;
		}
###endsub###

###sub open_textbox_salva($val as mixed) as void###
		function open_textbox_save($val){
//				echo "<hr> controllo textbox {$this->testo}";
//echo "<hr> controllo textbox {$this->attributes['VAR_TYPE']}";
//echo "<hr> controllo textbox {$this->attributes['VAR_STYPE']}";
		if ($this->attributes['VAR_TYPE']=='text')
			$controllo="t";
			else
			{
			 if ($this->attributes['FM_CODE'])
			  $fm=$this->attributes['FM_CODE'];
			 else
			  $fm="00";
			if ($this->attributes['VAR_STYPE']=='int')
			 $controllo="np".$fm;
			else
			 $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
			}
			$testo_js=make_js($this->testo);
			if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||$this->attributes['VAR_TYPE']!='text'){
				$this->salva_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
			}
			if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
				$this->salva_js="
				if (document.forms[0].".$this->attributes['CONDITION'].".value=='".$this->attributes['CONDITION_VALUE']."') c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
			}
		}
###endsub###

###sub open_textbox_invia($val as mixed) as void###
		function open_textbox_send($val){
//			echo "<hr> controllo textbox {$this->testo}";
			if ($this->attributes['VAR_TYPE']=='text')
			$controllo="t";
			else
			{
			 if ($this->attributes['FM_CODE'])
			  $fm=$this->attributes['FM_CODE'];
			 else
			  $fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			 $controllo="np".$fm;
			else
			 $controllo="xp".$fm;
			}
			#echo "<hr> controllo textbox {$this->testo}";
			$testo_js=make_js($this->input_txt);
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
//echo "$oper<br>";
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
			#echo "<hr>$this->invia_js";
		}
###endsub###

###sub open_textbox_invia($val as mixed) as void###
		function open_textarea_send($val){
			$controllo="t";
			#echo "<hr> controllo textbox {$this->testo}";
			$testo_js=make_js($this->input_txt);
		  $this->invia_js="
				c1+='<<t###".$this->attributes['VAR']."###".$testo_js.">>';\n";
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
				else $this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
				$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) document.forms[0].".$this->attributes['VAR'].".value='';
				";
			}
			#echo "<hr>$this->invia_js";
		}
###endsub###

      function close_text($value){
    		global $in;
        $txt=$this->testo;
        if (isset($this->values)) foreach ($this->values as $key => $val) $value=$val;
        if ($value=='') $value="n.d.";
        $this->input_field="<b>".$value."</b>";
        $this->input_txt=$txt;
    }

###sub close_textbox($value as mixed) as string###
    function close_textbox($value){
    		global $in;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['USER_TIP']!='DE' and $this->attributes['CRYPTO']=='yes') $input_html='***';
        else $input_html=$value;
        if ($input_html=='') $input_html='&nbsp;';
        $this->input_txt=$txt;
        $this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
        #return $ret;
    }
###endsub###

############################
# 			RADIO     			 #
############################


###sub close_radio($value as mixed) as string###
   function close_radio($value){
	  global $inputval;
	  $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
	  $cols=$this->attributes['SUBTBCOL'];
      $txt=$this->testo;
      $input_html='
      <table border=0 cellpadding=0 cellspacing=0><tr style="display:none"><td colspan="'.$cols.'">&nbsp;</td>
      ';
      $col=0;
      $input_html='
      <table border=0 cellpadding=3 cellspacing=0><tr style="display:none"><td colspan="'.$cols.'">&nbsp;</td>
      ';
      foreach ($this->values as $val => $decode) {
      		if ($col==$cols) $col=0;
      		if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
      		$col++;
      	  $checked="";
      		if ($inputval[$this->attributes['VAR']]=="$val") {
      			$checked="checked";
      		}
      		if ($in[$this->attributes['VAR']]=="$val") {
      			$checked="checked";#echo "<hr>".$inputval[$this->attributes['VAR']]." - ".$in[$this->attributes['VAR']]." - $val";
      		}
      		if ($checked=='checked') {
      			$input_html.="<td><img src='/images/checkedradio.gif'>";
      		}
      		else $input_html.="<td><img src='/images/uncheckedradio.gif'>";
      		$input_html.=$decode."</td>";
      	}
      	$input_html.="</table>";
      $this->input_txt=$txt;
      $this->input_field=$input_html;
      if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
      else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';
      #return $ret;
		}
###endsub###

###sub open_radio($value as mixed) as string###
		function open_radio($value){
			global $inputval;
			global $in;
			#$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
			$cols=$this->attributes['SUBTBCOL'];
      $txt=$this->testo;
      $input_html='
      <table border=0 cellpadding=0 cellspacing=0><tr style="display:none"><td colspan="'.$cols.'">&nbsp;</td>
      ';
      $col=0;
      foreach ($this->values as $val => $decode) {
      		#echo "$val - $decode";
      		if ($col==$cols) $col=0;
      		if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
      		$col++;
      	  $checked="";
      		if ($inputval[$this->attributes['VAR']]==$val||$this->attributes['CHECKED']==$val) $checked="checked";
      		if ($in[$this->attributes['VAR']]==$val) $checked="checked";
      		$input_html.='
      		<td><input type="radio" value="'.$val.'" name="'.$this->attributes['VAR'].'" '.$checked.' onclick="cf();"/>'.$decode.'&nbsp;</td>';
      	}
      $input_html.='</tr></table><br/>(<a href="#" onclick="radioclear(\''.$this->attributes['VAR'].'\'); cf(); return false">deseleziona</a>)';
      $this->input_field=$input_html;
      $this->input_txt=$txt;
		}
###endsub###


###sub open_radio_disabled($val) as void###
		function open_radio_disabled($value){
			$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".disabled=true;
			";
		}
###endsub###

###sub open_radio_CONDITION($val) as void###
		function open_radio_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
					";
				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
				$this->check_js.=" \n
			  if (document.getElementById('".$this->attributes['VAR']."'))
				  document.getElementById('".$this->attributes['VAR']."').style.display='none';
				}
				else
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='';
				";
			}
			else $this->check_js.="
			if (document.getElementById('".$this->attributes['VAR']."'))
				document.getElementById('".$this->attributes['VAR']."').style.display='';";
			$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:none\">".$this->html."</tr>";
		}
###endsub###

###sub open_radio_invia($val) as void###
		function open_radio_send($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($this->input_txt);
			  #echo "$testo_js";
			  if ($this->attributes['CONDITION']!='') {
			  	$var_cond=$this->attributes['CONDITION'];
			  	$val_cond=$this->attributes['CONDITION_VALUE'];
			  	$this->invia_js="
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->invia_js="c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub open_radio_salva($val) as void###
		function open_radio_save($val){
			if ($val=='obbligatorio')
			  $testo=$this->input_txt;
			  $testo_js=make_js($this->input_txt);
			  if ($this->attributes['CONDITION']!='') {
			  	$var_cond=$this->attributes['CONDITION'];
			  	$val_cond=$this->attributes['CONDITION_VALUE'];
			  	$this->salva_js="
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->salva_js="c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###


############################
# 			SELECT     			 #
############################

###sub open_select($value as mixed) as string###
    function open_select($value){
    	  global $in;
    	  global $inputval;
    	  #echo "<hr> {$inputval['COUNTRY_ORGANIZATION']} - {$this->attributes['VAR']}";
//    	 print_r($inputval);
    	  $optgroup=false;
        #$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        #echo "<hr>$txt";
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Error!!!Make a selection</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $in[$this->attributes['VAR']]==''  && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Error!!!Make a selectiona</font>";
        }
        $submit="";
        if ($this->attributes['SUBMIT']!='') $submit="submit();";
        $onchange="";
         if ($this->attributes['ONCHANGE']!='') $onchange="{$this->attributes['ONCHANGE']};";
        $action="";
//        echo "{$this->attributes['ON_ACTION']}<hr>";
        if ($this->attributes['ON_ACTION']!='' && $this->attributes['ACTION_TYPE']!='') {
        $action=$this->attributes['ACTION_TYPE']."=\"".$this->attributes['ON_ACTION']."\"";
//         echo "$action<hr>";
        }

         if (isset($in['TB_COLL']) && $in['TB_COLL']!='')  $input_html='<select name="TB_COLL_'.$in['ID_REF'].'_'.$this->attributes['VAR'].'" onchange="cf();'.$submit.$onchange.'"'.$action.'><option value="">&nbsp;</option>';
				 else $input_html='<select name="'.$this->attributes['VAR'].'" onchange="cf();'.$submit.$onchange.'"'.$action.'><option value="">&nbsp;</option>';
				foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
//        		echo $txt.' -- '.$val.' - '.$this->attributes['VAR'].' - '.$in[$this->attributes['VAR']]."<hr>";
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if (preg_match("/optgroup/",$val))
        			{
        				$optgroup=true;
        				if ($options!='') $options.="
        				</optgroup>";
        				$options.='
        				<optgroup label="'.$decode.'">';
        			}
        		else $options.='
        				<option value="'.$val.'" '.$selected.'>'.$decode.'</option>';
        	}
        	if ($optgroup) $options.="</optgroup>";

        $input_html.=$options.'</select><input type="hidden" name="D_'.$this->attributes['VAR'].'"/>';
        $this->input_field=$input_html."&nbsp;".$this->attributes['DEF'];
        //echo $this->input_field."<hr>";
        $this->input_txt=$txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td>';
        #return $ret;
    }
###endsub###

###sub close_select($value as mixed) as string###
    function close_select($value){
    	  global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='') {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Error!!!Make a selection</font>";
        }
        foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - in ".$in[$this->attributes['VAR']]." - inputval ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($selected=='selected') $input_html.='<b><i><u><font color="#333300" size="2"><span class="selectedOption">'.$decode.'</span></font></u></i></b><br>';
        		else if ($this->attributes['SHOW_SELECTED']=='') $input_html.='<font color="#005dce" size="1"><span class="unselectedOption">'.$decode.'</span></font><br>';

        	}
        $this->input_txt=$txt;
        $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        return $ret;
    }
###endsub###

###sub open_select_CONDITION($val) as void###
		function open_select_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
				";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');
					if (value=='$value')
					{
			  	if (document.getElementById('".$this->attributes['VAR']."'))
							document.getElementById('".$this->attributes['VAR']."').style.display='';
					}
						";
			}
			else {
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
					";
				#foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
				$this->check_js.=" \n
				document.forms[0].".$this->attributes['VAR'].".value='';
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
				}
				else
				{
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='';
				}
				";
			}
		}
			$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:\">".$this->html."</tr>";
		}
###endsub###

###sub open_select_CONDITION($val) as void###
		function open_e_select_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
				";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');
					if (value=='$value')
					{
			  	if (document.getElementById('".$this->attributes['VAR']."'))
							document.getElementById('".$this->attributes['VAR']."').style.display='';
					}
						";
			}
			else {
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
					";
				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
				$this->check_js.=" \n
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='none';
				}
				else
			  if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='';
				";
			}
		}
			$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:none\">".$this->html."</tr>";
		}
###endsub###


###sub open_select_disabled($val) as void###
		function open_select_disabled($value){
			$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".disabled=true;
			";
		}
###endsub###

###sub open_select_salva($val) as void###
		function open_select_save($val){
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
				if ($this->attributes['CONDITION']!='') {
			  	$var_cond=$this->attributes['CONDITION'];
			  	$val_cond=$this->attributes['CONDITION_VALUE'];
			  	$this->salva_js="
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->salva_js="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub open_select_invia($val) as void###
		function open_select_send($val){
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  #echo "<hr>invia $testo $testo_js<hr>";
			  if ($this->attributes['CONDITION']!='') {
			  	$var_cond=$this->attributes['CONDITION'];
			  	$val_cond=$this->attributes['CONDITION_VALUE'];
			  	$this->invia_js="
			  	c1+='<<kt###".$this->attributes['VAR']."###v&&&".$var_cond."&&&=#".$val_cond."#*#*$$$".$testo_js.">>';\n
          c1+='<<kv###".$this->attributes['VAR']."###v&&&".$var_cond."&&&!#".$val_cond."#*#*$$$=##Vuoto#".$testo_js.">>';\n
//			  	value=value_of('$var_cond', '0');
//					if (value=='$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->invia_js="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub open_select_must_be($val) as void###
		function open_select_must_be($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo=preg_replace("/<(.*?)>/", "", $testo);
			  $testo=preg_replace("/'/", "/\/'/", $testo);
				$this->controlli.="if (document.forms[0].".$this->attributes['VAR'].".value!='".$val."') {alert ('".$testo." must be ".$this->values[$val]."'); return false}\n";
		}
###endsub###



############################
# 			CHECKBOX     			 #
############################

//		function open_check_send($val){
//			  $testo=$this->testo;
//			  $testo_js=make_js($this->input_txt);
//			  #echo "$testo_js";
//			  if ($this->attributes['CONDITION']!='') {
//			  	$var_cond=$this->attributes['CONDITION'];
//			  	$val_cond=$this->attributes['CONDITION_VALUE'];
//			  	$this->invia_js="
//			  	value=value_of('$var_cond', '0');
//					if (value=='$val_cond')
//			  	c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n
//			  	";
//			  }
//			  else $this->invia_js="c1+='<<r###".$this->attributes['VAR']."###".$testo_js.">>';\n";
//		}



###sub open_checkbox_CONDITION($val) as void###
		function open_checkbox_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
					";
				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].$key.checked=false;";
				if ($this->attributes['HIDE']=='yes')
					$this->check_js.=" \n	document.getElementById('".$this->attributes['VAR']."').style.display='none';";
					$this->check_js.="
				}
				else if (document.getElementById('".$this->attributes['VAR']."')) document.getElementById('".$this->attributes['VAR']."').style.display='';
				";
			$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:none\">".$this->html."</tr>";
		}
###endsub###

###sub open_checkbox($value as mixed) as string###
		function open_checkbox($value){
			global $inputval;
			global $in;
			$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
			$cols=$this->attributes['SUBTBCOL'];
//			print_r ($this->attributes);

      $txt=$this->testo;
      $input_html='
      <table border=0 cellpadding=0 cellspacing=0 width=100%><tr style="display:none"><td colspan="'.$cols.'">&nbsp;</td>
      ';
      $col=0;
      foreach ($this->values as $val => $decode) {
      		if ($col==$cols) $col=0;
      		if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
      		$col++;
      		$this->check_js.="
      		if (document.forms[0].$val.checked)
      				document.forms[0].$val.value=1;
      		else document.forms[0].$val.value=0;
      				";
      		$checked="";
      		if ($inputval[$val]==1) $checked="checked";
      		if ($in[$val]==1) $checked="checked";
      		if ($this->attributes['VALUE_TXT'][$val]!='')
      			$this->attributes['VALUE_TXT'][$val]="<br><font size=1><b>".$this->attributes['VALUE_TXT'][$val]."</b></font>";
      		$input_html.='
      		<td><input type="checkbox" value="1" name="'.$val.'" '.$checked.' onclick="cf();"/>'.$decode.' '.$this->attributes['VALUE_TXT'][$val].' </td>';
      	  if (isset($in['INVIOCO']) && !isset($in[$val])) $in[$val]=0;
      	}
      $input_html.='</tr></table>';
      $this->input_field=$input_html;
      $this->input_txt=$txt;
      if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
      else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';

      #return $ret;
		}
###endsub###

###sub close_checkbox($value as mixed) as string###
		function close_checkbox($value){
			global $inputval;
			global $in;
			$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
			$cols=$this->attributes['SUBTBCOL'];
      $txt=$this->testo;
//      echo "{$this->attributes['VAR']}<hr>";
      $input_html='
      <table border=0 cellpadding=0 cellspacing=0 width=100%><tr><td colspan="'.$cols.'">&nbsp;</td>
      ';
      $col=0;
      foreach ($this->values as $val => $decode) {
      		if ($col==$cols) $col=0;
      		if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
      		$col++;
      		$checked="";
//      		echo "$val=$inputval[$val]<hr>";
      		if ($inputval[$val]==1) $checked="checked";
//       		echo "$val=$inputval[$val]- $checked<hr>";
     		if ($checked=='checked') $input_html.='<td><img src="/images/checkedcheck.gif">';
     		else $input_html.='<td><img src="/images/uncheckedcheck.gif">';
     		if ($this->attributes['VALUE_TXT'][$val]!='')
      			$this->attributes['VALUE_TXT'][$val]="<br><font size=1><b>".$this->attributes['VALUE_TXT'][$val]."</b></font>";
//        		echo "$input_html<hr>";
     		$input_html.=$decode.' '.$this->attributes['VALUE_TXT'][$val].'</td>';
      	}
      $input_html.='</tr></table>';
//        		echo "$input_html<hr>";
     $this->input_txt=$txt;
      $this->input_field=$input_html;
//        		echo "---------{$this->input_field}<hr>";
     if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
      else $ret.='<td class="destra" align=right>'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';
      return $ret;
		}
###endsub###



############################
# 			E_SELECT     			 #
############################


###sub open_e_select($value as mixed) as string###
    function open_e_select($value){
    	  global $in;
    	  global $inputval;
    	  #echo "<hr>e-select<hr>";
        #$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $in[$this->attributes['VAR']]==''  && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        $input_html='<select name="'.$this->attributes['VAR'].'" onchange="cf();submit();">';
        if ($in[$this->attributes['VAR']]=='')$input_html.='<option value="" selected>&nbsp;</option>';
        else $input_html.='<option value="">&nbsp;</option>';
		foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]!='' && $inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]!='' && $in[$this->attributes['VAR']]==$val) $selected="selected";
        		$input_html.='<option value="'.$val.'" '.$selected.'>'.$decode.'</option>';
        	}
        $input_html.='</select><input type="hidden" name="D_'.$this->attributes['VAR'].'">';
        $this->input_txt=$txt;
        $this->input_field=$input_html;
        #if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        #else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        #return $ret;
    }
###endsub###

###sub close_e_select($value as mixed) as string###
    function close_e_select($value){
    	  global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($selected=='selected') $input_html.='<b><i>'.$decode.'</i></b><br/>';
        		#else $input_html.='<font color="#005dce" size="1"><span class="unselectedOption">'.$decode.'</span></font><br/>';
        	}
        $this->input_txt=$txt;
        $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        #return $ret;
    }
###endsub###

###sub open_e_select_onchange($val) as void###
		function open_e_select_onchange($val){
			$this->check_js.="
			$val
			";
		}
###endsub###

###sub open_e_select_invia($val) as void###
		function open_e_select_send($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  if ($this->attributes['CONDITION']!='') {
			  	$var_cond=$this->attributes['CONDITION'];
			  	$val_cond=$this->attributes['CONDITION_VALUE'];
			  	$this->invia_js="
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->invia_js="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###



############################
# 			RADIO_SELECT 			 #
############################


###sub open_radio_select($value as mixed) as string###
    function open_radio_select($value){
    	  global $in;
    	  global $inputval;
    	  #if ($in[$this->attributes['RADIO']]!='') $inputval[$this->attributes['RADIO']]=$in[$this->attributes['RADIO']];
    	  $optgroup=false;
        #$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $in[$this->attributes['VAR']]==''  && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        $input_html='<select name="'.$this->attributes['VAR'].'" onchange="cf();"><option value="">&nbsp;</option>';
        $checked="";
        if ($inputval[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $checked="checked";
        if ($in[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $checked="checked";
        $txt.="<input type=\"radio\" name=\"".$this->attributes['RADIO']."\" value=\"".$this->attributes['RADIO_VALUE']."\" $checked onclick=\"//submit();\"/>";
				foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if (preg_match("/optgroup/",$val))
        			{
        				$optgroup=true;
        				if ($options!='') $options.="
        				</optgroup>";
        				$options.='
        				<optgroup label="'.$decode.'">';
        			}
        		else $options.='
        				<option value="'.$val.'" '.$selected.'>'.$decode.'</option>';
        	}
        	if ($optgroup) $options.="</optgroup>";

        $input_html.=$options.'</select><input type="hidden" name="D_'.$this->attributes['VAR'].'"/>';
        $this->input_field=$input_html;
        #echo $this->input_field."<hr>";
        $this->input_txt=$txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td>';
        #return $ret;
    }
###endsub###

###sub open_radio_select_invia($val) as void###
		function open_radio_select_send($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  #echo "<hr>invia $testo_js<hr>";
			  if ($this->attributes['RADIO']!='') {
			  	$var_cond=$this->attributes['RADIO'];
			  	$val_cond=$this->attributes['RADIO_VALUE'];
			  	$this->invia_js.="
			  	value=value_of('$var_cond', '0');
			  	//alert ('$var_cond='+value);
					if (value=='$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';
					else  if (document.forms[0].".$this->attributes['VAR'].".value!='') {alert ('field: \\n $testo_js \\n must be blank!!!'); document.forms[0].$this->attributes['VAR'].focus(); return false;};
			  	";
			  }
			  else $this->invia_js.="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub open_radio_select_salva($val) as void###
		function open_radio_select_save($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  #echo "<hr>invia $testo_js<hr>";
			  if ($this->attributes['RADIO']!='') {
			  	$var_cond=$this->attributes['RADIO'];
			  	$val_cond=$this->attributes['RADIO_VALUE'];
			  	$this->salva_js.="
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			  }
			  else $this->salva_js.="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub close_radio_select($value as mixed) as string###
    function close_radio_select($value){
    	  global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo.":";
        if ($inputval[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $txt.="<img src='/images/checkedradio.gif'>";
      	else $txt.="<img src='/images/uncheckedradio.gif'>";
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='') {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($selected=='selected') $input_html.='<b><i><u><font color="#333300" size="2"><span class="selectedOption">'.$decode.'</span></font></u></i></b><br/>';
        		else $input_html.='<font color="#005dce" size="1"><span class="unselectedOption">'.$decode.'</span></font><br/>';
        	}
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        return $ret;
    }
###endsub###


############################
# 			DATA				 			 #
############################

###sub close_data($value as mixed) as string###
    function close_data($value){
    		global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        #echo $value;
        $dd=substr($value, 0,2);
        $mm=substr($value,2,2);
        $yyyy=substr($value,4,4);
        if ($this->attributes['NDAY']!='yes')
        {
          $input_html=$dd.' '.$mm.' '.$yyyy;
          $sstr='(gg mm aaaa)';
        }
        else
        {
          $input_html=$mm.' '.$yyyy;
           $sstr='(mm aaaa)';
       }
       $rc=$this->attributes['VAR'].'RC';
       if ($inputval[$rc]=='CONTIN')
        {
         $input_html='CONT';
         $sstr=' ';
       }


        $this->input_txt=$txt;
        $this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>'. $sstr;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
        else
        $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>'. $sstr.'</td></tr>';
        #return $ret;
    }
###endsub###

###sub open_data_CONDITION($val) as void###
		function open_data_CONDITION($val){
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {

				if (preg_match("/,/", $val_cond)){
				$this->check_js.="
				if (document.getElementById('".$this->attributes['VAR']."'))
				document.getElementById('".$this->attributes['VAR']."').style.display='none';
				";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');
					if (value=='$value')
					{
							document.forms[0].".$this->attributes['VAR']."D.value='';
							document.forms[0].".$this->attributes['VAR']."M.value='';
							document.forms[0].".$this->attributes['VAR']."Y.value='';
				   if (document.getElementById('".$this->attributes['VAR']."'))
							document.getElementById('".$this->attributes['VAR']."').style.display='';
					}
						";
			}
			else {
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
							document.forms[0].".$this->attributes['VAR']."D.value='';
							document.forms[0].".$this->attributes['VAR']."M.value='';
							document.forms[0].".$this->attributes['VAR']."Y.value='';
					";
				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
				$this->check_js.=" \n
				if (document.getElementById('".$this->attributes['VAR']."'))
          document.getElementById('".$this->attributes['VAR']."').style.display='none';
				}
				else
       if (document.getElementById('".$this->attributes['VAR']."'))
				  document.getElementById('".$this->attributes['VAR']."').style.display='';
				";
			}

//					$this->check_js=" \n
//					value=value_of('$var_cond', '0');
//					//alert ('$var_cond '+value);
//					if (value!='$val_cond')
//					{
//						";
//					foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
//					$this->check_js.=" \n	document.getElementById('".$this->attributes['VAR']."').style.display='none';
//					}
//					else document.getElementById('".$this->attributes['VAR']."').style.display='';
//					";
				}
				else $this->check_js.="
				if (document.getElementById('".$this->attributes['VAR']."'))
				 document.getElementById('".$this->attributes['VAR']."').style.display='';";
				$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:none\">".$this->html."</tr>";
		}
###endsub###

###sub open_data($value as mixed) as string###
    function open_data($value){
    		global $in;
//    		echo "<hr>$value<hr>";
    		global $inputval;
        #$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';

        if ($in[$this->attributes['VAR'].'D']!='' && $in[$this->attributes['VAR'].'M']!='' && $in[$this->attributes['VAR'].'Y']!=''){
        	if ($in[$this->attributes['VAR'].'D']!='') {
        		$in[$this->attributes['VAR'].'D']='0'.$in[$this->attributes['VAR'].'D'];
        		$in[$this->attributes['VAR'].'D']=substr($in[$this->attributes['VAR'].'D'],strlen($in[$this->attributes['VAR'].'D'])-2,2);
        	}
        	if ($in[$this->attributes['VAR'].'M']!='') {
        		$in[$this->attributes['VAR'].'M']='0'.$in[$this->attributes['VAR'].'M'];
        		$in[$this->attributes['VAR'].'M']=substr($in[$this->attributes['VAR'].'M'],strlen($in[$this->attributes['VAR'].'M'])-2,2);
        	}
        	$value=$in[$this->attributes['VAR']]=$in[$this->attributes['VAR'].'D'].$in[$this->attributes['VAR'].'M'].$in[$this->attributes['VAR'].'Y'];
        	$in[$this->attributes['VAR'].'D']+=0;
        	$in[$this->attributes['VAR'].'M']+=0;
        }
//        echo $value;
        $txt=$this->testo;
        #print_r($this->values);
        $keys=array_keys($this->values);
        //$value_init=$keys[0];
        //echo "<hr>$value";
        if ($value_init=='sysdate') $value=date("dmY");
        $dd=substr($value, 0,2);
        $mm=substr($value,2,2);
        $yyyy=substr($value,4,4);
        #echo "<hr>$value";
        if (isset($in['salva']) and $this->attributes['SAVE']=='obbligatorio'){
        	if (!checkdate($mm,$dd,$yyyy)) {
        		$txt.="<br/><font color=red size=\"-1\">Error! Date not valid</font>";
        		$this->validata=false;
        	}
        }
        if (isset($in['invia']) and $this->attributes['SEND']=='obbligatorio'){
        	if (!checkdate($mm,$dd, $yyyy)) {
        		$txt.="<br/><font color=red size=\"-1\">Error! Date not valid</font>";
        		$this->validata=false;
        	}
        }
        $check_onblur='';
        if ($this->attributes['CHECK_ONBLUR']!='') $check_onblur='onblur="el=f.elements;specifiche=\'A=ON&L=0&F=0\';c1=\'<<fd00###'.$this->attributes['VAR'].'###Data errata>>\';rc=contr(c1,specifiche);if (rc) {return false}"';
//        $input_html='<input type="text" name="'.$this->attributes['VAR'].'D" value="'.$dd.'" size=2 maxlenght=2 />
//                     <input type="text" name="'.$this->attributes['VAR'].'M" value="'.$mm.'" size=2 maxlenght=2 />
//                     <input type="text" name="'.$this->attributes['VAR'].'Y" value="'.$yyyy.'" size=4 maxlenght=4 '.$check_onblur.'/>
//                     <input type="hidden" name="'.$this->attributes['VAR'].'"/><input type="hidden" name="'.$this->attributes['VAR'].'RC" />';
        $rc=$this->attributes['VAR'].'RC';
//    		echo "<hr>$rc $in[$rc] $inputval[$rc]<hr>";
//    		print_r ($inputval);
//        if ($inputval[$rc]=='OKOKOK')
//        {
        if ($this->attributes['NDAY']!='yes')
        {
          $input_html='<input type="text" name="'.$this->attributes['VAR'].'D" value="'.$dd.'" size=2 maxlength=2 />&nbsp;';
        }
        else
        {
          $input_html='<input type="hidden" name="'.$this->attributes['VAR'].'D" value="15">';
        }
        $input_html.='<input type="text" name="'.$this->attributes['VAR'].'M" value="'.$mm.'" size=2 maxlength=2 />
                     <input type="text" name="'.$this->attributes['VAR'].'Y" value="'.$yyyy.'" size=4 maxlength=4 '.$check_onblur.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value="'.$dd.$mm.$yyyy.'"/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" />';
//       }
        if ($inputval[$rc]=='CONTIN')
        {
         $input_html='<input type="text" name="'.$this->attributes['VAR'].'D" value="" size=2 maxlength=2 />
                     <input type="text" name="'.$this->attributes['VAR'].'M" value="" size=2 maxlength=2 />
                     <input type="text" name="'.$this->attributes['VAR'].'Y" value="CONT" size=4 maxlength=4 '.$check_onblur.'/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'" value=""/>
                     <input type="hidden" name="'.$this->attributes['VAR'].'RC" value="CONTIN"/>';
        }

        $this->input_field=$input_html;
        $this->input_txt=$txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'(gg mm aaaa)</td>';
        #return $ret;
    }
###endsub###

		function open_data_compila($value){
			#echo "<hr>$value";
			$this->check_js.="
					if (document.forms[0].".$this->attributes['COMPILA_CONDITION_VAR'].".value==".$this->attributes['COMPILA_CONDITION_VALUE']."){
						compila_value=document.forms[0].".$this->attributes['COMPILA'].".value;
						if (compila_value>0){
							document.forms[0].".$this->attributes['VAR']."D.value=compila_value.substr(0,2);
							document.forms[0].".$this->attributes['VAR']."M.value=compila_value.substr(2,2);
							document.forms[0].".$this->attributes['VAR']."Y.value=compila_value.substr(4,4);
							document.forms[0].".$this->attributes['VAR']."D.disabled=true;
							document.forms[0].".$this->attributes['VAR']."M.disabled=true;
							document.forms[0].".$this->attributes['VAR']."Y.disabled=true;
							document.forms[0].".$this->attributes['VAR'].".value=compila_value;
						}
					}
			";
		}

		function open_select_compila($value){
			#echo "<hr>$value";
			$this->check_js.="
					if (document.forms[0].".$this->attributes['COMPILA_CONDITION_VAR'].".value==".$this->attributes['COMPILA_CONDITION_VALUE']."){
						compila_value=document.forms[0].".$this->attributes['COMPILA'].".value;
						if (compila_value>0){
							document.forms[0].".$this->attributes['VAR'].".value=compila_value;
							document.forms[0].".$this->attributes['VAR'].".disabled=true;
						}
					}
			";
		}

		function open_textbox_compila($value){
			#echo "<hr>$value";
			$this->check_js.="
					if (document.forms[0].".$this->attributes['COMPILA_CONDITION_VAR'].".value==".$this->attributes['COMPILA_CONDITION_VALUE']."){
						compila_value=document.forms[0].".$this->attributes['COMPILA'].".value;
						if (compila_value>0){
							document.forms[0].".$this->attributes['VAR'].".value=compila_value;
							document.forms[0].".$this->attributes['VAR'].".disabled=true;
						}
					}
			";
		}

		function open_radio_compila($value){
			#echo "<hr>$value";
			$this->check_js.="
					if (document.forms[0].".$this->attributes['COMPILA_CONDITION_VAR'].".value==".$this->attributes['COMPILA_CONDITION_VALUE']."){
						compila_value=document.forms[0].".$this->attributes['COMPILA'].".value;
						if (compila_value>0){
						  for (i=0;i<document.forms[0].".$this->attributes['VAR'].".length;i++){
						  	//alert (document.forms[0].".$this->attributes['VAR']."[i].value);
						  	if (document.forms[0].".$this->attributes['VAR']."[i].value==compila_value) document.forms[0].".$this->attributes['VAR']."[i].checked=true;
						  }
							document.forms[0].".$this->attributes['VAR'].".disabled=true;
						}
					}
			";
		}

###sub open_data_disabled($value as mixed) as string###
		function open_data_disabled($value){
			$this->check_js.="
				document.forms[0].".$this->attributes['VAR'].".disabled=true;
			";
		}
###endsub###

###sub open_data_invia($val) as void###
		function open_data_send($val){
			#echo "<hr>{$this->testo}";
			  $testo=make_js($this->testo);
			  $dcod='00';
			  if ($this->attributes['DCONT']=='yes') $dcod='16';
				if (!isset($this->attributes['CONDITION'])) $this->invia_js="
				c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
				";
				else
				{
				 $oper="==";
				 if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}

				$val_cond=$this->attributes['CONDITION_VALUE'];
//echo "$val_cond<br>";
				$vals=explode(",",$val_cond);$loc_js="if (";
		    for ($i=0;$i<count($vals);$i++){
		      if ($i!=0) $loc_js.="||";
		      $loc_js.="
		      value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
				}
				$loc_js.=")";
// echo "$loc_js<br>";
				$this->invia_js="
				$loc_js
					c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
					else {
					  c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';
						c1+='<<b###".$this->attributes['VAR']."Y###".$testo.">>';
						}

				";

		}
		}
###endsub###

###sub open_data_salva($val) as void###
		function open_data_save($val){
			  $dcod='00';
			  if ($this->attributes['DCONT']=='yes') $dcod='16';
			if ($val=='obbligatorio')
			  $testo=make_js($this->testo);
				$this->salva_js="
				c1+='<<d".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
		}
###endsub###

###sub open_data_min($val) as void###
function open_data_min($value){
	global $in;
	global $inputval;
	if (preg_match("/,/",$value)){
		$values=explode(",",$value);
		foreach ($values as $key=>$value){
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
			/*lato server*/
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			#echo "<hr>$data";
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
			else $value_txt="al ".$value_txt;
			#echo "<hr>$value";
			$rc=$this->attributes['VAR'].'RC';
      $vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data>$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
				$this->validata=false;
				#echo "<hr>$value";
				if ($data!='')
				$this->input_txt.="<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
			}
			/*lato client*/
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
			$testo_js=make_js($this->testo);
				$this->controlli.="
				//alert (data+' - '+value);
				if (data>value && value) {
						alert('La {$testo_js} deve essere precedente $value_txt');
						document.forms[0].".$this->attributes['VAR']."Y.focus();
						return false;
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
	//		echo "$testo_var_condizione<hr>";
			if ($in[$value_field]!='') $value=$in[$value_field];
		}
		/*lato server*/
		if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
		$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
		$data=$inputval[$this->attributes['VAR']];
		if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
		#echo "<hr>$data";
		$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
		$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
		if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
		else $value_txt="al ".$value_txt;
			$rc=$this->attributes['VAR'].'RC';
      $vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data>$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {

//		if ($data>$value && $data!='') {
			$this->validata=false;
			#echo "<hr>$value";
			if ($data!='')
			$this->input_txt.="<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
		}
		/*lato client*/
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
		$testo_js=make_js($this->testo);
			$this->controlli.="
			if (data>value) {
					alert('La {$testo_js} deve essere precedente $value_txt');
					document.forms[0].".$this->attributes['VAR']."Y.focus();
					return false;
			}
			}
		";
	}
}
###endsub###

###sub open_data_max($val) as void###
function open_data_max($value){
	global $in;
	global $inputval;
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
			#echo "<hr>".$this->attributes['VAR']." $value";
			/*lato server*/
			if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
			$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
			$data=$inputval[$this->attributes['VAR']];
			if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
			#echo "<hr>$data";
			$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
			$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
			if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
			else $value_txt="al ".$value_txt;
			$rc=$this->attributes['VAR'].'RC';
      $vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
//			if ($data<$value && $data!='' && $value!='') {
				$this->validata=false;
				#echo "<hr>$value";
				if ($data!='')
				$this->input_txt.="<br><font color=red>La Data deve essere successiva a $value_txt&nbsp;";
			}
			/*lato client*/
		//	echo "$value_field<hr>";
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
				if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
			else $value_txt="al ".$value_txt;
			$testo_js=make_js($this->testo);
				$this->controlli.="
				if (data<value && value) {
						alert('La {$testo_js} deve essere successiva $value_txt');
						document.forms[0].".$this->attributes['VAR']."Y.focus();
						return false;
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
	//		echo "$testo_var_condizione<hr>";
			if ($in[$value_field]!='') $value=$in[$value_field];
		}
		#echo "<hr>".$this->attributes['VAR']." $value";
		/*lato server*/
		if ($value=='today'||$value=='sysdate') $value=date("dmY", time());
		$value=substr($value,4,4).substr($value,2,2).substr($value,0,2);
		$data=$inputval[$this->attributes['VAR']];
		if ($in[$this->attributes['VAR']]!='') $data=$in[$this->attributes['VAR']];
		#echo "<hr>$data";
		$data=substr($data,4,4).substr($data,2,2).substr($data,0,2);
		$value_txt=substr($value,6,2)."/".substr($value,4,2)."/".substr($value,0,4);
		if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
		else $value_txt="al ".$value_txt;
			$rc=$this->attributes['VAR'].'RC';
      $vrc=$inputval[$rc];
			if ($in[$rc]!='') $vrc=$in[$rc];
			if ($data<$value && $data!='' && $value!='' && ($vrc=='OKOKOK' || $vrc=='')) {
//		if ($data<$value && $data!='') {
			$this->validata=false;
			#echo "<hr>$value";
			if ($data!='')
			$this->input_txt.="<br><font color=red>La Data deve essere successiva a $value_txt&nbsp;";
		}
		/*lato client*/
	//	echo "$value_field<hr>";
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
			if ($testo_var_condizione!='') $value_txt="alla ".$testo_var_condizione;
		else $value_txt="al ".$value_txt;
		$testo_js=make_js($this->testo);
			$this->controlli.="
//			alert(data+' '+value);

			if (data<value) {
					alert('La {$testo_js} deve essere successiva $value_txt');
					document.forms[0].".$this->attributes['VAR']."Y.focus();
					return false;
			}
			}
		";
	}
}
###endsub###



############################
# 			RADIO_TEXTBOX			 #
############################

###sub open_radio_textbox($value as mixed) as string###
    function open_radio_textbox($value){
    		global $in;
        $txt=$this->testo;
         if ($inputval[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $checked="checked";
        if ($in[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $checked="checked";
        $txt.="<input type=\"radio\" name=\"".$this->attributes['RADIO']."\" value=\"".$this->attributes['RADIO_VALUE']."\" $checked onclick=\"//submit();\"/>";
        if ($this->attributes['CONTROLLO']=='') $this->attributes['CONTROLLO']="testo";
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CONTROLLO']=='testo') {
        		if ($in[$this->attributes['VAR']]=='') {
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere testuale e non vuoto</font>";
        		}
        	}
        	if ($this->attributes['CONTROLLO']=='numerico') {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere numerico e non nullo</font>";
        	}
        }
         if ($in['salva']!='' && $this->attributes['SEND']=='obbligatorio' && $this->attributes['CONDITION']!=''&& $in[$this->attributes['CONDITION']]!=$this->attributes['CONDITION_VALUE'] && $in[$this->attributes['VAR']]!=''){
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere vuoto</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $this->attributes['CONDITION']!=''&& $in[$this->attributes['CONDITION']]!=$this->attributes['CONDITION_VALUE'] && $in[$this->attributes['VAR']]!=''){
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere vuoto</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CHECK']=='testo') {
        		if ($in[$this->attributes['VAR']]=='') {
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere testuale e non vuoto</font>";
        		}
        	}
        	if ($this->attributes['CHECK']=='numerico') {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere numerico e non nullo</font>";
        	}
        }
        #print_r($this->values);
        foreach ($this->values as $key => $val) $value=$val;
        if ($inputval[$this->attributes['VAR']]!='') $value=$inputval[$this->attributes['VAR']];
        if ($in[$this->attributes['VAR']]!='') $value=$in[$this->attributes['VAR']];
        $this->input_field=$this->attributes['DEF_ANTE'].'<input type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" name="'.$this->attributes['VAR'].'" value="'.$value.'" onblur="cf()"/>'.$this->attributes['DEF'].'';
        $this->input_txt=$txt;
    }
###endsub###

###sub close_radio_textbox($value as mixed) as string###
    function close_radio_textbox($value){
    	  global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo.":";
        if ($inputval[$this->attributes['RADIO']]==$this->attributes['RADIO_VALUE']) $txt.="<img src='/images/checkedradio.gif'>";
      	else $txt.="<img src='/images/uncheckedradio.gif'>";
       	$input_html.='<b>'.$inputval[$this->attributes['VAR']].'</b>';
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        return $ret;
    }
###endsub###

###sub open_radio_textbox_invia($val) as void###
		function open_radio_textbox_send($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  #echo "<hr>invia $testo_js<hr>";
			  if ($this->attributes['RADIO']!='') {
			  	$var_cond=$this->attributes['RADIO'];
			  	$val_cond=$this->attributes['RADIO_VALUE'];
			  	$this->invia_js.="
			  	value=value_of('$var_cond', '0');
			  	//alert ('$var_cond='+value);
					if (value=='$val_cond') c1+='<<t###".$this->attributes['VAR']."###".$testo_js.">>';
					else c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';
			  	";
			  }
			  else $this->invia_js.="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###

###sub open_radio_textbox_salva($val) as void###
		function open_radio_textbox_save($val){
			if ($val=='obbligatorio')
			  $testo=$this->testo;
			  $testo_js=make_js($testo);
			  #echo "<hr>invia $testo_js<hr>";
			  if ($this->attributes['RADIO']!='') {
			  	$var_cond=$this->attributes['RADIO'];
			  	$val_cond=$this->attributes['RADIO_VALUE'];
			  	$this->salva_js.="
			  	value=value_of('$var_cond', '0');
			  	//alert ('$var_cond='+value);
					if (value=='$val_cond') c1+='<<t###".$this->attributes['VAR']."###".$testo_js.">>';
					else c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';
			  	";
			  }
			  else $this->salva_js.="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
###endsub###


############################
# 												 #
############################






###sub open_CONDITION($val) as void###
		function open__CONDITION($val){
			#echo "<hr>open__CONDITION<hr>";
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {

			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
				if (document.getElementById('".$this->attributes['NAME']."'))
				document.getElementById('".$this->attributes['NAME']."').style.display='none';
				";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');
					if (value=='$value')
					{
				  if (document.getElementById('".$this->attributes['NAME']."'))
          document.getElementById('".$this->attributes['NAME']."').style.display='';
					}
						";
			}
			else {
				$this->check_js=" \n
				value=value_of('$var_cond', '0');
				if (value!='$val_cond')
				{
					";
				foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['NAME']."[".($key-1)."].checked=false;";
				$this->check_js.="
				if (document.getElementById('".$this->attributes['NAME']."'))
				 \n	document.getElementById('".$this->attributes['NAME']."').style.display='none';
				}
				else
				if (document.getElementById('".$this->attributes['NAME']."'))
				document.getElementById('".$this->attributes['NAME']."').style.display='';
				";
			}
		}
			$this->html="<tr id=\"".$this->attributes['NAME']."\" style=\"display: none\">$this->html</tr>";
		}
###endsub###

###sub open_($value as mixed) as string###
    function open_($value){
    		global $in;
        $ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
        $txt=$this->testo;
        $this->input_txt=$txt."<tr>";
    }
    ###sub open_($value as mixed) as string###
function close_($value){
    		global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
        $txt=$this->testo;
        if ($inputval[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE'])
        $this->input_txt=$txt."<tr>";
    }
###endsub###


function open_tb_coll($value){
	global $conn;
	global $xml_dir;
	global $in;
	$sql=new query($conn);
	$query="select cod,decode from {$this->attributes['TB_COLL']}";
	$sql->set_sql($query);
	$sql->exec();//obsoleto trovare dove testare
	$new_xml_form= new xml_form();
	$new_xml_form->xml_form_by_file($xml_dir.'/q_tb_coll.xml');
	//$in['CREATE']='yes';
	//$new_xml_form->allinea_db();
	$new_xml_form->tb_coll_header();
	$this->input_txt='<tr id="'.$this->attributes['NAME'].'" style="display:"><td colspan='.$this->attributes['COLSPAN'].'>';
	$this->input_txt.='<table border=1 cellpadding=0 cellspacing=0 width=100%><tr><td>&nbsp;</td>';
	$this->input_txt.=$new_xml_form->body;
	#echo $new_xml_form->body;
	$this->input_txt.='</tr>';
	while ($sql->get_row()){
	 $in['ID_REF']=$sql->row['COD'];
	 $in['TB_COLL']="yes";
	 $new_xml_form= new xml_form();
	 $new_xml_form->xml_form_by_file($xml_dir.'/q_tb_coll.xml');
	 $new_xml_form->closed_form();
	 $new_xml_form->tb_coll_open_form();
	 $this->input_txt.="<tr><td><b>{$sql->row['DECODE']}</b></td>";
	 $this->input_txt.=$new_xml_form->body;
	 $this->input_txt.="</tr>";
	}
	$xml_form=new xml_form();
	#echo "<hr>$xml_dir/$xml<hr>";
	global $es_form;
	$xml=$es_form[$in['VISITNUM']][$in['ESAM']];
	$xml_form->xml_form_by_file($xml_dir.'/'.$xml);
	$xml_form->closed_form();
	$in['TB_COLL']="";
	unset($in['TB_COLL']);
	#echo $this->input_txt.="</table></td></tr>";
	$this->input_txt.="</table></td></tr>";
}

function close_tb_coll($value){
	global $conn;
	global $xml_dir;
	global $in;
	$sql=new query($conn);
	$query="select cod,decode from {$this->attributes['TB_COLL']}";
	$sql->set_sql($query);
	$sql->exec();//obsoleto trovare dove testare
	$new_xml_form= new xml_form();
	$new_xml_form->xml_form_by_file($xml_dir.'/q_tb_coll.xml');
	//$in['CREATE']='yes';
	//$new_xml_form->allinea_db();
	$new_xml_form->tb_coll_header();
	$this->input_txt='<tr id="'.$this->attributes['NAME'].'" style="display:"><td colspan='.$this->attributes['COLSPAN'].'>';
	$this->input_txt.='<table border=1 cellpadding=0 cellspacing=0 width=100%><tr><td>&nbsp;</td>';
	$this->input_txt.=$new_xml_form->body;
	#echo $new_xml_form->body;
	$this->input_txt.='</tr>';
	while ($sql->get_row()){
	 $in['ID_REF']=$sql->row['COD'];
	 $in['TB_COLL']="yes";
	 $new_xml_form= new xml_form();
	 $new_xml_form->xml_form_by_file($xml_dir.'/q_tb_coll.xml');
	 if($in['DOWN']!='1') $new_xml_form->closed_form();
	 $new_xml_form->tb_coll_closed_form();
	 $this->input_txt.="<tr><td><b>{$sql->row['DECODE']}</b></td>";
	 $this->input_txt.=$new_xml_form->body;
	 $this->input_txt.="</tr>";
	}
	$xml_form=new xml_form();
	#echo "<hr>$xml_dir/$xml<hr>";
	global $es_form;
	$xml=$es_form[$in['VISITNUM']][$in['ESAM']];
	$xml_form->xml_form_by_file($xml_dir.'/'.$xml);
	if($in['DOWN']!='1') $xml_form->closed_form();
	$in['TB_COLL']="";
	unset($in['TB_COLL']);
	#echo $this->input_txt.="</table></td></tr>";
	$this->input_txt.="</table></td></tr>";
}


############################
# 			COUNTRY_BROWSE		 #
############################

###sub open_country_browse($value as mixed) as string###
    function open_country_browse($value){
    		global $in;
    		global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']) )) {
        	if ($this->attributes['CONTROLLO']=='testo') {
        		if ($in[$this->attributes['VAR']]=='') {
        			$this->validata=false;
        			$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere testuale e non vuoto</font>";
        		}
        	}
        	if ($this->attributes['CONTROLLO']=='numerico') {
        		$this->validata=false;
        		$txt.="<br/><font size='-1' color='red'>Errore!!!Il campo deve essere numerico e non nullo</font>";
        	}
        }
        $value=$inputval[$this->attributes['VAR']];
        if ($in[$this->attributes['VAR']]!='') $value=$in[$this->attributes['VAR']];
        $this->input_txt=$txt;
        $input_html='
        <input type="hidden" name="RET" value="DESCR"/><input type="hidden" name="sfoglia_table" value="PAESI_ISO" />
        <input name="'.$this->attributes['VAR'].'" type="text" value="'.$value.'" />&nbsp;
				<input type="submit" name="SFOGLIA" value="Search"  onClick="url_sfoglia=build_sfoglia_url(\'Cerca\',\'DESCR\',\'PAESI_ISO\');apri_window(url_sfoglia);return false;"/>
				&nbsp;&nbsp;
				<input type="submit" name="SFOGLIA" value="Explore"  onClick="url_sfoglia=build_sfoglia_url(\'Sfoglia\',\'DESCR\',\'PAESI_ISO\');apri_window(url_sfoglia);return false;"/>';
         $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';

    }
###endsub###

###sub close_country_browse($value as mixed) as string###
    function close_country_browse($value){
    		global $in;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        $input_html='<b><i><font color="#333300"><span class="textfield">'.$value.'</span></font></i></b>';
        $this->input_txt=$txt;
        $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b></td></tr>';
    }
###endsub###



############################
# 			CHECK_BROWSE			 #
############################

###sub open_data_CONDITION($val) as void###
		function open_check_select_CONDITION($val){
			#echo "<hr>{$this->attributes['VAR']} - {$this->attributes['CONDITION']} - {$this->attributes['CONDITION_VALUE']} <hr>";
			$var_cond=$val;
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if ($this->attributes['HIDE']=='yes') {
					$this->check_js=" \n
					value=value_of('$var_cond', '0');
					if (value!='$val_cond')
					{
						";
					foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->attributes['VAR']."[".($key-1)."].checked=false;";
					$this->check_js.=" \n
			  	if (document.getElementById('".$this->attributes['VAR']."'))
										  document.getElementById('".$this->attributes['VAR']."').style.display='none';
					}
					else
			  	if (document.getElementById('".$this->attributes['VAR']."'))
					  document.getElementById('".$this->attributes['VAR']."').style.display='';
					";
				}
				else $this->check_js.="
			  if (document.getElementById('".$this->attributes['VAR']."'))
					document.getElementById('".$this->attributes['VAR']."').style.display='';";
				$this->html="<tr id='".$this->attributes['VAR']."' style=\"display:none\">".$this->html."</tr>";
		}
###endsub###

###sub open_check_select($value as mixed) as string###
    function open_check_select($value){
    	  global $in;
    	  global $inputval;
    	  $optgroup=false;
        #$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='' && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        if ($in['invia']!='' && $this->attributes['SEND']=='obbligatorio' && $in[$this->attributes['VAR']]==''  && ($this->attributes['CONDITION']=='' || ($this->attributes['CONDITION']!='' && $in[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))) {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        $input_html='<select name="'.$this->attributes['VAR'].'" onchange="cf();"><option value="">&nbsp;</option>';
        $checked="";
        if ($inputval[$this->attributes['CHECK']]==$this->attributes['CHECK_VALUE']) $checked="checked";
        if ($in[$this->attributes['CHECK']]==$this->attributes['CHECK_VALUE']) $checked="checked";
        $txt.="<input type=\"checkbox\" name=\"".$this->attributes['CHECK']."\" value=\"".$this->attributes['CHECK_VALUE']."\" $checked />";
				foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if (preg_match("/optgroup/",$val))
        			{
        				$optgroup=true;
        				if ($options!='') $options.="
        				</optgroup>";
        				$options.='
        				<optgroup label="'.$decode.'">';
        			}
        		else $options.='
        				<option value="'.$val.'" '.$selected.'>'.$decode.'</option>';
        	}
        	if ($optgroup) $options.="</optgroup>";

        $input_html.=$options.'</select><input type="hidden" name="D_'.$this->attributes['VAR'].'"/>';
        $this->input_field=$input_html;
        #echo $this->input_field."<hr>";
        $this->input_txt=$txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td>';
        #return $ret;
    }
###endsub###


###sub close_select($value as mixed) as string###
    function close_check_select($value){
    	  global $in;
    	  global $inputval;
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo.":";
        if ($inputval[$this->attributes['CHECK']]==$this->attributes['CHECK_VALUE']) $txt.="<img src='/images/checkedcheck.gif'>";
      	else $txt.="<img src='/images/uncheckedcheck.gif'>";
        if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='') {
        	$this->validata=false;
        	$txt.="<br/><font size='-1' color='red'>Errore!!!Effettuare una selezione non nulla</font>";
        }
        foreach ($this->values as $val => $decode) {
        		$selected="";
        		#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
        		if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($in[$this->attributes['VAR']]==$val) $selected="selected";
        		if ($selected=='selected') $input_html.='<b><i><u><font color="#333300" size="2"><span class="selectedOption">'.$decode.'</span></font></u></i></b><br/>';
        		else $input_html.='<font color="#005dce" size="1"><span class="unselectedOption">'.$decode.'</span></font><br/>';
        	}
        $this->input_txt=$txt;
        $this->input_field=$input_html;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
        else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
        return $ret;
    }
###endsub###

############################
# 			TEXTAREA					 #
############################

###sub open_textarea($value as mixed) as string###
    function open_textarea($value){
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        $this->input_field='<textarea name="'.$this->attributes['VAR'].'" cols="'.$this->attributes['TCOLS'].'" rows="'.$this->attributes['ROWS'].'">'.$value.'</textarea>';
       	$this->input_txt=$txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';
        #return $ret;
    }
###endsub###

###sub close_textarea($value as mixed) as string###
    function close_textarea($value){
        $ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
        $txt=$this->testo;
        $input_html='<b>'.$value.'</b>';
        $this->input_txt=$txt;
        $this->input_field="&nbsp;".$input_html;
        if (isset($this->attributes['COLSPAN'])) $ret.='<td  class="input_txt" colspan="'.$this->attributes['COLSPAN'].'">'.$txt.':'.$input_html.'</td>';
        else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';
        #return $ret;
    }
###endsub###
























}

function make_js($testo){
	echo "<hr>$testo<hr>";
	 $testo_js=preg_replace("/'/", "\'", $testo);
	 $testo_js=preg_replace("/<a(.*?)\/a>/m", "", $testo_js);
	 $testo_js=preg_replace("/<(.*?)>/m", "", $testo_js);
	 $testo_js=preg_replace("/\n/", "", $testo_js);
	 $testo_js=preg_replace("/&(.*?);/", "", $testo_js);
	 $testo_js=preg_replace("/\((.*?)\)/", "", $testo_js);
	 $testo_js=preg_replace("/\?(.*)/", "", $testo_js);
	 $testo_js=preg_replace("/\*/", "", $testo_js);
	 #echo "<hr>make_js - $testo_js<hr>";
	 echo "<hr>$testo_js<hr>";
	 return $testo_js;
}

?>