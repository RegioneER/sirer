<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetProtocolStatus implements RequestInterface
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
     * @var string
     */
    private $statusCode = null;

    /**
     * @return int
     */
    public function getYear()
    {
        return $this->year;
    }

    /**
     * @param int $year
     * @return SetProtocolStatus
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
     * @return SetProtocolStatus
     */
    public function withNumber($number)
    {
        $new = clone $this;
        $new->number = $number;

        return $new;
    }

    /**
     * @return string
     */
    public function getStatusCode()
    {
        return $this->statusCode;
    }

    /**
     * @param string $statusCode
     * @return SetProtocolStatus
     */
    public function withStatusCode($statusCode)
    {
        $new = clone $this;
        $new->statusCode = $statusCode;

        return $new;
    }


}

