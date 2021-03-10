<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteFolder implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var int $folderId
     */
    public function __construct($strSessionId, $folderId)
    {
        $this->strSessionId = $strSessionId;
        $this->folderId = $folderId;
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
     * @return DeleteFolder
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
     * @return DeleteFolder
     */
    public function withFolderId($folderId)
    {
        $new = clone $this;
        $new->folderId = $folderId;

        return $new;
    }


}

