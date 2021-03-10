<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDrawers implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $cabinetId = null;

    /**
     * @var bool
     */
    private $bGetVisibility = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $cabinetId
     * @var bool $bGetVisibility
     */
    public function __construct($strSessionId, $cabinetId, $bGetVisibility)
    {
        $this->strSessionId = $strSessionId;
        $this->cabinetId = $cabinetId;
        $this->bGetVisibility = $bGetVisibility;
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
     * @return GetDrawers
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
    public function getCabinetId()
    {
        return $this->cabinetId;
    }

    /**
     * @param int $cabinetId
     * @return GetDrawers
     */
    public function withCabinetId($cabinetId)
    {
        $new = clone $this;
        $new->cabinetId = $cabinetId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetVisibility()
    {
        return $this->bGetVisibility;
    }

    /**
     * @param bool $bGetVisibility
     * @return GetDrawers
     */
    public function withBGetVisibility($bGetVisibility)
    {
        $new = clone $this;
        $new->bGetVisibility = $bGetVisibility;

        return $new;
    }


}

