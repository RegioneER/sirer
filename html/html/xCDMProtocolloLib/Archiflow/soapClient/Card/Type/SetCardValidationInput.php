<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardValidationInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardStatus
     */
    private $CardStatus = null;

    /**
     * @var string
     */
    private $StatusNote = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $Users = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \ArchiflowWSCard\Type\CardStatus $CardStatus
     * @var string $StatusNote
     * @var \ArchiflowWSCard\Type\ArrayOfint $Users
     */
    public function __construct($CardId, $CardStatus, $StatusNote, $Users)
    {
        $this->CardId = $CardId;
        $this->CardStatus = $CardStatus;
        $this->StatusNote = $StatusNote;
        $this->Users = $Users;
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
     * @return SetCardValidationInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardStatus
     */
    public function getCardStatus()
    {
        return $this->CardStatus;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardStatus $CardStatus
     * @return SetCardValidationInput
     */
    public function withCardStatus($CardStatus)
    {
        $new = clone $this;
        $new->CardStatus = $CardStatus;

        return $new;
    }

    /**
     * @return string
     */
    public function getStatusNote()
    {
        return $this->StatusNote;
    }

    /**
     * @param string $StatusNote
     * @return SetCardValidationInput
     */
    public function withStatusNote($StatusNote)
    {
        $new = clone $this;
        $new->StatusNote = $StatusNote;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $Users
     * @return SetCardValidationInput
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

