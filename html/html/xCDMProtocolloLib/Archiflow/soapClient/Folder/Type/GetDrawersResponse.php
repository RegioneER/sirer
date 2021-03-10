<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDrawersResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetDrawersResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfDrawer
     */
    private $oDrawers = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetDrawersResult()
    {
        return $this->GetDrawersResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetDrawersResult
     * @return GetDrawersResponse
     */
    public function withGetDrawersResult($GetDrawersResult)
    {
        $new = clone $this;
        $new->GetDrawersResult = $GetDrawersResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfDrawer
     */
    public function getODrawers()
    {
        return $this->oDrawers;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfDrawer $oDrawers
     * @return GetDrawersResponse
     */
    public function withODrawers($oDrawers)
    {
        $new = clone $this;
        $new->oDrawers = $oDrawers;

        return $new;
    }


}

