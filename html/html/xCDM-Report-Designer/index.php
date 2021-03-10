<?php
if (!isset($_SERVER['HTTPS'])){
	header("location: https://{$_SERVER['HTTP_HOST']}/xCDM-Report-Designer/");
}
require_once "config.inc.php";
include_once 'xcdm-libs.inc.php';
/*if ($_SERVER['REMOTE_USER'] != 'ADMIN') {
 error_page($_SERVER['REMOTE_USER'], "ERR", "Aggiornamenti");

 }*/

global $conn;
$conn=new dbconn();


$qBase1="CREATE OR REPLACE VIEW DOC_OBJ_VIEW AS 
  select d.id, t.type_name, t.id type_id, d.parent_id, d.deleted from doc_obj d, doc_type t 
where t.id=d.type_id";

$qBase2='
CREATE OR REPLACE VIEW DOC_OBJ_MD_VIEW ("TYPE_NAME", "TEMPLATE_NAME", "FIELD_NAME", "ELEMENT_ID", "CODE", "DECODE", "DATE_VALUE", "ELEMENT_LINK", "TXT_VALUE", "LONG_TXT_VALUE", "TEMPLATE_ID", "FIELD_ID", "MD_ID", "MDV_ID", "DELETED") AS 
  select dt.type_name,  t.name template_name, f.name field_name, md.element_id, mdv.code, mdv.decode, mdv.date_value, mdv.element_link, mdv.txt_value, mdv.long_txt_value, 
t.id as template_id, f.id as field_id, md.id md_id, mdv.id mdv_id, d.deleted as deleted
from doc_obj_md md, doc_obj_md_val mdv,
doc_md_field f, doc_md_template t, doc_obj d, doc_type dt
where md.FIELD_ID=f.id and md.TEMPLATE_ID=t.id and mdv.MD_ID=md.id
and d.id=md.element_id and dt.id=d.TYPE_ID';

$qBase3="
create or replace FUNCTION FIELDVALUE 
(
T_NAME IN VARCHAR2,
F_NAME IN VARCHAR2, 
E_ID IN VARCHAR2 
) RETURN VARCHAR2 AS 
retval varchar2(4000);
BEGIN
  retval:='';
  FOR res IN (select f.TYPE field_type, mdv.code, mdv.decode, to_char(mdv.date_value, 'DD/MM/YYYY') as date_value, mdv.element_link, mdv.txt_value, to_char(mdv.long_txt_value) long_txt_value
    from doc_obj_md md, doc_obj_md_val mdv,
    doc_md_field f, doc_md_template t, doc_obj d, doc_type dt
    where md.FIELD_ID=f.id and md.TEMPLATE_ID=t.id and mdv.MD_ID=md.id
    and d.id=md.element_id and dt.id=d.TYPE_ID
    and t.name=T_NAME
    and f.name=F_NAME
    and d.id=E_ID
    and d.deleted=0)
    LOOP
      if (res.field_type in (1,2)) then retval:=retval||res.long_txt_value; end if;
      if (res.field_type in (3,4,5,8)) then retval:=retval||res.decode; end if;
      if (res.field_type=6) then retval:=retval||res.date_value; end if;
      if (res.field_type=7) then retval:=retval||res.element_link; end if;
      if (res.field_type in (0,8)) then retval:=retval||res.txt_value; end if;
      retval:=retval||'|';
    END LOOP;  
  RETURN rtrim(retval,'|');
END FIELDVALUE;
";

$qBase4="create or replace FUNCTION FIELDVALUECODE 
(
T_NAME IN VARCHAR2,
F_NAME IN VARCHAR2, 
E_ID IN VARCHAR2 
) RETURN VARCHAR2 AS 
retval varchar2(4000);
BEGIN
  retval:='';
  FOR res IN (select f.TYPE field_type, mdv.code, mdv.decode, to_char(mdv.date_value, 'DD/MM/YYYY') as date_value, mdv.element_link, mdv.txt_value, to_char(mdv.long_txt_value) long_txt_value
    from doc_obj_md md, doc_obj_md_val mdv,
    doc_md_field f, doc_md_template t, doc_obj d, doc_type dt
    where md.FIELD_ID=f.id and md.TEMPLATE_ID=t.id and mdv.MD_ID=md.id
    and d.id=md.element_id and dt.id=d.TYPE_ID
    and t.name=T_NAME
    and f.name=F_NAME
    and d.id=E_ID
    and d.deleted=0)
    LOOP
      if (res.field_type in (3,4,5,8)) then retval:=retval||res.code; end if;
      retval:=retval||'|';
    END LOOP;  
  RETURN rtrim(retval,'|');
END FIELDVALUECODE;";




$q=new query($conn);

$q->exec($qBase1);

$q->exec($qBase2);

$q->exec($qBase3);

$q->exec($qBase4);

function getConnection(){
	global $conn;
	return $conn;
}

function getSmarty()
{
	$smarty = new Smarty();
	$smarty->setTemplateDir('templates/');
	$smarty->setCompileDir('templates_c/');
	$smarty->setConfigDir('configs/');
	$smarty->setCacheDir('cache/');
	//$smarty->clearAllCache();
	return $smarty;
}
dispatch('/', 'home');
dispatch('/getLinkedFieldSpec', 'getLinkedFieldSpec');
dispatch_post('/buildReport', 'buildReport');

function buildReport(){
	buildReportAction($_POST);
}

function getLinkedFieldSpec(){
	$conn=getConnection();
	$elTypeName=$_GET['elTypeName'];
	$templateName=$_GET['templateName'];
	$fieldName=$_GET['fieldName'];
	$sql3="select distinct type_name, type_id
	from doc_obj_view
	where id in (
	select distinct element_link
	from doc_obj_md_view
	where type_name='$elTypeName'
	and template_name='$templateName'
	and field_name='$fieldName'
	)";
	$q3=new query($conn);
	$q3->exec($sql3);
	while ($q3->get_row()){
		$ret[$q3->row['TYPE_NAME']]=getElementDetails($q3->row['TYPE_NAME'], $q3->row['TYPE_ID']);
	}
	header('Content-Type: application/json');
	echo json_encode($ret);
		
}



function home()
{
	if (isset($_GET['clearSession']) && $_GET['clearSession']!='') {
		foreach ($_SESSION as $key=>$val){
			unset($_SESSION[$key]);
		}
	}
	$smarty=getSmarty();
	$struct=getObjectStruct();
	$ace_css_added[]="bootstrap-multiselect";
	$ace_css_added[]="select2";
	$ace_css_added[]="bootstrap-treeview";
	$ace_js_added[]="bootstrap-multiselect";
	$ace_js_added[]="select2";
	$ace_js_added[]="bootstrap-treeview";
	$js_added[]="home";
	$css_added[]="style";

	$smarty->assign("ace_css_added", $ace_css_added);
	$smarty->assign("css_added", $css_added);
	$smarty->assign("ace_js_added", $ace_js_added);
	$smarty->assign("js_added", $js_added);
	$smarty->assign("title", "xCDM Report Designer");
	$smarty->assign("struct", $struct);
	$smarty->display("home.tpl");
}


run();
$conn->commit();
$conn->close();