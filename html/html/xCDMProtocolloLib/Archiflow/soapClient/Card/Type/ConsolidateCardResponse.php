<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ConsolidateCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ConsolidateCardOutput
     */
    private $ConsolidateCardResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ConsolidateCardOutput
     */
    public function getConsolidateCardResult()
    {
        return $this->ConsolidateCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ConsolidateCardOutput $ConsolidateCardResult
     * @return ConsolidateCardResponse
     */
    public function withConsolidateCardResult($ConsolidateCardResult)
    {
        $new = clone $this;
        $new->ConsolidateCardResult = $ConsolidateCardResult;

        return $new;
    }


}

