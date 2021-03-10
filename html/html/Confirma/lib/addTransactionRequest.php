<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Carlo
 * Date: 14/05/13
 * Time: 9.23
 * To change this template use File | Settings | File Templates.
 */

class addTransactionRequest extends SOAPMessage{

    public $transactionID;
    public $authenticationToken;
    public $authUserID;
    public $signUserID;
    public $presentationType;
    public $descriptionMimeType;
    public $descriptionValue;
    public $signingDateTime;
    public $toSignDocuments;

}
