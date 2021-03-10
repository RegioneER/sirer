<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocument5 implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardContentMode
     */
    private $mode = null;

    /**
     * @var int
     */
    private $nVersion = null;

    /**
     * @var \ArchiflowWSCard\Type\WaterMark
     */
    private $oWaterMark = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\CardContentMode $mode
     * @var int $nVersion
     * @var \ArchiflowWSCard\Type\WaterMark $oWaterMark
     */
    public function __construct($strSessionId, $oCardId, $mode, $nVersion, $oWaterMark)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->mode = $mode;
        $this->nVersion = $nVersion;
        $this->oWaterMark = $oWaterMark;
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
     * @return GetCardDocument5
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetCardDocument5
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardContentMode
     */
    public function getMode()
    {
        return $this->mode;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardContentMode $mode
     * @return GetCardDocument5
     */
    public function withMode($mode)
    {
        $new = clone $this;
        $new->mode = $mode;

        return $new;
    }

    /**
     * @return int
     */
    public function getNVersion()
    {
        return $this->nVersion;
    }

    /**
     * @param int $nVersion
     * @return GetCardDocument5
     */
    public function withNVersion($nVersion)
    {
        $new = clone $this;
        $new->nVersion = $nVersion;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\WaterMark
     */
    public function getOWaterMark()
    {
        return $this->oWaterMark;
    }

    /**
     * @param \ArchiflowWSCard\Type\WaterMark $oWaterMark
     * @return GetCardDocument5
     */
    public function withOWaterMark($oWaterMark)
    {
        $new = clone $this;
        $new->oWaterMark = $oWaterMark;

        return $new;
    }


}

