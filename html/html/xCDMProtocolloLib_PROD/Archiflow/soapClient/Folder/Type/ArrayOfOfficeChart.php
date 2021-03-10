<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfOfficeChart implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\OfficeChart
     */
    private $OfficeChart = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\OfficeChart $OfficeChart
     */
    public function __construct($OfficeChart)
    {
        $this->OfficeChart = $OfficeChart;
    }

    /**
     * @return \ArchiflowWSFolder\Type\OfficeChart
     */
    public function getOfficeChart()
    {
        return $this->OfficeChart;
    }

    /**
     * @param \ArchiflowWSFolder\Type\OfficeChart $OfficeChart
     * @return ArrayOfOfficeChart
     */
    public function withOfficeChart($OfficeChart)
    {
        $new = clone $this;
        $new->OfficeChart = $OfficeChart;

        return $new;
    }


}

