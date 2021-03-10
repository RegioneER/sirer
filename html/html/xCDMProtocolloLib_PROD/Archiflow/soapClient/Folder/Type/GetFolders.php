<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetFolders implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $drawerId = null;

    /**
     * @var bool
     */
    private $bGetVisibility = null;

    /**
     * @var bool
     */
    private $bGetCardIds = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $drawerId
     * @var bool $bGetVisibility
     * @var bool $bGetCardIds
     */
    public function __construct($strSessionId, $drawerId, $bGetVisibility, $bGetCardIds)
    {
        $this->strSessionId = $strSessionId;
        $this->drawerId = $drawerId;
        $this->bGetVisibility = $bGetVisibility;
        $this->bGetCardIds = $bGetCardIds;
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
     * @return GetFolders
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
    public function getDrawerId()
    {
        return $this->drawerId;
    }

    /**
     * @param int $drawerId
     * @return GetFolders
     */
    public function withDrawerId($drawerId)
    {
        $new = clone $this;
        $new->drawerId = $drawerId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetVisibility()
    {
        return $this->bGetVisibility;
    }

    /**
     * @param bool $bGetVisibility
     * @return GetFolders
     */
    public function withBGetVisibility($bGetVisibility)
    {
        $new = clone $this;
        $new->bGetVisibility = $bGetVisibility;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetCardIds()
    {
        return $this->bGetCardIds;
    }

    /**
     * @param bool $bGetCardIds
     * @return GetFolders
     */
    public function withBGetCardIds($bGetCardIds)
    {
        $new = clone $this;
        $new->bGetCardIds = $bGetCardIds;

        return $new;
    }


}

