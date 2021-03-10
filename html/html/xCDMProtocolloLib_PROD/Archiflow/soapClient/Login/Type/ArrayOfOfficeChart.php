<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfOfficeChart implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\OfficeChart
     */
    private $OfficeChart = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\OfficeChart $OfficeChart
     */
    public function __construct($OfficeChart)
    {
        $this->OfficeChart = $OfficeChart;
    }

    /**
     * @return \ArchiflowWSLogin\Type\OfficeChart
     */
    public function getOfficeChart()
    {
        return $this->OfficeChart;
    }

    /**
     * @param \ArchiflowWSLogin\Type\OfficeChart $OfficeChart
     * @return ArrayOfOfficeChart
     */
    public function withOfficeChart($OfficeChart)
    {
        $new = clone $this;
        $new->OfficeChart = $OfficeChart;

        return $new;
    }


}

