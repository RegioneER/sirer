<?

include_once "field.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package Fields
 */
class field_textbox extends field
{
    var $max_js;
    var $min_js;

    //Ridefinisco il costruttore
    function __construct($conn=null, $xml_form=null, $i=null, $session_vars=null, $db_vars=null, $service=null, $errors=null)
    {
        parent::field($conn, $xml_form, $i, $session_vars, $db_vars, $service, $errors);
        if ($this->attributes['SHOW_CRF'] == 'yes' && isset($_GET['CRF_BLANK'])) {
            unset($this->attributes['HIDE']);
        }
        //$this->testo=str_replace("*","",$this->testo);

    }


    /**
     * Costruisce il codice js del campo in con autocomplete
     *
     * + @param String $value
     */

    function autocomplete_js()
    {
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

    function autocomplete_js_field()
    {
        $actions = null;
        $lista=null;
        global $conn;
        $sql = new query($conn);

        $sql_query = $this->attributes['DIZIONARIO'];
        $sql_query = str_ireplace("[service]", $this->service, $sql_query);
        $replaceRet = query::varGlobReplace($sql_query);
        $sql_query = $replaceRet['sql'];
        //$sql->set_sql($sql_query);
        $sql->exec($sql_query, $replaceRet['binded']);
        while ($sql->get_row()) {
            $curr_obj = "";
            foreach ($sql->row as $field => $valore) {
                $valore = str_replace('"', '', $valore);
                $curr_obj .= "{$field}:\"{$valore}\",
                ";
            }
            $sql->row[$this->id] = str_replace('"', '', $sql->row[$this->id]);
            $curr_obj = rtrim($curr_obj, ',');
            $lista .= '{value:"' . $sql->row[$this->id] . '",label:"' . $sql->row[$this->id] . '",desc:{' . $curr_obj . '}},';
        }

        $lista = rtrim($lista, ',');
        $lista = str_replace("'", "\\'", $lista);
        if ($this->attributes['OPTIONS'] != '') {
            $options = rtrim($this->attributes['OPTIONS'], ', ') . ',';
        }
        $add_jquery = "
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
    function open_($value, $mock = false)
    {
        $agg_=null;
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

        if (isset ($this->values) && is_array($this->values))
            foreach ($this->values as $key => $val)
                $value = $val;
        if ($inputval [$this->attributes ['VAR']] != '')
            $value = $inputval [$this->attributes ['VAR']];
        if ($in [$this->attributes ['VAR']] != '')
            $value = $in [$this->attributes ['VAR']];

        if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
            if (strtoupper($this->config_service['lang']) == 'IT') {

                if ($value == -9911)
                    $value = "NA";
                if ($value == -9922)
                    $value = "NN";
                if ($value == -9933)
                    $value = "ND";
                if ($value == -9944)
                    $value = "NP";
                if ($value == -9955)
                    $value = "TE";
                if ($value == -9900)
                    $value = "OT";

            } else {
                if ($value == -9911)
                    $value = "NA";
                if ($value == -9922)
                    $value = "NK";
                if ($value == -9933)
                    $value = "ND";
                if ($value == -9944)
                    $value = "NP";
                if ($value == -9955)
                    $value = "TE";
                if ($value == -9900)
                    $value = "OT";
            }

        }
        if ($this->attributes['AUTOCOMPLETE']) {
            global $autocomplete;
            if (!$autocomplete) {
                $this->script .= $this->autocomplete_js();
                $autocomplete = true;
            }

            $add_jquery = $this->autocomplete_js_field();
        }
        //modifica by G.Tufano 19/11/2010:
        //controllo che un numero reale non sia tra 0 e 1, altrimenti appare tipo '.32' nella casella di testo
        if ($this->attributes ['VAR_TYPE'] == 'number' && (abs($value) > 0 && abs($value) < 1)) {
            if ($value > 0)
                $value = abs($value);
            else $value = "-" . abs($value);
        }


        if ($mock) {
            $this->input_field = '"';
            $cols = 1;
            $this->input_field .= "&nbsp;<input x-webkit-speech type='text' <%= rf.get(Formbuilder.options.mappings.DISABLED) && \'disabled\' %>  size='<%= rf.get(Formbuilder.options.mappings.SIZE) %>' /> &nbsp;<%= rf.get(Formbuilder.options.mappings.DEF) %>";
            $this->input_field .= '"';
        } else {
            $disabled = "";
            if ($this->attributes ['DISABLED'] != '') {
                if ($value != '')
                    $disabled = "disabled=\"disabled\"";
                $this->check_js .= "
					if (document.forms[0].{$this->id}.value!='') document.forms[0].{$this->id}.disabled=true;
				";
            }
            if ($this->attributes['BLOCK_VALUE'] == 'yes' && $this->db_vars[$this->attributes['VAR']] != "") {
                $disabled = "disabled=\"disabled\"";
            }
            $action = "";

            if ($this->attributes ['DISABLED'] != '') {
                $disabled = "disabled='disabled'";
            }
            if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
                if ($this->attributes ['ACTION_TYPE'] == "onblur") {
                    // Se gi  definito un onblur nel field , concateno l'upper case nel caso in cui scrivesse NA
                    $this->attributes ['ON_BLUR'] = $this->attributes ['ON_ACTION'] . "this.value=this.value.toUpperCase();";
                } else {
                    //Se viene digitato NA ad es. viene messo upper case.
                    $action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
                }
                //         echo "$action<hr>";
            }
            if ($this->attributes ['VAR_TYPE'] == "number") {
                $this->attributes ['ON_BLUR'] = "this.value=this.value.replace(/^\s*/, '').replace(/\s*$/, '');" . $this->attributes ['ON_BLUR'];
            } else {
                $this->attributes ['ON_BLUR'] = "if(this.value.replace(/^\s*/, '').replace(/\s*$/, '')==''){this.value=''};" . $this->attributes ['ON_BLUR'];
            }
            if ($in ['USER_TIP'] != 'DE' && $this->attributes ['CRYPTO'] == 'yes') {
                $html_parser = new HTML_Parser ();
                $html_parser->setAttribute("type", "hidden");
                $html_parser->setAttribute("name", $this->attributes ['VAR']);
                $html_parser->setContent('XXXXXXXXXXXXXXXX');
                $html_parser->setType("INPUT");
                $this->input_field = '***' . $html_parser->print_();
            } else {
                if ($this->attributes ['EMAIL'] != '') {
                    $val_email = explode("@", $value);
                    $this->input_field = "<input  x-webkit-speech type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input  x-webkit-speech type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input  x-webkit-speech type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
                } else {
                    //          echo "$action<hr>";
                    if ($this->attributes ['CALL_CF'] != '')
                        $cf_call = "cf();";
                    if ($this->attributes ['ON_BLUR'] != '') {
                        //echo "<hr>{$this->id}<hr>";
                        $var = $this->id;
                        $vars = explode("_PROGR_", $var);
                        $js_on_blur = preg_replace("/document\.forms\[0\]\.(.*?)\.value/i", "document.forms[0].\\1_PROGR_{$vars[1]}.value", $this->attributes ['ON_BLUR']);
                        //print_r($this->attributes);
                        $cf_call .= "{$js_on_blur};";
                        //echo "<li>$js_on_blur</li>";
                    }

                    $value = str_replace("\"", "&quot;", $value);
                    $html_parser = new HTML_Parser ();
                    $html_parser->setAttribute("type", "text");
                    $html_parser->setAttribute("maxlength", $this->attributes ['VAR_SIZE']);
                    $html_parser->setAttribute("size", $this->attributes ['SIZE']);
                    $html_parser->setAttribute("name", $this->attributes ['VAR']);
                    $html_parser->setAttribute("id", $this->id);
                    $html_parser->setAttribute("onblur", $cf_call);
                    if ($this->attributes['ONCHANGE'] != '')
                        $html_parser->setAttribute("onchange", $onchange);
                    $html_parser->setAttribute($disabled, "");
                    $html_parser->setAttribute($action, "");
                    $html_parser->setContent($value);
                    $html_parser->setType("INPUT");
                    $this->input_field = $html_parser->print_() . $this->attributes ['DEF'] . $agg_;
                    /*
                    $this->input_field='<input  type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" size="'.$this->attributes['SIZE'].'"
                    name="'.$this->attributes['VAR'].'" value="'.$value.'"
                    onblur="'.$cf_call.'" '.
                    $disabled.
                    $action.'>'.$this->attributes['DEF'].''.$agg_;
                    */

                }
            }
        }
        $this->input_txt = $txt;
        if ($this->attributes ['TEXTONLY'] == "yes") {
            $this->input_txt = $value;
            $this->input_field = '';
        }

        if (isset ($in['FIELD']) and $in['FIELD'] == $this->attributes['DESCRIPTION']) {
            $this->input_field = '
		      <table class="eqfield"><tr ><td >' . $html_parser->print_() . '</td></tr></table>
		      ';
        }

        if (isset($this->attributes['BROWSE']) && $this->attributes['BROWSE'] != '') {
            $link = $this->attributes['BROWSE'];
            $params = str_replace("|", "&", $this->attributes['BROWSE_PARAM']);
            $link .= "?" . $params;
            $this->input_field .= "&nbsp;<button id='BROWSE_{$this->id}' class=\"btn btn-sm btn-success\">
										" . mlOut("System.Browse", "Browse") . " &nbsp;<i class=\" el-icon-folder-open align-top bigger-125\"></i>
									</button>
						<script>
						$('#BROWSE_{$this->id}').click(function(){
							bootbox.dialog({
								title: '" . mlOut("System.Browse", "Browse") . "',
								className: 'browse_class',
								message: '<iframe style=\"border:0px;width:100%;\" src=\"$link\"/>'
							});	
						});
						</script>";
        }
        if (isset($this->attributes['SEARCH']) && $this->attributes['SEARCH'] != '') {
            $link = $this->attributes['SEARCH'];
            $params = str_replace("|", "&", $this->attributes['SEARCH_PARAM']);
            $link .= "?" . $params;
            $this->input_field .= "&nbsp;<button id='SEARCH_{$this->id}' class=\"btn btn-sm btn-success\">
				" . mlOut("System.Search", "Search") . " &nbsp;<i class=\" el-icon-search align-top bigger-125\"></i>
				</button>
				<script>
				$('#SEARCH_{$this->id}').click(function(){
					bootbox.dialog({
						className: 'search_class',
						title: '" . mlOut("System.Search", "Search") . "',
						message: '<iframe style=\"border:0px;width:100%;\" src=\"$link\"/>'
					});
				});
				</script>";
        }

        $this->input_field .= $add_jquery;
        //if ($this->attributes['DISABLED']!='') $this->input_field='<input type=\'hidden\' name="'.$this->attributes['VAR'].'" value="'.$value.'"><b>'.$value.'</b>';
    }

    function open_sfoglia_cerca($value)
    {
        $scType = 3;
        if (isset($this->attributes['SC_TYPE'])) {
            $scType = 0;
            if (preg_match("!cerca!i", $this->attributes['SC_TYPE'])) $scType += 1;
            if (preg_match("!sfoglia!i", $this->attributes['SC_TYPE'])) $scType += 2;
        }
        $mapFields = [];
        $maps = explode("|", $this->attributes['SC_MAP']);
        foreach ($maps as $map) {
            $mapFields[explode(":", $map)[1]] = explode(":", $map)[0];
        }
        $tb = $this->service . "_" . $this->attributes['SC_TB'];
        if ($scType == 1 || $scType == 3) {
            $searchFields = [];
            $maps = explode("|", $this->attributes['SC_CERCA']);
            foreach ($maps as $map) {
                if (explode(":", $map)[1] == null) {
                    $mode = "fullmatch";
                } else {
                    $mode = explode(":", $map)[1];
                }
                $searchFields[explode(":", $map)[0]] = $mode;
            }
            $this->input_field .= $this->sc_cerca($tb, $mapFields, $searchFields);
        }
        if ($scType >= 2 || $scType == 3) {
            $selectableLevel = $this->attributes['SC_SFOGLIA_SELECTABLE_LEVEL'];
            $sfogliaFields = [];
            $maps = explode("|", $this->attributes['SC_SFOGLIA']);
            foreach ($maps as $map) {
                if (explode(":", $map)[1] == null) {
                    $mode = "auto";
                } else {
                    $mode = explode(":", $map)[1];
                }
                $sfogliaFields[explode(":", $map)[0]] = $mode;
            }
            $this->input_field .= $this->sc_sfoglia($tb, $mapFields, $sfogliaFields, $selectableLevel);
        }

    }

    function sc_cerca($tb, $mapFields, $searchFields)
    {
        $fileName = str_replace(".xml", "", $this->xml_form->filename);
        $btnLabel = mlOut($fileName . "." . $this->id . ".cercaLabel", "Cerca ...");
        $str = "&nbsp;<button id='btnCerca{$this->id}' class='btn btn-xs btn-info'><i class='fa fa-search'></i> {$btnLabel}</button>";
        $arguments = [];
        $arguments['table'] = $tb;
        $arguments['mapFields'] = $mapFields;
        $arguments['searchFields'] = $searchFields;
        $arguments['xmlForm'] = $fileName;
        $action = "cerca";
        include_once "tokenUtils.inc.php";
        $token = TokenUtils::createToken($this->conn, $this->service, "global", $action, $arguments);
        $str .= "
        <script>
        $(document).ready(function(){
            $('#btnCerca{$this->id}').click(function(){
               buildModalCerca('" . urlencode($token) . "');
            });
            
        });
        
        </script>
        ";
        return $str;
    }

    function sc_sfoglia($tb, $mapFields, $sfogliaFields, $selectableLevel)
    {
        $fileName = str_replace(".xml", "", $this->xml_form->filename);
        $btnLabel = mlOut($fileName . "." . $this->id . ".sfogliaLabel", "Sfoglia ...");
        $str = "&nbsp;<button id='btnSfoglia{$this->id}' class='btn btn-xs btn-info'><i class='fa fa-book'></i> {$btnLabel}</button>";
        $arguments = [];
        $arguments['table'] = $tb;
        $arguments['mapFields'] = $mapFields;
        $arguments['sfogliaFields'] = $sfogliaFields;
        $arguments['xmlForm'] = $fileName;
        $arguments['selectableLevel'] = $selectableLevel;
        $action = "sfoglia";
        include_once "tokenUtils.inc.php";
        $token = TokenUtils::createToken($this->conn, $this->service, "global", $action, $arguments);
        $str .= "
        <script>
        $(document).ready(function(){
            $('#btnSfoglia{$this->id}').click(function(){
               buildModalSfoglia('" . urlencode($token) . "');
            });
            
        });
        
        </script>
        ";
        return $str;
    }

    /**
     * Controlli sul campo di tipo codice fiscale
     *
     * @param String $value
     */
    function open_codfisc($value)
    {

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
    function close_($value)
    {
        //		global $in;
        if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
            if (strtoupper($this->config_service['lang']) == 'IT') {

                if ($value == -9911)
                    $value = "NA";
                if ($value == -9922)
                    $value = "NN";
                if ($value == -9933)
                    $value = "ND";
                if ($value == -9944)
                    $value = "NP";
                if ($value == -9955)
                    $value = "TE";
                if ($value == -9900)
                    $value = "OT";

            } else {

                if ($value == -9911)
                    $value = "NA";
                if ($value == -9922)
                    $value = "NK";
                if ($value == -9933)
                    $value = "ND";
                if ($value == -9944)
                    $value = "NP";
                if ($value == -9955)
                    $value = "TE";
                if ($value == -9900)
                    $value = "OT";
            }
        }

        //modifica by G.Tufano 19/11/2010:
        //controllo che un numero reale non sia tra 0 e 1, altrimenti appare tipo '.32' nella casella di testo
        if ($this->attributes ['VAR_TYPE'] == 'number' && (abs($value) > 0 && abs($value) < 1)) {
            if ($value > 0)
                $value = abs($value);
            else $value = "-" . abs($value);
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
        if ($this->deleted == 2 && $this->attributes['MAIN'] != "yes") {
            $input_html = "<span style='text-decoration:line-through;'>$input_html</span>";
        }
        if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL'] != '') {
            $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->attributes, $this->xml_form);
            $input_html .= $audit_trail->audit_trail_popup($in);
        }

        $db = $this->attributes['VAR'];
        if (isset ($_GET ['CRF_ANNOTE'])) {
            $input_html .= $this->xml_form->form['TABLE'] . '.' . $db;
        }

        $this->input_txt = $txt;
        $this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $this->attributes ['DEF'];
        if (isset ($this->attributes ['COLSPAN']) and $this->cols_form > 1)
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
    function open_compila($value)
    {
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
    function open_max($value)
    {
        $controlli=null;
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
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
        $this->input_txt = str_replace("<font color=red></font>", "", $this->input_txt);
        $testo_js = trim(make_js($this->input_txt));
        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the value must be less than ";
        else
            $alert_msg = "Attenzione il valore deve essere minore di ";

        //E.Gargano 15/05/09 fine
        $controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value>value) {";


        $controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
        $this->controlli .= $this->addConditions($controlli);
    }


    /**
     * Controlli sul valore (minore)
     *
     * @param String $value
     */
    function open_min($value)
    {
        $controlli=null;
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
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

        $testo = make_js($this->testo);

        /* Nicola 20/01/2010
        * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
        */
        if ($this->attributes['LABEL_JS'] != "") {
            $testo = $this->attributes['LABEL_JS'];
        }

        //traduzione del messaggio di alert in inglese
        $this->input_txt = str_replace("<font color=red></font>", "", $this->input_txt);
        $testo_js = trim(make_js($this->input_txt));
        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the value {$testo} must be greater than ";
        else
            $alert_msg = "Attenzione il valore di {$testo} deve essere maggiore di ";


        //E.Gargano 15/05/09 fine
        $controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value<=value) {";

        $controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

        $this->controlli .= $this->addConditions($controlli);
    }

    /**
     * Controlli sul valore (minore o uguale)
     *
     * @param String $value
     */
    function open_min_eq($value)
    {
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
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
            $alert_msg = "Attenzione il valore di \"" . make_js($this->testo) . "\" deve essere maggiore o uguale a ";

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
    function open_dividendo($val)
    {
        global $in;
        $dividendo = $this->attributes ['DIVIDENDO'];
        if (preg_match("/\[/", $dividendo)) {
            $dividendo = preg_replace("/\[(.*?)\]/e", "$1", $dividendo);
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
        if (preg_match("/\[/", $divisore)) {
            $divisore = preg_replace("/\[(.*?)\]/e", "$1", $divisore);
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
    function open_equals($val)
    {
        $t = str_replace("*", "", $this->testo);
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
    function open_execute($value)
    {
        $this->check_js .= "
      $value" . ";";
    }

    /**
     * Esegue del codice js all'onchange
     *
     * @param String $value
     */
    function open_on_change($value)
    {
        $this->check_js .= "$value
		";
    }

    /**
     * Gestione dello sfoglia su dizionari
     *
     * @param String $value
     */
    function open_sfoglia($value)
    {
        $tip_sfo = explode(";", $value);
        for ($f = 0; $f < count($tip_sfo); $f++) {
            //         echo "$f--$tip_sfo[$f]<hr>";
            $but = explode(",", $tip_sfo [$f]);
            $but_text = $but [0];
            $but_file = $but [1];
            $but_file = preg_replace("!\[(.*?)\]!i", '$1', $but_file);
            $but_file = str_replace("|and|", '&', $but_file);

            if ($this->attributes ['SFOGLIA_ADD_PARAM'] != '') {
                $params = explode(",", $this->attributes ['SFOGLIA_ADD_PARAM']);
                foreach ($params as $key => $val) {
                    $but_file .= "&{$val}={$_GET[$val]}";
                }
            }
            if (preg_match('/^js:/', $but_text)) {
                $but_text = str_replace("js:", "", $but_text);
                $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
                $this->input_field .= $agg;
            } else {
                if (strtolower($but_text) == 'reset' || strtolower($but_text) == 'cancella' || $this->attributes['SFOGLIA_CLEAR_LABEL'] == $but_text)
                    $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
                else
                    $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
                //         echo "$but_text -- $but_file<hr>";
                $this->input_field .= $agg;
            }
        }
    }

    /**
     * Effettua in js operazione di somma
     *
     * @param String $val
     */
    function open_sum($val)
    {
        global $in;
        $campi = explode(",", $val);
        $minval = $this->attributes ['SUM_MAGGIORE'] + 0;
        $maxval = $this->attributes ['SUM_MINORE'] + 0;
        $check = "if (value >= $minval)";
        if ($maxval > 0)
            $check = "if (value >= $minval && value <= $maxval)";
        $somma = 0;
        for ($i = 0; $i < count($campi); $i++) {
            if ($i == 0)
                $this->check_js .= " \n
					document.forms[0]." . $this->attributes ['VAR'] . ".value='';
				";
            if (preg_match("/\[/", $campi [$i])) {
                $campo = preg_replace("/\[(.*?)\]/e", "$1", $campi [$i]);
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
    function open_upper($value)
    {
        $this->check_js .= "
			document.forms[0].{$this->id}.value=document.forms[0].{$this->id}.value.toUpperCase();
		";
    }

    /**
     * Visualizzazione nella modalit  progressiva
     *
     * @param String $var
     * @param number $i
     * @param array $row
     * @param boolean $this_closed
     * @return String
     */
    function all_in($var, $i, $row, $this_closed)
    {
        $body=null;
        $val = $this->attributes;
        $row[$val['VAR']] = str_replace("\"", "'", $row[$var]);
        if ($this_closed) {
            $body = "
			<td class=sc4bis>
				<b>{$row[$var]}</b>
				</td>
				";
            $ret['body'] = $body;
            return $ret;
        }
        if (isset ($val ['SFOGLIA'])
            //&& $this->xml_form->session_vars ['USER_TIP'] == 'DE'
            && !$this_closed) {
            $value = $val ['SFOGLIA'];
            $tip_sfo = explode(";", $value);
            $but = explode(",", $tip_sfo [0]);
            $but_text = $but [0];
            $but_file = $but [1];
            $but_file = preg_replace("!\[(.*?)\]!i", '$1' . "_PROGR_{$i}", $but_file);
            $but_file = str_replace("|and|", '&', $but_file);

            if ($val ['SFOGLIA_ADD_PARAM'] != '') {
                $params = explode(",", $val ['SFOGLIA_ADD_PARAM']);
                foreach ($params as $kp => $vp) {
                    $but_file .= "&{$vp}={$_GET[$vp]}";
                }
            }
            if ($row [$val ['VAR']] == '')
                $last_call_sfoglia = $but_file;
            else
                $last_call_sfoglia = '';

            if ($but_text == 'cancella')
                $agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
            else if ($val ['SFOGLIA_SINGOLO'] != 'no') {
                if ($row [$val ['VAR']] == '') $agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
            }
        } else
            $agg = '';

        $align = "";
        if ($this->attributes['ALIGN'] != "")
            $align = " align=\"{$this->attributes['ALIGN']}\"";

        if (isset ($val ['DISABLED_ALWAYS'])) {
            $body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
        } else {
            if (isset ($val ['DISABLED']) && $row[$val['VAR']] != '') {
                $body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
            } else {
                $maxlength = "";

                if (isset($val['VAR_SIZE'])) $maxlength = "MAXLENGTH=\"{$val['VAR_SIZE']}\"";
                $size = "";
                if (isset($val['SIZE'])) $maxlength .= " SIZE=\"{$val['SIZE']}\"";
                $body .= "
				<td class=sc4bis $align >
				<input  x-webkit-speech type='textbox' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\" $maxlength>$agg
				</td>
				";
            }
        }

        if ($this->config_service['eQuery'] == '1' && (isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM']))) {
            $eQ_content = "<input x-webkit-speech type='textbox' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\" $maxlength >$agg ";

            $eQ = $this->eQ_all_in($var, $i, $row, $this_closed);

            if ($this->xml_form->tb_vals[$this->id]) {
                $row[$var] = $this->xml_form->tb_vals[$this->id];
            }
        }

        if ($this_closed) {
            if (isset($this->session_vars['AUDIT_TRAIL']) && $this->session_vars['AUDIT_TRAIL'] != '') {
                $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->attributes, $this->xml_form);
                $at = $audit_trail->audit_trail_popup($this->session_vars, $i);
            } elseif (isset($_GET['CRF_ANNOTE'])) {
                $db = $this->attributes['VAR'];
                $table = $this->xml_form->form['TABLE'];
                $annote = "<b><br><u>$table.$db</u></b>";
            }
            $body = "
			<td class=sc4bis id=" . $var . '_PROGR_' . $i . ">&nbsp;
				<span id='view_field_{$var}_PROGR_{$i}'><b>{$row[$var]}</b> </span> $at $annote 
				<span id='mod_field_{$var}_PROGR_{$i}' style=\"display:none\">$eQ_content</span> $eQ
				</td>
				";
            $ret['body'] = $body;
            return $ret;
        }

        $ret['last_call_sfoglia'] = $last_call_sfoglia;
        $ret['body'] = $body;
        return $ret;
    }

    /**
     * Visualizzazione nella modalit  progressiva (header)
     *
     * @param field_textbox $field
     * @param number $m_p
     * @param form $xml_form
     * @return String
     */
    static function S_all_in($field, $m_p, $xml_form)
    {
        $field_tot=null;
        $tr_agg=null;
        $select_field = $field . ",";
        if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
            $onclick_action = "";
            for ($i = 1; $i <= $m_p; $i++) {
                $onclick_action .= "document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_TOT.value;
			";
            }
            $field_tot .= "
			<input x-webkit-speech type='textbox' name='{$field}_TOT'><br />
			<input type='button' value='applica a tutti' onclick=\"
			$onclick_action
			\">
		";
            $tr_agg .= "<td class='int'>$field_tot &nbsp;</td>";
        }
        return $tr_agg;
    }

    function builder_js()
    {
        /*	$field_description['field']="textbox";
            $field_description['order']=0;
            $field_description['view']= <<< EOT
                "<input type='text' class='rf-size-<%= rf.get(Formbuilder.options.mappings.SIZE) %>' />"
    EOT;
            $field_description['edit'][]='edit/db_info';
            $field_description['edit'][]='edit/allowed_values';
            $field_description['edit'][]='edit/bytb';
            $field_description['edit'][]='edit/main_sub';
            $field_description['edit'][]='edit/condition';
            $field_description['edit'][]='edit/javascript';
            $field_description['edit'][]='edit/formatting';
            $field_description['edit'][]='edit/save_send';
            $field_description['addButton']['class']='fa fa-font';
            $field_description['addButton']['label']='Textbox';

            return $field_description;
        */
        $field_description['field'] = "textbox";
        $field_description['order'] = 1;

        $this->open_('', true);
        $field_description['view'] = "\"<div class=\'form-group\' style='height:10px'><div><label class=\'col-sm-5 control-label no-padding-right\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></label><div class='col-sm-7'>\"+
		" . $this->input_field . "+" .
            "\"</div></div></div>\"";

        $field_description['edit'][] = 'edit/db_info';
        $field_description['edit'][] = 'edit/allowed_values';
        $field_description['edit'][] = 'edit/bytb';
        $field_description['edit'][] = 'edit/main_sub';
        $field_description['edit'][] = 'edit/condition';
        $field_description['edit'][] = 'edit/javascript';
        $field_description['edit'][] = 'edit/formatting';
        $field_description['edit'][] = 'edit/save_send';
        $field_description['addButton']['class'] = 'fa fa-font';
        $field_description['addButton']['label'] = 'Textbox';


        return $field_description;
    }
}

?>
