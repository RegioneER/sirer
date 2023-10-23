<?php


class axmr_ml{

    var	$prefix;
    var $lang;
    var $conn;

    function loadLanguage(){
        //Logger::send("Carico le stringhe...");
        //echo "<pre>LOAD LANGUAGE ({$this->lang})!!</pre>";
        //debug_print_backtrace();
        if (!$this->lang){
            $this->lang = "en";
            //echo "<pre>DEFAULT LANGUAGE!!</pre>";
        }
        $sql=new query($this->conn);
        $bind = array();
        $bind['LANG'] = $this->lang;
        $sql->exec("SELECT * FROM {$this->prefix}_I18N WHERE lower(LANG)=lower(:LANG)",$bind);
        unset($_SESSION['labels']);
        while ($sql->get_row()){
            $_SESSION['labels'][$sql->row['LABEL']]=$sql->row['TEXT'];
        }

    }

    function __construct($prefix, $lang, $conn, $config_param){
        if (!session_id()){
            session_start();
        }
        //echo "<pre>SESSID: ".session_id()."</pre>";
        $this->prefix=$prefix;
        $this->lang=$lang;
        $this->conn=$conn;
        //echo "<pre>PRODUCTION: ".$config_param['production']."</pre>";
        if ($config_param['production']!=1) {
            //unset($_SESSION['labels']);
            //debug_print_backtrace();
        }
        //unset($_SESSION['labels']['Profile_GDE.profileName']);
        //$_SESSION['labels']['System.Home']='System.Home';
        //$dbg = print_r($_SESSION['labels'],true);
        //$dbg = substr($dbg,0,20);
        //echo "<pre>$dbg</pre>";
        if (!isset($_SESSION['labels']) || !$_SESSION['labels'] || $_SESSION['labels_prefix']!=$this->prefix) {
            $this->loadLanguage();
            $_SESSION['labels_prefix']=$this->prefix;
        }
        global $ml;
        $ml=$this;
        //Verifico una variabile che dovrei sempre avere:
        //var_dump($_SESSION['labels']['System.Home']);
        if ($_SESSION['labels']['System.Home']=='System.Home'){
            //Meglio che ricarichi le etichette
            $this->loadLanguage();
            $_SESSION['labels_prefix']=$this->prefix;
        }

    }

    function changeLanguage($code){
        $this->lang=$code;
        $this->loadLanguage();
    }

    function updateLabel($string, $text){
        $bind['LANG'] = $this->lang;
        $bind['LABEL']= $string;
        $bind['TEXT']= $text;
        $sql=new query($this->conn);
        $sql->ins_upd("UPDATE {$this->prefix}_I18N SET TEXT=:TEXT WHERE lower(LANG)=lower(:LANG) AND LABEL=:LABEL ",$bind);
        $this->conn->commit();
        $_SESSION['labels'][$string]=$text;
    }

    function clearFormLabels($prefix){
        $bind['LANG'] = $this->lang;
        $bind['LABELPREFIX']= $prefix.".%";
        $sql=new query($this->conn);
        $sql->ins_upd("DELETE FROM {$this->prefix}_I18N WHERE lower(LANG)=lower(:LANG) AND LABEL LIKE :LABELPREFIX ",$bind);
        $this->conn->commit();
        unset($_SESSION['labels']);
    }

    function out($string, $defaultValue=null){
        //$retval = $string;
        //if (isset($defaultValue) && $defaultValue!="") $retval=$defaultValue;
        //if ($retval=="__EMPTY_STRING__");
        if (!isset($_SESSION['labels'][$string]) || $_SESSION['labels'][$string]==""){
            //echo "CARICA STRINGA SINGOLA: {$string}<hr/>";
            //debug_print_backtrace();
            $bind = array();
            $bind['LANG'] = $this->lang;
            $bind['LABEL']= $string;
            //var_dump($bind);
            //$label=$string;
            $sql=new query($this->conn);
            $sql_query="select * from {$this->prefix}_I18N where lower(LANG)=lower(:LANG) and LABEL=:LABEL";
            $text=$string;
            $sql->exec($sql_query, $bind);
            if ($sql->get_row()){
                $text=$sql->row['TEXT'];
            }else {
                if (isset($defaultValue) && $defaultValue!="") {
                    $bind['TEXT']=$defaultValue;
                    $text=$defaultValue;
                } else {
                    $bind['TEXT']= $string;
                }

                //Logger::send("inserisco in db {$bind['LABEL']}, $string");
                $sql->ins_upd("INSERT INTO {$this->prefix}_I18N (LANG, LABEL, TEXT) VALUES(lower(:LANG), :LABEL, :TEXT) ",$bind);
                $this->conn->commit();
            }
            //Imposto la mia variabile di sessione
            $_SESSION['labels'][$string]=$text;
        }
        $retval=$_SESSION['labels'][$string];
        //var_dump($_SESSION['labels'][$string]);
        if ($retval=='__EMPTY_STRING__'){
            $retval="";
        }
        if (!isset($_SESSION['editLabelInLine'])){
            return $retval;
        } else {
        $labelId="label-{$string}";
        $labelId=str_replace(".", "_", $labelId);
        $modLink="<span class='editlabel' data-id='{$string}' label-id='{$labelId}'><i class='fa fa-pencil'></i></span>";
            return "<span label-id-selector='{$labelId}'>$retval</span>".$modLink;
        }

    }

}

function mlClearFormLabels($formPrefix){
    global $ml;
    if (!$ml){
        return false;
    }
    $ml->clearFormLabels($formPrefix);
    $ml->loadLanguage();
    return true;
}

function mlOut($string, $defaultValue=null){
    global $ml;
    if(!$ml){
        //die("NO ML!");
        return $string;
    }
    $string=trim($string);
    $defaultValue=trim($defaultValue);
    return $ml->out($string, $defaultValue);
}


function mlChangeLanguage($code){
    global $ml;
    $ml->changeLanguage($code);
}

function mlGetLanguage(){
    global $ml;
    return $ml->lang;
}

function mlLoadLanguage(){
    global $ml;
    $ml->loadLanguage();
}

function mlOutJs($string, $defaultValue=null){
    return make_js(mlOut($string, $defaultValue));
}

function mlUpdateLabel($string, $text){
    global $ml;
    $ml->updateLabel($string, $text);
}
?>
