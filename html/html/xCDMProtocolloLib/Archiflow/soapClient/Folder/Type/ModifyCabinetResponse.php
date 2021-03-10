<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyCabinetResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $ModifyCabinetResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getModifyCabinetResult()
    {
        return $this->ModifyCabinetResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $ModifyCabinetResult
     * @return ModifyCabinetResponse
     */
    public function withModifyCabinetResult($ModifyCabinetResult)
    {
        $new = clone $this;
        $new->ModifyCabinetResult = $ModifyCabinetResult;

        return $new;
    }


}

