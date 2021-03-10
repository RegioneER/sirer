<?
class xml_vlist{

	var $titolo;
	var $blocco;
	var $links;
	var $html;
	var $page;

	function xml_vlist($xml_file){
		$xml_parser=new my_xml_parser($xml_file);
		$newtag=true;
		$bl=0;
		$this_node=new xml_node();
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){
				if ($this_node->tag=='VLIST') if ($this_node->type=='open' or $this_node->type=='complete') {
					$this->page=$this_node->attributes;

				}
				if ($this_node->tag=='ROW') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->blocco[$bl]=$this_node->attributes;
						$this->blocco[$bl]['TESTO']=$this_node->value;
						if ($this_node->type=='complete') $bl++;
					}
					if ($this_node->type=='close') {
						$bl++;
					}
				}
			}
		}
	}

	function vlist_html(){
		global $in;
		$center=$in['CENTER'];
		$center='00'.$center;
		$center=substr($center, strlen($center)-3,3);
		for ($i=0;$i<count($this->blocco);$i++) $this->vlist($i);
		return $this->body;
	}

	function vlist($i){
		global $conn;
		global $in;
		if (isset($this->blocco[$i]['FILTER'])) $filter=$this->blocco[$i]['FILTER'];
		#echo $filter;
		if (isset($filter)) $filter=explode(",",$filter);
		if (isset($filter)) for ($f=0;$f<count($filter);$f++){
			if ($in[$filter[$f]]!='') $where.=" and ".$filter[$f]."='".$in[$filter[$f]]."'";
		}
		if (isset($this->blocco[$i]['WHERE']) && $this->blocco[$i]['WHERE']!=''){
			$where.=" and ";
			$where.=$this->blocco[$i]['WHERE'];
			//$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
			$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
		}
		#echo "<hr>$where<hr>";
		if ($this->blocco[$i]['DECODE']!='') {
			$query="select distinct ".$this->blocco[$i]['DECODE']." as decode, ".$this->blocco[$i]['VALUE']." as value from ".$this->blocco[$i]['TABLE']." where ".$this->blocco[$i]['VALUE']." is not null $where order by ".$this->blocco[$i]['VALUE']."";
			$sql=new query($conn);
			$sql->set_sql($query);
			#echo "<hr> $query<hr>";
			$sql->exec();//obsoleto trovare dove testare
			while ($sql->get_row()){
				#echo $sql->row['DECODE']." - ".$sql->row['VALUE']."<hr>";
				$in[$sql->row['DECODE']]=$sql->row['VALUE'];
				$in[$this->blocco[$i]['SET']]=$sql->row['VALUE'];
				#echo "{$this->blocco[$i]['SET']} = {$in[$this->blocco[$i]['SET']]}<br>";
				$this->body.="<br><br>
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tbody>
	        <tr>
	         <td class=\"int\" align=center>".$sql->row['DECODE']."</td>
	          </tr></table>";
				#$in['PAT_RISK']=$sql->row['VALUE'];
				foreach ($this->blocco[$i] as $key => $val){
					$function_to_call="call_".$key;
					if (method_exists($this, $function_to_call)) $this->{$function_to_call}($val);
				}
			}
		}
		else {
			if ($this->blocco[$i]['TESTO']!='')
			$this->body.="<br><br>
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tr>
	         <td class=\"titolo1\">".$this->blocco[$i]['TESTO']."</td>
	          </tr></table>";
			foreach ($this->blocco[$i] as $key => $val){
				$function_to_call="call_".$key;
				if (method_exists($this, $function_to_call)) $this->{$function_to_call}($val);
			}

		}
	}

	function call_attach_list($value){
		global $xml_dir;
		#echo "<hr>call_attach_list($value)";
		$list_o= new xml_list($xml_dir.'/'.$value, null, null, null, null, $this->session_vars );
//		global $in;
		$lista=$list_o->list_html();
		if (!$list_o->empty) $this->body.=$lista;
		else $this->body.="<p align=center><b>Nessun messaggio presente</b></p>";
	}

	function call_attach_vlist($value){
		global $xml_dir;
		#echo "<hr>call_attach_vlist($value)";
		$v_list_o= new xml_vlist($xml_dir.'/'.$value);
		#echo "<hr>OK<hr>";
		global $in;
		$lista=$v_list_o->vlist_html();
		$in['DA']='';
		$in['A']='';
		if (!$list_o->empty) $this->body.=$lista;
	}
}

class xml_page{

	var $titolo;
	var $blocco;
	var $links;
	var $html;
	var $page;
	var $body;
	var $PK_SERVICE;
	var $xml_file;

	function xml_page($xml_file){
		$this->$xml_file = $xml_file;
		$xml_parser=new my_xml_parser($xml_file);
		$newtag=true;
		$bl=0;
		$ln=0;
		global $config_service;
		$this->PK_SERVICE=$config_service['PK_SERVICE'];
		//echo "<hr>{$this->PK_SERVICE}<hr> ";
		$this_node=new xml_node();
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);

			//                print "Nodo $i..." .$this_node->print_xml_node() ."----". $this_node->type ."---->". $this_node->attributes."<----" ."<br/>" ;

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

	function page_html(){
		for ($i=0;$i<count($this->blocco);$i++) $this->body.=$this->blocco_html($i);
		return $this->body;
	}

	function blocco_html($i){
		$html="<br>
		  				<TABLE cellSpacing=2 cellPadding=2 width=\"80%\" align=center border=0>
              <TBODY>
              	<TR>
                	<TD class=titolo>".$this->blocco[$i]['TITOLO']."</td>
								</tr>
							";
		for ($l=0;$l<count($this->links[$i]);$l++) {
			$param=$this->links[$i][$l]['PARAM'];
			$params=explode(",",$param);
			$param="";

			for ($p=0;$p<count($params);$p++) $param.=$params[$p]."&amp;";
			//$param=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $param);
			$param=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $param );
			#echo "<A href=\"".$this->links[$i][$l]['SCRIPT']."?".$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param."\">".$this->links[$i][$l]['TESTO']."</a>";
			$html.="
								<tr>
								 <td class=\"destra-bis\"><A class=\"home\" href=\"".$this->links[$i][$l]['SCRIPT']."?".$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param."\">".$this->links[$i][$l]['TESTO']."</a>
							   </td>
						   </tr>
						   ";
		}
		$html.=" </table>";
		return $html;

	}
}

class xml_list{

	var $titolo;
	var $cols;
	var $html;
	var $list;
	var $sql;
	var $empty=true;
	var $nome_file;
	var $PK_SERVICE;

	function xml_list($xml_file){
		$this->nome_file=$xml_file;

		$xml_parser=new my_xml_parser($xml_file);
		global $config_service;
		if ($config_service['PK_SERVICE']!='') $this->PK_SERVICE=$config_service['PK_SERVICE'];
		else $this->PK_SERVICE='CODPAT';
		$newtag=true;
		$cl=0;
		$this_node=new xml_node();
		#print_r($xml_parser->vals);
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){
				if ($this_node->tag=='LIST') if ($this_node->type=='open' or $this_node->type=='complete') {
					$this->list=$this_node->attributes;
				}
				if ($this_node->tag=='COL') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->cols[$cl]=$this_node->attributes;
						$this->cols[$cl]['TESTO']=$this_node->value;
						if ($this_node->type=='complete') $cl++;
					}
					if ($this_node->type=='close') {
						$cl++;
					}
				}
			}
		}

	}

	function col_th_testo($i){
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		$txt=$this->cols[$i]['TESTO'];
		if ($this->cols[$i]['ORD_ARROW']!='') {
			if ($this->cols[$i]['ORD_ARROW']=='yes') $this->cols[$i]['ORD_ARROW']=$this->cols[$i]['NOME'];
			$img_down="/images/down_arrow.gif";
			if ($in['ORD_TYPE']=='ASC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_down="/images/down_arrow_red.gif";
			$img_up="/images/up_arrow.gif";
			if ($in['ORD_TYPE']=='DESC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_up="/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			foreach($_GET as $key=>$val){
				if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="$key=$val&";
			}
			if (isset($in['page'])) $param.="page=1&";
			if (isset($in['ESAM'])&&isset($in['VISITNUM'])&&($in['VISITNUM']==0) &&($in['ESAM']==0))
			{

				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			}
			else
			{	//solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in['CENTER']!='') $center="CENTER={$in['CENTER']}";
				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		return "<th class=\"int\">".$txt."</th>";
	}

	function col_th_archivia($i){
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		$txt=$this->cols[$i]['TESTO'];
		if ($this->cols[$i]['ORD_ARROW']!='') {
			if ($this->cols[$i]['ORD_ARROW']=='yes') $this->cols[$i]['ORD_ARROW']=$this->cols[$i]['NOME'];
			$img_down="/images/down_arrow.gif";
			if ($in['ORD_TYPE']=='ASC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_down="/images/down_arrow_red.gif";
			$img_up="/images/up_arrow.gif";
			if ($in['ORD_TYPE']=='DESC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_up="/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			foreach($_GET as $key=>$val){
				if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="$key=$val&";
			}
			if (isset($in['page'])) $param.="page=1&";
			if (isset($in['ESAM'])&&isset($in['VISITNUM'])&&($in['VISITNUM']==0) &&($in['ESAM']==0))
			{

				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			}
			else
			{	//solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in['CENTER']!='') $center="CENTER={$in['CENTER']}";
				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		return "<th class=\"int\">".$txt."</th>";
	}


	function col_th_lente($i){
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		$txt=$this->cols[$i]['TESTO'];
		if ($this->cols[$i]['ORD_ARROW']!='') {
			if ($this->cols[$i]['ORD_ARROW']=='yes') $this->cols[$i]['ORD_ARROW']=$this->cols[$i]['NOME'];
			$img_down="/images/down_arrow.gif";
			if ($in['ORD_TYPE']=='ASC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_down="/images/down_arrow_red.gif";
			$img_up="/images/up_arrow.gif";
			if ($in['ORD_TYPE']=='DESC' && $in['ORD']==$this->cols[$i]['ORD_ARROW']) $img_up="/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			foreach($_GET as $key=>$val){
				if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="$key=$val&";
			}
			if (isset($in['page'])) $param.="page=1&";
			if (isset($in['ESAM'])&&isset($in['VISITNUM'])&&($in['VISITNUM']==0) &&($in['ESAM']==0))
			{

				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			}
			else
			{	//solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in['CENTER']!='') $center="CENTER={$in['CENTER']}";
				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		return "<th class=\"int\">".$txt."</th>";
	}

	function col_th_carico($i){
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		$txt=$this->cols[$i]['TESTO'];
		if ($this->cols[$i]['ORD_ARROW']!='') {
			$img_down="/images/down_arrow.gif";
			if ($in['ORD_TYPE']=='ASC' && $in['ORD']==$this->cols[$i]['NOME']) $img_down="/images/down_arrow_red.gif";
			$img_up="/images/up_arrow.gif";
			if ($in['ORD_TYPE']=='DESC' && $in['ORD']==$this->cols[$i]['NOME']) $img_up="/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			if (isset($in['ESAM'])&&isset($in['VISITNUM'])&&($in['VISITNUM']==0) &&($in['ESAM']==0))
			{
				$txt.="
	  			<br><a href=\"index.php?VISITNUM=0&ESAM=0&ORD={$this->cols[$i]['NOME']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?VISITNUM=0&ESAM=0&ORD={$this->cols[$i]['NOME']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			}
			else
			{	//solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in['CENTER']!='') $center="CENTER={$in['CENTER']}";
				foreach($_GET as $key=>$val){
					if ($key!='ORD' && $key!='ORD_TYPE') $param.="$key=$val&";
				}
				$txt.="
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['NOME']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}$center&ORD={$this->cols[$i]['NOME']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		return "<th class=\"int\">".$txt."</th>";
	}

	function col_th_validation($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_eq_link($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_html($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_freccia($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_visita($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_status($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_stato($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}

	function col_th_stampante($i){
		return "<th class=\"int\">".$this->cols[$i]['TESTO']."</th>";
	}


	function col_td_javascrip($i){
		global $in;
		//     echo $in['source']."<br>";
		$in['source']=preg_replace("/?/",",",$in['source']);
		//    echo $in['source']."<br>";
		$in['dest']=preg_replace("/?/",",",$in['dest']);
		$source=explode(",",$in['source']);
		$dest=explode(",",$in['dest']);
		$funct="";
		for ($f=0;$f<count($source);$f++){
			$qval=$this->sql->row[$source[$f]];
			//echo "$qval<br>";
			$qval=preg_replace("/\'/","\'",$qval);
			$qval=preg_replace("/\"/"," ",$qval);
			//echo "$qval<br>";

			$funct.=$this->cols[$i]['NOME_FUN']."('$qval','{$dest[$f]}');";
			//      	echo "$f -- $source[$f] -- $dest[$f]<br>";
			//print_r ($this->sql->row);
			//        echo "{$this->sql->row[$source[$f]]}<br>";
		}
		$value="";
		$value.="<a href=\"\" onClick=\"".$funct."window.close();\">";
		$value.="<img border=\"0\" src=\"/images/".$this->cols[$i]['IMAGE']."\">";
		$value.="</a>";
		return $value."&nbsp;";
	}

	function col_td_status($i){

		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=explode(" - ", $value);
		#echo "<hr>$value[0] . $value[1] . $value[2]<hr>";
		if ($value[1]==1){
			if ($value[0]==0) $txt="<b>Not Elegible for";
			else $txt="<b><a href=\"index.php?CENTER=".$this->sql->row['CENTER']."&{$this->PK_SERVICE}=".$this->sql->row[$this->PK_SERVICE]."&PROTOCOL=".$this->sql->row['PROTOCOL']."\">Enrolled in";
		}
		if ($value[1]=='')$txt="<b>On Screening";
		if ($value[1]=='0')$txt="<b><a href=\"index.php?CENTER=".$this->sql->row['CENTER']."&{$this->PK_SERVICE}=".$this->sql->row[$this->PK_SERVICE]."&VISITNUM=2&PROGR=2&ESAM=2&PROTOCOL=".$this->sql->row['PROTOCOL']."\">Verify Eligibility for";
		if ($this->sql->row['D_PROTOCOL']!='') $txt.="<br/>".$this->sql->row['D_PROTOCOL']."</a>";
		if ($this->sql->row['D_PAT_RISK']!='') $txt.="<br/>".$this->sql->row['D_PAT_RISK'];
		return $txt;
	}



	function col_th_visite($i){
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
		foreach ($visit->visitnums as $key => $val) {
			if ($th!='')	$th.="</th><th class=\"int\">";
			else $th="<th class=\"int\">";
			$th.=$val['SHORT_TXT'];
		}
		$th.="</th>";
		return $th;
	}

	function col_th_visite_gruppo($i){
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
		foreach ($visit->group as $key => $val) {
			if ($th!='')	$th.="</th><th class=\"int\">";
			else $th="<th class=\"int\">";
			$th.=$val['TEXT'];
		}
		$th.="</th>";
		return $th;
	}

	function col_td_visite($i){
		global $xml_dir;
		$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
		foreach ($visit->visitnums as $key => $val) {
			if ($td!='') $td.="</td><td class='sc4bis'>&nbsp;";
			$value=$this->sql->row[strtoupper('V'.$key)];
			$value=explode(" - ", $value);
			if ($value[3]==1){
				#echo " abiliata";
				$img="f_bianca.gif";
				if ($value[0]==1) $img="f_gialla.gif";
				if ($value[1]==1) $img="f_gialla.gif";
				if ($value[2]==1) $img="f_verde.gif";
				$param="?";
				if (count($visit->esams[$key])>1) $param.="exams=".$this->cols[$i]['EXAMS'];
				$params=$this->cols[$i]['PARAM'];
				$params=explode(",",$params);
				if ($param=='') $param='?';
				for ($p=0;$p<count($params);$p++){
					if ($this->sql->row[strtoupper($params[$p])]!='') {
						$param.="&amp;".strtoupper($params[$p])."=".$this->sql->row[strtoupper($params[$p])];
					}
					else $param.="&amp;".$params[$p];
				}
				$param.="&amp;VISITNUM=$key";
				if (count($visit->esams[$key])==1 && $visit->esams[$key]['PROGR']!='yes') {
					#echo "<hr>{$visit->esams[$key]['PROGR']}";
					#print_r($visit->esams[$key]);
					foreach ($visit->esams[$key] as $esam=>$nome_esam) {
						if ($nome_esam['PROGR']!='yes') $param.="&ESAM=$esam&form={$nome_esam['XML']}";
						else $param.="&exams=".$this->cols[$i]['EXAMS'];
					}
				}
				$td.="<a href=\"index.php$param\"><img src=\"/images/$img\" border=0 /></a>";
				#echo $img;
			}
		}
		return $td;
	}

	function col_td_visite_gruppo($i){
		global $xml_dir;
		#echo "<hr>col_td_visite_gruppo<hr>";
		#$th="<th class=\"int\">";
		$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
		foreach ($visit->group as $key => $val) {
			if ($td!='') $td.="</td><td class='sc4bis'>&nbsp;";
			$value=$this->sql->row[strtoupper('V'.$key)];
			# echo "<hr> gruppo $key $value";
			$value=explode(" - ", $value);
			if ($value[3]==1){
				$img="f_bianca.gif";
				if ($value[0]==1) $img="f_gialla.gif";
				if ($value[1]==1) $img="f_gialla.gif";
				if ($value[2]==1) $img="f_verde.gif";
				$param="?exams=".$this->cols[$i]['EXAMS'];
				$params=$this->cols[$i]['PARAM'];
				$params=explode(",",$params);
				if ($param=='') $param='?';
				for ($p=0;$p<count($params);$p++){
					if ($this->sql->row[strtoupper($params[$p])]!='') {
						#echo "<hr>".$params[$p]."=".$this->sql->row[strtoupper($params[$p])];
						$param.="&amp;".strtoupper($params[$p])."=".$this->sql->row[strtoupper($params[$p])];
					}
					else $param.="&amp;".$params[$p];
				}
				$param.="&amp;GROUP=$key";
				$td.="<a href=\"index.php$param\"><img src=\"/images/$img\" border=0 /></a>";
			}
		}
		return $td;
	}

	function col_td_visita($i){
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=explode(" - ", $value);
		if ($value[3]==1){
			$img="f_bianca.gif";
			if ($value[0]==1) $img="f_gialla.gif";
			if ($value[1]==1) $img="f_gialla.gif";
			if ($value[2]==1) $img="f_verde.gif";
			$img_tag="<img src=\"/images/$img\" border=0 />";
		}
		return $img_tag;
	}

	function col_script($i){
		$link=$this->cols[$i]['SCRIPT'];
		if ($this->cols[$i]['LIST']!='') $param="?list=".$this->cols[$i]['LIST'];
		if ($this->cols[$i]['EQUERY_VIEW']!='') $param="?equery_view=".$this->cols[$i]['EQUERY_VIEW'];
		if ($this->cols[$i]['VLIST']!='') $param="?vlist=".$this->cols[$i]['VLIST'];
		if ($this->cols[$i]['EXAMS']!='') $param="?exams=".$this->cols[$i]['EXAMS'];
		if ($this->cols[$i]['FORM']!='') $param="?form=".$this->cols[$i]['FORM'];
		if ($this->cols[$i]['EFORM']!='') $param="?eform=".$this->cols[$i]['EFORM'];
		if ($this->cols[$i]['TARGET']!='') $target="target=\"{$this->cols[$i]['TARGET']}\"";
		if ($this->cols[$i]['CONFIRM']!='') $confirm="onclick=\"if (!confirm('{$this->cols[$i]['CONFIRM']}')) return false;\"";
		//echo "$target<hr>";
		$params=$this->cols[$i]['PARAM'];
		$params=explode(",",$params);
		if ($param=='') $param='?';
		for ($p=0;$p<count($params);$p++){
			if ($this->sql->row[strtoupper($params[$p])]!='') {
				#echo "<hr>".$params[$p]."=".$this->sql->row[strtoupper($params[$p])];
				$param.="&amp;".strtoupper($params[$p])."=".$this->sql->row[strtoupper($params[$p])];
			}
			else $param.="&amp;".$params[$p];
		}
		#echo "<hr>".$param;
		//$param=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $param);
		$param=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $param );
		//	  	echo "<hr>".$param;
		//	  	echo "<hr>".$this->cols[$i]['LINK'];
		if ($this->cols[$i]['LINK']=='1')
		{
			$param=preg_replace("/\?(.*?)=/","", $param);
			//	  	echo "<hr>".$param;
		}
		$link.=$param;
		return "<a href=\"$link\" $target $confirm>";
	}

	function col_td_testo($i){
		global $in;
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		#print_r($this->cols[$i]);
		if ($this->cols[$i]['CRYPTO']=='yes' && ($in['USER_TIP']=='DM' || $in['USER_TIP']=='RO')) $value='****';
		return $value."&nbsp;";
	}

	function col_td_stampante($i){
		return "<img src=\"images/pdf.gif\">";
	}

	function col_td_lente($i){
		//print_r($this->cols[$i]);//if ($this->cols[$i])
		if ($this->cols[$i]['IMG']!='') $img="images/{$this->cols[$i]['IMG']}";
		else $img="images/lente.gif";
		$value="<img src=\"$img\" width=32 border=0>";
		return $value."&nbsp;";
	}

	function col_td_carico($i){
		global $in;
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=rtrim($value, " ");
		//		echo "<li>-$value-".strlen($value)." - {$in['USER_TIP']}</li>";
		if ($value=='' && $in['USER_TIP']=='DM') $value="<input type=\"button\" value=\"Prendi in carico\" onclick=\"window.location.href='index.php?in_carico={$this->sql->row['ID_PRAT']}';\">";
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		return $value."&nbsp;";
	}

	function col_td_archivia($i){
		global $in;
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=rtrim($value, " ");
		foreach($_GET as $key=>$val){
			$param.="$key=$val&";
		}
		$link_back="index.php?{$param}";
		$link_back=urlencode($link_back);
		//		echo "<li>-$value-".strlen($value)." - {$in['USER_TIP']}</li>";
		if (($value=='0' || $value=='2') && $in['USER_TIP']=='DM') $value="";
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		$value="
		<div id='button_archivia_{$this->sql->row['ID_PRAT']}' style=\"display:\">
			<input type=\"button\" value=\"Archivia\" onclick=\"
				show_hide('button_archivia_{$this->sql->row['ID_PRAT']}');
				show_hide('textarea_archivia_{$this->sql->row['ID_PRAT']}')\">
			</div>
		<div  id='textarea_archivia_{$this->sql->row['ID_PRAT']}' style=\"display:none\" >
		Motivazione:<br>
		<textarea id='textvalue_archivia_{$this->sql->row['ID_PRAT']}'></textarea>
		<input type='button' value='invia' onclick=\"
			if (confirm('Sei sicuro di voler archiviare la pratica?'))
			window.location.href='index.php?ARCHIVIA={$this->sql->row['ID_PRAT']}&LINK_BACK={$link_back}&TEXT_VALUE='+document.getElementById('textvalue_archivia_{$this->sql->row['ID_PRAT']}').value;
			else return false;\">
		<input type='button' value='annulla' onclick=\"
				show_hide('button_archivia_{$this->sql->row['ID_PRAT']}');
				show_hide('textarea_archivia_{$this->sql->row['ID_PRAT']}')
				\">
		</div>";
		return $value."&nbsp;";
	}

	function col_td_stato($i){
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		if ($value=='1') $txt_ret='<img src="/images/submitted.gif">';
		else $txt_ret='<img src="/images/saved.gif">';
		return $txt_ret."&nbsp;";
	}

	function col_td_validation($i){
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		if ($this->sql->row['TO_BE_VALIDATE']=='1' && $value=='') {
			return "<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$this->sql->row[$this->PK_SERVICE]."&amp;VISITNUM=".$this->sql->row['VISITNUM']."&amp;ESAM=".$this->sql->row['ESAM']."&amp;PROGR=".$this->sql->row['PROGR']."&amp;equery_view=view&ID=".$this->sql->row['ID']."\">Validate the form</a>";
		}
		else {
			if ($this->sql->row['TO_BE_VALIDATE']!='1') return "Not to be Validated";
			else return $value."&nbsp;";
		}
	}

	function col_td_eq_link($i){
		#echo "<hr>".$this->sql->row['CHIUSA']."<hr>";
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		#$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		if ($this->sql->row['CHIUSA']=='open') $value="<a href=\"index.php?equery_view=view&FORM=equery.xml&ID=$value\">$value</a>";
		return $value."&nbsp;";
	}

	function col_td_html($i){
		$value="<img src=\"images/pdf.jpg\" width=25  border=0 />";
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		return $value;
	}

	function col_td_freccia($i){
		return "<img src=\"/images/send-value.gif\" border=0 />";
	}

	function col_td_cartella($i){
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		return "<img src=\"images/folder_icon_open.gif\" border=0 onclick=\"if (document.getElementById('attach_{$value}').style.display=='none') {document.getElementById('attach_{$value}').style.display=''; this.src='images/folder_icon_open.gif';} else {document.getElementById('attach_{$value}').style.display='none'; this.src='images/folder_icon.gif';}\">";
	}

	function col_td_tree($i){
		$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
		$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		if ($this->sql->numrows==$this->sql->n_r) $img_tree="images/tree-L.png";
		else  $img_tree="images/tree-T.png";
		return "<img src=\"$img_tree\">";
	}

	function col_th_cartella($i){
		if ($this->js_order!='') $this->js_order.=",";
		#echo $this->cols[$i]['TESTO']."<hr>";
		if (preg_match("/date/i",$this->cols[$i]['TESTO'])) $this->js_order.="\"Date\"";
		else $this->js_order.="\"CaseInsensitiveString\"";
		return " \n<td class=\"int\">".$this->cols[$i]['TESTO']."</td>";
	}

	function col_th_tree($i){
		if ($this->js_order!='') $this->js_order.=",";
		#echo $this->cols[$i]['TESTO']."<hr>";
		return " \n<td class=\"int\">".$this->cols[$i]['TESTO']."</td>";
	}

	function list_html(){

		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $config_service;
		$this->sql=new query($conn);

		if ($this->list['ATTACHED']!='YES') $html="<table border=\"0\" id=\"table1\" width=\"95%\"   align=center><tr>";
		$cols=0;
		for ($i=0;$i<count($this->cols);$i++){
			if ($this->cols[$i]['TIPO']!='hidden') $cols++;
			if ($this->cols[$i]['GROUP_BY']!=''){
				if (!isset($group_by)) $group_by=$this->cols[$i]['VAR'];
				else $group_by.=",".$this->cols[$i]['VAR'];
			}
			if ($this->cols[$i]['ORDER_BY']!=''){
				$ord_t=$this->cols[$i]['ORDER_BY'];
				if (!isset($order_by)) $order_by=$this->cols[$i]['NOME'];
				else $order_by.=",".$this->cols[$i]['NOME'];
			}
			if ($in['ORD']!=''){
				$order_by="{$in['ORD']} {$in['ORD_TYPE']}";
			}
			if ($this->cols[$i]['WHERE']!=''){
				if (!isset($where)) $where=$this->cols[$i]['WHERE'];
				else $where.=" and ".$this->cols[$i]['WHERE'];
			}
			if ($this->cols[$i]['VAR']!=''){
				if (!isset($fields)) $fields=$this->cols[$i]['VAR']." as ".$this->cols[$i]['NOME'];
				else $fields.=",".$this->cols[$i]['VAR']." as ".$this->cols[$i]['NOME'];
			}
			if ($this->cols[$i]['TIPO']=='visite_gruppo'){
				$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
				foreach ($visit->group as $key => $val) 	{
					$in_sql='';
					foreach ($val['VISIT'] as $vis => $visval){
						if ($in_sql!='') $in_sql.=",";
						$in_sql.="'$vis'";
					}
					if (!isset($fields)) $fields="(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum in ($in_sql) and ".$GLOBALS['patients_table'].".{$this->PK_SERVICE}=".$GLOBALS['service']."_COORDINATE.{$this->PK_SERVICE}) as v".$key;
					else $fields.=",(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum in ($in_sql) and ".$GLOBALS['patients_table'].".{$this->PK_SERVICE}=".$GLOBALS['service']."_COORDINATE.{$this->PK_SERVICE}) as v".$key;
				}
			}
			if ($this->cols[$i]['TIPO']=='visite'){
				$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
				foreach ($visit->visitnums as $key => $val)
				if (!isset($fields)) $fields="(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum='".$key."' and ".$GLOBALS['patients_table'].".{$this->PK_SERVICE}=".$GLOBALS['service']."_COORDINATE.{$this->PK_SERVICE}) as v".$key;
				else $fields.=",(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum='".$key."' and ".$GLOBALS['patients_table'].".{$this->PK_SERVICE}=".$GLOBALS['service']."_COORDINATE.{$this->PK_SERVICE}) as v".$key;

			}

			//$this->cols[$i]['TABLE']=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $this->cols[$i]['TABLE']);
			$this->cols[$i]['TABLE']=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $this->cols[$i]['TABLE'] );
			if (!preg_match("/".$this->cols[$i]['TABLE']."/i", $tables)) {
				if ($tables!='') $tables.=",";
				$tables.=$this->cols[$i]['TABLE'];

			}
			$function_to_call="col_th_".$this->cols[$i]['TIPO'];
			if (method_exists($this,$function_to_call) && $this->list['ATTACHED']!='YES') $html.=$this->{$function_to_call}($i);
			$nome=$this->cols[$i]['NOME'];

			if (var_glob($nome)!='') {

				if ($where!='') $where.=" and ";
				$where.=$this->cols[$i]['VAR']."='".var_glob($nome)."' ";
			}
			if ($this->cols[$i]['ROWNUM']!='') {
				if ($where!='') $where.=" and ";
				$where.="rownum <= {$this->cols[$i]['ROWNUM']}";
			}
		}

		if ($this->list['ATTACHED']!='YES') $html.="</tr>";
		$query="select $fields from $tables";

		//PARTE RELATIVA ALLA RICERCA//
		foreach ($in as $key => $val){

			if (preg_match("/^S_/", $key)) {
				$key=preg_replace("/^S_/", "", $key);
				if (preg_match("/^FROM_DT_/", $key)) {
					$key=preg_replace("/^FROM_DT_/", "", $key);
					$trovato=false;
					for ($i=0;$i<count($this->cols); $i++){
						if ($this->cols[$i]['NOME']==$key) $trovato=true;
					}
					if ($trovato){

						$val_to=$in['S_TO_DT_'.$key];
						if ($val!='' and $val_to!=''){
							$val=preg_replace("/\//","",$val);
							$val_to=preg_replace("/\//","",$val_to);
							if ($where != '') $where.=" and ";
							$where.="$key between to_date('$val', 'DDMMYYYY') and to_date('$val_to', 'DDMMYYYY')";
						}}
				}
				else {

					$trovato=false;
					for ($i=0;$i<count($this->cols);$i++) {
						if ($this->cols[$i]['NOME']==$key) $trovato=true;

					}
					if ($trovato && $val!=''){
						$val=preg_replace("/?/", "a'", $val);
						$val=preg_replace("/?/", "e'", $val);
						$val=preg_replace("/?/", "i'", $val);
						$val=preg_replace("/?/", "u'", $val);
						$val=preg_replace("/?/", "o'", $val);
						$val=preg_replace("/\\'/","''",$val);
						if ($where != ''  && $in['oper']=='') $where.=" and ";
						if ($where != ''  && $in['oper']!='') $where.=" {$in['oper']} ";
						if ($val=='null') $where.=" $key is null";
						else $where.="lower($key) like '%".strtolower($val)."%'";
					}
				}
			}
		}

		if ($where!='') $query.=" where $where";

		if ($group_by!='') $query.=" group by $group_by";
		if($ord_t!='asc') $ord_t="desc";
		if ($in['ORD']!='') $query.=" order by $order_by ";
		else if ($order_by!='') $query.=" order by $order_by $ord_t";
		//$query=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $query);
		$query=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $query );
		//echo "$query<br>";

		$count=1;
		if(!isset($in['page'])) $in['page']=1;
		#unset($in['page']);
		if (isset($in['page'])){
			$query="select t.*, rownum as num_record  from ($query) t";
			$num_query="select count(*) as conto from ($query)";
			#echo "<hr>$num_query<hr>";
			#phpinfo();
			#echo "<hr>".getenv("NLS_LANG");
			$this->sql->set_sql($num_query);
			$this->sql->exec();//obsoleto trovare dove testare
			$this->sql->get_row();
			$nrows=$this->sql->row['CONTO'];
			#echo "<hr>$nrows - $num_query";
			$rpg=50;
			$page=$in['page'];
			$npages=ceil($nrows/$rpg);
			#echo "<hr>$nrows - $npages -".$nrows%$npages;
			#echo "<hr>$nrows - $npages";
			$first=($rpg*($page-1))+1;
			$last=$first+$rpg-1;
			$link_script="index.php";
			if ($in['scrip']!='') $link_script=$in['scrip'];
			foreach ($in as $key => $val){
				if($key!='page') $param.="$key=$val&";
			}
			$link_script.="?".$param;
			if ($last > $nrows) $last=$nrows;
			$listpages_top="
					<br>
					Numero pratiche totali:<b> $nrows</b><br>
					pratiche visualizzate dalla <b>$first</b> alla <b>$last</b><br>
					<b>Salta a pagina</b>(1 - $npages)<input type=\"text\" name=\"page\" size=3 id='page_id' value='$page'><input type='button' value='Vai' onclick=\"if (document.getElementById('page_id').value!='' && document.getElementById('page_id').value<=$npages && document.getElementById('page_id').value>=1) window.location.href='{$link_script}page='+document.getElementById('page_id').value; else alert('Attenzione!!!\\nNon esiste la pagina '+document.getElementById('page_id').value);\">
				";
			$listpages_bottom="
					<br>
					Numero pratiche totali:<b> $nrows</b><br>
					pratiche visualizzate dalla <b>$first</b> alla <b>$last</b><br>
					<b>Salta a pagina</b>(1 - $npages)<input type=\"text\" name=\"page\" size=3 id='page_id_b' value='$page'><input type='button' value='Vai' onclick=\"if (document.getElementById('page_id_b').value!='' && document.getElementById('page_id_b').value<='$npages' && document.getElementById('page_id_b').value>='1') window.location.href='{$link_script}page='+document.getElementById('page_id_b').value; else alert('Attenzione!!!\\nNon esiste la pagina '+document.getElementById('page_id_b').value);\">
				";
			if ($page!=1) {
				$first_page="<a href=\"{$link_script}page=1\">|&lt;</a>";
				$prev_page=$page-1;
				$prev="<a href=\"{$link_script}page=$prev_page\">&lt;</a>";
			}
			if ($page < $npages) {
				$last_page="<a href=\"{$link_script}page=$npages\">&gt;|</a>";
				$next_page=$page+1;
				$next="<a href=\"{$link_script}page=$next_page\">&gt;</a>";
			}
			$listpages="<p align=center>$first_page &nbsp; $prev &nbsp;";
			$begin=$page-10;
			if ($begin<=0) $begin=1;
			for ($i=$begin; $i<=$begin+20 && $i<=$npages &&$npages>1; $i++) {
				if ($i==$page) $listpages.="<b>$i</b>&nbsp;";
				else $listpages.="<a href=\"{$link_script}page=$i\">$i</a> &nbsp;";
			}
			$listpages.="$next &nbsp; $last_page</p>";
			if ($nrows<=$rpg) $listpages="";
		}
		else {
			$first=1;
			$last=$nrows;
		}
		$count=0;
		for ($i=0;$i<count($this->cols);$i++) if ($this->cols[$i]['TIPO']!='hidden') $count++;
		if (isset($in['page'])) {
			$query="select * from ($query) where num_record<=$last and num_record>=$first";
		}
		echo "<!--$query-->";
		$this->sql->set_sql($query);
		$this->sql->exec();//obsoleto trovare dove testare
		if (!isset($list)) $lista=$v_list;
		$tot=0;
		while ($this->sql->get_row()){
			if ($this->list['TOTALE']!='')
			$tot+=$this->sql->row[strtoupper($this->list['TOTALE'])];
			//if (!preg_match("/proc/", $this->nome_file) && !preg_match("/attach/", $this->nome_file)) $html.="<tr  height=\"2\"><td colspan=$count bgcolor='#B8CADD' height=\"2\"></td></tr>";
			//				echo "<br>Record: $count";
			$this->empty=false;
			#echo"$count - $first - $last<br>";
			$html.="<tr>";
			for ($i=0;$i<count($this->cols);$i++){
				$txt="";
				$function_to_call="col_td_".$this->cols[$i]['TIPO'];
				if (method_exists($this,$function_to_call)) $txt=$this->{$function_to_call}($i);

				if (isset($this->cols[$i]['SCRIPT']) && $this->cols[$i]['SCRIPT']!='') {
					$link=$this->col_script($i);
					$txt=$link.$txt."</a>";
				}
				if ($txt!='') {
					if ($this->cols[$i]['TIPO']!='testo') $html.="<td align=center class=\"sc4bis\">$txt</td>";
					else $html.="<td class=\"sc4bis\">$txt</td>" ;
				}
			}
			$html.="</tr>";
			if (isset($this->list['ATTACH']) && $this->list['ATTACH']!=''){
				$in[$this->list['PARAM']]=$this->sql->row[strtoupper($this->list['PARAM_VALUE'])];
				#echo "<hr> . settaggio - in[{$this->list['PARAM']}]={$in[$this->list['PARAM']]}";
				$attach_list=new xml_list($xml_dir."/".$this->list['ATTACH'], null, null, null, null, $this->session_vars );
				$tabella_attach=$attach_list->list_html();
				#echo "<hr>Attachment".$attach_list->list_html();
				$html.="
						<tbody id='attach_{$this->sql->row[strtoupper($this->list['PARAM_VALUE'])]}' style=\"display:\">
							$tabella_attach
						</tbody>";
			}

			$count++;
		}
		//		echo "<br>$tot";
		if ($this->list['TOTALE']!='')
		{
			$colsp=count($this->cols)-2;
			$html.="<tr><td <td class=\"sc4bis\" colspan=$colsp><b>Totale</b></td>
				 <td class=\"sc4bis\"><b>$tot</b></td>
				 <td class=\"sc4bis\"></td>
				 </tr>
				";
		}

		if ($this->list['ATTACHED']!='YES') $html.="</table>";
		if ($this->list['ATTACHED']=='YES') {
			$colspan=$cols-1;
			$link=$this->list['SCRIPT'];
			//	echo "<br>$link<br>";
			$params=$this->list['PARAM'];
			$params=explode(",",$params);
			if ($param=='') $param='?';
			for ($p=0;$p<count($params);$p++){
				if ($this->sql->row[strtoupper($params[$p])]!='') {
					$param.="&amp;".strtoupper($params[$p])."=".$this->sql->row[strtoupper($params[$p])];
				}
				else $param.="&amp;".$params[$p];
			}

			//$param=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $param);
			$param=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $param );
			$link.=$param;
			$query=new query($conn);
			$sql_select="select a.da as da, a2.in_carico as in_carico from at_forum a, at_forum a2 where a.id=(select max(a1.id) from at_forum a1 where id_ref='{$in['ID_REF']}' or id='{$in['ID_REF']}') and a2.id='{$in['ID_REF']}'";
			$query->set_sql($sql_select);
			$query->exec();//obsoleto trovare dove testare
			$query->get_row();
			$da=$query->row['DA'];
			$in_carico=$query->row['IN_CARICO'];
			$da=substr($da, 0, 2);
			global $_SERVER;
			#echo "<hr>$sql_select<hr>{$in['USER_TIP']} - {$in_carico} - {$_SERVER['PHP_AUTH_USER']}<hr>";
			if (($in['USER_TIP']=='UF' && $in_carico==strtoupper($_SERVER['PHP_AUTH_USER'])) || $in['USER_TIP']!='UF')
			if (!($in['USER_TIP']=='MS') && (($da!='' && $da!=$in['USER_TIP']) || ($da=='' && $in['USER_TIP']!='00'))) $html.="<tr><td class=sc4bis>&nbsp;</td><td colspan=$colspan class=sc4bis><a href=\"$link\">Rispondi al messaggio</a></td></tr>";
		}
		//			echo "<hr>$html<br>";
		if (isset($in[$this->PK_SERVICE])) {
			$param="{$this->PK_SERVICE}=".$in[$this->PK_SERVICE];
			$txt;
		}
		$param.="&amp;CENTER=".$in['CENTER'];
		if ($in['v_list']==''){
			if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Lista Pazienti</a></p>";
			#else if ($in['CENTER']!='') $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Lista Pazienti</a></p>";
		}
		//			echo "<hr>***$listpages***<br>";
		if ($listpages!='') return "
				<table border=0 width=95% align=center cellpadding=0 cellspacing=0>
					<tr>
						<td>$listpages_top $listpages</td>
					</tr>
				</table>$html
				<table border=0 width=95% align=center cellpadding=0 cellspacing=0>
					<tr>
						<td>$listpages $listpages_bottom</td>
					</tr>
				</table>
				";
		return $html;

	}
}

class legend{
	var $html_legend_visita;
	var $html_legend_lista;

	function legend(){
		global $in;
		$this->html_legend_visita="
 	<table border=\"0\" width=\"70%\" align=\"center\">
 <tr>
  <td width=\"8%\" class=\"titolo\" colspan=\"2\">Legenda</td>
 </tr>
        <TR>
          <TD class=\"inputdossier\" width=\"5%\"><IMG src=\"/images/to_be_comp.gif\" border=0> </TD>
          <TD class=\"inputdossier\" width=\"95%\">Scheda da compilare. Cliccare sul quadratino vuoto per compilare la scheda.</TD></TR>
        <TR>
          <TD class=\"inputdossier\"><IMG src=\"/images/saved.gif\" border=0> </TD>
          <TD class=\"inputdossier\">Scheda parzialmente compilata. Cliccare sul check rosso per completare o modificare i dati.</TD></TR>
        <TR>
          <TD class=\"inputdossier\"><IMG src=\"/images/submitted.gif\" border=0> </TD>
          <TD class=\"inputdossier\">Scheda completata e inviata. Non ? possibile modificarla. Cliccare sul check verde per visualizzare i dati inseriti</TD></TR>
        </TBODY>
</TABLE>
 	";
		$this->html_legend_lista="
 	<table border=\"0\" width=\"70%\" align=\"center\">
 <tr>
  <td width=\"8%\" class=\"titolo\" colspan=\"2\">Legenda</td>
 </tr>
 <tr>
  <td class=\"inputdossier\" width=\"5%\"><img src=\"/images/f_bianca.gif\" border=\"0\" ></td>
     <td class=\"inputdossier\" width=\"95%\">Schede da compilare. Cliccare sulla freccia bianca per iniziare l'inserimento</td>
 </tr>
 <tr>
  <td class=\"inputdossier\"><img src=\"/images/f_gialla.gif\" border=\"0\" ></td>
     <td class=\"inputdossier\">Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l'inserimento</td>
 </tr>
 <tr>
  <td class=\"inputdossier\"><img src=\"/images/f_verde.gif\" border=\"0\"></td>
     <td class=\"inputdossier\">Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti.</td>
 </tr>
 <tr>
  <td class=\"inputdossier\"><img src=\"/images/f_rossa.gif\" border=\"0\"></td>
     <td class=\"inputdossier\">Fine Studio</td>
 </tr>
 </table>";
		if ($in['USER_TIP']=='DM') $this->html_legend_visita="";
	}

}

class xml_esams_list{

	var $titolo;
	var $visitnums;
	var $esams;
	var $group;
	var $links;
	var $html;
	var $page;
	var $xml;
	var $PK_SERVICE;
	var $tabs;
	var $visit_menu;

	/**
	 * Costruttore
	 *
	 * @param string $xml_file
	 * @return xml_esams_list
	 */
	function xml_esams_list($xml_file){
		#echo "<hr>FILE: $xml_file";

		global $config_service;
		$this->PK_SERVICE=$config_service['PK_SERVICE'];
		$xml_parser=new my_xml_parser($xml_file);
		$this_node=new xml_node();
		$g=0;
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){
				if ($this_node->tag=='VISIT_EXAM') if ($this_node->type=='open' or $this_node->type=='complete') {
					$this->page=$this_node->attributes;
				}
				if ($this_node->tag=='GROUP') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->group[$g]=$this_node->attributes;
					}
					if ($this_node->type=='close') {
						$g++;
					}
				}

				if ($this_node->tag=='VISIT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$vis_num=$this_node->attributes['NUMBER']+0;
						$this->group[$g]['VISIT'][$vis_num]=$vis_num;
						$this->visitnums[$vis_num]=$this_node->attributes;
					}
				}
				if ($this_node->tag=='EXAM') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$es_num=$this_node->attributes['NUMBER']+0;
						$this->group[$g]['ESAM'][$es_num]=$es_num;
						$this->esams[$vis_num][$es_num]=$this_node->attributes;
						$this->xml[$es_num]=$this_node->attributes['XML'];
					}
				}
				if ($this_node->tag=='TEXT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->esams[$vis_num][$es_num]['TESTO']=$this_node->value;
					}
				}
				if ($this_node->tag=='CLOSE_ALL') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->esams['CLOSE_ALL']=$this_node->value;
					}
				}
			}
		}
		//print_r($this->esams);
	}

	/**
	 * Restituisce il codice xml dell'oggetto
	 *
	 * @return string
	 */
	function obj_to_xml(){
		$xml_str="<visit_exam>\n";
		#print_r($this->group);
		#print_r($this->visitnums);
		#print_r($this->esams);
		foreach ($this->group as $key => $val){
			$xml_str.="	<group text=\"{$val['TEXT']}\">\n";
			foreach ($val['VISIT'] as $key_v => $val_v) {
				$xml_str.="		<visit number=\"$val_v\" text=\"{$this->visitnums[$val_v]['TEXT']}\" short_txt=\"{$this->visitnums[$val_v]['SHORT_TXT']}\">\n";
				foreach ($this->esams[$val_v] as $es_num => $es_val){
					if (isset($es_val['PROGR'])) $progr="PROGR=\"{$es_val['PROGR']}\"";
					else $progr="";
					$xml_str.="			<exam number=\"{$es_num}\" xml=\"{$es_val['XML']}\" $progr >\n";
					$xml_str.="				<text>{$es_val['TESTO']}</text>\n";
					$xml_str.="			</exam>\n";
				}
				$xml_str.="		</visit>\n";
			}
			$xml_str.="	</group>\n";
		}
		$xml_str.="</visit_exam>";
		return $xml_str;
	}


	/**
	 * Costruisce i tab relativo alla form visualizzata
	 *
	 * @return string
	 */
	function esams_list_tab(){
		global $in;
		global $conn;
		global $xml_dir;
		global $config_service;
		$this->tab="
		<noscript>
		<font color='red'>Attenzione salvare i dati prima di cambiare form</font>
		</noscript>
		<ul id=\"globalnav\">";
		if ($config_service['PK_SERVICE']!='') $this->PK_SERVICE=$config_service['PK_SERVICE'];
		if ($config_service['VISITNUM_PROGR']=='1') {
			$add_vprogr="VISITNUM_PROGR,";
			$sql=new query($conn);
			$sql_select="select max(visitnum_progr) as maxvp from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'";
			$sql->set_sql($sql_select);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$max_vp=$sql->row['MAXVP'];
			foreach($this->visitnums as $visit => $vval){
				if ($vval['PROGR']=='yes') {
					$v_progr_esam_spec=$this->esams[$visit];
					unset($this->esams[$visit]);
					for ($i=0; $i<=$max_vp; $i++){
						$this->esams[$visit][$i]=$v_progr_esam_spec;
					}
				}
			}
		}
		if ($in[$this->PK_SERVICE]=='next') return;
		$query="select visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."' order by visitnum,$add_vprogr esam ,progr";
		//echo "<hr>$query<hr>";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		$this->visit_menu="<table  border=0><tr><th class=titolo><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;exams=visite_exams.xml\">Lista Schede</a></th></tr>";
		#print_r($this->visitnums);
		while ($sql->get_row()){
			if ($this->visitnums[$sql->row['VISITNUM']]['PROGR']=='yes') {
				if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED']=true;
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])){
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
				}
			}
			else {
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
					if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED']=true;
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
				}
			}
		}
		foreach ($this->visitnums as $key => $val) {
			if ($val['PROGR']=='yes'){
				foreach($this->esams[$key] as $vprogr => $vesam){

					$nro=$vprogr+1;
					if ($in['VISITNUM']==$key && $in['VISITNUM_PROGR']==$vprogr){
						if ($this->visitnums[$key][$vprogr]['ENABLED']) $this->visit_menu.="<tr><td class=int><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\"><font color=red>".$val['TEXT']." $nro</font></a></td></tr>";
						//$this->tab.="\n<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']." $nro</a>\n<ul>\n";
						$visit_enabled=false;
						foreach ($vesam as $esam => $es_val){
							if ($es_val)
							if ($in['VISITNUM']==$key)	$this->print_esams_tab($es_val,$key,$esam);
							else $this->print_esams_tab($es_val,$key,$esam,false);
						}
						//$this->tab.="</ul>";
					}
					else if ($this->visitnums[$key][$vprogr]['ENABLED']) {
						//$this->visit_menu.="<tr><td class=sc4bis><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']." $nro</a></td></tr>";
						$this->print_esams_tab($es_val,$key,$esam,false);
					}
					//else $this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']." $nro</a></li>\n";
					//echo "<hr>{$_GET['VISITNUM_PROGR']}<hr>";
				}
			}
			else {
				if ($in['VISITNUM']==$key){

					if ($this->visitnums[$key]['ENABLED']) $this->visit_menu.="<tr><td class=sc4bis><li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\"><font color=red>".$val['TEXT']."</font></a></li></td></tr>";
					//$this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']."</a></li>\n<ul>\n";
					foreach ($this->esams[$key] as $esam => $es_val){
						if ($in['VISITNUM']==$key)	$this->print_esams_tab($es_val,$key,$esam);
					}
					//$this->tab.="</ul>";
				}
				else {
					if ($this->visitnums[$key]['ENABLED']) $this->visit_menu.="<tr><td class=sc4bis><li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']."</a></li></td></tr>";
					foreach ($this->esams[$key] as $esam => $es_val){
						$this->print_esams_tab($es_val,$key,$esam,false);
					}
				}
				//else $this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']."</a></li>\n";
			}
		}
		$this->tab.="</ul><br><br><br>";
		global $config_service;
		global $tab_menu_list;
		$this->visit_menu.="
			<tr>
				<td class=titolo align=center><a href=\"index.php?list=patients_list.xml\">{$config_service['Patients_list']}</a></td>
			</tr>
			$tab_menu_list
		</table>";
		return $this->tab;
	}

	/**
	 * Restituisce il tab dell'esame $esam della visita $key
	 *
	 * @param array $es_val
	 * @param number $key
	 * @param number $esam
	 */
	function print_esams_tab($es_val, $key, $esam, $this_visit=true){
		global $in;
		global $config_service;
		global $conn;

		//echo "<hr>$key<hr>";
		$link="index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$key."&amp;ESAM={$esam}";
		//echo "<hr>$esam - <hr>";
		$enabled=false;


		if (isset($es_val['PROGR']) && $es_val['PROGR']=='yes' && $es_val['CONT_FORM']==''){
			if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach($es_val['RES'] as $res_key => $vals) {
				$es_progr=$res_key;
				$link.="&PROGR={$es_progr}";
				if ($vals['ABILITATO']=='1') $enabled=true;
				$sql2=new query($conn);
				if ($es_val['VAL_AGG']!='') {
					//echo "<hr>{$es_val['TESTO']}<hr>";
					$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and esam='$esam'";
					//echo "<hr>$query_data";
					$sql2->set_sql($query_data);
					$sql2->exec();//obsoleto trovare dove testare
					$sql2->get_row();
					$date=$sql2->row['VAL_AGG'];
					//echo $date;
				}
				$nome_esame=$es_val['TESTO']." $date";
				//echo "<hr>$nome_esame";
				if ($enabled){
					if (isset($in['ESAM']) && $in['ESAM']==$esam && $in['PROGR']==$es_progr) {
						if ($this_visit) $this->tab.="<li><a href=\"#\" class=\"here\" onclick=\"return false;\">{$nome_esame}</a></li>\n";
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$nome_esame}</font></a></li></td></tr>";
					}
					else {
						global $editing;
						if ($editing) {
							//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$nome_esame}</a></li></td></tr>";

							if ($this_visit) $this->tab.="<li><a href=\"$link\"
								onclick=\"
					window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
				\">{$nome_esame}</a></li>\n";
						}
						else {
							if ($this_visit) $this->tab.="<li><a href=\"$link\">{$es_val['TESTO']}</a></li>\n";
							//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$nome_esame}</a></li></td></tr>";
						}
					}
				}
			}
		}
		else{
			//print_r($es_val);
			if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach($es_val['RES'] as $res_key => $vals) {
				if ($vals['ABILITATO']=='1') $enabled=true;
			}
			if ($enabled){
				if (isset($in['ESAM']) && $in['ESAM']==$esam) {
					if ($this_visit) $this->tab.="<li><a href=\"#\" class=\"here\" onclick=\"return false;\">{$es_val['TESTO']}</a></li>\n";
					//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$es_val['TESTO']}</font></a></li></td></tr>";
				}
				else {
					global $editing;
					if ($editing) {
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$es_val['TESTO']}</a></li></td></tr>";
						if ($this_visit) $this->tab.="<li><a href=\"$link\"
								onclick=\"
					window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
				\">{$es_val['TESTO']}</a></li>\n";
					}
					else {
						if ($this_visit) $this->tab.="<li><a href=\"$link\">{$es_val['TESTO']}</a></li>\n";
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$es_val['TESTO']}</a></li></td></tr>";
					}
				}
			}
		}
	}

	/**
	 * Restituisce la lista delle form compilate e compilabili
	 *
	 * @return string
	 */
	function esams_list_html(){
		global $in;
		global $conn;
		global $xml_dir;
		global $config_service;
		$this->body.=patient_table();
		if ($in['USER_TIP']=='DM'){
			$sql_query="select min(stato) as stato, min(visitclose) as visitclose from checkin_coordinate where id_prat='{$in['ID_PRAT']}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$stato=$sql->row['STATO'];
			$visitclose=$sql->row['VISITCLOSE'];
			$sql_query="select prot_dt, prot from checkin_dettaglio where id_prat='{$in['ID_PRAT']}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$data_prot=explode(" ", $sql->row['PROT_DT']);
			//print_r($data_prot);
			if ($sql->row['PROT']!='')  $dati_prot_presenti=true;
			else $dati_prot_presenti=false;
			//echo "<hr>".$sql->row['PROT']."<hr>";
			//if ($dati_prot_presenti) echo "presenti";
			//else echo "Assenti";
			$data_prot=explode("/", $data_prot[0]);
			//print_r($data_prot);
			$day=$data_prot[0];
			$mon=$data_prot[1];
			$year=$data_prot[2];
			if (($stato==0 || $stato==3) && $visitclose==1){
				//echo "<li>{$sql->row['PROT_DT']}</li>";
				$data_prot=explode(" ", $sql->row['PROT_DT']);
				//print_r($data_prot);
				$data_prot=explode("/", $data_prot[0]);
				//print_r($data_prot);
				$day=$data_prot[0];
				$mon=$data_prot[1];
				$year=$data_prot[2];
				if (isset($in['PROT'])){
					$sql->row['PROT']=$in['PROT'];
					$day=$in['PROT_DTD'];
					$mon=$in['PROT_DTM'];
					$year=$in['PROT_DTY'];
					if (!checkdate($in['PROT_DTM'], $in['PROT_DTD'], $in['PROT_DTY']))
					$data_errata='<br><font color=\'red\'>Data non corretta</font>';
					//if (!is_numeric($in['PROT']))
					//$prot_errato='<br><font color=\'red\'>Numero protocollo errato</font>';
					if (checkdate($in['PROT_DTM'], $in['PROT_DTD'], $in['PROT_DTY']) && is_numeric($in['PROT'])){
						$dati_salvati="<tr><td colspan=2 class=input><font color='red'>Dati protocollo AIFA salvati con successo</font></td></tr>";
					}
				}
				$prot_num="<input type='text' name='PROT' value='{$sql->row['PROT']}'>";
				$prot_dt="
					<input type='text' name='PROT_DTD' value='$day' size=2>/
					<input type='text' name='PROT_DTM' value='$mon' size=2>/
					<input type='text' name='PROT_DTY' value='$year' size=4>
				";
				$buttons="<tr><td colspan=2 align=center><input type='submit' value='Salva dati protocollo AIFA'></td></tr>";
			}
			else {
				$prot_num="<b>{$sql->row['PROT']}</b>";
				$prot_dt="<b>$day/$mon/$year</b>";
				$buttons='';
			}
			$this->body.="
			<form method='post' action='index.php'>
				<input type='hidden' name='dati_prot' value='{$in['ID_PRAT']}'>
				<input type='hidden' name='CENTER' value='{$in['CENTER']}'>
				<table border=0 cellpadding=0 cellspacing=0 width=100%>
				<tr>
					<td colspan=2 class=titolo>
						Dati protocollo AIFA
					</td>
				</tr>
				$dati_salvati
				<tr>
					<td class=destra width=50%>
						Numero Protocollo: $prot_errato
					</td>
					<td class=input>
						$prot_num
					</td>
				</tr>
				<tr>
					<td class=destra>
						Data Protocollo: $data_errata
					</td>
					<td class=input>
						$prot_dt
					</td>
				</tr>
				$buttons
				</table></form><br>
			";
		}
		else {
			$sql_query="select min(stato) as stato, min(visitclose) as visitclose from checkin_coordinate where id_prat='{$in['ID_PRAT']}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$stato=$sql->row['STATO'];
			$sql_query="select prot_dt, prot from checkin_dettaglio where id_prat='{$in['ID_PRAT']}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$data_prot=explode(" ", $sql->row['PROT_DT']);

			if ($sql->row['PROT']!='')  $dati_prot_presenti=true;
			else $dati_prot_presenti=false;

			$data_prot=explode("/", $data_prot[0]);

			$day=$data_prot[0];
			$mon=$data_prot[1];
			$year=$data_prot[2];
			$prot_num="<b>{$sql->row['PROT']}</b>";
			$prot_dt="<b>$day/$mon/$year</b>";
			$buttons='';
			if ($dati_prot_presenti && $stato!=0) $this->body.="
			<form method='post' action='index.php'>
				<input type='hidden' name='dati_prot' value='{$in['ID_PRAT']}'>
				<input type='hidden' name='CENTER' value='{$in['CENTER']}'>
				<table border=0 cellpadding=0 cellspacing=0 width=100%>
				<tr>
					<td colspan=2 class=titolo>
						Dati protocollo AIFA
					</td>
				</tr>
				$dati_salvati
				<tr>
					<td class=destra width=50%>
						Numero Protocollo: $prot_errato
					</td>
					<td class=input>
						$prot_num
					</td>
				</tr>
				<tr>
					<td class=destra>
						Data Protocollo: $data_errata
					</td>
					<td class=input>
						$prot_dt
					</td>
				</tr>
				$buttons
				</table></form><br>
			";
		}
		if ($config_service['PK_SERVICE']=='') $config_service['PK_SERVICE']=$this->PK_SERVICE;
		if ($config_service['VISITNUM_PROGR']=='1') {
			$add_vprogr="VISITNUM_PROGR,";
			$sql=new query($conn);
			$sql_select="select max(visitnum_progr) as maxvp from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'";
			$sql->set_sql($sql_select);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$max_vp=$sql->row['MAXVP'];
			foreach($this->visitnums as $visit => $vval){
				if ($vval['PROGR']=='yes') {
					$v_progr_esam_spec=$this->esams[$visit];
					unset($this->esams[$visit]);
					for ($i=0; $i<=$max_vp; $i++){
						$this->esams[$visit][$i]=$v_progr_esam_spec;
					}
				}
			}
		}
		//if ($in['USER_TIP']=='DE')
		$query="select visitnum,$add_vprogr esam, progr, inizio, fine,validata, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."' order by visitnum,$add_vprogr esam ,progr";
		//else $query="select visitnum,$add_vprogr esam, progr, decode(validata,0,1,1,1,null,null) as inizio, validata as fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."' order by visitnum,$add_vprogr esam ,progr";
		//echo "<hr>$query<hr>";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		#print_r($this->visitnums);
		while ($sql->get_row()){
			if ($this->visitnums[$sql->row['VISITNUM']]['PROGR']=='yes') {
				if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED']=true;
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])){
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
				}
			}
			else {
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
					if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED']=true;
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
				}
			}
		}
		//print_r($this->esams);
		#print_r($this->esams);
		$this->tab="<ul id=\"globalnav\">";
		foreach ($this->visitnums as $key => $val) {
			$af_progr="";
			if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){


				if ($val['PROGR']=='yes') {
					//print_r($this->esams[$key]);
					if ($this->visitnums[$key][0]['ENABLED'])$this->body.="
		  		<table border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
						<tr>
							<td colspan=2>
								<ul id=\"globalnav\">
								<!--af_progr-->
								</ul>
							</td>
						</tr>

						";
					foreach($this->esams[$key] as $vprogr => $vesam) {
						if ($max_vprogr<$vprogr) $max_vprogr=$vprogr;
					}
					foreach($this->esams[$key] as $vprogr => $vesam){
						$nro=$vprogr+1;
						if ($this->visitnums[$key][$vprogr]['ENABLED']){

								/*$this->body.="
								<tr><td colspan=2 class=sc4bis>
								<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"98%\">
	        				<tr>
										<td colspan=2 class=\"int\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;VISITNUM_PROGR={$vprogr}&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']." n.ro $nro</a></td>
									</tr>
									<tr><td>";
									*/
									$param="";
									foreach($_GET as $gkey => $gval) if ($gkey!='VISITNUM_PROGR') $param.="$gkey=$gval&";
									if ($in['VISITNUM_PROGR']==$nro-1) {
										$display="";
										$class="class=\"here\"";
										//$this_af="<b>{$val['TEXT']} n.ro $nro</b>";
									}
									else {
										$display="none";
										$class="";
									}
									$onclick="";
									for ($i=0;$i<=$max_vprogr;$i++){
										$n_i=$i+1;
										if ($vprogr==$i)
											$onclick.="
											document.getElementById('af_{$n_i}').style.display='';
											document.getElementById('af_tab_{$n_i}').className='here';";
										else 	$onclick.="
											document.getElementById('af_{$n_i}').style.display='none';
											document.getElementById('af_tab_{$n_i}').className='';";
									}
									$onclick.="
									//document.getElementById('this_af').innerHTML='<b>{$val['TEXT']} n.ro $nro<b>';";
									$onclick.="
									return false;";

									//echo $onclick;
									$af_progr.="
										<li>
											<a id='af_tab_{$nro}' $class href=\"index.php?{$param}VISITNUM_PROGR=$vprogr\" onclick=\"$onclick\">{$val['SHORT_TXT']} n.ro $nro</a>
											</li>";
									$this->body.="<table id='af_{$nro}' style=\"display:{$display}\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        					<tr>
										<td colspan=2 align=\"center\" class=titolo width=100%>
											{$val['TEXT']} $nro
										</td>
									</tr>
									<tr>
										<td colspan=2 align=right class=sc4bis>
										<input type=\"button\" value=\"Clona {$val['TEXT']} $nro\"
											onclick=\"if (confirm('Attenzione!!!Sei sicuro di voler clonare questa {$val['TEXT']}')) window.location.href='index.php?clone_visit=yes&ID_PRAT={$in['ID_PRAT']}&VISITNUM={$key}&VISITNUM_PROGR=$vprogr';
											\"
										>
										&nbsp;
										<input type=\"button\" value=\"Elimina {$val['TEXT']} $nro\"
											onclick=\"if (confirm('Attenzione!!!Sei sicuro di voler eliminare questa {$val['TEXT']}')) window.location.href='index.php?del_visit=yes&ID_PRAT={$in['ID_PRAT']}&VISITNUM={$key}&VISITNUM_PROGR=$vprogr';
											\"
										>
										</td>
									</tr>
	        				";
								foreach ($vesam as $esam => $es_val){
									if ($vprogr==null) $vprogr="0";
									if ($es_val['RES'][1]['ABILITATO']=='1') $this->print_esams($es_val,$key,$esam, $vprogr);
								}
								$this->body.="<tr><td align=center class=sc4bis><img src=\"images/submitted.gif\"></td>
								<td class=sc4bis><a href=\"index.php?view_annex&VISITNUM_PROGR={$vprogr}&ID_PRAT={$in['ID_PRAT']}\">Annex Documents</a></td></tr>";
							$this->body.="</table>";
						}
					}
					$next_vprogr=$vprogr+1;
					$af_progr.="<li>
											<a href=\"index.php?CENTER={$in['CENTER']}&VISITNUM={$key}&ID_PRAT={$in['ID_PRAT']}&VISITNUM_PROGR={$next_vprogr}&CREATE_VPROGR=yes\" >Aggiungi</a>
											</li>";
					//$af_progr.="<ul><li id='this_af'>$this_af</li></ul>";
					$this->body=str_replace("<!--af_progr-->", $af_progr, $this->body);

				}
				else{
					if ($this->visitnums[$key]['ENABLED']){
						$this->body.="
		  		<table border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        	<tr>
							<td class=\"int\" colspan=2 align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']."</a></td>
				</tr>
						";

						foreach ($this->esams[$key] as $esam => $es_val){
							if ($es_val['RES'][1]['ABILITATO']=='1') $this->print_esams($es_val,$key,$esam);
						}
					}
				}
			}

			//echo "<hr>".$this->body."<hr>";
		}
		/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA*/
		/*if ($in['VISITNUM']!=''){
		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where ".$config_service['PK_SERVICE']."='".$in[$config_service['PK_SERVICE']]."' and VISITNUM='".$in['VISITNUM']."'";
		$sql->set_sql($query);
		$sql->exec();//commentata
		$sql->get_row();
		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
		<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
		<form method=post action='index.php' align=center>
		<input type='hidden' name='".$config_service['PK_SERVICE']."' value='".$in[$config_service['PK_SERVICE']]."'>
		<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
		<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
		<input type='hidden' name='exams' value='visite_exams.xml'>
		<!--input type='submit' name='close_visit' value='Close Visit' align=center-->
		</form>
		</td></tr></table>
		";
		}*/
		if ($this->body!='')	$this->body.="</table>";
		//print_r($this->esams);
		global $service;
		$sql_close="select min(visitclose) as closed from {$service}_coordinate where ID_PRAT='{$in['ID_PRAT']}'";
		$sql2=new query($conn);
		$sql2->set_sql($sql_close);
		$sql2->exec();//obsoleto trovare dove testare
		$sql2->get_row();
		if ($in['USER_TIP']=='DM'){
			$sql_query="select count(*) as conto from checkin_coordinate where ID_PRAT='{$in['ID_PRAT']}'";
			$sql=new query($conn);
			//echo "<hr>$sql_query<hr>";
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$tot_schede=$sql->row['CONTO'];
			$sql_query="select count(*) as conto from checkin_coordinate where ID_PRAT='{$in['ID_PRAT']}' and validata is not null";
			$sql=new query($conn);
			//echo "<hr>$sql_query<hr>";
			$sql->set_sql($sql_query);
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			$tot_schede_val=$sql->row['CONTO'];
			if ($tot_schede==$tot_schede_val){
				$sql_query="select min(validata) as validata, min(stato) as stato, min(visitclose) as visitclose from checkin_coordinate where ID_PRAT='{$in['ID_PRAT']}'";
				$sql=new query($conn);
				$sql->set_sql($sql_query);
				//echo "<hr>$sql_query<hr>";
				$sql->exec();//obsoleto trovare dove testare
				$sql->get_row();
				if ($sql->row['STATO']!='3' && $sql->row['VISITCLOSE']=='1' && $dati_prot_presenti){
					if ($sql->row['VALIDATA']=='1')
					$this->body.="
					<p align=center><input type='button' value='Valida la Pratica'  onclick=\"window.location.href='index.php?ID_PRAT={$in['ID_PRAT']}&CLOSE_DM_PRAT=yes&TO_UFF=yes'\"></p>
				";
					else $this->body.="
					<p align=center><input type='button' value=\"Invia richiesta di revisione all'azienda\" onclick=\"window.location.href='index.php?ID_PRAT={$in['ID_PRAT']}&CLOSE_DM_PRAT=yes&BACK_TO=yes'\"></p>
				";
				}
			}
		}
		if ($in['USER_TIP']=='DE'){
			//http://aifa-trasparenza.test.cineca.it/CKI/index.php?&make_appl_form=yes&ID_PRAT=22
			$this->body.="<p align=right>
				<a href=\"index.php?&make_appl_form=yes&ID_PRAT={$in['ID_PRAT']}\" target=\"_new\">Visualizza l'application form in formato html</a><br>
				<a href=\"index.php?&make_appl_form=yes&ID_PRAT={$in['ID_PRAT']}&pdf=make\" target=\"_new\">Visualizza l'application form in formato pdf</a>
			</p>";
		}
		if (isset($this->esams['CLOSE_ALL']) && $in['USER_TIP']=='DE' && $sql2->row['CLOSED']!='1')
		{
			$sql_query="select max(stato) as stato from checkin_coordinate where ID_PRAT='{$in['ID_PRAT']}'";
			//echo $sql_query;
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			//echo "<hr>$sql_query<hr>";
			$sql->exec();//obsoleto trovare dove testare
			$sql->get_row();
			if ($sql->row['STATO']=='2') {
				$sql_query="select min(fine) as fine from checkin_coordinate where ID_PRAT='{$in['ID_PRAT']}'";
				$sql=new query($conn);
				$sql->set_sql($sql_query);
				//echo "<hr>$sql_query<hr>";
				$sql->exec();//obsoleto trovare dove testare
				$sql->get_row();

				if ($sql->row['FINE']=='1')
				$this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
			Invia revisione
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\\'button\\' value=\\'Invia revisione\\' onclick=\"window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\'\">';
		</script>
		";
			}
			else $this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
			{$this->esams['CLOSE_ALL']}
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\\'button\\' value=\\'{$this->esams['CLOSE_ALL']}\\' onclick=\"window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\'\">';
		</script>
		";
		}
		$this->body.="<p align=right>";
		/*
		if ($in['USER_TIP']=='DE') $this->body.="
	  	<a href=\"index.php?list=patients_list.xml&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&CENTER=".$in['CENTER']."\">{$config_service['Menu_paziente']}</a><br>";
		*/
	  	$this->body.="
	  	<a href=\"index.php?exams=visite_exams.xml&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&CENTER=".$in['CENTER']."\">{$config_service['Lista_schede']}</a><br>";
		/*
	  	if ($in['USER_TIP']=='DE') $this->body.="
	  	<a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">{$config_service['Patients_list']}</a>";
	  	*/
		$this->body.="</p>";
		return $this->body;
	}

	/**
	 * Restituisce il codice html dell esame $esam della visita $key
	 *
	 * @param array $es_val
	 * @param number $key
	 * @param number $esam
	 */
	function print_esams($es_val, $key, $esam, $vprogr=null){
		//echo "<hr>$es_val, $key, $esam<hr>";
		if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
		else $agg_param="";
		global $in;
		global $conn;
		global $config_service;
		global $service;
		$nome_form=$es_val['TESTO'];
		//ESAMI NON PROGRESSIVO
		$sql_query="select min(stato) as stato from checkin_coordinate where id_prat='{$in['ID_PRAT']}'";
//		/echo $sql_query;
			$sql2=new query($conn);
			$sql2->set_sql($sql_query);
			$sql2->exec();//obsoleto trovare dove testare
			$sql2->get_row();
			//echo "<li>{$sql2->row['STATO']}</li>";
			if ($sql2->row['STATO']==4) $archiviata=true;
			else $archiviata=false;

		if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
			$img="to_be_comp.gif";
			$progr=1;
			if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
			#echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
			if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
			if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
			if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
			$date=$es_val['RES'][$progr]['INSERTDT'];
			$nome_esame=$es_val['TESTO'];
			$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
			$sql2=new query($conn);
			$sql2->set_sql($sql_query);
			$sql2->exec();//obsoleto trovare dove testare
			if ($sql2->numrows>0){
				$sql2->get_row();
				if ($in['USER_TIP']=='DE' && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
				//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
			}
			//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
			if ($in['USER_TIP']=='DM'  && !$archiviata ){
				if ($es_val['RES'][$progr]['VALIDATA']=='') $nome_esame.=" <font color=red>(Da validare)</font>";
				if ($es_val['RES'][$progr]['VALIDATA']=='1') $nome_esame.=" <font color=green>(Validata)</font>";
				if ($es_val['RES'][$progr]['VALIDATA']=='0') $nome_esame.=" <font color=red>(Richiesta revisione/non regolare)</font>";
			}
			if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
			//if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;equery=".$es_val['XML']."\">invia e-query";
			if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
				$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
				$close_href="</a>";
				$img_tag="<img src=\"/images/$img\" border=\"0\">";
				if ($in['USER_TIP']=='DM') $img_tag='';
				$this->body.="
									<tr>
										 <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$href}{$img_tag}{$close_href}
										</td>
										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame."$close_href<br/>
										</td>
										<!--td class=\"sc4bis\" align=\"center\">
										</td>
										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
										</td-->
										</tr>
										";
			}
		}
		//ESAMI PROGRESSIVI
		else {
			$last_progr=0;
			$form_alt='';
			//print_r($es_val);
			if (isset($es_val['RES']) && !isset($es_val['CORR'])){
				//print_r($es_val);
				if((isset($es_val['CONT_FORM']) && $es_val['CONT_FORM']=='yes') || isset($es_val['ALL_IN'])){
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						#	echo "<hr>$last_progr -  $es_progr";
						#print_r($es_val);
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							//print_r($es_val);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
								$sql2->exec();//obsoleto trovare dove testare
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							#print_r($this);
							if ($last_progr+1!=$es_progr)
							while ($last_progr<$es_progr-1){
								$last_progr++;
								$n_progr=$last_progr;
								$img="to_be_comp.gif";
								//												$form_alt=str_replace(".xml", "_alt.xml", $es_val['XML']);
								$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
								#echo "<hr>".$xml_dir.$form_alt;
								if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
								$nome_esame=$es_val['TESTO']." n. $n_progr";
								$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
								$sql2=new query($conn);
								$sql2->set_sql($sql_query);
								$sql2->exec();//obsoleto trovare dove testare
								if ($sql2->numrows>0){
									$sql2->get_row();
									if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
								}
								//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
								$close_href="</a>";
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($in['USER_TIP']=='DM') $img_tag='';
								//if ($in['USER_TIP']=='DM'  && !$archiviata ) $img_tag='';
								//echo "<hr>$key - $nome_esame";
								//echo "<hr> da aggiungere progressivo $n_progr";
								$this->body.="
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\"> - $href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}


							#echo "<hr>2 $es_progr - ";
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
							#$date="";
							#$date=$es_val['RES'][$es_progr]['INSERTDT'];


						}

						foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
							#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
							if ($es_val_corr['CORR']==$esam){
								# echo "<hr> Esame correlato per $esam : ".$esam_corr;
								$img="to_be_comp.gif";
								#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
								if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
								if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
								if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
								#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
								$dtp='';
								$query_data="select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val_corr['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
								$sql2->exec();//obsoleto trovare dove testare
								$sql2->get_row();
								$date=$sql2->row['DATA'];
								#echo "<hr>$date<hr>";
								$n_progr=$es_progr;
								if ($date!='') 	$dtp=" n.{$n_progr} ($date)";
								$nome_esame=$es_val_corr['TESTO']." $dtp";
								$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
								$sql2=new query($conn);
								$sql2->set_sql($sql_query);
								$sql2->exec();//obsoleto trovare dove testare
								if ($sql2->numrows>0){
									$sql2->get_row();
									if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
									//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
								}
								//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
								//if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val_corr['XML']."\">";
								$close_href="</a>";
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($in['USER_TIP']=='DM') $img_tag='';
								$this->body.="
										<tr>
											 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
											</td>
											<!--td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
											</td-->
											</tr>
											";
							}
						}
						#echo "<hr>ultimo progr $es_progr";
						$last_progr=$es_progr;
					}
					$n_progr=0;
					foreach ($es_val['RES'] as $keys => $val) {
						if ($val['INIZIO']=='1') $n_progr++;
					}
					if ($n_progr==0) {
						$img="to_be_comp.gif";
						$n_progr="Nuovo Inserimento";
					}
					$date=" (".$n_progr.") ".$date;
					$nome_esame=$es_val['TESTO']." $date";
					if ($progr!='') $sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
					else $sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and nvl(chiusa,0)<>1";
					//echo $sql_query;
					$sql2=new query($conn);
					$sql2->set_sql($sql_query);
					$sql2->exec();//obsoleto trovare dove testare
					if ($sql2->numrows>0){
						$sql2->get_row();
						//echo "<hr>sono qui<hr>";
						if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
						//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
					}
					//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
					$sql_query="select min(validata) as validata from checkin_coordinate where ID_PRAT={$in['ID_PRAT']} and ESAM=$esam and visitnum=$key";
					//echo $sql_query;
					$sql2=new query($conn);
					$sql2->set_sql($sql_query);
					$sql2->exec();//obsoleto trovare dove testare
					$sql2->get_row();
					$es_val['RES'][$es_progr]['VALIDATA']=$sql2->row['VALIDATA'];
					//echo
					//if ($sql2->row['VALIDATA']=='0')
					if ($in['USER_TIP']=='DM' && !$archiviata){
						if ($es_val['RES'][$es_progr]['VALIDATA']=='') $nome_esame.=" <font color=red>(Da validare)</font>";
						if ($es_val['RES'][$es_progr]['VALIDATA']=='1') $nome_esame.=" <font color=green>(Validata)</font>";
						if ($es_val['RES'][$es_progr]['VALIDATA']=='0') $nome_esame.=" <font color=red>(Richiesta revisione/non regolare)</font>";
					}
					//	}
					//					/echo "<hr>$nome_esame - $date";
					//if ($es_val['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;equery=".$es_val['XML']."\">invia e-query";
					if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";

						$close_href="</a>";
						$img_tag="<img src=\"/images/$img\" border=\"0\">";
						if ($in['USER_TIP']=='DM') $img_tag='';
						$this->body.="
													<tr>
														 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
														</td>
														<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
														</td>
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
														</td-->
													</tr>
												";
					}
				}
				else{
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						#	echo "<hr>$last_progr -  $es_progr";
						#print_r($es_val);
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							#print_r($es_val);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
								$sql2->exec();//obsoleto trovare dove testare
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							if ($es_val['VAL_AGG']!='') {
								//print_r($es_progr);
								$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and esam='$esam'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
								$sql2->exec();//obsoleto trovare dove testare
								$sql2->get_row();
								$date=$sql2->row['VAL_AGG'];
							}
							#print_r($this);
							if ($last_progr+1!=$es_progr)
							while ($last_progr<$es_progr-1){
								$last_progr++;
								$n_progr=$last_progr;
								$img="to_be_comp.gif";
								//												$form_alt=str_replace(".xml", "_alt.xml", $es_val['XML']);
								$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
								//echo "<hr>".$xml_dir.$form_alt;
								if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
								$nome_esame=$es_val['TESTO']." n. $n_progr";
								if ($progr!=''){
									$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr";
									$sql2=new query($conn);
									$sql2->set_sql($sql_query);
									$sql2->exec();//obsoleto trovare dove testare
									if ($sql2->numrows>0){
										$sql2->get_row();
										if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
										//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
									}
								}
								//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
								$close_href="</a>";
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($in['USER_TIP']=='DM') $img_tag='';
								//echo "<hr> da aggiungere progressivo $n_progr";
								$this->body.="
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							#echo "<hr>2 $es_progr - ";
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
							#$date="";
							#$date=$es_val['RES'][$es_progr]['INSERTDT'];
							$n_progr=$es_progr;
							if (isset($es_val['VAL_AGG'])) $nome_esame="{$es_val['TESTO']} {$date}";
							else {
								if ($date!='') $date=" n.{$n_progr} ($date)";
								$nome_esame=$es_val['TESTO']." $date";
							}
							#echo "<hr>{$es_val['TESTO']} - $date";
							//if ($es_val['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;equery=".$es_val['XML']."\">invia e-query";
							if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
								if ($es_progr!=''){
									$sql_query="select min(nvl(chiusa,0)) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$es_progr and validata=0";
									//echo "<hr>$sql_query<hr>";
									$sql2=new query($conn);
									$sql2->set_sql($sql_query);
									$sql2->exec();//obsoleto trovare dove testare
									if ($sql2->numrows>0){
										$sql2->get_row();
										if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
										//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
									}
								}

								//echo "<li>$nome_esame $esam - {$es_val['RES'][$es_progr]['VALIDATA']}</li>";
								if ($in['USER_TIP']=='DM' && !$archiviata ){
									if ($es_val['RES'][$es_progr]['VALIDATA']=='') $nome_esame.=" <font color=red>(Da validare)</font>";
									if ($es_val['RES'][$es_progr]['VALIDATA']=='1') $nome_esame.=" <font color=green>(Validata)</font>";
									if ($es_val['RES'][$es_progr]['VALIDATA']=='0') $nome_esame.=" <font color=red>(Richiesta revisione/non regolare)</font>";
								}
								//echo "<li>$nome_esame</li>";
								$close_href="</a>";
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($in['USER_TIP']=='DM') $img_tag='';
								$this->body.="
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}

							foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
								#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
								if ($es_val_corr['CORR']==$esam){
									# echo "<hr> Esame correlato per $esam : ".$esam_corr;
									$img="to_be_comp.gif";
									#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
									if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
									if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
									#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
									$dtp='';
									$query_data="select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val_corr['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
									#echo "<hr>$query_data";
									$sql2->set_sql($query_data);
									$sql2->exec();//obsoleto trovare dove testare
									$sql2->get_row();
									$date=$sql2->row['DATA'];
									//echo "<hr>$date<hr>";
									$n_progr=$es_progr;
									if ($date!='') 	$dtp=" n.{$n_progr} ($date)";
									$nome_esame=$es_val_corr['TESTO']." $dtp";
									if ($progr!=''){
										$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where id_prat={$in['ID_PRAT']} and visitnum=$key and esam=$esam and progr=$progr";
										$sql2=new query($conn);
										$sql2->set_sql($sql_query);
										$sql2->exec();//obsoleto trovare dove testare
										if ($sql2->numrows>0){
											$sql2->get_row();
											if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
											//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare/non regolare)</font>";
										}
									}
									//if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val_corr['XML']."\">";
									$close_href="</a>";
									$this->body.="
										<tr>
											 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
											</td>
											<!--td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
											</td-->
											</tr>
											";
								}
							}
							#echo "<hr>ultimo progr $es_progr";
							$last_progr=$es_progr;
						}

					}
				}
				//echo "<li>$key - $esam - ";
				//print_r($es_val);
				//echo "</li>";
				//print_r($this->esams[$key][$esam]['NEXT_ENABLED']);
				if (($es_val['RES'][$es_progr]['FINE']==1 || $es_val['RES'][$es_progr]['INIZIO']=='' || $es_val['NEXT_ENABLED']!='') && !isset($es_val['ALL_IN'])){
					//print_r($es_val);
					if ($es_val['RES'][$es_progr]['INIZIO']!='') $next_progr=$es_progr+1;
					else $next_progr=$es_progr;
					$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."\">";
					$close_href="</a>";
					if (!isset($form_alt) || $form_alt=='') $form_alt=$es_val['XML'];
					if ($es_val['CONT_FORM']!='yes' && $es_val['DISABLE_NEW']=='')$this->body.="
													<tr>
														<td class=\"sc4bis\" width=\"10%\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$form_alt."\">Nuovo inserimento: ".$es_val['TESTO']."</a><br/>
														</td>
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
														</td-->
													</tr>
											";
				}
			}
		}
	}


	/**
	 * Vista alternativa di visualizzazione delle form
	 *
	 * @return string
	 */
	function esams_list_html_view(){
		global $in;
		global $conn;
		global $es_form;
		global $xml_dir;
		$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}='".$in[$this->PK_SERVICE]."' order by visitnum,progr";
		//	  	echo "<hr>$query<hr>";
		//		echo $in[$this->PK_SERVICE]."<hr>";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		$esams_html="";
		while ($sql->get_row()){
			if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
			}
		}
		//	  	print_r($this->esams);
		foreach ($this->visitnums as $key => $val) {
			if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
				$this->body.="
		  		<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"95%\">
	        	<!--<tr>
							<td class=\"int\" align=\"left\"><b>".$val['TEXT']."</b></td>
						</tr>
						</table>
						<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">-->
					      <!--tr>
					      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
					      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
					     </tr-->
						";
				foreach ($this->esams[$key] as $esam => $es_val){
					$nome_form=$es_val['TESTO'];
					//ESAMI NON PROGRESSIVO
					if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
						$img="to_be_comp.gif";
						$progr=1;
						if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
						#echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
						if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
						if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
						if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
						$date=$es_val['RES'][$progr]['INSERTDT'];
						$nome_esame=$es_val['TESTO'];
						if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
						#if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;equery=".$es_val['XML']."\">invia e-query";
						if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
							#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;form=".$es_val['XML']."\">";
							#$close_href="</a>";
							//										$this->body.="
							//									<tr>
							//										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
							//										</td>
							//										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame."$close_href<br/>
							//										</td>
							//										<!--td class=\"sc4bis\" align=\"center\">
							//										</td>
							//										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
							//										</td-->
							//										</tr>
							//										";
							$in['VISITNUM']=$key;
							$in['ESAM']=$esam;
							$in['PROGR']=$progr;
							//										$in['CENTER']=$progr;
							$xml_form=new xml_form();
							//echo "$key -- $esam --{$es_form[$key][$esam]}<hr>";
							$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
							if ($xml_form->closed_form()) {
								$xml_form->close_form();
								$esam_html.="".$xml_form->body;
								$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
								$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
							}
							unset($in['VISITNUM']);

						}
					}
					//ESAMI PROGRESSIVI
					else {
						if (isset($es_val['RES']) && !isset($es_val['CORR'])){
							foreach ($es_val['RES'] as $es_progr => $progr_vals){
								//										echo "<hr>$es_progr - ";
								#print_r($es_val);
								if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
									#echo "<hr>2 $es_progr - ";
									if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
									if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
									$date="";
									$date=$es_val['RES'][$es_progr]['INSERTDT'];
									if ($date!='') $date="($date)";
									$nome_esame=$es_val['TESTO']." $date";
									#echo "<hr>{$es_val['TESTO']} - $date";
									#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val['XML']."\">invia e-query";
									if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
										#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
										#$close_href="</a>";
										//														$this->body.="
										//															<tr>
										//																 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
										//																</td>
										//																<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
										//																</td>
										//																<!--td class=\"sc4bis\" align=\"center\">
										//																</td>
										//																<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
										//																</td-->
										//															</tr>
										//														";
										$in['VISITNUM']=$key;
										$in['ESAM']=$esam;
										$in['PROGR']=$es_progr;
										$xml_form=new xml_form();
										$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
										if ($xml_form->closed_form()) {
											$xml_form->close_form();
											$esam_html.="".$xml_form->body;
											$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
											$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
										}
										unset($in['VISITNUM']);
										unset($in['ESAM']);
										unset($in['PROGR']);
									}
									foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
										#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
										if ($es_val_corr['CORR']==$esam){
											#echo "<hr> Esame correlato per $esam : ".$esam_corr;
											$img="to_be_comp.gif";
											//											print_r($es_val_corr);
											#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
											if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
											if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
											if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
											#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
											$dtp='';
											$date="";
											$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
											#echo "<hr>$date<hr>";
											if ($date!='') 	$dtp="($date)";
											$nome_esame=$es_val_corr['TESTO']." $dtp";
											#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val_corr['XML']."\">invia e-query";
											#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
											#$close_href="</a>";
											//										$this->body.="
											//									<tr>
											//										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											//										</td>
											//										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
											//										</td>
											//										<!--td class=\"sc4bis\" align=\"center\">
											//										</td>
											//										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
											//										</td-->
											//										</tr>
											//										";
											$in['VISITNUM']=$key;
											$in['ESAM']=$esam_corr;
											$in['PROGR']=$es_progr;
											$xml_form=new xml_form();
											$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam_corr]);
											if ($xml_form->closed_form()) {
												$xml_form->close_form();
												$esam_html.="".$xml_form->body;
												$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
												$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
											}
											unset($in['VISITNUM']);
											unset($in['ESAM']);
											unset($in['PROGR']);
										}
									}
								}

							}

						}
					}
				}
			}
			$this->body.="</table>";
		}
		/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA
		if ($in['VISITNUM']!=''){
		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}='".$in[$this->PK_SERVICE]."' and VISITNUM='".$in['VISITNUM']."'";
		$sql->set_sql($query);
		$sql->exec();//commentata
		$sql->get_row();
		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
		<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
		<form method=post action='index.php' align=center>
		<input type='hidden' name=$this->PK_SERVICE value='".$in[$this->PK_SERVICE]."'>
		<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
		<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
		<input type='hidden' name='exams' value='visite_exams.xml'>
		<input type='submit' name='close_visit' value='Close Visit' align=center>
		</form>
		</td></tr></table>
		";
		}*/
		/*$this->body.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Vista individuale</a>
		<br/><a href=\"index.php?exams=visite_exams.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Individual Patient Exam List</a>
		<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Procuratori registrati </a></p>";
		*/
		$this->body.=$esam_html;

		return $this->body;
	}

	/**
	 * Restituisce il codice html delle form raggrupate
	 *
	 * @return string
	 */
	function esams_group_html(){
		global $in;
		global $conn;
		$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}='".$in[$this->PK_SERVICE]."' order by progr";
		#echo $query;
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//obsoleto trovare dove testare
		while ($sql->get_row()){
			if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
			}
		}
		#print_r
		foreach ($this->group[$in['GROUP']]['VISIT'] as $grp => $val_grp){
			#echo "<hr>$grp<hr>";
			$in['VISITNUM']=$grp;
			foreach ($this->visitnums as $key => $val) {
				if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
					$this->body.="
			  		<table class=\"bordi\" border=\"0\" bordercolor=\"#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"100%\">
		        	<tr>
								<td class=\"int\" align=\"left\"><a href=\"index.php?{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=".$val['NUMBER']."&exams=".$GLOBALS['visit_structure_xml']."\" class=\"sc2b\">".$val['TEXT']."</a></td>
							</tr>
							</table>
							<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">
						      <!--tr>
						      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
						     </tr-->
							";
					foreach ($this->esams[$key] as $esam => $es_val){
						$nome_form=$es_val['TESTO'];
						//ESAMI NON PROGRESSIVO
						if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
							$img="to_be_comp.gif";
							$progr=1;
							if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
							#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
							if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
							$date=$es_val['RES'][$progr]['INSERTDT'];
							if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$progr&amp;form=".$es_val['XML']."\">";
								$close_href="</a>";
								$this->body.="
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$es_val['TESTO']."$close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
							}
						}
						//ESAMI PROGRESSIVI
						else {
							if (isset($es_val['RES']) && !isset($es_val['CORR'])){
								foreach ($es_val['RES'] as $es_progr => $progr_vals){
									#echo "<hr>$es_progr - ";
									#print_r($progr_vals);
									if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
										#echo "<hr>2 $es_progr - ";
										if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
										if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
										if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
										$date=$es_val['RES'][$es_progr]['INSERTDT'];
										$nome_form=$es_val['TESTO']." ($date)";
										if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
											$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
											$close_href="</a>";
											$this->body.="
																<tr>
																	 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$es_val['TESTO']."($date) $close_href<br/>
																	</td>
																	<td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
																	</td>
																</tr>
															";

										}

										foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
											#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
											if ($es_val_corr['CORR']==$esam){
												# echo "<hr> Esame correlato per $esam : ".$esam_corr;
												$img="to_be_comp.gif";
												#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
												if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
												if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
												if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
												#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
												$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
												$close_href="</a>";
												$this->body.="
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$es_val_corr['TESTO']."($date) $close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
											}
										}
									}

								}
								$next_progr=$es_progr+1;
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=".$es_val['XML']."\">";
								$close_href="</a>";
								$this->body.="
													<tr>
														<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\">New ".$es_val['TESTO']."</a><br/>
														</td>
														<td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
														</td>
													</tr>
											";
							}
						}
					}
				}
			}
		}
		$this->body.="</table><p align=right><a href=\"index.php?list=patients_list.xml&{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Menu Procuratore</a>
	  	<br/><a href=\"index.php?exams=".$GLOBALS['visit_structure_xml']."&{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Vista individuale</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Lista Procure</a></p>";
		return $this->body;
	}

}

function var_glob($value, $session_vars=null){
	global $in;
	global $inputval;
	
	#global $vis_name;
	//echo "<hr>{$in['ID_PRAT']}<hr>";

	if (isset($session_vars) && $session_vars[$value]!='') return $session_vars[$value];
	if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
	if (isset($in[$value]) && $in[$value]!='') return $in[$value];
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
}
