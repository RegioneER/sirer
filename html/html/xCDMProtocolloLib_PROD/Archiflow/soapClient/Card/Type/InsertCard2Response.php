<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCard2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertCard2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertCard2Result()
    {
        return $this->InsertCard2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertCard2Result
     * @return InsertCard2Response
     */
    public function withInsertCard2Result($InsertCard2Result)
    {
        $new = clone $this;
        $new->InsertCard2Result = $InsertCard2Result;

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
     * @return InsertCard2Response
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

