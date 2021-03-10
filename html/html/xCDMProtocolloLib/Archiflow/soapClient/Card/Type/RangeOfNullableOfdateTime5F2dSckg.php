<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RangeOfNullableOfdateTime5F2dSckg implements RequestInterface
{

    /**
     * @var \DateTime
     */
    private $From = null;

    /**
     * @var \DateTime
     */
    private $To = null;

    /**
     * Constructor
     *
     * @var \DateTime $From
     * @var \DateTime $To
     */
    public function __construct($From, $To)
    {
        $this->From = $From;
        $this->To = $To;
    }

    /**
     * @return \DateTime
     */
    public function getFrom()
    {
        return $this->From;
    }

    /**
     * @param \DateTime $From
     * @return RangeOfNullableOfdateTime5F2dSckg
     */
    public function withFrom($From)
    {
        $new = clone $this;
        $new->From = $From;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getTo()
    {
        return $this->To;
    }

    /**
     * @param \DateTime $To
     * @return RangeOfNullableOfdateTime5F2dSckg
     */
    public function withTo($To)
    {
        $new = clone $this;
        $new->To = $To;

        return $new;
    }


}

