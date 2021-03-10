<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RemoveAttachmentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RemoveAttachmentResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRemoveAttachmentResult()
    {
        return $this->RemoveAttachmentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RemoveAttachmentResult
     * @return RemoveAttachmentResponse
     */
    public function withRemoveAttachmentResult($RemoveAttachmentResult)
    {
        $new = clone $this;
        $new->RemoveAttachmentResult = $RemoveAttachmentResult;

        return $new;
    }


}

