<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $GetAdditives = null;

    /**
     * @var bool
     */
    private $GetHasData = null;

    /**
     * @var bool
     */
    private $GetIndexes = null;

    /**
     * @var bool
     */
    private $GetInvoice = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $GetAdditives
     * @var bool $GetHasData
     * @var bool $GetIndexes
     * @var bool $GetInvoice
     */
    public function __construct($CardId, $GetAdditives, $GetHasData, $GetIndexes, $GetInvoice)
    {
        $this->CardId = $CardId;
        $this->GetAdditives = $GetAdditives;
        $this->GetHasData = $GetHasData;
        $this->GetIndexes = $GetIndexes;
        $this->GetInvoice = $GetInvoice;
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
     * @return GetCardInput
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
    public function getGetAdditives()
    {
        return $this->GetAdditives;
    }

    /**
     * @param bool $GetAdditives
     * @return GetCardInput
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
    public function getGetHasData()
    {
        return $this->GetHasData;
    }

    /**
     * @param bool $GetHasData
     * @return GetCardInput
     */
    public function withGetHasData($GetHasData)
    {
        $new = clone $this;
        $new->GetHasData = $GetHasData;

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
     * @return GetCardInput
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
    public function getGetInvoice()
    {
        return $this->GetInvoice;
    }

    /**
     * @param bool $GetInvoice
     * @return GetCardInput
     */
    public function withGetInvoice($GetInvoice)
    {
        $new = clone $this;
        $new->GetInvoice = $GetInvoice;

        return $new;
    }


}

