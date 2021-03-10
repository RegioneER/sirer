<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExternNotification implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfExternNotificationOffice
     */
    private $OfficesAddress = null;

    /**
     * @var \ArchiflowWSFolder\Type\ExternNotificationUsers
     */
    private $UsersAddress = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfExternNotificationOffice $OfficesAddress
     * @var \ArchiflowWSFolder\Type\ExternNotificationUsers $UsersAddress
     */
    public function __construct($OfficesAddress, $UsersAddress)
    {
        $this->OfficesAddress = $OfficesAddress;
        $this->UsersAddress = $UsersAddress;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfExternNotificationOffice
     */
    public function getOfficesAddress()
    {
        return $this->OfficesAddress;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfExternNotificationOffice $OfficesAddress
     * @return ExternNotification
     */
    public function withOfficesAddress($OfficesAddress)
    {
        $new = clone $this;
        $new->OfficesAddress = $OfficesAddress;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ExternNotificationUsers
     */
    public function getUsersAddress()
    {
        return $this->UsersAddress;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ExternNotificationUsers $UsersAddress
     * @return ExternNotification
     */
    public function withUsersAddress($UsersAddress)
    {
        $new = clone $this;
        $new->UsersAddress = $UsersAddress;

        return $new;
    }


}

