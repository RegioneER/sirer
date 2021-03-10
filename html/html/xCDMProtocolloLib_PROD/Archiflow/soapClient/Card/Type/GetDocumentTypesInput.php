<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypesInput implements RequestInterface
{

    /**
     * @var bool
     */
    private $GetAddInEmailMapping = null;

    /**
     * @var bool
     */
    private $GetAdditives = null;

    /**
     * @var bool
     */
    private $GetFields = null;

    /**
     * @var bool
     */
    private $bReturnAll = null;

    /**
     * @var \ArchiflowWSCard\Type\AccessLevel
     */
    private $enAccessLevel = null;

    /**
     * Constructor
     *
     * @var bool $GetAddInEmailMapping
     * @var bool $GetAdditives
     * @var bool $GetFields
     * @var bool $bReturnAll
     * @var \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     */
    public function __construct($GetAddInEmailMapping, $GetAdditives, $GetFields, $bReturnAll, $enAccessLevel)
    {
        $this->GetAddInEmailMapping = $GetAddInEmailMapping;
        $this->GetAdditives = $GetAdditives;
        $this->GetFields = $GetFields;
        $this->bReturnAll = $bReturnAll;
        $this->enAccessLevel = $enAccessLevel;
    }

    /**
     * @return bool
     */
    public function getGetAddInEmailMapping()
    {
        return $this->GetAddInEmailMapping;
    }

    /**
     * @param bool $GetAddInEmailMapping
     * @return GetDocumentTypesInput
     */
    public function withGetAddInEmailMapping($GetAddInEmailMapping)
    {
        $new = clone $this;
        $new->GetAddInEmailMapping = $GetAddInEmailMapping;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetAdditives()
    {
        return $this->GetAdditives;
    }

    /**
     * @param bool $GetAdditives
     * @return GetDocumentTypesInput
     */
    public function withGetAdditives($GetAdditives)
    {
        $new = clone $this;
        $new->GetAdditives = $GetAdditives;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetFields()
    {
        return $this->GetFields;
    }

    /**
     * @param bool $GetFields
     * @return GetDocumentTypesInput
     */
    public function withGetFields($GetFields)
    {
        $new = clone $this;
        $new->GetFields = $GetFields;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBReturnAll()
    {
        return $this->bReturnAll;
    }

    /**
     * @param bool $bReturnAll
     * @return GetDocumentTypesInput
     */
    public function withBReturnAll($bReturnAll)
    {
        $new = clone $this;
        $new->bReturnAll = $bReturnAll;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AccessLevel
     */
    public function getEnAccessLevel()
    {
        return $this->enAccessLevel;
    }

    /**
     * @param \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @return GetDocumentTypesInput
     */
    public function withEnAccessLevel($enAccessLevel)
    {
        $new = clone $this;
        $new->enAccessLevel = $enAccessLevel;

        return $new;
    }


}

