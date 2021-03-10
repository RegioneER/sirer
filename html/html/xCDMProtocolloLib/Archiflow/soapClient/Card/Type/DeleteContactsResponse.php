<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteContactsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $DeleteContactsResult = null;

    /**
     * @var int
     */
    private $nRemoved = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getDeleteContactsResult()
    {
        return $this->DeleteContactsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $DeleteContactsResult
     * @return DeleteContactsResponse
     */
    public function withDeleteContactsResult($DeleteContactsResult)
    {
        $new = clone $this;
        $new->DeleteContactsResult = $DeleteContactsResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNRemoved()
    {
        return $this->nRemoved;
    }

    /**
     * @param int $nRemoved
     * @return DeleteContactsResponse
     */
    public function withNRemoved($nRemoved)
    {
        $new = clone $this;
        $new->nRemoved = $nRemoved;

        return $new;
    }


}

