<? 

include_once "xml_form.inc";
include_once "xml_page.inc";
###class xml_node### 
/*
<b>LIBRERIA DI GESTIONE XML</B>
    
    <b>Autore Carlo Contino</b>
    Data 21/04/2006
    
    <b>Sintassi costruttore:</b>
        $nome_oggetto=new <b>xmlnode</b>()
    <b>Variabili:</b>
        <b>$tag:</b> nome del tag;
        <b>$type:</b> tipo (apertura, chiusura, completo);
        <b>$attributes:</b> Array degli attributi;
        <b>$value:</b> valore (testo compreso tra il tag di apertura e chiusura;
    <b>Metodi:</b>
        <b>xml_node_by_array($node as array) as void:</b>  inizializza le variabili con i valori passati e crea la connessione ;    
        <b>xml_node_by_val($tag as string, $type as string, $attributes as array, $value as string) as void:</b> costruisce il nodo con i valori passati;
        <b>print_xml_node() as string:</b> restituisce una stringa con il codice xml relativo al nodo;
        <b>print_attr() as string:</b> restituisce una stringa con le chiavi ed i relativi valori degli attributi;
*/
###endclass###

class xml_node{
    
    var $tag;
    var $type;
    var $attributes;
    var $value;
    
###sub xml_node_by_array($node as array) as void###
    function xml_node_by_array($node){
        $this->tag=$node['tag'];
        $this->type=$node['type'];
        $this->attributes=$node['attributes'];
        $this->value=$node['value'];        
    }
###endsub###

###sub  xml_node_by_val($tag as string, $type as string, $attributes as array, $value as string) as void###
    function xml_node_by_val($tag, $type, $attributes, $value){
        $this->tag=$tag;
        $this->type=$type;
        $this->attributes=$attributes;
        $this->value=$value; 
    }
###endsub###
    
    
###sub print_xml_node() as string###
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
###endsub###
    
###sub print_attr() as string###
    function print_attr(){ 
        $attr_str='';  
        foreach ($this->attributes as $key => $val){ 
                $attr_str.=" $key=\"$val\"";
        }
        return $attr_str;
    }
###endsub###
} 


###class my_xml_parser###
/*
<b>Autore Carlo Contino</b>
    Data 26/04/2006
    
    <b>Sintassi costruttore:</b>
        $nome_oggetto=new <b>my_xml_parser</b>($nome_file_xml)
    <b>Variabili:</b>
        <b>$xml_file:</b> nome del file xml;
        <b>$index:</b> array di indicizzazione;
        <b>$vals:</b> Array dei valori;
    <b>Metodi:</b>
        <b>my_xml_parser($xml_file as string) as void:</b>  Costruttore: inizializza le variabili interne leggendo il contenuto del file xml;  
        <b>print_xml() as string:</b> Stampa il contenuto dell'array $vals in formato xml;

*/ 
###endclass###
class my_xml_parser{

    var $xml_file;
    var $index;
    var $vals;

###sub my_xml_parser($xml_file as string) as void###    
    function my_xml_parser($xml_file){
    	global $in;
        global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
        global $session_number;
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
        $filetxt = file_get_contents($xml_file) or error_page($in['remote_userid'],"FILE XML: $xml_file non trovato","");
        $p = xml_parser_create();
        xml_parse_into_struct($p, $filetxt, $this->vals, $this->index);
        xml_parser_free($p);
    }
###endsub###

###sub print_xml() as string###    
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
###endsub###
}




?>                                
