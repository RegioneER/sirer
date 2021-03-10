<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfArchiveTypedocCardId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArchiveTypedocCardId
     */
    private $ArchiveTypedocCardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArchiveTypedocCardId $ArchiveTypedocCardId
     */
    public function __construct($ArchiveTypedocCardId)
    {
        $this->ArchiveTypedocCardId = $ArchiveTypedocCardId;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArchiveTypedocCardId
     */
    public function getArchiveTypedocCardId()
    {
        return $this->ArchiveTypedocCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArchiveTypedocCardId $ArchiveTypedocCardId
     * @return ArrayOfArchiveTypedocCardId
     */
    public function withArchiveTypedocCardId($ArchiveTypedocCardId)
    {
        $new = clone $this;
        $new->ArchiveTypedocCardId = $ArchiveTypedocCardId;

        return $new;
    }


}

