<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ImportDocument2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ImportDocument2Result = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getImportDocument2Result()
    {
        return $this->ImportDocument2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ImportDocument2Result
     * @return ImportDocument2Response
     */
    public function withImportDocument2Result($ImportDocument2Result)
    {
        $new = clone $this;
        $new->ImportDocument2Result = $ImportDocument2Result;

        return $new;
    }


}

