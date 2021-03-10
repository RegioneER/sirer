<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendCardsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfSendingOutValues
     */
    private $ListSendingValues = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfSendingOutValues $ListSendingValues
     */
    public function __construct($ListSendingValues)
    {
        $this->ListSendingValues = $ListSendingValues;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfSendingOutValues
     */
    public function getListSendingValues()
    {
        return $this->ListSendingValues;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfSendingOutValues $ListSendingValues
     * @return SendCardsOutput
     */
    public function withListSendingValues($ListSendingValues)
    {
        $new = clone $this;
        $new->ListSendingValues = $ListSendingValues;

        return $new;
    }


}

