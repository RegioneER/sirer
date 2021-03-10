<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachments2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardAttachments2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAttachment
     */
    private $oAttachments = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardAttachments2Result()
    {
        return $this->GetCardAttachments2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardAttachments2Result
     * @return GetCardAttachments2Response
     */
    public function withGetCardAttachments2Result($GetCardAttachments2Result)
    {
        $new = clone $this;
        $new->GetCardAttachments2Result = $GetCardAttachments2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAttachment
     */
    public function getOAttachments()
    {
        return $this->oAttachments;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAttachment $oAttachments
     * @return GetCardAttachments2Response
     */
    public function withOAttachments($oAttachments)
    {
        $new = clone $this;
        $new->oAttachments = $oAttachments;

        return $new;
    }


}

