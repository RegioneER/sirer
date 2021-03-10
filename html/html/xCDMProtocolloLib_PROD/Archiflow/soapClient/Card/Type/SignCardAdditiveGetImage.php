<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SignCardAdditiveGetImage implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\Additive
     */
    private $oAdditive = null;

    /**
     * @var \ArchiflowWSCard\Type\ImageFormat
     */
    private $imageformat = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\Additive $oAdditive
     * @var \ArchiflowWSCard\Type\ImageFormat $imageformat
     */
    public function __construct($oSessionInfo, $oCardId, $oAdditive, $imageformat)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardId = $oCardId;
        $this->oAdditive = $oAdditive;
        $this->imageformat = $imageformat;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @return SignCardAdditiveGetImage
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

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
     * @return SignCardAdditiveGetImage
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Additive
     */
    public function getOAdditive()
    {
        return $this->oAdditive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Additive $oAdditive
     * @return SignCardAdditiveGetImage
     */
    public function withOAdditive($oAdditive)
    {
        $new = clone $this;
        $new->oAdditive = $oAdditive;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ImageFormat
     */
    public function getImageformat()
    {
        return $this->imageformat;
    }

    /**
     * @param \ArchiflowWSCard\Type\ImageFormat $imageformat
     * @return SignCardAdditiveGetImage
     */
    public function withImageformat($imageformat)
    {
        $new = clone $this;
        $new->imageformat = $imageformat;

        return $new;
    }


}

