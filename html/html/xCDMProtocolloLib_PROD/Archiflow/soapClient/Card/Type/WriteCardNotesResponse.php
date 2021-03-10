<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class WriteCardNotesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $WriteCardNotesResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getWriteCardNotesResult()
    {
        return $this->WriteCardNotesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $WriteCardNotesResult
     * @return WriteCardNotesResponse
     */
    public function withWriteCardNotesResult($WriteCardNotesResult)
    {
        $new = clone $this;
        $new->WriteCardNotesResult = $WriteCardNotesResult;

        return $new;
    }


}

