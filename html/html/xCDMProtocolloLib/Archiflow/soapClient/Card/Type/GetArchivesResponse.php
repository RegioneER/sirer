<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetArchivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetArchivesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfArchive
     */
    private $oArchives = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetArchivesResult()
    {
        return $this->GetArchivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetArchivesResult
     * @return GetArchivesResponse
     */
    public function withGetArchivesResult($GetArchivesResult)
    {
        $new = clone $this;
        $new->GetArchivesResult = $GetArchivesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfArchive
     */
    public function getOArchives()
    {
        return $this->oArchives;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfArchive $oArchives
     * @return GetArchivesResponse
     */
    public function withOArchives($oArchives)
    {
        $new = clone $this;
        $new->oArchives = $oArchives;

        return $new;
    }


}

