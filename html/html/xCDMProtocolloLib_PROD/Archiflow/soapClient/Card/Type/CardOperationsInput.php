<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardOperationsInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $GetAll = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCardOperation
     */
    private $OperationsFilter = null;

    /**
     * @var bool
     */
    private $TestSdIXmlIsSigned = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $WorkItemId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $GetAll
     * @var \ArchiflowWSCard\Type\ArrayOfCardOperation $OperationsFilter
     * @var bool $TestSdIXmlIsSigned
     * @var \ArchiflowWSCard\Type\Guid $WorkItemId
     */
    public function __construct($CardId, $GetAll, $OperationsFilter, $TestSdIXmlIsSigned, $WorkItemId)
    {
        $this->CardId = $CardId;
        $this->GetAll = $GetAll;
        $this->OperationsFilter = $OperationsFilter;
        $this->TestSdIXmlIsSigned = $TestSdIXmlIsSigned;
        $this->WorkItemId = $WorkItemId;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return CardOperationsInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetAll()
    {
        return $this->GetAll;
    }

    /**
     * @param bool $GetAll
     * @return CardOperationsInput
     */
    public function withGetAll($GetAll)
    {
        $new = clone $this;
        $new->GetAll = $GetAll;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfCardOperation
     */
    public function getOperationsFilter()
    {
        return $this->OperationsFilter;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfCardOperation $OperationsFilter
     * @return CardOperationsInput
     */
    public function withOperationsFilter($OperationsFilter)
    {
        $new = clone $this;
        $new->OperationsFilter = $OperationsFilter;

        return $new;
    }

    /**
     * @return bool
     */
    public function getTestSdIXmlIsSigned()
    {
        return $this->TestSdIXmlIsSigned;
    }

    /**
     * @param bool $TestSdIXmlIsSigned
     * @return CardOperationsInput
     */
    public function withTestSdIXmlIsSigned($TestSdIXmlIsSigned)
    {
        $new = clone $this;
        $new->TestSdIXmlIsSigned = $TestSdIXmlIsSigned;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getWorkItemId()
    {
        return $this->WorkItemId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $WorkItemId
     * @return CardOperationsInput
     */
    public function withWorkItemId($WorkItemId)
    {
        $new = clone $this;
        $new->WorkItemId = $WorkItemId;

        return $new;
    }


}

