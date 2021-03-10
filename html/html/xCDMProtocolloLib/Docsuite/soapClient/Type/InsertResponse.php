<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $InsertResult = null;

    /**
     * @return string
     */
    public function getInsertResult()
    {
        return $this->InsertResult;
    }

    /**
     * @param string $InsertResult
     * @return InsertResponse
     */
    public function withInsertResult($InsertResult)
    {
        $new = clone $this;
        $new->InsertResult = $InsertResult;

        return $new;
    }


}

