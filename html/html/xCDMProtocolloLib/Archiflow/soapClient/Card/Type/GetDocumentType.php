<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentType implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nDocumentTypeId
     * @var bool $bGetFields
     * @var bool $bGetAdditives
     */
    public function __construct($strSessionId, $nDocumentTypeId, $bGetFields, $bGetAdditives)
    {
        $this->strSessionId = $strSessionId;
        $this->nDocumentTypeId = $nDocumentTypeId;
        $this->bGetFields = $bGetFields;
        $this->bGetAdditives = $bGetAdditives;
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
     * @return GetDocumentType
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
     * @return GetDocumentType
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
     * @return GetDocumentType
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
     * @return GetDocumentType
     */
    public function withBGetAdditives($bGetAdditives)
    {
        $new = clone $this;
        $new->bGetAdditives = $bGetAdditives;

        return $new;
    }


}

