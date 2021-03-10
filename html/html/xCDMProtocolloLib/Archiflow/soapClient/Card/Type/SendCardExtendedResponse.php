<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardExtendedResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SendCardExtendedResult = null;

    /**
     * @var \ArchiflowWSCard\Type\SendingOutValues
     */
    private $oSendingValuesRet = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSendCardExtendedResult()
    {
        return $this->SendCardExtendedResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SendCardExtendedResult
     * @return SendCardExtendedResponse
     */
    public function withSendCardExtendedResult($SendCardExtendedResult)
    {
        $new = clone $this;
        $new->SendCardExtendedResult = $SendCardExtendedResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendingOutValues
     */
    public function getOSendingValuesRet()
    {
        return $this->oSendingValuesRet;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendingOutValues $oSendingValuesRet
     * @return SendCardExtendedResponse
     */
    public function withOSendingValuesRet($oSendingValuesRet)
    {
        $new = clone $this;
        $new->oSendingValuesRet = $oSendingValuesRet;

        return $new;
    }


}

