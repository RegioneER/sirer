<?php

namespace ArchiflowWSCard;

use ArchiflowWSCard\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class ArchiFlowCardClientClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\AttachDocument $parameters
     * @return ResultInterface|Type\AttachDocumentResponse
     * @throws SoapException
     */
    public function attachDocument(\ArchiflowWSCard\Type\AttachDocument $parameters) : \ArchiflowWSCard\Type\AttachDocumentResponse
    {
        return $this->call('AttachDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\AttachExternalDocument $parameters
     * @return ResultInterface|Type\AttachExternalDocumentResponse
     * @throws SoapException
     */
    public function attachExternalDocument(\ArchiflowWSCard\Type\AttachExternalDocument $parameters) : \ArchiflowWSCard\Type\AttachExternalDocumentResponse
    {
        return $this->call('AttachExternalDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\RemoveAttachment $parameters
     * @return ResultInterface|Type\RemoveAttachmentResponse
     * @throws SoapException
     */
    public function removeAttachment(\ArchiflowWSCard\Type\RemoveAttachment $parameters) : \ArchiflowWSCard\Type\RemoveAttachmentResponse
    {
        return $this->call('RemoveAttachment', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyAttachmentNote $parameters
     * @return ResultInterface|Type\ModifyAttachmentNoteResponse
     * @throws SoapException
     */
    public function modifyAttachmentNote(\ArchiflowWSCard\Type\ModifyAttachmentNote $parameters) : \ArchiflowWSCard\Type\ModifyAttachmentNoteResponse
    {
        return $this->call('ModifyAttachmentNote', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyExternalDocument $parameters
     * @return ResultInterface|Type\ModifyExternalDocumentResponse
     * @throws SoapException
     */
    public function modifyExternalDocument(\ArchiflowWSCard\Type\ModifyExternalDocument $parameters) : \ArchiflowWSCard\Type\ModifyExternalDocumentResponse
    {
        return $this->call('ModifyExternalDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardRight $parameters
     * @return ResultInterface|Type\GetCardRightResponse
     * @throws SoapException
     */
    public function getCardRight(\ArchiflowWSCard\Type\GetCardRight $parameters) : \ArchiflowWSCard\Type\GetCardRightResponse
    {
        return $this->call('GetCardRight', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardRights $parameters
     * @return ResultInterface|Type\GetCardRightsResponse
     * @throws SoapException
     */
    public function getCardRights(\ArchiflowWSCard\Type\GetCardRights $parameters) : \ArchiflowWSCard\Type\GetCardRightsResponse
    {
        return $this->call('GetCardRights', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardRightsConfig $parameters
     * @return ResultInterface|Type\GetCardRightsConfigResponse
     * @throws SoapException
     */
    public function getCardRightsConfig(\ArchiflowWSCard\Type\GetCardRightsConfig $parameters) : \ArchiflowWSCard\Type\GetCardRightsConfigResponse
    {
        return $this->call('GetCardRightsConfig', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardVisibility $parameters
     * @return ResultInterface|Type\GetCardVisibilityResponse
     * @throws SoapException
     */
    public function getCardVisibility(\ArchiflowWSCard\Type\GetCardVisibility $parameters) : \ArchiflowWSCard\Type\GetCardVisibilityResponse
    {
        return $this->call('GetCardVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardVisibility2 $parameters
     * @return ResultInterface|Type\GetCardVisibility2Response
     * @throws SoapException
     */
    public function getCardVisibility2(\ArchiflowWSCard\Type\GetCardVisibility2 $parameters) : \ArchiflowWSCard\Type\GetCardVisibility2Response
    {
        return $this->call('GetCardVisibility2', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertListItem $parameters
     * @return ResultInterface|Type\InsertListItemResponse
     * @throws SoapException
     */
    public function insertListItem(\ArchiflowWSCard\Type\InsertListItem $parameters) : \ArchiflowWSCard\Type\InsertListItemResponse
    {
        return $this->call('InsertListItem', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertListItemAdditives $parameters
     * @return ResultInterface|Type\InsertListItemAdditivesResponse
     * @throws SoapException
     */
    public function insertListItemAdditives(\ArchiflowWSCard\Type\InsertListItemAdditives $parameters) : \ArchiflowWSCard\Type\InsertListItemAdditivesResponse
    {
        return $this->call('InsertListItemAdditives', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyListItem $parameters
     * @return ResultInterface|Type\ModifyListItemResponse
     * @throws SoapException
     */
    public function modifyListItem(\ArchiflowWSCard\Type\ModifyListItem $parameters) : \ArchiflowWSCard\Type\ModifyListItemResponse
    {
        return $this->call('ModifyListItem', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteListItem $parameters
     * @return ResultInterface|Type\DeleteListItemResponse
     * @throws SoapException
     */
    public function deleteListItem(\ArchiflowWSCard\Type\DeleteListItem $parameters) : \ArchiflowWSCard\Type\DeleteListItemResponse
    {
        return $this->call('DeleteListItem', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetExistingCardVisibility $parameters
     * @return ResultInterface|Type\GetExistingCardVisibilityResponse
     * @throws SoapException
     */
    public function getExistingCardVisibility(\ArchiflowWSCard\Type\GetExistingCardVisibility $parameters) : \ArchiflowWSCard\Type\GetExistingCardVisibilityResponse
    {
        return $this->call('GetExistingCardVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetExistingCardVisibilityCC $parameters
     * @return ResultInterface|Type\GetExistingCardVisibilityCCResponse
     * @throws SoapException
     */
    public function getExistingCardVisibilityCC(\ArchiflowWSCard\Type\GetExistingCardVisibilityCC $parameters) : \ArchiflowWSCard\Type\GetExistingCardVisibilityCCResponse
    {
        return $this->call('GetExistingCardVisibilityCC', $parameters);
    }

    /**
     * @param RequestInterface|Type\BuildFileDigest $parameters
     * @return ResultInterface|Type\BuildFileDigestResponse
     * @throws SoapException
     */
    public function buildFileDigest(\ArchiflowWSCard\Type\BuildFileDigest $parameters) : \ArchiflowWSCard\Type\BuildFileDigestResponse
    {
        return $this->call('BuildFileDigest', $parameters);
    }

    /**
     * @param RequestInterface|Type\SignFileDigest $parameters
     * @return ResultInterface|Type\SignFileDigestResponse
     * @throws SoapException
     */
    public function signFileDigest(\ArchiflowWSCard\Type\SignFileDigest $parameters) : \ArchiflowWSCard\Type\SignFileDigestResponse
    {
        return $this->call('SignFileDigest', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreateTimeStampedDataFileDigest $parameters
     * @return ResultInterface|Type\CreateTimeStampedDataFileDigestResponse
     * @throws SoapException
     */
    public function createTimeStampedDataFileDigest(\ArchiflowWSCard\Type\CreateTimeStampedDataFileDigest $parameters) : \ArchiflowWSCard\Type\CreateTimeStampedDataFileDigestResponse
    {
        return $this->call('CreateTimeStampedDataFileDigest', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardKeyVersions $parameters
     * @return ResultInterface|Type\GetCardKeyVersionsResponse
     * @throws SoapException
     */
    public function getCardKeyVersions(\ArchiflowWSCard\Type\GetCardKeyVersions $parameters) : \ArchiflowWSCard\Type\GetCardKeyVersionsResponse
    {
        return $this->call('GetCardKeyVersions', $parameters);
    }

    /**
     * @param RequestInterface|Type\OrderArrayProgID $parameters
     * @return ResultInterface|Type\OrderArrayProgIDResponse
     * @throws SoapException
     */
    public function orderArrayProgID(\ArchiflowWSCard\Type\OrderArrayProgID $parameters) : \ArchiflowWSCard\Type\OrderArrayProgIDResponse
    {
        return $this->call('OrderArrayProgID', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetStatus $parameters
     * @return ResultInterface|Type\GetStatusResponse
     * @throws SoapException
     */
    public function getStatus(\ArchiflowWSCard\Type\GetStatus $parameters) : \ArchiflowWSCard\Type\GetStatusResponse
    {
        return $this->call('GetStatus', $parameters);
    }

    /**
     * @param RequestInterface|Type\CheckIn $parameters
     * @return ResultInterface|Type\CheckInResponse
     * @throws SoapException
     */
    public function checkIn(\ArchiflowWSCard\Type\CheckIn $parameters) : \ArchiflowWSCard\Type\CheckInResponse
    {
        return $this->call('CheckIn', $parameters);
    }

    /**
     * @param RequestInterface|Type\CheckOut $parameters
     * @return ResultInterface|Type\CheckOutResponse
     * @throws SoapException
     */
    public function checkOut(\ArchiflowWSCard\Type\CheckOut $parameters) : \ArchiflowWSCard\Type\CheckOutResponse
    {
        return $this->call('CheckOut', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyAddInEmailMapping $parameters
     * @return ResultInterface|Type\ModifyAddInEmailMappingResponse
     * @throws SoapException
     */
    public function modifyAddInEmailMapping(\ArchiflowWSCard\Type\ModifyAddInEmailMapping $parameters) : \ArchiflowWSCard\Type\ModifyAddInEmailMappingResponse
    {
        return $this->call('ModifyAddInEmailMapping', $parameters);
    }

    /**
     * @param RequestInterface|Type\DigestAttachment $parameters
     * @return ResultInterface|Type\DigestAttachmentResponse
     * @throws SoapException
     */
    public function digestAttachment(\ArchiflowWSCard\Type\DigestAttachment $parameters) : \ArchiflowWSCard\Type\DigestAttachmentResponse
    {
        return $this->call('DigestAttachment', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCardExtended $parameters
     * @return ResultInterface|Type\SendCardExtendedResponse
     * @throws SoapException
     */
    public function sendCardExtended(\ArchiflowWSCard\Type\SendCardExtended $parameters) : \ArchiflowWSCard\Type\SendCardExtendedResponse
    {
        return $this->call('SendCardExtended', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreateWebLink $parameters
     * @return ResultInterface|Type\CreateWebLinkResponse
     * @throws SoapException
     */
    public function createWebLink(\ArchiflowWSCard\Type\CreateWebLink $parameters) : \ArchiflowWSCard\Type\CreateWebLinkResponse
    {
        return $this->call('CreateWebLink', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreateWebLinks $parameters
     * @return ResultInterface|Type\CreateWebLinksResponse
     * @throws SoapException
     */
    public function createWebLinks(\ArchiflowWSCard\Type\CreateWebLinks $parameters) : \ArchiflowWSCard\Type\CreateWebLinksResponse
    {
        return $this->call('CreateWebLinks', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetRegisterRecords $parameters
     * @return ResultInterface|Type\GetRegisterRecordsResponse
     * @throws SoapException
     */
    public function getRegisterRecords(\ArchiflowWSCard\Type\GetRegisterRecords $parameters) : \ArchiflowWSCard\Type\GetRegisterRecordsResponse
    {
        return $this->call('GetRegisterRecords', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetSearchModels $parameters
     * @return ResultInterface|Type\GetSearchModelsResponse
     * @throws SoapException
     */
    public function getSearchModels(\ArchiflowWSCard\Type\GetSearchModels $parameters) : \ArchiflowWSCard\Type\GetSearchModelsResponse
    {
        return $this->call('GetSearchModels', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetSearchModel $parameters
     * @return ResultInterface|Type\GetSearchModelResponse
     * @throws SoapException
     */
    public function getSearchModel(\ArchiflowWSCard\Type\GetSearchModel $parameters) : \ArchiflowWSCard\Type\GetSearchModelResponse
    {
        return $this->call('GetSearchModel', $parameters);
    }

    /**
     * @param RequestInterface|Type\RetrieveCardsFromSearchModel $parameters
     * @return ResultInterface|Type\RetrieveCardsFromSearchModelResponse
     * @throws SoapException
     */
    public function retrieveCardsFromSearchModel(\ArchiflowWSCard\Type\RetrieveCardsFromSearchModel $parameters) : \ArchiflowWSCard\Type\RetrieveCardsFromSearchModelResponse
    {
        return $this->call('RetrieveCardsFromSearchModel', $parameters);
    }

    /**
     * @param RequestInterface|Type\RetrieveCardsFromSearchModel2 $parameters
     * @return ResultInterface|Type\RetrieveCardsFromSearchModel2Response
     * @throws SoapException
     */
    public function retrieveCardsFromSearchModel2(\ArchiflowWSCard\Type\RetrieveCardsFromSearchModel2 $parameters) : \ArchiflowWSCard\Type\RetrieveCardsFromSearchModel2Response
    {
        return $this->call('RetrieveCardsFromSearchModel2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocTypesSameFields $parameters
     * @return ResultInterface|Type\GetDocTypesSameFieldsResponse
     * @throws SoapException
     */
    public function getDocTypesSameFields(\ArchiflowWSCard\Type\GetDocTypesSameFields $parameters) : \ArchiflowWSCard\Type\GetDocTypesSameFieldsResponse
    {
        return $this->call('GetDocTypesSameFields', $parameters);
    }

    /**
     * @param RequestInterface|Type\SaveSearchModel $parameters
     * @return ResultInterface|Type\SaveSearchModelResponse
     * @throws SoapException
     */
    public function saveSearchModel(\ArchiflowWSCard\Type\SaveSearchModel $parameters) : \ArchiflowWSCard\Type\SaveSearchModelResponse
    {
        return $this->call('SaveSearchModel', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteSearchModel $parameters
     * @return ResultInterface|Type\DeleteSearchModelResponse
     * @throws SoapException
     */
    public function deleteSearchModel(\ArchiflowWSCard\Type\DeleteSearchModel $parameters) : \ArchiflowWSCard\Type\DeleteSearchModelResponse
    {
        return $this->call('DeleteSearchModel', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetSearchModelsVisibility $parameters
     * @return ResultInterface|Type\GetSearchModelsVisibilityResponse
     * @throws SoapException
     */
    public function getSearchModelsVisibility(\ArchiflowWSCard\Type\GetSearchModelsVisibility $parameters) : \ArchiflowWSCard\Type\GetSearchModelsVisibilityResponse
    {
        return $this->call('GetSearchModelsVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardHistoryPerPage $parameters
     * @return ResultInterface|Type\GetCardHistoryPerPageResponse
     * @throws SoapException
     */
    public function getCardHistoryPerPage(\ArchiflowWSCard\Type\GetCardHistoryPerPage $parameters) : \ArchiflowWSCard\Type\GetCardHistoryPerPageResponse
    {
        return $this->call('GetCardHistoryPerPage', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocumentInChunk $parameters
     * @return ResultInterface|Type\GetCardDocumentInChunkResponse
     * @throws SoapException
     */
    public function getCardDocumentInChunk(\ArchiflowWSCard\Type\GetCardDocumentInChunk $parameters) : \ArchiflowWSCard\Type\GetCardDocumentInChunkResponse
    {
        return $this->call('GetCardDocumentInChunk', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachmentInChunk $parameters
     * @return ResultInterface|Type\GetCardAttachmentInChunkResponse
     * @throws SoapException
     */
    public function getCardAttachmentInChunk(\ArchiflowWSCard\Type\GetCardAttachmentInChunk $parameters) : \ArchiflowWSCard\Type\GetCardAttachmentInChunkResponse
    {
        return $this->call('GetCardAttachmentInChunk', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardFromSapDocId $parameters
     * @return ResultInterface|Type\GetCardFromSapDocIdResponse
     * @throws SoapException
     */
    public function getCardFromSapDocId(\ArchiflowWSCard\Type\GetCardFromSapDocId $parameters) : \ArchiflowWSCard\Type\GetCardFromSapDocIdResponse
    {
        return $this->call('GetCardFromSapDocId', $parameters);
    }

    /**
     * @param RequestInterface|Type\SAPRegisterInvoice $parameters
     * @return ResultInterface|Type\SAPRegisterInvoiceResponse
     * @throws SoapException
     */
    public function sAP_RegisterInvoice(\ArchiflowWSCard\Type\SAPRegisterInvoice $parameters) : \ArchiflowWSCard\Type\SAPRegisterInvoiceResponse
    {
        return $this->call('SAP_RegisterInvoice', $parameters);
    }

    /**
     * @param RequestInterface|Type\SAPRegisterInvoiceError $parameters
     * @return ResultInterface|Type\SAPRegisterInvoiceErrorResponse
     * @throws SoapException
     */
    public function sAP_RegisterInvoiceError(\ArchiflowWSCard\Type\SAPRegisterInvoiceError $parameters) : \ArchiflowWSCard\Type\SAPRegisterInvoiceErrorResponse
    {
        return $this->call('SAP_RegisterInvoiceError', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCardBarcodeToSap $parameters
     * @return ResultInterface|Type\SendCardBarcodeToSapResponse
     * @throws SoapException
     */
    public function sendCardBarcodeToSap(\ArchiflowWSCard\Type\SendCardBarcodeToSap $parameters) : \ArchiflowWSCard\Type\SendCardBarcodeToSapResponse
    {
        return $this->call('SendCardBarcodeToSap', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardValidation $parameters
     * @return ResultInterface|Type\SetCardValidationResponse
     * @throws SoapException
     */
    public function setCardValidation(\ArchiflowWSCard\Type\SetCardValidation $parameters) : \ArchiflowWSCard\Type\SetCardValidationResponse
    {
        return $this->call('SetCardValidation', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetListItemsByParam $parameters
     * @return ResultInterface|Type\GetListItemsByParamResponse
     * @throws SoapException
     */
    public function getListItemsByParam(\ArchiflowWSCard\Type\GetListItemsByParam $parameters) : \ArchiflowWSCard\Type\GetListItemsByParamResponse
    {
        return $this->call('GetListItemsByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\DocumentDigest $parameters
     * @return ResultInterface|Type\DocumentDigestResponse
     * @throws SoapException
     */
    public function documentDigest(\ArchiflowWSCard\Type\DocumentDigest $parameters) : \ArchiflowWSCard\Type\DocumentDigestResponse
    {
        return $this->call('DocumentDigest', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetFieldVersion $parameters
     * @return ResultInterface|Type\GetFieldVersionResponse
     * @throws SoapException
     */
    public function getFieldVersion(\ArchiflowWSCard\Type\GetFieldVersion $parameters) : \ArchiflowWSCard\Type\GetFieldVersionResponse
    {
        return $this->call('GetFieldVersion', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardFolders $parameters
     * @return ResultInterface|Type\GetCardFoldersResponse
     * @throws SoapException
     */
    public function getCardFolders(\ArchiflowWSCard\Type\GetCardFolders $parameters) : \ArchiflowWSCard\Type\GetCardFoldersResponse
    {
        return $this->call('GetCardFolders', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardOperationsAllowed $parameters
     * @return ResultInterface|Type\GetCardOperationsAllowedResponse
     * @throws SoapException
     */
    public function getCardOperationsAllowed(\ArchiflowWSCard\Type\GetCardOperationsAllowed $parameters) : \ArchiflowWSCard\Type\GetCardOperationsAllowedResponse
    {
        return $this->call('GetCardOperationsAllowed', $parameters);
    }

    /**
     * @param RequestInterface|Type\MoveCardDocAndAttachments $parameters
     * @return ResultInterface|Type\MoveCardDocAndAttachmentsResponse
     * @throws SoapException
     */
    public function moveCardDocAndAttachments(\ArchiflowWSCard\Type\MoveCardDocAndAttachments $parameters) : \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsResponse
    {
        return $this->call('MoveCardDocAndAttachments', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetGraphometricSignatureTemplate $parameters
     * @return ResultInterface|Type\GetGraphometricSignatureTemplateResponse
     * @throws SoapException
     */
    public function getGraphometricSignatureTemplate(\ArchiflowWSCard\Type\GetGraphometricSignatureTemplate $parameters) : \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateResponse
    {
        return $this->call('GetGraphometricSignatureTemplate', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardDocumentLock $parameters
     * @return ResultInterface|Type\SetCardDocumentLockResponse
     * @throws SoapException
     */
    public function setCardDocumentLock(\ArchiflowWSCard\Type\SetCardDocumentLock $parameters) : \ArchiflowWSCard\Type\SetCardDocumentLockResponse
    {
        return $this->call('SetCardDocumentLock', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardsVisibility $parameters
     * @return ResultInterface|Type\GetCardsVisibilityResponse
     * @throws SoapException
     */
    public function getCardsVisibility(\ArchiflowWSCard\Type\GetCardsVisibility $parameters) : \ArchiflowWSCard\Type\GetCardsVisibilityResponse
    {
        return $this->call('GetCardsVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCards $parameters
     * @return ResultInterface|Type\SendCardsResponse
     * @throws SoapException
     */
    public function sendCards(\ArchiflowWSCard\Type\SendCards $parameters) : \ArchiflowWSCard\Type\SendCardsResponse
    {
        return $this->call('SendCards', $parameters);
    }

    /**
     * @param RequestInterface|Type\ExportCardsToCsv $parameters
     * @return ResultInterface|Type\ExportCardsToCsvResponse
     * @throws SoapException
     */
    public function exportCardsToCsv(\ArchiflowWSCard\Type\ExportCardsToCsv $parameters) : \ArchiflowWSCard\Type\ExportCardsToCsvResponse
    {
        return $this->call('ExportCardsToCsv', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardValidationByParam $parameters
     * @return ResultInterface|Type\SetCardValidationByParamResponse
     * @throws SoapException
     */
    public function setCardValidationByParam(\ArchiflowWSCard\Type\SetCardValidationByParam $parameters) : \ArchiflowWSCard\Type\SetCardValidationByParamResponse
    {
        return $this->call('SetCardValidationByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\MainDocumentToPDF $parameters
     * @return ResultInterface|Type\MainDocumentToPDFResponse
     * @throws SoapException
     */
    public function mainDocumentToPDF(\ArchiflowWSCard\Type\MainDocumentToPDF $parameters) : \ArchiflowWSCard\Type\MainDocumentToPDFResponse
    {
        return $this->call('MainDocumentToPDF', $parameters);
    }

    /**
     * @param RequestInterface|Type\ResetCard $parameters
     * @return ResultInterface|Type\ResetCardResponse
     * @throws SoapException
     */
    public function resetCard(\ArchiflowWSCard\Type\ResetCard $parameters) : \ArchiflowWSCard\Type\ResetCardResponse
    {
        return $this->call('ResetCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\ConsolidateCard $parameters
     * @return ResultInterface|Type\ConsolidateCardResponse
     * @throws SoapException
     */
    public function consolidateCard(\ArchiflowWSCard\Type\ConsolidateCard $parameters) : \ArchiflowWSCard\Type\ConsolidateCardResponse
    {
        return $this->call('ConsolidateCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\ProtocolCard $parameters
     * @return ResultInterface|Type\ProtocolCardResponse
     * @throws SoapException
     */
    public function protocolCard(\ArchiflowWSCard\Type\ProtocolCard $parameters) : \ArchiflowWSCard\Type\ProtocolCardResponse
    {
        return $this->call('ProtocolCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCardFromCardByParam $parameters
     * @return ResultInterface|Type\InsertCardFromCardByParamResponse
     * @throws SoapException
     */
    public function insertCardFromCardByParam(\ArchiflowWSCard\Type\InsertCardFromCardByParam $parameters) : \ArchiflowWSCard\Type\InsertCardFromCardByParamResponse
    {
        return $this->call('InsertCardFromCardByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\SaveDocumentVersion $parameters
     * @return ResultInterface|Type\SaveDocumentVersionResponse
     * @throws SoapException
     */
    public function saveDocumentVersion(\ArchiflowWSCard\Type\SaveDocumentVersion $parameters) : \ArchiflowWSCard\Type\SaveDocumentVersionResponse
    {
        return $this->call('SaveDocumentVersion', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreateZipCardsData $parameters
     * @return ResultInterface|Type\CreateZipCardsDataResponse
     * @throws SoapException
     */
    public function createZipCardsData(\ArchiflowWSCard\Type\CreateZipCardsData $parameters) : \ArchiflowWSCard\Type\CreateZipCardsDataResponse
    {
        return $this->call('CreateZipCardsData', $parameters);
    }

    /**
     * @param RequestInterface|Type\CheckCreateZipCardsData $parameters
     * @return ResultInterface|Type\CheckCreateZipCardsDataResponse
     * @throws SoapException
     */
    public function checkCreateZipCardsData(\ArchiflowWSCard\Type\CheckCreateZipCardsData $parameters) : \ArchiflowWSCard\Type\CheckCreateZipCardsDataResponse
    {
        return $this->call('CheckCreateZipCardsData', $parameters);
    }

    /**
     * @param RequestInterface|Type\CheckPrivacyVisibility $parameters
     * @return ResultInterface|Type\CheckPrivacyVisibilityResponse
     * @throws SoapException
     */
    public function checkPrivacyVisibility(\ArchiflowWSCard\Type\CheckPrivacyVisibility $parameters) : \ArchiflowWSCard\Type\CheckPrivacyVisibilityResponse
    {
        return $this->call('CheckPrivacyVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\LoadAutoCollationTemplates $parameters
     * @return ResultInterface|Type\LoadAutoCollationTemplatesResponse
     * @throws SoapException
     */
    public function loadAutoCollationTemplates(\ArchiflowWSCard\Type\LoadAutoCollationTemplates $parameters) : \ArchiflowWSCard\Type\LoadAutoCollationTemplatesResponse
    {
        return $this->call('LoadAutoCollationTemplates', $parameters);
    }

    /**
     * @param RequestInterface|Type\FoldersForAutoCollate $parameters
     * @return ResultInterface|Type\FoldersForAutoCollateResponse
     * @throws SoapException
     */
    public function foldersForAutoCollate(\ArchiflowWSCard\Type\FoldersForAutoCollate $parameters) : \ArchiflowWSCard\Type\FoldersForAutoCollateResponse
    {
        return $this->call('FoldersForAutoCollate', $parameters);
    }

    /**
     * @param RequestInterface|Type\AutoCollate $parameters
     * @return ResultInterface|Type\AutoCollateResponse
     * @throws SoapException
     */
    public function autoCollate(\ArchiflowWSCard\Type\AutoCollate $parameters) : \ArchiflowWSCard\Type\AutoCollateResponse
    {
        return $this->call('AutoCollate', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetContacts $parameters
     * @return ResultInterface|Type\GetContactsResponse
     * @throws SoapException
     */
    public function getContacts(\ArchiflowWSCard\Type\GetContacts $parameters) : \ArchiflowWSCard\Type\GetContactsResponse
    {
        return $this->call('GetContacts', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetContacts2 $parameters
     * @return ResultInterface|Type\GetContacts2Response
     * @throws SoapException
     */
    public function getContacts2(\ArchiflowWSCard\Type\GetContacts2 $parameters) : \ArchiflowWSCard\Type\GetContacts2Response
    {
        return $this->call('GetContacts2', $parameters);
    }

    /**
     * @param RequestInterface|Type\AddContactsToCard $parameters
     * @return ResultInterface|Type\AddContactsToCardResponse
     * @throws SoapException
     */
    public function addContactsToCard(\ArchiflowWSCard\Type\AddContactsToCard $parameters) : \ArchiflowWSCard\Type\AddContactsToCardResponse
    {
        return $this->call('AddContactsToCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\AddContactsToCard2 $parameters
     * @return ResultInterface|Type\AddContactsToCard2Response
     * @throws SoapException
     */
    public function addContactsToCard2(\ArchiflowWSCard\Type\AddContactsToCard2 $parameters) : \ArchiflowWSCard\Type\AddContactsToCard2Response
    {
        return $this->call('AddContactsToCard2', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteContacts $parameters
     * @return ResultInterface|Type\DeleteContactsResponse
     * @throws SoapException
     */
    public function deleteContacts(\ArchiflowWSCard\Type\DeleteContacts $parameters) : \ArchiflowWSCard\Type\DeleteContactsResponse
    {
        return $this->call('DeleteContacts', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetAddressesContacts $parameters
     * @return ResultInterface|Type\GetAddressesContactsResponse
     * @throws SoapException
     */
    public function getAddressesContacts(\ArchiflowWSCard\Type\GetAddressesContacts $parameters) : \ArchiflowWSCard\Type\GetAddressesContactsResponse
    {
        return $this->call('GetAddressesContacts', $parameters);
    }

    /**
     * @param RequestInterface|Type\RemoveVisibility $parameters
     * @return ResultInterface|Type\RemoveVisibilityResponse
     * @throws SoapException
     */
    public function removeVisibility(\ArchiflowWSCard\Type\RemoveVisibility $parameters) : \ArchiflowWSCard\Type\RemoveVisibilityResponse
    {
        return $this->call('RemoveVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\RemoveVisibilityByParam $parameters
     * @return ResultInterface|Type\RemoveVisibilityByParamResponse
     * @throws SoapException
     */
    public function removeVisibilityByParam(\ArchiflowWSCard\Type\RemoveVisibilityByParam $parameters) : \ArchiflowWSCard\Type\RemoveVisibilityByParamResponse
    {
        return $this->call('RemoveVisibilityByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\RemoveVisibilityById $parameters
     * @return ResultInterface|Type\RemoveVisibilityByIdResponse
     * @throws SoapException
     */
    public function removeVisibilityById(\ArchiflowWSCard\Type\RemoveVisibilityById $parameters) : \ArchiflowWSCard\Type\RemoveVisibilityByIdResponse
    {
        return $this->call('RemoveVisibilityById', $parameters);
    }

    /**
     * @param RequestInterface|Type\ChangeVisibilityType $parameters
     * @return ResultInterface|Type\ChangeVisibilityTypeResponse
     * @throws SoapException
     */
    public function changeVisibilityType(\ArchiflowWSCard\Type\ChangeVisibilityType $parameters) : \ArchiflowWSCard\Type\ChangeVisibilityTypeResponse
    {
        return $this->call('ChangeVisibilityType', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypesInSearch $parameters
     * @return ResultInterface|Type\GetDocumentTypesInSearchResponse
     * @throws SoapException
     */
    public function getDocumentTypesInSearch(\ArchiflowWSCard\Type\GetDocumentTypesInSearch $parameters) : \ArchiflowWSCard\Type\GetDocumentTypesInSearchResponse
    {
        return $this->call('GetDocumentTypesInSearch', $parameters);
    }

    /**
     * @param RequestInterface|Type\CheckUserRightToCreateCompliantCopy $parameters
     * @return ResultInterface|Type\CheckUserRightToCreateCompliantCopyResponse
     * @throws SoapException
     */
    public function checkUserRightToCreateCompliantCopy(\ArchiflowWSCard\Type\CheckUserRightToCreateCompliantCopy $parameters) : \ArchiflowWSCard\Type\CheckUserRightToCreateCompliantCopyResponse
    {
        return $this->call('CheckUserRightToCreateCompliantCopy', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocComplianceCertificationModels $parameters
     * @return ResultInterface|Type\GetDocComplianceCertificationModelsResponse
     * @throws SoapException
     */
    public function getDocComplianceCertificationModels(\ArchiflowWSCard\Type\GetDocComplianceCertificationModels $parameters) : \ArchiflowWSCard\Type\GetDocComplianceCertificationModelsResponse
    {
        return $this->call('GetDocComplianceCertificationModels', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDesktopCards $parameters
     * @return ResultInterface|Type\GetDesktopCardsResponse
     * @throws SoapException
     */
    public function getDesktopCards(\ArchiflowWSCard\Type\GetDesktopCards $parameters) : \ArchiflowWSCard\Type\GetDesktopCardsResponse
    {
        return $this->call('GetDesktopCards', $parameters);
    }

    /**
     * @param RequestInterface|Type\SearchCards $parameters
     * @return ResultInterface|Type\SearchCardsResponse
     * @throws SoapException
     */
    public function searchCards(\ArchiflowWSCard\Type\SearchCards $parameters) : \ArchiflowWSCard\Type\SearchCardsResponse
    {
        return $this->call('SearchCards', $parameters);
    }

    /**
     * @param RequestInterface|Type\SearchCards2 $parameters
     * @return ResultInterface|Type\SearchCards2Response
     * @throws SoapException
     */
    public function searchCards2(\ArchiflowWSCard\Type\SearchCards2 $parameters) : \ArchiflowWSCard\Type\SearchCards2Response
    {
        return $this->call('SearchCards2', $parameters);
    }

    /**
     * @param RequestInterface|Type\SearchCardsGrouping $parameters
     * @return ResultInterface|Type\SearchCardsGroupingResponse
     * @throws SoapException
     */
    public function searchCardsGrouping(\ArchiflowWSCard\Type\SearchCardsGrouping $parameters) : \ArchiflowWSCard\Type\SearchCardsGroupingResponse
    {
        return $this->call('SearchCardsGrouping', $parameters);
    }

    /**
     * @param RequestInterface|Type\RetrieveCards $parameters
     * @return ResultInterface|Type\RetrieveCardsResponse
     * @throws SoapException
     */
    public function retrieveCards(\ArchiflowWSCard\Type\RetrieveCards $parameters) : \ArchiflowWSCard\Type\RetrieveCardsResponse
    {
        return $this->call('RetrieveCards', $parameters);
    }

    /**
     * @param RequestInterface|Type\RetrieveCards2 $parameters
     * @return ResultInterface|Type\RetrieveCards2Response
     * @throws SoapException
     */
    public function retrieveCards2(\ArchiflowWSCard\Type\RetrieveCards2 $parameters) : \ArchiflowWSCard\Type\RetrieveCards2Response
    {
        return $this->call('RetrieveCards2', $parameters);
    }

    /**
     * @param RequestInterface|Type\RetrieveCardsByParam $parameters
     * @return ResultInterface|Type\RetrieveCardsByParamResponse
     * @throws SoapException
     */
    public function retrieveCardsByParam(\ArchiflowWSCard\Type\RetrieveCardsByParam $parameters) : \ArchiflowWSCard\Type\RetrieveCardsByParamResponse
    {
        return $this->call('RetrieveCardsByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetArchive $parameters
     * @return ResultInterface|Type\GetArchiveResponse
     * @throws SoapException
     */
    public function getArchive(\ArchiflowWSCard\Type\GetArchive $parameters) : \ArchiflowWSCard\Type\GetArchiveResponse
    {
        return $this->call('GetArchive', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetArchives $parameters
     * @return ResultInterface|Type\GetArchivesResponse
     * @throws SoapException
     */
    public function getArchives(\ArchiflowWSCard\Type\GetArchives $parameters) : \ArchiflowWSCard\Type\GetArchivesResponse
    {
        return $this->call('GetArchives', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentType $parameters
     * @return ResultInterface|Type\GetDocumentTypeResponse
     * @throws SoapException
     */
    public function getDocumentType(\ArchiflowWSCard\Type\GetDocumentType $parameters) : \ArchiflowWSCard\Type\GetDocumentTypeResponse
    {
        return $this->call('GetDocumentType', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentType2 $parameters
     * @return ResultInterface|Type\GetDocumentType2Response
     * @throws SoapException
     */
    public function getDocumentType2(\ArchiflowWSCard\Type\GetDocumentType2 $parameters) : \ArchiflowWSCard\Type\GetDocumentType2Response
    {
        return $this->call('GetDocumentType2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypes $parameters
     * @return ResultInterface|Type\GetDocumentTypesResponse
     * @throws SoapException
     */
    public function getDocumentTypes(\ArchiflowWSCard\Type\GetDocumentTypes $parameters) : \ArchiflowWSCard\Type\GetDocumentTypesResponse
    {
        return $this->call('GetDocumentTypes', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypesByParam $parameters
     * @return ResultInterface|Type\GetDocumentTypesByParamResponse
     * @throws SoapException
     */
    public function getDocumentTypesByParam(\ArchiflowWSCard\Type\GetDocumentTypesByParam $parameters) : \ArchiflowWSCard\Type\GetDocumentTypesByParamResponse
    {
        return $this->call('GetDocumentTypesByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypes2 $parameters
     * @return ResultInterface|Type\GetDocumentTypes2Response
     * @throws SoapException
     */
    public function getDocumentTypes2(\ArchiflowWSCard\Type\GetDocumentTypes2 $parameters) : \ArchiflowWSCard\Type\GetDocumentTypes2Response
    {
        return $this->call('GetDocumentTypes2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypesFromArchives $parameters
     * @return ResultInterface|Type\GetDocumentTypesFromArchivesResponse
     * @throws SoapException
     */
    public function getDocumentTypesFromArchives(\ArchiflowWSCard\Type\GetDocumentTypesFromArchives $parameters) : \ArchiflowWSCard\Type\GetDocumentTypesFromArchivesResponse
    {
        return $this->call('GetDocumentTypesFromArchives', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentTypeProtocolType $parameters
     * @return ResultInterface|Type\GetDocumentTypeProtocolTypeResponse
     * @throws SoapException
     */
    public function getDocumentTypeProtocolType(\ArchiflowWSCard\Type\GetDocumentTypeProtocolType $parameters) : \ArchiflowWSCard\Type\GetDocumentTypeProtocolTypeResponse
    {
        return $this->call('GetDocumentTypeProtocolType', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCard $parameters
     * @return ResultInterface|Type\GetCardResponse
     * @throws SoapException
     */
    public function getCard(\ArchiflowWSCard\Type\GetCard $parameters) : \ArchiflowWSCard\Type\GetCardResponse
    {
        return $this->call('GetCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCard2 $parameters
     * @return ResultInterface|Type\GetCard2Response
     * @throws SoapException
     */
    public function getCard2(\ArchiflowWSCard\Type\GetCard2 $parameters) : \ArchiflowWSCard\Type\GetCard2Response
    {
        return $this->call('GetCard2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardByParam $parameters
     * @return ResultInterface|Type\GetCardByParamResponse
     * @throws SoapException
     */
    public function getCardByParam(\ArchiflowWSCard\Type\GetCardByParam $parameters) : \ArchiflowWSCard\Type\GetCardByParamResponse
    {
        return $this->call('GetCardByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardHasData $parameters
     * @return ResultInterface|Type\GetCardHasDataResponse
     * @throws SoapException
     */
    public function getCardHasData(\ArchiflowWSCard\Type\GetCardHasData $parameters) : \ArchiflowWSCard\Type\GetCardHasDataResponse
    {
        return $this->call('GetCardHasData', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardFromReference $parameters
     * @return ResultInterface|Type\GetCardFromReferenceResponse
     * @throws SoapException
     */
    public function getCardFromReference(\ArchiflowWSCard\Type\GetCardFromReference $parameters) : \ArchiflowWSCard\Type\GetCardFromReferenceResponse
    {
        return $this->call('GetCardFromReference', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardFromReference2 $parameters
     * @return ResultInterface|Type\GetCardFromReference2Response
     * @throws SoapException
     */
    public function getCardFromReference2(\ArchiflowWSCard\Type\GetCardFromReference2 $parameters) : \ArchiflowWSCard\Type\GetCardFromReference2Response
    {
        return $this->call('GetCardFromReference2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCards $parameters
     * @return ResultInterface|Type\GetCardsResponse
     * @throws SoapException
     */
    public function getCards(\ArchiflowWSCard\Type\GetCards $parameters) : \ArchiflowWSCard\Type\GetCardsResponse
    {
        return $this->call('GetCards', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCards2 $parameters
     * @return ResultInterface|Type\GetCards2Response
     * @throws SoapException
     */
    public function getCards2(\ArchiflowWSCard\Type\GetCards2 $parameters) : \ArchiflowWSCard\Type\GetCards2Response
    {
        return $this->call('GetCards2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardsByParam $parameters
     * @return ResultInterface|Type\GetCardsByParamResponse
     * @throws SoapException
     */
    public function getCardsByParam(\ArchiflowWSCard\Type\GetCardsByParam $parameters) : \ArchiflowWSCard\Type\GetCardsByParamResponse
    {
        return $this->call('GetCardsByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardBundle $parameters
     * @return ResultInterface|Type\GetCardBundleResponse
     * @throws SoapException
     */
    public function getCardBundle(\ArchiflowWSCard\Type\GetCardBundle $parameters) : \ArchiflowWSCard\Type\GetCardBundleResponse
    {
        return $this->call('GetCardBundle', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardBundle2 $parameters
     * @return ResultInterface|Type\GetCardBundle2Response
     * @throws SoapException
     */
    public function getCardBundle2(\ArchiflowWSCard\Type\GetCardBundle2 $parameters) : \ArchiflowWSCard\Type\GetCardBundle2Response
    {
        return $this->call('GetCardBundle2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocument $parameters
     * @return ResultInterface|Type\GetCardDocumentResponse
     * @throws SoapException
     */
    public function getCardDocument(\ArchiflowWSCard\Type\GetCardDocument $parameters) : \ArchiflowWSCard\Type\GetCardDocumentResponse
    {
        return $this->call('GetCardDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocument2 $parameters
     * @return ResultInterface|Type\GetCardDocument2Response
     * @throws SoapException
     */
    public function getCardDocument2(\ArchiflowWSCard\Type\GetCardDocument2 $parameters) : \ArchiflowWSCard\Type\GetCardDocument2Response
    {
        return $this->call('GetCardDocument2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocument3 $parameters
     * @return ResultInterface|Type\GetCardDocument3Response
     * @throws SoapException
     */
    public function getCardDocument3(\ArchiflowWSCard\Type\GetCardDocument3 $parameters) : \ArchiflowWSCard\Type\GetCardDocument3Response
    {
        return $this->call('GetCardDocument3', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocument4 $parameters
     * @return ResultInterface|Type\GetCardDocument4Response
     * @throws SoapException
     */
    public function getCardDocument4(\ArchiflowWSCard\Type\GetCardDocument4 $parameters) : \ArchiflowWSCard\Type\GetCardDocument4Response
    {
        return $this->call('GetCardDocument4', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocument5 $parameters
     * @return ResultInterface|Type\GetCardDocument5Response
     * @throws SoapException
     */
    public function getCardDocument5(\ArchiflowWSCard\Type\GetCardDocument5 $parameters) : \ArchiflowWSCard\Type\GetCardDocument5Response
    {
        return $this->call('GetCardDocument5', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocumentInfo $parameters
     * @return ResultInterface|Type\GetCardDocumentInfoResponse
     * @throws SoapException
     */
    public function getCardDocumentInfo(\ArchiflowWSCard\Type\GetCardDocumentInfo $parameters) : \ArchiflowWSCard\Type\GetCardDocumentInfoResponse
    {
        return $this->call('GetCardDocumentInfo', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocumentInfoByParam $parameters
     * @return ResultInterface|Type\GetCardDocumentInfoByParamResponse
     * @throws SoapException
     */
    public function getCardDocumentInfoByParam(\ArchiflowWSCard\Type\GetCardDocumentInfoByParam $parameters) : \ArchiflowWSCard\Type\GetCardDocumentInfoByParamResponse
    {
        return $this->call('GetCardDocumentInfoByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocumentSignaturesInfo $parameters
     * @return ResultInterface|Type\GetCardDocumentSignaturesInfoResponse
     * @throws SoapException
     */
    public function getCardDocumentSignaturesInfo(\ArchiflowWSCard\Type\GetCardDocumentSignaturesInfo $parameters) : \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoResponse
    {
        return $this->call('GetCardDocumentSignaturesInfo', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardDocumentSignatureCertificate $parameters
     * @return ResultInterface|Type\GetCardDocumentSignatureCertificateResponse
     * @throws SoapException
     */
    public function getCardDocumentSignatureCertificate(\ArchiflowWSCard\Type\GetCardDocumentSignatureCertificate $parameters) : \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateResponse
    {
        return $this->call('GetCardDocumentSignatureCertificate', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachmentSignaturesInfo $parameters
     * @return ResultInterface|Type\GetCardAttachmentSignaturesInfoResponse
     * @throws SoapException
     */
    public function getCardAttachmentSignaturesInfo(\ArchiflowWSCard\Type\GetCardAttachmentSignaturesInfo $parameters) : \ArchiflowWSCard\Type\GetCardAttachmentSignaturesInfoResponse
    {
        return $this->call('GetCardAttachmentSignaturesInfo', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachmentSignatureCertificate $parameters
     * @return ResultInterface|Type\GetCardAttachmentSignatureCertificateResponse
     * @throws SoapException
     */
    public function getCardAttachmentSignatureCertificate(\ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificate $parameters) : \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateResponse
    {
        return $this->call('GetCardAttachmentSignatureCertificate', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachment $parameters
     * @return ResultInterface|Type\GetCardAttachmentResponse
     * @throws SoapException
     */
    public function getCardAttachment(\ArchiflowWSCard\Type\GetCardAttachment $parameters) : \ArchiflowWSCard\Type\GetCardAttachmentResponse
    {
        return $this->call('GetCardAttachment', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachment2 $parameters
     * @return ResultInterface|Type\GetCardAttachment2Response
     * @throws SoapException
     */
    public function getCardAttachment2(\ArchiflowWSCard\Type\GetCardAttachment2 $parameters) : \ArchiflowWSCard\Type\GetCardAttachment2Response
    {
        return $this->call('GetCardAttachment2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachments $parameters
     * @return ResultInterface|Type\GetCardAttachmentsResponse
     * @throws SoapException
     */
    public function getCardAttachments(\ArchiflowWSCard\Type\GetCardAttachments $parameters) : \ArchiflowWSCard\Type\GetCardAttachmentsResponse
    {
        return $this->call('GetCardAttachments', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAttachments2 $parameters
     * @return ResultInterface|Type\GetCardAttachments2Response
     * @throws SoapException
     */
    public function getCardAttachments2(\ArchiflowWSCard\Type\GetCardAttachments2 $parameters) : \ArchiflowWSCard\Type\GetCardAttachments2Response
    {
        return $this->call('GetCardAttachments2', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardIndexes $parameters
     * @return ResultInterface|Type\GetCardIndexesResponse
     * @throws SoapException
     */
    public function getCardIndexes(\ArchiflowWSCard\Type\GetCardIndexes $parameters) : \ArchiflowWSCard\Type\GetCardIndexesResponse
    {
        return $this->call('GetCardIndexes', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetListItems $parameters
     * @return ResultInterface|Type\GetListItemsResponse
     * @throws SoapException
     */
    public function getListItems(\ArchiflowWSCard\Type\GetListItems $parameters) : \ArchiflowWSCard\Type\GetListItemsResponse
    {
        return $this->call('GetListItems', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetListItemsAdditives $parameters
     * @return ResultInterface|Type\GetListItemsAdditivesResponse
     * @throws SoapException
     */
    public function getListItemsAdditives(\ArchiflowWSCard\Type\GetListItemsAdditives $parameters) : \ArchiflowWSCard\Type\GetListItemsAdditivesResponse
    {
        return $this->call('GetListItemsAdditives', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardAdditives $parameters
     * @return ResultInterface|Type\GetCardAdditivesResponse
     * @throws SoapException
     */
    public function getCardAdditives(\ArchiflowWSCard\Type\GetCardAdditives $parameters) : \ArchiflowWSCard\Type\GetCardAdditivesResponse
    {
        return $this->call('GetCardAdditives', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardNotes $parameters
     * @return ResultInterface|Type\GetCardNotesResponse
     * @throws SoapException
     */
    public function getCardNotes(\ArchiflowWSCard\Type\GetCardNotes $parameters) : \ArchiflowWSCard\Type\GetCardNotesResponse
    {
        return $this->call('GetCardNotes', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardHistory $parameters
     * @return ResultInterface|Type\GetCardHistoryResponse
     * @throws SoapException
     */
    public function getCardHistory(\ArchiflowWSCard\Type\GetCardHistory $parameters) : \ArchiflowWSCard\Type\GetCardHistoryResponse
    {
        return $this->call('GetCardHistory', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardIndexes $parameters
     * @return ResultInterface|Type\SetCardIndexesResponse
     * @throws SoapException
     */
    public function setCardIndexes(\ArchiflowWSCard\Type\SetCardIndexes $parameters) : \ArchiflowWSCard\Type\SetCardIndexesResponse
    {
        return $this->call('SetCardIndexes', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardIndexes1 $parameters
     * @return ResultInterface|Type\SetCardIndexes1Response
     * @throws SoapException
     */
    public function setCardIndexes1(\ArchiflowWSCard\Type\SetCardIndexes1 $parameters) : \ArchiflowWSCard\Type\SetCardIndexes1Response
    {
        return $this->call('SetCardIndexes1', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardExpiration $parameters
     * @return ResultInterface|Type\SetCardExpirationResponse
     * @throws SoapException
     */
    public function setCardExpiration(\ArchiflowWSCard\Type\SetCardExpiration $parameters) : \ArchiflowWSCard\Type\SetCardExpirationResponse
    {
        return $this->call('SetCardExpiration', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardExpiration $parameters
     * @return ResultInterface|Type\GetCardExpirationResponse
     * @throws SoapException
     */
    public function getCardExpiration(\ArchiflowWSCard\Type\GetCardExpiration $parameters) : \ArchiflowWSCard\Type\GetCardExpirationResponse
    {
        return $this->call('GetCardExpiration', $parameters);
    }

    /**
     * @param RequestInterface|Type\CalculateCardExpiration $parameters
     * @return ResultInterface|Type\CalculateCardExpirationResponse
     * @throws SoapException
     */
    public function calculateCardExpiration(\ArchiflowWSCard\Type\CalculateCardExpiration $parameters) : \ArchiflowWSCard\Type\CalculateCardExpirationResponse
    {
        return $this->call('CalculateCardExpiration', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardNotes $parameters
     * @return ResultInterface|Type\SetCardNotesResponse
     * @throws SoapException
     */
    public function setCardNotes(\ArchiflowWSCard\Type\SetCardNotes $parameters) : \ArchiflowWSCard\Type\SetCardNotesResponse
    {
        return $this->call('SetCardNotes', $parameters);
    }

    /**
     * @param RequestInterface|Type\WriteCardNotes $parameters
     * @return ResultInterface|Type\WriteCardNotesResponse
     * @throws SoapException
     */
    public function writeCardNotes(\ArchiflowWSCard\Type\WriteCardNotes $parameters) : \ArchiflowWSCard\Type\WriteCardNotesResponse
    {
        return $this->call('WriteCardNotes', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardAOS $parameters
     * @return ResultInterface|Type\SetCardAOSResponse
     * @throws SoapException
     */
    public function setCardAOS(\ArchiflowWSCard\Type\SetCardAOS $parameters) : \ArchiflowWSCard\Type\SetCardAOSResponse
    {
        return $this->call('SetCardAOS', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardAsReadOnly $parameters
     * @return ResultInterface|Type\SetCardAsReadOnlyResponse
     * @throws SoapException
     */
    public function setCardAsReadOnly(\ArchiflowWSCard\Type\SetCardAsReadOnly $parameters) : \ArchiflowWSCard\Type\SetCardAsReadOnlyResponse
    {
        return $this->call('SetCardAsReadOnly', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardAdditives $parameters
     * @return ResultInterface|Type\SetCardAdditivesResponse
     * @throws SoapException
     */
    public function setCardAdditives(\ArchiflowWSCard\Type\SetCardAdditives $parameters) : \ArchiflowWSCard\Type\SetCardAdditivesResponse
    {
        return $this->call('SetCardAdditives', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardAdditives1 $parameters
     * @return ResultInterface|Type\SetCardAdditives1Response
     * @throws SoapException
     */
    public function setCardAdditives1(\ArchiflowWSCard\Type\SetCardAdditives1 $parameters) : \ArchiflowWSCard\Type\SetCardAdditives1Response
    {
        return $this->call('SetCardAdditives1', $parameters);
    }

    /**
     * @param RequestInterface|Type\WriteCardHistory $parameters
     * @return ResultInterface|Type\WriteCardHistoryResponse
     * @throws SoapException
     */
    public function writeCardHistory(\ArchiflowWSCard\Type\WriteCardHistory $parameters) : \ArchiflowWSCard\Type\WriteCardHistoryResponse
    {
        return $this->call('WriteCardHistory', $parameters);
    }

    /**
     * @param RequestInterface|Type\SignCardAdditive $parameters
     * @return ResultInterface|Type\SignCardAdditiveResponse
     * @throws SoapException
     */
    public function signCardAdditive(\ArchiflowWSCard\Type\SignCardAdditive $parameters) : \ArchiflowWSCard\Type\SignCardAdditiveResponse
    {
        return $this->call('SignCardAdditive', $parameters);
    }

    /**
     * @param RequestInterface|Type\SignCardAdditiveGetImage $parameters
     * @return ResultInterface|Type\SignCardAdditiveGetImageResponse
     * @throws SoapException
     */
    public function signCardAdditiveGetImage(\ArchiflowWSCard\Type\SignCardAdditiveGetImage $parameters) : \ArchiflowWSCard\Type\SignCardAdditiveGetImageResponse
    {
        return $this->call('SignCardAdditiveGetImage', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCard $parameters
     * @return ResultInterface|Type\SendCardResponse
     * @throws SoapException
     */
    public function sendCard(\ArchiflowWSCard\Type\SendCard $parameters) : \ArchiflowWSCard\Type\SendCardResponse
    {
        return $this->call('SendCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCard1 $parameters
     * @return ResultInterface|Type\SendCard1Response
     * @throws SoapException
     */
    public function sendCard1(\ArchiflowWSCard\Type\SendCard1 $parameters) : \ArchiflowWSCard\Type\SendCard1Response
    {
        return $this->call('SendCard1', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCardByParam $parameters
     * @return ResultInterface|Type\SendCardByParamResponse
     * @throws SoapException
     */
    public function sendCardByParam(\ArchiflowWSCard\Type\SendCardByParam $parameters) : \ArchiflowWSCard\Type\SendCardByParamResponse
    {
        return $this->call('SendCardByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendCardToDesktop $parameters
     * @return ResultInterface|Type\SendCardToDesktopResponse
     * @throws SoapException
     */
    public function sendCardToDesktop(\ArchiflowWSCard\Type\SendCardToDesktop $parameters) : \ArchiflowWSCard\Type\SendCardToDesktopResponse
    {
        return $this->call('SendCardToDesktop', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCard $parameters
     * @return ResultInterface|Type\InsertCardResponse
     * @throws SoapException
     */
    public function insertCard(\ArchiflowWSCard\Type\InsertCard $parameters) : \ArchiflowWSCard\Type\InsertCardResponse
    {
        return $this->call('InsertCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreateCard $parameters
     * @return ResultInterface|Type\CreateCardResponse
     * @throws SoapException
     */
    public function createCard(\ArchiflowWSCard\Type\CreateCard $parameters) : \ArchiflowWSCard\Type\CreateCardResponse
    {
        return $this->call('CreateCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCard1 $parameters
     * @return ResultInterface|Type\InsertCard1Response
     * @throws SoapException
     */
    public function insertCard1(\ArchiflowWSCard\Type\InsertCard1 $parameters) : \ArchiflowWSCard\Type\InsertCard1Response
    {
        return $this->call('InsertCard1', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCard2 $parameters
     * @return ResultInterface|Type\InsertCard2Response
     * @throws SoapException
     */
    public function insertCard2(\ArchiflowWSCard\Type\InsertCard2 $parameters) : \ArchiflowWSCard\Type\InsertCard2Response
    {
        return $this->call('InsertCard2', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCard3 $parameters
     * @return ResultInterface|Type\InsertCard3Response
     * @throws SoapException
     */
    public function insertCard3(\ArchiflowWSCard\Type\InsertCard3 $parameters) : \ArchiflowWSCard\Type\InsertCard3Response
    {
        return $this->call('InsertCard3', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCard4 $parameters
     * @return ResultInterface|Type\InsertCard4Response
     * @throws SoapException
     */
    public function insertCard4(\ArchiflowWSCard\Type\InsertCard4 $parameters) : \ArchiflowWSCard\Type\InsertCard4Response
    {
        return $this->call('InsertCard4', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCardByParam $parameters
     * @return ResultInterface|Type\InsertCardByParamResponse
     * @throws SoapException
     */
    public function insertCardByParam(\ArchiflowWSCard\Type\InsertCardByParam $parameters) : \ArchiflowWSCard\Type\InsertCardByParamResponse
    {
        return $this->call('InsertCardByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCardFromCard $parameters
     * @return ResultInterface|Type\InsertCardFromCardResponse
     * @throws SoapException
     */
    public function insertCardFromCard(\ArchiflowWSCard\Type\InsertCardFromCard $parameters) : \ArchiflowWSCard\Type\InsertCardFromCardResponse
    {
        return $this->call('InsertCardFromCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\SortCard $parameters
     * @return ResultInterface|Type\SortCardResponse
     * @throws SoapException
     */
    public function sortCard(\ArchiflowWSCard\Type\SortCard $parameters) : \ArchiflowWSCard\Type\SortCardResponse
    {
        return $this->call('SortCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteCard $parameters
     * @return ResultInterface|Type\DeleteCardResponse
     * @throws SoapException
     */
    public function deleteCard(\ArchiflowWSCard\Type\DeleteCard $parameters) : \ArchiflowWSCard\Type\DeleteCardResponse
    {
        return $this->call('DeleteCard', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteCardByParam $parameters
     * @return ResultInterface|Type\DeleteCardByParamResponse
     * @throws SoapException
     */
    public function deleteCardByParam(\ArchiflowWSCard\Type\DeleteCardByParam $parameters) : \ArchiflowWSCard\Type\DeleteCardByParamResponse
    {
        return $this->call('DeleteCardByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\MakePressMark $parameters
     * @return ResultInterface|Type\MakePressMarkResponse
     * @throws SoapException
     */
    public function makePressMark(\ArchiflowWSCard\Type\MakePressMark $parameters) : \ArchiflowWSCard\Type\MakePressMarkResponse
    {
        return $this->call('MakePressMark', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetPressMarkInfo $parameters
     * @return ResultInterface|Type\GetPressMarkInfoResponse
     * @throws SoapException
     */
    public function getPressMarkInfo(\ArchiflowWSCard\Type\GetPressMarkInfo $parameters) : \ArchiflowWSCard\Type\GetPressMarkInfoResponse
    {
        return $this->call('GetPressMarkInfo', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetPressMarkModelsList $parameters
     * @return ResultInterface|Type\GetPressMarkModelsListResponse
     * @throws SoapException
     */
    public function getPressMarkModelsList(\ArchiflowWSCard\Type\GetPressMarkModelsList $parameters) : \ArchiflowWSCard\Type\GetPressMarkModelsListResponse
    {
        return $this->call('GetPressMarkModelsList', $parameters);
    }

    /**
     * @param RequestInterface|Type\AttachPressMark $parameters
     * @return ResultInterface|Type\AttachPressMarkResponse
     * @throws SoapException
     */
    public function attachPressMark(\ArchiflowWSCard\Type\AttachPressMark $parameters) : \ArchiflowWSCard\Type\AttachPressMarkResponse
    {
        return $this->call('AttachPressMark', $parameters);
    }

    /**
     * @param RequestInterface|Type\ProtectModify $parameters
     * @return ResultInterface|Type\ProtectModifyResponse
     * @throws SoapException
     */
    public function protectModify(\ArchiflowWSCard\Type\ProtectModify $parameters) : \ArchiflowWSCard\Type\ProtectModifyResponse
    {
        return $this->call('ProtectModify', $parameters);
    }

    /**
     * @param RequestInterface|Type\ImportDocument $parameters
     * @return ResultInterface|Type\ImportDocumentResponse
     * @throws SoapException
     */
    public function importDocument(\ArchiflowWSCard\Type\ImportDocument $parameters) : \ArchiflowWSCard\Type\ImportDocumentResponse
    {
        return $this->call('ImportDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\ImportDocument2 $parameters
     * @return ResultInterface|Type\ImportDocument2Response
     * @throws SoapException
     */
    public function importDocument2(\ArchiflowWSCard\Type\ImportDocument2 $parameters) : \ArchiflowWSCard\Type\ImportDocument2Response
    {
        return $this->call('ImportDocument2', $parameters);
    }

    /**
     * @param RequestInterface|Type\ImportDocumentByParam $parameters
     * @return ResultInterface|Type\ImportDocumentByParamResponse
     * @throws SoapException
     */
    public function importDocumentByParam(\ArchiflowWSCard\Type\ImportDocumentByParam $parameters) : \ArchiflowWSCard\Type\ImportDocumentByParamResponse
    {
        return $this->call('ImportDocumentByParam', $parameters);
    }


}

