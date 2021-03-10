<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CheckCreateZipCardsDataInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $ZipOperationId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $ZipOperationId
     */
    public function __construct($ZipOperationId)
    {
        $this->ZipOperationId = $ZipOperationId;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getZipOperationId()
    {
        return $this->ZipOperationId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $ZipOperationId
     * @return CheckCreateZipCardsDataInput
     */
    public function withZipOperationId($ZipOperationId)
    {
        $new = clone $this;
        $new->ZipOperationId = $ZipOperationId;

        return $new;
    }


}

