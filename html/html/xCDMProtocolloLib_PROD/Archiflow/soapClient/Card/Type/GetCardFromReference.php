<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardFromReference implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

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
     * @var string $strSessionId
     * @var int $archiveId
     * @var string $fieldRefValue
     */
    public function __construct($strSessionId, $archiveId, $fieldRefValue)
    {
        $this->strSessionId = $strSessionId;
        $this->archiveId = $archiveId;
        $this->fieldRefValue = $fieldRefValue;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetCardFromReference
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetCardFromReference
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
     * @return GetCardFromReference
     */
    public function withFieldRefValue($fieldRefValue)
    {
        $new = clone $this;
        $new->fieldRefValue = $fieldRefValue;

        return $new;
    }


}

