<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCabinet implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSFolder\Type\Cabinet
     */
    private $oCabinet = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSFolder\Type\Cabinet $oCabinet
     */
    public function __construct($strSessionId, $oCabinet)
    {
        $this->strSessionId = $strSessionId;
        $this->oCabinet = $oCabinet;
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
     * @return InsertCabinet
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Cabinet
     */
    public function getOCabinet()
    {
        return $this->oCabinet;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Cabinet $oCabinet
     * @return InsertCabinet
     */
    public function withOCabinet($oCabinet)
    {
        $new = clone $this;
        $new->oCabinet = $oCabinet;

        return $new;
    }


}

