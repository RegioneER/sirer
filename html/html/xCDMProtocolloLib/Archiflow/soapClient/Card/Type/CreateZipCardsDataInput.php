<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateZipCardsDataInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $GetOriginalContent = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $SearchCriteria = null;

    /**
     * @var bool
     */
    private $ZipExtAttachments = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var bool $GetOriginalContent
     * @var \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     * @var bool $ZipExtAttachments
     */
    public function __construct($CardIds, $GetOriginalContent, $SearchCriteria, $ZipExtAttachments)
    {
        $this->CardIds = $CardIds;
        $this->GetOriginalContent = $GetOriginalContent;
        $this->SearchCriteria = $SearchCriteria;
        $this->ZipExtAttachments = $ZipExtAttachments;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return CreateZipCardsDataInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetOriginalContent()
    {
        return $this->GetOriginalContent;
    }

    /**
     * @param bool $GetOriginalContent
     * @return CreateZipCardsDataInput
     */
    public function withGetOriginalContent($GetOriginalContent)
    {
        $new = clone $this;
        $new->GetOriginalContent = $GetOriginalContent;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getSearchCriteria()
    {
        return $this->SearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     * @return CreateZipCardsDataInput
     */
    public function withSearchCriteria($SearchCriteria)
    {
        $new = clone $this;
        $new->SearchCriteria = $SearchCriteria;

        return $new;
    }

    /**
     * @return bool
     */
    public function getZipExtAttachments()
    {
        return $this->ZipExtAttachments;
    }

    /**
     * @param bool $ZipExtAttachments
     * @return CreateZipCardsDataInput
     */
    public function withZipExtAttachments($ZipExtAttachments)
    {
        $new = clone $this;
        $new->ZipExtAttachments = $ZipExtAttachments;

        return $new;
    }


}

