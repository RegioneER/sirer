<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardFromReference2 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var int
     */
    private $archiveId = null;

    /**
     * @var string
     */
    private $fieldRefValue = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var int $archiveId
     * @var string $fieldRefValue
     */
    public function __construct($oSessionInfo, $archiveId, $fieldRefValue)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->archiveId = $archiveId;
        $this->fieldRefValue = $fieldRefValue;
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
     * @return GetCardFromReference2
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->archiveId;
    }

    /**
     * @param int $archiveId
     * @return GetCardFromReference2
     */
    public function withArchiveId($archiveId)
    {
        $new = clone $this;
        $new->archiveId = $archiveId;

        return $new;
    }

    /**
     * @return string
     */
    public function getFieldRefValue()
    {
        return $this->fieldRefValue;
    }

    /**
     * @param string $fieldRefValue
     * @return GetCardFromReference2
     */
    public function withFieldRefValue($fieldRefValue)
    {
        $new = clone $this;
        $new->fieldRefValue = $fieldRefValue;

        return $new;
    }


}

