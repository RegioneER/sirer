<?php
//ini_set("display_errors",1);
//error_reporting(E_ALL);

define ("JQGID","_id_");
//DB UTILITIES
function _data_load($select, $select_count, $bind=array(), $order_override=array()){
    $count_query=db_query_bind($select_count, $bind);
    $count=0;
    while ($row = db_nextrow($count_query)){
        $count=$row['CONTO'];
    }
    //Se sidx è vuoto, allora imposto USERID di default? (1a colonna)
    if ($_GET['sidx']) {
        //$order_override è key-value pair array, dove la key è cosa mi arriva e il value cosa diventa.
        foreach ($order_override as $orkey => $orval) {
            if ($_GET['sidx'] == $orkey) {
                $_GET['sidx'] = $orval;
            }
        }
        if ($_GET['sord']){
            $select .= " ORDER BY {$_GET['sidx']} {$_GET['sord']}";
        }
    }
    //Il paginatore se il caricamento è lato server, ci vuole.
    if(isset($_GET['page']) && $_GET['page']!="" && isset($_GET['rows']) && $_GET['rows']!=""){
        $first= ($_GET['page'] - 1) * $_GET['rows']+1;
        $last= (($_GET['page'] - 1) * $_GET['rows'])+$_GET['rows'];

        $select="SELECT * FROM (
		SELECT t.*,rownum as n_r FROM(
				".$select."
			) t
		) t2 WHERE t2.n_r BETWEEN ".$first." AND ".$last;
        //echo $select;
    }
    //Fine paginatore
    $rs = db_query_bind($select,$bind);
    $retval = array();
    $retval['COUNT']=$count;
    $retval['DATASET']=$rs;
    return $retval;
}

function JqGridFilter2SqlBinded($filters){
	$op=$filters->groupOp;
	$sqlwhere="";
	foreach ($filters->rules as $key=>$val){
		switch ($val->op){
			case 'cn':
				$clause="UPPER(".$val->field.") like '%'||:JQF_{$val->field}||'%'";
				$bind["JQF_{$val->field}"]=strtoupper($val->data);
				break;
		}
		if ($sqlwhere!='') $sqlwhere.=" ".$op." ";
		$sqlwhere.=$clause;	
	}
	
	$ret['where']=$sqlwhere;
	$ret['bind']=$bind;
	return $ret;
}

function _data_parse($data, $count, $jqGrid){
    if($jqGrid) {
    	$rows=1;
		$page=1;
    	if(isset($_GET['rows'])){
    		$rows=$_GET['rows'];
    	}
		if(isset($_GET['page'])){
    		$page=$_GET['page'];
    	}

		header('Content-Type: application/json');
        echo json_encode(array('rows'=>$rows,'page'=>$page,'total'=>$count, 'root'=>$data));
        die();
    }
    if(isAjax()){
        //if($jqGrid){
        //		echo json_encode(array('rows'=>$_GET['rows'],'page'=>$_GET['page'],'total'=>$count, 'root'=>$retval));
        //}
        //else{
    	header('Content-Type: application/json');
        echo json_encode(array_merge(array("sstatus" => "ok"), $data));
        //}
        die();
    }
    return; // $data;
}
function _data_actions($actions, $row){
    $output = "";
    foreach ($actions as $a){
        $l = $a['LINK'];
        foreach ($row as $column=>$value){
            if (!is_object($value)){
            $l = str_replace("[{$column}]",$value,$l); //standard
            $l = str_replace("%5B{$column}%5D",$value,$l); //urlencodato
        }
        }
        $c = (isset($a['COLOR'])?$a['COLOR']:false);
        $t = (isset($a['TARGET'])?$a['TARGET']:null);
        $o = (isset($a['ONCLICK'])?$a['ONCLICK']:false);
        $show = true;
        if ($a['NOT_CONDITION']){
            $cond = $a['NOT_CONDITION'];
            foreach ($row as $column=>$value){
                $cond = str_replace("[{$column}]",$value,$cond); //standard
                $cond = str_replace("%5B{$column}%5D",$value,$cond); //urlencodato
            }
            if (strpos($cond,"|")===false) {
                if ($cond) {
                    $show = false;
                }
            }else{
                $cspl = explode("|",$cond);
                foreach ($cspl as $cc){
                    if ($cc){
                        $show = false;
                    }
                }
            }
        }
        if ($a['CONDITION']){
            $cond = $a['CONDITION'];
            foreach ($row as $column=>$value){
                $cond = str_replace("[{$column}]",$value,$cond); //standard
                $cond = str_replace("%5B{$column}%5D",$value,$cond); //urlencodato
            }
            if (strpos($cond,"|")===false) {
                if (!$cond) {
                    $show = false;
                }
            }else{
                $cspl = explode("|",$cond);
                foreach ($cspl as $cc){
                    if (!$cc){
                        $show = false;
                    }
                }
            }
        }
        if ($a['COLOR_CONDITION']){
            $cspl = explode("|",$a['COLOR_CONDITION']);
            $cond = $cspl[0];
            foreach ($row as $column=>$value){
                $cond = str_replace("[{$column}]",$value,$cond); //standard
                $cond = str_replace("%5B{$column}%5D",$value,$cond); //urlencodato
            }
            if (!$cond){
                $c=$cspl[1];
            }
        }
        if($show){
        $output.=new Link(t($a['LABEL']), $a['ICON'], $l, $c, $t, $o);
        }
    }
    return $output;
}

function _data_retrieve($jqGrid,$select, $bind, $order_override=null, $pkeys=null, $checkicons=null, $actions=null, $assignpkey=null, $dynamic_actions = array())
{
    //Inserisco qui il filtro lato server
    if ($_GET['_search']=="true") {
        $ret = JqGridFilter2SqlBinded(json_decode($_GET['filters']));
        if ($ret['where'] != '') {
            $select = "select * from ({$select}) where " . $ret['where'];
            foreach ($ret['bind'] as $k => $v) {
                $bind[$k] = $v;
            }
        }
    }
    //la select_count la genero dalla select.
    //$fpos = stripos($select,"FROM");
    ////$sel = substr($select,0,$fpos);
    //$from = substr($select,$fpos);
    $select_count = "SELECT COUNT(*) AS CONTO FROM ($select)"; //.$from;
    //if ($_POST['_search']){
    //    //clausola search ipoteticamente anche qua?
    //}
    $data = _data_load($select, $select_count, $bind, $order_override);
    $rs = $data['DATASET'];
    $count = $data['COUNT'];
    $retval = array();
    while ($row = db_nextrow($rs)){
        if($jqGrid) {
            //aggiungo le azioni dinamiche recuperate dalla funzione $dafunc che utilizza per chiave il valore $dakey (tutto letto dall'array)
            $merged_actions = $actions;
            foreach ($dynamic_actions as $dakey => $dafunc) {
                if (function_exists($dafunc)) {
                    $merged_actions = array_merge($merged_actions, call_user_func_array($dafunc, array($row[$dakey])));
                }else{
                    $merged_actions = array_merge($merged_actions, array('LABEL' => 'Function '.$dafunc.' Not Found', 'ICON' => 'bomb', 'LINK' => '#'));
                }
            }
            foreach ($checkicons as $ifield) {
                if ($row[$ifield] == 1) {
                    $row[$ifield] = '<i class="bigger-150 fa fa-check-circle green"></i>';
                } else {
                    $row[$ifield] = '<i class="bigger-150 fa fa-times-circle red"></i>';
                }
            }
            $row['_ACTIONS_']=_data_actions($merged_actions,$row);
            $row[JQGID] = "";
            foreach ($pkeys as $pkey){
                if ($row[JQGID]){
                    $row[JQGID].="|";
                }
                $row[JQGID].=$row[$pkey];
            }
            $retval[] = $row;
        }else{
            if ($assignpkey){
                $pkass = "";
                foreach ($pkeys as $k){
                    if ($pkass != ""){
                        $pkass .= "|";
                    }
                    $pkass .= $row[$k];
                }
                $retval[$pkass] = $row;
            }else{
                $retval[] = $row;
            }
        }
    }
    _data_parse($retval, $count, $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
    return $retval;
}

//COMMON FUNCTIONS

function common_strOneLine($txt){
    $retval = str_replace("\r\n","\n",$txt);
    $retval = str_replace("\r","\n",$retval);
    $retval = str_replace("\n"," ",$retval);
    return trim($retval);
}


?>
