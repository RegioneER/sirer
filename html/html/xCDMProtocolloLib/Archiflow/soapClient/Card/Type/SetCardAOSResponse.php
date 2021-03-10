<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardAOSResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardAOSResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardAOSResult()
    {
        return $this->SetCardAOSResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardAOSResult
     * @return SetCardAOSResponse
     */
    public function withSetCardAOSResult($SetCardAOSResult)
    {
        $new = clone $this;
        $new->SetCardAOSResult = $SetCardAOSResult;

        return $new;
    }


}

