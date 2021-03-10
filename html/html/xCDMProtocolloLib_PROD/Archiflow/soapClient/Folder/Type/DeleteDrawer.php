<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteDrawer implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $drawerId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $drawerId
     */
    public function __construct($strSessionId, $drawerId)
    {
        $this->strSessionId = $strSessionId;
        $this->drawerId = $drawerId;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return DeleteDrawer
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDrawerId()
    {
        return $this->drawerId;
    }

    /**
     * @param int $drawerId
     * @return DeleteDrawer
     */
    public function withDrawerId($drawerId)
    {
        $new = clone $this;
        $new->drawerId = $drawerId;

        return $new;
    }


}

