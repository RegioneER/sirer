<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RangeOfNullableOfint5F2dSckg implements RequestInterface
{

    /**
     * @var int
     */
    private $From = null;

    /**
     * @var int
     */
    private $To = null;

    /**
     * Constructor
     *
     * @var int $From
     * @var int $To
     */
    public function __construct($From, $To)
    {
        $this->From = $From;
        $this->To = $To;
    }

    /**
     * @return int
     */
    public function getFrom()
    {
        return $this->From;
    }

    /**
     * @param int $From
     * @return RangeOfNullableOfint5F2dSckg
     */
    public function withFrom($From)
    {
        $new = clone $this;
        $new->From = $From;

        return $new;
    }

    /**
     * @return int
     */
    public function getTo()
    {
        return $this->To;
    }

    /**
     * @param int $To
     * @return RangeOfNullableOfint5F2dSckg
     */
    public function withTo($To)
    {
        $new = clone $this;
        $new->To = $To;

        return $new;
    }


}

