<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SearchCards2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SearchCards2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSearchCards2Result()
    {
        return $this->SearchCards2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SearchCards2Result
     * @return SearchCards2Response
     */
    public function withSearchCards2Result($SearchCards2Result)
    {
        $new = clone $this;
        $new->SearchCards2Result = $SearchCards2Result;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOCardIds()
    {
        return $this->oCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @return SearchCards2Response
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }


}

