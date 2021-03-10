<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardNotesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardNotesResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardNotesResult()
    {
        return $this->SetCardNotesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardNotesResult
     * @return SetCardNotesResponse
     */
    public function withSetCardNotesResult($SetCardNotesResult)
    {
        $new = clone $this;
        $new->SetCardNotesResult = $SetCardNotesResult;

        return $new;
    }


}

