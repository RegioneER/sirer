<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SaveSearchModel implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var bool
     */
    private $isUser = null;

    /**
     * @var string
     */
    private $modelName = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $oSearchCriteria = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var bool $isUser
     * @var string $modelName
     * @var \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     */
    public function __construct($sessionId, $isUser, $modelName, $oSearchCriteria)
    {
        $this->sessionId = $sessionId;
        $this->isUser = $isUser;
        $this->modelName = $modelName;
        $this->oSearchCriteria = $oSearchCriteria;
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
     * @return SaveSearchModel
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsUser()
    {
        return $this->isUser;
    }

    /**
     * @param bool $isUser
     * @return SaveSearchModel
     */
    public function withIsUser($isUser)
    {
        $new = clone $this;
        $new->isUser = $isUser;

        return $new;
    }

    /**
     * @return string
     */
    public function getModelName()
    {
        return $this->modelName;
    }

    /**
     * @param string $modelName
     * @return SaveSearchModel
     */
    public function withModelName($modelName)
    {
        $new = clone $this;
        $new->modelName = $modelName;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getOSearchCriteria()
    {
        return $this->oSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     * @return SaveSearchModel
     */
    public function withOSearchCriteria($oSearchCriteria)
    {
        $new = clone $this;
        $new->oSearchCriteria = $oSearchCriteria;

        return $new;
    }


}

