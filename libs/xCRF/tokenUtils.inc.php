<?php

class TokenUtils{


    public static function createToken($conn, $prefix, $type, $action, $arguments){
        $q=new query($conn);
        $checkTable="select count(*) as C from user_tables where table_name='{$prefix}_TOKENS'";
        $q->get_row($checkTable);
        if ($q->row['C']==0){
            $createTokenTable="create table ".$prefix."_TOKENS(
                TOKEN_VALUE VARCHAR2(300 CHAR),
                TOKEN_TYPE VARCHAR2(15 CHAR),
                SESSION_ID VARCHAR2(100 CHAR),
                ACTION VARCHAR2(300 CHAR),
                TOKEN_CREATE_DT date,
                ARGS CLOB
                )";
            $q->exec($createTokenTable);
        }
        $argumentString=json_encode($arguments);
        $values=[];
        if ($type=='session') {
            $values['SESSION_ID']=session_id();
            $tokenValue = base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, md5($values['SESSION_ID'].$argumentString), $action, MCRYPT_MODE_CBC, md5(md5($values['SESSION_ID'].$argumentString))));
        }else {
            $tokenValue = base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, md5($argumentString), $action, MCRYPT_MODE_CBC, md5(md5($argumentString))));
        }
        $values['TOKEN_VALUE']=$tokenValue;
        $values['TOKEN_TYPE']=$type;
        $values['ACTION']=$action;
        $values['ARGS']=$argumentString;
        $values['TOKEN_CREATE_DT']="sysdate";
        $sqlCheck="select count(*) as C from ".$prefix."_TOKENS where TOKEN_VALUE=:tk";
        $bind=[];
        $bind["tk"]=$tokenValue;
        $q->get_row($sqlCheck, $bind);
        if ($q->row['C']==0){
            $q->insert($values,$prefix."_TOKENS", array());
            $conn->commit();
        }
        return $tokenValue;
    }

    public static function getTokenInfo($conn, $prefix, $token){
        $q=new query($conn);
        $sqlCheck="select * from ".$prefix."_TOKENS where TOKEN_VALUE=:tk";
        $bind=[];
        $bind["tk"]=$token;
        if ($q->get_row($sqlCheck, $bind)){
            if ($q->row['TOKEN_TYPE']=='session'){
                if ($q->row['SESSION_ID']!=session_id()) return false;
            }
            if ($q->row['ARGS']!='') $q->row['ARGS']=json_decode($q->row['ARGS'], true);
            return $q->row;
        }else return false;
    }

    public static function consumeToken($conn, $prefix, $token){
        $q=new query($conn);
        $sqlCheck="select * from ".$prefix."_TOKENS where TOKEN_VALUE=:tk";
        $bind=[];
        $bind["tk"]=$token;
        if ($q->get_row($sqlCheck, $bind)){
            if ($q->row['TOKEN_TYPE']=='onetime'){
                $sqlDelete="delete from ".$prefix."_TOKENS where TOKEN_VALUE=:tk";
                $q->ins_upd($sqlDelete);
                $conn->commit();
                return true;
            }
        }else return false;
    }


}

?>