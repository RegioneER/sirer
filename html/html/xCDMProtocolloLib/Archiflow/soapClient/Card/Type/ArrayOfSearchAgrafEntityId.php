<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfSearchAgrafEntityId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SearchAgrafEntityId
     */
    private $SearchAgrafEntityId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SearchAgrafEntityId $SearchAgrafEntityId
     */
    public function __construct($SearchAgrafEntityId)
    {
        $this->SearchAgrafEntityId = $SearchAgrafEntityId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchAgrafEntityId
     */
    public function getSearchAgrafEntityId()
    {
        return $this->SearchAgrafEntityId;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchAgrafEntityId $SearchAgrafEntityId
     * @return ArrayOfSearchAgrafEntityId
     */
    public function withSearchAgrafEntityId($SearchAgrafEntityId)
    {
        $new = clone $this;
        $new->SearchAgrafEntityId = $SearchAgrafEntityId;

        return $new;
    }


}

