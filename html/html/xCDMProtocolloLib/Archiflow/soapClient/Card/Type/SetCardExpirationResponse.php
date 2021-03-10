<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardExpirationResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SetCardExpirationOutput
     */
    private $SetCardExpirationResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SetCardExpirationOutput
     */
    public function getSetCardExpirationResult()
    {
        return $this->SetCardExpirationResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SetCardExpirationOutput $SetCardExpirationResult
     * @return SetCardExpirationResponse
     */
    public function withSetCardExpirationResult($SetCardExpirationResult)
    {
        $new = clone $this;
        $new->SetCardExpirationResult = $SetCardExpirationResult;

        return $new;
    }


}

