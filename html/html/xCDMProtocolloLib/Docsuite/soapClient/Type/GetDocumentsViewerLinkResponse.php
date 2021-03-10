<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentsViewerLinkResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $GetDocumentsViewerLinkResult = null;

    /**
     * @return string
     */
    public function getGetDocumentsViewerLinkResult()
    {
        return $this->GetDocumentsViewerLinkResult;
    }

    /**
     * @param string $GetDocumentsViewerLinkResult
     * @return GetDocumentsViewerLinkResponse
     */
    public function withGetDocumentsViewerLinkResult($GetDocumentsViewerLinkResult)
    {
        $new = clone $this;
        $new->GetDocumentsViewerLinkResult = $GetDocumentsViewerLinkResult;

        return $new;
    }


}

