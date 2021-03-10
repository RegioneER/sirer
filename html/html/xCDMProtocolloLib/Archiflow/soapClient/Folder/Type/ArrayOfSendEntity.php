<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfSendEntity implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SendEntity
     */
    private $SendEntity = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\SendEntity $SendEntity
     */
    public function __construct($SendEntity)
    {
        $this->SendEntity = $SendEntity;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SendEntity
     */
    public function getSendEntity()
    {
        return $this->SendEntity;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendEntity $SendEntity
     * @return ArrayOfSendEntity
     */
    public function withSendEntity($SendEntity)
    {
        $new = clone $this;
        $new->SendEntity = $SendEntity;

        return $new;
    }


}

