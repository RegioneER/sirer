<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypesInSearchResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypesInSearchResult = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchResult
     */
    private $searchResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $docTypeIds = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypesInSearchResult()
    {
        return $this->GetDocumentTypesInSearchResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypesInSearchResult
     * @return GetDocumentTypesInSearchResponse
     */
    public function withGetDocumentTypesInSearchResult($GetDocumentTypesInSearchResult)
    {
        $new = clone $this;
        $new->GetDocumentTypesInSearchResult = $GetDocumentTypesInSearchResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchResult
     */
    public function getSearchResult()
    {
        return $this->searchResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchResult $searchResult
     * @return GetDocumentTypesInSearchResponse
     */
    public function withSearchResult($searchResult)
    {
        $new = clone $this;
        $new->searchResult = $searchResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getDocTypeIds()
    {
        return $this->docTypeIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $docTypeIds
     * @return GetDocumentTypesInSearchResponse
     */
    public function withDocTypeIds($docTypeIds)
    {
        $new = clone $this;
        $new->docTypeIds = $docTypeIds;

        return $new;
    }


}

