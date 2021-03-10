<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AddContactsToCard implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $sessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    private $cardContacts = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContact $cardContacts
     * @var \ArchiflowWSCard\Type\Guid $cardId
     */
    public function __construct($sessionInfo, $cardContacts, $cardId)
    {
        $this->sessionInfo = $sessionInfo;
        $this->cardContacts = $cardContacts;
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
     * @return AddContactsToCard
     */
    public function withSessionInfo($sessionInfo)
    {
        $new = clone $this;
        $new->sessionInfo = $sessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    public function getCardContacts()
    {
        return $this->cardContacts;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardContact $cardContacts
     * @return AddContactsToCard
     */
    public function withCardContacts($cardContacts)
    {
        $new = clone $this;
        $new->cardContacts = $cardContacts;

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
     * @return AddContactsToCard
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }


}

