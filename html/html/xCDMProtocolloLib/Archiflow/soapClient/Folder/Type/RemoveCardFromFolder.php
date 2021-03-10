<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RemoveCardFromFolder implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSFolder\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var int
     */
    private $folderId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSFolder\Type\Guid $oCardId
     * @var int $folderId
     */
    public function __construct($strSessionId, $oCardId, $folderId)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
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
     * @return RemoveCardFromFolder
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Guid $oCardId
     * @return RemoveCardFromFolder
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
    public function getFolderId()
    {
        return $this->folderId;
    }

    /**
     * @param int $folderId
     * @return RemoveCardFromFolder
     */
    public function withFolderId($folderId)
    {
        $new = clone $this;
        $new->folderId = $folderId;

        return $new;
    }


}

