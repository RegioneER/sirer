<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardHasDataOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardHasData
     */
    private $HasData = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardHasData $HasData
     */
    public function __construct($HasData)
    {
        $this->HasData = $HasData;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardHasData
     */
    public function getHasData()
    {
        return $this->HasData;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardHasData $HasData
     * @return GetCardHasDataOutput
     */
    public function withHasData($HasData)
    {
        $new = clone $this;
        $new->HasData = $HasData;

        return $new;
    }


}

