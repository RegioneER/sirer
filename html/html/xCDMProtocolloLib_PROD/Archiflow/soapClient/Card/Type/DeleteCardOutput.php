<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteCardOutput implements RequestInterface
{

    /**
     * @var bool
     */
    private $Deleted = null;

    /**
     * Constructor
     *
     * @var bool $Deleted
     */
    public function __construct($Deleted)
    {
        $this->Deleted = $Deleted;
    }

    /**
     * @return bool
     */
    public function getDeleted()
    {
        return $this->Deleted;
    }

    /**
     * @param bool $Deleted
     * @return DeleteCardOutput
     */
    public function withDeleted($Deleted)
    {
        $new = clone $this;
        $new->Deleted = $Deleted;

        return $new;
    }


}

