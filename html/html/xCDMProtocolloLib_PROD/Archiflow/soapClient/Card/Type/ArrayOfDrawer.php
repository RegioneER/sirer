<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfDrawer implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Drawer
     */
    private $Drawer = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Drawer $Drawer
     */
    public function __construct($Drawer)
    {
        $this->Drawer = $Drawer;
    }

    /**
     * @return \ArchiflowWSCard\Type\Drawer
     */
    public function getDrawer()
    {
        return $this->Drawer;
    }

    /**
     * @param \ArchiflowWSCard\Type\Drawer $Drawer
     * @return ArrayOfDrawer
     */
    public function withDrawer($Drawer)
    {
        $new = clone $this;
        $new->Drawer = $Drawer;

        return $new;
    }


}

