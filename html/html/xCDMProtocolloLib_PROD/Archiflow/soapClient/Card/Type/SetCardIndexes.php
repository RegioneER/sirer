<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardIndexes implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var bool
     */
    private $bAutomaticProtocol = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $oIndexes = null;

    /**
     * @var \ArchiflowWSCard\Type\Archive
     */
    private $oArchive = null;

    /**
     * @var \ArchiflowWSCard\Type\DocumentType
     */
    private $oDocumentType = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bAutomaticProtocol
     * @var \ArchiflowWSCard\Type\ArrayOfField $oIndexes
     * @var \ArchiflowWSCard\Type\Archive $oArchive
     * @var \ArchiflowWSCard\Type\DocumentType $oDocumentType
     */
    public function __construct($oSessionInfo, $oCardId, $bAutomaticProtocol, $oIndexes, $oArchive, $oDocumentType)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardId = $oCardId;
        $this->bAutomaticProtocol = $bAutomaticProtocol;
        $this->oIndexes = $oIndexes;
        $this->oArchive = $oArchive;
        $this->oDocumentType = $oDocumentType;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @return SetCardIndexes
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return SetCardIndexes
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBAutomaticProtocol()
    {
        return $this->bAutomaticProtocol;
    }

    /**
     * @param bool $bAutomaticProtocol
     * @return SetCardIndexes
     */
    public function withBAutomaticProtocol($bAutomaticProtocol)
    {
        $new = clone $this;
        $new->bAutomaticProtocol = $bAutomaticProtocol;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getOIndexes()
    {
        return $this->oIndexes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $oIndexes
     * @return SetCardIndexes
     */
    public function withOIndexes($oIndexes)
    {
        $new = clone $this;
        $new->oIndexes = $oIndexes;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Archive
     */
    public function getOArchive()
    {
        return $this->oArchive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Archive $oArchive
     * @return SetCardIndexes
     */
    public function withOArchive($oArchive)
    {
        $new = clone $this;
        $new->oArchive = $oArchive;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentType
     */
    public function getODocumentType()
    {
        return $this->oDocumentType;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentType $oDocumentType
     * @return SetCardIndexes
     */
    public function withODocumentType($oDocumentType)
    {
        $new = clone $this;
        $new->oDocumentType = $oDocumentType;

        return $new;
    }


}

