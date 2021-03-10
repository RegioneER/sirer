<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertCardResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertCardResult()
    {
        return $this->InsertCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertCardResult
     * @return InsertCardResponse
     */
    public function withInsertCardResult($InsertCardResult)
    {
        $new = clone $this;
        $new->InsertCardResult = $InsertCardResult;

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
     * @return InsertCardResponse
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

