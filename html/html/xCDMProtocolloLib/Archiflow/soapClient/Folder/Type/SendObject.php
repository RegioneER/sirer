<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendObject implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfSendEntity
     */
    private $SendEntities = null;

    /**
     * @var \ArchiflowWSFolder\Type\SendOptions
     */
    private $SendOptions = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfSendEntity $SendEntities
     * @var \ArchiflowWSFolder\Type\SendOptions $SendOptions
     */
    public function __construct($SendEntities, $SendOptions)
    {
        $this->SendEntities = $SendEntities;
        $this->SendOptions = $SendOptions;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfSendEntity
     */
    public function getSendEntities()
    {
        return $this->SendEntities;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfSendEntity $SendEntities
     * @return SendObject
     */
    public function withSendEntities($SendEntities)
    {
        $new = clone $this;
        $new->SendEntities = $SendEntities;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SendOptions
     */
    public function getSendOptions()
    {
        return $this->SendOptions;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendOptions $SendOptions
     * @return SendObject
     */
    public function withSendOptions($SendOptions)
    {
        $new = clone $this;
        $new->SendOptions = $SendOptions;

        return $new;
    }


}

