<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardRight implements RequestInterface
{

    /**
     * @var bool
     */
    private $Enabled = null;

    /**
     * @var \ArchiflowWSCard\Type\RightsRwCard
     */
    private $Id = null;

    /**
     * Constructor
     *
     * @var bool $Enabled
     * @var \ArchiflowWSCard\Type\RightsRwCard $Id
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
     * @return CardRight
     */
    public function withEnabled($Enabled)
    {
        $new = clone $this;
        $new->Enabled = $Enabled;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RightsRwCard
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param \ArchiflowWSCard\Type\RightsRwCard $Id
     * @return CardRight
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }


}

