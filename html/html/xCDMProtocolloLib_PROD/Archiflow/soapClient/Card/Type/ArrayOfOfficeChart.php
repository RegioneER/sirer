<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfOfficeChart implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\OfficeChart
     */
    private $OfficeChart = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\OfficeChart $OfficeChart
     */
    public function __construct($OfficeChart)
    {
        $this->OfficeChart = $OfficeChart;
    }

    /**
     * @return \ArchiflowWSCard\Type\OfficeChart
     */
    public function getOfficeChart()
    {
        return $this->OfficeChart;
    }

    /**
     * @param \ArchiflowWSCard\Type\OfficeChart $OfficeChart
     * @return ArrayOfOfficeChart
     */
    public function withOfficeChart($OfficeChart)
    {
        $new = clone $this;
        $new->OfficeChart = $OfficeChart;

        return $new;
    }


}

