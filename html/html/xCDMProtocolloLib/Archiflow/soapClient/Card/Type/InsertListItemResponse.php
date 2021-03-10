<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertListItemResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertListItemResult = null;

    /**
     * @var int
     */
    private $newListItemId = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertListItemResult()
    {
        return $this->InsertListItemResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertListItemResult
     * @return InsertListItemResponse
     */
    public function withInsertListItemResult($InsertListItemResult)
    {
        $new = clone $this;
        $new->InsertListItemResult = $InsertListItemResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNewListItemId()
    {
        return $this->newListItemId;
    }

    /**
     * @param int $newListItemId
     * @return InsertListItemResponse
     */
    public function withNewListItemId($newListItemId)
    {
        $new = clone $this;
        $new->newListItemId = $newListItemId;

        return $new;
    }


}

