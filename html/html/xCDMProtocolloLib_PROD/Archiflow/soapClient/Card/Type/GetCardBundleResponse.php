<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardBundleResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardBundleResult = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $oCardBundle = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardBundleResult()
    {
        return $this->GetCardBundleResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardBundleResult
     * @return GetCardBundleResponse
     */
    public function withGetCardBundleResult($GetCardBundleResult)
    {
        $new = clone $this;
        $new->GetCardBundleResult = $GetCardBundleResult;

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
     * @return GetCardBundleResponse
     */
    public function withOCardBundle($oCardBundle)
    {
        $new = clone $this;
        $new->oCardBundle = $oCardBundle;

        return $new;
    }


}

