<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AddFolderInDrawer implements RequestInterface
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
     * @var int
     */
    private $drawerId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $folderId
     * @var int $drawerId
     */
    public function __construct($strSessionId, $folderId, $drawerId)
    {
        $this->strSessionId = $strSessionId;
        $this->folderId = $folderId;
        $this->drawerId = $drawerId;
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
     * @return AddFolderInDrawer
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
     * @return AddFolderInDrawer
     */
    public function withFolderId($folderId)
    {
        $new = clone $this;
        $new->folderId = $folderId;

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
     * @return AddFolderInDrawer
     */
    public function withDrawerId($drawerId)
    {
        $new = clone $this;
        $new->drawerId = $drawerId;

        return $new;
    }


}

