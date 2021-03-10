<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocComplianceCertificationModelsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocComplianceCertificationModelsResult = null;

    /**
     * @var int
     */
    private $defaultIndex = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $customDescs = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $modelNames = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocComplianceCertificationModelsResult()
    {
        return $this->GetDocComplianceCertificationModelsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo
     * $GetDocComplianceCertificationModelsResult
     * @return GetDocComplianceCertificationModelsResponse
     */
    public function withGetDocComplianceCertificationModelsResult($GetDocComplianceCertificationModelsResult)
    {
        $new = clone $this;
        $new->GetDocComplianceCertificationModelsResult = $GetDocComplianceCertificationModelsResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getDefaultIndex()
    {
        return $this->defaultIndex;
    }

    /**
     * @param int $defaultIndex
     * @return GetDocComplianceCertificationModelsResponse
     */
    public function withDefaultIndex($defaultIndex)
    {
        $new = clone $this;
        $new->defaultIndex = $defaultIndex;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getCustomDescs()
    {
        return $this->customDescs;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $customDescs
     * @return GetDocComplianceCertificationModelsResponse
     */
    public function withCustomDescs($customDescs)
    {
        $new = clone $this;
        $new->customDescs = $customDescs;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getModelNames()
    {
        return $this->modelNames;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $modelNames
     * @return GetDocComplianceCertificationModelsResponse
     */
    public function withModelNames($modelNames)
    {
        $new = clone $this;
        $new->modelNames = $modelNames;

        return $new;
    }


}

