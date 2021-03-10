<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCommit implements RequestInterface
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
     * Constructor
     *
     * @var int $year
     * @var int $number
     */
    public function __construct($year, $number)
    {
        $this->year = $year;
        $this->number = $number;
    }

    /**
     * @return int
     */
    public function getYear()
    {
        return $this->year;
    }

    /**
     * @param int $year
     * @return InsertCommit
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
     * @return InsertCommit
     */
    public function withNumber($number)
    {
        $new = clone $this;
        $new->number = $number;

        return $new;
    }


}

