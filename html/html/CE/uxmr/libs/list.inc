<?

/**
 * classe xml_list_prototype
 * Classe per la costruzione delle liste a partire dal file xml
 *
 * @package ViewsAndControllers
 *
 */



class xml_list_prototype {
	
	function var_glob($value, &$binded=null){
		global $in;
		global $inputval;
		if (isset($inputval[$value]) && $inputval[$value]!='') {
			if (isset($binded)) {
				$binded["global_".$value]=$inputval[$value];
				return ":global_".$value;
			}
			return $inputval[$value];
		}
		if (isset($in[$value]) && $in[$value]!='') {
			if (isset($binded)) {
				$binded["global_".$value]=$in[$value];
				return ":global_".$value;
			}
			return $in[$value];
		}
		if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') {
			if (isset($binded)) {
				$binded["global_".$value]=$GLOBALS[$value];
				return ":global_".$value;
			}
			
			return $GLOBALS[$value];
		}
	}

	var $titolo;
	var $cols;
	var $html;
	var $list;
	var $sql;
	var $page;
	var $rpp;
	var $empty = true;
	var $count_items = false;
	var $items_name;
	var $presenti_string;
	var $n_item_returned;
	var $conn;
	var $config_service;
	var $session_vars;

	/**
	 * Costruttore
	 *
	 * $xml_file: file xml
	 *
	 * @param string $xml_file
	 * @return xml_list_prototype
	 */
	function xml_list_prototype($xml_file, $page=null, $rpp=null,$conn=null, $config_service=null, $session_vars=null) {
		if(!$conn){
			global $conn;
			if(!$conn)
			$this->conn=$conn=new dbconn();
		}
		if(!$config_service){
			global $config_service;
		}
		$this->config_service=$config_service;
		$this->session_vars=$session_vars;

		if (isset($page) && $page!='') $this->page=$page;
		if (isset($rpp) && $rpp!='') $this->rpp=$rpp;
		$xml_parser = new my_xml_parser ( $xml_file );
		$newtag = true;
		$cl = 0;
		$this_node = new xml_node ( );
		#print_r($xml_parser->vals);
		for($i = 0; $i < count ( $xml_parser->vals ); $i ++) {
			$this_node->xml_node_by_array ( $xml_parser->vals [$i] );

			if ($this_node->type != 'cdata') {
				if ($this_node->tag == 'LIST')
				if ($this_node->type == 'open' or $this_node->type == 'complete') {
					$this->list = $this_node->attributes;
				}
				if ($this_node->tag == 'COL') {
					if ($this_node->type == 'open' or $this_node->type == 'complete') {
						$this->cols [$cl] = $this_node->attributes;
						$this->cols [$cl] ['TESTO'] = $this_node->value;
						if ($this_node->type == 'complete')
						$cl ++;
					}
					if ($this_node->type == 'close') {
						$cl ++;
					}
				}
			}
		}
	}

	function col_th_testo($i) {
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		if($in['SEARCH']){
			foreach ($in as $par => $valore){
				if($valore!='' && $par!='remote_userid')$param.="&".urlencode($par)."=".urlencode($valore);
			}
		}
		
		$txt = $this->cols [$i] ['TESTO'];
		if ($this->cols [$i] ['ORD_ARROW'] != '') {
			if ($this->cols [$i] ['ORD_ARROW'] == 'yes')
			$this->cols [$i] ['ORD_ARROW'] = $this->cols [$i] ['NOME'];
			$img_down = "/images/down_arrow.gif";
			if ($in ['ORD_TYPE'] == 'ASC' && $in ['ORD'] == $this->cols [$i] ['ORD_ARROW'])
			$img_down = "/images/down_arrow_red.gif";
			$img_up = "/images/up_arrow.gif";
			if ($in ['ORD_TYPE'] == 'DESC' && $in ['ORD'] == $this->cols [$i] ['ORD_ARROW'])
			$img_up = "/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			foreach($_GET as $key=>$val){
				if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="&".urlencode($key)."=".urlencode($val);
			}
			if (isset ( $in ['page'] ))
			$param .= "page=1&";
			if (isset ( $in ['ESAM'] ) && isset ( $in ['VISITNUM'] ) && ($in ['VISITNUM'] == 0) && ($in ['ESAM'] == 0)) {
				$txt .= "
	  			<br><a href=\"index.php?&{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?&{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			} else { //solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in ['CENTER'] != '')
				$center = "CENTER={$in['CENTER']}";
				$txt .= "
	  			<br><a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		return "<th class=\"int\">" . $txt . "</th>";
	}

	function col_th_validation($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_eq_link($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_html($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_pdf($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_freccia($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_lente($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}
	function col_th_image($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}
	function col_th_image_if_value($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_elimina($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_visita($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_status($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_td_status($i) {

		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		$value = explode ( " - ", $value );
		#echo "<hr>$value[0] . $value[1] . $value[2]<hr>";
		if ($value [1] == 1) {
			if ($value [0] == 0)
			$txt = "<b>Not Elegible for";
			else
			$txt = "<b><a href=\"index.php?CENTER=" . $this->sql->row ['CENTER'] . "&CODPAT=" . $this->sql->row ['CODPAT'] . "&PROTOCOL=" . $this->sql->row ['PROTOCOL'] . "\">Enrolled in";
		}
		if ($value [1] == '')
		$txt = "<b>On Screening";
		if ($value [1] == '0')
		$txt = "<b><a href=\"index.php?CENTER=" . $this->sql->row ['CENTER'] . "&CODPAT=" . $this->sql->row ['CODPAT'] . "&VISITNUM=2&PROGR=2&ESAM=2&PROTOCOL=" . $this->sql->row ['PROTOCOL'] . "\">Verify Eligibility for";
		if ($this->sql->row ['D_PROTOCOL'] != '')
		$txt .= "<br>" . $this->sql->row ['D_PROTOCOL'] . "</a>";
		if ($this->sql->row ['D_PAT_RISK'] != '')
		$txt .= "<br>" . $this->sql->row ['D_PAT_RISK'];
		return $txt;
	}

	function col_th_visite($i) {
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		foreach ( $visit->visitnums as $key => $val ) {
			if ($th != '')
			$th .= "</th><th class=\"int\">";
			else
			$th = "<th class=\"int\">";
			$th .= $val ['SHORT_TXT'];
		}
		$th .= "</th>";
		return $th;
	}

	function col_th_visite_dm($i) {
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		foreach ( $visit->visitnums as $key => $val ) {
			if ($th != '')
			$th .= "</th><th class=\"int\">";
			else
			$th = "<th class=\"int\">";
			$th .= $val ['SHORT_TXT'];
		}
		$th .= "</th>";
		return $th;
	}

	function col_th_visite_gruppo($i) {
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		foreach ( $visit->group as $key => $val ) {
			if ($th != '')
			$th .= "</th><th class=\"int\">";
			else
			$th = "<th class=\"int\">";
			$th .= $val ['TEXT'];
		}
		$th .= "</th>";
		return $th;
	}

	function col_td_visite_dm($i) {
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		$sql_visite = "
			select
				fine,
				inizio,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		unset($bind);
		$bind['PK_SERVICE']=$pk_service;
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite,$bind );//binded
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
		}
		$remote_userid = $in ['remote_userid'];
		foreach ( $visit->visitnums as $visitnum => $val ) {
			if ($string != '')
			$string .= "\n<td class=sc4bis align=center>";
			$is_data_entry = false;
			$img="";
			$visita [$visitnum]['closed'] = false;
			$visita[$visitnum]['init']=false;
			$visita[$visitnum]['enabled']=false;
			$visita[$visitnum]['exist']=false;
			$visita[$visitnum]['active']=false;
			$visita[$visitnum]['all_my_closed']=true;
            $f_bianca = "f_bianca.gif";
            $f_gialla = "f_gialla.gif";
            $f_verde = "f_verde.gif";
            $f_grigia = "f_grigia.gif";
            $f_blue = "f_blue.gif";
            if (isset ( $visit->visitnums [$visitnum] ['IMG_CLOSE'] )){
            $f_verde = $visit->visitnums [$visitnum] ['IMG_CLOSE'];
            }
            if (isset ( $visit->visitnums [$visitnum] ['IMG_SAVED'] ))
            $f_gialla = $visit->visitnums [$visitnum] ['IMG_SAVED'];
            if (isset ( $visit->visitnums [$visitnum] ['IMG_BLANK'] ))
            $f_bianca = $visit->visitnums [$visitnum] ['IMG_BLANK'];
			if ($val ['VIEWABLE_ON_CLOSE'] == 'yes')
			$visit_viewable_on_close = true;
			else
			$visit_viewable_on_close = false;
			$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
			foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) {
				foreach ( $visit->esams [$visitnum] as $esam => $val_esam ) {
					foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) {
						$visita[$visitnum]['exist']=true;
						if ($remote_userid == $val_progr ['USERID'] || $val_progr ['USERID']=='') {
							$is_data_entry = true;
							$is_data_entry [$progr] = true;
							$visita[$visitnum]['active']=true;
						} else {
							$is_data_entry [$progr] = false;
						}

						if ($val_esam['VIEWABLE_ON_CLOSE']){
							//esame visibile solo se inviato o dall'utente specificato
							if ($remote_userid!=$val_progr['USERID']){
								if ($val_progr['FINE']==1) $visita[$visitnum]['init']=true;
							}
							else {
								if ($val_progr['FINE']!=1 || $val_esam['ADD_PROGR']=='') $visita[$visitnum]['all_my_closed']=false;
								$visita[$visitnum]['enabled']=true;
								if ($val_progr['INIZIO']==1) $visita[$visitnum]['init']=true;
							}
						}
						else {
							if ($val_progr['FINE']!=1 || $val_esam['ADD_PROGR']=='') $visita[$visitnum]['all_my_closed']=false;
							//esame visibile dall'utente in questione in ogni caso
							$visita[$visitnum]['enabled']=true;
							if ($val_progr['INIZIO']==1) $visita[$visitnum]['init']=true;
						}
						if ($val_progr ['VISITCLOSE'] == 1) {
							$visita [$visitnum] ['closed'] = true;
						}
					}
				}
			}
			if ($visita[$visitnum]['exist']) $img = $f_grigia;
			if ($visita[$visitnum]['enabled']) {
				$img = $f_bianca;
//				if (!$visita[$visitnum]['active']) $img=$f_grigia;
			}
			if ($visita [$visitnum] ['closed']) {
				//VISITA CHIUSA
				$img = $f_verde;
			} else {
				//VISITA non chiusa
				if ($visit_viewable_on_close) {
					if ($is_data_entry && $visita[$visitnum]['init']) $img=$f_gialla;
				}
				else {
					if ($visita[$visitnum]['init']) {
						$img=$f_gialla;
//						if (!$visita[$visitnum]['active']) $img=$f_blue;
					}

				}
			}

			if ($visita[$visitnum]['init']==1 && $visita[$visitnum]['enabled']==1 && $visita[$visitnum]['all_my_closed']==1) $img=$f_verde;
			$param = "?exams=" . $this->cols [$i] ['EXAMS'];
			$params = $this->cols [$i] ['PARAM'];
			$params = explode ( ",", $params );
			for($p = 0; $p < count ( $params ); $p ++) {
				if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
					$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
				} else
				$param .= "&amp;" . $params [$p];
			}
			$param .= "&amp;VISITNUM=$visitnum";
			if ($img != '') {
				$img_tag = "<img src=\"/images/$img\" border=0>";
				if ($img!=$f_grigia)
				$href = "
				<a href=\"index.php$param\">$img_tag</a>
				";
				else $href=$img_tag;
			} else {
				$img_tag = '&nbsp;';
				$href = "
				$img_tag
				";
			}
			$string .= "$href &nbsp;</td>";
		}
		//print_r($visita);
		return $string;
		foreach ( $visit->visitnums as $key => $val ) {
			if ($td != '')
			$td .= "
				</td>
				<td class='sc4bis'>&nbsp;
				";
			$value = $this->sql->row [strtoupper ( 'V' . $key )];
			$value = explode ( " - ", $value );
			$img = '';
			$f_bianca = "f_bianca.gif";
			$f_gialla = "f_gialla.gif";
			$f_verde = "f_verde.gif";
			if (isset ( $visit->visitnums [$key] ['IMG_CLOSE'] ))
			$f_verde = $visit->visitnums [$key] ['IMG_CLOSE'];
			if (isset ( $visit->visitnums [$key] ['IMG_SAVED'] ))
			$f_gialla = $visit->visitnums [$key] ['IMG_SAVED'];
			if (isset ( $visit->visitnums [$key] ['IMG_BLANK'] ))
			$f_bianca = $visit->visitnums [$key] ['IMG_BLANK'];
			if ($value [3] == '1')
			$img = $f_bianca;
			if ($value [0] == '1')
			$img = $f_gialla;
			if ($value [1] == '1')
			$img = $f_gialla;
			if ($value [2] == '1')
			$img = $f_verde;
			$param = "?exams=" . $this->cols [$i] ['EXAMS'];
			$params = $this->cols [$i] ['PARAM'];
			$params = explode ( ",", $params );
			if ($param == '')
			$param = '?';
			for($p = 0; $p < count ( $params ); $p ++) {
				if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
					$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
				} else
				$param .= "&amp;" . $params [$p];
			}
			$param .= "&amp;VISITNUM=$key";
			if ($img != '') {
				$img_tag = "<img src=\"/images/$img\" border=0>";
				$td .= "
				<a href=\"index.php$param\">$img_tag</a>
				";
			} else {
				$img_tag = '&nbsp;';
				$td .= "
				$img_tag
				";
			}

		}

		return $td;
	}

	function col_td_visite($i) {
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		$sql_visite = "
			select
				fine,
				inizio,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		unset($bind);
		$bind['PK_SERVICE']=$pk_service;
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite ,$bind); //binded
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
		}
		$remote_userid = $in ['remote_userid'];
		foreach ( $visit->visitnums as $visitnum => $val ) {
//			print_r($val);
			if ($string != '')
			$string .= "\n<td class=sc4bis align=center>";
			$is_data_entry = false;
			$img="";
			$visita [$visitnum]['closed'] = false;
			$visita[$visitnum]['init']=false;
			$visita[$visitnum]['enabled']=false;
			$visita[$visitnum]['exist']=false;
			$visita[$visitnum]['active']=false;
			$visita[$visitnum]['all_my_closed']=true;
            $f_bianca = "f_bianca.gif";
            $f_gialla = "f_gialla.gif";
            $f_verde = "f_verde.gif";
            $f_grigia = "f_grigia.gif";
            $f_blue = "f_blue.gif";
            if (isset ( $visit->visitnums [$visitnum] ['IMG_CLOSE'] )){
            $f_verde = $visit->visitnums [$visitnum] ['IMG_CLOSE'];
            }
            if (isset ( $visit->visitnums [$visitnum] ['IMG_SAVED'] ))
            $f_gialla = $visit->visitnums [$visitnum] ['IMG_SAVED'];
            if (isset ( $visit->visitnums [$visitnum] ['IMG_BLANK'] ))
            $f_bianca = $visit->visitnums [$visitnum] ['IMG_BLANK'];
			if ($val ['VIEWABLE_ON_CLOSE'] == 'yes')
			$visit_viewable_on_close = true;
			else
			$visit_viewable_on_close = false;
			$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
			foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) {
				foreach ( $visit->esams [$visitnum] as $esam => $val_esam ) {
					foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) {
						$visita[$visitnum]['exist']=true;
						if ($remote_userid == $val_progr ['USERID'] || $val_progr ['USERID']=='') {
							$is_data_entry = true;
							$is_data_entry [$progr] = true;
							$visita[$visitnum]['active']=true;
						} else {
							$is_data_entry [$progr] = false;
						}

						if ($val_esam['VIEWABLE_ON_CLOSE']){
							//esame visibile solo se inviato o dall'utente specificato
							if ($remote_userid!=$val_progr['USERID']){
								if ($val_progr['FINE']==1) $visita[$visitnum]['init']=true;
							}
							else {
								if ($val_progr['FINE']!=1 || $val_esam['ADD_PROGR']=='') $visita[$visitnum]['all_my_closed']=false;
								$visita[$visitnum]['enabled']=true;
								if ($val_progr['INIZIO']==1) $visita[$visitnum]['init']=true;
							}
						}
						else {
							if ($val_progr['FINE']!=1 || $val_esam['ADD_PROGR']=='') $visita[$visitnum]['all_my_closed']=false;
							//esame visibile dall'utente in questione in ogni caso
							$visita[$visitnum]['enabled']=true;
							if ($val_progr['INIZIO']==1) $visita[$visitnum]['init']=true;
						}
						if ($val_progr ['VISITCLOSE'] == 1) {
							$visita [$visitnum] ['closed'] = true;
						}
					}
				}
			}
			if ($visita[$visitnum]['exist']) $img = $f_grigia;
			if ($visita[$visitnum]['enabled']) {
				$img = $f_bianca;
				if (!$visita[$visitnum]['active']) $img=$f_grigia;
			}
			if ($visita [$visitnum] ['closed']) {
				//VISITA CHIUSA
				$img = $f_verde;
			} else {
				//VISITA non chiusa
				if ($visit_viewable_on_close) {
					if ($is_data_entry && $visita[$visitnum]['init']) $img=$f_gialla;
				}
				else {
					if ($visita[$visitnum]['init']) {
						$img=$f_gialla;
//						if (!$visita[$visitnum]['active']) $img=$f_blue;
					}

				}
			}

			if ($visita[$visitnum]['init']==1 && $visita[$visitnum]['enabled']==1 && $visita[$visitnum]['all_my_closed']==1) $img=$f_verde;
			$param = "?exams=" . $this->cols [$i] ['EXAMS'];
			$params = $this->cols [$i] ['PARAM'];
			$params = explode ( ",", $params );
			for($p = 0; $p < count ( $params ); $p ++) {
				if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
					$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
				} else
				$param .= "&amp;" . $params [$p];
			}
			$param .= "&amp;VISITNUM=$visitnum";
			if ($img != '') {
				$img_tag = "<img src=\"/images/$img\" border=0>";
				if ($img!=$f_grigia)
				$href = "
				<a href=\"index.php$param\">$img_tag</a>
				";
				else $href=$img_tag;
			} else {
				$img_tag = '&nbsp;';
				$href = "
				$img_tag
				";
			}
			$string .= "$href &nbsp;</td>";
		}
		//print_r($visita);
		return $string;
		foreach ( $visit->visitnums as $key => $val ) {
			if ($td != '')
			$td .= "
				</td>
				<td class='sc4bis'>&nbsp;
				";
			$value = $this->sql->row [strtoupper ( 'V' . $key )];
			$value = explode ( " - ", $value );
			$img = '';
			$f_bianca = "f_bianca.gif";
			$f_gialla = "f_gialla.gif";
			$f_verde = "f_verde.gif";
			if (isset ( $visit->visitnums [$key] ['IMG_CLOSE'] ))
			$f_verde = $visit->visitnums [$key] ['IMG_CLOSE'];
			if (isset ( $visit->visitnums [$key] ['IMG_SAVED'] ))
			$f_gialla = $visit->visitnums [$key] ['IMG_SAVED'];
			if (isset ( $visit->visitnums [$key] ['IMG_BLANK'] ))
			$f_bianca = $visit->visitnums [$key] ['IMG_BLANK'];
			if ($value [3] == '1')
			$img = $f_bianca;
			if ($value [0] == '1')
			$img = $f_gialla;
			if ($value [1] == '1')
			$img = $f_gialla;
			if ($value [2] == '1')
			$img = $f_verde;
			$param = "?exams=" . $this->cols [$i] ['EXAMS'];
			$params = $this->cols [$i] ['PARAM'];
			$params = explode ( ",", $params );
			if ($param == '')
			$param = '?';
			for($p = 0; $p < count ( $params ); $p ++) {
				if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
					$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
				} else
				$param .= "&amp;" . $params [$p];
			}
			$param .= "&amp;VISITNUM=$key";
			if ($img != '') {
				$img_tag = "<img src=\"/images/$img\" border=0>";
				$td .= "
				<a href=\"index.php$param\">$img_tag</a>
				";
			} else {
				$img_tag = '&nbsp;';
				$td .= "
				$img_tag
				";
			}

		}

		return $td;
	}

	function col_td_visite_gruppo($i) {
		global $xml_dir;
		#echo "<hr>col_td_visite_gruppo<hr>";
		#$th="<th class=\"int\">";
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		foreach ( $visit->group as $key => $val ) {
			if ($td != '')
			$td .= "</td><td class='sc4bis'>&nbsp;";
			$value = $this->sql->row [strtoupper ( 'V' . $key )];
			# echo "<hr> gruppo $key $value";
			$value = explode ( " - ", $value );
			if ($value [3] == 1) {
				$f_bianca = "f_bianca.gif";
				$f_gialla = "f_gialla.gif";
				$f_verde = "f_verde.gif";

				if (isset ( $visit->group [$key] ['IMG_CLOSE'] ))
				$f_verde = $visit->group [$key] ['IMG_CLOSE'];
				if (isset ( $visit->group [$key] ['IMG_SAVED'] ))
				$f_gialla = $visit->group [$key] ['IMG_SAVED'];
				if (isset ( $visit->group [$key] ['IMG_BLANK'] ))
				$f_bianca = $visit->group [$key] ['IMG_BLANK'];
				$img = $f_bianca;
				if ($value [0] == 1)
				$img = $f_gialla;
				if ($value [1] == 1)
				$img = $f_gialla;
				if ($value [2] == 1)
				$img = $f_verde;
				$param = "?exams=" . $this->cols [$i] ['EXAMS'];
				$params = $this->cols [$i] ['PARAM'];
				$params = explode ( ",", $params );
				if ($param == '')
				$param = '?';
				for($p = 0; $p < count ( $params ); $p ++) {
					if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
						#echo "<hr>".$params[$p]."=".$this->sql->row[strtoupper($params[$p])];
						$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
					} else
					$param .= "&amp;" . $params [$p];
				}
				$param .= "&amp;GROUP=$key";
				$td .= "<a href=\"index.php$param\"><img src=\"/images/$img\" border=0></a>";
			}
		}
		return $td;
	}

	function col_td_visita($i) {
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		$value = explode ( " - ", $value );
		if ($value [3] == 1) {
			$img = "f_bianca.gif";
			if ($value [0] == 1)
			$img = "f_gialla.gif";
			if ($value [1] == 1)
			$img = "f_gialla.gif";
			if ($value [2] == 1)
			$img = "f_verde.gif";
			$img_tag = "<img src=\"/images/$img\" border=0>";
		}
		return $img_tag;
	}

	/**
	 * col_script
	 * Costruisce il link
	 *
	 * @param int $i
	 * @return string
	 */
	function col_script($i) {
		$link = $this->cols [$i] ['SCRIPT'];
		if ($this->cols [$i] ['LIST'] != '')
		$param = "?list=" . $this->cols [$i] ['LIST'];
		if ($this->cols [$i] ['EQUERY_VIEW'] != '')
		$param = "?equery_view=" . $this->cols [$i] ['EQUERY_VIEW'];
		if ($this->cols [$i] ['VLIST'] != '')
		$param = "?vlist=" . $this->cols [$i] ['VLIST'];
		if ($this->cols [$i] ['EXAMS'] != '')
		$param = "?exams=" . $this->cols [$i] ['EXAMS'];
		if ($this->cols [$i] ['FORM'] != '')
		$param = "?form=" . $this->cols [$i] ['FORM'];
		if ($this->cols [$i] ['EFORM'] != '')
		$param = "?eform=" . $this->cols [$i] ['EFORM'];
		if ($this->cols [$i] ['CONFIRM'] != '') {
			$confirm = " onclick=\"
				if (!confirm('{$this->cols[$i]['CONFIRM']}')) return false;
				\"";
		}
		$params = $this->cols [$i] ['PARAM'];
		$params = explode ( ",", $params );
		if ($param == '')
		$param = '?';
		for($p = 0; $p < count ( $params ); $p ++) {
			$params[$p]=preg_replace("/\|/i", "," , $params[$p]);
			if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
				#echo "<hr>".$params[$p]."=".$this->sql->row[strtoupper($params[$p])];
				$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
			} else
			$param .= "&amp;" . $params [$p];
		}
		$param = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $param );
		$link .= $param;
//		echo $link.'<hr />';
		$target="";
		if(isset($this->cols [$i]['TARGET'])) $target=" target=\"{$this->cols [$i]['TARGET']}\"";
		return "<a href=\"$link\" $target $confirm>";
	}

	function col_td_testo($i) {
//		global $in;
		if($this->session_vars) $in=$this->session_vars;
		else{
			global $in;
		}
		//		print($in ['USER_TIP']);
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
  		if ($this->cols [$i] ['CRYPTO'] == 'yes' && ($in ['USER_TIP'] == 'DM' || $in ['USER_TIP'] == 'RO'))
		$value = '****';
        if($this->cols [$i] ['SKIP_XSS']!='yes')$value = htmlspecialchars($value,ENT_QUOTES,"UTF-8");
		return $value . "&nbsp;";
	}

	function col_td_validation($i) {
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
		if ($this->sql->row ['TO_BE_VALIDATE'] == '1' && $value == '') {
			return "<a href=\"index.php?CENTER=003&CODPAT=" . $this->sql->row ['CODPAT'] . "&VISITNUM=" . $this->sql->row ['VISITNUM'] . "&ESAM=" . $this->sql->row ['ESAM'] . "&PROGR=" . $this->sql->row ['PROGR'] . "&equery_view=view&ID=" . $this->sql->row ['ID'] . "\">Validate the form</a>";
		} else {
			if ($this->sql->row ['TO_BE_VALIDATE'] != '1')
			return "Not to be Validated";
			else
			return $value . "&nbsp;";
		}
	}

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $i
	 * @return unknown
	 */
	function col_td_eq_link($i) {
		#echo "<hr>".$this->sql->row['CHIUSA']."<hr>";
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
        if($this->cols [$i] ['SKIP_XSS']!='yes')htmlspecialchars($value,ENT_QUOTES,"UTF-8");
		#$value=preg_replace("/#(.*?)#/", "<\\1>", $value);
		if ($this->sql->row ['CHIUSA'] == 'open')
		$value = "<a href=\"index.php?equery_view=view&FORM=equery.xml&ID=$value\">$value</a>";
		return $value . "&nbsp;";
	}

	function col_td_html($i) {
		$value = "<img src=\"images/html.gif\" width=25  border=0>";
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
		return $value;
	}

	function col_td_pdf($i) {
		$value = "<img src=\"images/pdf.gif\" width=25  border=0>";
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
		return $value;
	}

	function col_td_javascript($i){
		global $in;
		//     echo $in['source']."<br>";
		//INIZIALMENTE ERANO 3 preg_replace sia per source sia per dest, ma gli ultimi due avevano un carattere illeggibile,
		//quindi ho corretto il secondo con il percento perché eravamo sicuri, e il terzo l'abbiamo tolto.
		//eventuali segnalazioni a G.Tufano o C.Contino.
		$in['source']=preg_replace("/£/",",",$in['source']);
		$in['source']=preg_replace("/?/",",",$in['source']);
		$in['source']=preg_replace("/?/",",",$in['source']);
		$in['source']=preg_replace("/%/",",",$in['source']);
		
		//    echo $in['source']."<br>";
		$in['dest']=preg_replace("/£/",",",$in['dest']);
		$in['dest']=preg_replace("/?/",",",$in['dest']);
		$in['dest']=preg_replace("/?/",",",$in['dest']);
		$in['dest']=preg_replace("/%/",",",$in['dest']);
        $in['source']=preg_replace('/[^A-Za-z0-9_,]/', '', $in['source']);
        $in['dest']=preg_replace('/[^A-Za-z0-9_,]/', '', $in['dest']);
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

	/**
	 * Enter description here...
	 *
	 * @param unknown_type $i
	 * @return unknown
	 */
	function col_td_freccia($i) {
		return "<img src=\"/images/send-value.gif\" border=0>";
	}

	function col_td_lente($i) {
		return "<img src=\"/images/lente.gif\" border=0>";
	}

	function col_td_elimina($i) {
		return "<img src=\"/images/trash.png\" border=0>";
	}
	function col_td_image($i) {
		$size = $this->cols [$i] ['SIZE'];
		if (is_numeric($size) && $size >0)
			$width = 'width="'.$size.'px"';
		return "<img src=\"/images/{$this->cols[$i]['IMAGE']}\" border='0' $width>";
	}
	
	function col_td_image_if_value($i) {
		$size = $this->cols [$i] ['SIZE'];
		if (is_numeric($size) && $size >0)
			$width = 'width="'.$size.'px"';
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		if($value){
			return "<img src=\"/images/{$this->cols[$i]['IMAGE']}\" border='0' $width>";
		}
	}
	/**
	 * Costruisce il codice html della lista
	 *
	 * @return string
	 */
	function list_html($session_vars=null) {
		# echo "<hr>list_html<hr>";
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
        if(strtoupper($in['oper'])!='AND' && strtoupper($in['oper'])!='OR'){
            $in['oper']='';
        }
		//global $config_service;
		//if($session_vars)$in=$session_vars;
		if($in['PAGE']>0)$this->page=$in['PAGE'];
		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];

		$html = "<table border=\"0\" id=\"table1\" width=\"95%\" align=center class=\"table table-striped table-bordered table-hover\"><thead><tr>";
		$sql = new query ( $conn );
		$sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'" );
		$sql->ins_upd ();//non richiede binding
		for($i = 0; $i < count ( $this->cols ); $i ++) {
			if ($this->cols [$i] ['GROUP_BY'] != '') {
				if (! isset ( $group_by ))
				$group_by = $this->cols [$i] ['VAR'];
				else
				$group_by .= "," . $this->cols [$i] ['VAR'];
			}
			if ($this->cols [$i] ['ORDER_BY'] != '') {
				if($this->cols [$i] ['ORDER_BY']=='asc' || $this->cols [$i] ['ORDER_BY']=='desc')$ord_t = $this->cols [$i] ['ORDER_BY'];
				else $ord_t='';
				if (! isset ( $order_by ))
				$order_by = $this->cols [$i] ['NOME'] ." ".$ord_t;
				else
				$order_by .= "," . $this->cols [$i] ['NOME'];
			}
			if ($in ['ORD'] != '') {
			$checkOrdPassed=false;
				foreach ($this->cols as $idx=>$ordValFor){
					if ($ordValFor['ORD_ARROW']==yes) {
						if ($in['ORD']==$ordValFor['NOME']) $checkOrdPassed=true;
					}else {
						if ($in['ORD']==$ordValFor['ORD_ARROW']) $checkOrdPassed=true;
					}
				}
				if (strtoupper($in['ORD_TYPE'])!='ASC' && strtoupper($in['ORD_TYPE'])!='DESC') $checkOrdPassed=false;
				if ($checkOrdPassed) {
					$order_by = "{$in['ORD']} {$in['ORD_TYPE']}";
				}
			}
			if ($this->cols [$i] ['WHERE'] != '') {
				if (! isset ( $where ))
				$where = $this->cols [$i] ['WHERE'];
				else
				$where .= " and " . $this->cols [$i] ['WHERE'];
			}
			if ($this->cols [$i] ['VAR'] != '') {
				if (! isset ( $fields ))
				$fields = $this->cols [$i] ['VAR'] . " as " . $this->cols [$i] ['NOME'];
				else
				$fields .= "," . $this->cols [$i] ['VAR'] . " as " . $this->cols [$i] ['NOME'];
			}
			if ($this->cols [$i] ['TIPO'] == 'studio_simple_text'){
				if($fields!='')$fields.=", ";
				//$this->cols [$i] ['TABLE_REF'] = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $this->cols [$i] ['TABLE_REF'] );
				$this->cols [$i] ['TABLE_REF'] = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $this->cols [$i] ['TABLE_REF'] );
				$fields.="(select count(*) as conto from {$this->cols [$i]['STUDIO']}_coordinate where $pk_service={$this->cols [$i]['TABLE_REF']}.$pk_service) as {$this->cols [$i]['STUDIO']}";
			}
			if ($this->cols [$i] ['TIPO'] == 'all_substudies'){
				//				if($fields!='')$fields.=", ";
				//				$this->cols [$i] ['TABLE_REF'] = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $this->cols [$i] ['TABLE_REF'] );
				//				$fields.="(select count(*) as conto from {$this->cols [$i]['STUDIO']}_coordinate where $pk_service={$this->cols [$i]['TABLE_REF']}.$pk_service) as {$this->cols [$i]['STUDIO']}";
				//				$xmr = new xmrwf ( "study.xml", $conn );
				//				print_r($xmr);
			}

			if ($this->cols [$i] ['TIPO'] == 'visite_gruppo') {
				$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
				foreach ( $visit->group as $key => $val ) {
					$in_sql = '';
					foreach ( $val ['VISIT'] as $vis => $visval ) {
						if ($in_sql != '')
						$in_sql .= ",";
						$in_sql .= "'$vis'";
					}
					if($this->cols[$i]['REF_TABLE']!='')$ref_table=$this->cols[$i]['REF_TABLE'];
					else $ref_table=$GLOBALS['patients_table'];
					if (! isset ( $fields ))
					$fields = "
						(
							select
								max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
							from " . $GLOBALS ['service'] . "_COORDINATE
							where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
							and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
					else
					$fields .= ",
						(
							select
								max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
							from " . $GLOBALS ['service'] . "_COORDINATE
							where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
							and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
				}
			}
			$this->cols [$i] ['TABLE'] = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $this->cols [$i] ['TABLE'] );
			if (! preg_match ( "/" . $this->cols [$i] ['TABLE'] . "/i", $tables )) {
				if ($tables != '')
				$tables .= ",";
				$tables .= $this->cols [$i] ['TABLE'];
			}
			$function_to_call = "col_th_" . $this->cols [$i] ['TIPO'];
			if (method_exists ( $this, $function_to_call ))
			$html .= $this->{$function_to_call} ( $i );
			$nome = $this->cols [$i] ['NOME'];
			//echo "<hr/>".var_glob ( $nome,$session_vars ) ;
			if (var_glob ( $nome,$session_vars ) != '' && var_glob ( $nome,$session_vars ) != 'next') {
				//echo "<br/>entro";
				if ($where != '')
				$where .= " and ";
				$where .=  $this->cols [$i] ['VAR'] . "=:session_" . $this->cols [$i] ['NOME'] . " ";
				$binded_vars["session_".$this->cols [$i] ['NOME']]=var_glob ( $nome, $session_vars );
			}
		}

		$html .= "</tr></thead>";
		$query = "select $fields from $tables";
//		echo "<!-- ".$query."<hr> -->";
//		echo "<hr />". print_r($in,true) ."<hr /> ";
		foreach ( $in as $key => $val ) {
			$val=trim($val," ");
			if (preg_match ( "/^SW_/", $key )) {
				//Start with
				$skey = preg_replace ( "/^SW_/", "", $key );
				if ($where != '')
				$where .= " and ";
				$where .= "lower($skey) like lower(:sw_{$skey}||'%')";
				$binded_vars["sw_".$skey]=$val;
			}
			if (preg_match ( "/^S_/", $key )) {
				$key = preg_replace ( "/^S_/", "", $key );
				if (preg_match ( "/^FROM_DT_/", $key )) {
					$key = preg_replace ( "/^FROM_DT_/", "", $key );
					$trovato = false;

					for($i = 0; $i < count ( $this->cols ); $i ++) {
						if ($this->cols [$i] ['NOME'] == $key)
						$trovato = true;
					}
					if ($trovato) {
						$val_to = $in ['S_TO_DT_' . $key];
						
						if ($val != '' and $val_to != '') {
							$val = preg_replace ( "/\//", "", $val );
							$val_to = preg_replace ( "/\//", "", $val_to );
							if ($where != '')
							$where .= " and ";
							$where .= "$key between to_date(:search_from_{$key}, 'DDMMYYYY') and to_date(:search_to_{$key}, 'DDMMYYYY')+1";
							$binded_vars['search_from_'.$key]=$val;
							$binded_vars['search_to_'.$key]=$val_to;
					}
					}
				} else {

					$trovato = false;
					
					for($i = 0; $i < count ( $this->cols ); $i ++) {
						if ($this->cols [$i] ['NOME'] == $key)
						$trovato = true;

					}
					if ($trovato && $val != '') {
						// $val = preg_replace ( "/à/", "a'", $val );
						// $val = preg_replace ( "/è/", "e'", $val );
						// $val = preg_replace ( "/ì/", "i'", $val );
						// $val = preg_replace ( "/ò/", "u'", $val );
						// $val = preg_replace ( "/ù/", "o'", $val );
						$val = preg_replace ( "/\\'/", "''", $val );
						if ($where != '' && $in ['oper'] == '')
						$where .= " and ";
						if ($where != '' && $in ['oper'] != '')
						$where .= " {$in['oper']} ";
						if ($val == 'null')
						$where .= " $key is null";
						else
						$where .= "lower($key) like lower('%'||:search_{$key}||'%')";
						$binded_vars["search_".$key]=$val;
					}
				}
			}
			if (preg_match ( "/^S2_/", $key )) {
				$key = preg_replace ( "/^S2_/", "", $key );
				if (preg_match ( "/^FROM_DT_/", $key )) {
					$key = preg_replace ( "/^FROM_DT_/", "", $key );
					$trovato = false;

					for($i = 0; $i < count ( $this->cols ); $i ++) {
						if ($this->cols [$i] ['NOME'] == $key){
						$trovato = true;
						break;
						}
					}
					if ($trovato) {
						$val_to = $in ['S_TO_DT_' . $key];
						
						if ($val != '' and $val_to != '') {
							$val = preg_replace ( "/\//", "", $val );
							$val_to = preg_replace ( "/\//", "", $val_to );
							if ($where != '')
							$where .= " and ";
							$where .= "{$this->cols [$i] ['VAR']} between to_date(:search_from_{$key}, 'DDMMYYYY') and to_date(:search_to_{$key}, 'DDMMYYYY')+1";
							$binded_vars['search_from_'.$key]=$val;
							$binded_vars['search_to_'.$key]=$val_to;
					}
					}
				} else {

					$trovato = false;
					
					for($i = 0; $i < count ( $this->cols ); $i ++) {
						if ($this->cols [$i] ['NOME'] == $key){
						$trovato = true;
						break;
						}

					}
					if ($trovato && $val != '') {
						// $val = preg_replace ( "/à/", "a'", $val );
						// $val = preg_replace ( "/è/", "e'", $val );
						// $val = preg_replace ( "/ì/", "i'", $val );
						// $val = preg_replace ( "/ò/", "u'", $val );
						// $val = preg_replace ( "/ù/", "o'", $val );
						$val = preg_replace ( "/\\'/", "''", $val );
						if ($where != '' && $in ['oper'] == '')
						$where .= " and ";
						if ($where != '' && $in ['oper'] != '')
						$where .= " {$in['oper']} ";
						if ($val == 'null')
						$where .= " $key is null";
						else
						$where .= "lower({$this->cols [$i] ['VAR']}) like lower('%'||:search_{$key}||'%')";
						//echo $where;
						$binded_vars["search_".$key]=$val;
					}
				}
			}
			if (preg_match ( "/^IN_S_/", $key )) {
				$key = preg_replace ( "/^IN_S_/", "", $key );
				if ($where != '' && $in ['oper'] == '')
				$where .= " and ";
				$split='';
				/*
				 * Prima di splittare sulla virgola controlliamo che il parametro passato non sia del tipo
				 * 
				 */
				if (preg_match("!'!", $val)){ 
					//$val=preg_replace("!'(.*?)'!e",  "str_replace(',','###virgola###','\\1')", $val);
					$val=preg_replace_callback ( "!'(.*?)'!", function($matches){return str_replace(',','###virgola###', $matches[1]);}, $val );
				}
				
				$split=explode(",", $val);
				$ins='';
				foreach ($split as $h=>$w){
					$w=preg_replace("!^'!", "",$w);
					$w=preg_replace("!'$!", "",$w);
					$w=str_replace("###virgola###", ",", $w);
					$binded_vars['in_s_'.$key.'_'.$h]=$w;
					if ($ins!='') $ins.=",";
					$ins.=':in_s_'.$key.'_'.$h;
				}
				$where .= "$key in ($ins)";
			}
			if (preg_match ( "/^IN_S2_/", $key )) {
				$key = preg_replace ( "/^IN_S2_/", "", $key );
				unset($curr_index);
				for($i = 0; $i < count ( $this->cols ); $i ++) {
						if ($this->cols [$i] ['NOME'] == $key){
							$curr_index = $i;
							break;
						}
				}
				if(isset($curr_index)){
					if ($where != '' && $in ['oper'] == '')
					$where .= " and ";
					$split='';
				if (preg_match("!'!", $val)){
					//$val=preg_replace("!'(.*?)'!e",  "str_replace(',','###virgola###','\\1')", $val);
					$val=preg_replace_callback ( "!'(.*?)'!", function($matches){return str_replace(',','###virgola###', $matches[1]);}, $val );
				}
				$split=explode(",", $val);
				$ins='';
				foreach ($split as $h=>$w){
					$w=preg_replace("!^'!", "",$w);
					$w=preg_replace("!'$!", "",$w);
					$w=str_replace("###virgola###", ",", $w);
					$binded_vars['in_s2_'.$key.'_'.$h]=$w;
					if ($ins!='') $ins.=",";
					$ins.=':in_s2_'.$key.'_'.$h;
				}
					$where .= "{$this->cols [$i] ['VAR']} in ($ins)";
				}
			}
		}
		//die ($where);
		$replaceRet=query::varGlobReplace($where);
		$where=$replaceRet['sql'];
		//die ($where);
		foreach ($replaceRet['binded'] as $key=>$val){
			$binded_vars[$key]=$val;
		}
		if ($where != '')
		$query .= " where $where";
		if ($group_by != '')
		$query .= " group by $group_by";
		if ($order_by != '')
		$query .= " order by $order_by";
		$query = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $query );
		/**DEBUG OLD WAY**/

		if ($this->page!=''){
			$sql_count="select count(*) as conto from ($query)";
			$sql = new query ( $conn );
			//var_dump ($binded_vars);
			//var_dump ($GLOBALS);
			$sql->get_row($sql_count, $binded_vars);
			$conto=$sql->row['CONTO']-0;
			$npages=ceil($conto/$this->rpp);
			$first=(($this->page-1)*$this->rpp)+1;
			if ($conto > $this->rpp) $last=$this->page*$this->rpp;
			if ($conto <= $this->rpp) $last=$conto;
			$pages=21;
			$first_page_bar=$this->page-(($pages-1)/2);
			if ($first_page_bar<=0) $first_page_bar=1;
			$last_page_bar=$first_page_bar+($pages-1);
			if ($last_page_bar>$npages){
				$last_page_bar=$npages;
				$first_page_bar=$last_page_bar-($pages-1);
				if ($first_page_bar<=0) $first_page_bar=1;
			}
			$url_base="index.php?";
			$prev_page=$this->page-1;
			$next_page=$this->page+1;
			foreach ($_GET as $key => $val){
				if ($key!='PAGE') $url_base.=urlencode($key)."=".urlencode($val)."&";
			}
			foreach ($_POST as $key => $val){
				if ($key!='PAGE' && $key!='form' && $key!='ESAM') $url_base.=urlencode($key)."=".urlencode($val)."&";
			}

			if ($this->page!=1){
				$navigation_bar.="<li><a href=\"{$url_base}PAGE=1\"><i class=\"icon-double-angle-left\"></i></a></li>&nbsp;<li><a href=\"{$url_base}PAGE=$prev_page\"><i class=\"icon-angle-left\"></i></a></li>";
			}
			if ($first_page_bar!=1){
				//$navigation_bar.="...";
			}
			for ($i=$first_page_bar;$i<=$last_page_bar;$i++){
				if ($i==$this->page) $navigation_bar.=" <li class=\"active\"><a href=\"#\">$i</a></li>";
				else $navigation_bar.="<li><a href=\"{$url_base}PAGE=$i\">$i</a></li>";
			}

			if ($last_page_bar!=$npages){
				//$navigation_bar.="...";
			}
			if ($this->page!=$npages){
				$navigation_bar.="<li><a href=\"{$url_base}PAGE=$next_page\"><i class=\"icon-angle-right\"></i></a></li>&nbsp;<li><a href=\"{$url_base}PAGE=$npages\"><i class=\"icon-double-angle-right\"></i></a></li>";
			}
			
			/* Se siamo nell'ultima pagina il "to"($last) corrisponde al numero di risultati */
			if($_GET['PAGE'] == $last_page_bar){
				$last=$conto;
			}else{
				$last=$this->page*$this->rpp;
			}
			
			if($this->config_service ['lang'] == "en"){
				$specchietto_riassuntivo="
				Total Number of Records: <b>$conto</b><br>
				Records displayed on this page from <b>$first</b> to <b>$last</b><br>
				Go to page (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Go' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Warning! Please, select page in the range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				";
			}else{
				$_GET['PAGE']=htmlentities($_GET['PAGE']);
				$specchietto_riassuntivo="
				Numero totale records: <b>$conto</b><br>
				Record mostrati in questa pagina dal <b>$first</b> al <b>$last</b><br>
				Vai a pagina (1-$npages): <input type='text' style='width: 50px;' id='to_page' value=\"{$_GET['PAGE']}\">
				
				<!--input type='button' value='Vai' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Attenzione! Selezionare una pagina nel range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\"-->
				
				<button class=\"btn btn-xs btn-info\" type=\"button\" onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Attenzione! Selezionare una pagina nel range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				<i class=\"fa fa-arrow-right\"></i>
				</button>
				";	
			}
			
			$query="select * from (select t.*, rownum as n_r from ($query) t) where n_r between $first and $last";
			#GC 20/11/2015 NUOVA_GRAFICA
			//$html="$specchietto_riassuntivo<p align=center>$navigation_bar</p>$html";
			$html="<div style=\"margin-bottom: 0px;\" class=\"well well-sm\">$specchietto_riassuntivo</div><div style=\"text-align: center\"><ul class=\"pagination\">$navigation_bar</ul></div>$html";
		}
		
		$this->sql = new query ( $conn );
		$this->sql->exec ($query, $binded_vars); //binded
		if ($this->count_items) {
			$this->n_item_returned = $this->sql->numrows;
			$html = "<p align=center style='font-size:14px'>$this->presenti_string <b>{$this->n_item_returned}</b> {$this->items_name}</p>" . $html;
		}

		$tot = 0;
		while ( $this->sql->get_row () ) {
			if ($this->list ['TOTALE'] != '')
			$tot += $this->sql->row [strtoupper ( $this->list ['TOTALE'] )];
			$this->empty = false;
			$html .= "\n<tr>";
			for($i = 0; $i < count ( $this->cols ); $i ++) {
				$txt = "";
				$function_to_call = "col_td_" . $this->cols [$i] ['TIPO'];
				if (method_exists ( $this, $function_to_call ))
				$txt .= "\n" . $this->{$function_to_call} ( $i );
				if ($this->cols [$i] ['SCRIPT'] != '') {
					$link = $this->col_script ( $i );
					$txt = $link . $txt . "</a>";
				}
				if ($txt != '')
				$html .= "<td class=\"sc4bis\" {$this->cols [$i] ['ALIGN']}>$txt</td>";
			}
			$html .= "</tr>";
		}
		if (isset ( $in ['CODPAT'] )) {
			$param = "CODPAT=" . $in ['CODPAT'];
			$txt;
		}
		$param .= "&amp;CENTER=" . $in ['CENTER'];
		if ($in ['v_list'] == '') {
			//if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Lista Pazienti</a></p>";
			//else  $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Lista Pazienti</a></p>";
		}
		if ($this->list ['TOTALE'] != '') {
			$colsp = count ( $this->cols ) - 3;
			if($this->config_service ['lang'] != "en"){
				$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Totale</b></td>";
			}else{
				$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Total</b></td>";
			}

			$html .= "<td class=\"sc4bis\"><b>$tot</b></td>
				 <td class=\"sc4bis\"></td>
				 </tr>
				";
		}
		$html .= "</table>";
//echo $html."<hr>";
//echo "<!--$query-->";
		return $html;

	}

	function col_td_carica($i) {
		global $in;
		if ($this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )] == ' ' || $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )] == '') {
			$value = "<input type='button' onclick=\"window.location.href=window.location.href+'&ID_PRAT={$this->sql->row[$this->cols[$i]['PK']]}&CARICA'\" value='Prendi in carico'>";
		} else
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['NOME'] )];
		return $value . "&nbsp;";
	}

	function col_th_carica($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_th_studio_simple_text($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_td_studio_simple_text($i) {
		$this->cols [$i];
		$value = $this->sql->row [strtoupper ( $this->cols [$i] ['STUDIO'] )];
		if($value>0){
			$field=$this->cols [$i] ['ENROLLED_TEXT'];
		}

		return $field ;
	}

	function col_th_all_substudies($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_td_all_substudies($i) {
		/**
		 *  Al momento viene ricreato tale oggetto in futuro tale oggetto dovrà essere passato
		 */
		global $conn;
		$this->conn=$conn;
//		print_r($this->conn);
		$xmr = new xmrwf ( "study.xml", $this->conn );
		//		print_r($xmr->substudies);

		foreach ($xmr->substudies as $curr_study ){
			$str="select count(*) conto from {$curr_study->configurations['PREFIX']}_coordinate where  {$curr_study->configurations['PK_SERVICE']}='{$this->sql->row[$curr_study->configurations['PK_SERVICE']]}'";
			// print($str);
			$sql=new query($this->conn);
			$sql->get_row($str);
			if($this->cols[$i]['GO_BACK'])$this->cols[$i]['SCRIPT']="../".$curr_study->configurations['PREFIX']."/index.php";
			else $this->cols[$i]['SCRIPT']=$curr_study->configurations['PREFIX']."/index.php";
			$link=$this->col_script($i);
			if($sql->row['CONTO']>0) $ret.="<p>$link".$curr_study->workflow['DESCR']."&nbsp;&gt;&gt;</a></p>";
		}

		return $ret ;
	}

	function col_th_service_visit($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}

	function col_td_service_visit($i) {
		/**
		 *  Al momento viene ricreato tale oggetto in futuro tale oggetto dovrà essere passato
		 */
		global $conn;
		$this->conn=$conn;
//		print_r($this->conn);

		//		print_r($xmr->substudies);


			$str="select
								max(inizio) inizio,
								min(nvl(fine,0)) fine,
								min(nvl(visitclose,0)) visitclose,
								max(abilitato) abilitato
							from " . $this->cols [$i]['SERVICE'] . "_COORDINATE
							where " . $this->cols [$i]['SERVICE'] . "_COORDINATE.visitnum in ({$this->cols [$i]['VISITNUM']}) and
							{$this->config_service ['PK_SERVICE']}='{$this->sql->row [$this->config_service ['PK_SERVICE']]}'

							" ;
			$sql=new query($this->conn);
			$sql->get_row($str);
			$this->cols[$i]['SCRIPT']=$this->cols [$i]['DIR']."index.php";
			$link=$this->col_script($i);

			switch ($sql->row['ABILITATO']){
				case '1':
					switch ($sql->row['INIZIO']){
						case '1':
							switch($sql->row['VISITCLOSE']){
								case '1':
									$flag="f_verde.gif";
									break;
								case '':
								case '0':
									switch($sql->row['FINE']){
										case '1':
											$flag="f_verde.gif";
											break;
										case '':
										case '0':
											$flag="f_gialla.gif";
											break;
									}
									break;
							}
							break;
						case '':
						case '0':
						default:
						$flag="f_bianca.gif";
						break;
					}
					break;
				case '':
				case '0':
				default:
					$flag="";
					break;
			}

			if($flag!='') $ret.="$link<img src=\"/images/$flag\" border=0></a>";


		return $ret ;
	}

}

?>
