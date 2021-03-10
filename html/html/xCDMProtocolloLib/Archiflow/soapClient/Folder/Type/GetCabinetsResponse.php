<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCabinetsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetCabinetsResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfCabinet
     */
    private $oCabinets = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetCabinetsResult()
    {
        return $this->GetCabinetsResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetCabinetsResult
     * @return GetCabinetsResponse
     */
    public function withGetCabinetsResult($GetCabinetsResult)
    {
        $new = clone $this;
        $new->GetCabinetsResult = $GetCabinetsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfCabinet
     */
    public function getOCabinets()
    {
        return $this->oCabinets;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfCabinet $oCabinets
     * @return GetCabinetsResponse
     */
    public function withOCabinets($oCabinets)
    {
        $new = clone $this;
        $new->oCabinets = $oCabinets;

        return $new;
    }


}

