<?php
global $fieldAdded;

if (!isset($_POST["rep_prefix"]) || $_POST["rep_prefix"]=='') $_POST["rep_prefix"]='RP1';

function getTypes(){
	$types[0]="TEXTBOX";
	$types[1]="RICHTEXT";
	$types[2]="TEXTAREA";
	$types[3]="SELECT";
	$types[4]="RADIO";
	$types[5]="CHECKBOX";
	$types[6]="DATE";
	$types[7]="ELEMENT_LINK";
	$types[8]="EXT_DICTIONARY";
	$types[9]="PLACE_HOLDER";
	return $types;
}

function getObjectStruct($parentId=null){
	
	if ($parentId!=null) {
		if (isset($_SESSION["xcmd-struct"][$parentId]) && count($_SESSION["xcmd-struct"][$parentId])>0) return $_SESSION["xcmd-struct"][$parentId];
		$sql="select * from doc_type where id in (select dd.allowedchilds_id from doc_type_doc_type dd where dd.doc_type_id=$parentId) and deleted!=1 order by type_name asc";
	}
	else {
		if (isset($_SESSION["xcmd-global-struct"]) && count($_SESSION["xcmd-global-struct"])>0) return $_SESSION["xcmd-global-struct"];
		$sql="select * from doc_type where can_be_root=1 and deleted!=1 order by type_name asc";
	}
	$conn=getConnection();
	$q=new query($conn);
	$q->exec($sql);
	$ret=[];
	while ($q->get_row()){
		$ret[]=getElementDetails($q->row['TYPE_NAME'], $q->row['ID']);
	}
	if ($parentId!=null) {
		$_SESSION["xcmd-struct"][$parentId]=$ret;
	}else {
		$_SESSION["xcmd-global-struct"]=$ret;
	}
	return $ret;
}


function getElementDetails($elTypeName, $elementTypeId){
	if (isset($_SESSION["el"][$elTypeName])) return $_SESSION["el"][$elTypeName];
	$el['name']=$elTypeName;
	$el['id']=$elementTypeId;
	$el['fields']=getFieldsByElementType($elTypeName, $elementTypeId);
	$children=getObjectStruct($elementTypeId);
	if (count($children)>0) $el['children']=$children;
	$_SESSION["el"][$elTypeName]=$el;
	return $el;
}

function getFieldsByElementType($elTypeName, $elementTypeId){
	if (isset($_SESSION["el-fields"][$elTypeName])) return $_SESSION["el-fields"][$elTypeName];
	$conn=getConnection();
	$q2=new query($conn);
	$sql2="select dmt.id as template_id, dmt.name as template_name, dmf.id as field_id, dmf.name as field_name, dmf.type as ftype from doc_type_md_template dtmt, doc_md_template dmt, doc_md_field dmf
	where
	dmf.template_id = dmt.id
	and dmf.deleted<>1
	and dtmt.template_id=dmt.id
	and dtmt.type_id={$elementTypeId}
	and dmf.deleted<>1
	order by dmt.name, dmf.position";
	$q2->exec($sql2);
	while ($q2->get_row()){
		$_SESSION['field-types'][$q2->row['TEMPLATE_NAME']][$q2->row['FIELD_NAME']]=$q2->row['FTYPE'];
		$f['name']=$q2->row['FIELD_NAME'];
		$f['field_id']=$q2->row['FIELD_ID'];
		$f['template_id']=$q2->row['TEMPLATE_ID'];
		$f["type"]=getTypes()[$q2->row['FTYPE']];
		$ret[$q2->row['TEMPLATE_NAME']][]=$f;
	}
	$_SESSION["el-fields"][$elTypeName]=$ret;
	return $ret;
}

function buildReportAction($params){
	$tbPaths=[];
	$tbFields=[];
	foreach ($params['fields'] as $field){
		if (isset($params[str_replace(".", "_", $field)])) {
			$fe1=explode("_", $field);
			$last="";
			$fe=[];
			foreach ($fe1 as $k=>$val){
				if ($last!=$val) $fe[]=$val;
				$last=$val;
			}
			$tbPath=$fe[0];
			$fieldPath=$fe[1];
			$tbPathExplode=explode(".", $tbPath);
			$fieldExplode=explode(".", $fieldPath);
			$thisTbPath=recursiveTbPath($tbPathExplode); 
			$tbPaths=array_merge_recursive($tbPaths, $thisTbPath);
			if (count($fe)>2){
				$fieldSpec['alias']=$params[str_replace(".", "_", $field)];
				$fieldSpec['type']="linked";
				$idx=2;
				$nlevel=0;
				while ($idx<count($fe)){
					$fieldSpec['linkedEl'][$nlevel]=$fe[$idx];
					$fieldSpec['linkedField'][$nlevel]=$fe[$idx+1];
					$idx+=2;
					$nlevel++;
				}
				$tbFields[$tbPathExplode[count($tbPathExplode)-1]][$fieldExplode[0]][$fieldExplode[1]]['type']="linked";
				$tbFields[$tbPathExplode[count($tbPathExplode)-1]][$fieldExplode[0]][$fieldExplode[1]]["fields"][]=$fieldSpec;
			}else {
				$tbFields[$tbPathExplode[count($tbPathExplode)-1]][$fieldExplode[0]][$fieldExplode[1]]['alias']=$params[str_replace(".", "_", $field)];
				$tbFields[$tbPathExplode[count($tbPathExplode)-1]][$fieldExplode[0]][$fieldExplode[1]]['type']="std";
			}
		}
	}
	$masterTable=getMasterTable($tbPaths);
	//$sql=masterTbElementIdsQuery($masterTable);
	$slavePaths=getSlaveTablePaths($tbPaths);
	$sqlMaster=masterTbQuery($masterTable, $tbFields);
	foreach ($slavePaths as $key=>$val){
		slaveTbQuery($masterTable, $key, $val, $tbFields);
	}
	global $viewCreated;
	
	global $sqls;
	foreach ($sqls as $key=>$query){
		echo "<li>$key - <textarea cols='20' rows='2'>$query</textarea></li>";
	}
}

$sqls=[];

function appendToMasterTable($tail){
	$ret="";
	foreach ($tail as $k=>$v){
		$ret.=".".$k;
		if (is_array($v) && count($v)>0) $ret.=appendToMasterTable($v);
	}
	return $ret;
}
 
function slaveTbQuery($masterTable, $firstLevel, $slavePath, $tbFields){
	global $fieldAdded;
	global $viewCreated;
	$viewName="";
	for($i=0;$i<strlen($firstLevel);$i++){
		if ($firstLevel[$i]==strtoupper($firstLevel[$i])) $viewName.=$firstLevel[$i];
	}
	$masterTable.=".".$firstLevel;
	$masterTable.=appendToMasterTable($slavePath);
	$masterEls=explode(".",$masterTable);
	$fields="";
	$orders="";
	$joins="";
	$aliasTot="";
	$sqlIds=masterTbElementIdsQuery($masterTable);
	foreach ($masterEls as $el){
		if ($fields!="") $fields.=", ";
		$fields.="m.{$el}_id
		";
		if ($aliasTot!='') $aliasTot.=", ";
		$aliasTot.="{$el}_id";
		if ($orders!="") $orders.=", ";
		$orders.="m.{$el}_id
		";
		$linkedIdx=1;
		$linkedPaths=[];
		if (count($tbFields[$el])>0){
			foreach ($tbFields[$el] as $template=>$tail){
				foreach ($tail as $field=>$fieldSpec){
					if ($fieldAdded[$el][$template][$field]) continue;
					$alias=$fieldSpec['alias'];
					if ($fieldSpec['type']=='std'){
						if ($fields!="") $fields.=", ";
						$fields.="fieldvalue('$template', '$field', m.{$el}_id) as \"$alias\"";
						if ($aliasTot!='') $aliasTot.=", ";
						$aliasTot.=$alias;
						
						$fType=$_SESSION['field-types'][$template][$field];
						if ($fType==3 || $fType==4 || $fType==5){
							$fields.=", fieldvaluecode('$template', '$field', m.{$el}_id) as {$alias}_code
							";
							if ($aliasTot!='') $aliasTot.=", ";
							$aliasTot.=$alias."_code";
						}
					}else if ($fieldSpec['type']=='linked') {
						$linkedPaths[$el."|".$template."|".$field]['baseField']["element"]=$el;
						$linkedPaths[$el."|".$template."|".$field]['baseField']["template"]=$template;
						$linkedPaths[$el."|".$template."|".$field]['baseField']["field"]=$field;
						foreach ($fieldSpec["fields"] as $f){
							$level=1;
							foreach ($f['linkedEl'] as $idx=>$linkedEl){
								$linkedPaths[$el."|".$template."|".$field]["level_".$level]['key']=$linkedEl;
								if ($level==count($f['linkedEl'])) $linkedPaths[$el."|".$template."|".$field]["level_".$level][$linkedEl][$f['linkedField'][$idx]]=$f['alias'];
								else $linkedPaths[$el."|".$template."|".$field]["level_".$level][$linkedEl][$f['linkedField'][$idx]]=$f['linkedEl'][$idx+1]."_id";
								$level++;
							}
						}

					}
				}
					
			}
				
		}
	}
	$linkedQueries=[];
	foreach ($linkedPaths as $pathIdx=>$path){
		$appendFields=[];
		$tbBase=$path['level_1']['key'];
		$sql_linked="select
				fieldvalue('".$path['baseField']['template']."','".$path['baseField']['field']."', ".$path['baseField']['element']."_id) as ".$path['level_1']['key']."_id,
				".$path['baseField']['element']."_id from ($sqlIds)
				";
		$appendFields[strtoupper($path['baseField']['element']."_id")]=true;
		for ($i=1;isset($path["level_".$i]);$i++){
			$partial_sql="select
				";
			$appendAlias=[];
			foreach ($path["level_".$i][$path["level_".$i]['key']] as $fieldSpec=>$alias){
				$partial_sql.="fieldvalue('".explode(".",$fieldSpec)[0]."','".explode(".",$fieldSpec)[1]."',".$path["level_".$i]['key']."_id) as \"{$alias}\",
				";
				$appendAlias[strtoupper($alias)]=true;
			}
			$appendFields[strtoupper($path["level_".$i]['key']."_id")]=true;
			foreach ($appendFields as $key=>$val){
				$partial_sql.= " $key,";
			}
			foreach ($appendAlias as $key=>$val){
				$appendFields[$key]=$val;
			}
			$partial_sql=rtrim($partial_sql,",");
			$sql_linked=$partial_sql." from ($sql_linked)";
		}
		$linkedQueries[$pathIdx]=$sql_linked;
	}

	$masterSql="
	select
	{$fields}
	from
	(".$sqlIds.") m
	$joins
	order by $orders";
	
	global $sqls;
	
	$sqls["{$_POST["rep_prefix"]}_{$viewName}_JOIN_V"]="select {$aliasTot} from ($masterSql)";
	
	
	$sqlTot="
	create or replace view
	{$_POST["rep_prefix"]}_{$viewName}_JOIN_V as
	select
	{$fields}
	from
	(".$sqlIds.") m
	$joins
	order by $orders;
	";
	
	
	$conn=getConnection();
	$q=new query($conn);
	$masterTbName="{$_POST["rep_prefix"]}_{$viewName}_JOIN";
	$q->exec("create or replace view {$masterTbName}_V as $masterSql");
	$viewCreated[]=$masterTbName;
	$c=1;
	foreach ($linkedQueries as $idx=>$query){
		if (count($linkedQueries)>1) $subTbName="{$_POST["rep_prefix"]}_{$viewName}_{$c}";
		$subTbName="{$_POST["rep_prefix"]}_{$viewName}";
		$q->exec("create or replace view {$subTbName}_V as $query");
		$idx=str_replace("|", " -> ", $idx);
		$viewCreated[]=$subTbName;
		$sqls["{$subTbName}_V"]=$query;
		$sqlTot.="
		create or replace view {$subTbName}_V as
		$query;
		";
		$c++;
	}
	return $sqlTot;
}


function masterTbQuery($masterTable, $tbFields){
	global $fieldAdded;
	$masterEls=explode(".",$masterTable);
	$fields="";
	$orders="";
	$joins="";
	$sqlIds=masterTbElementIdsQuery($masterTable);
	$sqlIdsOuter=masterTbElementIdsQueryOuter($masterTable);
	foreach ($masterEls as $el){
		if ($fields!="") $fields.=", ";
		$fields.="m.{$el}_id
		";
		if ($aliasTot!='') $aliasTot.=", ";
		$aliasTot.="{$el}_id";
		if ($orders!="") $orders.=", ";
		$orders.="m.{$el}_id
		";
		$linkedIdx=1;
		$linkedPaths=[];
		if (count($tbFields[$el])>0){
			foreach ($tbFields[$el] as $template=>$tail){
				foreach ($tail as $field=>$fieldSpec){
					$fieldAdded[$el][$template][$field]=true;
					$alias=$fieldSpec['alias'];
					if ($fieldSpec['type']=='std'){
						if ($fields!="") $fields.=", ";
						$fields.="fieldvalue('$template', '$field', m.{$el}_id) as $alias";
						if ($aliasTot!='') $aliasTot.=", ";
						$aliasTot.="{$alias}";
						$fType=$_SESSION['field-types'][$template][$field];
						if ($fType==3 || $fType==4 || $fType==5){
							$fields.=", fieldvaluecode('$template', '$field', m.{$el}_id) as {$alias}_code
							";	
							if ($aliasTot!='') $aliasTot.=", ";
							$aliasTot.="{$alias}_code";
						}
					}else if ($fieldSpec['type']=='linked') {
						$linkedPaths[$el."|".$template."|".$field]['baseField']["element"]=$el;
						$linkedPaths[$el."|".$template."|".$field]['baseField']["template"]=$template;
						$linkedPaths[$el."|".$template."|".$field]['baseField']["field"]=$field;
						foreach ($fieldSpec["fields"] as $f){
							$level=1;
							foreach ($f['linkedEl'] as $idx=>$linkedEl){
								$linkedPaths[$el."|".$template."|".$field]["level_".$level]['key']=$linkedEl;
								if ($level==count($f['linkedEl'])) $linkedPaths[$el."|".$template."|".$field]["level_".$level][$linkedEl][$f['linkedField'][$idx]]=$f['alias'];
								else $linkedPaths[$el."|".$template."|".$field]["level_".$level][$linkedEl][$f['linkedField'][$idx]]=$f['linkedEl'][$idx+1]."_id";
								$level++;
							}
						}
						
					}
				}
				 
			}
			
		}
	}
	$linkedQueries=[];
	foreach ($linkedPaths as $pathIdx=>$path){
		$appendFields=[];
		$tbBase=$path['level_1']['key'];
		$sql_linked="select 
				fieldvalue('".$path['baseField']['template']."','".$path['baseField']['field']."', ".$path['baseField']['element']."_id) as ".$path['level_1']['key']."_id, 
				".$path['baseField']['element']."_id from ($sqlIds)
				";
		$appendFields[strtoupper($path['baseField']['element']."_id")]=true;
		for ($i=1;isset($path["level_".$i]);$i++){
			$partial_sql="select 
				";
			$appendAlias=[];
			foreach ($path["level_".$i][$path["level_".$i]['key']] as $fieldSpec=>$alias){
				$partial_sql.="fieldvalue('".explode(".",$fieldSpec)[0]."','".explode(".",$fieldSpec)[1]."',".$path["level_".$i]['key']."_id) as {$alias},
						";
				$appendAlias[strtoupper($alias)]=true;	
			}
			$appendFields[strtoupper($path["level_".$i]['key']."_id")]=true;
			foreach ($appendFields as $key=>$val){
				$partial_sql.= " $key,";
			}
			foreach ($appendAlias as $key=>$val){
				$appendFields[$key]=$val;
			}
			$partial_sql=rtrim($partial_sql,",");
			$sql_linked=$partial_sql." from ($sql_linked)";	
		}
		$linkedQueries[$pathIdx]=$sql_linked;
	}
	
	$masterSql="
	select 
		{$fields} 
	from 
		(".$sqlIds.") m 
		$joins 
	order by $orders";
	
	$masterSqlOuter="
		select
		{$fields}
		from
		(".$sqlIdsOuter.") m
		$joins
		order by $orders";
		
	global $sqls;
		
	$sqls["{$_POST["rep_prefix"]}_MASTER_V"]="select {$aliasTot} from ($masterSql)";
	$sqls["{$_POST["rep_prefix"]}_MASTER_V_O"]="select {$aliasTot} from ($masterSqlOuter)";
	
		
	$sqlTot="
	create or replace view 
	{$_POST["rep_prefix"]}_master as		
	select 
		{$fields} 
	from 
		(".$sqlIds.") m 
		$joins 
	order by $orders;
	";
		
	$conn=getConnection();
	$q=new query($conn);
	global $viewCreated;
	$masterTbName="{$_POST["rep_prefix"]}_master";
	$q->exec("create or replace view {$masterTbName}_V as $masterSql");
	$q->exec("create or replace view {$masterTbName}_V_O as $masterSqlOuter");
	$viewCreated[]=$masterTbName;
	$c=1;
	foreach ($linkedQueries as $idx=>$query){
		$slaveTbName="{$_POST["rep_prefix"]}_SLAVE_{$c}";
		$q->exec("create or replace view {$slaveTbName}_V as $query");
		$idx=str_replace("|", " -> ", $idx);
		
		$viewCreated[]=$slaveTbName;
		$sqls["{$slaveTbName}_V"]=$query;
		$sqlTot.="
		create or replace view 
		{$slaveTbName}_V as
		$query;
		";
		$c++;
	}
	return $sqlTot;
}

function masterTbElementIdsQuery($masterTable){
	$masterEls=explode(".", $masterTable);
	$i=count($masterEls)-1;
	$level=1;
	while ($i>=0){
		if ($level==1){
			$fields="l1.id as {$masterEls[$i]}_id";
			$from=" from doc_obj_view l1";
			$where="l1.type_name='{$masterEls[$i]}' and l1.deleted=0";
		}else {
			$fields.=", l{$level}.id as {$masterEls[$i]}_id";
			$precLevel=$level-1;
			$joins.="
			join doc_obj_view l{$level} on l{$level}.type_name='{$masterEls[$i]}' and l{$level}.id=l{$precLevel}.parent_id  and l{$level}.deleted=0";
		}
		$level++;
		$i--;
	}
	$sql="select {$fields} {$from} $joins
	where $where";
	return $sql;
}

function masterTbElementIdsQueryOuter($masterTable){
	$masterEls=explode(".", $masterTable);
	$maxCount=count($masterEls);
	$level=1;
	$i=0;
	while ($i<$maxCount){
		if ($level==1){
			$fields="l1.id as {$masterEls[$i]}_id";
			$from=" from doc_obj_view l1";
			$where="l1.type_name='{$masterEls[$i]}' and l1.deleted=0";
		}else {
			$fields.=", l{$level}.id as {$masterEls[$i]}_id";
			$precLevel=$level-1;
			$joins.="
			left join doc_obj_view l{$level} on l{$level}.type_name='{$masterEls[$i]}' and l{$level}.parent_id=l{$precLevel}.id  and l{$level}.deleted=0";
		}
		$level++;
		$i++;
	}
	$sql="select {$fields} {$from} $joins
	where $where";
	return $sql;
}

function recursiveTbPath($exploded){
	$ret=[];
	if (count($exploded)==0) return [];
	foreach ($exploded as $idx=>$tb){
		unset ($exploded[$idx]);
		$ret[$tb]=recursiveTbPath($exploded);
		break;
	}
	return $ret;
}

function getMasterTable($tbPaths, $first=true){
	if (count($tbPaths)>1) return "";
	else {
		foreach ($tbPaths as $tb=>$tail){
			if ($first) return $tb.getMasterTable($tail, false);
			else return ".".$tb.getMasterTable($tail, false);
		}
	}	
}

function getSlaveTablePaths($tbPaths){
	if (count($tbPaths)==0) return [];
	if (count($tbPaths)>1) return $tbPaths;
	else {
		foreach ($tbPaths as $tb=>$tail){
			return getSlaveTablePaths($tail);
		}
	}
}
