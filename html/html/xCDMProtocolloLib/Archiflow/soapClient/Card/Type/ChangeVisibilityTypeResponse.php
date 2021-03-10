<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ChangeVisibilityTypeResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ChangeVisibilityTypeOutput
     */
    private $ChangeVisibilityTypeResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ChangeVisibilityTypeOutput
     */
    public function getChangeVisibilityTypeResult()
    {
        return $this->ChangeVisibilityTypeResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ChangeVisibilityTypeOutput
     * $ChangeVisibilityTypeResult
     * @return ChangeVisibilityTypeResponse
     */
    public function withChangeVisibilityTypeResult($ChangeVisibilityTypeResult)
    {
        $new = clone $this;
        $new->ChangeVisibilityTypeResult = $ChangeVisibilityTypeResult;

        return $new;
    }


}

