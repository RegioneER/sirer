<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetAddressesContactsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetAddressesContactsOutput
     */
    private $GetAddressesContactsResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetAddressesContactsOutput
     */
    public function getGetAddressesContactsResult()
    {
        return $this->GetAddressesContactsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetAddressesContactsOutput
     * $GetAddressesContactsResult
     * @return GetAddressesContactsResponse
     */
    public function withGetAddressesContactsResult($GetAddressesContactsResult)
    {
        $new = clone $this;
        $new->GetAddressesContactsResult = $GetAddressesContactsResult;

        return $new;
    }


}

