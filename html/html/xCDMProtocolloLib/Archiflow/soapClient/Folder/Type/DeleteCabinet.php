<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteCabinet implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var int $cabinetId
     */
    public function __construct($strSessionId, $cabinetId)
    {
        $this->strSessionId = $strSessionId;
        $this->cabinetId = $cabinetId;
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
     * @return DeleteCabinet
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
     * @return DeleteCabinet
     */
    public function withCabinetId($cabinetId)
    {
        $new = clone $this;
        $new->cabinetId = $cabinetId;

        return $new;
    }


}

