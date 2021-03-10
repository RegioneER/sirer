<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetListItemsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetListItemsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfListItem
     */
    private $oIndexItems = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetListItemsResult()
    {
        return $this->GetListItemsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetListItemsResult
     * @return GetListItemsResponse
     */
    public function withGetListItemsResult($GetListItemsResult)
    {
        $new = clone $this;
        $new->GetListItemsResult = $GetListItemsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfListItem
     */
    public function getOIndexItems()
    {
        return $this->oIndexItems;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfListItem $oIndexItems
     * @return GetListItemsResponse
     */
    public function withOIndexItems($oIndexItems)
    {
        $new = clone $this;
        $new->oIndexItems = $oIndexItems;

        return $new;
    }


}

