<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendObject implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfSendEntity
     */
    private $SendEntities = null;

    /**
     * @var \ArchiflowWSCard\Type\SendOptions
     */
    private $SendOptions = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfSendEntity $SendEntities
     * @var \ArchiflowWSCard\Type\SendOptions $SendOptions
     */
    public function __construct($SendEntities, $SendOptions)
    {
        $this->SendEntities = $SendEntities;
        $this->SendOptions = $SendOptions;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfSendEntity
     */
    public function getSendEntities()
    {
        return $this->SendEntities;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfSendEntity $SendEntities
     * @return SendObject
     */
    public function withSendEntities($SendEntities)
    {
        $new = clone $this;
        $new->SendEntities = $SendEntities;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendOptions
     */
    public function getSendOptions()
    {
        return $this->SendOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendOptions $SendOptions
     * @return SendObject
     */
    public function withSendOptions($SendOptions)
    {
        $new = clone $this;
        $new->SendOptions = $SendOptions;

        return $new;
    }


}

