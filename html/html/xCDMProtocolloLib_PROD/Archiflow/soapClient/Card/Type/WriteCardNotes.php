<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class WriteCardNotes implements RequestInterface
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
     * @var int
     */
    private $authorId = null;

    /**
     * @var bool
     */
    private $writeHistory = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAnnotation
     */
    private $aAnnotations = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var int $authorId
     * @var bool $writeHistory
     * @var \ArchiflowWSCard\Type\ArrayOfAnnotation $aAnnotations
     */
    public function __construct($strSessionId, $oCardId, $authorId, $writeHistory, $aAnnotations)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->authorId = $authorId;
        $this->writeHistory = $writeHistory;
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
     * @return WriteCardNotes
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
     * @return WriteCardNotes
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getAuthorId()
    {
        return $this->authorId;
    }

    /**
     * @param int $authorId
     * @return WriteCardNotes
     */
    public function withAuthorId($authorId)
    {
        $new = clone $this;
        $new->authorId = $authorId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWriteHistory()
    {
        return $this->writeHistory;
    }

    /**
     * @param bool $writeHistory
     * @return WriteCardNotes
     */
    public function withWriteHistory($writeHistory)
    {
        $new = clone $this;
        $new->writeHistory = $writeHistory;

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
     * @return WriteCardNotes
     */
    public function withAAnnotations($aAnnotations)
    {
        $new = clone $this;
        $new->aAnnotations = $aAnnotations;

        return $new;
    }


}

