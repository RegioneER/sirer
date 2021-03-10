<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCabinetResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $InsertCabinetResult = null;

    /**
     * @var int
     */
    private $newCabinetId = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getInsertCabinetResult()
    {
        return $this->InsertCabinetResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $InsertCabinetResult
     * @return InsertCabinetResponse
     */
    public function withInsertCabinetResult($InsertCabinetResult)
    {
        $new = clone $this;
        $new->InsertCabinetResult = $InsertCabinetResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNewCabinetId()
    {
        return $this->newCabinetId;
    }

    /**
     * @param int $newCabinetId
     * @return InsertCabinetResponse
     */
    public function withNewCabinetId($newCabinetId)
    {
        $new = clone $this;
        $new->newCabinetId = $newCabinetId;

        return $new;
    }


}

