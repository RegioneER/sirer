<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocument3Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocument3Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocument3Result()
    {
        return $this->GetCardDocument3Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocument3Result
     * @return GetCardDocument3Response
     */
    public function withGetCardDocument3Result($GetCardDocument3Result)
    {
        $new = clone $this;
        $new->GetCardDocument3Result = $GetCardDocument3Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Document
     */
    public function getODocument()
    {
        return $this->oDocument;
    }

    /**
     * @param \ArchiflowWSCard\Type\Document $oDocument
     * @return GetCardDocument3Response
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

