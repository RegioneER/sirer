<?php
$paths = array(
    realpath($_SERVER['DOCUMENT_ROOT']."/../libs"),
    '.',
);

set_include_path(implode(PATH_SEPARATOR, $paths));
require_once 'Zend/Loader/StandardAutoloader.php';
$loader = new Zend_Loader_StandardAutoloader(array('autoregister_zf' => true));

// this is not recommended.
$loader->setFallbackAutoloader(true);

// Register with spl_autoload:
$loader->register();


class ActivitiService{

    const BASE_URL = 'http://appserv-siss01.dev.cineca.it/xWM/rest-service/';
    const ADMIN_USERNAME = 'admin';
    const ADMIN_PASSWORD = 'xxx';

    private $_base_url;
    private $_client;

    private $_base_service;

    public $WAITMESSAGE = "[WAITING]";
    public $RES_SUCCESS = "[SUCCESS]";
    public $RES_FAILURE = "[FAILURE]";

    public function __construct($baseurl = self::BASE_URL, $username = self::ADMIN_USERNAME, $password = self::ADMIN_PASSWORD){
        $this->_base_url = $baseurl;
        $this->_client = new Zend_Http_Client();
        $this->_client->setAuth($username, $password);
        $headers['content-type']="application/json";
        $this->_client->setHeaders($headers);
        $this->_client->setConfig(array("timeout" => "30"));
        $this->_base_service = substr($_SERVER['HTTP_HOST'],0,strpos($_SERVER['HTTP_HOST'],"."));
    }

    public function getProcessId($key, $value){
        $this->_client->setUri($this->_base_url."repository/process-definitions?latest=true&{$key}={$value}");
        $this->_client->setMethod("GET");
        //print_r($this->_client);
        $response=$this->_getResponse();
        //print_r($response);
        return $response['data'][0]['id'];
    }
	
	public function getProcesses(){
        $this->_client->setUri($this->_base_url."repository/process-definitions?latest=true&size=100000"); //This output is paginated!
        $this->_client->setMethod("GET");
        $response=$this->_getResponse();
        return $response;
    }

    public function getStartFormDetail($processDefId){
        $this->_client->setUri($this->_base_url."form/form-data?processDefinitionId={$processDefId}");
        $this->_client->setMethod("GET");
        $response=$this->_getResponse();
        foreach($response['formProperties'] as $key=>$val){
            $fields[$val['id']]['name']=$val['name'];
            $fields[$val['id']]['type']=$val['type'];
        }
        return $fields;
    }

    public function startProcess($processDefinitionKey, $vars){
        $procdefkey = $this->_base_service.".".$processDefinitionKey;
		//echo "PDKEY: $procdefkey";
        $processId=$this->getProcessId("key", $procdefkey);
    	$fields=$this->getStartFormDetail($processId);
        $this->_client->setUri($this->_base_url."form/form-data");
        $body['processDefinitionId']=$processId;
        foreach ($vars as $key=>$val){
            if (isset($fields[$key])){
                $pVars['id']=$key;
                $pVars['value']=$val;
                $tVars[]=$pVars;
            }
        }
        global $in;
        $objVars = array();
        foreach ($in as $key=>$val){
            $objVars[$key]=$val;
        }
        $jsonFormData = json_encode($objVars);
        $pVars['id'] = "jsonFormData";
        $pVars['value'] = $jsonFormData;
        $tVars[] = $pVars;
        $body['properties']=$tVars;
        //echo "<pre>";
        //print_r($body);
        //echo "</pre>";
        $rawBody=json_encode($body);
		//die($rawBody);
        $this->_client->setRawData($rawBody);
        $this->_client->setMethod("POST");
        $response=$this->_getResponse();
        //print_r($response);
        //die();
        if ($response['statusCode']=='500') throw new Exception("Process execution error. See logs for details. - {$response['errorMessage']} (".$response['statusCode'].")");
        return $response['id'];
    }

    public function hasProcessEnded($processDefinitionKey, $processId)
    {
        $retval = "";
        $procdefkey = $this->_base_service . "." . $processDefinitionKey;
        //echo "PDKEY: $procdefkey";
        $definitionId = $this->getProcessId("key", $procdefkey);

        $this->_client->setUri($this->_base_url."history/historic-process-instances/".$processId);
        $this->_client->setMethod("GET");
        $response=$this->_getResponse();
        if ($response['statusCode']=='500') throw new Exception("Process execution error. See logs for details. - {$response['errorMessage']} (".$response['statusCode'].")");
        //var_dump($response);
        if ($response['endTime']){
            $this->_client->setUri($this->_base_url."repository/process-definitions/".$definitionId."/model");
            $this->_client->setMethod("GET");
            $model=$this->_getResponse();
            //var_dump($model);
            $endId = $response["endActivityId"];
            $name = "";
            $elements = $model["processes"][0]["flowElements"];
            foreach ($elements as $el){
                if ($el["id"]==$endId){
                    $name = $el["name"];
                    //die("FOUND!");
                }
            }
            if ($name=="success"){
                //Tutto bene
                $retval = $this->RES_SUCCESS;
            }else{
                //End-node di fallimento
                $retval = $this->RES_FAILURE;
            }
        }else{
            $retval = $this->WAITMESSAGE;
        }

        return $retval;
    }

    private function _getResponse(){
    	$body = $this->_client->request()->getBody();
    	$result = self::_toJson($body);
    	return $result;
    }

    private static function _toJson($data){
        if ($data) {
            return json_decode($data, true);
        }else{
            return "";
        }
    }

}
?>