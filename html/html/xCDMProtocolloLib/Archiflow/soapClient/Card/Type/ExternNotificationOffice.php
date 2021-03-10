<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExternNotificationOffice implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $Adresses = null;

    /**
     * @var int
     */
    private $OfficeID = null;

    /**
     * @var string
     */
    private $URL = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfstring $Adresses
     * @var int $OfficeID
     * @var string $URL
     */
    public function __construct($Adresses, $OfficeID, $URL)
    {
        $this->Adresses = $Adresses;
        $this->OfficeID = $OfficeID;
        $this->URL = $URL;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getAdresses()
    {
        return $this->Adresses;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $Adresses
     * @return ExternNotificationOffice
     */
    public function withAdresses($Adresses)
    {
        $new = clone $this;
        $new->Adresses = $Adresses;

        return $new;
    }

    /**
     * @return int
     */
    public function getOfficeID()
    {
        return $this->OfficeID;
    }

    /**
     * @param int $OfficeID
     * @return ExternNotificationOffice
     */
    public function withOfficeID($OfficeID)
    {
        $new = clone $this;
        $new->OfficeID = $OfficeID;

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
     * @return ExternNotificationOffice
     */
    public function withURL($URL)
    {
        $new = clone $this;
        $new->URL = $URL;

        return $new;
    }


}

