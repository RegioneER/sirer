<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetPecs implements RequestInterface
{

    /**
     * @var int
     */
    private $year = null;

    /**
     * @var int
     */
    private $number = null;

    /**
     * @return int
     */
    public function getYear()
    {
        return $this->year;
    }

    /**
     * @param int $year
     * @return GetPecs
     */
    public function withYear($year)
    {
        $new = clone $this;
        $new->year = $year;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumber()
    {
        return $this->number;
    }

    /**
     * @param int $number
     * @return GetPecs
     */
    public function withNumber($number)
    {
        $new = clone $this;
        $new->number = $number;

        return $new;
    }


}

