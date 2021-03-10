<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetRegisterRecordsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetRegisterRecordsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfRecord
     */
    private $oRegRecords = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetRegisterRecordsResult()
    {
        return $this->GetRegisterRecordsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetRegisterRecordsResult
     * @return GetRegisterRecordsResponse
     */
    public function withGetRegisterRecordsResult($GetRegisterRecordsResult)
    {
        $new = clone $this;
        $new->GetRegisterRecordsResult = $GetRegisterRecordsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfRecord
     */
    public function getORegRecords()
    {
        return $this->oRegRecords;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfRecord $oRegRecords
     * @return GetRegisterRecordsResponse
     */
    public function withORegRecords($oRegRecords)
    {
        $new = clone $this;
        $new->oRegRecords = $oRegRecords;

        return $new;
    }


}

