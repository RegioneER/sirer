<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExportCardsToCsvOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Base64Binary
     */
    private $CsvBytes = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Base64Binary $CsvBytes
     */
    public function __construct($CsvBytes)
    {
        $this->CsvBytes = $CsvBytes;
    }

    /**
     * @return \ArchiflowWSCard\Type\Base64Binary
     */
    public function getCsvBytes()
    {
        return $this->CsvBytes;
    }

    /**
     * @param \ArchiflowWSCard\Type\Base64Binary $CsvBytes
     * @return ExportCardsToCsvOutput
     */
    public function withCsvBytes($CsvBytes)
    {
        $new = clone $this;
        $new->CsvBytes = $CsvBytes;

        return $new;
    }


}

