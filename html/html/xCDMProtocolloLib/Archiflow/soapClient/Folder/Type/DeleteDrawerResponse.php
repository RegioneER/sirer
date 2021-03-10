<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteDrawerResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $DeleteDrawerResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getDeleteDrawerResult()
    {
        return $this->DeleteDrawerResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $DeleteDrawerResult
     * @return DeleteDrawerResponse
     */
    public function withDeleteDrawerResult($DeleteDrawerResult)
    {
        $new = clone $this;
        $new->DeleteDrawerResult = $DeleteDrawerResult;

        return $new;
    }


}

