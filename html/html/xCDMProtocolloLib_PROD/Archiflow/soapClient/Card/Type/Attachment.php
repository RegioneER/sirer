<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Attachment implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * @var int
     */
    private $SecurityUserId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $Code
     * @var string $Name
     * @var string $Note
     * @var int $SecurityUserId
     */
    public function __construct($CardId, $Code, $Name, $Note, $SecurityUserId)
    {
        $this->CardId = $CardId;
        $this->Code = $Code;
        $this->Name = $Name;
        $this->Note = $Note;
        $this->SecurityUserId = $SecurityUserId;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return Attachment
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return Attachment
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return Attachment
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return string
     */
    public function getNote()
    {
        return $this->Note;
    }

    /**
     * @param string $Note
     * @return Attachment
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

        return $new;
    }

    /**
     * @return int
     */
    public function getSecurityUserId()
    {
        return $this->SecurityUserId;
    }

    /**
     * @param int $SecurityUserId
     * @return Attachment
     */
    public function withSecurityUserId($SecurityUserId)
    {
        $new = clone $this;
        $new->SecurityUserId = $SecurityUserId;

        return $new;
    }


}

