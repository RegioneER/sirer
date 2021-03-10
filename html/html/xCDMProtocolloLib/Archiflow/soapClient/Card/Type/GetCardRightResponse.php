<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardRightResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardRightResult = null;

    /**
     * @var bool
     */
    private $bHasRight = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardRightResult()
    {
        return $this->GetCardRightResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardRightResult
     * @return GetCardRightResponse
     */
    public function withGetCardRightResult($GetCardRightResult)
    {
        $new = clone $this;
        $new->GetCardRightResult = $GetCardRightResult;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBHasRight()
    {
        return $this->bHasRight;
    }

    /**
     * @param bool $bHasRight
     * @return GetCardRightResponse
     */
    public function withBHasRight($bHasRight)
    {
        $new = clone $this;
        $new->bHasRight = $bHasRight;

        return $new;
    }


}

