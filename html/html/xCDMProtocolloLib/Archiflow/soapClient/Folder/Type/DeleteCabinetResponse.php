<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteCabinetResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $DeleteCabinetResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getDeleteCabinetResult()
    {
        return $this->DeleteCabinetResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $DeleteCabinetResult
     * @return DeleteCabinetResponse
     */
    public function withDeleteCabinetResult($DeleteCabinetResult)
    {
        $new = clone $this;
        $new->DeleteCabinetResult = $DeleteCabinetResult;

        return $new;
    }


}

