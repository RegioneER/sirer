<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardAdditives1Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardAdditives1Result = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardAdditives1Result()
    {
        return $this->SetCardAdditives1Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardAdditives1Result
     * @return SetCardAdditives1Response
     */
    public function withSetCardAdditives1Result($SetCardAdditives1Result)
    {
        $new = clone $this;
        $new->SetCardAdditives1Result = $SetCardAdditives1Result;

        return $new;
    }


}

