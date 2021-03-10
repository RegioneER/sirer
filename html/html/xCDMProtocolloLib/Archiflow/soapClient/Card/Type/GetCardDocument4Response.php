<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocument4Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocument4Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocument4Result()
    {
        return $this->GetCardDocument4Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocument4Result
     * @return GetCardDocument4Response
     */
    public function withGetCardDocument4Result($GetCardDocument4Result)
    {
        $new = clone $this;
        $new->GetCardDocument4Result = $GetCardDocument4Result;

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
     * @return GetCardDocument4Response
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

