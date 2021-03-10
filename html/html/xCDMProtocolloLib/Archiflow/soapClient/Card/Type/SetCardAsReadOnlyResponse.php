<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardAsReadOnlyResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardAsReadOnlyResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardAsReadOnlyResult()
    {
        return $this->SetCardAsReadOnlyResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardAsReadOnlyResult
     * @return SetCardAsReadOnlyResponse
     */
    public function withSetCardAsReadOnlyResult($SetCardAsReadOnlyResult)
    {
        $new = clone $this;
        $new->SetCardAsReadOnlyResult = $SetCardAsReadOnlyResult;

        return $new;
    }


}

