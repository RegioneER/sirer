<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AutoCollate implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\Folder
     */
    private $defaultFolder = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\Guid $cardId
     * @var string $autoCollationTemplateName
     * @var \ArchiflowWSCard\Type\Folder $defaultFolder
     */
    public function __construct($sessionId, $cardId, $autoCollationTemplateName, $defaultFolder)
    {
        $this->sessionId = $sessionId;
        $this->cardId = $cardId;
        $this->autoCollationTemplateName = $autoCollationTemplateName;
        $this->defaultFolder = $defaultFolder;
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
     * @return AutoCollate
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
     * @return AutoCollate
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
     * @return AutoCollate
     */
    public function withAutoCollationTemplateName($autoCollationTemplateName)
    {
        $new = clone $this;
        $new->autoCollationTemplateName = $autoCollationTemplateName;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Folder
     */
    public function getDefaultFolder()
    {
        return $this->defaultFolder;
    }

    /**
     * @param \ArchiflowWSCard\Type\Folder $defaultFolder
     * @return AutoCollate
     */
    public function withDefaultFolder($defaultFolder)
    {
        $new = clone $this;
        $new->defaultFolder = $defaultFolder;

        return $new;
    }


}

