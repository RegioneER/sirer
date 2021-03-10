<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CheckOut implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * @var int
     */
    private $sSubNetId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var int $sSubNetId
     */
    public function __construct($strSessionId, $cardId, $sSubNetId)
    {
        $this->strSessionId = $strSessionId;
        $this->cardId = $cardId;
        $this->sSubNetId = $sSubNetId;
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
     * @return CheckOut
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
    public function getCardId()
    {
        return $this->cardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $cardId
     * @return CheckOut
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getSSubNetId()
    {
        return $this->sSubNetId;
    }

    /**
     * @param int $sSubNetId
     * @return CheckOut
     */
    public function withSSubNetId($sSubNetId)
    {
        $new = clone $this;
        $new->sSubNetId = $sSubNetId;

        return $new;
    }


}

