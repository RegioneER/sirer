<?

include_once "field.inc";

class field_date_hyper extends field
{


    /************************************
     *
     * Libreria Data di tipo drop down sui mesi.<
     * Molto simile alla data standard in XMR , con calendario e select sui mesi
     * con relativa decodifica.
     *
     * TODO:
     *
     *** Funzionamento:
     * 1- includere nel template.htm del servizio le librerie:
     * <script type="text/javascript" src="libs/js_tooltip/calendar.js"></script>
     * <link  href="libs/js_tooltip/calendar.css" rel="stylesheet" type="text/css" />
     * 2- verificare che l'immagine calendar_icon.gif si prensente nella cartella (o link).
     * [nomeservizio]/html/images/
     *
     *** Lingua:
     * Default: Italiano.
     * Per settare l'inglese , aggiungere:
     * nel file config.inc: $config_service['lang']='en';
     * nel file template.htm: <script type="text/javascript" src="libs/js_tooltip/calendar_en.js"></script>
     *
     * Per info: Andrea Colabufalo.
     * **********************************/

    /**
     * open_
     * Costruisce il codice html del campo in compilazione
     *
     * @param string $value
     */
    function open_($value)
    {
        $ret = null;
        $input_html = null;
        if (!isset($this->attributes['SEND'])) $this->attributes['SEND'] = 'facoltativo';
//		print_r($this->xml_form->salva_js);
//		$this->xml_form->salva_js='';
//		$this->xml_form->check_js='';
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $this->validata = true;
        $this->input_txt = str_replace("<font color=red></font>", "", $this->input_txt);
        //$this->testo=str_replace("*","",$this->testo);
        $add_cal = '
<script type="text/javascript" src="libs/js_tooltip/calendar.js"></script>
<script type="text/javascript" src="libs/js_tooltip/calendar_en.js"></script>
<link  href="libs/js_tooltip/calendar.css" rel="stylesheet" type="text/css" />

		<script>
		 var ' . $this->attributes['VAR'] . '_cal=new CalendarPopup(\'' . $this->attributes['VAR'] . '_cal_div\');
		 ' . $this->attributes['VAR'] . '_cal.showNavigationDropdowns();
		 ' . $this->attributes['VAR'] . '_cal.setReturnFunction("setMultipleValues_' . $this->attributes['VAR'] . '");
		 function setMultipleValues_' . $this->attributes['VAR'] . ' (y,m,d) {
		     document.forms[0].' . $this->attributes['VAR'] . 'Y.value=y;
 		     if(m<10 && m>0){m="0"+m;}
			document.forms[0].' . $this->attributes['VAR'] . 'M.value=m;
		     document.forms[0].' . $this->attributes['VAR'] . 'D.value=d;
    	 }
    	 document.write(\'<a href="#" name="' . $this->attributes['VAR'] . '_cal_anchor" id="' . $this->attributes['VAR'] . '_cal_anchor" onclick="' . $this->attributes['VAR'] . '_cal.showCalendar(\\\'' . $this->attributes['VAR'] . '_cal_anchor\\\');return false;" >&nbsp;<img width="20"  style="vertical-align:bottom;" height="20" src="/images/calendar_icon.gif"></a><span id="' . $this->attributes['VAR'] . '_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
    	 </script>

		 ';

        $disabled = "";
        if ($this->attributes ['DISABLED'] != '') {
            $disabled = "disabled='disabled'";
            $add_cal = '';
        }
        $txt = $this->testo;
        $is_sysdate = false;
        if (in_array('sysdate', array_keys(array_change_key_case($this->values))) || strtolower($value) == 'sysdate') {
            $is_sysdate = true;
            $value = date("d/m/Y");
        }
        if ($value == '') {
            $keys = array_keys($this->values);
            $value = $keys[0];
        }

        if (preg_match("/\//", $value)) {
            $dd = substr($value, 0, 2);
            $mm = substr($value, 3, 2);
            $yyyy = substr($value, 6, 4);
        } else {
            $dd = substr($value, 0, 2);
            $mm = substr($value, 2, 2);
            $yyyy = substr($value, 4, 4);
        }

        /**  Gestione NA e NK salvati in Db con form in compilazione **/
        $months_nn['NA'] = -9911;
        $months_nn['NK'] = -9922;
        if (!$is_sysdate) {
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 0, 2) != 'OK') $dd = substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 0, 2);
            else $dd = substr($value, 0, 2);
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 2, 2) != 'OK') $mm = $months_nn[substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 2, 2)];
            else $mm = substr($value, 2, 2);
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 4, 2) != 'OK') $yyyy = substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 4, 2);
            else $yyyy = substr($value, 4, 4);
        }
        /**  Fine Gestione NA e NK salvati in Db con form in compilazione **/

        $select_months = "<select  id='{$this->attributes['VAR']}M' name='{$this->attributes['VAR']}M' $disabled> ";
        $months[''] = '';
        if ($this->config_service['lang'] == 'en') {
            $months['01'] = 'Jan';
            $months['02'] = 'Feb';
            $months['03'] = 'Mar';
            $months['04'] = 'Apr';
            $months['05'] = 'May';
            $months['06'] = 'Jun';
            $months['07'] = 'Jul';
            $months['08'] = 'Aug';
            $months['09'] = 'Sep';
            $months['10'] = 'Oct';
            $months['11'] = 'Nov';
            $months['12'] = 'Dec';
            $date_def = '(DD MM YYYY)';
        } else {
            $months['01'] = 'Gen';
            $months['02'] = 'Feb';
            $months['03'] = 'Mar';
            $months['04'] = 'Apr';
            $months['05'] = 'Mag';
            $months['06'] = 'Giu';
            $months['07'] = 'Lug';
            $months['08'] = 'Ago';
            $months['09'] = 'Set';
            $months['10'] = 'Ott';
            $months['11'] = 'Nov';
            $months['12'] = 'Dic';
            $date_def = '(GG MM AAAA)';
        }
        $months['-9911'] = 'NA';
        $months['-9922'] = 'NK';

        $option = "";

        foreach ($months as $key => $val) {
            if ($mm == $key) $selected = " selected=\"selected\" ";
            else $selected = "";
            $option .= "<option $selected value=\"$key\">$val</option>";
        }
        $select_months .= $option . "</select>";
        if ($in[$this->attributes['VAR'] . 'D'] != '' && $in[$this->attributes['VAR'] . 'M'] != '' && $in[$this->attributes['VAR'] . 'Y'] != '') {
            if ($in[$this->attributes['VAR'] . 'D'] != '') {
                $in[$this->attributes['VAR'] . 'D'] = '0' . $in[$this->attributes['VAR'] . 'D'];
                $in[$this->attributes['VAR'] . 'D'] = substr($in[$this->attributes['VAR'] . 'D'], strlen($in[$this->attributes['VAR'] . 'D']) - 2, 2);
            }
            if ($in[$this->attributes['VAR'] . 'M'] != '') {
                $in[$this->attributes['VAR'] . 'M'] = '0' . $in[$this->attributes['VAR'] . 'M'];
                $in[$this->attributes['VAR'] . 'M'] = substr($in[$this->attributes['VAR'] . 'M'], strlen($in[$this->attributes['VAR'] . 'M']) - 2, 2);
            }
            $value = $in[$this->attributes['VAR']] = $in[$this->attributes['VAR'] . 'D'] . $in[$this->attributes['VAR'] . 'M'] . $in[$this->attributes['VAR'] . 'Y'];
            $in[$this->attributes['VAR'] . 'D'] += 0;
            $in[$this->attributes['VAR'] . 'M'] += 0;
        }

        $this->validata = true;
        if (isset($in['salva']) and $this->attributes['SAVE'] == 'obbligatorio') {
            if (!checkdate($mm, $dd, $yyyy)) {
                $txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
                $this->validata = false;
            }
        }
        if (isset($in['invia']) and $this->attributes['SEND'] == 'obbligatorio' && $this->condition_passed) {
            if (!checkdate($mm, $dd, $yyyy)) {
                //echo "<hr>Campo non validato {$this->id}<hr>";
                $txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
                $this->validata = false;
            }
        }
        $check_onblur = '';
        if ($this->attributes['ONBLUR'] != '') {
            $check_fn = 'onchange="' . $this->attributes['ONBLUR'] . '"';
        }
        if ($this->attributes['CHECK_ONBLUR'] != '') {
            $check_onblur = 'onblur="el=f.elements;specifiche=\'A=ON&L=0&F=0\';c1=\'<<fd00###' . $this->attributes['VAR'] . '###Data errata>>\';rc=contr(c1,specifiche);if (rc) {return false}"';
        }
        $rc = $this->attributes['VAR'] . 'RC';
        if ($this->attributes['NDAY'] != 'yes') {
            $input_html .= '<input onblur="this.value=document.forms[0].' . $this->attributes['VAR'] . 'D.value.toUpperCase();if(this.value.length==1) this.value=\'0\'+this.value;" type="text" name="' . $this->attributes['VAR'] . 'D" value="' . $dd . '" size=2 maxlength=2 ' . $check_fn . ' ' . $disabled . '/>&nbsp;';
        } else {
//Ho messo un .= in input_html qui altrimneti non mi inseriva nell'html la hidden con la description
            $this->check_js .= "
				if (f.{$this->attributes['VAR']}M.value=='' && f.{$this->attributes['VAR']}Y.value==''){
					f.{$this->attributes['VAR']}D.value='';
				}
				else f.{$this->attributes['VAR']}D.value='15';
			";
            $input_html .= '<input type="hidden" name="' . $this->attributes['VAR'] . 'D" value="15" >';
        }
        $input_html .= $select_months . '
                     <input onblur="this.value=document.forms[0].' . $this->attributes['VAR'] . 'Y.value.toUpperCase();" type="text" name="' . $this->attributes['VAR'] . 'Y" value="' . $yyyy . '" size=4 maxlength=4 ' . $check_onblur . $check_fn . ' ' . $disabled . ' />
                     <input type="hidden" name="' . $this->attributes['VAR'] . '" value="' . $dd . $mm . $yyyy . '"/>
                     <input type="hidden" name="' . $this->attributes['VAR'] . 'RC" />';
        if ($inputval[$rc] == 'CONTIN') {
            $input_html = '<input type="text" name="' . $this->attributes['VAR'] . 'D" value="" size=2 maxlength=2 />' . $select_months . '

                     <input type="text" name="' . $this->attributes['VAR'] . 'Y" value="CONT" size=4 maxlength=4 ' . $check_onblur . ' ' . $disabled . '/>
                     <input type="hidden" name="' . $this->attributes['VAR'] . '" value=""/>
                     <input type="hidden" name="' . $this->attributes['VAR'] . 'RC" value="CONTIN"/>';
        }
        $input_html .= $add_cal;
        $this->salva_js .= "
				c1+='<<fd00###" . $this->attributes['VAR'] . "###Wrong date>>';";
        $this->invia_js .= "
				c1+='<<fd00###" . $this->attributes['VAR'] . "###Wrong date>>';";
        if ($this->attributes['DEF'] != '') $input_html .= '<br />' . $this->attributes['DEF'];
        $this->input_field = $input_html;
        $this->input_txt = $txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form > 1) $ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
        else $ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . $date_def . '</td>';
        $this->session_vars = $in;

        //var_dump($this);
    }

    /**
     * close_
     * Costruisce il codice html del campo in visualizzazione
     *
     * @param string $value
     * @return string
     */
    function close_($value)
    {
        $inputval = $this->session_vars;
        $ret = '<tr id="' . $this->attributes['VAR'] . '" style="display:">';
        $txt = $this->testo;
        //print_r($this); die();
        //		echo $value;
//		print_r($this->db_vars[$this->attributes['VAR'].'RC']);
        if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 0, 6) == 'CONTIN') {
            $dd = '';
            $mm = '';
            $yyyy = 'CONT';
        } else {
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 0, 2) != 'OK') $dd = substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 0, 2);
            else $dd = substr($value, 0, 2);
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 2, 2) != 'OK') $mm = substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 2, 2);
            else $mm = substr($value, 2, 2);
            if (substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 4, 2) != 'OK') $yyyy = substr($this->db_vars[$this->attributes['VAR'] . 'RC'], 4, 2);
            else $yyyy = substr($value, 4, 4);

            $months[''] = '';

            if ($this->config_service['lang'] == 'en') {
                $months[1] = 'Jan';
                $months[2] = 'Feb';
                $months[3] = 'Mar';
                $months[4] = 'Apr';
                $months[5] = 'May';
                $months[6] = 'Jun';
                $months[7] = 'Jul';
                $months[8] = 'Aug';
                $months[9] = 'Sep';
                $months[10] = 'Oct';
                $months[11] = 'Nov';
                $months[12] = 'Dec';
            } else {
                $months[1] = 'Gen';
                $months[2] = 'Feb';
                $months[3] = 'Mar';
                $months[4] = 'Apr';
                $months[5] = 'Mag';
                $months[6] = 'Giu';
                $months[7] = 'Lug';
                $months[8] = 'Ago';
                $months[9] = 'Set';
                $months[10] = 'Ott';
                $months[11] = 'Nov';
                $months[12] = 'Dic';
            }
            foreach ($months as $key => $val) {
                if ($mm == $key && ($mm != 'NK' || $mm != 'NA')) $mm = $val;
            }
        }
        if ($this->attributes['NDAY'] != 'yes') {
            $input_html = $dd . ' ' . $mm . ' ' . $yyyy;
            if ($this->config_service['lang'] == 'en') {
                $sstr = '(DD MMM YYYY)';
            } else {
                $sstr = '(GG MMM AAAA)';
            }
        } else {
            $input_html = $mm . ' ' . $yyyy;
            if ($this->config_service['lang'] == 'en')
                $sstr = '(MMM YYYY)';
            else
                $sstr = '(MMM AAAA)';
        }
        $rc = $this->attributes['VAR'] . 'RC';
        if ($inputval[$rc] == 'CONTIN') {
            $input_html = 'CONT';
            $sstr = ' ';
        }
//		print_r($inputval);
        if ($this->deleted == 2 && $this->attributes['MAIN'] != "yes") {
            $input_html = "<span style='text-decoration:line-through;'>$input_html</span>";
        }
        if (isset($inputval['AUDIT_TRAIL']) && $inputval['AUDIT_TRAIL'] != '') {
            $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->attributes, $this->xml_form);
            $input_html .= $audit_trail->audit_trail_popup($inputval);

        }

        $this->input_txt = $txt;
        if (isset ($_GET ['CRF_ANNOTE'])) {
            $db = $this->attributes['VAR'];
            $this->input_field = '<b><u><i><font color="#333300"><span class="textfield">' . $this->xml_form->form['TABLE'] . '.' . $input_html . $db . '&nbsp;&nbsp;</span></font></i></u></b>' . $sstr;
        } else {
            $db = "";
            $this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '&nbsp;&nbsp;</span></font></i></b>' . $sstr;
        }

        if (isset($this->attributes['COLSPAN']) and $this->cols_form > 1) $ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
        else
            $ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $sstr . '</td></tr>';
        #return $ret;
    }

    /**
     * Popola le proprietè "field_stmt" e "value_stmt" necessarie alla costruzione degli stmt di inserimento/update
     *
     */
    function insert_stmt($insert = true)
    {

        //echo "<hr>entra en la funcion";
        $in = $this->session_vars;
        $conn = $this->conn;
        if ($this->attributes['NNDAYVALUE'] == '') {
            $this->attributes['NNDAYVALUE'] = '09';
        }
        if ($this->attributes['NNMONTHVALUE'] == '') {
            $this->attributes['NNMONTHVALUE'] = '09';
        }

        if (isset($this->attributes['FORMAT'])) $format = $this->attributes['FORMAT'];
        else $format = 'DDMMYYYY';
        $sql = new query($conn);
        $sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = '{$format}'");
        $sql->ins_upd();
        if (!$insert) {
            $this->field_stmt[0] = "{$this->attributes['VAR']}";
            $this->field_stmt[1] = "{$this->attributes['VAR']}RC";
            return;
        }

        if (strlen($in[$this->attributes['VAR'] . 'D']) == 1) {
            $in[$this->attributes['VAR'] . 'D'] = "0" . $in[$this->attributes['VAR'] . 'D'];
        }

        if ($this->attributes['TB'] != 'no') {
            $this->field_stmt[0] = "{$this->attributes['VAR']}";
            $this->field_stmt[1] = "{$this->attributes['VAR']}RC";
            $this->value_stmt[0] = $in[$this->attributes['VAR']] = $in[$this->attributes['VAR'] . 'D'] . $in[$this->attributes['VAR'] . 'M'] . $in[$this->attributes['VAR'] . 'Y'];
            $this->value_stmt[1] = $in[$this->attributes['VAR'] . 'RC'] = "OKOKOK";
        }

        /**Aggiunta controllo NA e NK **/
        if ($in[$this->attributes['VAR'] . 'D'] == 'NA' || $in[$this->attributes['VAR'] . 'D'] == 'NK') {
            $this->value_stmt[0] = "{$this->attributes['NNDAYVALUE']}" . "{$in[$this->attributes['VAR'].'M']}" . "{$in[$this->attributes['VAR'].'Y']}";
            if ($in[$this->attributes['VAR'] . 'D'] == 'NA') $this->value_stmt[1] = 'NAOKOK';
            if ($in[$this->attributes['VAR'] . 'D'] == 'NK') $this->value_stmt[1] = 'NKOKOK';
        }
        if ($in[$this->attributes['VAR'] . 'M'] == '-9911' || $in[$this->attributes['VAR'] . 'M'] == '-9922') {
            $this->value_stmt[0] = "{$this->attributes['NNDAYVALUE']}" . "{$this->attributes['NNMONTHVALUE']}" . "{$in[$this->attributes['VAR'].'Y']}";
            if ($in[$this->attributes['VAR'] . 'M'] == '-9911') $this->value_stmt[1] = 'NANAOK';
            if ($in[$this->attributes['VAR'] . 'M'] == '-9922') $this->value_stmt[1] = 'NKNKOK';
        }
        if ($in[$this->attributes['VAR'] . 'Y'] == 'NA' || $in[$this->attributes['VAR'] . 'Y'] == 'NK') {
            $this->value_stmt[0] = "{$this->attributes['NNDAYVALUE']}" . "{$this->attributes['NNMONTHVALUE']}" . "9999";
            if ($in[$this->attributes['VAR'] . 'Y'] == 'NA') $this->value_stmt[1] = 'NANANA';
            if ($in[$this->attributes['VAR'] . 'Y'] == 'NK') $this->value_stmt[1] = 'NKNKNK';
        }
        if ($in[$this->attributes['VAR'] . 'D'] == '' && $in[$this->attributes['VAR'] . 'M'] == '' && $in[$this->attributes['VAR'] . 'Y'] == '') {
            $this->value_stmt[1] = '';
            $this->value_stmt[0] = '';
        }


//		echo "<hr>ESTO ES LO QUE SE INSERTA!";
//		print_r($this->value_stmt);
//		echo "<hr>";die();

        return;
    }

    /**
     * allinea_db
     * Costruisce l'array dei campi necessari da creare in DB     *
     *
     * @return array
     */
    function allinea_db()
    {

        if ($this->attributes['TB'] != 'no') {
            $ret[0] = "{$this->attributes['VAR']} DATE";
            $ret[1] = "{$this->attributes['VAR']}RC VARCHAR2(8)";
            $ret[2] = "{$this->attributes['VAR']}_D as (decode ( substr({$this->attributes['VAR']}RC,1,2), 'OK' ,to_char({$this->attributes['VAR']},'DD') ,'' ,to_char({$this->attributes['VAR']},'DD'), 'NA' , 'NA' , 'NK', 'NK'))";
            $ret[3] = "{$this->attributes['VAR']}_M as ( decode ( substr({$this->attributes['VAR']}RC,3,2), 'OK' ,to_char({$this->attributes['VAR']},'MM') , '' ,to_char({$this->attributes['VAR']},'MM'),'NA' , 'NA' , 'NK', 'NK')) ";
            $ret[4] = "{$this->attributes['VAR']}_Y as ( decode ( substr({$this->attributes['VAR']}RC,5,2), 'OK' ,to_char({$this->attributes['VAR']},'YYYY') ,'' ,to_char({$this->attributes['VAR']},'YYYY') , 'NA' , 'NA' , 'NK', 'NK'))";

            return $ret;
        } else return;
    }

    /**
     * allinea_db
     * Costruisce l'array dei campi necessari da creare in DB     storico, senza colonne virtuali
     *
     * @return array
     */
    function allinea_db_storico()
    {

        if ($this->attributes['TB'] != 'no') {
            $ret[0] = "{$this->attributes['VAR']} DATE";
            $ret[1] = "{$this->attributes['VAR']}RC VARCHAR2(8)";
            $ret[2] = "{$this->attributes['VAR']}_D VARCHAR2(2)";
            $ret[3] = "{$this->attributes['VAR']}_M VARCHAR2(2)";
            $ret[4] = "{$this->attributes['VAR']}_Y VARCHAR2(4)";

            return $ret;
        } else return;
    }


    /**
     * open_condition
     * Costruisce i controlli js e lato server per i campi condizionati
     *
     * @param string $val
     */
    function open_condition($val)
    {
        $js_condition = '';
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $var_cond = $val;
        $this->condition_passed = false;
        $val_cond = $this->attributes['CONDITION_VALUE'];
        if ($this->attributes['HIDE'] == 'yes' && $this->attributes['SHOW_HIDE'] != 'yes' && !isset($in['CRF_BLANK'])) {
            // Campi condizionati nascosti.
            if (preg_match("/,/", $val_cond)) {
                /*
				 * Con la virgola si va a settare la condition su più valori
				 */
                $values_cond = explode(",", $val_cond);
                // Ripeto la funzione per tutti i valori
                $val_cond_final = "false";
                $op_final = '!=';

                foreach ($values_cond as $key => $val_cond) {
                    $op = '!=';
                    if (preg_match("/\!/", $val_cond)) {
                        $val_cond = str_replace("!", "", $val_cond);
                        $op = '==';
                    }
                    if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                    else {
                        $value_to_control = $inputval[$var_cond];
                        if ($inputval[$var_cond] == "") {
                            $value_to_control = $in[$var_cond];
                        }
                    }
                    if ($op == '==') $this->condition_passed = ($value_to_control != $val_cond);
                    else $this->condition_passed = ($value_to_control == $val_cond);


                    if ($this->condition_passed) {
                        $op_final = $op;
                        $val_cond_final = $val_cond;
                        $js_condition = "value{$op_final}'$val_cond_final'";
                        break;
                    } else {
                        if ($js_condition == "") {
                            $js_condition = "value" . $op . "'" . $val_cond . "'";
                        } else {
                            $js_condition .= " && value" . $op . "'" . $val_cond . "'";
                        }
                    }
                }

                //Potrebbe non funzionare con date nascoste condizionate e precompilate
                $this->check_js = " \n
					value=value_of('$var_cond', '0');
					if (document.forms[0]." . $this->id . "D.value!=''){ {$this->id}D_val=document.forms[0]." . $this->id . "D.value;}
					else{{$this->id}D_val='';}
					if (document.forms[0]." . $this->id . "M.value!=''){ {$this->id}M_val=document.forms[0]." . $this->id . "M.value;}
					else{{$this->id}M_val='';}
					if (document.forms[0]." . $this->id . "Y.value!=''){ {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;}
					else{{$this->id}Y_val='';}
					//colabuf
					if ($js_condition)
					{
					  document.forms[0]." . $this->id . "D.value='';
					  document.forms[0]." . $this->id . "M.value='';
					  document.forms[0]." . $this->id . "Y.value='';
					";
                //foreach ($this->values as $key => $decode) $this->check_js.=" \n	document.forms[0].".$this->id."[".($key-1)."].checked=false;";
                $this->check_js .= " \n
					  if (document.getElementById('tr_" . $this->id . "'))
					    document.getElementById('tr_" . $this->id . "').style.display='none';
					  } else {
						if (typeof({$this->id}D_val)!= \"undefined\" && {$this->id}D_val) document.forms[0]." . $this->id . "D.value={$this->id}D_val;
						if (typeof({$this->id}M_val)!= \"undefined\" && {$this->id}M_val) document.forms[0]." . $this->id . "M.value={$this->id}M_val;
						if (typeof({$this->id}Y_val)!= \"undefined\" && {$this->id}Y_val) document.forms[0]." . $this->id . "Y.value={$this->id}Y_val;
						if (document.getElementById('tr_" . $this->id . "'))
								document.getElementById('tr_" . $this->id . "').style.display='';
						}";
            } else {
                /*
					 * Condition classica su un valore singolo.
					 */
                $op = '!=';
                if (preg_match("/\!/", $val_cond)) {
                    $val_cond = str_replace("!", "", $val_cond);
                    $op = '==';
                }
                if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                else $value_to_control = $inputval[$var_cond];
                if ($op == '==') $this->condition_passed = ($value_to_control != $val_cond);
                else $this->condition_passed = ($value_to_control == $val_cond);
                //Potrebbe non funzionare con date nascostoste condizionate e precompilate
                $this->check_js = " \n
					value=value_of('$var_cond', '0');
					if (document.forms[0]." . $this->id . "D.value!=''){ {$this->id}D_val=document.forms[0]." . $this->id . "D.value;}
					else{{$this->id}D_val='';}
					if (document.forms[0]." . $this->id . "M.value!=''){ {$this->id}M_val=document.forms[0]." . $this->id . "M.value;}
					else{{$this->id}M_val='';}
					if (document.forms[0]." . $this->id . "Y.value!=''){ {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;}
					else{{$this->id}Y_val='';}
					if (value{$op}'$val_cond')
					{
					document.forms[0]." . $this->id . "D.value='';
					document.forms[0]." . $this->id . "M.value='';
					document.forms[0]." . $this->id . "Y.value='';
					";
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
            /*
			 * Condition classica su un valore singolo non nascosta.
			 */
            $op = '!=';
            if (preg_match("/\!/", $val_cond)) {
                $val_cond = str_replace("!", "", $val_cond);
                $op = '==';
            }
            if ($op == '==') $this->condition_passed = ($in[$var_cond] != $val_cond);
            else $this->condition_passed = ($in[$var_cond] == $val_cond);

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
        $this->html = "<tr id='tr_" . $this->id . "' style=\"display:none\">" . $this->html . "</tr>";
    }

    /**
     * open_condition
     * Costruisce i controlli js e lato server per i campi condizionati
     *
     * @param string $val
     */
    function open_conditionOLD($val)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $var_cond = $val;
        $this->condition_passed = false;
        $val_cond = $this->attributes['CONDITION_VALUE'];
        if ($this->attributes['HIDE'] == 'yes' && $this->attributes['SHOW_HIDE'] != 'yes' && !isset($in['CRF_BLANK'])) {

            if (preg_match("/,/", $val_cond)) {
                $this->check_js .= "
	if (document.getElementById('" . $this->id . "'))
	document.getElementById('" . $this->id . "').style.display='none';
	";
                $vals = explode(",", $val_cond);
                foreach ($vals as $key => $value) {
                    if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                    else $value_to_control = $inputval[$var_cond];
                    if ($value_to_control == $value) {
                        $this->condition_passed = true;
                    }
                    $this->check_js .= " \n
		value=value_of('$var_cond', '0');
		if (value=='$value')
		{
		document.forms[0]." . $this->id . "D.value='';
		document.forms[0]." . $this->id . "M.value='';
		document.forms[0]." . $this->id . "Y.value='';
		if (document.getElementById('tr_" . $this->id . "'))
		document.getElementById('tr_" . $this->id . "').style.display='';
		}
		";
                }
            } else {
                $op = '!=';
                if (preg_match("/\!/", $val_cond)) {
                    $val_cond = str_replace("!", "", $val_cond);
                    $op = '==';
                }
                if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                else $value_to_control = $inputval[$var_cond];
                if ($op == '==') $this->condition_passed = ($value_to_control != $val_cond);
                else $this->condition_passed = ($value_to_control == $val_cond);
                //Potrebbe non funzionare con date nascostoste condizionate e precompilate
                $this->check_js = " \n
	value=value_of('$var_cond', '0');
	if (document.forms[0]." . $this->id . "D.value!=''){ {$this->id}D_val=document.forms[0]." . $this->id . "D.value;}
	else{{$this->id}D_val='';}
	if (document.forms[0]." . $this->id . "M.value!=''){ {$this->id}M_val=document.forms[0]." . $this->id . "M.value;}
	else{{$this->id}M_val='';}
	if (document.forms[0]." . $this->id . "Y.value!=''){ {$this->id}Y_val=document.forms[0]." . $this->id . "Y.value;}
	else{{$this->id}Y_val='';}
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
            if (preg_match("/\!/", $val_cond)) {
                $val_cond = str_replace("!", "", $val_cond);
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
            if ($op == '==') $this->condition_passed = ($in[$var_cond] != $val_cond);
            else $this->condition_passed = ($in[$var_cond] == $val_cond);

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
					if (document.forms[0]." . $this->attributes['COMPILA_CONDITION_VAR'] . ".value==" . $this->attributes['COMPILA_CONDITION_VALUE'] . "){
						compila_value=document.forms[0]." . $this->attributes['COMPILA'] . ".value;
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
    function open_max_eq($value)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        if (preg_match("/,/", $value)) {
            $values = explode(",", $value);
            foreach ($values as $key => $value) {
                if (preg_match("/\[/", $value)) {
                    $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                    $value = $inputval[$value_field];
                    foreach ($this->xml_form->fields as $key => $val) {
                        if ($value_field == $val['VAR']) {
                            $i = $key;
                        }
                    }
                    $cond_obj = new field($this->xml_form, $i);
                    $testo_var_condizione = $cond_obj->testo;
                    //		echo "$testo_var_condizione<hr>";
                    if ($in[$value_field] != '') $value = $in[$value_field];
                }
                if ($value == 'today' || $value == 'sysdate') $value = date("dmY", time());
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval[$this->attributes['VAR']];
                if ($in[$this->attributes['VAR']] != '') $data = $in[$this->attributes['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;
                $rc = $this->attributes['VAR'] . 'RC';
                $vrc = $inputval[$rc];
                if ($in[$rc] != '') $vrc = $in[$rc];
                if ($data <= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        if ($data != '')
                            $this->input_txt .= "<br><font color=red>

					La Data deve essere successiva a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes['VAR'] . "D && document.forms[0]." . $this->attributes['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes['VAR'] . "M.value!=
				 && document.forms[0]." . $this->attributes['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
                if ($value_field != '') {
                    $this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
                }
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                elseif ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;
                $testo_js = make_js($this->testo);

                //traduzione del messaggio di alert in inglese
                if ($this->config_service['lang'] == "en")
                    $alert_msg = "{$testo_js} must be after $value_txt";
                else
                    $alert_msg = "La {$testo_js} deve essere successiva $value_txt";

                $this->controlli .= "

						if (data<=value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes['VAR'] . "Y.focus();
								return false;
							}
						}
					";
            }
        } else {
            if (preg_match("/\[/", $value)) {
                $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                $value = $inputval[$value_field];
                foreach ($this->xml_form->fields as $key => $val) {
                    if ($value_field == $val['VAR']) {
                        $i = $key;
                    }
                }
                $cond_obj = new field($this->xml_form, $i);
                $testo_var_condizione = $cond_obj->testo;
                if ($in[$value_field] != '') $value = $in[$value_field];
            }
            if ($value == 'today' || $value == 'sysdate') $value = date("dmY", time());
            if (!preg_match("/NA/", $value) && !preg_match("/NK/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9911/", $value)) {
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval[$this->attributes['VAR']];
                if ($in[$this->attributes['VAR']] != '') $data = $in[$this->attributes['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                elseif ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;
                $rc = $this->attributes['VAR'] . 'RC';
                $vrc = $inputval[$rc];
                if ($in[$rc] != '') $vrc = $in[$rc];
                if ($data <= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        //if ($data!='')
                        //$this->input_txt.="<br><font color=red>

                        //$data - $value
                        //La Data deve essere successiva a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes['VAR'] . "D && document.forms[0]." . $this->attributes['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(4,4);
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
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
                }
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;
                $value_txt = make_js($value_txt);
                $testo_js = make_js($this->testo);

                //traduzione del messaggio di alert in inglese
                if ($this->config_service['lang'] == "en")
                    $alert_msg = "{$testo_js} must be after $value_txt";
                else
                    $alert_msg = "La {$testo_js} deve essere successiva $value_txt";

                $this->controlli .= "
						if (data<=value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes['VAR'] . "Y.focus();
								return false;
						}

					}
				";
            }
        }
    }

    /**
     * Controlli sul valore della data (maggiore)
     *
     * @param String $value
     */
    function open_max($value)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        if (preg_match("/,/", $value)) {
            $values = explode(",", $value);
            foreach ($values as $key => $value) {
                if (preg_match("/\[/", $value)) {
                    $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                    $value = $inputval [$value_field];
                    foreach ($this->xml_form->fields as $key => $val) {
                        if ($value_field == $val ['VAR']) {
                            $i = $key;
                        }
                    }
                    $cond_obj = new field ($this->xml_form, $i);
                    $testo_var_condizione = $cond_obj->testo;
                    if ($cond_obj->attributes['LABEL_JS'])
                        $testo_var_condizione = $cond_obj->attributes['LABEL_JS'];
                    //  echo "$testo_var_condizione<hr>";
                    if ($in [$value_field] != '')
                        $value = $in [$value_field];
                }
                if ($value == 'today' || $value == 'sysdate')
                    $value = date("dmY", time());
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval [$this->attributes ['VAR']];
                if ($in [$this->attributes ['VAR']] != '')
                    $data = $in [$this->attributes ['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;
                $rc = $this->attributes ['VAR'] . 'RC';
                $vrc = $inputval [$rc];
                if ($in [$rc] != '')
                    $vrc = $in [$rc];
                if ($data < $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        if ($data != '')
                            $this->input_txt .= "<br><font color=red>

                    La Data deve essere successiva a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
                  {
                        var data=new Date();
                        giorno=document.forms[0]." . $this->attributes ['VAR'] . "D.value;
                        mese=document.forms[0]." . $this->attributes ['VAR'] . "M.value-1;
                        anno=document.forms[0]." . $this->attributes ['VAR'] . "Y.value;
                        data.setFullYear(anno,mese,giorno);
                        data.setHours(0,0,0,0);
                        var value=new Date();
                        ";
                if ($value_field != '') {
                    $this->controlli .= "
                        vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
                        vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
                        vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
                        
                        if (vmese>=0){
                            value.setFullYear(vanno,vmese,vgiorno);
                            value.setHours(0,0,0,0);
                        }
                        else value=0;
                        ";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
                        value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
                        value.setHours(0,0,0,0);
                        ";
                }
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;

                $testo = make_js($this->testo);
                /* Nicola 20/01/2010
                 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
                 */
                if ($this->attributes['LABEL_JS'] != "") {
                    $testo = $this->attributes['LABEL_JS'];
                }

                if ($this->attributes['LABEL_JS_COND'] != "") {
                    $value_txt = $this->attributes['LABEL_JS_COND'];
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
            if (preg_match("/\[/", $value)) {
                $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                $value = $inputval [$value_field];
                foreach ($this->xml_form->fields as $key => $val) {
                    if ($value_field == $val ['VAR']) {
                        $i = $key;
                    }
                }
                $cond_obj = new field ($this->xml_form, $i);
                $testo_var_condizione = $cond_obj->testo;
                if ($cond_obj->attributes['LABEL_JS'])
                    $testo_var_condizione = $cond_obj->attributes['LABEL_JS'];
                if ($in [$value_field] != '')
                    $value = $in [$value_field];
            }
            if ($value == 'today' || $value == 'sysdate')
                $value = date("dmY", time());
            if (!preg_match("/NA/", $value) && !preg_match("/NK/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9911/", $value)) {
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval [$this->attributes ['VAR']];
                if ($in [$this->attributes ['VAR']] != '')
                    $data = $in [$this->attributes ['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;

                $rc = $this->attributes ['VAR'] . 'RC';
                $vrc = $inputval [$rc];
                if ($in [$rc] != '')
                    $vrc = $in [$rc];

                if ($data < $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        //if ($data != '')
                        //    $this->input_txt .= "<br><font color=red>

                        //$data - $value
                        //La Data deve essere successiva a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
              {
                    var data=new Date();
                    giorno=document.forms[0]." . $this->attributes ['VAR'] . "D.value;
                    mese=document.forms[0]." . $this->attributes ['VAR'] . "M.value-1;
                    anno=document.forms[0]." . $this->attributes ['VAR'] . "Y.value;
                    data.setFullYear(anno,mese,giorno);
                    data.setHours(0,0,0,0);
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
                    value.setHours(0,0,0,0);
                    ";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
                    value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
                    value.setHours(0,0,0,0);
                    ";
                }
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;

                $value_txt = make_js($value_txt);
                $testo = make_js($this->testo);
                /* Nicola 20/01/2010
             * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
             */
                if ($this->attributes['LABEL_JS'] != "") {
                    $testo = $this->attributes['LABEL_JS'];
                }

                if ($this->attributes['LABEL_JS_COND'] != "") {
                    $value_txt = $this->attributes['LABEL_JS_COND'];
                }
                $value_txt = make_js($value_txt);
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
        }
    }


    /**
     * Controlli sul valore della data (minore o uguale)
     *
     * @param String $value
     */
    function open_min_eq($value)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        if (preg_match("/,/", $value)) {
            $values = explode(",", $value);
            foreach ($values as $key => $value) {
                if (preg_match("/\[/", $value)) {
                    $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                    $value = $inputval[$value_field];
                    foreach ($this->xml_form->fields as $key => $val) {
                        if ($value_field == $val['VAR']) {
                            $i = $key;
                        }
                    }
                    $cond_obj = new field($this->xml_form, $i);
                    $testo_var_condizione = $cond_obj->testo;
                    //		echo "$testo_var_condizione<hr>";
                    if ($in[$value_field] != '') $value = $in[$value_field];
                }
                /*lato server*/
                if ($value == 'today' || $value == 'sysdate') $value = date("dmY", time());
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval[$this->attributes['VAR']];
                if ($in[$this->attributes['VAR']] != '') $data = $in[$this->attributes['VAR']];
                #echo "<hr>$data";
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;
                #echo "<hr>$value";
                $rc = $this->attributes['VAR'] . 'RC';
                $vrc = $inputval[$rc];
                if ($in[$rc] != '') $vrc = $in[$rc];
                if ($data >= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        #echo "<hr>$value";
                        if ($data != '')
                            $this->input_txt .= "<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
                    }
                }
                /*lato client*/
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes['VAR'] . "D && document.forms[0]." . $this->attributes['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes['VAR'] . "Y.value!='')
				  {
						var data=new Date();
						giorno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(0,2);
						mese=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(2,2)-1;
						anno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(4,4);
						data.setFullYear(anno,mese,giorno);
						var value=new Date();
						";
                if ($value_field != '') {
                    $this->controlli .= "
					 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
						vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
						if (vmese>0)
							value.setFullYear(vanno,vmese,vgiorno);
						else value=0;
					 	";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
                }
                $testo_js = make_js($this->testo);

                //traduzione del messaggio di alert in inglese
                if ($this->config_service['lang'] == "en")
                    $alert_msg = "{$testo_js} must be before $value_txt";
                else
                    $alert_msg = "La {$testo_js} deve essere precedente $value_txt";

                $this->controlli .= "
						//alert (data+' - '+value);
						if (data>=value && value) {
								alert('$alert_msg');
								document.forms[0]." . $this->attributes['VAR'] . "Y.focus();
								return false;
						}
						}
					";
            }
        } else {
            if (preg_match("/\[/", $value)) {
                $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                $value = $inputval[$value_field];
                foreach ($this->xml_form->fields as $key => $val) {
                    if ($value_field == $val['VAR']) {
                        $i = $key;
                    }
                }
                $cond_obj = new field($this->xml_form, $i);
                $testo_var_condizione = $cond_obj->testo;
                //		echo "$testo_var_condizione<hr>";
                if ($in[$value_field] != '') $value = $in[$value_field];
            }
            /*lato server*/
            if ($value == 'today' || $value == 'sysdate') $value = date("dmY", time());
            if (!preg_match("/NA/", $value) && !preg_match("/NK/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9911/", $value)) {
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval[$this->attributes['VAR']];
                if ($in[$this->attributes['VAR']] != '') $data = $in[$this->attributes['VAR']];
                #echo "<hr>$data";
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service['lang'] != "en") $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service['lang'] != "en") $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service['lang'] == "en") $value_txt = $testo_var_condizione;

                $rc = $this->attributes['VAR'] . 'RC';
                $vrc = $inputval[$rc];
                if ($in[$rc] != '') $vrc = $in[$rc];
                if ($data >= $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        //		if ($data>$value && $data!='') {
                        $this->validata = false;
                        #echo "<hr>$value";
                        //if ($data!='')
                        //$this->input_txt.="<br><font color=red>La Data deve essere precedente $value_txt&nbsp;";
                    }
                }
                /*lato client*/
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes['VAR'] . "D && document.forms[0]." . $this->attributes['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes['VAR'] . "Y.value!='')
			  {
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(0,2);
					mese=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(2,2)-1;
					anno=document.forms[0]." . $this->attributes['VAR'] . ".value.substr(4,4);
					data.setFullYear(anno,mese,giorno);
					var value=new Date();
					";
                if ($value_field != '') {
                    $this->controlli .= "
				 	vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
					vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
					vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
					value.setFullYear(vanno,vmese,vgiorno);
				 	";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
					value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
					";
                }
                $testo_js = make_js($this->testo);

                //traduzione del messaggio di alert in inglese
                if ($this->config_service['lang'] == "en")
                    $alert_msg = "{$testo_js} must be before $value_txt";
                else
                    $alert_msg = "La {$testo_js} deve essere precedente $value_txt";

                $this->controlli .= "
					if (data>=value) {
							alert('$alert_msg');
							document.forms[0]." . $this->attributes['VAR'] . "Y.focus();
							return false;
					}
					}
				";
            }
        }
    }


    /**
     * Controlli sul valore della data (minore)
     *
     * @param String $value
     */
    function open_min($value)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        if (preg_match("/,/", $value)) {
            $values = explode(",", $value);
            foreach ($values as $key => $value) {
                if (preg_match("/\[/", $value)) {
                    $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                    $value = $inputval [$value_field];
                    foreach ($this->xml_form->fields as $key => $val) {
                        if ($value_field == $val ['VAR']) {
                            $i = $key;
                        }
                    }
                    $cond_obj = new field ($this->xml_form, $i);
                    $testo_var_condizione = $cond_obj->testo;
                    if ($cond_obj->attributes['LABEL_JS'])
                        $testo_var_condizione = $cond_obj->attributes['LABEL_JS'];
                    //  echo "$testo_var_condizione<hr>";
                    if ($in [$value_field] != '')
                        $value = $in [$value_field];
                }
                if ($value == 'today' || $value == 'sysdate')
                    $value = date("dmY", time());
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval [$this->attributes ['VAR']];
                if ($in [$this->attributes ['VAR']] != '')
                    $data = $in [$this->attributes ['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;
                $rc = $this->attributes ['VAR'] . 'RC';
                $vrc = $inputval [$rc];
                if ($in [$rc] != '')
                    $vrc = $in [$rc];
                if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        if ($data != '')
                            $this->input_txt .= "<br><font color=red>

                    La Data deve essere precedente a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
                  {
                        var data=new Date();
                        giorno=document.forms[0]." . $this->attributes ['VAR'] . "D.value;
                        mese=document.forms[0]." . $this->attributes ['VAR'] . "M.value-1;
                        anno=document.forms[0]." . $this->attributes ['VAR'] . "Y.value;
                        data.setFullYear(anno,mese,giorno);
                        data.setHours(0,0,0,0);
                        var value=new Date();
                        ";
                if ($value_field != '') {
                    $this->controlli .= "
                        vgiorno=document.forms[0]." . $value_field . ".value.substr(0,2);
                        vmese=document.forms[0]." . $value_field . ".value.substr(2,2)-1;
                        vanno=document.forms[0]." . $value_field . ".value.substr(4,4);
                       
                        if (vmese>=0){
                            value.setFullYear(vanno,vmese,vgiorno);
                            value.setHours(0,0,0,0);
                        }
                        else value=0;
                        ";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
                        value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
                        value.setHours(0,0,0,0);
                        ";
                }
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;


                $testo = make_js($this->testo);
                /* Nicola 20/01/2010
                 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
                 */
                if ($this->attributes['LABEL_JS'] != "") {
                    $testo = $this->attributes['LABEL_JS'];
                }

                if ($this->attributes['LABEL_JS_COND'] != "") {
                    $value_txt = $this->attributes['LABEL_JS_COND'];
                }
                $value_txt = make_js($value_txt);
                //traduzione del messaggio di alert in inglese
                if ($this->config_service ['lang'] == "en")
                    $alert_msg = "{$testo} must be before $value_txt";
                else
                    $alert_msg = "La {$testo} deve essere precedente $value_txt";

                $this->controlli .= "

                        if (data>value && value) {
                                alert('$alert_msg');
                                document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
                                return false;
                            }
                        }
                    ";
            }
        } else {
            if (preg_match("/\[/", $value)) {
                $value_field = preg_replace("/\[(.*?)\]/", "$1", $value);
                $value = $inputval [$value_field];
                foreach ($this->xml_form->fields as $key => $val) {
                    if ($value_field == $val ['VAR']) {
                        $i = $key;
                    }
                }
                $cond_obj = new field ($this->xml_form, $i);
                $testo_var_condizione = $cond_obj->testo;
                if ($cond_obj->attributes['LABEL_JS'])
                    $testo_var_condizione = $cond_obj->attributes['LABEL_JS'];
                if ($in [$value_field] != '')
                    $value = $in [$value_field];
            }
            if ($value == 'today' || $value == 'sysdate')
                $value = date("dmY", time());
            if (!preg_match("/NA/", $value) && !preg_match("/NK/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9922/", $value) && !preg_match("/-9911/", $value)) {
                $value = str_replace("/", "", $value);
                $value = substr($value, 4, 4) . substr($value, 2, 2) . substr($value, 0, 2);
                $data = $inputval [$this->attributes ['VAR']];
                if ($in [$this->attributes ['VAR']] != '')
                    $data = $in [$this->attributes ['VAR']];
                $data = substr($data, 4, 4) . substr($data, 2, 2) . substr($data, 0, 2);
                $value_txt = substr($value, 6, 2) . "/" . substr($value, 4, 2) . "/" . substr($value, 0, 4);
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;

                $rc = $this->attributes ['VAR'] . 'RC';
                $vrc = $inputval [$rc];
                if ($in [$rc] != '')
                    $vrc = $in [$rc];
                if ($data > $value && $data != '' && $value != '' && ($vrc == 'OKOKOK' || $vrc == '')) {
                    if (substr($in[$this->attributes['VAR']], 0, 2) != 'NA' && substr($in[$this->attributes['VAR']], 0, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 2, 2) != 'NA' && substr($in[$this->attributes['VAR']], 2, 2) != 'NK'
                        && substr($in[$this->attributes['VAR']], 4, 2) != 'NA' && substr($in[$this->attributes['VAR']], 4, 2) != 'NK') {
                        $this->validata = false;
                        //if ($data != '')
                        //    $this->input_txt .= "<br><font color=red>

                        //$data - $value
                        //La Data deve essere precedente a $value_txt&nbsp;";
                    }
                }
                $giorno = substr($data, 6, 2) + 0;
                $mese = substr($data, 4, 2) - 1;
                $anno = substr($data, 0, 4) + 0;
                $this->controlli .= " if (document.forms[0]." . $this->attributes ['VAR'] . "D && document.forms[0]." . $this->attributes ['VAR'] . "D.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "M.value!='' && document.forms[0]." . $this->attributes ['VAR'] . "Y.value!='')
              {
                    var data=new Date();
                    giorno=document.forms[0]." . $this->attributes ['VAR'] . "D.value;
                    mese=document.forms[0]." . $this->attributes ['VAR'] . "M.value-1;
                    anno=document.forms[0]." . $this->attributes ['VAR'] . "Y.value;
                    data.setFullYear(anno,mese,giorno);
                    data.setHours(0,0,0,0);
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
                    value.setHours(0,0,0,0);
                    ";

                } else {
                    $vgiorno = substr($value, 6, 2) + 0;
                    $vmese = substr($value, 4, 2) - 1;
                    $vanno = substr($value, 0, 4) + 0;

                    $this->controlli .= "
                    value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
                    value.setHours(0,0,0,0);
                    ";
                }
                if ($testo_var_condizione != '' && $this->config_service ['lang'] != "en")
                    $value_txt = "alla " . $testo_var_condizione;
                else if ($this->config_service ['lang'] != "en")
                    $value_txt = "al " . $value_txt;
                if ($testo_var_condizione != '' && $this->config_service ['lang'] == "en")
                    $value_txt = $testo_var_condizione;

                $value_txt = make_js($value_txt);
                $testo = make_js($this->testo);
                /* Nicola 20/01/2010
             * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
             */
                if ($this->attributes['LABEL_JS'] != "") {
                    $testo = $this->attributes['LABEL_JS'];
                }

                if ($this->attributes['LABEL_JS_COND'] != "") {
                    $value_txt = $this->attributes['LABEL_JS_COND'];
                }
                //traduzione del messaggio di alert in inglese
                if ($this->config_service ['lang'] == "en")
                    $alert_msg = "{$testo} must be before $value_txt";
                else
                    $alert_msg = "La {$testo} deve essere precedente $value_txt";

                $this->controlli .= "
                        if (data>value && value) {
                            
                                alert('$alert_msg');
                                document.forms[0]." . $this->attributes ['VAR'] . "Y.focus();
                                return false;
                        }

                    }
                ";
            }
        }
    }


    /**
     * open_save
     * Costruisce i controlli javascript e lato server per il salvataggio della scheda
     *
     * @param string $val
     */
    function open_save($val)
    {
        $testo_js = null;
        //      echo "<hr>{$this->testo}";
        $testo = make_js($this->testo);

        /* Nicola 20/01/2010
         * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
         */
        if ($this->attributes['LABEL_JS'] != "") {
            $testo = $this->attributes['LABEL_JS'];
        }
        if ($this->config_service['lang'] == "en") {
            $alert_msg_obbl = "Mandatory field: $testo $testo_js";
        } else {
            $alert_msg_obbl = "Campo obbligatorio: $testo $testo_js";
        }
        if ($this->attributes['SAVE'] == 'obbligatorio') {
            $obblig_contr = "
                    if(f.{$this->attributes['VAR']}D.value=='' && f.{$this->attributes['VAR']}M.value=='' && f.{$this->attributes['VAR']}Y.value=='')
                        {
                            alert('" . $alert_msg_obbl . "');
                            this.focus();
                            return false;
                        }
                ";
        }
        $dcod = '00';
        if ($this->attributes['DCONT'] == 'yes') $dcod = '16';
        if ($this->attributes['DSPEC'] == 'yes') $dcod = '03';
        if ($this->attributes['DCONT'] == 'yes' && $this->attributes['DSPEC'] == 'yes') $dcod = '31';
        if (!isset($this->attributes['CONDITION'])) {
            //la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
            $this->salva_js = "";
            if ($this->attributes['NDAY'] == 'yes') {
                $this->salva_js .= "
             if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
             document.forms[0].{$this->attributes['VAR']}D.value='';
             else
             document.forms[0].{$this->attributes['VAR']}D.value='15';
             
             ";
            }

            $this->salva_js .= "
                    var f = document.forms[0];
                    var el = f.elements;
                
                    d=f.{$this->attributes['VAR']}D.value;
                    if(d<10 && d>0 && d.length<2){
                        d='0'+d;
                        f.{$this->attributes['VAR']}D.value=d;
                    }
                    if(CheckDate(f.{$this->attributes['VAR']}D.value,f.{$this->attributes['VAR']}M.value,f.{$this->attributes['VAR']}Y.value , '{$testo}') == false){
                       return false;
                    }
                    
                    $obblig_contr
                    f.{$this->attributes['VAR']}.value=f.{$this->attributes['VAR']}D.value+''+f.{$this->attributes['VAR']}M.value+''+f.{$this->attributes['VAR']}Y.value;

                ";

        } else {
            $oper = "==";
            if (preg_match("/!/", $this->attributes['CONDITION_VALUE'])) {
                $oper = "!=";
                $this->attributes['CONDITION_VALUE'] = substr($this->attributes['CONDITION_VALUE'], 1);
            }

            $val_cond = $this->attributes['CONDITION_VALUE'];
            //echo "$val_cond<br>";
            $vals = explode(",", $val_cond);
            $loc_js = "if (";
            for ($i = 0; $i < count($vals); $i++) {
                if ($i != 0) $loc_js .= "||";
                $loc_js .= "
              value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
            }
            $loc_js .= ")";
            // echo "$loc_js<br>";
            //la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
            $this->salva_js = "";
            if ($this->attributes['NDAY'] == 'yes') {
                $this->salva_js .= "
             if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
             {
             document.forms[0].{$this->attributes['VAR']}D.value='';
             
             }
             else{
             document.forms[0].{$this->attributes['VAR']}D.value='15';
            
             }
             
             ";
            }

            $this->salva_js .= "
            $loc_js
                    {
                        var f = document.forms[0];
                        var el = f.elements;
                        d=f.{$this->attributes['VAR']}D.value;
                        if(d<10 && d>0 && d.length<2){
                            d='0'+d;
                            f.{$this->attributes['VAR']}D.value=d;
                        }
                        if(CheckDate(f.{$this->attributes['VAR']}D.value,f.{$this->attributes['VAR']}M.value,f.{$this->attributes['VAR']}Y.value , '{$testo}') == false){
                            return false;
                        }
                        $obblig_contr
                        f.{$this->attributes['VAR']}.value=f.{$this->attributes['VAR']}D.value+''+f.{$this->attributes['VAR']}M.value+''+f.{$this->attributes['VAR']}Y.value;
                    }
                    else {
                      c1+='<<fd" . $dcod . "###" . $this->attributes['VAR'] . "###" . $testo . ">>';
                      c1+='<<b###" . $this->attributes['VAR'] . "Y###" . $testo . ">>';
                    }

                ";


        }

        $in = $this->session_vars;
        $insert_errors = $this->errors;

        if (($in['salva'] != '' || $in['INVIOCO'] != '1') && $this->attributes['SAVE'] != 'facoltativo') {
            if ($this->condition_passed) {
                if ($in[$this->attributes['VAR']] == '') {
                    $this->validata = false;
                    $testo = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo e' obbligatorio";
                }
            } else {
                if ($in[$this->attributes['VAR']] != '') {
                    $this->validata = false;
                    $testo = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo deve essere vuoto";
                }
            }
        }


    }


    /**
     * open_send
     * Costruisce i controlli javascript e lato server per l'invio della scheda
     *
     * @param string $val
     * @return bool
     */

    function open_send($val)
    {
        $testo_js = null;
        //      echo "<hr>{$this->testo}";
        $testo = make_js($this->testo);

        /* Nicola 20/01/2010
         * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
         */
        if ($this->attributes['LABEL_JS'] != "") {
            $testo = $this->attributes['LABEL_JS'];
        }
        if ($this->config_service['lang'] == "en") {
            $alert_msg_obbl = "Mandatory field: $testo $testo_js";
        } else {
            $alert_msg_obbl = "Campo obbligatorio: $testo $testo_js";
        }
        if ($this->attributes['SEND'] == 'obbligatorio') {
            $obblig_contr = "
                    if(f.{$this->attributes['VAR']}D.value=='' && f.{$this->attributes['VAR']}M.value=='' && f.{$this->attributes['VAR']}Y.value=='')
                        {
                            alert('" . $alert_msg_obbl . "');
                            this.focus();
                            return false;
                        }
                ";
        }
        $dcod = '00';
        if ($this->attributes['DCONT'] == 'yes') $dcod = '16';
        if ($this->attributes['DSPEC'] == 'yes') $dcod = '03';
        if ($this->attributes['DCONT'] == 'yes' && $this->attributes['DSPEC'] == 'yes') $dcod = '31';
        if (!isset($this->attributes['CONDITION'])) {
            //la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
            $this->invia_js = "";
            if ($this->attributes['NDAY'] == 'yes') {
                $this->invia_js .= "
             if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
             document.forms[0].{$this->attributes['VAR']}D.value='';
             else
             document.forms[0].{$this->attributes['VAR']}D.value='15';
             
             ";
            }

            $this->invia_js .= "
           
                    var f = document.forms[0];
                    var el = f.elements;
                
                    d=f.{$this->attributes['VAR']}D.value;
                    if(d<10 && d>0 && d.length<2){
                        d='0'+d;
                        f.{$this->attributes['VAR']}D.value=d;
                    }
                    if(CheckDate(f.{$this->attributes['VAR']}D.value,f.{$this->attributes['VAR']}M.value,f.{$this->attributes['VAR']}Y.value , '{$testo}') == false){
                       return false;
                    }
                    
                    $obblig_contr
                    f.{$this->attributes['VAR']}.value=f.{$this->attributes['VAR']}D.value+''+f.{$this->attributes['VAR']}M.value+''+f.{$this->attributes['VAR']}Y.value;

                ";

        } else {
            $oper = "==";
            if (preg_match("/!/", $this->attributes['CONDITION_VALUE'])) {
                $oper = "!=";
                $this->attributes['CONDITION_VALUE'] = substr($this->attributes['CONDITION_VALUE'], 1);
            }

            $val_cond = $this->attributes['CONDITION_VALUE'];
            //echo "$val_cond<br>";
            $vals = explode(",", $val_cond);
            $loc_js = "if (";
            for ($i = 0; $i < count($vals); $i++) {
                if ($i != 0) $loc_js .= "||";
                $loc_js .= "
              value_of('{$this->attributes['CONDITION']}')$oper'{$vals[$i]}'";
            }
            $loc_js .= ")";
            // echo "$loc_js<br>";
            //la seguente linea è inserita solo per mantenere un comportamento il più simile possibile al precedente, la correttezza di tale comportamento sarebbe da valutare
            $this->invia_js = "";
            if ($this->attributes['NDAY'] == 'yes') {
                $this->invia_js .= "
             if(document.forms[0].{$this->attributes['VAR']}M.value=='' && document.forms[0].{$this->attributes['VAR']}Y.value=='')
             {
             document.forms[0].{$this->attributes['VAR']}D.value='';
             
             }
             else{
             document.forms[0].{$this->attributes['VAR']}D.value='15';
            
             }
             
             ";
            }

            $this->invia_js .= "
            $loc_js
                    {
                        var f = document.forms[0];
                        var el = f.elements;
                        d=f.{$this->attributes['VAR']}D.value;
                        if(d<10 && d>0 && d.length<2){
                            d='0'+d;
                            f.{$this->attributes['VAR']}D.value=d;
                        }
                        if(CheckDate(f.{$this->attributes['VAR']}D.value,f.{$this->attributes['VAR']}M.value,f.{$this->attributes['VAR']}Y.value , '{$testo}') == false){
                            return false;
                        }
                        $obblig_contr
                        f.{$this->attributes['VAR']}.value=f.{$this->attributes['VAR']}D.value+''+f.{$this->attributes['VAR']}M.value+''+f.{$this->attributes['VAR']}Y.value;
                    }
                    else {
                      c1+='<<fd" . $dcod . "###" . $this->attributes['VAR'] . "###" . $testo . ">>';
                      c1+='<<b###" . $this->attributes['VAR'] . "Y###" . $testo . ">>';
                    }

                ";


        }

        $in = $this->session_vars;
        $insert_errors = $this->errors;

        if (($in['invia'] != '' || $in['INVIOCO'] == '1') && $this->attributes['SEND'] != 'facoltativo') {
            if ($this->condition_passed) {
                if ($in[$this->attributes['VAR']] == '') {
                    $this->validata = false;
                    $testo = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo e' obbligatorio";
                }
            } else {
                if ($in[$this->attributes['VAR']] != '') {
                    $this->validata = false;
                    $testo = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo deve essere vuoto";
                }
            }
        }


    }


    /**
     * Gestione della disabilitazione del campo
     *
     * @param String $value
     */
    function open_disabled($value)
    {
        $this->check_js .= "
				if(document.forms[0]." . $this->id . "D && document.forms[0]." . $this->id . "D.value!='')
					document.forms[0]." . $this->id . "D.disabled=true;
			";
        $this->check_js .= "
				if(document.forms[0]." . $this->id . "M && document.forms[0]." . $this->id . "M.value!='')
					document.forms[0]." . $this->id . "M.disabled=true;
			";
        $this->check_js .= "
				if(document.forms[0]." . $this->id . "Y && document.forms[0]." . $this->id . "Y.value!='')
					document.forms[0]." . $this->id . "Y.disabled=true;
			";
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
    function all_in($var, $i, $row, $this_closed)
    {
        $disabled = null;
        $c1_agg = null;
        $eQ = null;
        $add_cal = '
		<script>
		 var ' . $var . '_PROGR_' . $i . '_cal=new CalendarPopup(\'' . $var . '_PROGR_' . $i . '_cal_div\');
		 ' . $var . '_PROGR_' . $i . '_cal.showNavigationDropdowns();
		 ' . $var . '_PROGR_' . $i . '_cal.setReturnFunction("setMultipleValues_' . $var . '_PROGR_' . $i . '");
		 function setMultipleValues_' . $var . '_PROGR_' . $i . ' (y,m,d) {
		     document.forms[0].' . $var . '_PROGR_' . $i . 'Y.value=y;
 		     document.forms[0].' . $var . '_PROGR_' . $i . 'M.value=m;
		     document.forms[0].' . $var . '_PROGR_' . $i . 'D.value=d;
    	 }
    	 document.write(\'<a href="#" name="' . $this->attributes['VAR'] . '_cal_anchor" id="' . $var . '_PROGR_' . $i . '_cal_anchor" onclick="' . $var . '_PROGR_' . $i . '_cal.showCalendar(\\\'' . $var . '_PROGR_' . $i . '_cal_anchor\\\');return false;" >&nbsp;<img width="25"  height="25" src="/images/calendar_icon.gif"></a><span id="' . $var . '_PROGR_' . $i . '_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
		 </script>

		 ';


        $select_months = "<select id='{$var}_PROGR_{$i}M' name='{$var}_PROGR_{$i}M' $disabled> ";
        $months[''] = '';

        if ($this->config_service['lang'] == 'en') {
            $months[1] = 'jan';
            $months[2] = 'Feb';
            $months[3] = 'mar';
            $months[4] = 'apr';
            $months[5] = 'may';
            $months[6] = 'jun';
            $months[7] = 'jul';
            $months[8] = 'aug';
            $months[9] = 'sep';
            $months[10] = 'oct';
            $months[11] = 'nov';
            $months[12] = 'dec';
            $date_def = '(DD MM YYYY)';
        } else {
            $months[1] = 'gen';
            $months[2] = 'Feb';
            $months[3] = 'mar';
            $months[4] = 'apr';
            $months[5] = 'mag';
            $months[6] = 'giu';
            $months[7] = 'lug';
            $months[8] = 'ago';
            $months[9] = 'set';
            $months[10] = 'ott';
            $months[11] = 'nov';
            $months[12] = 'dic';
            $date_def = '(GG MM AAAA)';
        }
        $option = "";
        if ($row[$var] != '') {
            if (preg_match("/\//", $row [$var])) {
                $date[0] = substr($row[$var], 0, 2);
                $date[1] = substr($row[$var], 3, 2);
                $date[2] = substr($row[$var], 6, 4);
            } else {
                $date[0] = substr($row[$var], 0, 2);
                $date[1] = substr($row[$var], 2, 2);
                $date[2] = substr($row[$var], 4, 4);
            }
        } else {
            $date = '';
        }

        foreach ($months as $key => $val) {
            if ($date[1] == $key) {
                $selected = " selected=\"selected\" ";
            } else $selected = "";
            $option .= "<option $selected value=\"$key\">$val</option>";
        }
        $select_months .= $option . "</select>";

        if ($this_closed) {
            if ($this->config_service['eQuery'] == '1' && (isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM']))) {
                $eQ_content = "<input type='text' name='{$var}_PROGR_{$i}D' size=\"2\" value=\"{$date[0]}\" >/
								$select_months/
								<input type='text' name='{$var}_PROGR_{$i}Y' size=\"4\" value=\"{$date[2]}\" >
								<input type=\"hidden\" name=\"{$var}_PROGR_{$i}\" value=\"\"/>
					            <input type=\"hidden\" name=\"{$var}_PROGR_{$i}RC\" />$add_cal ";

                $c1_agg .= "c1+='<<fd00###{$var}_PROGR_{$i}###>>'";

                $eQ = $this->eQ_all_in($var, $i, $row, $this_closed);
            }
            if (isset($this->session_vars['AUDIT_TRAIL']) && $this->session_vars['AUDIT_TRAIL'] != '' && $i != "") {
                $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->attributes, $this->xml_form);
                $at = $audit_trail->audit_trail_popup($this->session_vars, $i);
            } elseif (isset($_GET['CRF_ANNOTE'])) {
                $db = $this->attributes['VAR'];
                $table = $this->xml_form->form['TABLE'];
                $annote = "<b><br><u>$table.$db</u></b>";
            }
            $ret['body'] = "
			<td class=sc4bis id=" . $var . '_PROGR_' . $i . " >&nbsp;
			<span id='view_field_{$var}_PROGR_{$i}'>{$row[$var]} </span>  $at $annote
			<span id='mod_field_{$var}_PROGR_{$i}' style=\"display:none\">$eQ_content</span> $eQ
			</td>
			";
            return $ret;
        } else {


            $ret['body'] = "
				<td class=sc4bis>
				<input type='text' name='{$var}_PROGR_{$i}D' size=\"2\" value=\"{$date[0]}\" >/
				$select_months/
				<input type='text' name='{$var}_PROGR_{$i}Y' size=\"4\" value=\"{$date[2]}\" >
				<input type=\"hidden\" name=\"{$var}_PROGR_{$i}\" value=\"\"/>
	            <input type=\"hidden\" name=\"{$var}_PROGR_{$i}RC\" />$add_cal $eQ
				</td>";
            $c1_agg .= "
				c1+='<<fd00###{$var}_PROGR_{$i}###>>';
			";
            $ret['c1_agg'] = $c1_agg;
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
    static function S_all_in($field, $m_p, $xml_form)
    {
        $field_tot = null;
        $tr_agg = null;
        $select_field = "to_char($field,'DD/MM/YYYY') as $field,";
        if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
            $onclick_action = "";
            for ($i = 1; $i <= $m_p; $i++) {
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
					<input type='text' name='{$field}_TOT_Y' size=\"4\"><br>(gg/mm/aaaa)
					<input type='button' value='applica a tutti' onclick=\"
					$onclick_action
					\">
				";
            $tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
        }
        return $tr_agg;
    }

    // Ridefinisco il BYTB per il date_hyper
    // M. Verrocchio Aprile 2011

    function fields_value_bytb($value)
    {
        echo $value;
        die();
        if ($this->xml_form->no_field_value_by_tb) {
            // Se specifico la non valorizzazione dei bytb esco
            return;
        }
        global $in;
        global $inputval;
        global $init_service;
        if ($init_service) return;
        //		print_r($inputval);
        if ($this->xml_form->closed && $this->xml_form->form['NO_LOAD_BYTB'] == "yes") {
            $this->values[$inputval[$this->attributes['VAR']]] = $inputval['D_' . $this->attributes['VAR']];

            return;
        }

        $code = $this->attributes['BYTBCODE'];
        $decode = $this->attributes['BYTBDECODE'];
        $where = $this->attributes['BYTBWHERE'];
        $order_by = $this->attributes['BYTBORDERBY'];
        $where = str_replace("min_of", "<", $where);
        $where = str_replace("max_of", ">", $where);
        if (!preg_match("/ana_utenti/i", $value)) {
            $value = $GLOBALS['service'] . "_" . $value;
        }
        $decode = str_replace("#BR#", "<br>", $decode);
        $decode = str_replace("#i#", "<i>", $decode);
        $decode = str_replace("#/i#", "</i>", $decode);
        //ridondanza richiesta a causa di problematiche riscontrate in ADCARE. Giorgio Delsignore 15/12/2007 (A - Allineamento)
        $where = preg_replace("/\[VISITNUM_PROGR\]/e", $in['VISITNUM_PROGR'], $where);
        $where = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $where);
        $decode = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $decode);
        $code = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $code);
        $order_by = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $order_by);
        //echo "<hr>{$inputval['PROV_CP']} - {$in['PROV_CP']} - {$_GLOBALS['PROV_CP']}<hr>$where";
        global $conn;
        if ($where != '') $where = "where $where";
        $query = "select $code as code";
        if ($decode != '') $query .= ", $decode as decode";
        if ($order_by != '') $query .= " from $value $where order by $order_by";
        else $query .= " from $value $where order by decode asc";

//		echo $query; 		print_r($value);echo "-";die();
        $sql = new query($conn);
        $sql->set_sql($query);
        //if($this->attributes['VAR']=='PROVINCIA_NSC')	echo "<li>$query</li>";
        //$querys_[count($query_)]=
        $sql->exec();
        global $in;
//		echo $query;
        while ($sql->get_row()) {
            if ($decode != '') {
                $this->values[$sql->row['CODE']] = $sql->row['DECODE'];
                if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE'] == 'hidden') {
                    $in[$this->attributes['VAR']] = $sql->row['DECODE'];
                }
            } else {
                global ${$this->attributes['BYVAR']};
                $this->values[$sql->row['CODE']] = ${$this->attributes['BYVAR']}[$sql->row['CODE']];
            }
            $this->db_vars[$this->attributes['VAR']] = $sql->row['CODE'];
        }
    }

}


?>