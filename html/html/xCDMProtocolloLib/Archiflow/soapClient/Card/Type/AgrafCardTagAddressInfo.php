<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCardTagAddressInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContactAddressInfo
     */
    private $CardContacts = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $GuidCard = null;

    /**
     * @var string
     */
    private $TagId = null;

    /**
     * @var string
     */
    private $TagName = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContactAddressInfo $CardContacts
     * @var \ArchiflowWSCard\Type\Guid $GuidCard
     * @var string $TagId
     * @var string $TagName
     */
    public function __construct($CardContacts, $GuidCard, $TagId, $TagName)
    {
        $this->CardContacts = $CardContacts;
        $this->GuidCard = $GuidCard;
        $this->TagId = $TagId;
        $this->TagName = $TagName;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardContactAddressInfo
     */
    public function getCardContacts()
    {
        return $this->CardContacts;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardContactAddressInfo $CardContacts
     * @return AgrafCardTagAddressInfo
     */
    public function withCardContacts($CardContacts)
    {
        $new = clone $this;
        $new->CardContacts = $CardContacts;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getGuidCard()
    {
        return $this->GuidCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $GuidCard
     * @return AgrafCardTagAddressInfo
     */
    public function withGuidCard($GuidCard)
    {
        $new = clone $this;
        $new->GuidCard = $GuidCard;

        return $new;
    }

    /**
     * @return string
     */
    public function getTagId()
    {
        return $this->TagId;
    }

    /**
     * @param string $TagId
     * @return AgrafCardTagAddressInfo
     */
    public function withTagId($TagId)
    {
        $new = clone $this;
        $new->TagId = $TagId;

        return $new;
    }

    /**
     * @return string
     */
    public function getTagName()
    {
        return $this->TagName;
    }

    /**
     * @param string $TagName
     * @return AgrafCardTagAddressInfo
     */
    public function withTagName($TagName)
    {
        $new = clone $this;
        $new->TagName = $TagName;

        return $new;
    }


}

