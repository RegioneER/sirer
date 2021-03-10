<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExternNotificationUsers implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfstring
     */
    private $Adresses = null;

    /**
     * @var string
     */
    private $URL = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfstring $Adresses
     * @var string $URL
     */
    public function __construct($Adresses, $URL)
    {
        $this->Adresses = $Adresses;
        $this->URL = $URL;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfstring
     */
    public function getAdresses()
    {
        return $this->Adresses;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfstring $Adresses
     * @return ExternNotificationUsers
     */
    public function withAdresses($Adresses)
    {
        $new = clone $this;
        $new->Adresses = $Adresses;

        return $new;
    }

    /**
     * @return string
     */
    public function getURL()
    {
        return $this->URL;
    }

    /**
     * @param string $URL
     * @return ExternNotificationUsers
     */
    public function withURL($URL)
    {
        $new = clone $this;
        $new->URL = $URL;

        return $new;
    }


}

