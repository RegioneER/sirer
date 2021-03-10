<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardVisibilityResult = null;

    /**
     * @var \ArchiflowWSCard\Type\SendObject
     */
    private $oSendObject = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardVisibilityResult()
    {
        return $this->GetCardVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardVisibilityResult
     * @return GetCardVisibilityResponse
     */
    public function withGetCardVisibilityResult($GetCardVisibilityResult)
    {
        $new = clone $this;
        $new->GetCardVisibilityResult = $GetCardVisibilityResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendObject
     */
    public function getOSendObject()
    {
        return $this->oSendObject;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendObject $oSendObject
     * @return GetCardVisibilityResponse
     */
    public function withOSendObject($oSendObject)
    {
        $new = clone $this;
        $new->oSendObject = $oSendObject;

        return $new;
    }


}

