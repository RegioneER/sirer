<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class BuildFileDigest implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @var string
     */
    private $strCertificate = null;

    /**
     * @var \ArchiflowWSCard\Type\DigestTarget
     */
    private $target = null;

    /**
     * @var bool
     */
    private $bRemoveTempFile = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @var string $strCertificate
     * @var \ArchiflowWSCard\Type\DigestTarget $target
     * @var bool $bRemoveTempFile
     */
    public function __construct($strSessionId, $oCardIds, $strCertificate, $target, $bRemoveTempFile)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardIds = $oCardIds;
        $this->strCertificate = $strCertificate;
        $this->target = $target;
        $this->bRemoveTempFile = $bRemoveTempFile;
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
     * @return BuildFileDigest
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOCardIds()
    {
        return $this->oCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @return BuildFileDigest
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrCertificate()
    {
        return $this->strCertificate;
    }

    /**
     * @param string $strCertificate
     * @return BuildFileDigest
     */
    public function withStrCertificate($strCertificate)
    {
        $new = clone $this;
        $new->strCertificate = $strCertificate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DigestTarget
     */
    public function getTarget()
    {
        return $this->target;
    }

    /**
     * @param \ArchiflowWSCard\Type\DigestTarget $target
     * @return BuildFileDigest
     */
    public function withTarget($target)
    {
        $new = clone $this;
        $new->target = $target;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBRemoveTempFile()
    {
        return $this->bRemoveTempFile;
    }

    /**
     * @param bool $bRemoveTempFile
     * @return BuildFileDigest
     */
    public function withBRemoveTempFile($bRemoveTempFile)
    {
        $new = clone $this;
        $new->bRemoveTempFile = $bRemoveTempFile;

        return $new;
    }


}

