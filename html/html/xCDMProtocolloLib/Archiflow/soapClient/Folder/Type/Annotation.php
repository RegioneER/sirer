<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Annotation implements RequestInterface
{

    /**
     * @var string
     */
    private $Author = null;

    /**
     * @var \ArchiflowWSFolder\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \DateTime
     */
    private $Date = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var string
     */
    private $Text = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
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
     * @var \ArchiflowWSFolder\Type\Guid $CardId
     * @var \DateTime $Date
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @var string $Text
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $Users
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
     * @return \ArchiflowWSFolder\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Guid $CardId
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
     * @return \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @return Annotation
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
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
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $Users
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

