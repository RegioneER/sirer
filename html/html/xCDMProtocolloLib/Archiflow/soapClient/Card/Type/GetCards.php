<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCards implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @var bool
     */
    private $bGetIndexes = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @var bool $bGetIndexes
     */
    public function __construct($strSessionId, $oCardIds, $bGetIndexes)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardIds = $oCardIds;
        $this->bGetIndexes = $bGetIndexes;
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
     * @return GetCards
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetCards
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
    public function getBGetIndexes()
    {
        return $this->bGetIndexes;
    }

    /**
     * @param bool $bGetIndexes
     * @return GetCards
     */
    public function withBGetIndexes($bGetIndexes)
    {
        $new = clone $this;
        $new->bGetIndexes = $bGetIndexes;

        return $new;
    }


}

