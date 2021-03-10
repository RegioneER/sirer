<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AttachPressMarkInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var string
     */
    private $ContentType = null;

    /**
     * @var bool
     */
    private $NotWritePressmarkHistory = null;

    /**
     * @var \ArchiflowWSCard\Type\Base64Binary
     */
    private $PressMarkContent = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var string $ContentType
     * @var bool $NotWritePressmarkHistory
     * @var \ArchiflowWSCard\Type\Base64Binary $PressMarkContent
     */
    public function __construct($CardId, $ContentType, $NotWritePressmarkHistory, $PressMarkContent)
    {
        $this->CardId = $CardId;
        $this->ContentType = $ContentType;
        $this->NotWritePressmarkHistory = $NotWritePressmarkHistory;
        $this->PressMarkContent = $PressMarkContent;
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
     * @return AttachPressMarkInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return $this->ContentType;
    }

    /**
     * @param string $ContentType
     * @return AttachPressMarkInput
     */
    public function withContentType($ContentType)
    {
        $new = clone $this;
        $new->ContentType = $ContentType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getNotWritePressmarkHistory()
    {
        return $this->NotWritePressmarkHistory;
    }

    /**
     * @param bool $NotWritePressmarkHistory
     * @return AttachPressMarkInput
     */
    public function withNotWritePressmarkHistory($NotWritePressmarkHistory)
    {
        $new = clone $this;
        $new->NotWritePressmarkHistory = $NotWritePressmarkHistory;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Base64Binary
     */
    public function getPressMarkContent()
    {
        return $this->PressMarkContent;
    }

    /**
     * @param \ArchiflowWSCard\Type\Base64Binary $PressMarkContent
     * @return AttachPressMarkInput
     */
    public function withPressMarkContent($PressMarkContent)
    {
        $new = clone $this;
        $new->PressMarkContent = $PressMarkContent;

        return $new;
    }


}

