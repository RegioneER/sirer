<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class WaterMark implements RequestInterface
{

    /**
     * @var int
     */
    private $Brightness = null;

    /**
     * @var \ArchiflowWSCard\Type\WatermarkFlags
     */
    private $Flags = null;

    /**
     * @var string
     */
    private $Name_1 = null;

    /**
     * @var string
     */
    private $Name_24 = null;

    /**
     * @var string
     */
    private $Name_8G = null;

    /**
     * @var int
     */
    private $PosX = null;

    /**
     * @var int
     */
    private $PosY = null;

    /**
     * @var int
     */
    private $Quality = null;

    /**
     * Constructor
     *
     * @var int $Brightness
     * @var \ArchiflowWSCard\Type\WatermarkFlags $Flags
     * @var string $Name_1
     * @var string $Name_24
     * @var string $Name_8G
     * @var int $PosX
     * @var int $PosY
     * @var int $Quality
     */
    public function __construct($Brightness, $Flags, $Name_1, $Name_24, $Name_8G, $PosX, $PosY, $Quality)
    {
        $this->Brightness = $Brightness;
        $this->Flags = $Flags;
        $this->Name_1 = $Name_1;
        $this->Name_24 = $Name_24;
        $this->Name_8G = $Name_8G;
        $this->PosX = $PosX;
        $this->PosY = $PosY;
        $this->Quality = $Quality;
    }

    /**
     * @return int
     */
    public function getBrightness()
    {
        return $this->Brightness;
    }

    /**
     * @param int $Brightness
     * @return WaterMark
     */
    public function withBrightness($Brightness)
    {
        $new = clone $this;
        $new->Brightness = $Brightness;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\WatermarkFlags
     */
    public function getFlags()
    {
        return $this->Flags;
    }

    /**
     * @param \ArchiflowWSCard\Type\WatermarkFlags $Flags
     * @return WaterMark
     */
    public function withFlags($Flags)
    {
        $new = clone $this;
        $new->Flags = $Flags;

        return $new;
    }

    /**
     * @return string
     */
    public function getName_1()
    {
        return $this->Name_1;
    }

    /**
     * @param string $Name_1
     * @return WaterMark
     */
    public function withName_1($Name_1)
    {
        $new = clone $this;
        $new->Name_1 = $Name_1;

        return $new;
    }

    /**
     * @return string
     */
    public function getName_24()
    {
        return $this->Name_24;
    }

    /**
     * @param string $Name_24
     * @return WaterMark
     */
    public function withName_24($Name_24)
    {
        $new = clone $this;
        $new->Name_24 = $Name_24;

        return $new;
    }

    /**
     * @return string
     */
    public function getName_8G()
    {
        return $this->Name_8G;
    }

    /**
     * @param string $Name_8G
     * @return WaterMark
     */
    public function withName_8G($Name_8G)
    {
        $new = clone $this;
        $new->Name_8G = $Name_8G;

        return $new;
    }

    /**
     * @return int
     */
    public function getPosX()
    {
        return $this->PosX;
    }

    /**
     * @param int $PosX
     * @return WaterMark
     */
    public function withPosX($PosX)
    {
        $new = clone $this;
        $new->PosX = $PosX;

        return $new;
    }

    /**
     * @return int
     */
    public function getPosY()
    {
        return $this->PosY;
    }

    /**
     * @param int $PosY
     * @return WaterMark
     */
    public function withPosY($PosY)
    {
        $new = clone $this;
        $new->PosY = $PosY;

        return $new;
    }

    /**
     * @return int
     */
    public function getQuality()
    {
        return $this->Quality;
    }

    /**
     * @param int $Quality
     * @return WaterMark
     */
    public function withQuality($Quality)
    {
        $new = clone $this;
        $new->Quality = $Quality;

        return $new;
    }


}

