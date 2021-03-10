<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceMonitor implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfPhase
     */
    private $Phases = null;

    /**
     * @var int
     */
    private $Total = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfPhase $Phases
     * @var int $Total
     */
    public function __construct($Phases, $Total)
    {
        $this->Phases = $Phases;
        $this->Total = $Total;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfPhase
     */
    public function getPhases()
    {
        return $this->Phases;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfPhase $Phases
     * @return InvoiceMonitor
     */
    public function withPhases($Phases)
    {
        $new = clone $this;
        $new->Phases = $Phases;

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
     * @return InvoiceMonitor
     */
    public function withTotal($Total)
    {
        $new = clone $this;
        $new->Total = $Total;

        return $new;
    }


}

