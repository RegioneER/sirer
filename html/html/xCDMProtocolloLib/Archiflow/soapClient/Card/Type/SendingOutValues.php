<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendingOutValues implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ExternNotification
     */
    private $ExternMailNotification = null;

    /**
     * @var string
     */
    private $ExternMailNotificationXML = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ExternNotification $ExternMailNotification
     * @var string $ExternMailNotificationXML
     */
    public function __construct($ExternMailNotification, $ExternMailNotificationXML)
    {
        $this->ExternMailNotification = $ExternMailNotification;
        $this->ExternMailNotificationXML = $ExternMailNotificationXML;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternNotification
     */
    public function getExternMailNotification()
    {
        return $this->ExternMailNotification;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternNotification $ExternMailNotification
     * @return SendingOutValues
     */
    public function withExternMailNotification($ExternMailNotification)
    {
        $new = clone $this;
        $new->ExternMailNotification = $ExternMailNotification;

        return $new;
    }

    /**
     * @return string
     */
    public function getExternMailNotificationXML()
    {
        return $this->ExternMailNotificationXML;
    }

    /**
     * @param string $ExternMailNotificationXML
     * @return SendingOutValues
     */
    public function withExternMailNotificationXML($ExternMailNotificationXML)
    {
        $new = clone $this;
        $new->ExternMailNotificationXML = $ExternMailNotificationXML;

        return $new;
    }


}

