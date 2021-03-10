<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachment2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardAttachment2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Attachment
     */
    private $oAttachment = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardAttachment2Result()
    {
        return $this->GetCardAttachment2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardAttachment2Result
     * @return GetCardAttachment2Response
     */
    public function withGetCardAttachment2Result($GetCardAttachment2Result)
    {
        $new = clone $this;
        $new->GetCardAttachment2Result = $GetCardAttachment2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Attachment
     */
    public function getOAttachment()
    {
        return $this->oAttachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\Attachment $oAttachment
     * @return GetCardAttachment2Response
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }


}

