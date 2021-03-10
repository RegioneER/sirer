<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetContactResponse implements ResultInterface
{

    /**
     * @var int
     */
    private $GetContactResult = null;

    /**
     * @return int
     */
    public function getGetContactResult()
    {
        return $this->GetContactResult;
    }

    /**
     * @param int $GetContactResult
     * @return GetContactResponse
     */
    public function withGetContactResult($GetContactResult)
    {
        $new = clone $this;
        $new->GetContactResult = $GetContactResult;

        return $new;
    }


}

