<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteSearchModel implements RequestInterface
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
     * Constructor
     *
     * @var string $sessionId
     * @var bool $isUser
     * @var string $modelName
     */
    public function __construct($sessionId, $isUser, $modelName)
    {
        $this->sessionId = $sessionId;
        $this->isUser = $isUser;
        $this->modelName = $modelName;
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
     * @return DeleteSearchModel
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
     * @return DeleteSearchModel
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
     * @return DeleteSearchModel
     */
    public function withModelName($modelName)
    {
        $new = clone $this;
        $new->modelName = $modelName;

        return $new;
    }


}

