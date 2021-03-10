<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MainDocumentToPDFInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $PDFA1b = null;

    /**
     * @var bool
     */
    private $SaveDocAsAttachment = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $PDFA1b
     * @var bool $SaveDocAsAttachment
     */
    public function __construct($CardId, $PDFA1b, $SaveDocAsAttachment)
    {
        $this->CardId = $CardId;
        $this->PDFA1b = $PDFA1b;
        $this->SaveDocAsAttachment = $SaveDocAsAttachment;
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
     * @return MainDocumentToPDFInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPDFA1b()
    {
        return $this->PDFA1b;
    }

    /**
     * @param bool $PDFA1b
     * @return MainDocumentToPDFInput
     */
    public function withPDFA1b($PDFA1b)
    {
        $new = clone $this;
        $new->PDFA1b = $PDFA1b;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSaveDocAsAttachment()
    {
        return $this->SaveDocAsAttachment;
    }

    /**
     * @param bool $SaveDocAsAttachment
     * @return MainDocumentToPDFInput
     */
    public function withSaveDocAsAttachment($SaveDocAsAttachment)
    {
        $new = clone $this;
        $new->SaveDocAsAttachment = $SaveDocAsAttachment;

        return $new;
    }


}

