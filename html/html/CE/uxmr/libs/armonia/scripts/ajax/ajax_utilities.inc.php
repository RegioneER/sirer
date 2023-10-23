<?php 

/**************************************************************************************************************************
 *
* UTILITY
*
**************************************************************************************************************************/

class EnvironmentCheck{
	/**
	 * Advanced PHP-CLI mode check.
	 *
	 * @return boolean    Returns true if PHP is running from the CLI or else false.
	 *
	 * @access public
	 * @static
	 */
	public static function isCli()
	{
		// If STDIN was not defined and PHP is running as CGI module
		// we can test for the environment variable TERM. This
		// should be a right way how to test the circumstance under
		// what mode PHP is running.
		if(!defined('STDIN') && self::isCgi()) {
			// STDIN was not defined, but if the environment variable TERM
			// is set, it is save to say that PHP is running from CLI.
			if(getenv('TERM')) {
				return true;
			}
			// Now return false, because TERM was not set.
			return false;
		}
		return defined('STDIN');
	}

	/**
	 * Simple PHP-CGI mode check.
	 *
	 * (DSO = Dynamic Shared Object)
	 *
	 * @link http://httpd.apache.org/docs/current/dso.html DSO
	 * @link http://www.php.net/manual/en/function.php-sapi-name.php PHP_SAPI
	 *
	 * @return boolean    Returns true if PHP is running as CGI module or else false.
	 *
	 * @access public
	 * @static
	 */
	public static function isCgi()
	{
		if (substr(PHP_SAPI, 0, 3) == 'cgi') {
			return true;
		} else {
			return false;
		}
		return false;
	}
	
	public static function isAjax()
	{
		if(isset($_SERVER['HTTP_X_REQUESTED_WITH']) && $_SERVER['HTTP_X_REQUESTED_WITH'] == "XMLHttpRequest")
 			return true;
		else
 			return false;
	}
	
	
	/**
	 * 
	 * Questo serve per capire in che ambiente sono (se non ne ho idea!)
	 */
	public static function getEnvironment(){
		foreach((get_class_methods('EnvironmentCheck')) as $method_name){
			if ($method_name !='getEnvironment'){
				if ((call_user_func_array(array('EnvironmentCheck',$method_name),''))==true)
					return $method_name;
		}
		return 'none';
		}
	}
}


function array_to_json( $array ){

	if( !is_array( $array ) ){
		return false;
	}

	$associative = count( array_diff( array_keys($array), array_keys( array_keys( $array )) ));
	if( $associative ){

		$construct = array();
		foreach( $array as $key => $value ){

			// We first copy each key/value pair into a staging array,
			// formatting each key and value properly as we go.

			// Format the key:
			if( is_numeric($key) ){
				$key = "key_$key";
			}
			$key = "\"".addslashes($key)."\"";

			// Format the value:
			if( is_array( $value )){
				$value = array_to_json( $value );
			} else if( !is_numeric( $value ) || is_string( $value ) ){
				$value = "\"".addslashes($value)."\"";
			}

			// Add to staging array:
			$construct[] = "$key: $value";
		}

		// Then we collapse the staging array into the JSON form:
		$result = "{ " . implode( ", ", $construct ) . " }";

	} else { // If the array is a vector (not associative):

		$construct = array();
		foreach( $array as $value ){

			// Format the value:
			if( is_array( $value )){
				$value = array_to_json( $value );
			} else if( !is_numeric( $value ) || is_string( $value ) ){
				$value = "'".addslashes($value)."'";
			}

			// Add to staging array:
			$construct[] = $value;
		}

		// Then we collapse the staging array into the JSON form:
		$result = "[ " . implode( ", ", $construct ) . " ]";
	}

	return $result;
}



