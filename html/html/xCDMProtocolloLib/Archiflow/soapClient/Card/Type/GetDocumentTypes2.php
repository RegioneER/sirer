<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypes2 implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\AccessLevel
     */
    private $enAccessLevel = null;

    /**
     * @var bool
     */
    private $bReturnAll = null;

    /**
     * @var bool
     */
    private $bGetFields = null;

    /**
     * @var bool
     */
    private $bGetAddInEmailMapping = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @var bool $bReturnAll
     * @var bool $bGetFields
     * @var bool $bGetAddInEmailMapping
     */
    public function __construct($strSessionId, $enAccessLevel, $bReturnAll, $bGetFields, $bGetAddInEmailMapping)
    {
        $this->strSessionId = $strSessionId;
        $this->enAccessLevel = $enAccessLevel;
        $this->bReturnAll = $bReturnAll;
        $this->bGetFields = $bGetFields;
        $this->bGetAddInEmailMapping = $bGetAddInEmailMapping;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetDocumentTypes2
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetDocumentTypes2
     */
    public function withEnAccessLevel($enAccessLevel)
    {
        $new = clone $this;
        $new->enAccessLevel = $enAccessLevel;

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
     * @return GetDocumentTypes2
     */
    public function withBReturnAll($bReturnAll)
    {
        $new = clone $this;
        $new->bReturnAll = $bReturnAll;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetFields()
    {
        return $this->bGetFields;
    }

    /**
     * @param bool $bGetFields
     * @return GetDocumentTypes2
     */
    public function withBGetFields($bGetFields)
    {
        $new = clone $this;
        $new->bGetFields = $bGetFields;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetAddInEmailMapping()
    {
        return $this->bGetAddInEmailMapping;
    }

    /**
     * @param bool $bGetAddInEmailMapping
     * @return GetDocumentTypes2
     */
    public function withBGetAddInEmailMapping($bGetAddInEmailMapping)
    {
        $new = clone $this;
        $new->bGetAddInEmailMapping = $bGetAddInEmailMapping;

        return $new;
    }


}

