<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentInfoByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentInfoOutput
     */
    private $GetCardDocumentInfoByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentInfoOutput
     */
    public function getGetCardDocumentInfoByParamResult()
    {
        return $this->GetCardDocumentInfoByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentInfoOutput
     * $GetCardDocumentInfoByParamResult
     * @return GetCardDocumentInfoByParamResponse
     */
    public function withGetCardDocumentInfoByParamResult($GetCardDocumentInfoByParamResult)
    {
        $new = clone $this;
        $new->GetCardDocumentInfoByParamResult = $GetCardDocumentInfoByParamResult;

        return $new;
    }


}

