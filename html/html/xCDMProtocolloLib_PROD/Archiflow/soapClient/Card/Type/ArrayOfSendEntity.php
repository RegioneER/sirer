<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfSendEntity implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendEntity
     */
    private $SendEntity = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SendEntity $SendEntity
     */
    public function __construct($SendEntity)
    {
        $this->SendEntity = $SendEntity;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendEntity
     */
    public function getSendEntity()
    {
        return $this->SendEntity;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendEntity $SendEntity
     * @return ArrayOfSendEntity
     */
    public function withSendEntity($SendEntity)
    {
        $new = clone $this;
        $new->SendEntity = $SendEntity;

        return $new;
    }


}

