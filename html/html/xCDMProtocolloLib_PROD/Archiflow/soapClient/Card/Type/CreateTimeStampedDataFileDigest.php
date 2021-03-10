<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateTimeStampedDataFileDigest implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var string
     */
    private $xmlDigest = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $lstTSDDigest = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var string $xmlDigest
     * @var \ArchiflowWSCard\Type\ArrayOfstring $lstTSDDigest
     */
    public function __construct($strSessionId, $xmlDigest, $lstTSDDigest)
    {
        $this->strSessionId = $strSessionId;
        $this->xmlDigest = $xmlDigest;
        $this->lstTSDDigest = $lstTSDDigest;
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
     * @return CreateTimeStampedDataFileDigest
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return string
     */
    public function getXmlDigest()
    {
        return $this->xmlDigest;
    }

    /**
     * @param string $xmlDigest
     * @return CreateTimeStampedDataFileDigest
     */
    public function withXmlDigest($xmlDigest)
    {
        $new = clone $this;
        $new->xmlDigest = $xmlDigest;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getLstTSDDigest()
    {
        return $this->lstTSDDigest;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $lstTSDDigest
     * @return CreateTimeStampedDataFileDigest
     */
    public function withLstTSDDigest($lstTSDDigest)
    {
        $new = clone $this;
        $new->lstTSDDigest = $lstTSDDigest;

        return $new;
    }


}

