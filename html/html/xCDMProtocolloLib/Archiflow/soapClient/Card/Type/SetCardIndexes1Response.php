<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardIndexes1Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardIndexes1Result = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardIndexes1Result()
    {
        return $this->SetCardIndexes1Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardIndexes1Result
     * @return SetCardIndexes1Response
     */
    public function withSetCardIndexes1Result($SetCardIndexes1Result)
    {
        $new = clone $this;
        $new->SetCardIndexes1Result = $SetCardIndexes1Result;

        return $new;
    }


}

