<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Insert implements RequestInterface
{

    /**
     * @var string
     */
    private $xmlProt = null;

    /**
     * Constructor
     *
     * @var string $xmlProt
     */
    public function __construct($xmlProt)
    {
        $this->xmlProt=$xmlProt;
    }

    /**
     * @return string
     */
    public function getXmlProt()
    {
        return $this->xmlProt;
    }

    /**
     * @param string $xmlProt
     * @return Insert
     */
    public function withXmlProt($xmlProt)
    {
        $new = clone $this;
        $new->xmlProt = $xmlProt;

        return $new;
    }


}

