<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetProtocolStatusesResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $GetProtocolStatusesResult = null;

    /**
     * @return string
     */
    public function getGetProtocolStatusesResult()
    {
        return $this->GetProtocolStatusesResult;
    }

    /**
     * @param string $GetProtocolStatusesResult
     * @return GetProtocolStatusesResponse
     */
    public function withGetProtocolStatusesResult($GetProtocolStatusesResult)
    {
        $new = clone $this;
        $new->GetProtocolStatusesResult = $GetProtocolStatusesResult;

        return $new;
    }


}

