<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCabinets implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var bool
     */
    private $bGetVisibility = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var bool $bGetVisibility
     */
    public function __construct($strSessionId, $bGetVisibility)
    {
        $this->strSessionId = $strSessionId;
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
     * @return GetCabinets
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetCabinets
     */
    public function withBGetVisibility($bGetVisibility)
    {
        $new = clone $this;
        $new->bGetVisibility = $bGetVisibility;

        return $new;
    }


}

