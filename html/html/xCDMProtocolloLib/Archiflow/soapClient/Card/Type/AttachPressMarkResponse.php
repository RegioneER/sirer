<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AttachPressMarkResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AttachPressMarkOutput
     */
    private $AttachPressMarkResult = null;

    /**
     * @return \ArchiflowWSCard\Type\AttachPressMarkOutput
     */
    public function getAttachPressMarkResult()
    {
        return $this->AttachPressMarkResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\AttachPressMarkOutput $AttachPressMarkResult
     * @return AttachPressMarkResponse
     */
    public function withAttachPressMarkResult($AttachPressMarkResult)
    {
        $new = clone $this;
        $new->AttachPressMarkResult = $AttachPressMarkResult;

        return $new;
    }


}

