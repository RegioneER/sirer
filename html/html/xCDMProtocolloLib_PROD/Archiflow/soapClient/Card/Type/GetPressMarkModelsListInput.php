<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetPressMarkModelsListInput implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveType = null;

    /**
     * @var int
     */
    private $DocumentType = null;

    /**
     * @var \ArchiflowWSCard\Type\PressMarkType
     */
    private $PressMarkType = null;

    /**
     * Constructor
     *
     * @var int $ArchiveType
     * @var int $DocumentType
     * @var \ArchiflowWSCard\Type\PressMarkType $PressMarkType
     */
    public function __construct($ArchiveType, $DocumentType, $PressMarkType)
    {
        $this->ArchiveType = $ArchiveType;
        $this->DocumentType = $DocumentType;
        $this->PressMarkType = $PressMarkType;
    }

    /**
     * @return int
     */
    public function getArchiveType()
    {
        return $this->ArchiveType;
    }

    /**
     * @param int $ArchiveType
     * @return GetPressMarkModelsListInput
     */
    public function withArchiveType($ArchiveType)
    {
        $new = clone $this;
        $new->ArchiveType = $ArchiveType;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param int $DocumentType
     * @return GetPressMarkModelsListInput
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\PressMarkType
     */
    public function getPressMarkType()
    {
        return $this->PressMarkType;
    }

    /**
     * @param \ArchiflowWSCard\Type\PressMarkType $PressMarkType
     * @return GetPressMarkModelsListInput
     */
    public function withPressMarkType($PressMarkType)
    {
        $new = clone $this;
        $new->PressMarkType = $PressMarkType;

        return $new;
    }


}

