<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypes implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @var bool $bReturnAll
     * @var bool $bGetFields
     */
    public function __construct($strSessionId, $enAccessLevel, $bReturnAll, $bGetFields)
    {
        $this->strSessionId = $strSessionId;
        $this->enAccessLevel = $enAccessLevel;
        $this->bReturnAll = $bReturnAll;
        $this->bGetFields = $bGetFields;
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
     * @return GetDocumentTypes
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
     * @return GetDocumentTypes
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
     * @return GetDocumentTypes
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
     * @return GetDocumentTypes
     */
    public function withBGetFields($bGetFields)
    {
        $new = clone $this;
        $new->bGetFields = $bGetFields;

        return $new;
    }


}

