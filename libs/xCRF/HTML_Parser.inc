<?

/**
 * Classe HTML_Parser
 * Genera il codice html W3C compliant
 * @package CORE
 *
 */
class HTML_Parser{
	
	var $attributes;
	var $content;
	var $html_attributes;
	var $type;
	
	/**
	 * Costruttore
	 *
	 * $attributes: array associativo degli attributi
	 * $content stringa con il contenuto del tag
	 * $type: stringa con il tipo di tag (ad es: TD, TR...)
	 * 
	 * @param array $attributes
	 * @param string $content
	 * @param string $type
	 * @return HTML_Parser
	 */
	function HTML_Parser($attributes=null, $content=null,$type=null){
		$this->attributes=$attributes;
		$this->content=$content;
		$this->type=$type;
	}
	
	/**
	 * setAttribute
	 * Imposta l'attributo $attribute
	 *
	 * @param string $attribute
	 * @param string $value
	 */
	function setAttribute($attribute, $value){
		$this->attributes[$attribute]=$value;
	}
	
	/**
	 * getAttributes
	 * Restituisce il valore dell'attributo $attribute
	 *
	 * @param string $attribute
	 * @return string
	 */
	function getAttribute($attribute){
		return $this->attributes[$attribute];
	}
	
	/**
	 * setType
	 * Imposta il tipo di tag
	 *
	 * @param string $type
	 */
	function setType($type){
		$this->type=strtolower($type);
	}
	
	/**
	 * getType
	 * Resituisce la tipologia del tag
	 *
	 * @return string
	 */
	function getType(){
		return $this->type;
	}
	
	/**
	 * setContent
	 * Imposta il contenuto del tag
	 *
	 * @param string $content
	 */
	function setContent($content){
		$this->content=$content;
	}
	
	/**
	 * getContent
	 * Restituisce la proprietà Content
	 *
	 * @return string
	 */
	function getContent(){
		return $this->content;
	}
	
	/**
	 * build_attributes
	 * Costruisce la lista degli attributi
	 *
	 */
	function build_attributes(){
		foreach ($this->attributes as $key=>$val){
			switch ($key){
				case "class":
					$this->html_attributes.=" class='$val'";
					break;
				case "colspan":
					if ($val=='') $val=1;
					$this->html_attributes.=" colspan=\"$val\"";
					break;
				case "rowspan":
					if ($val=='') $val=1;
					$this->html_attributes.=" rowspan=\"$val\"";
					break;
				case "id":
					$this->html_attributes.=" id=\"$val\"";
					break;
				case "display":
					$style.="display:$val;";
					break;
				case "type":
					$this->html_attributes.=" type=\"$val\"";
					break;
				case "align":
					$style.="text-align:$val;";
					break;
				case "onblur":
					if ($val!='') $this->html_attributes.=" $key=\"$val\"";
					 break;
				default:
					if ($val!='') $this->html_attributes.=" $key=\"$val\"";
					else $this->html_attributes.=" $key";
					break;
			}
		}
		if ($style!='') $style=" style=\"$style\"";
		$this->html_attributes.=$style;
	}
	
	/**
	 * print_
	 * Restituisce il codice html generato
	 *
	 * @return string
	 */
	function print_(){
		$this->build_attributes();
		if (method_exists($this, $this->getType())) return $this->{$this->getType()}();
	}
	
	/**
	 * td
	 * Tag di tipo TD
	 *
	 * @return string
	 */
	function td(){
		return "<td {$this->html_attributes}>{$this->content}</td>";
	}
	
	/**
	 * input
	 * Tag di tipo input
	 *
	 * @return unknown
	 */
	function input(){
		return "<input {$this->html_attributes} value=\"{$this->content}\"/>";
	}
	
	
}

?>