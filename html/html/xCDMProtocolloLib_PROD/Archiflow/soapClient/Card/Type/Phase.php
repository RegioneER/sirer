<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Phase implements RequestInterface
{

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfStatus
     */
    private $StatusList = null;

    /**
     * @var int
     */
    private $Total = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceType
     */
    private $Type = null;

    /**
     * Constructor
     *
     * @var string $Name
     * @var \ArchiflowWSCard\Type\ArrayOfStatus $StatusList
     * @var int $Total
     * @var \ArchiflowWSCard\Type\InvoiceType $Type
     */
    public function __construct($Name, $StatusList, $Total, $Type)
    {
        $this->Name = $Name;
        $this->StatusList = $StatusList;
        $this->Total = $Total;
        $this->Type = $Type;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return Phase
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfStatus
     */
    public function getStatusList()
    {
        return $this->StatusList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfStatus $StatusList
     * @return Phase
     */
    public function withStatusList($StatusList)
    {
        $new = clone $this;
        $new->StatusList = $StatusList;

        return $new;
    }

    /**
     * @return int
     */
    public function getTotal()
    {
        return $this->Total;
    }

    /**
     * @param int $Total
     * @return Phase
     */
    public function withTotal($Total)
    {
        $new = clone $this;
        $new->Total = $Total;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceType
     */
    public function getType()
    {
        return $this->Type;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceType $Type
     * @return Phase
     */
    public function withType($Type)
    {
        $new = clone $this;
        $new->Type = $Type;

        return $new;
    }


}

