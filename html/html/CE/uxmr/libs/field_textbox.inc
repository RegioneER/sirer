<?

include_once "field.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package Fields
 */
class field_textbox extends field {
	var $max_js;
	var $min_js;

/**
 * Costruisce il codice js del campo in con autocomplete
 *
 + @param String $value
 */

    function autocomplete_js(){
        return "<style>
    * {
    font-family: Verdana,Arial,Helvetica,sans-serif !important;
    font-size: 10px !important;
    /*font-weight: bold;*/
}


    .ui-autocomplete {
        max-height: 100px;
        overflow-y: auto;
        /* prevent horizontal scrollbar */
        overflow-x: hidden;
        /* add padding to account for vertical scrollbar */
        padding-right: 20px;
        white-space: nowrap;
    }
    /* IE 6 doesn't support max-height
     * we use height instead, but this forces the menu to always be this tall
     */
    * html .ui-autocomplete {
        height: 100px;
    }
    </style>
    <link media=\"screen\" href=\"libs/js/jquery/themes/base/jquery.ui.all.css\" rel=\"stylesheet\" type=\"text/css\" />
    
<script type=\"text/javascript\" src=\"libs/js/jquery/jquery.min.js\"></script>
<script src=\"libs/js/jquery/ui/jquery.ui.core.js\"></script>
<script src=\"libs/js/jquery/ui/jquery.ui.widget.js\"></script>
<script src=\"libs/js/jquery/ui/jquery.ui.position.js\"></script>
<script type=\"text/javascript\" src=\"libs/js/jquery/ui/jquery.ui.autocomplete.js\"></script>
    ";
    }

    function autocomplete_js_field(){
          global $conn;
          $sql=new query($conn);

          $sql_query=$this->attributes['DIZIONARIO'];
        $sql_query=str_ireplace("[service]",$this->service , $sql_query);
        $replaceRet=query::varGlobReplace($sql_query);
        $sql_query=$replaceRet['sql'];
        //$sql->set_sql($sql_query);
        $sql->exec($sql_query,$replaceRet['binded']);
        while ($sql->get_row()) {
            $curr_obj="";
            foreach ($sql->row as $field => $valore){
                $valore=str_replace('"', '', $valore);
                $curr_obj.="{$field}:\"{$valore}\",
                ";
            }
            $sql->row[$this->id]=str_replace('"', '', $sql->row[$this->id]);
            $curr_obj=rtrim($curr_obj,',');
            $lista.='{value:"'.$sql->row[$this->id].'",label:"'.$sql->row[$this->id].'",desc:{'.$curr_obj.'}},';
        }
        
        $lista=rtrim($lista,',');
        $lista=str_replace("'","\\'",$lista);
        if($this->attributes['OPTIONS']!=''){
            $options=rtrim($this->attributes['OPTIONS'],', ').',';
        }
        $add_jquery="
        <script type=\"text/javascript\">
        $(function (){
        var lista=[$lista];
        $( \"[name={$this->id}]\" ).autocomplete({
                       {$options}
                    minLength: 0,
                    focus: function( event, ui ) {
                    for (var campo in ui.item.desc){
                      $( \"[name=\"+campo+\"]\" ).val( ui.item.desc[campo] );
                       
                    }
                    //  $( \"[name={$this->id}]\" ).val( ui.item.label );
                        return false;
                    },
                    select: function( event, ui ) {
                        //$( \"[name={$this->id}]\" ).val( ui.item.label );
                        for (var campo in ui.item.desc){
                            $( \"[name=\"+campo+\"]\" ).val( ui.item.desc[campo] );
                        }
                        cf();
                        return false;
                    },
                    source: lista
                }).data( \"autocomplete\" )._renderItem = function( ul, item ) {
                    return $( \"<li></li>\" )
                        .data( \"item.autocomplete\", item )
                        .append( \"<a>\" + item.label + \"</a>\" )
                        .appendTo( ul );
                };
                
            });
            $( \"[name={$this->id}]\" ).attr('autocomplete','off');
            $( \"[name={$this->id}]\" ).change(function(){cf();});
            $actions
            </script>
        
            ";
            return $add_jquery;
    }
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value) {
		$in = $this->session_vars;
		//		echo $in['USER_TIP'];
		//		global $inputval;
		$inputval = $this->db_vars;
		$txt = $this->testo;
		if ($this->attributes ['CHECK'] == '')
			$this->attributes ['CHECK'] = "text";

		if ($this->attributes ['SIZE'] == '')
			$this->attributes ['SIZE'] = '20';

		if ($this->attributes ['ONCHANGE'] != '')
			$onchange = "{$this->attributes['ONCHANGE']};";

		if (isset ( $this->values ) && is_array ( $this->values ))
			foreach ( $this->values as $key => $val )
				$value = $val;
		if ($inputval [$this->attributes ['VAR']] != '')
			$value = $inputval [$this->attributes ['VAR']];
		if ($in [$this->attributes ['VAR']] != '')
			$value = $in [$this->attributes ['VAR']];

		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
		    if(strtoupper($this->config_service['lang'])=='IT'){
                if ($value == - 9911)
                    $value = "NA";
                if ($value == - 9922)
                    $value = "NN";
                if ($value == - 9933)
                    $value = "ND";
                if ($value == - 9944)
                    $value = "NP";
                if ($value == - 9955)
                    $value = "TE";
                if ($value == - 9900)
                    $value = "OT";
                  
            }
            else{
    			if ($value == - 9911)
    				$value = "NA";
    			if ($value == - 9922)
    				$value = "NK";
    			if ($value == - 9933)
    				$value = "ND";
    			if ($value == - 9944)
    				$value = "NP";
    			if ($value == - 9955)
    				$value = "TE";
    			if ($value == - 9900)
    				$value = "OT";
            }

		}
		if($this->attributes['AUTOCOMPLETE']){
		    global $autocomplete;
            if(!$autocomplete){             
                $this->script.=$this->autocomplete_js();
                $autocomplete=true;
            }
            
            $add_jquery=$this->autocomplete_js_field();     
        }
	//modifica by G.Tufano 19/11/2010:
    //controllo che un numero reale non sia tra 0 e 1, altrimenti appare tipo '.32' nella casella di testo
        if ($this->attributes ['VAR_TYPE'] == 'number' && (abs($value) > 0 && abs($value) < 1)){
            if ($value > 0)
                $value = abs($value);
            else $value = "-". abs($value);
        }
		
		
		$disabled = "";
		if ($this->attributes ['DISABLED'] != '') {
			if ($value != '')
				$disabled = "disabled=\"disabled\"";
			$this->check_js .= "
				if (document.forms[0].{$this->id}.value!='') document.forms[0].{$this->id}.disabled=true;
			";
		}
		if( $this->attributes['BLOCK_VALUE']=='yes' && $this->db_vars[$this->attributes['VAR']]!="") {
	  		$disabled = "disabled=\"disabled\"";
	  	}
		$action = "";

		if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
			$action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
			//         echo "$action<hr>";
		}

		if ($in ['USER_TIP'] != 'DE' && $this->attributes ['CRYPTO'] == 'yes') {
			$html_parser = new HTML_Parser ( );
			$html_parser->setAttribute ( "type", "hidden" ); 
			$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
            $html_parser->setContent ( 'XXXXXXXXXXXXXXXX' );
			$html_parser->setType ( "INPUT" );
			$this->input_field = '***' . $html_parser->print_ ();
		} else {
			if ($this->attributes ['EMAIL'] != '') {
				$val_email = explode ( "@", $value );
				$this->input_field = "<input type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
			} else {
				//          echo "$action<hr>";
				if ($this->attributes ['CALL_CF'] != '')
					$cf_call = "cf();";
				if ($this->attributes ['ON_BLUR'] != '') {
					//echo "<hr>{$this->id}<hr>";
					$var = $this->id;
					$vars = explode ( "_PROGR_", $var );
					$js_on_blur = preg_replace ( "/document\.forms\[0\]\.(.*?)\.value/i", "document.forms[0].\\1_PROGR_{$vars[1]}.value", $this->attributes ['ON_BLUR'] );
					//print_r($this->attributes);
					$cf_call .= "{$js_on_blur};";
					//echo "<li>$js_on_blur</li>";
				}

				$value = str_replace ( "\"", "&quot;", $value );
				$html_parser = new HTML_Parser ( );
				$html_parser->setAttribute ( "type", "text" );
				$html_parser->setAttribute ( "maxlength", $this->attributes ['VAR_SIZE'] );
				$html_parser->setAttribute ( "size", $this->attributes ['SIZE'] );
				$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
				$html_parser->setAttribute ( "onblur", $cf_call );
				if($this->attributes['ONCHANGE']!='')
					$html_parser->setAttribute ( "onchange", $onchange );
				$html_parser->setAttribute ( $disabled, "" );
				$html_parser->setAttribute ( $action, "" );
				$html_parser->setContent ( $value );
				$html_parser->setType ( "INPUT" );
				$this->input_field = $html_parser->print_ () . $this->attributes ['DEF'] . $agg_;
				/*
				$this->input_field='<input  type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" size="'.$this->attributes['SIZE'].'"
				name="'.$this->attributes['VAR'].'" value="'.$value.'"
				onblur="'.$cf_call.'" '.
				$disabled.
				$action.'>'.$this->attributes['DEF'].''.$agg_;
				*/

			}
		}
		$this->input_txt = $txt;
		if ($this->attributes ['TEXTONLY'] == "yes") {
			$this->input_txt = $value;
			$this->input_field = '';
		}
        $this->input_field.=$add_jquery;
		//if ($this->attributes['DISABLED']!='') $this->input_field='<input type=\'hidden\' name="'.$this->attributes['VAR'].'" value="'.$value.'"><b>'.$value.'</b>';
	}

	/**
	 * Controlli sul campo di tipo codice fiscale
	 *
	 * @param String $value
	 */
	function open_codfisc($value) {

		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
			$alert_msg = "Warning the fiscal code must be 16 characters ";
		else
			$alert_msg = "Attenzione il codice fiscale deve essere di 16 caratteri ";

		$this->invia_js .= "
			if (document.forms[0].{$this->id}.value.length!=16){
				alert('" . $alert_msg . "');
				document.forms[0].{$this->id}.focus();
				return false;
			}
		";
		$this->salva_js .= "
			if (document.forms[0].{$this->id}.value.length!=16){
				alert('" . $alert_msg . "');
				document.forms[0].{$this->id}.focus();
				return false;
			}
		";
	}

	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
		//		global $in;
		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
		     if(strtoupper($this->config_service['lang'])=='IT'){
		         
                if ($value == - 9911)
                    $value = "NA";
                if ($value == - 9922)
                    $value = "NN";
                if ($value == - 9933)
                    $value = "ND";
                if ($value == - 9944)
                    $value = "NP";
                if ($value == - 9955)
                    $value = "TE";
                if ($value == - 9900)
                    $value = "OT";
                  
            }
            else{
      
    			if ($value == - 9911)
    				$value = "NA";
    			if ($value == - 9922)
    				$value = "NK";
    			if ($value == - 9933)
    				$value = "ND";
    			if ($value == - 9944)
    				$value = "NP";
    			if ($value == - 9955)
    				$value = "TE";
    			if ($value == - 9900)
    				$value = "OT";
            }
		}
		
	//modifica by G.Tufano 19/11/2010:
    //controllo che un numero reale non sia tra 0 e 1, altrimenti appare tipo '.32' nella casella di testo
        if ($this->attributes ['VAR_TYPE'] == 'number' && (abs($value) > 0 && abs($value) < 1)){
            if ($value > 0)
                $value = abs($value);
            else $value = "-". abs($value);
        }
		
		$in = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$txt = $this->testo;
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes')
			$input_html = '***';
		else
			$input_html = $value;
		if ($input_html == '')
			$input_html = '&nbsp;';
		$this->input_txt = $txt;

		$this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $this->attributes ['DEF'];
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '">' . $txt . $input_html . '';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>';

	#return $ret;
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
							document.forms[0]." . $this->id . ".value=compila_value;
							document.forms[0]." . $this->id . ".disabled=true;
						}
					}
			";
	}

	/**
	 * Controlli sul valore (maggiore)
	 *
	 * @param String $value
	 */
	function open_max($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
			$controlli .= "
						value=value_of('" . $campo . "', '0');
						";
		} else {
			$value -= 0;
			$controlli .= "value=$value;\n";
		}
		if ($this->attributes ['VAR_TYPE'] == 'number') {
			$controlli .= "
			value=parseFloat(value);
			";
		}
		$testo=make_js($this->testo);
		
		
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		
		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
		$alert_msg = "Warning the value {$testo} must be less than ";
		else
		$alert_msg = "Attenzione il valore di {$testo} deve essere minore di ";

		//E.Gargano 15/05/09 fine
		$controlli.="
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0].".$this->id.".value>value) {";



		$controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";	
		$this->controlli.=$this->addConditions($controlli);
	}

	
	
	
	/**
	 * Controlli sul valore (minore)
	 *
	 * @param String $value
	 */
	function open_min($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
			$controlli .= "
						value=value_of('" . $campo . "', '0');
						";

		} else {
			$value -= 0;
			$controlli .= "value=$value;\n";

		}
		if ($this->attributes ['VAR_TYPE'] == 'number') {
			$controlli .= "
			value=parseFloat(value);
			";

		}

		$testo=make_js($this->testo);

		/* Nicola 20/01/2010
		* Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		*/
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}

		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
		$alert_msg = "Warning the value {$testo} must be greater than ";
		else
		$alert_msg = "Attenzione il valore di {$testo} deve essere maggiore di ";


		//E.Gargano 15/05/09 fine
		$controlli.="
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0].".$this->id.".value<=value) {";

		$controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

		$this->controlli.=$this->addConditions($controlli);
	}

	/**
	 * Controlli sul valore (minore o uguale)
	 *
	 * @param String $value
	 */
	function open_min_eq($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
			$this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
			if ($this->attributes ['SAVE'] != '')
				$this->salva_js .= "
						value=value_of('" . $campo . "', '0');
						";
		} else {
			$value -= 0;
			$this->controlli .= "value=$value;\n";
			if ($this->attributes ['SAVE'] == 'obbligatorio')
				$this->salva_js .= "value=$value;\n";
		}
		if ($this->attributes ['VAR_TYPE'] == 'number') {
			$this->controlli .= "
			value=parseFloat(value);
			";
			if ($this->attributes ['SAVE'] != '')
				$this->salva_js .= "
					value=parseFloat(value);
						";

		}
		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
			$alert_msg = "Warning the value must be equal to or greater than ";
		else
			$alert_msg = "Attenzione il valore di \"" . make_js ( $this->testo ) . "\" deve essere maggiore o uguale a ";

		if ($this->attributes ['SEND'] == 'obbligatorio')
			$this->controlli .= "
				if (document.forms[0]." . $this->id . ".value<value) {";
		else
			$this->controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value<value) {";
		$this->controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
		if ($this->attributes ['SAVE'] == 'obbligatorio')
			$this->salva_js .= "
				if (document.forms[0]." . $this->id . ".value<value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

	}

	/**
	 * Controlli sull'operazione di divisione
	 *
	 * @param String $val
	 */
	function open_dividendo($val) {
		global $in;
		$dividendo = $this->attributes ['DIVIDENDO'];
		if (preg_match ( "/\[/", $dividendo )) {
			//$dividendo = preg_replace ( "/\[(.*?)\]/e", "$1", $dividendo );
			$dividendo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $dividendo );
			$this->check_js .= "
				value=value_of('$dividendo', '0');
				value=value-0;
					";
			$dividendo = $in [$dividendo] + 0;
		} else
			$this->check_js .= "
				value=$dividendo;
				";
		$divisore = $this->attributes ['DIVISORE'];
		#echo "<hr>$divisore<hr>";
		if (preg_match ( "/\[/", $divisore )) {
			//$divisore = preg_replace ( "/\[(.*?)\]/e", "$1", $divisore );
			$divisore = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $divisore );
			$this->check_js .= "
				divisore=value_of('$divisore', '0');
				divisore=divisore-0;
					";
			$divisore = $in [$divisore] + 0;
		} else
			$this->check_js .= "
				divisore=$divisore;
				";
		$this->check_js .= " \n
				//value=value_of('$dividendo', '0');
				//value=value-0;
				valore=value/divisore;
				document.forms[0]." . $this->attributes ['VAR'] . ".value=valore;
				";
		$valore = $dividendo / $divisore;
		$in [$this->attributes ['VAR']] = $valore;
	}

	/**
	 * Controlli di uguaglianza
	 *
	 * @param String $val
	 */
	function open_equals($val) {
		$t = str_replace ( "*", "", $this->testo );
		$this->invia_js .= "value=$val;\n";

		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
			$alert_msg = "must be";
		else
			$alert_msg = "deve essere";

		$this->invia_js .= "
				if (document.forms[0]." . $this->attributes ['VAR'] . ".value!=value) {
					alert('{$t} " . $alert_msg . " '+value);
					document.forms[0]." . $this->attributes ['VAR'] . ".focus();
					return false;
				}
		";

	}

	/**
	 * Esegue del codice javascript
	 *
	 * @param String $value
	 */
	function open_execute($value) {
		$this->check_js .= "
      $value" . ";";
	}

	/**
	 * Esegue del codice js all'onchange
	 *
	 * @param String $value
	 */
	function open_on_change($value) {
		$this->check_js .= "$value
		";
	}

	/**
	 * Gestione dello sfoglia su dizionari
	 *
	 * @param String $value
	 */
	function open_sfoglia($value) {
		$tip_sfo = explode ( ";", $value );
		for($f = 0; $f < count ( $tip_sfo ); $f ++) {
			  //      echo "$f--$tip_sfo[$f]<hr>";
			$but = explode ( ",", $tip_sfo [$f] );
			$but_text = $but [0];
			$but_file = $but [1];
			//$but_file = preg_replace ( "!\[(.*?)\]!i", '$1', $but_file );
			$but_file = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $but_file );
			$but_file = str_replace ( "|and|", '&', $but_file );

			if ($this->attributes ['SFOGLIA_ADD_PARAM'] != '') {
				$params = explode ( ",", $this->attributes ['SFOGLIA_ADD_PARAM'] );
				foreach ( $params as $key => $val ) {
					$but_file .= "&{$val}={$_GET[$val]}";
				}
			}
			if(preg_match('/^js:/',$but_text)){
				$but_text=str_replace("js:","",$but_text);
				$agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
			}
			else{
				if (strtolower($but_text) == 'reset' || strtolower($but_text) == 'cancella' || $this->attributes['SFOGLIA_CLEAR_LABEL']==$but_text)
					$agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
				else
					$agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
					//         echo "$but_text -- $but_file<hr>";
				}
				$this->input_field .= $agg;
			
		}
	}

	/**
	 * Effettua in js operazione di somma
	 *
	 * @param String $val
	 */
	function open_sum($val) {
		global $in;
		$campi = explode ( ",", $val );
		$minval = $this->attributes ['SUM_MAGGIORE'] + 0;
		$maxval = $this->attributes ['SUM_MINORE'] + 0;
		$check = "if (value >= $minval)";
		if ($maxval > 0)
			$check = "if (value >= $minval && value <= $maxvalue)";
		$somma = 0;
		for($i = 0; $i < count ( $campi ); $i ++) {
			if ($i == 0)
				$this->check_js .= " \n
					document.forms[0]." . $this->attributes ['VAR'] . ".value='';
				";
			if (preg_match ( "/\[/", $campi [$i] )) {
				//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $campi [$i] );
				$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $campi [$i] );
				$somma += $in [$campo];
				$this->check_js .= "
						value=value_of('" . $campo . "', '0');
						value=value-0;
						//alert (value);
						";
			} else {
				$somma += $campi [$i];
				$this->check_js .= "
						value=" . $campi [$i] . ";
						";
			}
			$this->check_js .= "
					//$check {
					somma=document.forms[0]." . $this->attributes ['VAR'] . ".value - 0;
					somma+=value;
					document.forms[0]." . $this->attributes ['VAR'] . ".value=somma;
					//}
				";
		}
		$in [$this->attributes ['VAR']] = $somma;
	}

	/**
	 * Trasforma il campo in uppercase
	 *
	 * @param String $value
	 */
	function open_upper($value) {
		$this->check_js .= "
			document.forms[0].{$this->id}.value=document.forms[0].{$this->id}.value.toUpperCase();
		";
	}

	/**
	 * Visualizzazione nella modalità  progressiva
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	function all_in($var, $i, $row, $this_closed) {
		$val=$this->attributes;
		$row[$val['VAR']]=str_replace("\"", "'", $row[$var]);
		if ($this_closed){
			$body="
			<td class=sc4bis>
				<b>{$row[$var]}</b>
				</td>
				";
				$ret['body']=$body;
				return $ret;
		}
		if (isset ( $val ['SFOGLIA'] )
		//&& $this->xml_form->session_vars ['USER_TIP'] == 'DE'
		&& ! $this_closed) {
			$value = $val ['SFOGLIA'];
			$tip_sfo = explode ( ";", $value );
			$but = explode ( ",", $tip_sfo [0] );
			$but_text = $but [0];
			$but_file = $but [1];
			$but_file = preg_replace ( "!\[(.*?)\]!i", '$1' . "_PROGR_{$i}", $but_file );
			$but_file = str_replace ( "|and|", '&', $but_file );

			if ($val ['SFOGLIA_ADD_PARAM'] != '') {
				$params = explode ( ",", $val ['SFOGLIA_ADD_PARAM'] );
				foreach ( $params as $kp => $vp ) {
					$but_file .= "&{$vp}={$_GET[$vp]}";
				}
			}
			if ($row [$val ['VAR']] == '')
				$last_call_sfoglia = $but_file;
			else
				$last_call_sfoglia = '';

			if ($but_text == 'cancella')
				$agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
			else if($val ['SFOGLIA_SINGOLO']!='no'){
				if ($row [$val ['VAR']] == '')	$agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
			}
		} else
			$agg = '';
			
		$align="";
		if($this->attributes['ALIGN']!="")
		$align=" align=\"{$this->attributes['ALIGN']}\"";
		
		if (isset ( $val ['DISABLED_ALWAYS'] )) {
			$body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
		} else {
			if (isset ( $val ['DISABLED'] ) && $row[$val['VAR']]!='') {
				$body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
			} else {
				$maxlength="";

				if(isset($val['VAR_SIZE'])) $maxlength="MAXLENGTH=\"{$val['VAR_SIZE']}\"";
				$size="";
				if(isset($val['SIZE'])) $maxlength.=" SIZE=\"{$val['SIZE']}\"";
				$body .= "
				<td class=sc4bis $align >
				<input type='textbox' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\" $maxlength>$agg
				</td>
				";
			}
		}
		$ret['last_call_sfoglia']=$last_call_sfoglia;
		$ret['body']=$body;
		return $ret;
	}

	/**
	 * Visualizzazione nella modalità  progressiva (header)
	 *
	 * @param field_textbox $field
	 * @param number $m_p
	 * @param form $xml_form
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		$select_field .= $field . ",";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$onclick_action = "";
		for($i = 1; $i <= $m_p; $i ++) {
			$onclick_action .= "document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_TOT.value;
			";
		}
		$field_tot .= "
			<input type='textbox' name='{$field}_TOT'><br />
			
			<!--input type='button' value='applica a tutti' onclick=\"$onclick_action\"-->
			<button class=\"btn btn-xs btn-warning\" type=\"button\" onclick=\"$onclick_action\">
				applica a tutti
			</button>
			
		";
		$tr_agg .= "<td class='int'>$field_tot &nbsp;</td>";
		}
		return $tr_agg;
	}
}

?>
