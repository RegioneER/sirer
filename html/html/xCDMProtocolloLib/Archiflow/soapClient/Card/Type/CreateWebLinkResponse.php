<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreateWebLinkResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CreateWebLinkResult = null;

    /**
     * @var string
     */
    private $webLink = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCreateWebLinkResult()
    {
        return $this->CreateWebLinkResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CreateWebLinkResult
     * @return CreateWebLinkResponse
     */
    public function withCreateWebLinkResult($CreateWebLinkResult)
    {
        $new = clone $this;
        $new->CreateWebLinkResult = $CreateWebLinkResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getWebLink()
    {
        return $this->webLink;
    }

    /**
     * @param string $webLink
     * @return CreateWebLinkResponse
     */
    public function withWebLink($webLink)
    {
        $new = clone $this;
        $new->webLink = $webLink;

        return $new;
    }


}

