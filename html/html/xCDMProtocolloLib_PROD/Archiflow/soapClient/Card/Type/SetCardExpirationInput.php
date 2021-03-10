<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardExpirationInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $Duration = null;

    /**
     * @var \ArchiflowWSCard\Type\ExpirationMethodType
     */
    private $ExpirationMethod = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $Duration
     * @var \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     */
    public function __construct($CardId, $Duration, $ExpirationMethod)
    {
        $this->CardId = $CardId;
        $this->Duration = $Duration;
        $this->ExpirationMethod = $ExpirationMethod;
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
     * @return SetCardExpirationInput
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
    public function getDuration()
    {
        return $this->Duration;
    }

    /**
     * @param int $Duration
     * @return SetCardExpirationInput
     */
    public function withDuration($Duration)
    {
        $new = clone $this;
        $new->Duration = $Duration;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExpirationMethodType
     */
    public function getExpirationMethod()
    {
        return $this->ExpirationMethod;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @return SetCardExpirationInput
     */
    public function withExpirationMethod($ExpirationMethod)
    {
        $new = clone $this;
        $new->ExpirationMethod = $ExpirationMethod;

        return $new;
    }


}

