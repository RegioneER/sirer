<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardBarcodeToSapResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SendCardBarcodeToSapResult = null;

    /**
     * @var string
     */
    private $docId = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSendCardBarcodeToSapResult()
    {
        return $this->SendCardBarcodeToSapResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SendCardBarcodeToSapResult
     * @return SendCardBarcodeToSapResponse
     */
    public function withSendCardBarcodeToSapResult($SendCardBarcodeToSapResult)
    {
        $new = clone $this;
        $new->SendCardBarcodeToSapResult = $SendCardBarcodeToSapResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocId()
    {
        return $this->docId;
    }

    /**
     * @param string $docId
     * @return SendCardBarcodeToSapResponse
     */
    public function withDocId($docId)
    {
        $new = clone $this;
        $new->docId = $docId;

        return $new;
    }


}

