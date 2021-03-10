<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfExternNotificationOffice implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ExternNotificationOffice
     */
    private $ExternNotificationOffice = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ExternNotificationOffice $ExternNotificationOffice
     */
    public function __construct($ExternNotificationOffice)
    {
        $this->ExternNotificationOffice = $ExternNotificationOffice;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ExternNotificationOffice
     */
    public function getExternNotificationOffice()
    {
        return $this->ExternNotificationOffice;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ExternNotificationOffice
     * $ExternNotificationOffice
     * @return ArrayOfExternNotificationOffice
     */
    public function withExternNotificationOffice($ExternNotificationOffice)
    {
        $new = clone $this;
        $new->ExternNotificationOffice = $ExternNotificationOffice;

        return $new;
    }


}

