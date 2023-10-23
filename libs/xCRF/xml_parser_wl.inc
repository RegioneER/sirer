<?


/**
 * Classe xml_node
 *
 * Singolo nodo xml
 *
 * @package CORE
 *
 */
class xml_node
{

    var $tag;
    var $type;
    var $attributes;
    var $value;


    /**
     * xml_node_by_array
     * Costruisce l'oggetto a partire da un array associativo
     *
     * @param unknown_type $node
     */
    function xml_node_by_array($node)
    {

        $this->tag = $node['tag'];
        $this->type = $node['type'];
        $this->attributes = (isset($node['attributes']) ? $node['attributes'] : array());//$this->attributes=$node['attributes'];
        $this->value = (isset($node['value']) ? $node['value'] : false); //$node['value'];
    }


    /**
     * xml_node_by_val
     * Costruisce l'oggeto a partire dai singoli valore
     *
     * @param string $tag
     * @param string $type
     * @param array $attributes
     * @param string $value
     */
    function xml_node_by_val($tag, $type, $attributes, $value)
    {
        $this->tag = $tag;
        $this->type = $type;
        $this->attributes = $attributes;
        $this->value = $value;
    }


    /**
     * Costruttore
     *
     * @return xml_node
     */
    function print_xml_node()
    {
        $node = '';
        if (preg_match('/</', $this->value) or preg_match('/>/', $this->value)) $this->value = "<![CDATA[" . $this->value . "]]>";
        if ($this->type == 'open') {
            $node .= "<" . $this->tag . "";
            if ($this->attributes) $node .= $this->print_attr();
            $node .= ">" . $this->value;
        }
        if ($this->type == 'complete') {
            $node .= "<" . $this->tag . "";
            if ($this->attributes) $node .= $this->print_attr();
            $node .= ">" . $this->value . "</" . $this->tag . ">";
        }
        if ($this->type == 'close') {
            $node .= "</" . $this->tag . "> ";
        }
        return $node;
    }


    /**
     * print_attr
     *
     * Stampa gli attributi
     *
     * @return string
     */
    function print_attr()
    {
        $attr_str = '';
        foreach ($this->attributes as $key => $val) {
            $attr_str .= " $key=\"$val\"";
        }
        return $attr_str;
    }
}


/**
 * Classe my_xml_parser
 *
 * Classe per la gestione del parser xml
 *
 * @package CORE
 *
 */
class my_xml_parser
{

    var $xml_file;
    var $index;
    var $vals;

    /**
     * Costruttore
     *
     * @param string $xml_file
     * @return my_xml_parser
     */

    //VIENE UTILIZZATO QUESTO FILE!
    function my_xml_parser($xml_file)
    {
        //echo "<li>$xml_file</li>";
        $real_file_path = realpath($xml_file);
        $doc_root_real = realpath($_SERVER['DOCUMENT_ROOT']);
        //if(!preg_match('|^'.$doc_root_real.'|', $real_file_path) &&  $real_file_path!=''){
        //    error_page($in['remote_userid'],'Error possible path traversal','Error possible path traversal');
        //}
        return $this->my_xml_parser_old($xml_file);
        //return $this->my_xml_parser_new($xml_file);
    }

    function my_xml_parser_new($xml_file)
    {
        $in = null; //TODO: check
        global $xml_conn;
        $msg = "";
        if (!isset($xml_conn) || $xml_conn == '') {
            $xml_conn = new dbconn();
            $msg .= "CREO CONNESSIONE DB xml_conn\n";
        }
        $sql_query = "select count(*) as exist from user_all_tables where table_name='XMR_FS_XML'";
        $query = new query($xml_conn);
        $query->get_row($sql_query);
        if ($query->row['EXIST'] == '0') {
            $sql_create_1 = "
			create table XMR_FS_XML
			(
			\"PATH\" varchar2(2000 char),
			\"DT\" date,
			\"TS\" number,
			\"CONTENT\" clob
			)
			";
            $sql_create_2 = "
			alter table XMR_FS_XML add constraint PK_XMR_FS_XML primary key (PATH)
			";
            $query->set_sql($sql_create_1);
            $query->ins_upd();//non richiede binding
            $query->set_sql($sql_create_2);
            $query->ins_upd();//non richiede binding
        }
        $msg .= "File: $xml_file - eseguo filemtime\n";
        $lastmod = filemtime($xml_file);
        $error = false;
        if (!$lastmod) {
            $error = true;
            $msg .= "filemtime FALLITA!!!!\n";
        }
        $lastmod -= 0;
        $date_format = date("d/m/Y H:i:s", $lastmod);
        $sql_query = "select * from XMR_FS_XML where PATH='{$xml_file}'";
        $query->exec($sql_query); //obsoleta e non richiede binding
        if ($query->get_row()) {
            $msg .= "File presente in DB (lastmod fs: $lastmod - lastmod db: {$query->row['TS']}\n";
            $query->row['TS'] -= 0;
            if ($query->row['TS'] < $lastmod) {
                $query2 = new query($xml_conn);
                $msg .= "Effettuo update\n";
                $values['TS'] = $lastmod;
                $values['DT'] = "to_date('$date_format','DD/MM/YYYY HH24:MI:SS')";
                $content = $clob['CONTENT'] = file_get_contents($xml_file);
                if (!$content) {
                    $content = $query->row['CONTENT'];
                    $error = true;
                    $msg .= "ERRORE LETTURA (file_get_contents)!!!!";
                } else {
                    $pk['PATH'] = $xml_file;
                    $query2->update($values, "XMR_FS_XML", $pk, $clob);
                    $xml_conn->commit();
                }
            } else {
                $msg .= "Utilizzo versione DB\n";
                $content = $query->row['CONTENT'];
            }
        } else {
            $query2 = new query($xml_conn);
            $msg .= "File non presente in DB, carico dati per insert\n";
            $values['TS'] = $lastmod;
            $values['DT'] = "to_date('$date_format','DD/MM/YYYY HH24:MI:SS')";
            $content = $clob['CONTENT'] = file_get_contents($xml_file);
            if (!$content) {
                $error = true;
                $msg .= "ERRORE LETTURA (file_get_contents)!!!!";

            } else {
                $values['PATH'] = $xml_file;
                $pk = '';
                $query2->insert($values, "XMR_FS_XML", $pk, true, null, $clob);
                $xml_conn->commit();
            }
        }
        if ($error) {
            $msg .= "----SPECIFICHE----\n";
            if (!file_exists($xml_file)) $msg .= "La file_exists riporta errore per il file $xml_file\n";
            else $msg .= "La file_exists riporta successo per il file $xml_file\n";
            $msg .= "Time: " . date("d/m/Y H:i:s") . "\n";
            ob_start();
            print_r($_SERVER);
            $msg .= ob_get_contents();
            ob_end_clean();
            mail("amr-admin@cineca.it", "File non trovato su FS {$_SERVER['SERVER_NAME']} - {$_SERVER['SERVER_ADDR']}", $msg);
        }
        $filetxt = $content;
        if ($filetxt == '') {
            header("HTTP/1.1 404 Not Found");
            error_page($in['remote_userid'], "{$msg} XML FILE: $xml_file not found", array('LINEA' => __LINE__, 'FILE' => __FILE__));
        }
        global $config_service;
        if (isset($config_service['PARSER_CHARSET'])) {
            if (strtolower($config_service['PARSER_CHARSET']) == 'none') {
                $p = xml_parser_create();
            } else {
                $p = xml_parser_create($config_service['PARSER_CHARSET']);
            }
        } else {
            $p = xml_parser_create("ISO-8859-1");
        }
        xml_parse_into_struct($p, $filetxt, $this->vals, $this->index);
        xml_parser_free($p);
    }


    //*/


    function my_xml_parser_old($xml_file)
    {
        global $in;
        global $SRV;
        global $log_conn;
        global $service;
        global $remote_userid;
        global $session_number;
        $path = "";
        $dirs = explode("/", $xml_file);
        unset($dirs[count($dirs) - 1]);
        foreach ($dirs as $key => $curr_dir) {
            $path .= "/" . $curr_dir;
        }
// 		$dummyFile=$path."/dummy";
// 		$createDummyFile=system("touch ".$dummyFile);
        $this->xml_file = $xml_file;
//		


        $filetxt = file_get_contents($xml_file);
        if ($filetxt == '') {
            if (preg_match("!sissdev\.cineca!", $_SERVER['HTTP_HOST'])) {
                $xml_file = "/siss-devel" . $xml_file;
            }

            $filetxt = file_get_contents($xml_file);
            if ($filetxt != '') {
                mail("c.contino@cineca.it,m.chiesi@cineca.it", "Errore File non found $xml_file", "File non trovato al path $xml_file \n work-around funzionante(aggiungo /siss-devel in testa al path $xml_file");
            }
        }
        if ($filetxt == '') {
            if (!file_exists($xml_file)) {
                error_page($in['remote_userid'], "XML FILE: $xml_file not found", array('LINEA' => __LINE__, 'FILE' => __FILE__));
            } else {
                $fp = fopen($xml_file, "r");
                if ($fp) {
                    $filetxt = fread($fp, filesize($xml_file));
                    fclose($fp);
                } else {
                    header("HTTP/1.1 404 Not Found");
                    $msg = "Non si accede al file $xml_file ";
                    foreach ($_SERVER as $key => $val) {
                        $msg .= "\n$key: $val";
                    }
                    $msg = "Non si accede al file $xml_file ";
                    mail('c.contino@cineca.it,f.belletti@cineca.it', "Errore accesso a file $xml_file", $msg);
                    $fallito_in_parser = $fallito = true;
                    if (is_dir("/http/lib/php_utils/")) {
                        include("/http/lib/php_utils/nosuch_web_in_parser.php");
                        include("/http/lib/php_utils/nosuch_web_in_parser_local_fs.php");
                    }
                    error_page($in['remote_userid'], "XML FILE: $xml_file not found", array('LINEA' => __LINE__, 'FILE' => __FILE__));
                }
            }
        } else {
            $fallito_in_parser = $fallito = false;
            if (is_dir("/http/lib/php_utils/")) {
                include("/http/lib/php_utils/nosuch_web_in_parser.php");
                include("/http/lib/php_utils/nosuch_web_in_parser_local_fs.php");
            }
        }
        if ($filetxt == '') {
            header("HTTP/1.1 404 Not Found");
            error_page($in['remote_userid'], "XML FILE: $xml_file not found", array('LINEA' => __LINE__, 'FILE' => __FILE__));
        }
        //unlink($dummyFile);
        global $config_service;
        if (isset($config_service['PARSER_CHARSET'])) {
            if (strtolower($config_service['PARSER_CHARSET']) == 'none') {
                $p = xml_parser_create();
            } else {
                $p = xml_parser_create($config_service['PARSER_CHARSET']);
            }
        } else {
            $p = xml_parser_create();
        }
        xml_parse_into_struct($p, $filetxt, $this->vals, $this->index);
        xml_parser_free($p);
    }

    /**
     * print_xml
     *
     * Costruisce il codice xml dall'oggetto
     *
     * @return unknown
     */
    function print_xml()
    {
        $this_node = new xml_node();
        $file = "<\?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        for ($i = 0; $i < count($this->vals); $i++) {
            $this_node->xml_node_by_array($this->vals[$i]);
            if ($this_node->type != 'cdata') {
                if ($this_node['level'] == 2) $file .= "   ";
                if ($this_node['level'] == 3) $file .= "      ";
                $file .= $this_node->print_xml_node() . "\n";
            }
        }
        return $file;
    }
}


?>
