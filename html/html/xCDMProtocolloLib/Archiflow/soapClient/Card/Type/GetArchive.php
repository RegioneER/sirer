<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetArchive implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $nArchiveId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nArchiveId
     */
    public function __construct($strSessionId, $nArchiveId)
    {
        $this->strSessionId = $strSessionId;
        $this->nArchiveId = $nArchiveId;
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
     * @return GetArchive
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
    public function getNArchiveId()
    {
        return $this->nArchiveId;
    }

    /**
     * @param int $nArchiveId
     * @return GetArchive
     */
    public function withNArchiveId($nArchiveId)
    {
        $new = clone $this;
        $new->nArchiveId = $nArchiveId;

        return $new;
    }


}

