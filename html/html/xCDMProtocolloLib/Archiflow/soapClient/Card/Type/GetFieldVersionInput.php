<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetFieldVersionInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $VersionId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $VersionId
     */
    public function __construct($CardId, $VersionId)
    {
        $this->CardId = $CardId;
        $this->VersionId = $VersionId;
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
     * @return GetFieldVersionInput
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
    public function getVersionId()
    {
        return $this->VersionId;
    }

    /**
     * @param int $VersionId
     * @return GetFieldVersionInput
     */
    public function withVersionId($VersionId)
    {
        $new = clone $this;
        $new->VersionId = $VersionId;

        return $new;
    }


}

