<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetExistingCardVisibilityCC implements RequestInterface
{

    /**
     * @var string
     */
    private $strGuidConnect = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * Constructor
     *
     * @var string $strGuidConnect
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     */
    public function __construct($strGuidConnect, $oCardId)
    {
        $this->strGuidConnect = $strGuidConnect;
        $this->oCardId = $oCardId;
    }

    /**
     * @return string
     */
    public function getStrGuidConnect()
    {
        return $this->strGuidConnect;
    }

    /**
     * @param string $strGuidConnect
     * @return GetExistingCardVisibilityCC
     */
    public function withStrGuidConnect($strGuidConnect)
    {
        $new = clone $this;
        $new->strGuidConnect = $strGuidConnect;

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
     * @return GetExistingCardVisibilityCC
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }


}

