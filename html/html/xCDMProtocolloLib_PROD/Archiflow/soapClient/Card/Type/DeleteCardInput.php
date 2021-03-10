<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteCardInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardDelete
     */
    private $Delete = null;

    /**
     * @var bool
     */
    private $DeleteLast = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \ArchiflowWSCard\Type\CardDelete $Delete
     * @var bool $DeleteLast
     */
    public function __construct($CardId, $Delete, $DeleteLast)
    {
        $this->CardId = $CardId;
        $this->Delete = $Delete;
        $this->DeleteLast = $DeleteLast;
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
     * @return DeleteCardInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardDelete
     */
    public function getDelete()
    {
        return $this->Delete;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardDelete $Delete
     * @return DeleteCardInput
     */
    public function withDelete($Delete)
    {
        $new = clone $this;
        $new->Delete = $Delete;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDeleteLast()
    {
        return $this->DeleteLast;
    }

    /**
     * @param bool $DeleteLast
     * @return DeleteCardInput
     */
    public function withDeleteLast($DeleteLast)
    {
        $new = clone $this;
        $new->DeleteLast = $DeleteLast;

        return $new;
    }


}

