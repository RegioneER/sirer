<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Carlo
 * Date: 14/05/13
 * Time: 9.30
 * To change this template use File | Settings | File Templates.
 */

class getSignedTransactionResponse  extends SOAPMessage{
    public $transactionID;
    public $signedDocuments;
}