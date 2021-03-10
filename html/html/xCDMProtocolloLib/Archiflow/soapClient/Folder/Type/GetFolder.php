<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetFolder implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $folderId = null;

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
     * @var int $folderId
     * @var bool $bGetVisibility
     * @var bool $bGetCardIds
     */
    public function __construct($strSessionId, $folderId, $bGetVisibility, $bGetCardIds)
    {
        $this->strSessionId = $strSessionId;
        $this->folderId = $folderId;
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
     * @return GetFolder
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
    public function getFolderId()
    {
        return $this->folderId;
    }

    /**
     * @param int $folderId
     * @return GetFolder
     */
    public function withFolderId($folderId)
    {
        $new = clone $this;
        $new->folderId = $folderId;

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
     * @return GetFolder
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
     * @return GetFolder
     */
    public function withBGetCardIds($bGetCardIds)
    {
        $new = clone $this;
        $new->bGetCardIds = $bGetCardIds;

        return $new;
    }


}

