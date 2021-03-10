<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Annotation implements RequestInterface
{

    /**
     * @var string
     */
    private $Author = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \DateTime
     */
    private $Date = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var string
     */
    private $Text = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * @var bool
     */
    private $VisAll = null;

    /**
     * Constructor
     *
     * @var string $Author
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \DateTime $Date
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var string $Text
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var bool $VisAll
     */
    public function __construct($Author, $CardId, $Date, $Groups, $Offices, $Text, $Users, $VisAll)
    {
        $this->Author = $Author;
        $this->CardId = $CardId;
        $this->Date = $Date;
        $this->Groups = $Groups;
        $this->Offices = $Offices;
        $this->Text = $Text;
        $this->Users = $Users;
        $this->VisAll = $VisAll;
    }

    /**
     * @return string
     */
    public function getAuthor()
    {
        return $this->Author;
    }

    /**
     * @param string $Author
     * @return Annotation
     */
    public function withAuthor($Author)
    {
        $new = clone $this;
        $new->Author = $Author;

        return $new;
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
     * @return Annotation
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDate()
    {
        return $this->Date;
    }

    /**
     * @param \DateTime $Date
     * @return Annotation
     */
    public function withDate($Date)
    {
        $new = clone $this;
        $new->Date = $Date;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @return Annotation
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @return Annotation
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return string
     */
    public function getText()
    {
        return $this->Text;
    }

    /**
     * @param string $Text
     * @return Annotation
     */
    public function withText($Text)
    {
        $new = clone $this;
        $new->Text = $Text;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @return Annotation
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVisAll()
    {
        return $this->VisAll;
    }

    /**
     * @param bool $VisAll
     * @return Annotation
     */
    public function withVisAll($VisAll)
    {
        $new = clone $this;
        $new->VisAll = $VisAll;

        return $new;
    }


}

