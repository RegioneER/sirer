<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafSearchCriteria implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfSearchAgrafEntityId
     */
    private $SearchAgrafEntitiesId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfSearchAgrafOptionsTag
     */
    private $SearchAgrafOptionsTags = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfSearchAgrafEntityId $SearchAgrafEntitiesId
     * @var \ArchiflowWSCard\Type\ArrayOfSearchAgrafOptionsTag $SearchAgrafOptionsTags
     */
    public function __construct($SearchAgrafEntitiesId, $SearchAgrafOptionsTags)
    {
        $this->SearchAgrafEntitiesId = $SearchAgrafEntitiesId;
        $this->SearchAgrafOptionsTags = $SearchAgrafOptionsTags;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfSearchAgrafEntityId
     */
    public function getSearchAgrafEntitiesId()
    {
        return $this->SearchAgrafEntitiesId;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfSearchAgrafEntityId $SearchAgrafEntitiesId
     * @return AgrafSearchCriteria
     */
    public function withSearchAgrafEntitiesId($SearchAgrafEntitiesId)
    {
        $new = clone $this;
        $new->SearchAgrafEntitiesId = $SearchAgrafEntitiesId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfSearchAgrafOptionsTag
     */
    public function getSearchAgrafOptionsTags()
    {
        return $this->SearchAgrafOptionsTags;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfSearchAgrafOptionsTag
     * $SearchAgrafOptionsTags
     * @return AgrafSearchCriteria
     */
    public function withSearchAgrafOptionsTags($SearchAgrafOptionsTags)
    {
        $new = clone $this;
        $new->SearchAgrafOptionsTags = $SearchAgrafOptionsTags;

        return $new;
    }


}

