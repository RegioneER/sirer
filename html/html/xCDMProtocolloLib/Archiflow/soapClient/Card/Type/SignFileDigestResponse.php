<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SignFileDigestResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SignFileDigestResult = null;

    /**
     * @var string
     */
    private $xmlSignedHashes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSignFileDigestResult()
    {
        return $this->SignFileDigestResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SignFileDigestResult
     * @return SignFileDigestResponse
     */
    public function withSignFileDigestResult($SignFileDigestResult)
    {
        $new = clone $this;
        $new->SignFileDigestResult = $SignFileDigestResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getXmlSignedHashes()
    {
        return $this->xmlSignedHashes;
    }

    /**
     * @param string $xmlSignedHashes
     * @return SignFileDigestResponse
     */
    public function withXmlSignedHashes($xmlSignedHashes)
    {
        $new = clone $this;
        $new->xmlSignedHashes = $xmlSignedHashes;

        return $new;
    }


}

