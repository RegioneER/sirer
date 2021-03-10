<?php
include "db.inc";

echo "<pre>";
function getFirstId($table, $conn){
    $q=new query($conn);
    $firstIdSql="select pos from (
            select id, rownum as pos from (
                select id from $table order by id asc) t
        ) t2 where t2.id!=t2.pos and rownum<=1";
    if ($q->get_row($firstIdSql)){
        $id=$q->row['POS'];
    }else {
        $firstIdSql="select count(*)+1 as pos from $table";
        $q->get_row($firstIdSql);
        $id=$q->row['POS'];
    }
    return $id;
}

$fieldType=array();
$fieldType['TEXTBOX']=0;
$fieldType['RICHTEXT']=1;
$fieldType['TEXTAREA']=2;
$fieldType['SELECT']=3;
$fieldType['RADIO']=4;
$fieldType['CHECKBOX']=5;
$fieldType['DATE']=6;
$fieldType['ELEMENT_LINK']=7;
$fieldType['EXT_DICTIONARY']=8;
$fieldType['PLACE_HOLDER']=9;

$_SERVER['ORIG_URL']='https://sirer-ctms.sissprep.cineca.it/sirer';
$_SERVER['ORIG_USERNAME']='VMAZZEO';
$_SERVER['ORIG_PASSWORD']='test123\;';
$_SERVER['DB_DEST_HOST']='cman01-ext.dbc.cineca.it';
$_SERVER['DB_DEST_PORT']='5555';
$_SERVER['DB_DEST_SERVICENAME']='db41_ext.pdv.cineca.it';
$_SERVER['DB_DEST_USERNAME']='GARAER';
$_SERVER['DB_DEST_PASSWORD']='gra3r24!01';
$_SERVER['DEST_URL']='https://sirer.progetto-sole.it/sirer';
$_SERVER['DEST_USERNAME']='VMAZZEO';
$_SERVER['DEST_PASSWORD']='SIRER2019!';

$host = "sirer_prod";
//$host = str_replace("__DB_HOST__", $_SERVER['DB_DEST_HOST'], $host);
//$host = str_replace("__DB_PORT__", $_SERVER['DB_DEST_PORT'], $host);
//$host = str_replace("__DB_SERVICENAME__", $_SERVER['DB_DEST_SERVICENAME'], $host);
$conn = new dbconn($_SERVER['DB_DEST_USERNAME'], $_SERVER['DB_DEST_PASSWORD'], $host);

echo "\nLeggo configurazione da ".$_SERVER['ORIG_URL']." ...";

$cmd1="curl -q -u {$_SERVER['ORIG_USERNAME']}:{$_SERVER['ORIG_PASSWORD']} {$_SERVER['ORIG_URL']}/services/dm/rest/admin/getJsonConfiguration";
echo "\n\t".$cmd1;
$result=shell_exec($cmd1);

$configuration=json_decode($result, true);

$q = new query($conn);

echo "\n - 1 - Allineo i template ...";

$templateId=array();


foreach ($configuration['templates'] as $template){
    echo "\n\t - - Template id: ".$template['id'];
    $sqlcheck="select * from DOC_MD_TEMPLATE where id=:id";
    $bind=array("id"=>$template['id']);
    $values=array();
    $templateId[$template['name']]=$template['id'];
    $values['IS_AUDITABLE']=($template['auditable'] ==1 ? 1 : 0);
    $values['CAL_COLOR']=$template['calendarColor'];
    $values['CALENDAR_NAME']=$template['calendarName'];
    $values['CALENDARIZED']=($template['calendarized'] ==1 ? 1 : 0);
    $values['DELETED']=($template['deleted'] ==1 ? 1 : 0);
    $values['DESCRIPTION']=$template['description'];
    $values['NAME']=$template['name'];
    $values['CAL_START_FIELD']=$template['startDateField'];
    $values['CAL_END_FIELD']=$template['endDateField'];
    $q1=new query($conn);
    if ($q->get_row($sqlcheck, $bind)){
        echo "\n\t - - Template {$template['name']} (id:{$template['id']}) trovato effettuo aggiornamento ...";
        if ($q->row['NAME']!=$template['name']) {
            echo "\n\t TEMPLATE TROVATO CON NOME DIVERSO. ERRORE!!!!";
            exit(1);
        }
        $pk['ID']=$template['id'];
        $q->update($values, "DOC_MD_TEMPLATE", $pk);
    }else {
        echo "\n\t - - Template {$template['name']} (id:{$template['id']}) NON trovato effettuo insert ...";
        $values['ID']=$template['id'];
        $q->insert($values, "DOC_MD_TEMPLATE", null);
    }
    $conn->commit();
    echo "\n\t\t Allineo campi ...";
    foreach ($template['fields'] as $field){
        echo "\n\t\t - - Campo id: ".$field['id'];
        $sqlcheck="select * from DOC_MD_FIELD where id=:id";
        $bind=array("id"=>$field['id']);
        $values=array();
        $values['CASCADE']=($field['cascadeDelete'] ==1 ? 1 : 0);
        $values['DELETED']=($field['deleted'] ==1 ? 1 : 0);
        $values['MANDATORY']=($field['mandatory']==1 ? 1 : 0);
        $values['NAME']=$field['name'];
        $values['ADD_FILTER_FIELDS']=$field['addFilterFields'];
        $values['AVAILABLE_VALUES']=$field['availableValues'];
        $values['EXT_DICTIONARY']=$field['externalDictionary'];
        $values['POSITION']=$field['position'];
        $values['TYPE']=$fieldType[$field['type']];
        $values['BASE_NAME_ORA']=$field['baseNameOra'];
        $values['F_MACRO']=$field['macro'];
        $values['F_MACRO_VIEW']=$field['macroView'];
        $values['REGEXP_CHECK']=$field['regexpCheck'];
        $values['F_SIZE']=$field['size'];
        $values['TYPE_FILTERS']=$field['typefilters'];
        $values['TEMPLATE_ID']=$template['id'];


        $q1=new query($conn);
        if ($q->get_row($sqlcheck, $bind)){
            echo "\n\t\t - - Campo {$field['name']} (id:{$field['id']}) trovato effettuo aggiornamento ...";
            if ($q->row['NAME']!=$field['name']) {
                echo "\n\t\t CAMPO TROVATO CON NOME DIVERSO. ERRORE!!!!";
                exit(1);
            }
            $pk['ID']=$field['id'];
            $q->update($values, "DOC_MD_FIELD", $pk);
        }else {
            echo "\n\t\t - - Campo {$field['name']} (id:{$field['id']}) NON trovato effettuo insert ...";
            $values['ID']=$field['id'];
            $q->insert($values, "DOC_MD_FIELD", null);
        }
        $conn->commit();
    }

    echo " fatto!";
}

echo "\n - 1 - Allineo i tipi ...";

$docTplAcls=array();
$docAcls=array();

foreach ($configuration['types'] as $type){
    echo "\n\t - - Template id: ".$type['id'];
    $sqlcheck="select * from DOC_TYPE where id=:id";
    $bind=array("id"=>$type['id']);
    $values=array();
    $values['TYPE_NAME']=$type['typeId'];
    $values['FTL_DETAIL']=$type['ftlDetailTemplate'];
    $values['FTL_FORM']=$type['ftlFormTemplate'];
    $values['FTL_ROW']=$type['ftlRowTemplate'];
    $values['GROUP_UP_LEVEL']=$type['groupUpLevel'];
    $values['TITLE_REGEX']=$type['titleRegex'];

    $values['CHECK_OUT_ENABLED']=($type['checkOutEnabled'] ==1 ? 1 : 0);
    $values['IS_CONTAINER']=($type['container'] ==1 ? 1 : 0);
    $values['DELETED']=($type['deleted'] ==1 ? 1 : 0);
    $values['DRAFTABLE']=($type['draftable'] ==1 ? 1 : 0);
    $values['FILE_ON_FS']=($type['fileOnFS'] ==1 ? 1 : 0);
    $values['CAN_HAVE_FILE']=($type['hasFileAttached'] ==1 ? 1 : 0);
    $values['NO_FILE_INFO']=($type['noFileinfo'] ==1 ? 1 : 0);
    $values['CAN_BE_ROOT']=($type['rootAble'] ==1 ? 1 : 0);
    $values['SEARCHABLE']=($type['searchable'] ==1 ? 1 : 0);
    $values['IS_SELF_RECURSIVE']=($type['selfRecursive'] ==1 ? 1 : 0);
    $values['SORTABLE']=($type['sortable'] ==1 ? 1 : 0);


    $q1=new query($conn);
    if ($q->get_row($sqlcheck, $bind)){
        echo "\n\t - - Tipo {$type['typeId']} (id:{$type['id']}) trovato effettuo aggiornamento ...";
        if ($q->row['TYPE_NAME']!=$type['typeId']) {
            echo "\n\t TEMPLATE TROVATO CON NOME DIVERSO. ERRORE!!!!";
            exit(1);
        }
        $pk['ID']=$type['id'];
        $q->update($values, "DOC_TYPE", $pk);
    }else {
        echo "\n\t - - Tipo {$type['typeId']} (id:{$type['id']}) NON trovato effettuo insert ...";
        $values['ID']=$type['id'];
        $q->insert($values, "DOC_TYPE", null);
    }
    $conn->commit();

    foreach ($type['associatedTemplates'] as $associatedTemplate){
        echo "\n\t\t - - AssocTemplate id: ".$associatedTemplate['id'];
        $sqlcheck="select * from DOC_TYPE_MD_TEMPLATE where id=:id";
        $bind=array("id"=>$associatedTemplate['id']);
        $values=array();
        $values['TEMPLATE_ID']=$associatedTemplate['metadataId'];
        $values['ENABLED']=($associatedTemplate['enabled'] ==1 ? 1 : 0);
        $values['TYPE_ID']=$type['id'];
        $q1=new query($conn);
        if ($q->get_row($sqlcheck, $bind)){
            echo "\n\t\t - - AssocTemplate (id:{$associatedTemplate['id']}) trovato effettuo aggiornamento ...";
            $pk['ID']=$associatedTemplate['id'];
            $q->update($values, "DOC_TYPE_MD_TEMPLATE", $pk);
        }else {
            echo "\n\t\t - - AssocTemplate (id:{$associatedTemplate['id']}) NON trovato effettuo insert ...";
            $values['ID']=$associatedTemplate['id'];
            $q->insert($values, "DOC_TYPE_MD_TEMPLATE", null);
        }
        $conn->commit();
        echo " fatto!";
    }
    foreach ($type['allowedChildNames'] as $childName){
        echo "\n\t\t - - Controllo figlio : ".$childName;
        $child=null;
        foreach ($configuration['types'] as $possibleChild){
            if ($possibleChild['typeId']==$childName) {
                $child=$possibleChild;
                break;
            }
        }
        $sqlcheck="select * from DOC_TYPE_DOC_TYPE where doc_type_id=:id and allowedchilds_id=:childId";
        $bind=array("id"=>$type['id'], "childId"=>$child['id']);
        $values=array();
        $values['DOC_TYPE_ID']=$type['id'];
        $values['ALLOWEDCHILDS_ID']=$child['id'];
        $q1=new query($conn);
        if (!$q->get_row($sqlcheck, $bind)){
            echo "\n\t\t - - figlio : {$childName} NON trovato effettuo insert ...";
            $q->insert($values, "DOC_TYPE_DOC_TYPE", null);
        }
        $conn->commit();
        echo " fatto!";
    }

    foreach ($type['associatedWorkflows'] as $associatedWorkflows){
        echo "\n\t\t - - AssocTemplate id: ".$associatedWorkflows['id'];
        $sqlcheck="select * from DOC_TYPE_WF where id=:id";
        $bind=array("id"=>$associatedWorkflows['id']);
        $values=array();
        $values['PROCESS_KEY']=$associatedWorkflows['processKey'];
        $values['ENABLED']=($associatedWorkflows['enabled'] ==1 ? 1 : 0);
        $values['START_ON_CREATE']=($associatedWorkflows['startOnCreate'] ==1 ? 1 : 0);
        $values['START_ON_DELETE']=($associatedWorkflows['startOnDelete'] ==1 ? 1 : 0);
        $values['START_ON_UPDATE']=($associatedWorkflows['startOnUpdate'] ==1 ? 1 : 0);
        $values['TYPE_ID']=$type['id'];
        $q1=new query($conn);
        if ($q->get_row($sqlcheck, $bind)){
            echo "\n\t\t - - associatedWorkflows (id:{associatedWorkflows['id']}) trovato effettuo aggiornamento ...";
            $pk['ID']=$associatedWorkflows['id'];
            $q->update($values, "DOC_TYPE_WF", $pk);
        }else {
            echo "\n\t\t - - associatedWorkflows (id:{associatedWorkflows['id']}) NON trovato effettuo insert ...";
            $values['ID']=$associatedWorkflows['id'];
            $q->insert($values, "DOC_TYPE_WF", null);
        }
        $conn->commit();
        echo " fatto!";
    }

    foreach ($type['acls'] as $acl){
        $aclRow=array();
        $aclRow['TEMPLATE_FTL']=$acl['detailTemplate'];
        $aclRow['ID_REF']=$acl['idRef'];
        $aclRow['POLICY_VALE']=$acl['policyValue'];
        $aclRow['POSITIONAL_ACE']=$acl['positionalAce'];
        $aclRow['TYPE_ID']=$type['id'];
        $aclRow['containers']=array();
        foreach ($acl['containers'] as $container){
            $aclContainerRow=array();
            $aclContainerRow['AUTHORITY']=($container['authority'] ==1 ? 1 : 0);
            $aclContainerRow['CONTAINER']=$container['container'];
            $aclRow['containers'][]=$aclContainerRow;
        }

        $docAcls[]=$aclRow;

    }
    echo " fatto!";
}

echo "\n\tProcesso ACL";

echo "\n\t\t Elimino ACL";

$deleteAclContainer="delete from DOC_ACL_CONTAINER where acl_di in (select id from DOC_ACL where type_id is not null)";
$deleteAcl="delete from DOC_ACL where type_id is not null";

$d=new query($conn);
$d->ins_upd($deleteAclContainer);
$d->ins_upd($deleteAcl);
$conn->commit();



foreach ($docAcls as $acl){
    $acl['ID']=getFirstId("DOC_ACL", $conn);
    $containers=$acl['containers'];
    unset($acl['containers']);
    $q->insert($acl, "DOC_ACL", null);
    $conn->commit();
    foreach ($containers as $container){
        $container['ACL_DI']=$acl['ID'];
        $container['ID']=getFirstId("DOC_ACL_CONTAINER", $conn);
        $q->insert($container, "DOC_ACL_CONTAINER", null);
        $conn->commit();
    }
    echo "\n\t\tInserita ACL {$acl['ID']}";
}


$seq['DOC_ACL_SEQUENCE']=array("DOC_ACL", "DOC_ACL_CONTAINER", "DOC_TPL_ACL", "DOC_TPL_ACL_CONTAINER");
#$seq['DOC_MDVAL_SEQUENCE']=array("DOC_COMMENT", "DOC_OBJ_GROUP", "DOC_EL_PROCESS", "DOC_OBJ_TEMPLATE", "DOC_AUDIT_EME_VAL", "DOC_AUDIT_MD_VAL", "DOC_OBJ_MD_VAL", "DOC_OBJ_MD", "DOC_AUDIT_FILE", "DOC_OBJ_FILE", "DOC_OBJ_FILE_CONTENT", "DOC_AUDIT_FILE_CONTENT");
$seq['DOC_MODEL_SEQUENCE']=array("DOC_TYPE", "DOC_TYPE_MD_TEMPLATE", "DOC_TYPE_WF", "DOC_MD_TEMPLATE", "DOC_POLICY", "DOC_MD_FIELD");
#$seq['ELEMENT_SEQUENCE']=array("DOC_OBJ");

echo "\n\t Rigenero Sequence";

foreach ($seq as $seqName=>$tables){
    $sqlMax="select max(id)+1 as ID from (";
    foreach ($tables as $table){
        $sqlMax.="
        select max(id) as id from $table
        UNION ALL
        ";
    }
    $sqlMax.="
      select 1 as id from dual
    )";
    $q=new query($conn);
    if ($q->get_row($sqlMax)){
        $id=$q->row['ID'];
    }else {
        $id=1;
    }
    $sqlDropSeq="DROP SEQUENCE $seqName";
    $q->ins_upd($sqlDropSeq);
    $sqlCreateSeq="CREATE SEQUENCE $seqName MINVALUE 1 INCREMENT BY 1 START WITH $id NOCACHE NOORDER NOCYCLE";
    $q->ins_upd($sqlCreateSeq);
    echo "\n\t\t Sequence $seqName ricreata";
}

$conn->commit();


$cmd2="curl -q -u {$_SERVER['ORIG_USERNAME']}:{$_SERVER['ORIG_PASSWORD']} {$_SERVER['ORIG_URL']}/services/dm/rest/admin/processes/getJsonConfiguration";
echo "\n\t".$cmd2;
$processResult=shell_exec($cmd2);

$processes=json_decode($processResult, true);


foreach ($processes['processes'] as $processKey => $processContent) {
    $configuration['processes'][$processKey]=base64_decode($processContent['content']);
}



$cmd2="curl -q -u {$_SERVER['DEST_USERNAME']}:{$_SERVER['DEST_PASSWORD']} {$_SERVER['DEST_URL']}/services/dm/rest/admin/processes/getJsonConfiguration";
echo "\n\t".$cmd2;
$processResult=shell_exec($cmd2);

$destProcesses=json_decode($processResult, true);

$destConfiguration['processes']=array();
if (count($destProcesses)>0) {
    foreach ($destProcesses['processes'] as $processKey => $processContent) {
        $destConfiguration['processes'][$processKey] = base64_decode($processContent['content']);
    }
}


$processesToDeploy=array();

foreach ($configuration['processes'] as $key=>$value){
    if (!isset($destConfiguration)) {
        $processesToDeploy[$key]=$value;
        continue;
    }
    if (!isset($destConfiguration['processes'][$key])) $processesToDeploy[$key]=$value;
    else {
        if ($destConfiguration['processes'][$key]!=$value) $processesToDeploy[$key]=$value;
    }
}

echo "\n - Processi da deployare";

if (count($processesToDeploy)>0){
    foreach ($processesToDeploy as $key=>$val){
        echo "\n\t Processo da deployare: $key";
        file_put_contents($key.".bpmn20.xml", $val);
        $deployCommand="curl -X POST -H \"Content-Type: multipart/form-data\" -F \"data=@{$key}.bpmn20.xml\" -u {$_SERVER['DEST_USERNAME']}:{$_SERVER['DEST_PASSWORD']} {$_SERVER['DEST_URL']}/services/process-engine/repository/deployments";
        system($deployCommand);
    }
}



echo "\nFINE";

echo "</pre>";
die();