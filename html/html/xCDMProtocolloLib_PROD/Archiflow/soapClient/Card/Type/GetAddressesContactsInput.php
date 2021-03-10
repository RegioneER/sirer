<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetAddressesContactsInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $GetOnlyMainAddresses = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var bool $GetOnlyMainAddresses
     */
    public function __construct($CardIds, $GetOnlyMainAddresses)
    {
        $this->CardIds = $CardIds;
        $this->GetOnlyMainAddresses = $GetOnlyMainAddresses;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return GetAddressesContactsInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetOnlyMainAddresses()
    {
        return $this->GetOnlyMainAddresses;
    }

    /**
     * @param bool $GetOnlyMainAddresses
     * @return GetAddressesContactsInput
     */
    public function withGetOnlyMainAddresses($GetOnlyMainAddresses)
    {
        $new = clone $this;
        $new->GetOnlyMainAddresses = $GetOnlyMainAddresses;

        return $new;
    }


}

