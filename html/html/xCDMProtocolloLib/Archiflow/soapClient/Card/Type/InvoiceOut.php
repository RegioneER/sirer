<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceOut implements RequestInterface
{

    /**
     * @var \DateTime
     */
    private $SendDate = null;

    /**
     * @var int
     */
    private $SendStatus = null;

    /**
     * Constructor
     *
     * @var \DateTime $SendDate
     * @var int $SendStatus
     */
    public function __construct($SendDate, $SendStatus)
    {
        $this->SendDate = $SendDate;
        $this->SendStatus = $SendStatus;
    }

    /**
     * @return \DateTime
     */
    public function getSendDate()
    {
        return $this->SendDate;
    }

    /**
     * @param \DateTime $SendDate
     * @return InvoiceOut
     */
    public function withSendDate($SendDate)
    {
        $new = clone $this;
        $new->SendDate = $SendDate;

        return $new;
    }

    /**
     * @return int
     */
    public function getSendStatus()
    {
        return $this->SendStatus;
    }

    /**
     * @param int $SendStatus
     * @return InvoiceOut
     */
    public function withSendStatus($SendStatus)
    {
        $new = clone $this;
        $new->SendStatus = $SendStatus;

        return $new;
    }


}

