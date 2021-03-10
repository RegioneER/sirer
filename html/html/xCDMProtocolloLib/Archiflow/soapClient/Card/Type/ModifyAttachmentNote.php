<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyAttachmentNote implements RequestInterface
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
     * @var int
     */
    private $attachmentCode = null;

    /**
     * @var string
     */
    private $newNote = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var int $attachmentCode
     * @var string $newNote
     */
    public function __construct($sessionId, $cardId, $attachmentCode, $newNote)
    {
        $this->sessionId = $sessionId;
        $this->cardId = $cardId;
        $this->attachmentCode = $attachmentCode;
        $this->newNote = $newNote;
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
     * @return ModifyAttachmentNote
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
     * @return ModifyAttachmentNote
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getAttachmentCode()
    {
        return $this->attachmentCode;
    }

    /**
     * @param int $attachmentCode
     * @return ModifyAttachmentNote
     */
    public function withAttachmentCode($attachmentCode)
    {
        $new = clone $this;
        $new->attachmentCode = $attachmentCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getNewNote()
    {
        return $this->newNote;
    }

    /**
     * @param string $newNote
     * @return ModifyAttachmentNote
     */
    public function withNewNote($newNote)
    {
        $new = clone $this;
        $new->newNote = $newNote;

        return $new;
    }


}

