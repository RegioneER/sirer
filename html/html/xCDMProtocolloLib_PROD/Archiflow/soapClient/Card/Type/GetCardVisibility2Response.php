<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardVisibility2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardVisibility2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\SendObject
     */
    private $oSendObject = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardVisibility2Result()
    {
        return $this->GetCardVisibility2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardVisibility2Result
     * @return GetCardVisibility2Response
     */
    public function withGetCardVisibility2Result($GetCardVisibility2Result)
    {
        $new = clone $this;
        $new->GetCardVisibility2Result = $GetCardVisibility2Result;

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
     * @return GetCardVisibility2Response
     */
    public function withOSendObject($oSendObject)
    {
        $new = clone $this;
        $new->oSendObject = $oSendObject;

        return $new;
    }


}

