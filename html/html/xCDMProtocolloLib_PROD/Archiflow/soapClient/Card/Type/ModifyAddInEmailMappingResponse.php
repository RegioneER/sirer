<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyAddInEmailMappingResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ModifyAddInEmailMappingResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getModifyAddInEmailMappingResult()
    {
        return $this->ModifyAddInEmailMappingResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ModifyAddInEmailMappingResult
     * @return ModifyAddInEmailMappingResponse
     */
    public function withModifyAddInEmailMappingResult($ModifyAddInEmailMappingResult)
    {
        $new = clone $this;
        $new->ModifyAddInEmailMappingResult = $ModifyAddInEmailMappingResult;

        return $new;
    }


}

