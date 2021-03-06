<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class UserRight implements RequestInterface
{

    /**
     * @var bool
     */
    private $Enabled = null;

    /**
     * @var \ArchiflowWSCard\Type\UserRights
     */
    private $Id = null;

    /**
     * Constructor
     *
     * @var bool $Enabled
     * @var \ArchiflowWSCard\Type\UserRights $Id
     */
    public function __construct($Enabled, $Id)
    {
        $this->Enabled = $Enabled;
        $this->Id = $Id;
    }

    /**
     * @return bool
     */
    public function getEnabled()
    {
        return $this->Enabled;
    }

    /**
     * @param bool $Enabled
     * @return UserRight
     */
    public function withEnabled($Enabled)
    {
        $new = clone $this;
        $new->Enabled = $Enabled;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserRights
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserRights $Id
     * @return UserRight
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }


}

