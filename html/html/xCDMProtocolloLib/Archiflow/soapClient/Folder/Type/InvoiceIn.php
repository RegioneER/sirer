<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceIn implements RequestInterface
{

    /**
     * @var \DateTime
     */
    private $ReceiveDate = null;

    /**
     * Constructor
     *
     * @var \DateTime $ReceiveDate
     */
    public function __construct($ReceiveDate)
    {
        $this->ReceiveDate = $ReceiveDate;
    }

    /**
     * @return \DateTime
     */
    public function getReceiveDate()
    {
        return $this->ReceiveDate;
    }

    /**
     * @param \DateTime $ReceiveDate
     * @return InvoiceIn
     */
    public function withReceiveDate($ReceiveDate)
    {
        $new = clone $this;
        $new->ReceiveDate = $ReceiveDate;

        return $new;
    }


}

