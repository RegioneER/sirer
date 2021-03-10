<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardKeyVersionsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardKeyVersionsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfKeyVersion
     */
    private $keyVersions = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardKeyVersionsResult()
    {
        return $this->GetCardKeyVersionsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardKeyVersionsResult
     * @return GetCardKeyVersionsResponse
     */
    public function withGetCardKeyVersionsResult($GetCardKeyVersionsResult)
    {
        $new = clone $this;
        $new->GetCardKeyVersionsResult = $GetCardKeyVersionsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfKeyVersion
     */
    public function getKeyVersions()
    {
        return $this->keyVersions;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfKeyVersion $keyVersions
     * @return GetCardKeyVersionsResponse
     */
    public function withKeyVersions($keyVersions)
    {
        $new = clone $this;
        $new->keyVersions = $keyVersions;

        return $new;
    }


}

