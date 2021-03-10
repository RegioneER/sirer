<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceDataTransmissionSearchCriteria implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $ArchiveList = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $CompetenceDate = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $InsertDate = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $PhaseList = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $StatusList = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfint $ArchiveList
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $CompetenceDate
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InsertDate
     * @var \ArchiflowWSCard\Type\ArrayOfstring $PhaseList
     * @var \ArchiflowWSCard\Type\ArrayOfstring $StatusList
     */
    public function __construct($ArchiveList, $CompetenceDate, $InsertDate, $PhaseList, $StatusList)
    {
        $this->ArchiveList = $ArchiveList;
        $this->CompetenceDate = $CompetenceDate;
        $this->InsertDate = $InsertDate;
        $this->PhaseList = $PhaseList;
        $this->StatusList = $StatusList;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getArchiveList()
    {
        return $this->ArchiveList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $ArchiveList
     * @return InvoiceDataTransmissionSearchCriteria
     */
    public function withArchiveList($ArchiveList)
    {
        $new = clone $this;
        $new->ArchiveList = $ArchiveList;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getCompetenceDate()
    {
        return $this->CompetenceDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $CompetenceDate
     * @return InvoiceDataTransmissionSearchCriteria
     */
    public function withCompetenceDate($CompetenceDate)
    {
        $new = clone $this;
        $new->CompetenceDate = $CompetenceDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getInsertDate()
    {
        return $this->InsertDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InsertDate
     * @return InvoiceDataTransmissionSearchCriteria
     */
    public function withInsertDate($InsertDate)
    {
        $new = clone $this;
        $new->InsertDate = $InsertDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getPhaseList()
    {
        return $this->PhaseList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $PhaseList
     * @return InvoiceDataTransmissionSearchCriteria
     */
    public function withPhaseList($PhaseList)
    {
        $new = clone $this;
        $new->PhaseList = $PhaseList;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getStatusList()
    {
        return $this->StatusList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $StatusList
     * @return InvoiceDataTransmissionSearchCriteria
     */
    public function withStatusList($StatusList)
    {
        $new = clone $this;
        $new->StatusList = $StatusList;

        return $new;
    }


}

