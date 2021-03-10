<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ResetCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResetCardOutput
     */
    private $ResetCardResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResetCardOutput
     */
    public function getResetCardResult()
    {
        return $this->ResetCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResetCardOutput $ResetCardResult
     * @return ResetCardResponse
     */
    public function withResetCardResult($ResetCardResult)
    {
        $new = clone $this;
        $new->ResetCardResult = $ResetCardResult;

        return $new;
    }


}

