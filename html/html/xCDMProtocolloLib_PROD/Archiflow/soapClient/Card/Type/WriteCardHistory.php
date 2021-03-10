<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class WriteCardHistory implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\HistoryOperation
     */
    private $enHistoryOperation = null;

    /**
     * @var string
     */
    private $strCustomDescription = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\HistoryOperation $enHistoryOperation
     * @var string $strCustomDescription
     */
    public function __construct($strSessionId, $oCardId, $enHistoryOperation, $strCustomDescription)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->enHistoryOperation = $enHistoryOperation;
        $this->strCustomDescription = $strCustomDescription;
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
     * @return WriteCardHistory
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
     * @return WriteCardHistory
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\HistoryOperation
     */
    public function getEnHistoryOperation()
    {
        return $this->enHistoryOperation;
    }

    /**
     * @param \ArchiflowWSCard\Type\HistoryOperation $enHistoryOperation
     * @return WriteCardHistory
     */
    public function withEnHistoryOperation($enHistoryOperation)
    {
        $new = clone $this;
        $new->enHistoryOperation = $enHistoryOperation;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrCustomDescription()
    {
        return $this->strCustomDescription;
    }

    /**
     * @param string $strCustomDescription
     * @return WriteCardHistory
     */
    public function withStrCustomDescription($strCustomDescription)
    {
        $new = clone $this;
        $new->strCustomDescription = $strCustomDescription;

        return $new;
    }


}

