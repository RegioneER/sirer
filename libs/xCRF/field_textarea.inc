<?

include_once "field.inc";

/**
 * Classe per la gestione del campo di tipo textarea
 *
 * @package Fields
 */
class field_textarea extends field
{

    /**
     * Costruisce il codice html del campo in compilazione
     *
     * @param String $value
     */
    function open_($value, $mock = false)
    {
        $input_html = null;
        if ($mock) {
            $this->input_field = '"';
            $this->input_field .= "<textarea class=\'rf-size-<%= rf.get(Formbuilder.options.mappings.SIZE) %>\'></textarea>";
            $this->input_field .= '"';
        } else {
            $ret = '<tr id="' . $this->attributes['VAR'] . '" style="display:">';
            $txt = $this->testo;
            foreach ($this->xml_form->fields as $key => $val) {
                //echo "<li>{$this->attributes['VAR']} - {$val['CONDITION']}</li>";
                if ($this->attributes['VAR'] == $val['CONDITION']) $onblur = "onblur=\"cf();\"";
            }
            //bycode/decode valorizzazione fatta male! prende solo ultimo valore
            if ($value == "") {
                foreach ($this->values as $key => $val) {
                    $value = $this->values[$key];
                }
            }

            $events = '';
            if (strtolower($this->attributes['VAR_SIZE'] != "clob"))
                $events = 'onKeypress="if (event.keyCode==13) this.value+=\'\n\'"
			onKeyDown="textCounter(this,\'progressbar_' . $this->id . '\',' . $this->attributes['VAR_SIZE'] . ')"
			onKeyUp="textCounter(this,\'progressbar_' . $this->id . '\',' . $this->attributes['VAR_SIZE'] . ')"
			onFocus="textCounter(this,\'progressbar_' . $this->id . '\',' . $this->attributes['VAR_SIZE'] . ')"
			onChange="textCounter(this,\'progressbar_' . $this->id . '\',' . $this->attributes['VAR_SIZE'] . ')"';

            $this->input_field = '
			<style type="text/css">
				.progress{
					width: 1px;
					height: 14px;
					color: white;
					font-size: 12px;
				  	overflow: hidden;
					background-color: navy;
					padding-left: 5px;
				}
			</style>';

            $this->input_field .= '<textarea ' . $onblur . ' id=\'maxchar' . $this->id . '\' name="' . $this->attributes['VAR'] . '"
			cols="' . $this->attributes['TCOLS'] . '" rows="' . $this->attributes['ROWS'] . '"
			' . $events . '
			>' . $value . '</textarea>';

            //only se non CLOB
            if (strtolower($this->attributes['VAR_SIZE']) != 'clob')
                $this->input_field .= '<div id="progressbar_' . $this->id . '" class="progress"></div>
			<script>textCounter(document.getElementById("maxchar' . $this->id . '"),"progressbar_' . $this->id . '",' . $this->attributes['VAR_SIZE'] . ')</script>
			';
            $this->input_txt = $txt;
            $this->input_field .= $this->attributes ['DEF'];
            if (isset($this->attributes['COLSPAN']) and $this->cols_form > 1) $ret .= '<td colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
            else $ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '</td></tr>';
        }
        #return $ret;
    }

    /**
     * Costruisce il codice html del campo in visualizzazione
     *
     * @param String $value
     */
    function close_($value)
    {
        $ret = '<tr id="' . $this->attributes['VAR'] . '" style="display:">';
        $txt = $this->testo;
        $input_html = '<span class="textfield">' . $value . '</span>';
        $this->input_txt = $txt;
        $this->input_field = "&nbsp;" . $input_html;
        $this->input_field .= $this->attributes ['DEF'];
        if (isset($this->attributes['COLSPAN'])) $ret .= '<td  class="input_txt" colspan="' . $this->attributes['COLSPAN'] . '">' . $txt . ':' . $input_html . '</td>';
        else $ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '</td></tr>';
        #return $ret;
    }

    function allinea_db()
    {
        if ($this->attributes['TB'] != 'no') {
            if (strtolower($this->attributes['VAR_TYPE']) == 'clob') $type_field = "CLOB";
            else $type_field = "VARCHAR2({$this->attributes['VAR_SIZE']})";
            $ret[0] = "{$this->attributes['VAR']} {$type_field}";
            return $ret;
        } else return;
    }

    /**
     * Visualizzazione nella modalitè  progressiva
     *
     * @param String $var
     * @param number $i
     * @param array $row
     * @param boolean $this_closed
     * @return String
     */
    function all_in($var, $i, $row, $this_closed)
    {
        $last_call_sfoglia = null;
        $counter = null;
        $body = null;
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
        //dalt extbox ho levato if sfoglia
        $agg = '';
        if (isset ($val ['DISABLED_ALWAYS'])) {
            $body .= "
				<td class=sc4bis>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
        } else {
            if (isset ($val ['DISABLED']) && $row[$val['VAR']] != '') {
                $body .= "
				<td class=sc4bis>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
            } else {
                $style = '
				<style type="text/css">
					.progress{
						width: 1px;
						height: 14px;
						color: white;
						font-size: 12px;
					  	overflow: hidden;
						background-color: navy;
						padding-left: 5px;
					}
				</style>';

                $counter .= '<div id="progressbar_' . $this->id . '" class="progress"></div>
				<script>textCounter(document.getElementById("maxchar' . $this->id . '"),"progressbar_' . $this->id . '",' . $this->attributes['VAR_SIZE'] . ')</script>
				';

                $body .= "
				<td class=sc4bis>$style
				<textarea name='{$var}_PROGR_{$i}' cols=\"60\" rows=\"15\" id='maxchar{$this->id}'
				onKeypress=\"if (event.keyCode==13) this.value+='\\n'\"
				onKeyDown=\"textCounter(this,'progressbar_" . $this->id . "','4000')\"
				onKeyUp=\"textCounter(this,'progressbar_" . $this->id . "','4000')\"
				onFocus=\"textCounter(this,'progressbar_" . $this->id . "','4000')\"
				onChange=\"textCounter(this,'progressbar_" . $this->id . "','4000')\"
				>{$row[$val['VAR']]}</textarea>
				$counter
				</td>
				";

            }
        }
        $ret['last_call_sfoglia'] = $last_call_sfoglia;
        $ret['body'] = $body;
        return $ret;
    }

    /**
     * Visualizzazione nella modalità progressiva (header)
     *
     *
     * @param field_textarea $field
     * @param nubmer $m_p
     * @param form $xml_form
     * @return String
     */
    static function S_all_in($field, $m_p, $xml_form)
    {
        $field_tot = null;
        $tr_agg = null;
//		return "<td class=int>&nbsp;</td>";
        $select_field = $field . ",";
        if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
            $onclick_action = "";
            for ($i = 1; $i <= $m_p; $i++) {
                $onclick_action .= "document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_TOT.value;
			";
            }
//		$field_tot .= "
//			<textarea name='{$field}_TOT' cols=\"30\" rows=\"8\">{$row[$val['VAR']]}</textarea>
//			<input type='button' value='applica a tutti' onclick=\"
//			$onclick_action
//			\">
//		";
            $tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
        }

        return $tr_agg;
    }

    function builder_js()
    {

        $field_description['field'] = "textarea";
        $field_description['order'] = 5;
        $this->open_('', true);
        $field_description['view'] = "\"<div class=\'form-group\' style=\'height:50px\'><div><label class=\'col-sm-5 control-label no-padding-right\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></label><div class='col-sm-7'>\"+
		" . $this->input_field . "+" .
            "\"&nbsp;</div><div class=\'col-sm-5\'></div><div class=\'col-sm-5\'><%= rf.get(Formbuilder.options.mappings.DEF) %></div></div></div>\"";

        //$field_description['view']="\"<textarea class=\'rf-size-<%= rf.get(Formbuilder.options.mappings.SIZE) %>\'></textarea>\"";
        $field_description['edit'][] = 'edit/db_info';
        $field_description['edit'][] = 'edit/allowed_values';
        $field_description['edit'][] = 'edit/bytb';
        $field_description['edit'][] = 'edit/main_sub';
        $field_description['edit'][] = 'edit/condition';
        $field_description['edit'][] = 'edit/javascript';
        $field_description['edit'][] = 'edit/formatting';
        $field_description['edit'][] = 'edit/save_send';
        $field_description['addButton']['class'] = 'fa';
        $field_description['addButton']['icon'] = '<b>&#182;</b>';
        $field_description['addButton']['label'] = 'Text Area';


        return $field_description;
    }
}