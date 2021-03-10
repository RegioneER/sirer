<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentInfoInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $VersionNumber = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $VersionNumber
     */
    public function __construct($CardId, $VersionNumber)
    {
        $this->CardId = $CardId;
        $this->VersionNumber = $VersionNumber;
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
     * @return GetCardDocumentInfoInput
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
    public function getVersionNumber()
    {
        return $this->VersionNumber;
    }

    /**
     * @param int $VersionNumber
     * @return GetCardDocumentInfoInput
     */
    public function withVersionNumber($VersionNumber)
    {
        $new = clone $this;
        $new->VersionNumber = $VersionNumber;

        return $new;
    }


}

