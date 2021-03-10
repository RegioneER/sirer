<?php
include_once "db_wl.inc";
function error_page($a, $b, $c){
    var_dump($a);
    var_dump($b);
    var_dump($c);
}

$prefix="DOC_";
global $conn1;
global $conn2;

if(!isset($_GET['orig'])) $_GET['orig']="devel";

switch($_GET['orig']){
    case 'devel':
        $conn1=new dbconn();
        break;
    case 'prep':
        $origDocRoot=$_SERVER['DOCUMENT_ROOT'];
        $_SERVER['DOCUMENT_ROOT']="/sissprep".$_SERVER['DOCUMENT_ROOT'];
        $conn1=new dbconn();
        $_SERVER['DOCUMENT_ROOT']=$origDocRoot;
        break;
    case 'prod':
        $origDocRoot=$_SERVER['DOCUMENT_ROOT'];
        $_SERVER['DOCUMENT_ROOT']="/sissprod".$_SERVER['DOCUMENT_ROOT'];
        $conn1=new dbconn();
        $_SERVER['DOCUMENT_ROOT']=$origDocRoot;
        break;
}

switch($_GET['dest']){
    case 'devel':
        $conn2=new dbconn();
        break;
    case 'prep':
        $origDocRoot=$_SERVER['DOCUMENT_ROOT'];
        $_SERVER['DOCUMENT_ROOT']="/sissprep".$_SERVER['DOCUMENT_ROOT'];
        $conn2=new dbconn();
        $_SERVER['DOCUMENT_ROOT']=$origDocRoot;
        break;
    case 'prod':
        $origDocRoot=$_SERVER['DOCUMENT_ROOT'];
        $_SERVER['DOCUMENT_ROOT']="/sissprod".$_SERVER['DOCUMENT_ROOT'];
        $conn2=new dbconn();
        $_SERVER['DOCUMENT_ROOT']=$origDocRoot;
        break;
}

function getConnection($type){
    global $conn1;
    global $conn2;
    if ($type=='orig'){
        return $conn1;
    }
    if ($type=='dest'){
        return $conn2;
    }

}
$conn1= new dbconn("GARAER_PREPROD","r4thu;1w","generici_dev");
$conn2= new dbconn("GARAER","gra3r24!01","generici_dev");
function createQueryObj($source){
    return new query(getConnection($source));
}

function getObjectTypes($source){
    $q=createQueryObj($source);
    $sql="select t.id, t.type_name, t.can_be_root, t.is_self_recursive, t.check_out_enabled, t.is_container, t.searchable, t.sortable, 
        t.title_regex, t.ftl_detail, t.ftl_form, t.can_have_file, t.no_file_info, t.file_on_fs ,
        f.name as title_field_name, tpl.name as title_template_name
        from doc_type t
        left join doc_md_field f on f.id=t.title_field_id
        left join doc_md_template tpl on tpl.id=f.template_id
        where t.deleted=0 
        order by type_name
        ";
    $q->exec($sql);
    $ret=[];
    while ($q->get_row()){
        $thisObj=$q->row;
        $sql2="select t.type_name from doc_type_doc_type dt, doc_type t where t.id=dt.allowedchilds_id and dt.doc_type_id={$q->row['ID']} order by t.type_name";
        $q2=createQueryObj($source);
        $q2->exec($sql2);
        unset($thisObj['ID']);
        $thisObj['children']=[];
        while ($q2->get_row()){
            $thisObj['children'][$q2->row['TYPE_NAME']]=true;
        }
        $sql2="select t.name, dt.enabled from doc_type_md_template dt, doc_md_template t where dt.type_id={$q->row['ID']} and t.id=dt.template_id order by t.name";
        $q2=createQueryObj($source);
        $q2->exec($sql2);
        $thisObj['templates']=[];
        while ($q2->get_row()){
            $thisObj['templates'][$q2->row['NAME']]=$q2->row['ENABLED'];
        }
        $ret[$q->row['TYPE_NAME']]=$thisObj;
    }
    return $ret;
}

function loadTemplates($source){
    $q=createQueryObj($source);
    $sql="select * from (select 
        t.name template_name, t.description template_description,
        t.is_auditable, f.name field_name, f.mandatory, f.type, f.type_filters, f.available_values, f.position, f.add_filter_fields, f.ext_dictionary, f.f_size, f.F_MACRO, f.f_macro_view, f.base_name_ora, f.cascade
        from doc_md_template t, doc_md_field f 
        where 
        t.deleted=0 and f.deleted=0 and
        f.template_id=t.id)
        order by template_name, field_name";
    $q->exec($sql);
    $ret=[];
    while ($q->get_row()){
        if ($ret[$q->row['TEMPLATE_NAME']]==null){
            $ret[$q->row['TEMPLATE_NAME']]=[];
            $ret[$q->row['TEMPLATE_NAME']]['description']=$q->row['TEMPLATE_DESCRIPTION'];
            $ret[$q->row['TEMPLATE_NAME']]['auditable']=$q->row['IS_AUDITABLE'];
            $ret[$q->row['TEMPLATE_NAME']]['fields']=[];
        }
        $ret[$q->row['TEMPLATE_NAME']]['fields'][$q->row['FIELD_NAME']]=$q->row;
        unset($ret[$q->row['TEMPLATE_NAME']]['fields'][$q->row['FIELD_NAME']]['TEMPLATE_DESCRIPTION']);
        unset($ret[$q->row['TEMPLATE_NAME']]['fields'][$q->row['FIELD_NAME']]['IS_AUDITABLE']);
        unset($ret[$q->row['TEMPLATE_NAME']]['fields'][$q->row['FIELD_NAME']]['TEMPLATE_NAME']);
    }
    return $ret;
}

function loadAclsType($source){
    $q=createQueryObj($source);
    $sql="select t.type_name, da.template_ftl, da.positional_ace, dac.authority, dac.container 
        from doc_acl da, doc_acl_container dac, doc_type t 
        where dac.acl_di=da.id and da.TYPE_ID = t.id and t.deleted=0
        order by dac.authority, dac.container";
    $q->exec($sql);
    while ($q->get_row()){
        if ($source=='orig'){
            global $origObj;
            if ($origObj[$q->row['TYPE_NAME']]['acls']==null){
                $origObj[$q->row['TYPE_NAME']]['acls']=[];
            }
            $acl=[];
            if ($q->row['AUTHORITY']==1){
                $acl['CONTAINER']="G:".$q->row['CONTAINER'];
            }else {
                $acl['CONTAINER']="U:".$q->row['CONTAINER'];
            }
            $acl['POLICY']=$q->row['POSITIONAL_ACE'];
            $acl['FTL']=$q->row['TEMPLATE_FTL'];
            $origObj[$q->row['TYPE_NAME']]['acls'][$acl['CONTAINER']."###".$acl['POLICY']]=$acl;
        }else {
            global $destObj;
            if ($destObj[$q->row['TYPE_NAME']]['acls']==null){
                $destObj[$q->row['TYPE_NAME']]['acls']=[];
            }
            $acl=[];
            if ($q->row['AUTHORITY']==1){
                $acl['CONTAINER']="G:".$q->row['CONTAINER'];
            }else {
                $acl['CONTAINER']="U:".$q->row['CONTAINER'];
            }
            $acl['POLICY']=$q->row['POSITIONAL_ACE'];
            $acl['FTL']=$q->row['TEMPLATE_FTL'];
            $destObj[$q->row['TYPE_NAME']]['acls'][$acl['CONTAINER']."###".$acl['POLICY']]=$acl;
        }
    }
}


function loadWFsType($source){
    $q=createQueryObj($source);
    $sql="select t.type_name, w.process_key, w.start_on_create, w.start_on_delete, w.start_on_update 
        from doc_type_wf w, doc_type t
        where w.type_id=t.id and w.enabled=1";
    $q->exec($sql);
    while ($q->get_row()){
        if ($source=='orig'){
            global $origObj;
            if ($origObj[$q->row['TYPE_NAME']]['wfs']==null){
                $origObj[$q->row['TYPE_NAME']]['wfs']=[];
            }
            $wf=[];
            $wf=$q->row;
            unset($wf['PROCESS_KEY']);
            unset($wf['TYPE_NAME']);
            $origObj[$q->row['TYPE_NAME']]['wfs'][$q->row['PROCESS_KEY']]=$wf;
        }else {
            global $destObj;
            if ($destObj[$q->row['TYPE_NAME']]['wfs']==null){
                $destObj[$q->row['TYPE_NAME']]['wfs']=[];
            }
            $wf=[];
            $wf=$q->row;
            unset($wf['PROCESS_KEY']);
            unset($wf['TYPE_NAME']);
            $destObj[$q->row['TYPE_NAME']]['wfs'][$q->row['PROCESS_KEY']]=$wf;
        }
    }
}



function loadAclsTplType($source){
    $q=createQueryObj($source);
    $sql="select t.type_name, tpl.name, da.positional_ace, dac.authority, dac.container from doc_tpl_acl da, doc_tpl_acl_container dac, doc_type_md_template tt, doc_md_template tpl, doc_type t
where dac.ACL_ID=da.id and da.ELEMENT_TYPE_ASSOC_TPL_ID=tt.id and t.id=tt.type_id and tpl.id=tt.template_id";
    $q->exec($sql);
    while ($q->get_row()){
        if ($source=='orig'){
            global $origObj;
            if ($origObj[$q->row['TYPE_NAME']]['aclTpls']==null){
                $origObj[$q->row['TYPE_NAME']]['aclTpls']=[];
            }
            $acl=[];
            if ($q->row['AUTHORITY']==1){
                $acl['CONTAINER']="G:".$q->row['CONTAINER'];
            }else {
                $acl['CONTAINER']="U:".$q->row['CONTAINER'];
            }
            $acl['POLICY']=$q->row['POSITIONAL_ACE'];
            $acl['TEMPLATE']=$q->row['NAME'];
            $origObj[$q->row['TYPE_NAME']]['aclTpls'][$acl['TEMPLATE']."##".$acl['CONTAINER']."###".$acl['POLICY']]=$acl;
        }else {
            global $destObj;
            if ($destObj[$q->row['TYPE_NAME']]['aclTpls']==null){
                $destObj[$q->row['TYPE_NAME']]['aclTpls']=[];
            }
            $acl=[];
            if ($q->row['AUTHORITY']==1){
                $acl['CONTAINER']="G:".$q->row['CONTAINER'];
            }else {
                $acl['CONTAINER']="U:".$q->row['CONTAINER'];
            }
            $acl['POLICY']=$q->row['POSITIONAL_ACE'];
            $acl['TEMPLATE']=$q->row['NAME'];
            $destObj[$q->row['TYPE_NAME']]['aclTpls'][$acl['TEMPLATE']."##".$acl['CONTAINER']."###".$acl['POLICY']]=$acl;
        }
    }
}

function check_diff_multi($array1, $array2){
    $result = array();
    foreach($array1 as $key => $val) {
        if(isset($array2[$key])){
            if(is_array($val) && $array2[$key]){
                $result[$key] = check_diff_multi($val, $array2[$key]);
            }else {
                if ($array2[$key]!=$array1[$key]){
                    $result[$key]=$val;
                }
            }
        } else {
            if ($val==null && $array2[$val]==null) {
            }else {
                $result[$key] = $val;
            }
        }
    }

    return $result;
}

$origObj=getObjectTypes("orig");
$destObj=getObjectTypes("dest");
global $origObj;
global $destObj;
loadAclsType("orig");
loadAclsType("dest");
loadAclsTplType("orig");
loadAclsTplType("dest");
loadWFsType("orig");
loadWFsType("dest");
$origTemplates=loadTemplates("orig");
$destTemplates=loadTemplates("dest");
echo "<h1>Confronto {$_GET['orig']} -> {$_GET['dest']}</h1>";


echo "<ul><h2>Configurazione Template:</h2>";

foreach ($origTemplates as $tplName=>$template) {
    if (isset($destTemplates[$tplName])) {
        $differenti = false;
        $diffs = check_diff_multi($origTemplates[$tplName], $destTemplates[$tplName]);
        $str = "";
        $str .= "<li><strong>$tplName</strong>";
        if ($diffs != null) {
            foreach ($diffs as $key=>$val) {
                if ($key != 'fields') {
                    $differenti = true;
                    $str .= "<ul><li><b>$key</b> - sorgente: {$origObj[$objName][$key]}-> destinazione: {$destObj[$objName][$key]}</li></ul>";
                } else {
                    if (count($diffs[$key])>0){
                        if ($key=='fields'){
                            foreach ($diffs[$key] as $childk=>$child){
                                if (count($child)>0){
                                    if ($destTemplates[$tplName]['fields'][$childk]==null){
                                        echo "<li>Campo <strong>{$tplName}.{$childk}</strong> - Non presente in destinazione</li>";
                                    }else {
                                        echo "<li>Template: <strong>$tplName</strong> - Campo <strong>$childk</strong>";
                                        foreach ($child as $k=>$v){
                                            echo "<ul><li><strong>$k</strong>: $v</li></ul>";
                                        }
                                        echo "</li>";
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }else {
        echo "<li>Template <strong>$tplName</strong> - Non esiste nella destinazione</li>";
    }
}
echo "</ul>";

echo "<ul><h2>Configurazione tipi:</h2>";

foreach ($origObj as $objName=>$obj){
    if (isset($destObj[$objName])){
        $differenti=false;
        $diffs=check_diff_multi($origObj[$objName], $destObj[$objName]);
        $str="";
        $str.="<li><strong>$objName</strong>";
        if ($diffs!=null){
            foreach ($diffs as $key=>$val){
                if ($key!='children' && $key!='templates' && $key!='acls' && $key!='aclTpls' && $key!='wfs'){
                    $differenti=true;
                    $str.= "<ul><li><b>$key</b> - sorgente: {$origObj[$objName][$key]}-> destinazione: {$destObj[$objName][$key]}</li></ul>";
                }else {

                    if (count($diffs[$key])>0){
                        if ($key=='children'){
                            $differenti=true;
                            $str.= "<ul><strong>Figli diversi:</strong>";
                            foreach ($diffs[$key] as $childk=>$child){
                                $str.= "<li>Figlio <strong>$childk</strong> mancante</li>";
                            }
                            $str.= "</ul>";
                        }
                        if ($key=='templates'){
                            $differenti=true;
                            $str.= "<ul><strong>Templates diversi:</strong>";
                            foreach ($diffs[$key] as $childk=>$child){
                                $str.= "<li>Template <strong>$childk</strong> mancante</li>";
                            }
                            $str.= "</ul>";
                        }
                        if ($key=='acls'){
                            $allAclDifferent=false;
                            $aclStr= "<ul><strong>ACL diverse:</strong>";
                            foreach ($diffs[$key] as $childk=>$child){
                                $aclSame=true;
                                $aclDiff= "<li>ACL:";
                                if (count($child)>0){
                                    $aclSame=false;
                                    foreach ($child as $k=>$v){
                                        $aclDiff.=" - $k=\"$v\"";
                                    }
                                }
                                $aclDiff.="</li>";
                                if (!$aclSame) {
                                    $allAclDifferent=true;
                                    $aclStr.=$aclDiff;
                                }
                            }
                            if ($allAclDifferent){
                                $differenti=true;
                                $str.= $aclStr."</ul>";
                            }

                        }
                        if ($key=='aclTpls'){
                            $allAclDifferent=false;
                            $aclStr= "<ul><strong>ACL TPL diverse:</strong>";
                            foreach ($diffs[$key] as $childk=>$child){
                                $aclSame=true;
                                $aclDiff= "<li>ACL:";
                                if (count($child)>0){
                                    $aclSame=false;
                                    foreach ($child as $k=>$v){
                                        $aclDiff.=" - $k=\"$v\"";
                                    }
                                }
                                $aclDiff.="</li>";
                                if (!$aclSame) {
                                    $allAclDifferent=true;
                                    $aclStr.=$aclDiff;
                                }
                            }
                            if ($allAclDifferent){
                                $differenti=true;
                                $str.= $aclStr."</ul>";
                            }

                        }
                        if ($key=='wfs'){
                            $allAclDifferent=false;
                            $aclStr= "<ul><strong>WF diverse:</strong>";
                            foreach ($diffs[$key] as $childk=>$child){
                                $aclSame=true;
                                $aclDiff= "<li>WF: <strong>$childk</strong>";
                                if (count($child)>0){
                                    $aclSame=false;
                                    foreach ($child as $k=>$v){
                                        $aclDiff.=" - $k=\"$v\"";
                                    }
                                }
                                $aclDiff.="</li>";
                                if (!$aclSame) {
                                    $allAclDifferent=true;
                                    $aclStr.=$aclDiff;
                                }
                            }
                            if ($allAclDifferent){
                                $differenti=true;
                                $str.= $aclStr."</ul>";
                            }

                        }
                    }
                }
            }
        }
        if (!$differenti) {
            $str.= " - UGUALI";
        }
        $str.= "</li>";
        if ($differenti) echo $str;
    }else {
        echo "<li><strong>$objName</strong> - Non esiste nella destinazione</li>";
    }
}

echo "</ul>";

