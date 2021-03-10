<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetListItemsAdditivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetListItemsAdditivesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfListItem
     */
    private $indexItems = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetListItemsAdditivesResult()
    {
        return $this->GetListItemsAdditivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetListItemsAdditivesResult
     * @return GetListItemsAdditivesResponse
     */
    public function withGetListItemsAdditivesResult($GetListItemsAdditivesResult)
    {
        $new = clone $this;
        $new->GetListItemsAdditivesResult = $GetListItemsAdditivesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfListItem
     */
    public function getIndexItems()
    {
        return $this->indexItems;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfListItem $indexItems
     * @return GetListItemsAdditivesResponse
     */
    public function withIndexItems($indexItems)
    {
        $new = clone $this;
        $new->indexItems = $indexItems;

        return $new;
    }


}

