<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetProtocolInfoResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $GetProtocolInfoResult = null;

    /**
     * @return string
     */
    public function getGetProtocolInfoResult()
    {
        return $this->GetProtocolInfoResult;
    }

    /**
     * @param string $GetProtocolInfoResult
     * @return GetProtocolInfoResponse
     */
    public function withGetProtocolInfoResult($GetProtocolInfoResult)
    {
        $new = clone $this;
        $new->GetProtocolInfoResult = $GetProtocolInfoResult;

        return $new;
    }


}

