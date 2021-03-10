<?php
class ManageMysqlConnect {
	var $mysql_userid = "root";
	var $mysql_password = "";
	var $mysql_host = "127.0.0.1";
	var $mysql_db = "mbsphp_test";
	
	var $link;
	
	function ManageMysqlConnect() {
		$link = false;
	}
	
	function connect() {
		$this->link = mysql_connect($this->mysql_host, $this->mysql_userid, $this->mysql_password) or die('Could not connect: ' . mysql_error());
		mysql_select_db($this->mysql_db, $this->link) or die('Could not select database');
	}
	
	function getLink() {
		if (!$this->link) {
			$this->connect();
		}
		return $this->link;
	}
	
	function disconnect() {
		mysql_close($this->link);
	}
}	
?>