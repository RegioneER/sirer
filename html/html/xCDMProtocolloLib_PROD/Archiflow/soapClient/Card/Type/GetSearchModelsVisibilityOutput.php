<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetSearchModelsVisibilityOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ModelTypeFilter
     */
    private $Filter = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ModelTypeFilter $Filter
     */
    public function __construct($Filter)
    {
        $this->Filter = $Filter;
    }

    /**
     * @return \ArchiflowWSCard\Type\ModelTypeFilter
     */
    public function getFilter()
    {
        return $this->Filter;
    }

    /**
     * @param \ArchiflowWSCard\Type\ModelTypeFilter $Filter
     * @return GetSearchModelsVisibilityOutput
     */
    public function withFilter($Filter)
    {
        $new = clone $this;
        $new->Filter = $Filter;

        return $new;
    }


}

