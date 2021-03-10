<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetFieldVersionResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetFieldVersionOutput
     */
    private $GetFieldVersionResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetFieldVersionOutput
     */
    public function getGetFieldVersionResult()
    {
        return $this->GetFieldVersionResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetFieldVersionOutput $GetFieldVersionResult
     * @return GetFieldVersionResponse
     */
    public function withGetFieldVersionResult($GetFieldVersionResult)
    {
        $new = clone $this;
        $new->GetFieldVersionResult = $GetFieldVersionResult;

        return $new;
    }


}

