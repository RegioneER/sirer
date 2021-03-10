<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateCard implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\InsertParameters
     */
    private $oInsertParameters = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\InsertParameters $oInsertParameters
     */
    public function __construct($strSessionId, $oInsertParameters)
    {
        $this->strSessionId = $strSessionId;
        $this->oInsertParameters = $oInsertParameters;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return CreateCard
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InsertParameters
     */
    public function getOInsertParameters()
    {
        return $this->oInsertParameters;
    }

    /**
     * @param \ArchiflowWSCard\Type\InsertParameters $oInsertParameters
     * @return CreateCard
     */
    public function withOInsertParameters($oInsertParameters)
    {
        $new = clone $this;
        $new->oInsertParameters = $oInsertParameters;

        return $new;
    }


}

