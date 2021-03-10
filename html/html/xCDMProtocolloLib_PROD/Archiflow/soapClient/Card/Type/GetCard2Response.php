<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCard2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCard2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $oCard = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCard2Result()
    {
        return $this->GetCard2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCard2Result
     * @return GetCard2Response
     */
    public function withGetCard2Result($GetCard2Result)
    {
        $new = clone $this;
        $new->GetCard2Result = $GetCard2Result;

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
     * @return GetCard2Response
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }


}

