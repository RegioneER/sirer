<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SortCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SortCardResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardGuid = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSortCardResult()
    {
        return $this->SortCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SortCardResult
     * @return SortCardResponse
     */
    public function withSortCardResult($SortCardResult)
    {
        $new = clone $this;
        $new->SortCardResult = $SortCardResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardGuid()
    {
        return $this->oCardGuid;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardGuid
     * @return SortCardResponse
     */
    public function withOCardGuid($oCardGuid)
    {
        $new = clone $this;
        $new->oCardGuid = $oCardGuid;

        return $new;
    }


}

