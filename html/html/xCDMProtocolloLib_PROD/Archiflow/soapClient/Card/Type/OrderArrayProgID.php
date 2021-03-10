<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class OrderArrayProgID implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\FieldToOrderBy
     */
    private $eFieldToOrderBy = null;

    /**
     * @var bool
     */
    private $bSortDescending = null;

    /**
     * @var \ArchiflowWSCard\Type\ProgIdType
     */
    private $eProgIdType = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @var bool
     */
    private $bSharedMail = null;

    /**
     * @var int
     */
    private $iOfficeId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\FieldToOrderBy $eFieldToOrderBy
     * @var bool $bSortDescending
     * @var \ArchiflowWSCard\Type\ProgIdType $eProgIdType
     * @var \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @var bool $bSharedMail
     * @var int $iOfficeId
     */
    public function __construct($oSessionInfo, $eFieldToOrderBy, $bSortDescending, $eProgIdType, $oCardIds, $bSharedMail, $iOfficeId)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->eFieldToOrderBy = $eFieldToOrderBy;
        $this->bSortDescending = $bSortDescending;
        $this->eProgIdType = $eProgIdType;
        $this->oCardIds = $oCardIds;
        $this->bSharedMail = $bSharedMail;
        $this->iOfficeId = $iOfficeId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @return OrderArrayProgID
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\FieldToOrderBy
     */
    public function getEFieldToOrderBy()
    {
        return $this->eFieldToOrderBy;
    }

    /**
     * @param \ArchiflowWSCard\Type\FieldToOrderBy $eFieldToOrderBy
     * @return OrderArrayProgID
     */
    public function withEFieldToOrderBy($eFieldToOrderBy)
    {
        $new = clone $this;
        $new->eFieldToOrderBy = $eFieldToOrderBy;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSortDescending()
    {
        return $this->bSortDescending;
    }

    /**
     * @param bool $bSortDescending
     * @return OrderArrayProgID
     */
    public function withBSortDescending($bSortDescending)
    {
        $new = clone $this;
        $new->bSortDescending = $bSortDescending;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ProgIdType
     */
    public function getEProgIdType()
    {
        return $this->eProgIdType;
    }

    /**
     * @param \ArchiflowWSCard\Type\ProgIdType $eProgIdType
     * @return OrderArrayProgID
     */
    public function withEProgIdType($eProgIdType)
    {
        $new = clone $this;
        $new->eProgIdType = $eProgIdType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOCardIds()
    {
        return $this->oCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @return OrderArrayProgID
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSharedMail()
    {
        return $this->bSharedMail;
    }

    /**
     * @param bool $bSharedMail
     * @return OrderArrayProgID
     */
    public function withBSharedMail($bSharedMail)
    {
        $new = clone $this;
        $new->bSharedMail = $bSharedMail;

        return $new;
    }

    /**
     * @return int
     */
    public function getIOfficeId()
    {
        return $this->iOfficeId;
    }

    /**
     * @param int $iOfficeId
     * @return OrderArrayProgID
     */
    public function withIOfficeId($iOfficeId)
    {
        $new = clone $this;
        $new->iOfficeId = $iOfficeId;

        return $new;
    }


}

