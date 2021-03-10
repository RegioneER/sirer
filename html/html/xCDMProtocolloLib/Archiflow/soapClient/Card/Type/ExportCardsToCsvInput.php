<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExportCardsToCsvInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $GetAll = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $SearchCriteria = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var bool $GetAll
     * @var \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     */
    public function __construct($CardIds, $GetAll, $SearchCriteria)
    {
        $this->CardIds = $CardIds;
        $this->GetAll = $GetAll;
        $this->SearchCriteria = $SearchCriteria;
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
     * @return ExportCardsToCsvInput
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
    public function getGetAll()
    {
        return $this->GetAll;
    }

    /**
     * @param bool $GetAll
     * @return ExportCardsToCsvInput
     */
    public function withGetAll($GetAll)
    {
        $new = clone $this;
        $new->GetAll = $GetAll;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getSearchCriteria()
    {
        return $this->SearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     * @return ExportCardsToCsvInput
     */
    public function withSearchCriteria($SearchCriteria)
    {
        $new = clone $this;
        $new->SearchCriteria = $SearchCriteria;

        return $new;
    }


}

