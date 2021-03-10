<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class MoveCardDocAndAttachmentsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsOutput
     */
    private $MoveCardDocAndAttachmentsResult = null;

    /**
     * @return \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsOutput
     */
    public function getMoveCardDocAndAttachmentsResult()
    {
        return $this->MoveCardDocAndAttachmentsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsOutput
     * $MoveCardDocAndAttachmentsResult
     * @return MoveCardDocAndAttachmentsResponse
     */
    public function withMoveCardDocAndAttachmentsResult($MoveCardDocAndAttachmentsResult)
    {
        $new = clone $this;
        $new->MoveCardDocAndAttachmentsResult = $MoveCardDocAndAttachmentsResult;

        return $new;
    }


}

