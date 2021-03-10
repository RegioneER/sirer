<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardExpirationInfo implements RequestInterface
{

    /**
     * @var int
     */
    private $Duration = null;

    /**
     * @var \DateTime
     */
    private $ExpirationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\ExpirationMethodType
     */
    private $ExpirationMethod = null;

    /**
     * Constructor
     *
     * @var int $Duration
     * @var \DateTime $ExpirationDate
     * @var \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     */
    public function __construct($Duration, $ExpirationDate, $ExpirationMethod)
    {
        $this->Duration = $Duration;
        $this->ExpirationDate = $ExpirationDate;
        $this->ExpirationMethod = $ExpirationMethod;
    }

    /**
     * @return int
     */
    public function getDuration()
    {
        return $this->Duration;
    }

    /**
     * @param int $Duration
     * @return CardExpirationInfo
     */
    public function withDuration($Duration)
    {
        $new = clone $this;
        $new->Duration = $Duration;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getExpirationDate()
    {
        return $this->ExpirationDate;
    }

    /**
     * @param \DateTime $ExpirationDate
     * @return CardExpirationInfo
     */
    public function withExpirationDate($ExpirationDate)
    {
        $new = clone $this;
        $new->ExpirationDate = $ExpirationDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExpirationMethodType
     */
    public function getExpirationMethod()
    {
        return $this->ExpirationMethod;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @return CardExpirationInfo
     */
    public function withExpirationMethod($ExpirationMethod)
    {
        $new = clone $this;
        $new->ExpirationMethod = $ExpirationMethod;

        return $new;
    }


}

