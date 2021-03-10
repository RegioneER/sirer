<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCard3Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertCard3Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertCard3Result()
    {
        return $this->InsertCard3Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertCard3Result
     * @return InsertCard3Response
     */
    public function withInsertCard3Result($InsertCard3Result)
    {
        $new = clone $this;
        $new->InsertCard3Result = $InsertCard3Result;

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
     * @return InsertCard3Response
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

