<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class History implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \DateTime
     */
    private $Date = null;

    /**
     * @var bool
     */
    private $HasDetails = null;

    /**
     * @var string
     */
    private $IPAddress = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var \ArchiflowWSCard\Type\Operation
     */
    private $Operation = null;

    /**
     * @var string
     */
    private $RecipientDescription = null;

    /**
     * @var string
     */
    private $UserDescription = null;

    /**
     * @var int
     */
    private $VersionNumber = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \DateTime $Date
     * @var bool $HasDetails
     * @var string $IPAddress
     * @var int $Id
     * @var \ArchiflowWSCard\Type\Operation $Operation
     * @var string $RecipientDescription
     * @var string $UserDescription
     * @var int $VersionNumber
     */
    public function __construct($CardId, $Date, $HasDetails, $IPAddress, $Id, $Operation, $RecipientDescription, $UserDescription, $VersionNumber)
    {
        $this->CardId = $CardId;
        $this->Date = $Date;
        $this->HasDetails = $HasDetails;
        $this->IPAddress = $IPAddress;
        $this->Id = $Id;
        $this->Operation = $Operation;
        $this->RecipientDescription = $RecipientDescription;
        $this->UserDescription = $UserDescription;
        $this->VersionNumber = $VersionNumber;
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
     * @return History
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
     * @return History
     */
    public function withDate($Date)
    {
        $new = clone $this;
        $new->Date = $Date;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasDetails()
    {
        return $this->HasDetails;
    }

    /**
     * @param bool $HasDetails
     * @return History
     */
    public function withHasDetails($HasDetails)
    {
        $new = clone $this;
        $new->HasDetails = $HasDetails;

        return $new;
    }

    /**
     * @return string
     */
    public function getIPAddress()
    {
        return $this->IPAddress;
    }

    /**
     * @param string $IPAddress
     * @return History
     */
    public function withIPAddress($IPAddress)
    {
        $new = clone $this;
        $new->IPAddress = $IPAddress;

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
     * @return History
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Operation
     */
    public function getOperation()
    {
        return $this->Operation;
    }

    /**
     * @param \ArchiflowWSCard\Type\Operation $Operation
     * @return History
     */
    public function withOperation($Operation)
    {
        $new = clone $this;
        $new->Operation = $Operation;

        return $new;
    }

    /**
     * @return string
     */
    public function getRecipientDescription()
    {
        return $this->RecipientDescription;
    }

    /**
     * @param string $RecipientDescription
     * @return History
     */
    public function withRecipientDescription($RecipientDescription)
    {
        $new = clone $this;
        $new->RecipientDescription = $RecipientDescription;

        return $new;
    }

    /**
     * @return string
     */
    public function getUserDescription()
    {
        return $this->UserDescription;
    }

    /**
     * @param string $UserDescription
     * @return History
     */
    public function withUserDescription($UserDescription)
    {
        $new = clone $this;
        $new->UserDescription = $UserDescription;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersionNumber()
    {
        return $this->VersionNumber;
    }

    /**
     * @param int $VersionNumber
     * @return History
     */
    public function withVersionNumber($VersionNumber)
    {
        $new = clone $this;
        $new->VersionNumber = $VersionNumber;

        return $new;
    }


}

