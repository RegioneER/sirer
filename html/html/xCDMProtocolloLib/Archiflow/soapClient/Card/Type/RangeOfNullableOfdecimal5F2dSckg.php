<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RangeOfNullableOfdecimal5F2dSckg implements RequestInterface
{

    /**
     * @var float
     */
    private $From = null;

    /**
     * @var float
     */
    private $To = null;

    /**
     * Constructor
     *
     * @var float $From
     * @var float $To
     */
    public function __construct($From, $To)
    {
        $this->From = $From;
        $this->To = $To;
    }

    /**
     * @return float
     */
    public function getFrom()
    {
        return $this->From;
    }

    /**
     * @param float $From
     * @return RangeOfNullableOfdecimal5F2dSckg
     */
    public function withFrom($From)
    {
        $new = clone $this;
        $new->From = $From;

        return $new;
    }

    /**
     * @return float
     */
    public function getTo()
    {
        return $this->To;
    }

    /**
     * @param float $To
     * @return RangeOfNullableOfdecimal5F2dSckg
     */
    public function withTo($To)
    {
        $new = clone $this;
        $new->To = $To;

        return $new;
    }


}

