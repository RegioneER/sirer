<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentType2 implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $nDocumentTypeId = null;

    /**
     * @var bool
     */
    private $bGetFields = null;

    /**
     * @var bool
     */
    private $bGetAdditives = null;

    /**
     * @var bool
     */
    private $bGetAddInEmailMapping = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nDocumentTypeId
     * @var bool $bGetFields
     * @var bool $bGetAdditives
     * @var bool $bGetAddInEmailMapping
     */
    public function __construct($strSessionId, $nDocumentTypeId, $bGetFields, $bGetAdditives, $bGetAddInEmailMapping)
    {
        $this->strSessionId = $strSessionId;
        $this->nDocumentTypeId = $nDocumentTypeId;
        $this->bGetFields = $bGetFields;
        $this->bGetAdditives = $bGetAdditives;
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
     * @return GetDocumentType2
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
    public function getNDocumentTypeId()
    {
        return $this->nDocumentTypeId;
    }

    /**
     * @param int $nDocumentTypeId
     * @return GetDocumentType2
     */
    public function withNDocumentTypeId($nDocumentTypeId)
    {
        $new = clone $this;
        $new->nDocumentTypeId = $nDocumentTypeId;

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
     * @return GetDocumentType2
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
    public function getBGetAdditives()
    {
        return $this->bGetAdditives;
    }

    /**
     * @param bool $bGetAdditives
     * @return GetDocumentType2
     */
    public function withBGetAdditives($bGetAdditives)
    {
        $new = clone $this;
        $new->bGetAdditives = $bGetAdditives;

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
     * @return GetDocumentType2
     */
    public function withBGetAddInEmailMapping($bGetAddInEmailMapping)
    {
        $new = clone $this;
        $new->bGetAddInEmailMapping = $bGetAddInEmailMapping;

        return $new;
    }


}

