<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardNotesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardNotesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAnnotation
     */
    private $oAnnotations = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardNotesResult()
    {
        return $this->GetCardNotesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardNotesResult
     * @return GetCardNotesResponse
     */
    public function withGetCardNotesResult($GetCardNotesResult)
    {
        $new = clone $this;
        $new->GetCardNotesResult = $GetCardNotesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAnnotation
     */
    public function getOAnnotations()
    {
        return $this->oAnnotations;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAnnotation $oAnnotations
     * @return GetCardNotesResponse
     */
    public function withOAnnotations($oAnnotations)
    {
        $new = clone $this;
        $new->oAnnotations = $oAnnotations;

        return $new;
    }


}

