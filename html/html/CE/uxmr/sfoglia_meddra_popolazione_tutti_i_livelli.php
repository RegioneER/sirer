<?
include_once "config.inc";

//$conn = new dbconn ( "OSSC", "SSC0907!", "aifa_regolatori_prod" );

$conn = new dbconn ( );

$body="<p class=int>BancaDati MedDRA</p>";

$query['SOC']="select 
	distinct 
	'SOC' as LIVELLO_, 
	soc_code as CODICE, 
	soc_name as DECODIFICA 
	from md_hierarchy_91";
$query['HLGT']="select 
	distinct 
	soc_name as LIVELLO_SOC, 
	soc_code as COD_LIVELLO_SOC,
	'HLGT' as LIVELLO_, 
	HLGT_code as CODICE, 
	hlgt_name as DECODIFICA 
	from md_hierarchy_91";
$query['HLT']="select 
	distinct 
	soc_name as LIVELLO_SOC, 
	soc_code as COD_LIVELLO_SOC,
	hlgt_name as LIVELLO_HLGT, 
	hlgt_code as COD_LIVELLO_HLGT,
	'HLT' as LIVELLO_, 
	HLT_code as CODICE, 
	hlt_name as DECODIFICA 
	from md_hierarchy_91";
$query['PT']="select 
	distinct 
	soc_name as LIVELLO_SOC, 
	soc_code as COD_LIVELLO_SOC,
	hlgt_name as LIVELLO_HLGT,
	hlgt_code as COD_LIVELLO_HLGT, 
	hlt_name as LIVELLO_HLT,
	hlt_code as COD_LIVELLO_HLT,
	'PT' as LIVELLO_, 
	pt_code as CODICE, 
	pt_name as DECODIFICA 
	from md_hierarchy_91";
$query['LLT']="select 
	distinct 
	soc_name as LIVELLO_SOC, 
	soc_code as COD_LIVELLO_SOC,
	hlgt_name as LIVELLO_HLGT,
	hlgt_code as COD_LIVELLO_HLGT,  
	hlt_name as LIVELLO_HLT,
	hlt_code as COD_LIVELLO_HLT,
	pt_name as LIVELLO_PT,
	pt_code as COD_LIVELLO_PT,
	'LLT' as LIVELLO_, 
	LLT_code as CODICE, 
	llt_name as DECODIFICA 
	from md_hierarchy_91";


if ($_GET['MODE']=='SFOGLIA'){
	$action_link="sfoglia_meddra_popolazione_tutti_i_livelli.php?MODE=SFOGLIA&LIVELLO={$_GET['LIVELLO']}&CODICE={$_GET['CODICE']}&DESCRIZIONE={$_GET['DESCRIZIONE']}&L1=PATOLOGIAL1&L2=PATOLOGIAL2&L3=PATOLOGIAL3&L4=PATOLOGIAL4&L5=PATOLOGIAL5&DL1=D_PATOLOGIAL1&DL2=D_PATOLOGIAL2&DL3=D_PATOLOGIAL3&DL4=D_PATOLOGIAL4&DL5=D_PATOLOGIAL5";

	if (isset($_POST['SOC_CODE']) && $_POST['SOC_CODE']!='') $where['SOC']="SOC_CODE='{$_POST['SOC_CODE']}'";
	if (isset($_POST['HLGT_CODE']) && $_POST['HLGT_CODE']!='') $where['HLGT']="HLGT_CODE='{$_POST['HLGT_CODE']}'";
	if (isset($_POST['HLT_CODE']) && $_POST['HLT_CODE']!='') $where['HLT']="HLT_CODE='{$_POST['HLT_CODE']}'";
	if (isset($_POST['PT_CODE']) && $_POST['PT_CODE']!='') $where['PT']="PT_CODE='{$_POST['PT_CODE']}'";	
	$query_sql=$query['SOC'];
	if (isset($_POST['SOC_CODE']) && $_POST['SOC_CODE']!='') $query_sql=$query['HLGT'];
	if (isset($_POST['HLGT_CODE']) && $_POST['HLGT_CODE']!='') $query_sql=$query['HLT'];
	if (isset($_POST['HLT_CODE']) && $_POST['HLT_CODE']!='') $query_sql=$query['PT'];
	if (isset($_POST['PT_CODE']) && $_POST['PT_CODE']!='') $query_sql=$query['LLT'];
	foreach ($where as $key =>$val){
		if ($where_!='') $where_.=" and ";
		$where_.=$val;
	}
	if ($where_!='') $query_sql.=" where $where_";
	
	$res=tabella_risultati(0,$query_sql, $conn);
	$last_row=$res['last_row'];
	$tb_res=$res['tb'];
	$navigation_bar=navigation_bar($last_row, 0);
	$form_sfoglia=make_form(0,$action_link);	
	$tb_res="<table border=1>
		<tr>
			<th>Livello</th>
			<th>Codice</th>
			<th>Descrizione</th>
			<th>Seleziona</th>
		</tr>
	".$tb_res."</table>";
	$body.=$navigation_bar;
	$body.=$form_sfoglia;
	$body.=$tb_res;
}
if ($_GET['MODE']=='CERCA'){
	$action_link="sfoglia_meddra_popolazione_tutti_i_livelli.php?MODE=CERCA&LIVELLO={$_GET['LIVELLO']}&CODICE={$_GET['CODICE']}&DESCRIZIONE={$_GET['DESCRIZIONE']}&L1=PATOLOGIAL1&L2=PATOLOGIAL2&L3=PATOLOGIAL3&L4=PATOLOGIAL4&L5=PATOLOGIAL5&DL1=D_PATOLOGIAL1&DL2=D_PATOLOGIAL2&DL3=D_PATOLOGIAL3&DL4=D_PATOLOGIAL4&DL5=D_PATOLOGIAL5";
	$body.=make_form(0,$action_link,false);	
	if (isset($_POST['cerca'])){
		$action_link="sfoglia_meddra_popolazione_tutti_i_livelli.php?MODE=SFOGLIA&LIVELLO={$_GET['LIVELLO']}&CODICE={$_GET['CODICE']}&DESCRIZIONE={$_GET['DESCRIZIONE']}&L1=PATOLOGIAL1&L2=PATOLOGIAL2&L3=PATOLOGIAL3&L4=PATOLOGIAL4&L5=PATOLOGIAL5&DL1=D_PATOLOGIAL1&DL2=D_PATOLOGIAL2&DL3=D_PATOLOGIAL3&DL4=D_PATOLOGIAL4&DL5=D_PATOLOGIAL5";
		$i=1;
		foreach ($query as $key => $val){
			$keyword=strtoupper($_POST['PATTERN']);
			$keyword=str_replace("'", "%", $keyword);
			//echo $keyword;
			//die();
			$query_sql="select * from ($val) where upper(DECODIFICA) like '%".$keyword."%'";
			$body.=make_form($i, $action_link);
			$res=tabella_risultati($i,$query_sql, $conn);
			$last_row=$res['last_row'];
			$tb_res.=$res['tb'];
			$i++;
		}
		$tb_res="<table border=1>
		<tr>
			<th>Livello</th>
			<th>Codice</th>
			<th>Descrizione</th>
			<th>Seleziona</th>
		</tr>
	".$tb_res."</table>";
		$body.=$tb_res;
	}
}
	$filetxt = str_replace ( "<!--body-->", $body, $filetxt );
	die ($filetxt);
	
	function make_form($idx, $action_link, $sfoglia=true){
		if ($sfoglia) return "
		<form method='POST' name='sfoglia_form_$idx' action=\"$action_link\">
			<input type='hidden' name='SOC_CODE' value='{$_POST['SOC_CODE']}'>
			<input type='hidden' name='HLGT_CODE' value='{$_POST['HLGT_CODE']}'>
			<input type='hidden' name='HLT_CODE' value='{$_POST['HLT_CODE']}'>
			<input type='hidden' name='PT_CODE' value='{$_POST['PT_CODE']}'>
			<input type='hidden' name='LLT_CODE' value='{$_POST['LLT_CODE']}'>
		</form>
		";
		else return "
		<form method='POST' name='sfoglia_form_$idx' action=\"$action_link\">
			Cerca: <input type='text' name='PATTERN' value=\"{$_POST['PATTERN']}\">
			<input type='submit' name='cerca' value='Cerca'>
		</form>
		";
	}
	
	function tabella_risultati($idx, $sql_query, $conn){
		$sql=new query($conn);
		$sql->exec($sql_query);
		
		while ($sql->get_row()){
			
			$onclick_plus='';
			$nav='';
			foreach ($sql->row as $key=>$val){
				if (preg_match("!^COD_LIVELLO_!", $key) && $key!='LIVELLO_'){
					$livello=str_replace("COD_LIVELLO_", "", $key);
					$nav.="<li>$livello - $val</li>";
					$onclick_plus.="
					document.forms['sfoglia_form_$idx'].{$livello}_CODE.value='$val';
					";
				}
			}			
			if ($sql->row['LIVELLO_']=='LLT'){
				$value="{$sql->row['DECODIFICA']}";
			}
			
			else $value="
			<a href=\"#\" onclick=\"
					{$onclick_plus}
					document.forms['sfoglia_form_$idx'].{$sql->row['LIVELLO_']}_CODE.value='{$sql->row['CODICE']}';
					document.forms['sfoglia_form_$idx'].submit();
				\">{$sql->row['DECODIFICA']}</a>
			";
			$js_txt=str_replace("'", "\\'", $sql->row['DECODIFICA']);
			$sql->row['LIVELLO_SOC']=str_replace("'", "\\'", $sql->row['LIVELLO_SOC']);
			$sql->row['LIVELLO_HLGT']=str_replace("'", "\\'", $sql->row['LIVELLO_HLGT']);
			$sql->row['LIVELLO_HLT']=str_replace("'", "\\'", $sql->row['LIVELLO_HLT']);
			$sql->row['LIVELLO_PT']=str_replace("'", "\\'", $sql->row['LIVELLO_PT']);
			
			/*
			echo $sql->row['COD_LIVELLO_SOC']."<br>";
			echo $sql->row['COD_LIVELLO_HLGT']."<br>";
			echo $sql->row['COD_LIVELLO_HLT']."<br>";
			echo $sql->row['COD_LIVELLO_PT']."<br>";
			echo $sql->row['LIVELLO_']."<br>";
			echo $sql->row['CODICE']."<br>";
			echo $sql->row['DECODIFICA']."<br>";
			*/
			
			if($sql->row['LIVELLO_']=='SOC'){
				$L1=$sql->row['CODICE'];
				$DL1=$js_txt;
			}
			else{$L1=$_POST['SOC_CODE'];}
			
			if($sql->row['LIVELLO_']=='HLGT'){
				$L1=$sql->row['COD_LIVELLO_SOC'];
				$DL1=$sql->row['LIVELLO_SOC'];
				$L2=$sql->row['COD_LIVELLO_HLGT'];
				$DL2=$js_txt;
			}
			else{$L2=$_POST['HLGT_CODE'];}
			
			if($sql->row['LIVELLO_']=='HLT'){
				$L1=$sql->row['COD_LIVELLO_SOC'];
				$DL1=$sql->row['LIVELLO_SOC'];
				$L2=$sql->row['COD_LIVELLO_HLGT'];
				$DL2=$sql->row['LIVELLO_HLGT'];
				$L3=$sql->row['COD_LIVELLO_HLT'];
				$DL3=$js_txt;
			}
			else{$L3=$_POST['HLT_CODE'];}
			
			if($sql->row['LIVELLO_']=='PT'){
				$L1=$sql->row['COD_LIVELLO_SOC'];
				$DL1=$sql->row['LIVELLO_SOC'];
				$L2=$sql->row['COD_LIVELLO_HLGT'];
				$DL2=$sql->row['LIVELLO_HLGT'];
				$L3=$sql->row['COD_LIVELLO_HLT'];
				$DL3=$sql->row['LIVELLO_HLT'];
				$L4=$sql->row['COD_LIVELLO_PT'];
				$DL4=$js_txt;
			}
			else{$L4=$_POST['PT_CODE'];}
			
			if($sql->row['LIVELLO_']=='LLT') {
				$L1=$sql->row['COD_LIVELLO_SOC'];
				$DL1=$sql->row['LIVELLO_SOC'];
				$L2=$sql->row['COD_LIVELLO_HLGT'];
				$DL2=$sql->row['LIVELLO_HLGT'];
				$L3=$sql->row['COD_LIVELLO_HLT'];
				$DL3=$sql->row['LIVELLO_HLT'];
				$L4=$sql->row['COD_LIVELLO_PT'];
				$DL4=$sql->row['LIVELLO_PT'];
				$L5=$sql->row['CODICE'];
				$DL5=$js_txt;
			}
			
			$tb_res.="
			<tr>
				<td>{$sql->row['LIVELLO_']}</td>
				<td>{$sql->row['CODICE']}</td>
				<td>$value</td>
				
				<td><input type='button' value='&gt;&gt;' onclick=\"
					window.opener.document.forms[0].{$_GET['LIVELLO']}.value='{$sql->row['LIVELLO_']}';
					window.opener.document.forms[0].{$_GET['CODICE']}.value='{$sql->row['CODICE']}';
					window.opener.document.forms[0].{$_GET['DESCRIZIONE']}.value='{$js_txt}';
					window.opener.document.forms[0].{$_GET['L1']}.value='{$L1}';
					window.opener.document.forms[0].{$_GET['L2']}.value='{$L2}';
					window.opener.document.forms[0].{$_GET['L3']}.value='{$L3}';
					window.opener.document.forms[0].{$_GET['L4']}.value='{$L4}';
					window.opener.document.forms[0].{$_GET['L5']}.value='{$L5}';
					window.opener.document.forms[0].{$_GET['DL1']}.value='{$DL1}';
					window.opener.document.forms[0].{$_GET['DL2']}.value='{$DL2}';
					window.opener.document.forms[0].{$_GET['DL3']}.value='{$DL3}';
					window.opener.document.forms[0].{$_GET['DL4']}.value='{$DL4}';
					window.opener.document.forms[0].{$_GET['DL5']}.value='{$DL5}';
					
					window.close();
				\"></td>
			</tr>	
			";	
		}
		$res['tb']=$tb_res;
		$res['last_row']=$sql->row;
		return $res;
	}
	
	function navigation_bar($last_row, $idx){
	foreach ($last_row as $key=>$val){
		if (preg_match("!^LIVELLO_!", $key) && $key!='LIVELLO_'){
			$livello=str_replace("LIVELLO_","", $key);
			$navigation_bar.="<li>$livello: <b>$val</b></li>";	
		}
	}
	if ($navigation_bar!=''){
		$navigation_bar.="<p align=center><a href=\"#\" onclick=\"
		if (document.forms['sfoglia_form_$idx'].PT_CODE.value!=''){
			document.forms['sfoglia_form_$idx'].PT_CODE.value='';
			document.forms['sfoglia_form_$idx'].submit();
			return false;
		}
		if (document.forms['sfoglia_form_$idx'].HLT_CODE.value!=''){
			document.forms['sfoglia_form_$idx'].HLT_CODE.value='';
			document.forms['sfoglia_form_$idx'].submit();
			return false;
		}
		if (document.forms['sfoglia_form_$idx'].HLGT_CODE.value!=''){
			document.forms['sfoglia_form_$idx'].HLGT_CODE.value='';
			document.forms['sfoglia_form_$idx'].submit();
			return false;
		}
		if (document.forms['sfoglia_form_$idx'].SOC_CODE.value!=''){
			document.forms['sfoglia_form_$idx'].SOC_CODE.value='';
			document.forms['sfoglia_form_$idx'].submit();
			return false;
		}		
		\"
		>Torna al livello precedente</a></p>";
		}
		return $navigation_bar;
	}
?>