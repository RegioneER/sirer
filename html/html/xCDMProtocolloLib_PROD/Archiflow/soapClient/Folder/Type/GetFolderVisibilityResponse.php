<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetFolderVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetFolderVisibilityResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\SendObject
     */
    private $oSendObject = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetFolderVisibilityResult()
    {
        return $this->GetFolderVisibilityResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetFolderVisibilityResult
     * @return GetFolderVisibilityResponse
     */
    public function withGetFolderVisibilityResult($GetFolderVisibilityResult)
    {
        $new = clone $this;
        $new->GetFolderVisibilityResult = $GetFolderVisibilityResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SendObject
     */
    public function getOSendObject()
    {
        return $this->oSendObject;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendObject $oSendObject
     * @return GetFolderVisibilityResponse
     */
    public function withOSendObject($oSendObject)
    {
        $new = clone $this;
        $new->oSendObject = $oSendObject;

        return $new;
    }


}

