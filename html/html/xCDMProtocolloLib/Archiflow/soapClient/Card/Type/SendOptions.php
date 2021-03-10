<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendOptions implements RequestInterface
{

    /**
     * @var bool
     */
    private $IsAutomaticSending = null;

    /**
     * @var bool
     */
    private $IsDisabledReceivers = null;

    /**
     * @var bool
     */
    private $IsVisibleOnlyDoc = null;

    /**
     * Constructor
     *
     * @var bool $IsAutomaticSending
     * @var bool $IsDisabledReceivers
     * @var bool $IsVisibleOnlyDoc
     */
    public function __construct($IsAutomaticSending, $IsDisabledReceivers, $IsVisibleOnlyDoc)
    {
        $this->IsAutomaticSending = $IsAutomaticSending;
        $this->IsDisabledReceivers = $IsDisabledReceivers;
        $this->IsVisibleOnlyDoc = $IsVisibleOnlyDoc;
    }

    /**
     * @return bool
     */
    public function getIsAutomaticSending()
    {
        return $this->IsAutomaticSending;
    }

    /**
     * @param bool $IsAutomaticSending
     * @return SendOptions
     */
    public function withIsAutomaticSending($IsAutomaticSending)
    {
        $new = clone $this;
        $new->IsAutomaticSending = $IsAutomaticSending;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsDisabledReceivers()
    {
        return $this->IsDisabledReceivers;
    }

    /**
     * @param bool $IsDisabledReceivers
     * @return SendOptions
     */
    public function withIsDisabledReceivers($IsDisabledReceivers)
    {
        $new = clone $this;
        $new->IsDisabledReceivers = $IsDisabledReceivers;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsVisibleOnlyDoc()
    {
        return $this->IsVisibleOnlyDoc;
    }

    /**
     * @param bool $IsVisibleOnlyDoc
     * @return SendOptions
     */
    public function withIsVisibleOnlyDoc($IsVisibleOnlyDoc)
    {
        $new = clone $this;
        $new->IsVisibleOnlyDoc = $IsVisibleOnlyDoc;

        return $new;
    }


}

