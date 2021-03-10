<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ExportCardsToCsvResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ExportCardsToCsvOutput
     */
    private $ExportCardsToCsvResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ExportCardsToCsvOutput
     */
    public function getExportCardsToCsvResult()
    {
        return $this->ExportCardsToCsvResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExportCardsToCsvOutput $ExportCardsToCsvResult
     * @return ExportCardsToCsvResponse
     */
    public function withExportCardsToCsvResult($ExportCardsToCsvResult)
    {
        $new = clone $this;
        $new->ExportCardsToCsvResult = $ExportCardsToCsvResult;

        return $new;
    }


}

