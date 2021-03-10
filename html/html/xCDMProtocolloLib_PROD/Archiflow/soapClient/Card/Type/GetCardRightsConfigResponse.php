<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardRightsConfigResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardRightsConfigResult = null;

    /**
     * @var \ArchiflowWSCard\Type\CardRightsConfig
     */
    private $oCardRightsConfig = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardRightsConfigResult()
    {
        return $this->GetCardRightsConfigResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardRightsConfigResult
     * @return GetCardRightsConfigResponse
     */
    public function withGetCardRightsConfigResult($GetCardRightsConfigResult)
    {
        $new = clone $this;
        $new->GetCardRightsConfigResult = $GetCardRightsConfigResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardRightsConfig
     */
    public function getOCardRightsConfig()
    {
        return $this->oCardRightsConfig;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardRightsConfig $oCardRightsConfig
     * @return GetCardRightsConfigResponse
     */
    public function withOCardRightsConfig($oCardRightsConfig)
    {
        $new = clone $this;
        $new->oCardRightsConfig = $oCardRightsConfig;

        return $new;
    }


}

