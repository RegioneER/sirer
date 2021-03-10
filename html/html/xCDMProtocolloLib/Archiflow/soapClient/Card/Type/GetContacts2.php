<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetContacts2 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $sessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $tagId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var \ArchiflowWSCard\Type\Guid $tagId
     */
    public function __construct($sessionInfo, $cardId, $tagId)
    {
        $this->sessionInfo = $sessionInfo;
        $this->cardId = $cardId;
        $this->tagId = $tagId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getSessionInfo()
    {
        return $this->sessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @return GetContacts2
     */
    public function withSessionInfo($sessionInfo)
    {
        $new = clone $this;
        $new->sessionInfo = $sessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->cardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $cardId
     * @return GetContacts2
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getTagId()
    {
        return $this->tagId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $tagId
     * @return GetContacts2
     */
    public function withTagId($tagId)
    {
        $new = clone $this;
        $new->tagId = $tagId;

        return $new;
    }


}

