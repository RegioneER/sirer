<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypeProtocolTypeResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypeProtocolTypeResult = null;

    /**
     * @var \ArchiflowWSCard\Type\AipType
     */
    private $enProtocolType = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypeProtocolTypeResult()
    {
        return $this->GetDocumentTypeProtocolTypeResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypeProtocolTypeResult
     * @return GetDocumentTypeProtocolTypeResponse
     */
    public function withGetDocumentTypeProtocolTypeResult($GetDocumentTypeProtocolTypeResult)
    {
        $new = clone $this;
        $new->GetDocumentTypeProtocolTypeResult = $GetDocumentTypeProtocolTypeResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AipType
     */
    public function getEnProtocolType()
    {
        return $this->enProtocolType;
    }

    /**
     * @param \ArchiflowWSCard\Type\AipType $enProtocolType
     * @return GetDocumentTypeProtocolTypeResponse
     */
    public function withEnProtocolType($enProtocolType)
    {
        $new = clone $this;
        $new->enProtocolType = $enProtocolType;

        return $new;
    }


}

