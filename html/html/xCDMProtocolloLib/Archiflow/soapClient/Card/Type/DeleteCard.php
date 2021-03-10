<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteCard implements RequestInterface
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
     * @var bool
     */
    private $bDeleteLast = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bDeleteLast
     */
    public function __construct($strSessionId, $oCardId, $bDeleteLast)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bDeleteLast = $bDeleteLast;
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
     * @return DeleteCard
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
     * @return DeleteCard
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
    public function getBDeleteLast()
    {
        return $this->bDeleteLast;
    }

    /**
     * @param bool $bDeleteLast
     * @return DeleteCard
     */
    public function withBDeleteLast($bDeleteLast)
    {
        $new = clone $this;
        $new->bDeleteLast = $bDeleteLast;

        return $new;
    }


}

