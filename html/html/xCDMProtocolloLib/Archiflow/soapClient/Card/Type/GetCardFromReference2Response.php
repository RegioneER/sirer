<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardFromReference2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardFromReference2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $oCard = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardFromReference2Result()
    {
        return $this->GetCardFromReference2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardFromReference2Result
     * @return GetCardFromReference2Response
     */
    public function withGetCardFromReference2Result($GetCardFromReference2Result)
    {
        $new = clone $this;
        $new->GetCardFromReference2Result = $GetCardFromReference2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Card
     */
    public function getOCard()
    {
        return $this->oCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\Card $oCard
     * @return GetCardFromReference2Response
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }


}

