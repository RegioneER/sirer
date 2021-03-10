<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCardContact implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardContact
     */
    private $AgrafCardContact = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCardContact $AgrafCardContact
     */
    public function __construct($AgrafCardContact)
    {
        $this->AgrafCardContact = $AgrafCardContact;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardContact
     */
    public function getAgrafCardContact()
    {
        return $this->AgrafCardContact;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardContact $AgrafCardContact
     * @return ArrayOfAgrafCardContact
     */
    public function withAgrafCardContact($AgrafCardContact)
    {
        $new = clone $this;
        $new->AgrafCardContact = $AgrafCardContact;

        return $new;
    }


}

