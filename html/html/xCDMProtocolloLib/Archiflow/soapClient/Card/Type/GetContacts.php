<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetContacts implements RequestInterface
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
     * @var string
     */
    private $tag = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var string $tag
     */
    public function __construct($sessionInfo, $cardId, $tag)
    {
        $this->sessionInfo = $sessionInfo;
        $this->cardId = $cardId;
        $this->tag = $tag;
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
     * @return GetContacts
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
     * @return GetContacts
     */
    public function withCardId($cardId)
    {
        $new = clone $this;
        $new->cardId = $cardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getTag()
    {
        return $this->tag;
    }

    /**
     * @param string $tag
     * @return GetContacts
     */
    public function withTag($tag)
    {
        $new = clone $this;
        $new->tag = $tag;

        return $new;
    }


}

