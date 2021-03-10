<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardVisibility implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $nArchiveId = null;

    /**
     * @var int
     */
    private $nDocumentTypeId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $oFields = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nArchiveId
     * @var int $nDocumentTypeId
     * @var \ArchiflowWSCard\Type\ArrayOfField $oFields
     */
    public function __construct($strSessionId, $nArchiveId, $nDocumentTypeId, $oFields)
    {
        $this->strSessionId = $strSessionId;
        $this->nArchiveId = $nArchiveId;
        $this->nDocumentTypeId = $nDocumentTypeId;
        $this->oFields = $oFields;
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
     * @return GetCardVisibility
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNArchiveId()
    {
        return $this->nArchiveId;
    }

    /**
     * @param int $nArchiveId
     * @return GetCardVisibility
     */
    public function withNArchiveId($nArchiveId)
    {
        $new = clone $this;
        $new->nArchiveId = $nArchiveId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNDocumentTypeId()
    {
        return $this->nDocumentTypeId;
    }

    /**
     * @param int $nDocumentTypeId
     * @return GetCardVisibility
     */
    public function withNDocumentTypeId($nDocumentTypeId)
    {
        $new = clone $this;
        $new->nDocumentTypeId = $nDocumentTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getOFields()
    {
        return $this->oFields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $oFields
     * @return GetCardVisibility
     */
    public function withOFields($oFields)
    {
        $new = clone $this;
        $new->oFields = $oFields;

        return $new;
    }


}

