<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDrawerVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetDrawerVisibilityResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\SendObject
     */
    private $oSendObject = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetDrawerVisibilityResult()
    {
        return $this->GetDrawerVisibilityResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetDrawerVisibilityResult
     * @return GetDrawerVisibilityResponse
     */
    public function withGetDrawerVisibilityResult($GetDrawerVisibilityResult)
    {
        $new = clone $this;
        $new->GetDrawerVisibilityResult = $GetDrawerVisibilityResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SendObject
     */
    public function getOSendObject()
    {
        return $this->oSendObject;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendObject $oSendObject
     * @return GetDrawerVisibilityResponse
     */
    public function withOSendObject($oSendObject)
    {
        $new = clone $this;
        $new->oSendObject = $oSendObject;

        return $new;
    }


}

