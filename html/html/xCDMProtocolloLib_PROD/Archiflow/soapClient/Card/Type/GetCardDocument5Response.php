<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocument5Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocument5Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocument5Result()
    {
        return $this->GetCardDocument5Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocument5Result
     * @return GetCardDocument5Response
     */
    public function withGetCardDocument5Result($GetCardDocument5Result)
    {
        $new = clone $this;
        $new->GetCardDocument5Result = $GetCardDocument5Result;

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
     * @return GetCardDocument5Response
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

