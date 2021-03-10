<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetProtocolLinkResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $GetProtocolLinkResult = null;

    /**
     * @return string
     */
    public function getGetProtocolLinkResult()
    {
        return $this->GetProtocolLinkResult;
    }

    /**
     * @param string $GetProtocolLinkResult
     * @return GetProtocolLinkResponse
     */
    public function withGetProtocolLinkResult($GetProtocolLinkResult)
    {
        $new = clone $this;
        $new->GetProtocolLinkResult = $GetProtocolLinkResult;

        return $new;
    }


}

