<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDomainsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetDomainsResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\ArrayOfArchiflowDomain
     */
    private $oDomains = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetDomainsResult()
    {
        return $this->GetDomainsResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetDomainsResult
     * @return GetDomainsResponse
     */
    public function withGetDomainsResult($GetDomainsResult)
    {
        $new = clone $this;
        $new->GetDomainsResult = $GetDomainsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\ArrayOfArchiflowDomain
     */
    public function getODomains()
    {
        return $this->oDomains;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ArrayOfArchiflowDomain $oDomains
     * @return GetDomainsResponse
     */
    public function withODomains($oDomains)
    {
        $new = clone $this;
        $new->oDomains = $oDomains;

        return $new;
    }


}

