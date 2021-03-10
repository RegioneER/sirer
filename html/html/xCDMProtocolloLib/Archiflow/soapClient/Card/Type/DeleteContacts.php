<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteContacts implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $sessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContactId
     */
    private $contactsId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContactId $contactsId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     */
    public function __construct($sessionInfo, $contactsId, $cardId)
    {
        $this->sessionInfo = $sessionInfo;
        $this->contactsId = $contactsId;
        $this->cardId = $cardId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getSessionInfo()
    {
        return $this->sessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @return DeleteContacts
     */
    public function withSessionInfo($sessionInfo)
    {
        $new = clone $this;
        $new->sessionInfo = $sessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardContactId
     */
    public function getContactsId()
    {
        return $this->contactsId;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardContactId $contactsId
     * @return DeleteContacts
     */
    public function withContactsId($contactsId)
    {
        $new = clone $this;
        $new->contactsId = $contactsId;

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
     * @return DeleteContacts
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }


}

