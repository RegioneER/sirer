<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCardContactId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafEntityId
     */
    private $ContactId = null;

    /**
     * @var string
     */
    private $Tag = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafEntityId $ContactId
     * @var string $Tag
     */
    public function __construct($ContactId, $Tag)
    {
        $this->ContactId = $ContactId;
        $this->Tag = $Tag;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafEntityId
     */
    public function getContactId()
    {
        return $this->ContactId;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafEntityId $ContactId
     * @return AgrafCardContactId
     */
    public function withContactId($ContactId)
    {
        $new = clone $this;
        $new->ContactId = $ContactId;

        return $new;
    }

    /**
     * @return string
     */
    public function getTag()
    {
        return $this->Tag;
    }

    /**
     * @param string $Tag
     * @return AgrafCardContactId
     */
    public function withTag($Tag)
    {
        $new = clone $this;
        $new->Tag = $Tag;

        return $new;
    }


}

