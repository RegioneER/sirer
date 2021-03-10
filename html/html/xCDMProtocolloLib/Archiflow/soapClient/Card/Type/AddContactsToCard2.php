<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AddContactsToCard2 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $sessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCard
     */
    private $agrafCards = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * @var bool
     */
    private $appendContacts = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCard $agrafCards
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var bool $appendContacts
     */
    public function __construct($sessionInfo, $agrafCards, $cardId, $appendContacts)
    {
        $this->sessionInfo = $sessionInfo;
        $this->agrafCards = $agrafCards;
        $this->cardId = $cardId;
        $this->appendContacts = $appendContacts;
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
     * @return AddContactsToCard2
     */
    public function withSessionInfo($sessionInfo)
    {
        $new = clone $this;
        $new->sessionInfo = $sessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCard
     */
    public function getAgrafCards()
    {
        return $this->agrafCards;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCard $agrafCards
     * @return AddContactsToCard2
     */
    public function withAgrafCards($agrafCards)
    {
        $new = clone $this;
        $new->agrafCards = $agrafCards;

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
     * @return AddContactsToCard2
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAppendContacts()
    {
        return $this->appendContacts;
    }

    /**
     * @param bool $appendContacts
     * @return AddContactsToCard2
     */
    public function withAppendContacts($appendContacts)
    {
        $new = clone $this;
        $new->appendContacts = $appendContacts;

        return $new;
    }


}

