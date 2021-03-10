<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SignFileDigest implements RequestInterface
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
    private $lstSignedDigest = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var string $xmlDigest
     * @var \ArchiflowWSCard\Type\ArrayOfstring $lstSignedDigest
     */
    public function __construct($strSessionId, $xmlDigest, $lstSignedDigest)
    {
        $this->strSessionId = $strSessionId;
        $this->xmlDigest = $xmlDigest;
        $this->lstSignedDigest = $lstSignedDigest;
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
     * @return SignFileDigest
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
     * @return SignFileDigest
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
    public function getLstSignedDigest()
    {
        return $this->lstSignedDigest;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $lstSignedDigest
     * @return SignFileDigest
     */
    public function withLstSignedDigest($lstSignedDigest)
    {
        $new = clone $this;
        $new->lstSignedDigest = $lstSignedDigest;

        return $new;
    }


}

