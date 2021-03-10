<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CheckPrivacyVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CheckPrivacyVisibilityOutput
     */
    private $CheckPrivacyVisibilityResult = null;

    /**
     * @return \ArchiflowWSCard\Type\CheckPrivacyVisibilityOutput
     */
    public function getCheckPrivacyVisibilityResult()
    {
        return $this->CheckPrivacyVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\CheckPrivacyVisibilityOutput
     * $CheckPrivacyVisibilityResult
     * @return CheckPrivacyVisibilityResponse
     */
    public function withCheckPrivacyVisibilityResult($CheckPrivacyVisibilityResult)
    {
        $new = clone $this;
        $new->CheckPrivacyVisibilityResult = $CheckPrivacyVisibilityResult;

        return $new;
    }


}

