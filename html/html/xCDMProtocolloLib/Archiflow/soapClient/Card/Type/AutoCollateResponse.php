<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AutoCollateResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $AutoCollateResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Folder
     */
    private $folder = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getAutoCollateResult()
    {
        return $this->AutoCollateResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $AutoCollateResult
     * @return AutoCollateResponse
     */
    public function withAutoCollateResult($AutoCollateResult)
    {
        $new = clone $this;
        $new->AutoCollateResult = $AutoCollateResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Folder
     */
    public function getFolder()
    {
        return $this->folder;
    }

    /**
     * @param \ArchiflowWSCard\Type\Folder $folder
     * @return AutoCollateResponse
     */
    public function withFolder($folder)
    {
        $new = clone $this;
        $new->folder = $folder;

        return $new;
    }


}

