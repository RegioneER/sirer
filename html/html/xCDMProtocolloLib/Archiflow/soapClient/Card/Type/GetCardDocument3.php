<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocument3 implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\CardContentMode $mode
     */
    public function __construct($strSessionId, $oCardId, $mode)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->mode = $mode;
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
     * @return GetCardDocument3
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
     * @return GetCardDocument3
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
     * @return GetCardDocument3
     */
    public function withMode($mode)
    {
        $new = clone $this;
        $new->mode = $mode;

        return $new;
    }


}

