<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExternNotification implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfExternNotificationOffice
     */
    private $OfficesAddress = null;

    /**
     * @var \ArchiflowWSCard\Type\ExternNotificationUsers
     */
    private $UsersAddress = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfExternNotificationOffice $OfficesAddress
     * @var \ArchiflowWSCard\Type\ExternNotificationUsers $UsersAddress
     */
    public function __construct($OfficesAddress, $UsersAddress)
    {
        $this->OfficesAddress = $OfficesAddress;
        $this->UsersAddress = $UsersAddress;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfExternNotificationOffice
     */
    public function getOfficesAddress()
    {
        return $this->OfficesAddress;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfExternNotificationOffice $OfficesAddress
     * @return ExternNotification
     */
    public function withOfficesAddress($OfficesAddress)
    {
        $new = clone $this;
        $new->OfficesAddress = $OfficesAddress;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternNotificationUsers
     */
    public function getUsersAddress()
    {
        return $this->UsersAddress;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternNotificationUsers $UsersAddress
     * @return ExternNotification
     */
    public function withUsersAddress($UsersAddress)
    {
        $new = clone $this;
        $new->UsersAddress = $UsersAddress;

        return $new;
    }


}

