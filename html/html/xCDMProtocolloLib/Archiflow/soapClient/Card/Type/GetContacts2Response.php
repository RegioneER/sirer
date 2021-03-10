<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetContacts2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetContacts2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCard
     */
    private $agrafCards = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetContacts2Result()
    {
        return $this->GetContacts2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetContacts2Result
     * @return GetContacts2Response
     */
    public function withGetContacts2Result($GetContacts2Result)
    {
        $new = clone $this;
        $new->GetContacts2Result = $GetContacts2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCard
     */
    public function getAgrafCards()
    {
        return $this->agrafCards;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCard $agrafCards
     * @return GetContacts2Response
     */
    public function withAgrafCards($agrafCards)
    {
        $new = clone $this;
        $new->agrafCards = $agrafCards;

        return $new;
    }


}

