<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreateCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CreateCardResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $oCardRet = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCreateCardResult()
    {
        return $this->CreateCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CreateCardResult
     * @return CreateCardResponse
     */
    public function withCreateCardResult($CreateCardResult)
    {
        $new = clone $this;
        $new->CreateCardResult = $CreateCardResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Card
     */
    public function getOCardRet()
    {
        return $this->oCardRet;
    }

    /**
     * @param \ArchiflowWSCard\Type\Card $oCardRet
     * @return CreateCardResponse
     */
    public function withOCardRet($oCardRet)
    {
        $new = clone $this;
        $new->oCardRet = $oCardRet;

        return $new;
    }


}

