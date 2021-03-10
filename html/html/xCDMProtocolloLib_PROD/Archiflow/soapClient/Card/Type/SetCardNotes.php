<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardNotes implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAnnotation
     */
    private $aAnnotations = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\ArrayOfAnnotation $aAnnotations
     */
    public function __construct($strSessionId, $oCardId, $aAnnotations)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->aAnnotations = $aAnnotations;
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
     * @return SetCardNotes
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return SetCardNotes
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAnnotation
     */
    public function getAAnnotations()
    {
        return $this->aAnnotations;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAnnotation $aAnnotations
     * @return SetCardNotes
     */
    public function withAAnnotations($aAnnotations)
    {
        $new = clone $this;
        $new->aAnnotations = $aAnnotations;

        return $new;
    }


}

