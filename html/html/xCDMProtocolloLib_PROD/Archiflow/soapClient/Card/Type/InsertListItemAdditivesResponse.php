<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertListItemAdditivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $InsertListItemAdditivesResult = null;

    /**
     * @var int
     */
    private $newListItemId = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getInsertListItemAdditivesResult()
    {
        return $this->InsertListItemAdditivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $InsertListItemAdditivesResult
     * @return InsertListItemAdditivesResponse
     */
    public function withInsertListItemAdditivesResult($InsertListItemAdditivesResult)
    {
        $new = clone $this;
        $new->InsertListItemAdditivesResult = $InsertListItemAdditivesResult;

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
     * @return InsertListItemAdditivesResponse
     */
    public function withNewListItemId($newListItemId)
    {
        $new = clone $this;
        $new->newListItemId = $newListItemId;

        return $new;
    }


}

