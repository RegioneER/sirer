<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyListItemResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ModifyListItemResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getModifyListItemResult()
    {
        return $this->ModifyListItemResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ModifyListItemResult
     * @return ModifyListItemResponse
     */
    public function withModifyListItemResult($ModifyListItemResult)
    {
        $new = clone $this;
        $new->ModifyListItemResult = $ModifyListItemResult;

        return $new;
    }


}

