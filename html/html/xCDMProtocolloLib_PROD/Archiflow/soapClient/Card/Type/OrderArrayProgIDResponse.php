<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class OrderArrayProgIDResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $OrderArrayProgIDResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oOrderedCardIds = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getOrderArrayProgIDResult()
    {
        return $this->OrderArrayProgIDResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $OrderArrayProgIDResult
     * @return OrderArrayProgIDResponse
     */
    public function withOrderArrayProgIDResult($OrderArrayProgIDResult)
    {
        $new = clone $this;
        $new->OrderArrayProgIDResult = $OrderArrayProgIDResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOOrderedCardIds()
    {
        return $this->oOrderedCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oOrderedCardIds
     * @return OrderArrayProgIDResponse
     */
    public function withOOrderedCardIds($oOrderedCardIds)
    {
        $new = clone $this;
        $new->oOrderedCardIds = $oOrderedCardIds;

        return $new;
    }


}

