<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCabinetVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetCabinetVisibilityResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\SendObject
     */
    private $oSendObject = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetCabinetVisibilityResult()
    {
        return $this->GetCabinetVisibilityResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetCabinetVisibilityResult
     * @return GetCabinetVisibilityResponse
     */
    public function withGetCabinetVisibilityResult($GetCabinetVisibilityResult)
    {
        $new = clone $this;
        $new->GetCabinetVisibilityResult = $GetCabinetVisibilityResult;

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
     * @return GetCabinetVisibilityResponse
     */
    public function withOSendObject($oSendObject)
    {
        $new = clone $this;
        $new->oSendObject = $oSendObject;

        return $new;
    }


}

