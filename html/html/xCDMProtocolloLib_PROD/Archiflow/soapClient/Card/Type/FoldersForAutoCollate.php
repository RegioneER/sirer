<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class FoldersForAutoCollate implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $cardId = null;

    /**
     * @var string
     */
    private $autoCollationTemplateName = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var string $autoCollationTemplateName
     */
    public function __construct($sessionId, $cardId, $autoCollationTemplateName)
    {
        $this->sessionId = $sessionId;
        $this->cardId = $cardId;
        $this->autoCollationTemplateName = $autoCollationTemplateName;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->sessionId;
    }

    /**
     * @param string $sessionId
     * @return FoldersForAutoCollate
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

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
     * @return FoldersForAutoCollate
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
    public function getAutoCollationTemplateName()
    {
        return $this->autoCollationTemplateName;
    }

    /**
     * @param string $autoCollationTemplateName
     * @return FoldersForAutoCollate
     */
    public function withAutoCollationTemplateName($autoCollationTemplateName)
    {
        $new = clone $this;
        $new->autoCollationTemplateName = $autoCollationTemplateName;

        return $new;
    }


}

