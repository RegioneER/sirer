<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocument2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocument2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocument2Result()
    {
        return $this->GetCardDocument2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocument2Result
     * @return GetCardDocument2Response
     */
    public function withGetCardDocument2Result($GetCardDocument2Result)
    {
        $new = clone $this;
        $new->GetCardDocument2Result = $GetCardDocument2Result;

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
     * @return GetCardDocument2Response
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

