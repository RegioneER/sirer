<?

/**
 * Classe nodo XML
 *
 * @package CORE
 */
class xml_node{

    /**
     * Nome del tag
     *
     * @var String
     */
    var $tag;
    /**
     * Tipo del tag
     *
     * @var String
     */
    var $type;
    /**
     * Attributi del nodo
     *
     * @var array
     */
    var $attributes;
    /**
     * Valore
     *
     * @var String
     */
    var $value;


    /**
     * Costruisce un noda da un array
     *
     * @param array $node
     */
    function xml_node_by_array($node){
        $this->tag=$node['tag'];
        $this->type=$node['type'];
        $this->attributes=$node['attributes'];
        $this->value=$node['value'];
    }


    /**
     * Costruisce un nodo
     *
     * @param String $tag
     * @param String $type
     * @param array $attributes
     * @param String $value
     */
    function xml_node_by_val($tag, $type, $attributes, $value){
        $this->tag=$tag;
        $this->type=$type;
        $this->attributes=$attributes;
        $this->value=$value;
    }


    /**
     * Restituisce il codice XML del nodo
     *
     * @return String
     */
    function print_xml_node(){
       $node='';
       if (preg_match('/</',$this->value) or preg_match('/>/',$this->value)) $this->value="<![CDATA[".$this->value."]]>";
       if ($this->type=='open'){
            $node.= "<".$this->tag."";
            if ( $this->attributes)  $node.=$this->print_attr();
            $node.= ">".$this->value;
       }
       if ($this->type=='complete'){
            $node.= "<".$this->tag."";
            if ( $this->attributes) $node.=$this->print_attr();
            $node.= ">".$this->value."</".$this->tag.">";
       }
       if ($this->type=='close'){
            $node.= "</".$this->tag."> ";
       }
       return $node;
    }


    /**
     * Restituisce gli attributi del nodo
     *
     * @return String
     */
    function print_attr(){
        $attr_str='';
        foreach ($this->attributes as $key => $val){
                $attr_str.=" $key=\"$val\"";
        }
        return $attr_str;
    }

    
}




/**
 * Parser XML
 *
 * @package CORE
 */
class my_xml_parser{

    /**
     * Nome del file
     *
     * @var String
     */
    var $xml_file;
    /**
     * Indice
     *
     * @var Array
     */
    var $index;
    /**
     * Valori dell'XML
     *
     * @var array
     */
    var $vals;



    /**
     * Costruttore
     *
     * @param String $xml_file
     * @return my_xml_parser
     */
    function my_xml_parser($xml_file){
    	global $in;
        global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
        global $session_number;
        $real_file_path=realpath($xml_file);
        $doc_root_real=realpath($_SERVER['DOCUMENT_ROOT']);
        if(!preg_match('|^'.$doc_root_real.'|', $real_file_path)){
            error_page($in['remote_userid'],'Error possible path traversal','Error possible path traversal');
        }
		if ($service!=''){
						#echo $service;
						#$SQL_QUERY=preg_replace("/'/", "''", $this->str);
						foreach ($in as $key => $val) {
							if ($POST_GET_PARAM!='') $POST_GET_PARAM.=" - ";
							$POST_GET_PARAM.="$key=$val";
						}
						foreach ($SRV as $key => $val) {
							if ($SERVER_PARAM!='') $SERVER_PARAM.=" - ";
							$SERVER_PARAM.="$key=$val";
						}
						$POST_GET_PARAM=preg_replace("/&/", "", $POST_GET_PARAM);
						$SERVER_PARAM=preg_replace("/\n/", "", $SERVER_PARAM);
						$SERVER_PARAM=preg_replace("/<(.*?)>/", "", $SERVER_PARAM);
						$SERVER_PARAM=preg_replace("/\r/", "", $SERVER_PARAM);
						$SERVER_PARAM=preg_replace("/\t/", "", $SERVER_PARAM);
						$SERVER_PARAM=preg_replace("/&/", "&&", $SERVER_PARAM);
                        $XML_FILE=$xml_file;
						$sql="insert into ".$service."_LOGS (userid, SERVER_PARAM, POST_GET_PARAM, XML_FILE, ACTION,ID, SID) values('$remote_userid','$SERVER_PARAM', '$POST_GET_PARAM', '$XML_FILE', 'Parsing XML file',".$service."_logs_seq.nextval, $session_number)";
						#echo "<hr>$sql";
                        $stmt = OCIParse($log_conn->conn, $sql);
						ociexecute($stmt);
                        $log_conn->commit();
				}
        $this->xml_file=$xml_file;
        $filetxt = file_get_contents($xml_file) or error_page($in['remote_userid'],"XML FILE: $xml_file not found","");
        global $config_service;
        if(isset($config_service['PARSER_CHARSET'])){
            if(strtolower($config_service['PARSER_CHARSET'])=='none'){
                $p = xml_parser_create();
            }
            else{
                $p = xml_parser_create($config_service['PARSER_CHARSET']);
            }
        }
        else {
            $p = xml_parser_create();
        }
        xml_parse_into_struct($p, $filetxt, $this->vals, $this->index);
        xml_parser_free($p);

//        print "xml_file = $xml_file<br/>|$filetxt|<br/><br/>";
    }


    /**
     * Restituisce il codice XML
     *
     * @return String
     */
    function print_xml(){
        $this_node=new xml_node();
        $file="<\?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        for ($i=0;$i<count($this->vals);$i++){
                $this_node->xml_node_by_array($this->vals[$i]);
                if ($this_node->type!='cdata'){
                    if ($this_node['level']==2) $file.="   ";
                    if ($this_node['level']==3) $file.="      ";
                    $file.=$this_node->print_xml_node()."\n";
                }
        }
        return $file;
    }

    
}




?>
