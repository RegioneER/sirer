<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreateTimeStampedDataFileDigestResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CreateTimeStampedDataFileDigestResult = null;

    /**
     * @var string
     */
    private $xmlTSDSignedHashes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCreateTimeStampedDataFileDigestResult()
    {
        return $this->CreateTimeStampedDataFileDigestResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CreateTimeStampedDataFileDigestResult
     * @return CreateTimeStampedDataFileDigestResponse
     */
    public function withCreateTimeStampedDataFileDigestResult($CreateTimeStampedDataFileDigestResult)
    {
        $new = clone $this;
        $new->CreateTimeStampedDataFileDigestResult = $CreateTimeStampedDataFileDigestResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getXmlTSDSignedHashes()
    {
        return $this->xmlTSDSignedHashes;
    }

    /**
     * @param string $xmlTSDSignedHashes
     * @return CreateTimeStampedDataFileDigestResponse
     */
    public function withXmlTSDSignedHashes($xmlTSDSignedHashes)
    {
        $new = clone $this;
        $new->xmlTSDSignedHashes = $xmlTSDSignedHashes;

        return $new;
    }


}

