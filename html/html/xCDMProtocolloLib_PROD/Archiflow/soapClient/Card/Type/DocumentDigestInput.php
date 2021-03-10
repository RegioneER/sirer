<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentDigestInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $SubnetId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $SubnetId
     */
    public function __construct($CardId, $SubnetId)
    {
        $this->CardId = $CardId;
        $this->SubnetId = $SubnetId;
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
     * @return DocumentDigestInput
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
    public function getSubnetId()
    {
        return $this->SubnetId;
    }

    /**
     * @param int $SubnetId
     * @return DocumentDigestInput
     */
    public function withSubnetId($SubnetId)
    {
        $new = clone $this;
        $new->SubnetId = $SubnetId;

        return $new;
    }


}

