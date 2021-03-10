<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardHasData implements RequestInterface
{

    /**
     * @var bool
     */
    private $HasAdditionalData = null;

    /**
     * @var bool
     */
    private $HasAgraf = null;

    /**
     * @var bool
     */
    private $HasAttachment = null;

    /**
     * @var bool
     */
    private $HasComputerizedClassification = null;

    /**
     * @var bool
     */
    private $HasComputerizedFolder = null;

    /**
     * @var bool
     */
    private $HasDocument = null;

    /**
     * @var bool
     */
    private $HasEeEmail = null;

    /**
     * @var bool
     */
    private $HasFolder = null;

    /**
     * @var bool
     */
    private $HasIMInvoice = null;

    /**
     * @var bool
     */
    private $HasInternalAttachment = null;

    /**
     * @var bool
     */
    private $HasNotes = null;

    /**
     * @var bool
     */
    private $HasPartialInvalidations = null;

    /**
     * @var bool
     */
    private $HasPosteOnline = null;

    /**
     * @var bool
     */
    private $HasTasksAssignedTo = null;

    /**
     * @var bool
     */
    private $HasTasksToDo = null;

    /**
     * @var bool
     */
    private $IsWf = null;

    /**
     * Constructor
     *
     * @var bool $HasAdditionalData
     * @var bool $HasAgraf
     * @var bool $HasAttachment
     * @var bool $HasComputerizedClassification
     * @var bool $HasComputerizedFolder
     * @var bool $HasDocument
     * @var bool $HasEeEmail
     * @var bool $HasFolder
     * @var bool $HasIMInvoice
     * @var bool $HasInternalAttachment
     * @var bool $HasNotes
     * @var bool $HasPartialInvalidations
     * @var bool $HasPosteOnline
     * @var bool $HasTasksAssignedTo
     * @var bool $HasTasksToDo
     * @var bool $IsWf
     */
    public function __construct($HasAdditionalData, $HasAgraf, $HasAttachment, $HasComputerizedClassification, $HasComputerizedFolder, $HasDocument, $HasEeEmail, $HasFolder, $HasIMInvoice, $HasInternalAttachment, $HasNotes, $HasPartialInvalidations, $HasPosteOnline, $HasTasksAssignedTo, $HasTasksToDo, $IsWf)
    {
        $this->HasAdditionalData = $HasAdditionalData;
        $this->HasAgraf = $HasAgraf;
        $this->HasAttachment = $HasAttachment;
        $this->HasComputerizedClassification = $HasComputerizedClassification;
        $this->HasComputerizedFolder = $HasComputerizedFolder;
        $this->HasDocument = $HasDocument;
        $this->HasEeEmail = $HasEeEmail;
        $this->HasFolder = $HasFolder;
        $this->HasIMInvoice = $HasIMInvoice;
        $this->HasInternalAttachment = $HasInternalAttachment;
        $this->HasNotes = $HasNotes;
        $this->HasPartialInvalidations = $HasPartialInvalidations;
        $this->HasPosteOnline = $HasPosteOnline;
        $this->HasTasksAssignedTo = $HasTasksAssignedTo;
        $this->HasTasksToDo = $HasTasksToDo;
        $this->IsWf = $IsWf;
    }

    /**
     * @return bool
     */
    public function getHasAdditionalData()
    {
        return $this->HasAdditionalData;
    }

    /**
     * @param bool $HasAdditionalData
     * @return CardHasData
     */
    public function withHasAdditionalData($HasAdditionalData)
    {
        $new = clone $this;
        $new->HasAdditionalData = $HasAdditionalData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasAgraf()
    {
        return $this->HasAgraf;
    }

    /**
     * @param bool $HasAgraf
     * @return CardHasData
     */
    public function withHasAgraf($HasAgraf)
    {
        $new = clone $this;
        $new->HasAgraf = $HasAgraf;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasAttachment()
    {
        return $this->HasAttachment;
    }

    /**
     * @param bool $HasAttachment
     * @return CardHasData
     */
    public function withHasAttachment($HasAttachment)
    {
        $new = clone $this;
        $new->HasAttachment = $HasAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasComputerizedClassification()
    {
        return $this->HasComputerizedClassification;
    }

    /**
     * @param bool $HasComputerizedClassification
     * @return CardHasData
     */
    public function withHasComputerizedClassification($HasComputerizedClassification)
    {
        $new = clone $this;
        $new->HasComputerizedClassification = $HasComputerizedClassification;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasComputerizedFolder()
    {
        return $this->HasComputerizedFolder;
    }

    /**
     * @param bool $HasComputerizedFolder
     * @return CardHasData
     */
    public function withHasComputerizedFolder($HasComputerizedFolder)
    {
        $new = clone $this;
        $new->HasComputerizedFolder = $HasComputerizedFolder;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasDocument()
    {
        return $this->HasDocument;
    }

    /**
     * @param bool $HasDocument
     * @return CardHasData
     */
    public function withHasDocument($HasDocument)
    {
        $new = clone $this;
        $new->HasDocument = $HasDocument;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasEeEmail()
    {
        return $this->HasEeEmail;
    }

    /**
     * @param bool $HasEeEmail
     * @return CardHasData
     */
    public function withHasEeEmail($HasEeEmail)
    {
        $new = clone $this;
        $new->HasEeEmail = $HasEeEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasFolder()
    {
        return $this->HasFolder;
    }

    /**
     * @param bool $HasFolder
     * @return CardHasData
     */
    public function withHasFolder($HasFolder)
    {
        $new = clone $this;
        $new->HasFolder = $HasFolder;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasIMInvoice()
    {
        return $this->HasIMInvoice;
    }

    /**
     * @param bool $HasIMInvoice
     * @return CardHasData
     */
    public function withHasIMInvoice($HasIMInvoice)
    {
        $new = clone $this;
        $new->HasIMInvoice = $HasIMInvoice;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasInternalAttachment()
    {
        return $this->HasInternalAttachment;
    }

    /**
     * @param bool $HasInternalAttachment
     * @return CardHasData
     */
    public function withHasInternalAttachment($HasInternalAttachment)
    {
        $new = clone $this;
        $new->HasInternalAttachment = $HasInternalAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasNotes()
    {
        return $this->HasNotes;
    }

    /**
     * @param bool $HasNotes
     * @return CardHasData
     */
    public function withHasNotes($HasNotes)
    {
        $new = clone $this;
        $new->HasNotes = $HasNotes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasPartialInvalidations()
    {
        return $this->HasPartialInvalidations;
    }

    /**
     * @param bool $HasPartialInvalidations
     * @return CardHasData
     */
    public function withHasPartialInvalidations($HasPartialInvalidations)
    {
        $new = clone $this;
        $new->HasPartialInvalidations = $HasPartialInvalidations;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasPosteOnline()
    {
        return $this->HasPosteOnline;
    }

    /**
     * @param bool $HasPosteOnline
     * @return CardHasData
     */
    public function withHasPosteOnline($HasPosteOnline)
    {
        $new = clone $this;
        $new->HasPosteOnline = $HasPosteOnline;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasTasksAssignedTo()
    {
        return $this->HasTasksAssignedTo;
    }

    /**
     * @param bool $HasTasksAssignedTo
     * @return CardHasData
     */
    public function withHasTasksAssignedTo($HasTasksAssignedTo)
    {
        $new = clone $this;
        $new->HasTasksAssignedTo = $HasTasksAssignedTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasTasksToDo()
    {
        return $this->HasTasksToDo;
    }

    /**
     * @param bool $HasTasksToDo
     * @return CardHasData
     */
    public function withHasTasksToDo($HasTasksToDo)
    {
        $new = clone $this;
        $new->HasTasksToDo = $HasTasksToDo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsWf()
    {
        return $this->IsWf;
    }

    /**
     * @param bool $IsWf
     * @return CardHasData
     */
    public function withIsWf($IsWf)
    {
        $new = clone $this;
        $new->IsWf = $IsWf;

        return $new;
    }


}

