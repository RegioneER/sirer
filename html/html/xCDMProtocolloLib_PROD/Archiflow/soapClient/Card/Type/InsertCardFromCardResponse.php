<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCardFromCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertCardFromCardResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertCardFromCardResult()
    {
        return $this->InsertCardFromCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertCardFromCardResult
     * @return InsertCardFromCardResponse
     */
    public function withInsertCardFromCardResult($InsertCardFromCardResult)
    {
        $new = clone $this;
        $new->InsertCardFromCardResult = $InsertCardFromCardResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardGuid()
    {
        return $this->oCardGuid;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardGuid
     * @return InsertCardFromCardResponse
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

