<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardValidation implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\CardStatus
     */
    private $cardStatus = null;

    /**
     * @var string
     */
    private $statusNote = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var \ArchiflowWSCard\Type\CardStatus $cardStatus
     * @var string $statusNote
     */
    public function __construct($sessionId, $cardId, $cardStatus, $statusNote)
    {
        $this->sessionId = $sessionId;
        $this->cardId = $cardId;
        $this->cardStatus = $cardStatus;
        $this->statusNote = $statusNote;
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
     * @return SetCardValidation
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
     * @return SetCardValidation
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardStatus
     */
    public function getCardStatus()
    {
        return $this->cardStatus;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardStatus $cardStatus
     * @return SetCardValidation
     */
    public function withCardStatus($cardStatus)
    {
        $new = clone $this;
        $new->cardStatus = $cardStatus;

        return $new;
    }

    /**
     * @return string
     */
    public function getStatusNote()
    {
        return $this->statusNote;
    }

    /**
     * @param string $statusNote
     * @return SetCardValidation
     */
    public function withStatusNote($statusNote)
    {
        $new = clone $this;
        $new->statusNote = $statusNote;

        return $new;
    }


}

