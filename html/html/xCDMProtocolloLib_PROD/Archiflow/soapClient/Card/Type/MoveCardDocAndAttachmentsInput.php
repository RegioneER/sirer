<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MoveCardDocAndAttachmentsInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $IdAttachmentsVol = null;

    /**
     * @var int
     */
    private $IdDocumentVol = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $IdAttachmentsVol
     * @var int $IdDocumentVol
     */
    public function __construct($CardId, $IdAttachmentsVol, $IdDocumentVol)
    {
        $this->CardId = $CardId;
        $this->IdAttachmentsVol = $IdAttachmentsVol;
        $this->IdDocumentVol = $IdDocumentVol;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return MoveCardDocAndAttachmentsInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdAttachmentsVol()
    {
        return $this->IdAttachmentsVol;
    }

    /**
     * @param int $IdAttachmentsVol
     * @return MoveCardDocAndAttachmentsInput
     */
    public function withIdAttachmentsVol($IdAttachmentsVol)
    {
        $new = clone $this;
        $new->IdAttachmentsVol = $IdAttachmentsVol;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdDocumentVol()
    {
        return $this->IdDocumentVol;
    }

    /**
     * @param int $IdDocumentVol
     * @return MoveCardDocAndAttachmentsInput
     */
    public function withIdDocumentVol($IdDocumentVol)
    {
        $new = clone $this;
        $new->IdDocumentVol = $IdDocumentVol;

        return $new;
    }


}

