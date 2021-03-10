<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyAttachmentNoteResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ModifyAttachmentNoteResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getModifyAttachmentNoteResult()
    {
        return $this->ModifyAttachmentNoteResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ModifyAttachmentNoteResult
     * @return ModifyAttachmentNoteResponse
     */
    public function withModifyAttachmentNoteResult($ModifyAttachmentNoteResult)
    {
        $new = clone $this;
        $new->ModifyAttachmentNoteResult = $ModifyAttachmentNoteResult;

        return $new;
    }


}

