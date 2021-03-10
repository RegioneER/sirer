<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertDrawerResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $InsertDrawerResult = null;

    /**
     * @var int
     */
    private $newDrawerId = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getInsertDrawerResult()
    {
        return $this->InsertDrawerResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $InsertDrawerResult
     * @return InsertDrawerResponse
     */
    public function withInsertDrawerResult($InsertDrawerResult)
    {
        $new = clone $this;
        $new->InsertDrawerResult = $InsertDrawerResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNewDrawerId()
    {
        return $this->newDrawerId;
    }

    /**
     * @param int $newDrawerId
     * @return InsertDrawerResponse
     */
    public function withNewDrawerId($newDrawerId)
    {
        $new = clone $this;
        $new->newDrawerId = $newDrawerId;

        return $new;
    }


}

