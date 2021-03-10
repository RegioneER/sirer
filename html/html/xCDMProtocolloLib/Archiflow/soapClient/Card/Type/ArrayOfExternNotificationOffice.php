<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfExternNotificationOffice implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ExternNotificationOffice
     */
    private $ExternNotificationOffice = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ExternNotificationOffice $ExternNotificationOffice
     */
    public function __construct($ExternNotificationOffice)
    {
        $this->ExternNotificationOffice = $ExternNotificationOffice;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternNotificationOffice
     */
    public function getExternNotificationOffice()
    {
        return $this->ExternNotificationOffice;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternNotificationOffice $ExternNotificationOffice
     * @return ArrayOfExternNotificationOffice
     */
    public function withExternNotificationOffice($ExternNotificationOffice)
    {
        $new = clone $this;
        $new->ExternNotificationOffice = $ExternNotificationOffice;

        return $new;
    }


}

