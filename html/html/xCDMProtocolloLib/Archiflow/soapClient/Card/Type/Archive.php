<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Archive implements RequestInterface
{

    /**
     * @var string
     */
    private $AOOCode = null;

    /**
     * @var string
     */
    private $AdminCode = null;

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var string
     */
    private $ArchiveName = null;

    /**
     * @var string
     */
    private $InvalidatingMeasure = null;

    /**
     * @var bool
     */
    private $IsStorePECIn = null;

    /**
     * @var bool
     */
    private $IsStorePECOut = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfboolean
     */
    private $Options = null;

    /**
     * @var string
     */
    private $ProtocolRangeFromTime = null;

    /**
     * @var string
     */
    private $ProtocolRangeToTime = null;

    /**
     * @var string
     */
    private $ProtocolRegisterCode = null;

    /**
     * Constructor
     *
     * @var string $AOOCode
     * @var string $AdminCode
     * @var int $ArchiveId
     * @var string $ArchiveName
     * @var string $InvalidatingMeasure
     * @var bool $IsStorePECIn
     * @var bool $IsStorePECOut
     * @var \ArchiflowWSCard\Type\ArrayOfboolean $Options
     * @var string $ProtocolRangeFromTime
     * @var string $ProtocolRangeToTime
     * @var string $ProtocolRegisterCode
     */
    public function __construct($AOOCode, $AdminCode, $ArchiveId, $ArchiveName, $InvalidatingMeasure, $IsStorePECIn, $IsStorePECOut, $Options, $ProtocolRangeFromTime, $ProtocolRangeToTime, $ProtocolRegisterCode)
    {
        $this->AOOCode = $AOOCode;
        $this->AdminCode = $AdminCode;
        $this->ArchiveId = $ArchiveId;
        $this->ArchiveName = $ArchiveName;
        $this->InvalidatingMeasure = $InvalidatingMeasure;
        $this->IsStorePECIn = $IsStorePECIn;
        $this->IsStorePECOut = $IsStorePECOut;
        $this->Options = $Options;
        $this->ProtocolRangeFromTime = $ProtocolRangeFromTime;
        $this->ProtocolRangeToTime = $ProtocolRangeToTime;
        $this->ProtocolRegisterCode = $ProtocolRegisterCode;
    }

    /**
     * @return string
     */
    public function getAOOCode()
    {
        return $this->AOOCode;
    }

    /**
     * @param string $AOOCode
     * @return Archive
     */
    public function withAOOCode($AOOCode)
    {
        $new = clone $this;
        $new->AOOCode = $AOOCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getAdminCode()
    {
        return $this->AdminCode;
    }

    /**
     * @param string $AdminCode
     * @return Archive
     */
    public function withAdminCode($AdminCode)
    {
        $new = clone $this;
        $new->AdminCode = $AdminCode;

        return $new;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->ArchiveId;
    }

    /**
     * @param int $ArchiveId
     * @return Archive
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return string
     */
    public function getArchiveName()
    {
        return $this->ArchiveName;
    }

    /**
     * @param string $ArchiveName
     * @return Archive
     */
    public function withArchiveName($ArchiveName)
    {
        $new = clone $this;
        $new->ArchiveName = $ArchiveName;

        return $new;
    }

    /**
     * @return string
     */
    public function getInvalidatingMeasure()
    {
        return $this->InvalidatingMeasure;
    }

    /**
     * @param string $InvalidatingMeasure
     * @return Archive
     */
    public function withInvalidatingMeasure($InvalidatingMeasure)
    {
        $new = clone $this;
        $new->InvalidatingMeasure = $InvalidatingMeasure;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsStorePECIn()
    {
        return $this->IsStorePECIn;
    }

    /**
     * @param bool $IsStorePECIn
     * @return Archive
     */
    public function withIsStorePECIn($IsStorePECIn)
    {
        $new = clone $this;
        $new->IsStorePECIn = $IsStorePECIn;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsStorePECOut()
    {
        return $this->IsStorePECOut;
    }

    /**
     * @param bool $IsStorePECOut
     * @return Archive
     */
    public function withIsStorePECOut($IsStorePECOut)
    {
        $new = clone $this;
        $new->IsStorePECOut = $IsStorePECOut;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfboolean
     */
    public function getOptions()
    {
        return $this->Options;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfboolean $Options
     * @return Archive
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
    public function getProtocolRangeFromTime()
    {
        return $this->ProtocolRangeFromTime;
    }

    /**
     * @param string $ProtocolRangeFromTime
     * @return Archive
     */
    public function withProtocolRangeFromTime($ProtocolRangeFromTime)
    {
        $new = clone $this;
        $new->ProtocolRangeFromTime = $ProtocolRangeFromTime;

        return $new;
    }

    /**
     * @return string
     */
    public function getProtocolRangeToTime()
    {
        return $this->ProtocolRangeToTime;
    }

    /**
     * @param string $ProtocolRangeToTime
     * @return Archive
     */
    public function withProtocolRangeToTime($ProtocolRangeToTime)
    {
        $new = clone $this;
        $new->ProtocolRangeToTime = $ProtocolRangeToTime;

        return $new;
    }

    /**
     * @return string
     */
    public function getProtocolRegisterCode()
    {
        return $this->ProtocolRegisterCode;
    }

    /**
     * @param string $ProtocolRegisterCode
     * @return Archive
     */
    public function withProtocolRegisterCode($ProtocolRegisterCode)
    {
        $new = clone $this;
        $new->ProtocolRegisterCode = $ProtocolRegisterCode;

        return $new;
    }


}

