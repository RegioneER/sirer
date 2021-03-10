<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardRightsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardRightsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCardRight
     */
    private $oCardRights = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardRightsResult()
    {
        return $this->GetCardRightsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardRightsResult
     * @return GetCardRightsResponse
     */
    public function withGetCardRightsResult($GetCardRightsResult)
    {
        $new = clone $this;
        $new->GetCardRightsResult = $GetCardRightsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfCardRight
     */
    public function getOCardRights()
    {
        return $this->oCardRights;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfCardRight $oCardRights
     * @return GetCardRightsResponse
     */
    public function withOCardRights($oCardRights)
    {
        $new = clone $this;
        $new->oCardRights = $oCardRights;

        return $new;
    }


}

