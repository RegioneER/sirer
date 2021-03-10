<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Carlo
 * Date: 14/05/13
 * Time: 9.35
 * To change this template use File | Settings | File Templates.
 */

class ToSignDocument {
public $documentID;
    public $descriptionMimeType;
    public $descriptionValue;
    public $signatureTemplateID;
    public $timestampTemplateID;
    public $contentValue;
    public $contentURI;
    public $contentDigest;

    public function __construct($filePath,$description, $descriptionMimeType, $isPdf=true){
        $this->descriptionValue=$description;
        $this->descriptionMimeType=$descriptionMimeType;
        $this->documentID="1";
        $this->signatureTemplateID="PDF_SIGNATURE";
        $data = file_get_contents($filePath);
        //$base64=base64_encode($data);
        $this->contentValue=$data;
    }

}