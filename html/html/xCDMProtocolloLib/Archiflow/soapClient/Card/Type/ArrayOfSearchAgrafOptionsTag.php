<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfSearchAgrafOptionsTag implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SearchAgrafOptionsTag
     */
    private $SearchAgrafOptionsTag = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SearchAgrafOptionsTag $SearchAgrafOptionsTag
     */
    public function __construct($SearchAgrafOptionsTag)
    {
        $this->SearchAgrafOptionsTag = $SearchAgrafOptionsTag;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchAgrafOptionsTag
     */
    public function getSearchAgrafOptionsTag()
    {
        return $this->SearchAgrafOptionsTag;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchAgrafOptionsTag $SearchAgrafOptionsTag
     * @return ArrayOfSearchAgrafOptionsTag
     */
    public function withSearchAgrafOptionsTag($SearchAgrafOptionsTag)
    {
        $new = clone $this;
        $new->SearchAgrafOptionsTag = $SearchAgrafOptionsTag;

        return $new;
    }


}

