<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Channel implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $Guid = null;

    /**
     * @var int
     */
    private $Total = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $Guid
     * @var int $Total
     */
    public function __construct($Guid, $Total)
    {
        $this->Guid = $Guid;
        $this->Total = $Total;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getGuid()
    {
        return $this->Guid;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $Guid
     * @return Channel
     */
    public function withGuid($Guid)
    {
        $new = clone $this;
        $new->Guid = $Guid;

        return $new;
    }

    /**
     * @return int
     */
    public function getTotal()
    {
        return $this->Total;
    }

    /**
     * @param int $Total
     * @return Channel
     */
    public function withTotal($Total)
    {
        $new = clone $this;
        $new->Total = $Total;

        return $new;
    }


}

