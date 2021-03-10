<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class OfficeChart implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfint
     */
    private $ChildrenOfficesIds = null;

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var bool
     */
    private $IsExecutiveOffice = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfint $ChildrenOfficesIds
     * @var int $Code
     * @var bool $IsExecutiveOffice
     * @var string $Name
     */
    public function __construct($ChildrenOfficesIds, $Code, $IsExecutiveOffice, $Name)
    {
        $this->ChildrenOfficesIds = $ChildrenOfficesIds;
        $this->Code = $Code;
        $this->IsExecutiveOffice = $IsExecutiveOffice;
        $this->Name = $Name;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfint
     */
    public function getChildrenOfficesIds()
    {
        return $this->ChildrenOfficesIds;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfint $ChildrenOfficesIds
     * @return OfficeChart
     */
    public function withChildrenOfficesIds($ChildrenOfficesIds)
    {
        $new = clone $this;
        $new->ChildrenOfficesIds = $ChildrenOfficesIds;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return OfficeChart
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsExecutiveOffice()
    {
        return $this->IsExecutiveOffice;
    }

    /**
     * @param bool $IsExecutiveOffice
     * @return OfficeChart
     */
    public function withIsExecutiveOffice($IsExecutiveOffice)
    {
        $new = clone $this;
        $new->IsExecutiveOffice = $IsExecutiveOffice;

        return $new;
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
     * @return OfficeChart
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }


}

