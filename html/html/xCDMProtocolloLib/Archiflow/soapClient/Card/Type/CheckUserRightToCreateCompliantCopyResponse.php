<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CheckUserRightToCreateCompliantCopyResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CheckUserRightToCreateCompliantCopyResult = null;

    /**
     * @var bool
     */
    private $retAnalog = null;

    /**
     * @var bool
     */
    private $retDigital = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCheckUserRightToCreateCompliantCopyResult()
    {
        return $this->CheckUserRightToCreateCompliantCopyResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo
     * $CheckUserRightToCreateCompliantCopyResult
     * @return CheckUserRightToCreateCompliantCopyResponse
     */
    public function withCheckUserRightToCreateCompliantCopyResult($CheckUserRightToCreateCompliantCopyResult)
    {
        $new = clone $this;
        $new->CheckUserRightToCreateCompliantCopyResult = $CheckUserRightToCreateCompliantCopyResult;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRetAnalog()
    {
        return $this->retAnalog;
    }

    /**
     * @param bool $retAnalog
     * @return CheckUserRightToCreateCompliantCopyResponse
     */
    public function withRetAnalog($retAnalog)
    {
        $new = clone $this;
        $new->retAnalog = $retAnalog;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRetDigital()
    {
        return $this->retDigital;
    }

    /**
     * @param bool $retDigital
     * @return CheckUserRightToCreateCompliantCopyResponse
     */
    public function withRetDigital($retDigital)
    {
        $new = clone $this;
        $new->retDigital = $retDigital;

        return $new;
    }


}

