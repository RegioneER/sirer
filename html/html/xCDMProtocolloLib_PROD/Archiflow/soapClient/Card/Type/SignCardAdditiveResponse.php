<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SignCardAdditiveResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SignCardAdditiveResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSignCardAdditiveResult()
    {
        return $this->SignCardAdditiveResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SignCardAdditiveResult
     * @return SignCardAdditiveResponse
     */
    public function withSignCardAdditiveResult($SignCardAdditiveResult)
    {
        $new = clone $this;
        $new->SignCardAdditiveResult = $SignCardAdditiveResult;

        return $new;
    }


}

