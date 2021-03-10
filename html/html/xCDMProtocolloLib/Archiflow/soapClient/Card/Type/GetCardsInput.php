<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $GetAdditives = null;

    /**
     * @var bool
     */
    private $GetIndexes = null;

    /**
     * @var bool
     */
    private $GetInvoices = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var bool $GetAdditives
     * @var bool $GetIndexes
     * @var bool $GetInvoices
     */
    public function __construct($CardIds, $GetAdditives, $GetIndexes, $GetInvoices)
    {
        $this->CardIds = $CardIds;
        $this->GetAdditives = $GetAdditives;
        $this->GetIndexes = $GetIndexes;
        $this->GetInvoices = $GetInvoices;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return GetCardsInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetAdditives()
    {
        return $this->GetAdditives;
    }

    /**
     * @param bool $GetAdditives
     * @return GetCardsInput
     */
    public function withGetAdditives($GetAdditives)
    {
        $new = clone $this;
        $new->GetAdditives = $GetAdditives;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetIndexes()
    {
        return $this->GetIndexes;
    }

    /**
     * @param bool $GetIndexes
     * @return GetCardsInput
     */
    public function withGetIndexes($GetIndexes)
    {
        $new = clone $this;
        $new->GetIndexes = $GetIndexes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetInvoices()
    {
        return $this->GetInvoices;
    }

    /**
     * @param bool $GetInvoices
     * @return GetCardsInput
     */
    public function withGetInvoices($GetInvoices)
    {
        $new = clone $this;
        $new->GetInvoices = $GetInvoices;

        return $new;
    }


}

