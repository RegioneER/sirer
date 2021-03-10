<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetPecsResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $GetPecsResult = null;

    /**
     * @return string
     */
    public function getGetPecsResult()
    {
        return $this->GetPecsResult;
    }

    /**
     * @param string $GetPecsResult
     * @return GetPecsResponse
     */
    public function withGetPecsResult($GetPecsResult)
    {
        $new = clone $this;
        $new->GetPecsResult = $GetPecsResult;

        return $new;
    }


}

