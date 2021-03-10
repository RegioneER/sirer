<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class BuildFileDigestResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $BuildFileDigestResult = null;

    /**
     * @var string
     */
    private $xmlHashes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getBuildFileDigestResult()
    {
        return $this->BuildFileDigestResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $BuildFileDigestResult
     * @return BuildFileDigestResponse
     */
    public function withBuildFileDigestResult($BuildFileDigestResult)
    {
        $new = clone $this;
        $new->BuildFileDigestResult = $BuildFileDigestResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getXmlHashes()
    {
        return $this->xmlHashes;
    }

    /**
     * @param string $xmlHashes
     * @return BuildFileDigestResponse
     */
    public function withXmlHashes($xmlHashes)
    {
        $new = clone $this;
        $new->xmlHashes = $xmlHashes;

        return $new;
    }


}

