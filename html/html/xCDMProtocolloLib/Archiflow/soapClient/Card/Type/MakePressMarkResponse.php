<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class MakePressMarkResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $MakePressMarkResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getMakePressMarkResult()
    {
        return $this->MakePressMarkResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $MakePressMarkResult
     * @return MakePressMarkResponse
     */
    public function withMakePressMarkResult($MakePressMarkResult)
    {
        $new = clone $this;
        $new->MakePressMarkResult = $MakePressMarkResult;

        return $new;
    }


}

