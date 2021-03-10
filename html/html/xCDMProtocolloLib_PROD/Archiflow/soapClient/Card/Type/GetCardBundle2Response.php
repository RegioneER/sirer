<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardBundle2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardBundle2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $oCardBundle = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardBundle2Result()
    {
        return $this->GetCardBundle2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardBundle2Result
     * @return GetCardBundle2Response
     */
    public function withGetCardBundle2Result($GetCardBundle2Result)
    {
        $new = clone $this;
        $new->GetCardBundle2Result = $GetCardBundle2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardBundle
     */
    public function getOCardBundle()
    {
        return $this->oCardBundle;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardBundle $oCardBundle
     * @return GetCardBundle2Response
     */
    public function withOCardBundle($oCardBundle)
    {
        $new = clone $this;
        $new->oCardBundle = $oCardBundle;

        return $new;
    }


}

