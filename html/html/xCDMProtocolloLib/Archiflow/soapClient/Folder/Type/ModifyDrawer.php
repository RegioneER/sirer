<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyDrawer implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSFolder\Type\Drawer
     */
    private $oDrawer = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSFolder\Type\Drawer $oDrawer
     */
    public function __construct($strSessionId, $oDrawer)
    {
        $this->strSessionId = $strSessionId;
        $this->oDrawer = $oDrawer;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return ModifyDrawer
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Drawer
     */
    public function getODrawer()
    {
        return $this->oDrawer;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Drawer $oDrawer
     * @return ModifyDrawer
     */
    public function withODrawer($oDrawer)
    {
        $new = clone $this;
        $new->oDrawer = $oDrawer;

        return $new;
    }


}

