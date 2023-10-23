<?
/**
 * Classe xml_page_prototype
 * Class eper la gestione della pagine statiche
 * @package ViewsAndControllers
 *
 */
class xml_page_prototype{

	var $titolo;
	var $blocco;
	var $links;
	var $html;
	var $page;
	var $body;
	var $admin_profili;

	/**
	 * Costruttore
	 *
	 * @param string $xml_file
	 * @return xml_page_prototype
	 */
	function xml_page_prototype($xml_file,$admin_profili=null){
		$this->admin_profili=$admin_profili;
		$xml_parser=new my_xml_parser($xml_file);
		$newtag=true;
		$bl=0;
		$ln=0;
		$this_node=new xml_node();
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){
				if ($this_node->tag=='PAGE') if ($this_node->type=='open' or $this_node->type=='complete') {
					$this->page=$this_node->attributes;
				}
				if ($this_node->tag=='BLOCCO') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->blocco[$bl]=$this_node->attributes;
						$ln=0;
					}
					if ($this_node->type=='close') {
						$bl++;
					}
				}
				if ($this_node->tag=='LINK') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->links[$bl][$ln]=$this_node->attributes;
					}
					if ($this_node->type=='close') {
						$ln++;
					}
				}
				if ($this_node->tag=='TESTO'){
					if ($this_node->type=='open' or $this_node->type=='complete') $this->links[$bl][$ln]['TESTO']=$this_node->value;
				}
			}
		}
	}

	/**
	 * page_html
	 * Costruisce il codice html della pagina
	 *
	 * @return string
	 */
	function page_html(){
		for ($i=0;$i<count($this->blocco);$i++) $this->body.=$this->blocco_html($i);
		return $this->body;
	}

	/**
	 * blocco_html
	 * Costrusice il codice html del $i-esimo blocco
	 *
	 * @param int $i
	 * @return string
	 */
	function blocco_html($i){
		$html="
		  				<TABLE cellSpacing=2 cellPadding=2 width=\"95%\" align=center border=0>
              <TBODY>
              	<TR>
                	<TD class=int>".$this->blocco[$i]['TITOLO']."</td>
								</tr>
							";
		for ($l=0;$l<count($this->links[$i]);$l++) {
			$param=$this->links[$i][$l]['PARAM'];
            if ($param) {
                $params = explode(",", $param);
                $param = "";
                for ($p = 0; $p < count($params); $p++) {
                    $params[$p] = preg_replace("/\|/i", ",", $params[$p]);
                    #echo "{$params[$p]} <br>";
                    $param .= $params[$p] . "&";
                }
            }
//			if($this->links[$i][$l]['TR_CSS_CLASS']!="") $tr_css_class="class=\"{$this->links[$i][$l]['CLASS']}\" ";
//			else $tr_css_class="";
//			
//			echo $this->links[$i][$l]['TR_CSS_CLASS'];
//			
//			if($this->links[$i][$l]['ONCLICK']!="") $tr_onclick=" onclick=\"{$this->links[$i][$l]['ONCLICK']}\" ";
//			else $tr_onclick="";
			
//			echo "<a href=\"".$this->links[$i][$l]['SCRIPT']."?".$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param."\">".$this->links[$i][$l]['TESTO']."</a>";
			if ($this->links[$i][$l]['TIPO']!='') $param=$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param;
			if ($this->links[$i][$l]['PARAM']=="ADMIN_PROFILI=yes" && !in_array($_SERVER['REMOTE_USER'],$this->admin_profili)) {
				$html.="<tr>
						<td class=\"destra-bis\">Profilo non abilitato alla gestione dei profili</td>
					</tr>";
			} else {		
				$html.="<tr>
						<td class=\"destra-bis\"><a href=\"".$this->links[$i][$l]['SCRIPT'].($param?"?{$param}":"")."\">".$this->links[$i][$l]['TESTO']."</a></td>
					</tr>
						   ";
			}
		}
		$html.=" </table>";
		return $html;

	}
}


?>
