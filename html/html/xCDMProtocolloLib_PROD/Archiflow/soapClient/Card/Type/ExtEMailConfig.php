<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExtEMailConfig implements RequestInterface
{

    /**
     * @var bool
     */
    private $ExtendedEMailEnabled = null;

    /**
     * @var \ArchiflowWSCard\Type\ExtendedEMailOptions
     */
    private $ExtendedOptions = null;

    /**
     * @var bool
     */
    private $ExternalEMailEnabled = null;

    /**
     * @var bool
     */
    private $SendAllInOneEMail = null;

    /**
     * @var bool
     */
    private $SendSystemDefaut = null;

    /**
     * @var string
     */
    private $UrlWeb = null;

    /**
     * Constructor
     *
     * @var bool $ExtendedEMailEnabled
     * @var \ArchiflowWSCard\Type\ExtendedEMailOptions $ExtendedOptions
     * @var bool $ExternalEMailEnabled
     * @var bool $SendAllInOneEMail
     * @var bool $SendSystemDefaut
     * @var string $UrlWeb
     */
    public function __construct($ExtendedEMailEnabled, $ExtendedOptions, $ExternalEMailEnabled, $SendAllInOneEMail, $SendSystemDefaut, $UrlWeb)
    {
        $this->ExtendedEMailEnabled = $ExtendedEMailEnabled;
        $this->ExtendedOptions = $ExtendedOptions;
        $this->ExternalEMailEnabled = $ExternalEMailEnabled;
        $this->SendAllInOneEMail = $SendAllInOneEMail;
        $this->SendSystemDefaut = $SendSystemDefaut;
        $this->UrlWeb = $UrlWeb;
    }

    /**
     * @return bool
     */
    public function getExtendedEMailEnabled()
    {
        return $this->ExtendedEMailEnabled;
    }

    /**
     * @param bool $ExtendedEMailEnabled
     * @return ExtEMailConfig
     */
    public function withExtendedEMailEnabled($ExtendedEMailEnabled)
    {
        $new = clone $this;
        $new->ExtendedEMailEnabled = $ExtendedEMailEnabled;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExtendedEMailOptions
     */
    public function getExtendedOptions()
    {
        return $this->ExtendedOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExtendedEMailOptions $ExtendedOptions
     * @return ExtEMailConfig
     */
    public function withExtendedOptions($ExtendedOptions)
    {
        $new = clone $this;
        $new->ExtendedOptions = $ExtendedOptions;

        return $new;
    }

    /**
     * @return bool
     */
    public function getExternalEMailEnabled()
    {
        return $this->ExternalEMailEnabled;
    }

    /**
     * @param bool $ExternalEMailEnabled
     * @return ExtEMailConfig
     */
    public function withExternalEMailEnabled($ExternalEMailEnabled)
    {
        $new = clone $this;
        $new->ExternalEMailEnabled = $ExternalEMailEnabled;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendAllInOneEMail()
    {
        return $this->SendAllInOneEMail;
    }

    /**
     * @param bool $SendAllInOneEMail
     * @return ExtEMailConfig
     */
    public function withSendAllInOneEMail($SendAllInOneEMail)
    {
        $new = clone $this;
        $new->SendAllInOneEMail = $SendAllInOneEMail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendSystemDefaut()
    {
        return $this->SendSystemDefaut;
    }

    /**
     * @param bool $SendSystemDefaut
     * @return ExtEMailConfig
     */
    public function withSendSystemDefaut($SendSystemDefaut)
    {
        $new = clone $this;
        $new->SendSystemDefaut = $SendSystemDefaut;

        return $new;
    }

    /**
     * @return string
     */
    public function getUrlWeb()
    {
        return $this->UrlWeb;
    }

    /**
     * @param string $UrlWeb
     * @return ExtEMailConfig
     */
    public function withUrlWeb($UrlWeb)
    {
        $new = clone $this;
        $new->UrlWeb = $UrlWeb;

        return $new;
    }


}

