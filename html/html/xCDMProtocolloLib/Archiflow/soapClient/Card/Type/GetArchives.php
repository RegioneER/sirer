<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetArchives implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\AccessLevel
     */
    private $enAccessLevel = null;

    /**
     * @var bool
     */
    private $bReturnAll = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @var bool $bReturnAll
     */
    public function __construct($strSessionId, $enAccessLevel, $bReturnAll)
    {
        $this->strSessionId = $strSessionId;
        $this->enAccessLevel = $enAccessLevel;
        $this->bReturnAll = $bReturnAll;
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
     * @return GetArchives
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AccessLevel
     */
    public function getEnAccessLevel()
    {
        return $this->enAccessLevel;
    }

    /**
     * @param \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @return GetArchives
     */
    public function withEnAccessLevel($enAccessLevel)
    {
        $new = clone $this;
        $new->enAccessLevel = $enAccessLevel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBReturnAll()
    {
        return $this->bReturnAll;
    }

    /**
     * @param bool $bReturnAll
     * @return GetArchives
     */
    public function withBReturnAll($bReturnAll)
    {
        $new = clone $this;
        $new->bReturnAll = $bReturnAll;

        return $new;
    }


}

