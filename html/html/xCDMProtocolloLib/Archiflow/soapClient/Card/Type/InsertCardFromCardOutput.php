<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCardFromCardOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     */
    public function __construct($CardId)
    {
        $this->CardId = $CardId;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return InsertCardFromCardOutput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }


}

