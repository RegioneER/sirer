<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocComplianceCertificationModels implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * @var \ArchiflowWSCard\Type\CompCertModelType
     */
    private $modelType = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var \ArchiflowWSCard\Type\CompCertModelType $modelType
     */
    public function __construct($sessionId, $cardId, $modelType)
    {
        $this->sessionId = $sessionId;
        $this->cardId = $cardId;
        $this->modelType = $modelType;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->sessionId;
    }

    /**
     * @param string $sessionId
     * @return GetDocComplianceCertificationModels
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->cardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $cardId
     * @return GetDocComplianceCertificationModels
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CompCertModelType
     */
    public function getModelType()
    {
        return $this->modelType;
    }

    /**
     * @param \ArchiflowWSCard\Type\CompCertModelType $modelType
     * @return GetDocComplianceCertificationModels
     */
    public function withModelType($modelType)
    {
        $new = clone $this;
        $new->modelType = $modelType;

        return $new;
    }


}

