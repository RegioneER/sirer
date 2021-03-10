<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfDrawer implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Drawer
     */
    private $Drawer = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Drawer $Drawer
     */
    public function __construct($Drawer)
    {
        $this->Drawer = $Drawer;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Drawer
     */
    public function getDrawer()
    {
        return $this->Drawer;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Drawer $Drawer
     * @return ArrayOfDrawer
     */
    public function withDrawer($Drawer)
    {
        $new = clone $this;
        $new->Drawer = $Drawer;

        return $new;
    }


}

