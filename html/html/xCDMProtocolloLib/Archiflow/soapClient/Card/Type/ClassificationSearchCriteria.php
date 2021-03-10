<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ClassificationSearchCriteria implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SearchOptions
     */
    private $ClassificationOptions = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $ClassificationsId = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchOptions
     */
    private $StoreDossierOptions = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $StoreDossiersId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SearchOptions $ClassificationOptions
     * @var \ArchiflowWSCard\Type\ArrayOfint $ClassificationsId
     * @var \ArchiflowWSCard\Type\SearchOptions $StoreDossierOptions
     * @var \ArchiflowWSCard\Type\ArrayOfint $StoreDossiersId
     */
    public function __construct($ClassificationOptions, $ClassificationsId, $StoreDossierOptions, $StoreDossiersId)
    {
        $this->ClassificationOptions = $ClassificationOptions;
        $this->ClassificationsId = $ClassificationsId;
        $this->StoreDossierOptions = $StoreDossierOptions;
        $this->StoreDossiersId = $StoreDossiersId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchOptions
     */
    public function getClassificationOptions()
    {
        return $this->ClassificationOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchOptions $ClassificationOptions
     * @return ClassificationSearchCriteria
     */
    public function withClassificationOptions($ClassificationOptions)
    {
        $new = clone $this;
        $new->ClassificationOptions = $ClassificationOptions;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getClassificationsId()
    {
        return $this->ClassificationsId;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $ClassificationsId
     * @return ClassificationSearchCriteria
     */
    public function withClassificationsId($ClassificationsId)
    {
        $new = clone $this;
        $new->ClassificationsId = $ClassificationsId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchOptions
     */
    public function getStoreDossierOptions()
    {
        return $this->StoreDossierOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchOptions $StoreDossierOptions
     * @return ClassificationSearchCriteria
     */
    public function withStoreDossierOptions($StoreDossierOptions)
    {
        $new = clone $this;
        $new->StoreDossierOptions = $StoreDossierOptions;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getStoreDossiersId()
    {
        return $this->StoreDossiersId;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $StoreDossiersId
     * @return ClassificationSearchCriteria
     */
    public function withStoreDossiersId($StoreDossiersId)
    {
        $new = clone $this;
        $new->StoreDossiersId = $StoreDossiersId;

        return $new;
    }


}

