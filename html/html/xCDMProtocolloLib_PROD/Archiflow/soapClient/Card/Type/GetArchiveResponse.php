<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetArchiveResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetArchiveResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Archive
     */
    private $oArchive = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetArchiveResult()
    {
        return $this->GetArchiveResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetArchiveResult
     * @return GetArchiveResponse
     */
    public function withGetArchiveResult($GetArchiveResult)
    {
        $new = clone $this;
        $new->GetArchiveResult = $GetArchiveResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Archive
     */
    public function getOArchive()
    {
        return $this->oArchive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Archive $oArchive
     * @return GetArchiveResponse
     */
    public function withOArchive($oArchive)
    {
        $new = clone $this;
        $new->oArchive = $oArchive;

        return $new;
    }


}

