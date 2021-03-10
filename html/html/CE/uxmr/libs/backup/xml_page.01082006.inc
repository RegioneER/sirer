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
                    if ($this_node->tag=='vlist') if ($this_node->type=='open' or $this_node->type=='complete') {
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
	  	$filter=$this->blocco[$i]['FILTER'];
	  	#echo $filter;
	  	$filter=explode(",",$filter);
	  	for ($f=0;$f<count($filter);$f++){
	  		if ($in[$filter[$f]]!='') $where.=" and ".$filter[$f]."='".$in[$filter[$f]]."'";
	  	}
	  	if ($this->blocco[$i]['DECODE']!='') {
	  		$query="select distinct ".$this->blocco[$i]['DECODE']." as decode, ".$this->blocco[$i]['VALUE']." as value from ".$this->blocco[$i]['TABLE']." where ".$this->blocco[$i]['VALUE']." is not null $where order by ".$this->blocco[$i]['VALUE']."";
		  	$sql=new query($conn);
		  	$sql->set_sql($query);
		  	#echo "<hr> $query<hr>";
		  	$sql->exec();
		  	while ($sql->get_row()){
		  		#echo $sql->row['DECODE']." - ".$sql->row['VALUE']."<hr>";
		  		$in[$sql->row['DECODE']]=$sql->row['VALUE'];
		  		$this->body.="<br><br>
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tbody>
	        <tr>
	         <td class=\"int\" align=center>".$sql->row['DECODE']." - ".$sql->row['VALUE']."</td>
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
	  		$this->body.="
		  		<table border=\"0\" width=\"95%\" align=center>
	        <tr>
	         <td class=\"int\">".$this->blocco[$i]['TESTO']."</td>
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
	  	$list_o= new xml_list($xml_dir.'/'.$value);
	  	global $in;
	  	$lista=$list_o->list_html();
	  	if (!$list_o->empty) $this->body.=$lista;
	  }

	  function call_attach_vlist($value){
	  	global $xml_dir;
	  	#echo "<hr>call_attach_vlist($value)";
	  	$v_list_o= new xml_vlist($xml_dir.'/'.$value);
	  	#echo "<hr>OK<hr>";
	  	global $in;
	  	$lista=$v_list_o->vlist_html();
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

	  function xml_page($xml_file){
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

      function page_html(){
        for ($i=0;$i<count($this->blocco);$i++) $this->body.=$this->blocco_html($i);
        return $this->body;
      }

	  function blocco_html($i){
		  $html="<br>
		  				<TABLE cellSpacing=2 cellPadding=2 width=\"95%\" align=center border=0>
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

	  function xml_list($xml_file){
	  	$xml_parser=new my_xml_parser($xml_file);
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
	  	global $in;
	  	$txt=$this->cols[$i]['TESTO'];
	  	if ($this->cols[$i]['ORD_ARROW']!='') {
	  		$img_down="/images/down_arrow.gif";
	  		if ($in['ORD_TYPE']=='ASC' && $in['ORD']==$this->cols[$i]['NOME']) $img_down="/images/down_arrow_red.gif";
	  		$img_up="/images/up_arrow.gif";
	  		if ($in['ORD_TYPE']=='DESC' && $in['ORD']==$this->cols[$i]['NOME']) $img_up="/images/up_arrow_red.gif";
	  		if ($in['CENTER']!='') $center="CENTER={$in['CENTER']}";
	  		$txt.="
	  		<br><a href=\"index.php?list={$in['list']}&$center&ORD={$this->cols[$i]['NOME']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  		<a href=\"index.php?list={$in['list']}&$center&ORD={$this->cols[$i]['NOME']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
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

	  function col_td_status($i){

	  	$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
	  	$value=explode(" - ", $value);
	  	#echo "<hr>$value[0] . $value[1] . $value[2]<hr>";
	  	if ($value[1]==1){
	  		if ($value[0]==0) $txt="<b>Not Elegible for";
	  		else $txt="<b><a href=\"index.php?CENTER=".$this->sql->row['CENTER']."&CODPAT=".$this->sql->row['CODPAT']."&PROTOCOL=".$this->sql->row['PROTOCOL']."\">Enrolled in";
	  	}
	  	if ($value[1]=='')$txt="<b>On Screening";
	  	if ($value[1]=='0')$txt="<b><a href=\"index.php?CENTER=".$this->sql->row['CENTER']."&CODPAT=".$this->sql->row['CODPAT']."&VISITNUM=2&PROGR=2&ESAM=2&PROTOCOL=".$this->sql->row['PROTOCOL']."\">Verify Eligibility for";
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
                            $param="?exams=".$this->cols[$i]['EXAMS'];
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
	  	$param=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $param);
	  	$link.=$param;
	  	return "<a href=\"$link\" $target>";
	  }

	  function col_td_testo($i){
	  	$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
	  	$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
	  	return $value."&nbsp;";
	  }
	  
	  function col_td_validation($i){
	  	$value=$this->sql->row[strtoupper($this->cols[$i]['NOME'])];
	  	$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
	  	if ($this->sql->row['TO_BE_VALIDATE']=='1' && $value=='') {
				return "<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$this->sql->row['CODPAT']."&amp;VISITNUM=".$this->sql->row['VISITNUM']."&amp;ESAM=".$this->sql->row['ESAM']."&amp;PROGR=".$this->sql->row['PROGR']."&amp;equery_view=view&ID=".$this->sql->row['ID']."\">Validate the form</a>";
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

	  function list_html(){
         # echo "<hr>list_html<hr>";
	  	global $remote_userid;
	  	global $in;
	  	global $conn;
	  	global $xml_dir;
	  	$this->sql=new query($conn);
		  #print_r($this->cols);
		  $html="<table border=\"0\" id=\"table1\" width=\"95%\" align=center><tr>";
			for ($i=0;$i<count($this->cols);$i++){
				if ($this->cols[$i]['GROUP_BY']!=''){
					if (!isset($group_by)) $group_by=$this->cols[$i]['VAR'];
					else $group_by.=",".$this->cols[$i]['VAR'];
				}
				if ($this->cols[$i]['ORDER_BY']!=''){
					#echo "<hr>Trovato ORDER_BY";
					if (!isset($order_by)) $order_by=$this->cols[$i]['VAR'];
					else $order_by.=",".$this->cols[$i]['VAR'];
					#echo "$order_by<hr>";
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
						#echo "<hr>$key ".$val['TEXT'];
						$in_sql='';
						foreach ($val['VISIT'] as $vis => $visval){
							if ($in_sql!='') $in_sql.=",";
							$in_sql.="'$vis'";
						}
						if (!isset($fields)) $fields="(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum in ($in_sql) and ".$GLOBALS['patients_table'].".codpat=".$GLOBALS['service']."_COORDINATE.codpat) as v".$key;
						else $fields.=",(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum in ($in_sql) and ".$GLOBALS['patients_table'].".codpat=".$GLOBALS['service']."_COORDINATE.codpat) as v".$key;
					}
				}
				if ($this->cols[$i]['TIPO']=='visite'){
					$visit=new xml_esams_list($xml_dir.'/'.$GLOBALS['visit_structure_xml']);
					foreach ($visit->visitnums as $key => $val)
						if (!isset($fields)) $fields="(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum='".$key."' and ".$GLOBALS['patients_table'].".codpat=".$GLOBALS['service']."_COORDINATE.codpat) as v".$key;
						else $fields.=",(select max(inizio)||' - '||max(fine)||' - '||min(visitclose)||' - '||max(abilitato) from ".$GLOBALS['service']."_COORDINATE where ".$GLOBALS['service']."_COORDINATE.visitnum='".$key."' and ".$GLOBALS['patients_table'].".codpat=".$GLOBALS['service']."_COORDINATE.codpat) as v".$key;
				}
				$this->cols[$i]['TABLE']=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $this->cols[$i]['TABLE']);
				if (!preg_match("/".$this->cols[$i]['TABLE']."/i", $tables)) {
						if ($tables!='') $tables.=",";
						$tables.=$this->cols[$i]['TABLE'];
						#echo "<hr>".$this->cols[$i]['TABLE'];
				}
				$function_to_call="col_th_".$this->cols[$i]['TIPO'];
				if (method_exists($this,$function_to_call)) $html.=$this->{$function_to_call}($i);
//				foreach ($in as $key => $val){
//					if ($key==strtoupper($this->cols[$i]['NOME'])) {
//						if ($where!='') $where.=" and ";
//						$where.=$this->cols[$i]['VAR']."='$val' ";
//					}
//				}
				$nome=$this->cols[$i]['NOME'];
				if (var_glob($nome)!='') {
					if ($where!='') $where.=" and ";
						$where.=$this->cols[$i]['VAR']."='".var_glob($nome)."' ";
				}
			}
			#echo "<hr>$fields<hr>";
			$html.="</tr>";
			#echo "<hr>$where<hr>";
			$query="select $fields from $tables";
			
			//PARTE RELATIVA ALLA RICERCA//
			foreach ($in as $key => $val){
				if (preg_match("/^S_/", $key)) {
					$key=preg_replace("/^S_/", "", $key);
						if (preg_match("/^FROM_DT_/", $key)) {
						#if ($GLOBALS['debug']==1) echo "<hr>$key - $val";
							$key=preg_replace("/^FROM_DT_/", "", $key);
							$trovato=false;
							#echo "<hr>$key - $val";
							for ($i=0;$i<count($this->cols); $i++){
									if ($this->cols[$i]['NOME']==$key) $trovato=true;
							}
							if ($trovato){
								$val_to=$in['S_TO_DT_'.$key];
							if ($val!='' and $val_to!=''){
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
							if ($where != '') $where.=" and ";
							if ($val=='null') $where.=" $key is null";
							else $where.="UPPER($key) like '%".strtoupper($val)."%'";			
						}							
					}
				}
			}
			///////////////////////////////
			if ($where!='') $query.=" where $where";
			if ($group_by!='') $query.=" group by $group_by";
			if ($in['ORD']!='') $query.=" order by $order_by ";
			else if ($order_by!='') $query.=" order by $order_by desc";
			$query=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $query);
			#echo "<hr>$query<hr>";
			
			$this->sql->set_sql($query);
			$this->sql->exec();
			while ($this->sql->get_row()){
				$this->empty=false;
				$html.="<tr>";
				for ($i=0;$i<count($this->cols);$i++){
					$txt="";
					$function_to_call="col_td_".$this->cols[$i]['TIPO'];
					if (method_exists($this,$function_to_call)) $txt=$this->{$function_to_call}($i);
					if ($this->cols[$i]['SCRIPT']!='') {
					$link=$this->col_script($i);
					$txt=$link.$txt."</a>";
				}
				if ($txt!='') $html.="<td class=\"sc4bis\">$txt</td>" ;
			}
				$html.="</tr>";
			}
			$html.="</table>";
			if (isset($in['CODPAT'])) {
				$param="CODPAT=".$in['CODPAT'];
				$txt;
			}
			$param.="&amp;CENTER=".$in['CENTER'];
			if ($in['v_list']==''){
				if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Patients list visit</a></p>";
				#else if ($in['CENTER']!='') $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Patients list group</a></p>";
			}
			return $html;

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

  function xml_esams_list($xml_file){
	  	#echo "<hr>FILE: $xml_file";
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
                }
        }
        #print_r($this->visitnums);
        #echo "<hr>xml_esams_list<br/>";
	  }
	  
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

	function esams_list_html(){
	  	global $in;
	  	global $conn;
	  	$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where codpat='".$in['CODPAT']."' order by progr";
	  	#echo "<hr>$query<hr>";
	  	$sql=new query($conn);
	  	$sql->set_sql($query);
	  	$sql->exec();
	  	while ($sql->get_row()){
	  		if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
		  	}
	  	}
	  	#print_r($this->esams);
	  	foreach ($this->visitnums as $key => $val) {
	  		if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
		  		$this->body.="
		  		<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"95%\">
	        	<tr>
							<td class=\"int\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&CODPAT=".$in['CODPAT']."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=".$GLOBALS['visit_structure_xml']."\" class=\"sc2b\">".$val['TEXT']."</a></td>
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
								$progr=0;
								if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
								#echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
									if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
									if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
									$date=$es_val['RES'][$progr]['INSERTDT'];
									$nome_esame=$es_val['TESTO'];
									if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
									#if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;equery=".$es_val['XML']."\">send e-query";
									if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;form=".$es_val['XML']."\">";
										$close_href="</a>";
										$this->body.="
									<tr>
										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
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
								if (isset($es_val['RES']) && !isset($es_val['CORR'])){
									foreach ($es_val['RES'] as $es_progr => $progr_vals){
										#echo "<hr>$es_progr - ";
										#print_r($progr_vals);
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
											if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val['XML']."\">send e-query";
											if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
														$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
														$close_href="</a>";
														$this->body.="
															<tr>
																 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
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
										$date="";
										$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
										#echo "<hr>$date<hr>";
										if ($date!='') 	$dtp="($date)";
										$nome_esame=$es_val_corr['TESTO']." $dtp";
										if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val_corr['XML']."\">send e-query";
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
										$close_href="</a>";
										$this->body.="
									<tr>
										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
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
								}

								}
								$next_progr=$es_progr+1;
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=".$es_val['XML']."\">";
										$close_href="</a>";
										$this->body.="
												<tr>
													<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
													</td>
													<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\">New ".$es_val['TESTO']."</a><br/>
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
					$this->body.="</table>";
	  	}
	  	/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA*/
	  	if ($in['VISITNUM']!=''){
	  		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where CODPAT='".$in['CODPAT']."' and VISITNUM='".$in['VISITNUM']."'";
	  		$sql->set_sql($query);
	  		$sql->exec();
	  		$sql->get_row();
//	  		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
//	  			<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
//	  				<form method=post action='index.php' align=center>
//	  					<input type='hidden' name='CODPAT' value='".$in['CODPAT']."'>
//	  					<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
//	  					<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
//	  					<input type='hidden' name='exams' value='".$GLOBALS['visit_structure_xml']."'>
//	  					<input type='submit' name='close_visit' value='Close Visit' align=center>
//	  				</form>
//	  			</td></tr></table>
//	  		";
	  	}
	  	$this->body.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Menu Procuratore</a>
	  	<br/><a href=\"index.php?exams=".$GLOBALS['visit_structure_xml']."&amp;CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Vista individuale</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Lista Procure</a></p>";
	  	return $this->body;
	  }
	  
function esams_list_html_view(){
	  	global $in;
	  	global $conn;
	  	global $es_form;
	  	global $xml_dir;
	  	$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where codpat='".$in['CODPAT']."' order by progr";
	  	#echo "<hr>$query<hr>";
	  	$sql=new query($conn);
	  	$sql->set_sql($query);
	  	$sql->exec();
	  	$esams_html="";
	  	while ($sql->get_row()){
	  		if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
		  		$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
		  	}
	  	}
	  	#print_r($this->esams);
	  	foreach ($this->visitnums as $key => $val) {
	  		if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
		  		$this->body.="
		  		<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"95%\">
	        	<tr>
							<td class=\"int\" align=\"left\"><b>".$val['TEXT']."</b></td>
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
								$progr=0;
								if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
								#echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
									if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
									if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
									$date=$es_val['RES'][$progr]['INSERTDT'];
									$nome_esame=$es_val['TESTO'];
									if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
									#if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;equery=".$es_val['XML']."\">send e-query";
									if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
										#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;form=".$es_val['XML']."\">";
										#$close_href="</a>";
										$this->body.="
									<tr>
										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
										</td>
										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame."$close_href<br/>
										</td>
										<!--td class=\"sc4bis\" align=\"center\">
										</td>
										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
										</td-->
										</tr>
										";
										$in['VISITNUM']=$key;
										$in['ESAM']=$esam;
										$in['PROGR']=$progr;
										$in['CENTER']=$progr;
										$xml_form=new xml_form();
										$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
											if ($xml_form->closed_form()) {
												$xml_form->close_form();
												$esam_html.="<!--NewPage-->".$xml_form->body;
											}
											unset($in['VISITNUM']);
										
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
											$date="";
											$date=$es_val['RES'][$es_progr]['INSERTDT'];
											if ($date!='') $date="($date)";
											$nome_esame=$es_val['TESTO']." $date";
											#echo "<hr>{$es_val['TESTO']} - $date";
											#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val['XML']."\">send e-query";
											if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
														#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
														#$close_href="</a>";
														$this->body.="
															<tr>
																 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
																</td>
																<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																</td>
																<!--td class=\"sc4bis\" align=\"center\">
																</td>
																<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																</td-->
															</tr>
														";
														$in['VISITNUM']=$key;
														$in['ESAM']=$esam;
														$in['PROGR']=$es_progr;
														$xml_form=new xml_form();
														$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
															if ($xml_form->closed_form()) {
																$xml_form->close_form();
																$esam_html.="<!--NewPage-->".$xml_form->body;
															}
															unset($in['VISITNUM']);
															unset($in['ESAM']);
															unset($in['PROGR']);
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
										$date="";
										$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
										#echo "<hr>$date<hr>";
										if ($date!='') 	$dtp="($date)";
										$nome_esame=$es_val_corr['TESTO']." $dtp";
										#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val_corr['XML']."\">send e-query";
										#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
										#$close_href="</a>";
										$this->body.="
									<tr>
										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
										</td>
										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
										</td>
										<!--td class=\"sc4bis\" align=\"center\">
										</td>
										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
										</td-->
										</tr>
										";
										$in['VISITNUM']=$key;
										$in['ESAM']=$esam_corr;
										$in['PROGR']=$es_progr;
										$xml_form=new xml_form();
										$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
											if ($xml_form->closed_form()) {
																$xml_form->close_form();
																$esam_html.="<!--NewPage-->".$xml_form->body;
											}
											unset($in['VISITNUM']);
											unset($in['ESAM']);
											unset($in['PROGR']);
										}
									}
								}

								}
								/*
								$next_progr=$es_progr+1;
										#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=".$es_val['XML']."\">";
										#$close_href="</a>";
										$this->body.="
												<tr>
													<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
													</td>
													<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\">New ".$es_val['TESTO']."</a><br/>
													</td>
													<td class=\"sc4bis\" align=\"center\">
													</td>
													<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
													</td>
												</tr>
										";*/
								}
							}
						}
					}
					$this->body.="</table>";
	  	}
	  	/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA
	  	if ($in['VISITNUM']!=''){
	  		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where CODPAT='".$in['CODPAT']."' and VISITNUM='".$in['VISITNUM']."'";
	  		$sql->set_sql($query);
	  		$sql->exec();
	  		$sql->get_row();
	  		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
	  			<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
	  				<form method=post action='index.php' align=center>
	  					<input type='hidden' name='CODPAT' value='".$in['CODPAT']."'>
	  					<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
	  					<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
	  					<input type='hidden' name='exams' value='visite_exams.xml'>
	  					<input type='submit' name='close_visit' value='Close Visit' align=center>
	  				</form>
	  			</td></tr></table>
	  		";
	  	}*/
	  	/*$this->body.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Vista individuale</a>
	  	<br/><a href=\"index.php?exams=visite_exams.xml&amp;CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Individual Patient Exam List</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Procuratori registrati </a></p>";
	  	*/
	  	$this->body.=$esam_html;
	  	return $this->body;
	  }

	function esams_group_html(){
	  	global $in;
	  	global $conn;
	  	$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where codpat='".$in['CODPAT']."' order by progr";
	  	#echo $query;
	  	$sql=new query($conn);
	  	$sql->set_sql($query);
	  	$sql->exec();
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
								<td class=\"int\" align=\"left\"><a href=\"index.php?CODPAT=".$in['CODPAT']."&amp;VISITNUM=".$val['NUMBER']."&exams=".$GLOBALS['visit_structure_xml']."\" class=\"sc2b\">".$val['TEXT']."</a></td>
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
									$progr=0;
								if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
									#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
										if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
										if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
										if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
										$date=$es_val['RES'][$progr]['INSERTDT'];
										if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
											$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$progr&amp;form=".$es_val['XML']."\">";
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
															$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
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
											$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
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
											$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=".$es_val['XML']."\">";
											$close_href="</a>";
											$this->body.="
													<tr>
														<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."\">New ".$es_val['TESTO']."</a><br/>
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
	  	$this->body.="</table><p align=right><a href=\"index.php?list=patients_list.xml&CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Menu Procuratore</a>
	  	<br/><a href=\"index.php?exams=".$GLOBALS['visit_structure_xml']."&CODPAT=".$in['CODPAT']."&CENTER=".$in['CENTER']."\">Vista individuale</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Lista Procure</a></p>";
	  	return $this->body;
	}

}




function var_glob($value){
	global $in;
	global $inputval;
	#global $vis_name;
	if ($GLOBALS[$value]!='') return $GLOBALS[$value];
	if ($in[$value]!='') return $in[$value];
	if ($inputval[$value]!='') return $inputval[$value];
}
