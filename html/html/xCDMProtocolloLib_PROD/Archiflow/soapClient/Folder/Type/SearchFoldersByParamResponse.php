<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SearchFoldersByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SearchFoldersByParamOutput
     */
    private $SearchFoldersByParamResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\SearchFoldersByParamOutput
     */
    public function getSearchFoldersByParamResult()
    {
        return $this->SearchFoldersByParamResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SearchFoldersByParamOutput
     * $SearchFoldersByParamResult
     * @return SearchFoldersByParamResponse
     */
    public function withSearchFoldersByParamResult($SearchFoldersByParamResult)
    {
        $new = clone $this;
        $new->SearchFoldersByParamResult = $SearchFoldersByParamResult;

        return $new;
    }


}

