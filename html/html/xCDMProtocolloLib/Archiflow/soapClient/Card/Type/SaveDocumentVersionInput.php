<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SaveDocumentVersionInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $SubNetId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $SubNetId
     */
    public function __construct($CardId, $SubNetId)
    {
        $this->CardId = $CardId;
        $this->SubNetId = $SubNetId;
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
     * @return SaveDocumentVersionInput
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
    public function getSubNetId()
    {
        return $this->SubNetId;
    }

    /**
     * @param int $SubNetId
     * @return SaveDocumentVersionInput
     */
    public function withSubNetId($SubNetId)
    {
        $new = clone $this;
        $new->SubNetId = $SubNetId;

        return $new;
    }


}

