<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCard4Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertCard4Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertCard4Result()
    {
        return $this->InsertCard4Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertCard4Result
     * @return InsertCard4Response
     */
    public function withInsertCard4Result($InsertCard4Result)
    {
        $new = clone $this;
        $new->InsertCard4Result = $InsertCard4Result;

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
     * @return InsertCard4Response
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

