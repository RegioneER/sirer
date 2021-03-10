<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchCriteria implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafSearchCriteria
     */
    private $AgrafSearchCriteria = null;

    /**
     * @var string
     */
    private $AnnotationValue = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfArchive
     */
    private $Archives = null;

    /**
     * @var int
     */
    private $CardProgFrom = null;

    /**
     * @var int
     */
    private $CardProgTo = null;

    /**
     * @var bool
     */
    private $CardWithOutDoc = null;

    /**
     * @var bool
     */
    private $CheckSearchTooLong = null;

    /**
     * @var \ArchiflowWSCard\Type\ClassificationSearchCriteria
     */
    private $ClassificationSearchCriteria = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchContext
     */
    private $Context = null;

    /**
     * @var \ArchiflowWSCard\Type\ContextFullText
     */
    private $ContextFullText = null;

    /**
     * @var \ArchiflowWSCard\Type\DocumentType
     */
    private $DocumentType = null;

    /**
     * @var \ArchiflowWSCard\Type\DurationSearchCriteria
     */
    private $DurationSearchCriteria = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $ExtendedDocumentType = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $Fields = null;

    /**
     * @var string
     */
    private $FilterFullText = null;

    /**
     * @var bool
     */
    private $FuzzySearchFullText = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceDataTransmissionSearchCriteria
     */
    private $InvoiceDataTransmSearchCriteria = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceSearchCriteria
     */
    private $InvoiceSearchCriteria = null;

    /**
     * @var bool
     */
    private $IsForcedDate = null;

    /**
     * @var bool
     */
    private $IsForcedIndex = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchOptions
     */
    private $MainDoc = null;

    /**
     * @var int
     */
    private $MaxFounded = null;

    /**
     * @var int
     */
    private $MaxToWait = null;

    /**
     * @var bool
     */
    private $NoFormatKey = null;

    /**
     * @var string
     */
    private $NoWordFullText = null;

    /**
     * @var bool
     */
    private $NotDisplayInvalidatedCards = null;

    /**
     * @var string
     */
    private $OneWordFullText = null;

    /**
     * @var bool
     */
    private $OnlyConnectedUser = null;

    /**
     * @var \ArchiflowWSCard\Type\FieldToOrderBy
     */
    private $OrderByField = null;

    /**
     * @var \ArchiflowWSCard\Type\KeyOrderType
     */
    private $OrderType = null;

    /**
     * @var bool
     */
    private $PluralSearchFullText = null;

    /**
     * @var \ArchiflowWSCard\Type\RegisterOperation
     */
    private $RegisterOperation = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchResult
     */
    private $SearchResult = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchType
     */
    private $SearchType = null;

    /**
     * @var bool
     */
    private $SortDescending = null;

    /**
     * @var string
     */
    private $StringFullText = null;

    /**
     * @var bool
     */
    private $UseDefaultOptions = null;

    /**
     * @var string
     */
    private $WordsFullText = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafSearchCriteria $AgrafSearchCriteria
     * @var string $AnnotationValue
     * @var \ArchiflowWSCard\Type\ArrayOfArchive $Archives
     * @var int $CardProgFrom
     * @var int $CardProgTo
     * @var bool $CardWithOutDoc
     * @var bool $CheckSearchTooLong
     * @var \ArchiflowWSCard\Type\ClassificationSearchCriteria
     * $ClassificationSearchCriteria
     * @var \ArchiflowWSCard\Type\SearchContext $Context
     * @var \ArchiflowWSCard\Type\ContextFullText $ContextFullText
     * @var \ArchiflowWSCard\Type\DocumentType $DocumentType
     * @var \ArchiflowWSCard\Type\DurationSearchCriteria $DurationSearchCriteria
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType $ExtendedDocumentType
     * @var \ArchiflowWSCard\Type\ArrayOfField $Fields
     * @var string $FilterFullText
     * @var bool $FuzzySearchFullText
     * @var \ArchiflowWSCard\Type\InvoiceDataTransmissionSearchCriteria
     * $InvoiceDataTransmSearchCriteria
     * @var \ArchiflowWSCard\Type\InvoiceSearchCriteria $InvoiceSearchCriteria
     * @var bool $IsForcedDate
     * @var bool $IsForcedIndex
     * @var \ArchiflowWSCard\Type\SearchOptions $MainDoc
     * @var int $MaxFounded
     * @var int $MaxToWait
     * @var bool $NoFormatKey
     * @var string $NoWordFullText
     * @var bool $NotDisplayInvalidatedCards
     * @var string $OneWordFullText
     * @var bool $OnlyConnectedUser
     * @var \ArchiflowWSCard\Type\FieldToOrderBy $OrderByField
     * @var \ArchiflowWSCard\Type\KeyOrderType $OrderType
     * @var bool $PluralSearchFullText
     * @var \ArchiflowWSCard\Type\RegisterOperation $RegisterOperation
     * @var \ArchiflowWSCard\Type\SearchResult $SearchResult
     * @var \ArchiflowWSCard\Type\SearchType $SearchType
     * @var bool $SortDescending
     * @var string $StringFullText
     * @var bool $UseDefaultOptions
     * @var string $WordsFullText
     */
    public function __construct($AgrafSearchCriteria, $AnnotationValue, $Archives, $CardProgFrom, $CardProgTo, $CardWithOutDoc, $CheckSearchTooLong, $ClassificationSearchCriteria, $Context, $ContextFullText, $DocumentType, $DurationSearchCriteria, $ExtendedDocumentType, $Fields, $FilterFullText, $FuzzySearchFullText, $InvoiceDataTransmSearchCriteria, $InvoiceSearchCriteria, $IsForcedDate, $IsForcedIndex, $MainDoc, $MaxFounded, $MaxToWait, $NoFormatKey, $NoWordFullText, $NotDisplayInvalidatedCards, $OneWordFullText, $OnlyConnectedUser, $OrderByField, $OrderType, $PluralSearchFullText, $RegisterOperation, $SearchResult, $SearchType, $SortDescending, $StringFullText, $UseDefaultOptions, $WordsFullText)
    {
        $this->AgrafSearchCriteria = $AgrafSearchCriteria;
        $this->AnnotationValue = $AnnotationValue;
        $this->Archives = $Archives;
        $this->CardProgFrom = $CardProgFrom;
        $this->CardProgTo = $CardProgTo;
        $this->CardWithOutDoc = $CardWithOutDoc;
        $this->CheckSearchTooLong = $CheckSearchTooLong;
        $this->ClassificationSearchCriteria = $ClassificationSearchCriteria;
        $this->Context = $Context;
        $this->ContextFullText = $ContextFullText;
        $this->DocumentType = $DocumentType;
        $this->DurationSearchCriteria = $DurationSearchCriteria;
        $this->ExtendedDocumentType = $ExtendedDocumentType;
        $this->Fields = $Fields;
        $this->FilterFullText = $FilterFullText;
        $this->FuzzySearchFullText = $FuzzySearchFullText;
        $this->InvoiceDataTransmSearchCriteria = $InvoiceDataTransmSearchCriteria;
        $this->InvoiceSearchCriteria = $InvoiceSearchCriteria;
        $this->IsForcedDate = $IsForcedDate;
        $this->IsForcedIndex = $IsForcedIndex;
        $this->MainDoc = $MainDoc;
        $this->MaxFounded = $MaxFounded;
        $this->MaxToWait = $MaxToWait;
        $this->NoFormatKey = $NoFormatKey;
        $this->NoWordFullText = $NoWordFullText;
        $this->NotDisplayInvalidatedCards = $NotDisplayInvalidatedCards;
        $this->OneWordFullText = $OneWordFullText;
        $this->OnlyConnectedUser = $OnlyConnectedUser;
        $this->OrderByField = $OrderByField;
        $this->OrderType = $OrderType;
        $this->PluralSearchFullText = $PluralSearchFullText;
        $this->RegisterOperation = $RegisterOperation;
        $this->SearchResult = $SearchResult;
        $this->SearchType = $SearchType;
        $this->SortDescending = $SortDescending;
        $this->StringFullText = $StringFullText;
        $this->UseDefaultOptions = $UseDefaultOptions;
        $this->WordsFullText = $WordsFullText;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafSearchCriteria
     */
    public function getAgrafSearchCriteria()
    {
        return $this->AgrafSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafSearchCriteria $AgrafSearchCriteria
     * @return SearchCriteria
     */
    public function withAgrafSearchCriteria($AgrafSearchCriteria)
    {
        $new = clone $this;
        $new->AgrafSearchCriteria = $AgrafSearchCriteria;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnotationValue()
    {
        return $this->AnnotationValue;
    }

    /**
     * @param string $AnnotationValue
     * @return SearchCriteria
     */
    public function withAnnotationValue($AnnotationValue)
    {
        $new = clone $this;
        $new->AnnotationValue = $AnnotationValue;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfArchive
     */
    public function getArchives()
    {
        return $this->Archives;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfArchive $Archives
     * @return SearchCriteria
     */
    public function withArchives($Archives)
    {
        $new = clone $this;
        $new->Archives = $Archives;

        return $new;
    }

    /**
     * @return int
     */
    public function getCardProgFrom()
    {
        return $this->CardProgFrom;
    }

    /**
     * @param int $CardProgFrom
     * @return SearchCriteria
     */
    public function withCardProgFrom($CardProgFrom)
    {
        $new = clone $this;
        $new->CardProgFrom = $CardProgFrom;

        return $new;
    }

    /**
     * @return int
     */
    public function getCardProgTo()
    {
        return $this->CardProgTo;
    }

    /**
     * @param int $CardProgTo
     * @return SearchCriteria
     */
    public function withCardProgTo($CardProgTo)
    {
        $new = clone $this;
        $new->CardProgTo = $CardProgTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCardWithOutDoc()
    {
        return $this->CardWithOutDoc;
    }

    /**
     * @param bool $CardWithOutDoc
     * @return SearchCriteria
     */
    public function withCardWithOutDoc($CardWithOutDoc)
    {
        $new = clone $this;
        $new->CardWithOutDoc = $CardWithOutDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCheckSearchTooLong()
    {
        return $this->CheckSearchTooLong;
    }

    /**
     * @param bool $CheckSearchTooLong
     * @return SearchCriteria
     */
    public function withCheckSearchTooLong($CheckSearchTooLong)
    {
        $new = clone $this;
        $new->CheckSearchTooLong = $CheckSearchTooLong;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ClassificationSearchCriteria
     */
    public function getClassificationSearchCriteria()
    {
        return $this->ClassificationSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\ClassificationSearchCriteria
     * $ClassificationSearchCriteria
     * @return SearchCriteria
     */
    public function withClassificationSearchCriteria($ClassificationSearchCriteria)
    {
        $new = clone $this;
        $new->ClassificationSearchCriteria = $ClassificationSearchCriteria;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchContext
     */
    public function getContext()
    {
        return $this->Context;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchContext $Context
     * @return SearchCriteria
     */
    public function withContext($Context)
    {
        $new = clone $this;
        $new->Context = $Context;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ContextFullText
     */
    public function getContextFullText()
    {
        return $this->ContextFullText;
    }

    /**
     * @param \ArchiflowWSCard\Type\ContextFullText $ContextFullText
     * @return SearchCriteria
     */
    public function withContextFullText($ContextFullText)
    {
        $new = clone $this;
        $new->ContextFullText = $ContextFullText;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentType
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentType $DocumentType
     * @return SearchCriteria
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DurationSearchCriteria
     */
    public function getDurationSearchCriteria()
    {
        return $this->DurationSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\DurationSearchCriteria $DurationSearchCriteria
     * @return SearchCriteria
     */
    public function withDurationSearchCriteria($DurationSearchCriteria)
    {
        $new = clone $this;
        $new->DurationSearchCriteria = $DurationSearchCriteria;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    public function getExtendedDocumentType()
    {
        return $this->ExtendedDocumentType;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfDocumentType $ExtendedDocumentType
     * @return SearchCriteria
     */
    public function withExtendedDocumentType($ExtendedDocumentType)
    {
        $new = clone $this;
        $new->ExtendedDocumentType = $ExtendedDocumentType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getFields()
    {
        return $this->Fields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $Fields
     * @return SearchCriteria
     */
    public function withFields($Fields)
    {
        $new = clone $this;
        $new->Fields = $Fields;

        return $new;
    }

    /**
     * @return string
     */
    public function getFilterFullText()
    {
        return $this->FilterFullText;
    }

    /**
     * @param string $FilterFullText
     * @return SearchCriteria
     */
    public function withFilterFullText($FilterFullText)
    {
        $new = clone $this;
        $new->FilterFullText = $FilterFullText;

        return $new;
    }

    /**
     * @return bool
     */
    public function getFuzzySearchFullText()
    {
        return $this->FuzzySearchFullText;
    }

    /**
     * @param bool $FuzzySearchFullText
     * @return SearchCriteria
     */
    public function withFuzzySearchFullText($FuzzySearchFullText)
    {
        $new = clone $this;
        $new->FuzzySearchFullText = $FuzzySearchFullText;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceDataTransmissionSearchCriteria
     */
    public function getInvoiceDataTransmSearchCriteria()
    {
        return $this->InvoiceDataTransmSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceDataTransmissionSearchCriteria
     * $InvoiceDataTransmSearchCriteria
     * @return SearchCriteria
     */
    public function withInvoiceDataTransmSearchCriteria($InvoiceDataTransmSearchCriteria)
    {
        $new = clone $this;
        $new->InvoiceDataTransmSearchCriteria = $InvoiceDataTransmSearchCriteria;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceSearchCriteria
     */
    public function getInvoiceSearchCriteria()
    {
        return $this->InvoiceSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceSearchCriteria $InvoiceSearchCriteria
     * @return SearchCriteria
     */
    public function withInvoiceSearchCriteria($InvoiceSearchCriteria)
    {
        $new = clone $this;
        $new->InvoiceSearchCriteria = $InvoiceSearchCriteria;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsForcedDate()
    {
        return $this->IsForcedDate;
    }

    /**
     * @param bool $IsForcedDate
     * @return SearchCriteria
     */
    public function withIsForcedDate($IsForcedDate)
    {
        $new = clone $this;
        $new->IsForcedDate = $IsForcedDate;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsForcedIndex()
    {
        return $this->IsForcedIndex;
    }

    /**
     * @param bool $IsForcedIndex
     * @return SearchCriteria
     */
    public function withIsForcedIndex($IsForcedIndex)
    {
        $new = clone $this;
        $new->IsForcedIndex = $IsForcedIndex;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchOptions
     */
    public function getMainDoc()
    {
        return $this->MainDoc;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchOptions $MainDoc
     * @return SearchCriteria
     */
    public function withMainDoc($MainDoc)
    {
        $new = clone $this;
        $new->MainDoc = $MainDoc;

        return $new;
    }

    /**
     * @return int
     */
    public function getMaxFounded()
    {
        return $this->MaxFounded;
    }

    /**
     * @param int $MaxFounded
     * @return SearchCriteria
     */
    public function withMaxFounded($MaxFounded)
    {
        $new = clone $this;
        $new->MaxFounded = $MaxFounded;

        return $new;
    }

    /**
     * @return int
     */
    public function getMaxToWait()
    {
        return $this->MaxToWait;
    }

    /**
     * @param int $MaxToWait
     * @return SearchCriteria
     */
    public function withMaxToWait($MaxToWait)
    {
        $new = clone $this;
        $new->MaxToWait = $MaxToWait;

        return $new;
    }

    /**
     * @return bool
     */
    public function getNoFormatKey()
    {
        return $this->NoFormatKey;
    }

    /**
     * @param bool $NoFormatKey
     * @return SearchCriteria
     */
    public function withNoFormatKey($NoFormatKey)
    {
        $new = clone $this;
        $new->NoFormatKey = $NoFormatKey;

        return $new;
    }

    /**
     * @return string
     */
    public function getNoWordFullText()
    {
        return $this->NoWordFullText;
    }

    /**
     * @param string $NoWordFullText
     * @return SearchCriteria
     */
    public function withNoWordFullText($NoWordFullText)
    {
        $new = clone $this;
        $new->NoWordFullText = $NoWordFullText;

        return $new;
    }

    /**
     * @return bool
     */
    public function getNotDisplayInvalidatedCards()
    {
        return $this->NotDisplayInvalidatedCards;
    }

    /**
     * @param bool $NotDisplayInvalidatedCards
     * @return SearchCriteria
     */
    public function withNotDisplayInvalidatedCards($NotDisplayInvalidatedCards)
    {
        $new = clone $this;
        $new->NotDisplayInvalidatedCards = $NotDisplayInvalidatedCards;

        return $new;
    }

    /**
     * @return string
     */
    public function getOneWordFullText()
    {
        return $this->OneWordFullText;
    }

    /**
     * @param string $OneWordFullText
     * @return SearchCriteria
     */
    public function withOneWordFullText($OneWordFullText)
    {
        $new = clone $this;
        $new->OneWordFullText = $OneWordFullText;

        return $new;
    }

    /**
     * @return bool
     */
    public function getOnlyConnectedUser()
    {
        return $this->OnlyConnectedUser;
    }

    /**
     * @param bool $OnlyConnectedUser
     * @return SearchCriteria
     */
    public function withOnlyConnectedUser($OnlyConnectedUser)
    {
        $new = clone $this;
        $new->OnlyConnectedUser = $OnlyConnectedUser;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\FieldToOrderBy
     */
    public function getOrderByField()
    {
        return $this->OrderByField;
    }

    /**
     * @param \ArchiflowWSCard\Type\FieldToOrderBy $OrderByField
     * @return SearchCriteria
     */
    public function withOrderByField($OrderByField)
    {
        $new = clone $this;
        $new->OrderByField = $OrderByField;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\KeyOrderType
     */
    public function getOrderType()
    {
        return $this->OrderType;
    }

    /**
     * @param \ArchiflowWSCard\Type\KeyOrderType $OrderType
     * @return SearchCriteria
     */
    public function withOrderType($OrderType)
    {
        $new = clone $this;
        $new->OrderType = $OrderType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPluralSearchFullText()
    {
        return $this->PluralSearchFullText;
    }

    /**
     * @param bool $PluralSearchFullText
     * @return SearchCriteria
     */
    public function withPluralSearchFullText($PluralSearchFullText)
    {
        $new = clone $this;
        $new->PluralSearchFullText = $PluralSearchFullText;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RegisterOperation
     */
    public function getRegisterOperation()
    {
        return $this->RegisterOperation;
    }

    /**
     * @param \ArchiflowWSCard\Type\RegisterOperation $RegisterOperation
     * @return SearchCriteria
     */
    public function withRegisterOperation($RegisterOperation)
    {
        $new = clone $this;
        $new->RegisterOperation = $RegisterOperation;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchResult
     */
    public function getSearchResult()
    {
        return $this->SearchResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchResult $SearchResult
     * @return SearchCriteria
     */
    public function withSearchResult($SearchResult)
    {
        $new = clone $this;
        $new->SearchResult = $SearchResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchType
     */
    public function getSearchType()
    {
        return $this->SearchType;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchType $SearchType
     * @return SearchCriteria
     */
    public function withSearchType($SearchType)
    {
        $new = clone $this;
        $new->SearchType = $SearchType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSortDescending()
    {
        return $this->SortDescending;
    }

    /**
     * @param bool $SortDescending
     * @return SearchCriteria
     */
    public function withSortDescending($SortDescending)
    {
        $new = clone $this;
        $new->SortDescending = $SortDescending;

        return $new;
    }

    /**
     * @return string
     */
    public function getStringFullText()
    {
        return $this->StringFullText;
    }

    /**
     * @param string $StringFullText
     * @return SearchCriteria
     */
    public function withStringFullText($StringFullText)
    {
        $new = clone $this;
        $new->StringFullText = $StringFullText;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUseDefaultOptions()
    {
        return $this->UseDefaultOptions;
    }

    /**
     * @param bool $UseDefaultOptions
     * @return SearchCriteria
     */
    public function withUseDefaultOptions($UseDefaultOptions)
    {
        $new = clone $this;
        $new->UseDefaultOptions = $UseDefaultOptions;

        return $new;
    }

    /**
     * @return string
     */
    public function getWordsFullText()
    {
        return $this->WordsFullText;
    }

    /**
     * @param string $WordsFullText
     * @return SearchCriteria
     */
    public function withWordsFullText($WordsFullText)
    {
        $new = clone $this;
        $new->WordsFullText = $WordsFullText;

        return $new;
    }


}

