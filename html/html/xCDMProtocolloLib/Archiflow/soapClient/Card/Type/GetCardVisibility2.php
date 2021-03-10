<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardVisibility2 implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardVisibilityRequest
     */
    private $visRequest = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\CardVisibilityRequest $visRequest
     */
    public function __construct($strSessionId, $visRequest)
    {
        $this->strSessionId = $strSessionId;
        $this->visRequest = $visRequest;
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
     * @return GetCardVisibility2
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardVisibilityRequest
     */
    public function getVisRequest()
    {
        return $this->visRequest;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardVisibilityRequest $visRequest
     * @return GetCardVisibility2
     */
    public function withVisRequest($visRequest)
    {
        $new = clone $this;
        $new->visRequest = $visRequest;

        return $new;
    }


}

