<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreateWebLinksResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CreateWebLinksResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $oWebLinkList = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCreateWebLinksResult()
    {
        return $this->CreateWebLinksResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CreateWebLinksResult
     * @return CreateWebLinksResponse
     */
    public function withCreateWebLinksResult($CreateWebLinksResult)
    {
        $new = clone $this;
        $new->CreateWebLinksResult = $CreateWebLinksResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getOWebLinkList()
    {
        return $this->oWebLinkList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $oWebLinkList
     * @return CreateWebLinksResponse
     */
    public function withOWebLinkList($oWebLinkList)
    {
        $new = clone $this;
        $new->oWebLinkList = $oWebLinkList;

        return $new;
    }


}

