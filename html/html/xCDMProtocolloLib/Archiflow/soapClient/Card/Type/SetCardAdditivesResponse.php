<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardAdditivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardAdditivesResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardAdditivesResult()
    {
        return $this->SetCardAdditivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardAdditivesResult
     * @return SetCardAdditivesResponse
     */
    public function withSetCardAdditivesResult($SetCardAdditivesResult)
    {
        $new = clone $this;
        $new->SetCardAdditivesResult = $SetCardAdditivesResult;

        return $new;
    }


}

