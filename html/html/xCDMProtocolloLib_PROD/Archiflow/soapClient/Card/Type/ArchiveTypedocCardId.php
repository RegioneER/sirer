<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArchiveTypedocCardId implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $GuidCard = null;

    /**
     * @var int
     */
    private $TypeDocId = null;

    /**
     * Constructor
     *
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\Guid $GuidCard
     * @var int $TypeDocId
     */
    public function __construct($ArchiveId, $GuidCard, $TypeDocId)
    {
        $this->ArchiveId = $ArchiveId;
        $this->GuidCard = $GuidCard;
        $this->TypeDocId = $TypeDocId;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->ArchiveId;
    }

    /**
     * @param int $ArchiveId
     * @return ArchiveTypedocCardId
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getGuidCard()
    {
        return $this->GuidCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $GuidCard
     * @return ArchiveTypedocCardId
     */
    public function withGuidCard($GuidCard)
    {
        $new = clone $this;
        $new->GuidCard = $GuidCard;

        return $new;
    }

    /**
     * @return int
     */
    public function getTypeDocId()
    {
        return $this->TypeDocId;
    }

    /**
     * @param int $TypeDocId
     * @return ArchiveTypedocCardId
     */
    public function withTypeDocId($TypeDocId)
    {
        $new = clone $this;
        $new->TypeDocId = $TypeDocId;

        return $new;
    }


}

