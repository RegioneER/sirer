<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardAsReadOnly implements RequestInterface
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
    private $bReadOnly = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bReadOnly
     */
    public function __construct($strSessionId, $oCardId, $bReadOnly)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bReadOnly = $bReadOnly;
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
     * @return SetCardAsReadOnly
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
     * @return SetCardAsReadOnly
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
    public function getBReadOnly()
    {
        return $this->bReadOnly;
    }

    /**
     * @param bool $bReadOnly
     * @return SetCardAsReadOnly
     */
    public function withBReadOnly($bReadOnly)
    {
        $new = clone $this;
        $new->bReadOnly = $bReadOnly;

        return $new;
    }


}

