<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CalculateCardExpirationOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardExpirationInfo
     */
    private $CardExpiration = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardExpirationInfo $CardExpiration
     */
    public function __construct($CardExpiration)
    {
        $this->CardExpiration = $CardExpiration;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardExpirationInfo
     */
    public function getCardExpiration()
    {
        return $this->CardExpiration;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardExpirationInfo $CardExpiration
     * @return CalculateCardExpirationOutput
     */
    public function withCardExpiration($CardExpiration)
    {
        $new = clone $this;
        $new->CardExpiration = $CardExpiration;

        return $new;
    }


}

