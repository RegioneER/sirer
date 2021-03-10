<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardFoldersInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $GetCardIds = null;

    /**
     * @var bool
     */
    private $GetVisibility = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $GetCardIds
     * @var bool $GetVisibility
     */
    public function __construct($CardId, $GetCardIds, $GetVisibility)
    {
        $this->CardId = $CardId;
        $this->GetCardIds = $GetCardIds;
        $this->GetVisibility = $GetVisibility;
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
     * @return GetCardFoldersInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetCardIds()
    {
        return $this->GetCardIds;
    }

    /**
     * @param bool $GetCardIds
     * @return GetCardFoldersInput
     */
    public function withGetCardIds($GetCardIds)
    {
        $new = clone $this;
        $new->GetCardIds = $GetCardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetVisibility()
    {
        return $this->GetVisibility;
    }

    /**
     * @param bool $GetVisibility
     * @return GetCardFoldersInput
     */
    public function withGetVisibility($GetVisibility)
    {
        $new = clone $this;
        $new->GetVisibility = $GetVisibility;

        return $new;
    }


}

