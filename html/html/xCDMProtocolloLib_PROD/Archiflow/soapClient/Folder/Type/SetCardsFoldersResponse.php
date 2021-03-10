<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardsFoldersResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SetCardsFoldersOutput
     */
    private $SetCardsFoldersResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\SetCardsFoldersOutput
     */
    public function getSetCardsFoldersResult()
    {
        return $this->SetCardsFoldersResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SetCardsFoldersOutput $SetCardsFoldersResult
     * @return SetCardsFoldersResponse
     */
    public function withSetCardsFoldersResult($SetCardsFoldersResult)
    {
        $new = clone $this;
        $new->SetCardsFoldersResult = $SetCardsFoldersResult;

        return $new;
    }


}

