<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Record implements RequestInterface
{

    /**
     * @var bool
     */
    private $DontShow = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfRegistryField
     */
    private $Fields = null;

    /**
     * @var int
     */
    private $RecordId = null;

    /**
     * @var int
     */
    private $RegistryId = null;

    /**
     * Constructor
     *
     * @var bool $DontShow
     * @var \ArchiflowWSCard\Type\ArrayOfRegistryField $Fields
     * @var int $RecordId
     * @var int $RegistryId
     */
    public function __construct($DontShow, $Fields, $RecordId, $RegistryId)
    {
        $this->DontShow = $DontShow;
        $this->Fields = $Fields;
        $this->RecordId = $RecordId;
        $this->RegistryId = $RegistryId;
    }

    /**
     * @return bool
     */
    public function getDontShow()
    {
        return $this->DontShow;
    }

    /**
     * @param bool $DontShow
     * @return Record
     */
    public function withDontShow($DontShow)
    {
        $new = clone $this;
        $new->DontShow = $DontShow;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfRegistryField
     */
    public function getFields()
    {
        return $this->Fields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfRegistryField $Fields
     * @return Record
     */
    public function withFields($Fields)
    {
        $new = clone $this;
        $new->Fields = $Fields;

        return $new;
    }

    /**
     * @return int
     */
    public function getRecordId()
    {
        return $this->RecordId;
    }

    /**
     * @param int $RecordId
     * @return Record
     */
    public function withRecordId($RecordId)
    {
        $new = clone $this;
        $new->RecordId = $RecordId;

        return $new;
    }

    /**
     * @return int
     */
    public function getRegistryId()
    {
        return $this->RegistryId;
    }

    /**
     * @param int $RegistryId
     * @return Record
     */
    public function withRegistryId($RegistryId)
    {
        $new = clone $this;
        $new->RegistryId = $RegistryId;

        return $new;
    }


}

