<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCard implements RequestInterface
{

    /**
     * @var string
     */
    private $AgrafNote = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    private $CardContacts = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $GuidCard = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var int
     */
    private $Options = null;

    /**
     * @var string
     */
    private $Tag = null;

    /**
     * Constructor
     *
     * @var string $AgrafNote
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContact $CardContacts
     * @var \ArchiflowWSCard\Type\Guid $GuidCard
     * @var int $Id
     * @var int $Options
     * @var string $Tag
     */
    public function __construct($AgrafNote, $CardContacts, $GuidCard, $Id, $Options, $Tag)
    {
        $this->AgrafNote = $AgrafNote;
        $this->CardContacts = $CardContacts;
        $this->GuidCard = $GuidCard;
        $this->Id = $Id;
        $this->Options = $Options;
        $this->Tag = $Tag;
    }

    /**
     * @return string
     */
    public function getAgrafNote()
    {
        return $this->AgrafNote;
    }

    /**
     * @param string $AgrafNote
     * @return AgrafCard
     */
    public function withAgrafNote($AgrafNote)
    {
        $new = clone $this;
        $new->AgrafNote = $AgrafNote;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    public function getCardContacts()
    {
        return $this->CardContacts;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardContact $CardContacts
     * @return AgrafCard
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
     * @return AgrafCard
     */
    public function withGuidCard($GuidCard)
    {
        $new = clone $this;
        $new->GuidCard = $GuidCard;

        return $new;
    }

    /**
     * @return int
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return AgrafCard
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return int
     */
    public function getOptions()
    {
        return $this->Options;
    }

    /**
     * @param int $Options
     * @return AgrafCard
     */
    public function withOptions($Options)
    {
        $new = clone $this;
        $new->Options = $Options;

        return $new;
    }

    /**
     * @return string
     */
    public function getTag()
    {
        return $this->Tag;
    }

    /**
     * @param string $Tag
     * @return AgrafCard
     */
    public function withTag($Tag)
    {
        $new = clone $this;
        $new->Tag = $Tag;

        return $new;
    }


}

