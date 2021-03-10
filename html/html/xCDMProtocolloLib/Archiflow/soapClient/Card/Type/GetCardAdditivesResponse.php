<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAdditivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardAdditivesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    private $oAdditives = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardAdditivesResult()
    {
        return $this->GetCardAdditivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardAdditivesResult
     * @return GetCardAdditivesResponse
     */
    public function withGetCardAdditivesResult($GetCardAdditivesResult)
    {
        $new = clone $this;
        $new->GetCardAdditivesResult = $GetCardAdditivesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    public function getOAdditives()
    {
        return $this->oAdditives;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAdditive $oAdditives
     * @return GetCardAdditivesResponse
     */
    public function withOAdditives($oAdditives)
    {
        $new = clone $this;
        $new->oAdditives = $oAdditives;

        return $new;
    }


}

