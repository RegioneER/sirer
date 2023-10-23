<?

/**
 * Classe xml_vlist_prototype
 * Classe per la gestione delle liste verticali
 *
 * @package CORE
 *
 */
class xml_vlist_prototype
{

    var $titolo;
    var $blocco;
    var $links;
    var $html;
    var $page;

    /**
     * Costruttore
     *
     * @param string $xml_file
     * @return xml_vlist_prototype
     */
    function xml_vlist_prototype($xml_file)
    {
        $xml_parser = new my_xml_parser($xml_file);
        $newtag = true;
        $bl = 0;
        $this_node = new xml_node();
        for ($i = 0; $i < count($xml_parser->vals); $i++) {
            $this_node->xml_node_by_array($xml_parser->vals[$i]);
            if ($this_node->type != 'cdata') {
                if ($this_node->tag == 'vlist') if ($this_node->type == 'open' or $this_node->type == 'complete') {
                    $this->page = $this_node->attributes;

                }
                if ($this_node->tag == 'ROW') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->blocco[$bl] = $this_node->attributes;
                        $this->blocco[$bl]['TESTO'] = $this_node->value;
                        if ($this_node->type == 'complete') $bl++;
                    }
                    if ($this_node->type == 'close') {
                        $bl++;
                    }
                }
            }
        }
    }

    /**
     * vlist_html
     * Restituisce il codice html della lista verticale
     *
     * @return unknown
     */
    function vlist_html()
    {
        global $in;
        $center = $in['CENTER'];
        $center = '00' . $center;
        $center = substr($center, strlen($center) - 3, 3);
        for ($i = 0; $i < count($this->blocco); $i++) $this->vlist($i);
        return $this->body;
    }

    /**
     * vlist
     *
     * Costruisce i dati della lista
     *
     * @param unknown_type $i
     */
    function vlist($i)
    {
        $where = null;
        global $conn;
        global $in;
        $filter = $this->blocco[$i]['FILTER'];
        #echo $filter;
        $filter = explode(",", $filter);
        for ($f = 0; $f < count($filter); $f++) {
            if ($in[$filter[$f]] != '') $where .= " and " . $filter[$f] . "=:" . $filter[$f];
            $bind_filter[$filter[$f]] = $in[$filter[$f]];
        }
        if ($this->blocco[$i]['DECODE'] != '') {
            $query = "select distinct " . $this->blocco[$i]['DECODE'] . " as decode, " . $this->blocco[$i]['VALUE'] . " as value from " . $this->blocco[$i]['TABLE'] . " where " . $this->blocco[$i]['VALUE'] . " is not null $where order by " . $this->blocco[$i]['VALUE'] . "";
            $sql = new query($conn);

            #echo "<hr> $query<hr>";
            $sql->exec($query, $bind_filter);//binded
            while ($sql->get_row()) {
                #echo $sql->row['DECODE']." - ".$sql->row['VALUE']."<hr>";
                $in[$sql->row['DECODE']] = $sql->row['VALUE'];
                $this->body .= "<br><br>
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tbody>
	        <tr>
	         <td class=\"int\" align=center>" . $sql->row['DECODE'] . " - " . $sql->row['VALUE'] . "</td>
	          </tr></table>";
                #$in['PAT_RISK']=$sql->row['VALUE'];
                foreach ($this->blocco[$i] as $key => $val) {
                    $function_to_call = "call_" . $key;
                    if (method_exists($this, $function_to_call)) $this->{$function_to_call}($val);
                }
            }
        } else {
            if ($this->blocco[$i]['TESTO'] != '')
                $this->body .= "
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tr>
	         <td class=\"int\">" . $this->blocco[$i]['TESTO'] . "</td>
	          </tr></table>";
            foreach ($this->blocco[$i] as $key => $val) {
                $function_to_call = "call_" . $key;
                if (method_exists($this, $function_to_call)) $this->{$function_to_call}($val);
            }

        }
    }

    /**
     * call_attach_list
     * Gestione delle liste annidate
     *
     * @param string $value
     */
    function call_attach_list($value)
    {
        global $xml_dir;
        #echo "<hr>call_attach_list($value)";
        $list_o = new xml_list($xml_dir . '/' . $value, null, null, null, null, $this->session_vars);
        global $in;
        $lista = $list_o->list_html();
        if (!$list_o->empty) $this->body .= $lista;
    }

    /**
     * call_attach_vlist
     * Gestione delle liste verticali annidate
     *
     * @param unknown_type $value
     */
    function call_attach_vlist($value)
    {
        $list_o = null;
        global $xml_dir;
        #echo "<hr>call_attach_vlist($value)";
        $v_list_o = new xml_vlist($xml_dir . '/' . $value);
        #echo "<hr>OK<hr>";
        global $in;
        $lista = $v_list_o->vlist_html();
        if (!$list_o->empty) $this->body .= $lista;
    }
}


?>
