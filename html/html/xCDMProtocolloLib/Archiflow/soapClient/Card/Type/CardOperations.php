<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardOperations implements RequestInterface
{

    /**
     * @var bool
     */
    private $AdditionalData = null;

    /**
     * @var bool
     */
    private $AnalogCompliantCopyDoc = null;

    /**
     * @var bool
     */
    private $Annotations = null;

    /**
     * @var bool
     */
    private $ArchivalCollation = null;

    /**
     * @var bool
     */
    private $AutoUpdateDoc = null;

    /**
     * @var bool
     */
    private $Cancellation = null;

    /**
     * @var bool
     */
    private $CheckInOutDoc = null;

    /**
     * @var bool
     */
    private $ConsolidateDoc = null;

    /**
     * @var bool
     */
    private $ConvToPdfDoc = null;

    /**
     * @var bool
     */
    private $CreateLinkArchivalCollation = null;

    /**
     * @var bool
     */
    private $DigestAtt = null;

    /**
     * @var bool
     */
    private $DigestDoc = null;

    /**
     * @var bool
     */
    private $DigitalCompliantCopyDoc = null;

    /**
     * @var bool
     */
    private $DigitalSign = null;

    /**
     * @var bool
     */
    private $DigitalSignAtt = null;

    /**
     * @var bool
     */
    private $DuplicateCardIndexes = null;

    /**
     * @var bool
     */
    private $DuplicateCardIndexesAndDoc = null;

    /**
     * @var bool
     */
    private $ElectronicSign = null;

    /**
     * @var bool
     */
    private $ElectronicStampingSign = null;

    /**
     * @var bool
     */
    private $GlifoAtt = null;

    /**
     * @var bool
     */
    private $GlifoDoc = null;

    /**
     * @var bool
     */
    private $GraphometricSign = null;

    /**
     * @var bool
     */
    private $IMApprovalRefusal = null;

    /**
     * @var bool
     */
    private $IMChangeDatePlanSendInvoiceOnMainChannel = null;

    /**
     * @var bool
     */
    private $IMChangeDatePlanSendInvoiceOnMainChannelPEC = null;

    /**
     * @var bool
     */
    private $IMChangeDatePlanSendInvoiceOnMainChannelPEO = null;

    /**
     * @var bool
     */
    private $IMChangeDatePlanSendInvoiceOnMainChannelSDI = null;

    /**
     * @var bool
     */
    private $IMChannelSwitching = null;

    /**
     * @var bool
     */
    private $IMPlanSendInvoiceOnMainChannel = null;

    /**
     * @var bool
     */
    private $IMPlanSendInvoiceOnMainChannelPEC = null;

    /**
     * @var bool
     */
    private $IMPlanSendInvoiceOnMainChannelPEO = null;

    /**
     * @var bool
     */
    private $IMPlanSendInvoiceOnMainChannelSDI = null;

    /**
     * @var bool
     */
    private $IMReSendInvoiceOnSubChannel = null;

    /**
     * @var bool
     */
    private $IMReSendInvoiceOnSubChannelPEC = null;

    /**
     * @var bool
     */
    private $IMReSendInvoiceOnSubChannelPEO = null;

    /**
     * @var bool
     */
    private $IMSendApprovalRefusalToSDI = null;

    /**
     * @var bool
     */
    private $IMSendApprovalToSDI = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnMainChannel = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnMainChannelADP = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnMainChannelPEC = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnMainChannelPEO = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnMainChannelSDI = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnSubChannel = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnSubChannelADP = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnSubChannelPEC = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnSubChannelPEO = null;

    /**
     * @var bool
     */
    private $IMSendInvoiceOnSubChannelSDI = null;

    /**
     * @var bool
     */
    private $IMSendRefusalToSDI = null;

    /**
     * @var bool
     */
    private $IMStopSendInvoiceOnMainChannel = null;

    /**
     * @var bool
     */
    private $ImportAddDoc = null;

    /**
     * @var bool
     */
    private $ImportDoc = null;

    /**
     * @var bool
     */
    private $Indexes = null;

    /**
     * @var bool
     */
    private $InsModAtt = null;

    /**
     * @var bool
     */
    private $Invalidation = null;

    /**
     * @var bool
     */
    private $IsWf = null;

    /**
     * @var bool
     */
    private $LockDoc = null;

    /**
     * @var bool
     */
    private $PdfNativeSign = null;

    /**
     * @var bool
     */
    private $PdfNativeSignAtt = null;

    /**
     * @var bool
     */
    private $Permalink = null;

    /**
     * @var bool
     */
    private $PosteOnLine = null;

    /**
     * @var bool
     */
    private $PressMarkDoc = null;

    /**
     * @var bool
     */
    private $ProtocolCard = null;

    /**
     * @var bool
     */
    private $RemoteSign = null;

    /**
     * @var bool
     */
    private $RemoteSignAtt = null;

    /**
     * @var bool
     */
    private $SaveVersionDoc = null;

    /**
     * @var bool
     */
    private $ScanAddDoc = null;

    /**
     * @var bool
     */
    private $ScanDoc = null;

    /**
     * @var bool
     */
    private $SendExtendedEmail = null;

    /**
     * @var bool
     */
    private $SendExternalEmail = null;

    /**
     * @var bool
     */
    private $SendInteropEmail = null;

    /**
     * @var bool
     */
    private $SendInteropRefuseEmail = null;

    /**
     * @var bool
     */
    private $SendInvoice = null;

    /**
     * @var bool
     */
    private $SendNotificationEC = null;

    /**
     * @var bool
     */
    private $SendPECCourtesyCopy = null;

    /**
     * @var bool
     */
    private $SendPECPEOEmail = null;

    /**
     * @var bool
     */
    private $SendPECPEOEmailForward = null;

    /**
     * @var bool
     */
    private $SendPECPEOEmailProtocolReply = null;

    /**
     * @var bool
     */
    private $SendPECPEOEmailReply = null;

    /**
     * @var bool
     */
    private $Sharing = null;

    /**
     * @var bool
     */
    private $StandardCollation = null;

    /**
     * @var bool
     */
    private $StoreInteropEmail = null;

    /**
     * @var bool
     */
    private $StorePECPEOEmail = null;

    /**
     * @var bool
     */
    private $TaskOnDemand = null;

    /**
     * @var bool
     */
    private $TimeStamp = null;

    /**
     * @var bool
     */
    private $TimeStampAtt = null;

    /**
     * @var bool
     */
    private $Visibility = null;

    /**
     * @var bool
     */
    private $WfAssignInChargeTo = null;

    /**
     * @var bool
     */
    private $WfForward = null;

    /**
     * @var bool
     */
    private $WfProcessInfo = null;

    /**
     * @var bool
     */
    private $WfProcessRestore = null;

    /**
     * @var bool
     */
    private $WfProcessStart = null;

    /**
     * @var bool
     */
    private $WfProcessStop = null;

    /**
     * @var bool
     */
    private $WfProcessSuspend = null;

    /**
     * @var bool
     */
    private $WfRefuse = null;

    /**
     * @var bool
     */
    private $WfRemoveInChargeFrom = null;

    /**
     * @var bool
     */
    private $WfTakeInCharge = null;

    /**
     * Constructor
     *
     * @var bool $AdditionalData
     * @var bool $AnalogCompliantCopyDoc
     * @var bool $Annotations
     * @var bool $ArchivalCollation
     * @var bool $AutoUpdateDoc
     * @var bool $Cancellation
     * @var bool $CheckInOutDoc
     * @var bool $ConsolidateDoc
     * @var bool $ConvToPdfDoc
     * @var bool $CreateLinkArchivalCollation
     * @var bool $DigestAtt
     * @var bool $DigestDoc
     * @var bool $DigitalCompliantCopyDoc
     * @var bool $DigitalSign
     * @var bool $DigitalSignAtt
     * @var bool $DuplicateCardIndexes
     * @var bool $DuplicateCardIndexesAndDoc
     * @var bool $ElectronicSign
     * @var bool $ElectronicStampingSign
     * @var bool $GlifoAtt
     * @var bool $GlifoDoc
     * @var bool $GraphometricSign
     * @var bool $IMApprovalRefusal
     * @var bool $IMChangeDatePlanSendInvoiceOnMainChannel
     * @var bool $IMChangeDatePlanSendInvoiceOnMainChannelPEC
     * @var bool $IMChangeDatePlanSendInvoiceOnMainChannelPEO
     * @var bool $IMChangeDatePlanSendInvoiceOnMainChannelSDI
     * @var bool $IMChannelSwitching
     * @var bool $IMPlanSendInvoiceOnMainChannel
     * @var bool $IMPlanSendInvoiceOnMainChannelPEC
     * @var bool $IMPlanSendInvoiceOnMainChannelPEO
     * @var bool $IMPlanSendInvoiceOnMainChannelSDI
     * @var bool $IMReSendInvoiceOnSubChannel
     * @var bool $IMReSendInvoiceOnSubChannelPEC
     * @var bool $IMReSendInvoiceOnSubChannelPEO
     * @var bool $IMSendApprovalRefusalToSDI
     * @var bool $IMSendApprovalToSDI
     * @var bool $IMSendInvoiceOnMainChannel
     * @var bool $IMSendInvoiceOnMainChannelADP
     * @var bool $IMSendInvoiceOnMainChannelPEC
     * @var bool $IMSendInvoiceOnMainChannelPEO
     * @var bool $IMSendInvoiceOnMainChannelSDI
     * @var bool $IMSendInvoiceOnSubChannel
     * @var bool $IMSendInvoiceOnSubChannelADP
     * @var bool $IMSendInvoiceOnSubChannelPEC
     * @var bool $IMSendInvoiceOnSubChannelPEO
     * @var bool $IMSendInvoiceOnSubChannelSDI
     * @var bool $IMSendRefusalToSDI
     * @var bool $IMStopSendInvoiceOnMainChannel
     * @var bool $ImportAddDoc
     * @var bool $ImportDoc
     * @var bool $Indexes
     * @var bool $InsModAtt
     * @var bool $Invalidation
     * @var bool $IsWf
     * @var bool $LockDoc
     * @var bool $PdfNativeSign
     * @var bool $PdfNativeSignAtt
     * @var bool $Permalink
     * @var bool $PosteOnLine
     * @var bool $PressMarkDoc
     * @var bool $ProtocolCard
     * @var bool $RemoteSign
     * @var bool $RemoteSignAtt
     * @var bool $SaveVersionDoc
     * @var bool $ScanAddDoc
     * @var bool $ScanDoc
     * @var bool $SendExtendedEmail
     * @var bool $SendExternalEmail
     * @var bool $SendInteropEmail
     * @var bool $SendInteropRefuseEmail
     * @var bool $SendInvoice
     * @var bool $SendNotificationEC
     * @var bool $SendPECCourtesyCopy
     * @var bool $SendPECPEOEmail
     * @var bool $SendPECPEOEmailForward
     * @var bool $SendPECPEOEmailProtocolReply
     * @var bool $SendPECPEOEmailReply
     * @var bool $Sharing
     * @var bool $StandardCollation
     * @var bool $StoreInteropEmail
     * @var bool $StorePECPEOEmail
     * @var bool $TaskOnDemand
     * @var bool $TimeStamp
     * @var bool $TimeStampAtt
     * @var bool $Visibility
     * @var bool $WfAssignInChargeTo
     * @var bool $WfForward
     * @var bool $WfProcessInfo
     * @var bool $WfProcessRestore
     * @var bool $WfProcessStart
     * @var bool $WfProcessStop
     * @var bool $WfProcessSuspend
     * @var bool $WfRefuse
     * @var bool $WfRemoveInChargeFrom
     * @var bool $WfTakeInCharge
     */
    public function __construct($AdditionalData, $AnalogCompliantCopyDoc, $Annotations, $ArchivalCollation, $AutoUpdateDoc, $Cancellation, $CheckInOutDoc, $ConsolidateDoc, $ConvToPdfDoc, $CreateLinkArchivalCollation, $DigestAtt, $DigestDoc, $DigitalCompliantCopyDoc, $DigitalSign, $DigitalSignAtt, $DuplicateCardIndexes, $DuplicateCardIndexesAndDoc, $ElectronicSign, $ElectronicStampingSign, $GlifoAtt, $GlifoDoc, $GraphometricSign, $IMApprovalRefusal, $IMChangeDatePlanSendInvoiceOnMainChannel, $IMChangeDatePlanSendInvoiceOnMainChannelPEC, $IMChangeDatePlanSendInvoiceOnMainChannelPEO, $IMChangeDatePlanSendInvoiceOnMainChannelSDI, $IMChannelSwitching, $IMPlanSendInvoiceOnMainChannel, $IMPlanSendInvoiceOnMainChannelPEC, $IMPlanSendInvoiceOnMainChannelPEO, $IMPlanSendInvoiceOnMainChannelSDI, $IMReSendInvoiceOnSubChannel, $IMReSendInvoiceOnSubChannelPEC, $IMReSendInvoiceOnSubChannelPEO, $IMSendApprovalRefusalToSDI, $IMSendApprovalToSDI, $IMSendInvoiceOnMainChannel, $IMSendInvoiceOnMainChannelADP, $IMSendInvoiceOnMainChannelPEC, $IMSendInvoiceOnMainChannelPEO, $IMSendInvoiceOnMainChannelSDI, $IMSendInvoiceOnSubChannel, $IMSendInvoiceOnSubChannelADP, $IMSendInvoiceOnSubChannelPEC, $IMSendInvoiceOnSubChannelPEO, $IMSendInvoiceOnSubChannelSDI, $IMSendRefusalToSDI, $IMStopSendInvoiceOnMainChannel, $ImportAddDoc, $ImportDoc, $Indexes, $InsModAtt, $Invalidation, $IsWf, $LockDoc, $PdfNativeSign, $PdfNativeSignAtt, $Permalink, $PosteOnLine, $PressMarkDoc, $ProtocolCard, $RemoteSign, $RemoteSignAtt, $SaveVersionDoc, $ScanAddDoc, $ScanDoc, $SendExtendedEmail, $SendExternalEmail, $SendInteropEmail, $SendInteropRefuseEmail, $SendInvoice, $SendNotificationEC, $SendPECCourtesyCopy, $SendPECPEOEmail, $SendPECPEOEmailForward, $SendPECPEOEmailProtocolReply, $SendPECPEOEmailReply, $Sharing, $StandardCollation, $StoreInteropEmail, $StorePECPEOEmail, $TaskOnDemand, $TimeStamp, $TimeStampAtt, $Visibility, $WfAssignInChargeTo, $WfForward, $WfProcessInfo, $WfProcessRestore, $WfProcessStart, $WfProcessStop, $WfProcessSuspend, $WfRefuse, $WfRemoveInChargeFrom, $WfTakeInCharge)
    {
        $this->AdditionalData = $AdditionalData;
        $this->AnalogCompliantCopyDoc = $AnalogCompliantCopyDoc;
        $this->Annotations = $Annotations;
        $this->ArchivalCollation = $ArchivalCollation;
        $this->AutoUpdateDoc = $AutoUpdateDoc;
        $this->Cancellation = $Cancellation;
        $this->CheckInOutDoc = $CheckInOutDoc;
        $this->ConsolidateDoc = $ConsolidateDoc;
        $this->ConvToPdfDoc = $ConvToPdfDoc;
        $this->CreateLinkArchivalCollation = $CreateLinkArchivalCollation;
        $this->DigestAtt = $DigestAtt;
        $this->DigestDoc = $DigestDoc;
        $this->DigitalCompliantCopyDoc = $DigitalCompliantCopyDoc;
        $this->DigitalSign = $DigitalSign;
        $this->DigitalSignAtt = $DigitalSignAtt;
        $this->DuplicateCardIndexes = $DuplicateCardIndexes;
        $this->DuplicateCardIndexesAndDoc = $DuplicateCardIndexesAndDoc;
        $this->ElectronicSign = $ElectronicSign;
        $this->ElectronicStampingSign = $ElectronicStampingSign;
        $this->GlifoAtt = $GlifoAtt;
        $this->GlifoDoc = $GlifoDoc;
        $this->GraphometricSign = $GraphometricSign;
        $this->IMApprovalRefusal = $IMApprovalRefusal;
        $this->IMChangeDatePlanSendInvoiceOnMainChannel = $IMChangeDatePlanSendInvoiceOnMainChannel;
        $this->IMChangeDatePlanSendInvoiceOnMainChannelPEC = $IMChangeDatePlanSendInvoiceOnMainChannelPEC;
        $this->IMChangeDatePlanSendInvoiceOnMainChannelPEO = $IMChangeDatePlanSendInvoiceOnMainChannelPEO;
        $this->IMChangeDatePlanSendInvoiceOnMainChannelSDI = $IMChangeDatePlanSendInvoiceOnMainChannelSDI;
        $this->IMChannelSwitching = $IMChannelSwitching;
        $this->IMPlanSendInvoiceOnMainChannel = $IMPlanSendInvoiceOnMainChannel;
        $this->IMPlanSendInvoiceOnMainChannelPEC = $IMPlanSendInvoiceOnMainChannelPEC;
        $this->IMPlanSendInvoiceOnMainChannelPEO = $IMPlanSendInvoiceOnMainChannelPEO;
        $this->IMPlanSendInvoiceOnMainChannelSDI = $IMPlanSendInvoiceOnMainChannelSDI;
        $this->IMReSendInvoiceOnSubChannel = $IMReSendInvoiceOnSubChannel;
        $this->IMReSendInvoiceOnSubChannelPEC = $IMReSendInvoiceOnSubChannelPEC;
        $this->IMReSendInvoiceOnSubChannelPEO = $IMReSendInvoiceOnSubChannelPEO;
        $this->IMSendApprovalRefusalToSDI = $IMSendApprovalRefusalToSDI;
        $this->IMSendApprovalToSDI = $IMSendApprovalToSDI;
        $this->IMSendInvoiceOnMainChannel = $IMSendInvoiceOnMainChannel;
        $this->IMSendInvoiceOnMainChannelADP = $IMSendInvoiceOnMainChannelADP;
        $this->IMSendInvoiceOnMainChannelPEC = $IMSendInvoiceOnMainChannelPEC;
        $this->IMSendInvoiceOnMainChannelPEO = $IMSendInvoiceOnMainChannelPEO;
        $this->IMSendInvoiceOnMainChannelSDI = $IMSendInvoiceOnMainChannelSDI;
        $this->IMSendInvoiceOnSubChannel = $IMSendInvoiceOnSubChannel;
        $this->IMSendInvoiceOnSubChannelADP = $IMSendInvoiceOnSubChannelADP;
        $this->IMSendInvoiceOnSubChannelPEC = $IMSendInvoiceOnSubChannelPEC;
        $this->IMSendInvoiceOnSubChannelPEO = $IMSendInvoiceOnSubChannelPEO;
        $this->IMSendInvoiceOnSubChannelSDI = $IMSendInvoiceOnSubChannelSDI;
        $this->IMSendRefusalToSDI = $IMSendRefusalToSDI;
        $this->IMStopSendInvoiceOnMainChannel = $IMStopSendInvoiceOnMainChannel;
        $this->ImportAddDoc = $ImportAddDoc;
        $this->ImportDoc = $ImportDoc;
        $this->Indexes = $Indexes;
        $this->InsModAtt = $InsModAtt;
        $this->Invalidation = $Invalidation;
        $this->IsWf = $IsWf;
        $this->LockDoc = $LockDoc;
        $this->PdfNativeSign = $PdfNativeSign;
        $this->PdfNativeSignAtt = $PdfNativeSignAtt;
        $this->Permalink = $Permalink;
        $this->PosteOnLine = $PosteOnLine;
        $this->PressMarkDoc = $PressMarkDoc;
        $this->ProtocolCard = $ProtocolCard;
        $this->RemoteSign = $RemoteSign;
        $this->RemoteSignAtt = $RemoteSignAtt;
        $this->SaveVersionDoc = $SaveVersionDoc;
        $this->ScanAddDoc = $ScanAddDoc;
        $this->ScanDoc = $ScanDoc;
        $this->SendExtendedEmail = $SendExtendedEmail;
        $this->SendExternalEmail = $SendExternalEmail;
        $this->SendInteropEmail = $SendInteropEmail;
        $this->SendInteropRefuseEmail = $SendInteropRefuseEmail;
        $this->SendInvoice = $SendInvoice;
        $this->SendNotificationEC = $SendNotificationEC;
        $this->SendPECCourtesyCopy = $SendPECCourtesyCopy;
        $this->SendPECPEOEmail = $SendPECPEOEmail;
        $this->SendPECPEOEmailForward = $SendPECPEOEmailForward;
        $this->SendPECPEOEmailProtocolReply = $SendPECPEOEmailProtocolReply;
        $this->SendPECPEOEmailReply = $SendPECPEOEmailReply;
        $this->Sharing = $Sharing;
        $this->StandardCollation = $StandardCollation;
        $this->StoreInteropEmail = $StoreInteropEmail;
        $this->StorePECPEOEmail = $StorePECPEOEmail;
        $this->TaskOnDemand = $TaskOnDemand;
        $this->TimeStamp = $TimeStamp;
        $this->TimeStampAtt = $TimeStampAtt;
        $this->Visibility = $Visibility;
        $this->WfAssignInChargeTo = $WfAssignInChargeTo;
        $this->WfForward = $WfForward;
        $this->WfProcessInfo = $WfProcessInfo;
        $this->WfProcessRestore = $WfProcessRestore;
        $this->WfProcessStart = $WfProcessStart;
        $this->WfProcessStop = $WfProcessStop;
        $this->WfProcessSuspend = $WfProcessSuspend;
        $this->WfRefuse = $WfRefuse;
        $this->WfRemoveInChargeFrom = $WfRemoveInChargeFrom;
        $this->WfTakeInCharge = $WfTakeInCharge;
    }

    /**
     * @return bool
     */
    public function getAdditionalData()
    {
        return $this->AdditionalData;
    }

    /**
     * @param bool $AdditionalData
     * @return CardOperations
     */
    public function withAdditionalData($AdditionalData)
    {
        $new = clone $this;
        $new->AdditionalData = $AdditionalData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAnalogCompliantCopyDoc()
    {
        return $this->AnalogCompliantCopyDoc;
    }

    /**
     * @param bool $AnalogCompliantCopyDoc
     * @return CardOperations
     */
    public function withAnalogCompliantCopyDoc($AnalogCompliantCopyDoc)
    {
        $new = clone $this;
        $new->AnalogCompliantCopyDoc = $AnalogCompliantCopyDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAnnotations()
    {
        return $this->Annotations;
    }

    /**
     * @param bool $Annotations
     * @return CardOperations
     */
    public function withAnnotations($Annotations)
    {
        $new = clone $this;
        $new->Annotations = $Annotations;

        return $new;
    }

    /**
     * @return bool
     */
    public function getArchivalCollation()
    {
        return $this->ArchivalCollation;
    }

    /**
     * @param bool $ArchivalCollation
     * @return CardOperations
     */
    public function withArchivalCollation($ArchivalCollation)
    {
        $new = clone $this;
        $new->ArchivalCollation = $ArchivalCollation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAutoUpdateDoc()
    {
        return $this->AutoUpdateDoc;
    }

    /**
     * @param bool $AutoUpdateDoc
     * @return CardOperations
     */
    public function withAutoUpdateDoc($AutoUpdateDoc)
    {
        $new = clone $this;
        $new->AutoUpdateDoc = $AutoUpdateDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCancellation()
    {
        return $this->Cancellation;
    }

    /**
     * @param bool $Cancellation
     * @return CardOperations
     */
    public function withCancellation($Cancellation)
    {
        $new = clone $this;
        $new->Cancellation = $Cancellation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCheckInOutDoc()
    {
        return $this->CheckInOutDoc;
    }

    /**
     * @param bool $CheckInOutDoc
     * @return CardOperations
     */
    public function withCheckInOutDoc($CheckInOutDoc)
    {
        $new = clone $this;
        $new->CheckInOutDoc = $CheckInOutDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getConsolidateDoc()
    {
        return $this->ConsolidateDoc;
    }

    /**
     * @param bool $ConsolidateDoc
     * @return CardOperations
     */
    public function withConsolidateDoc($ConsolidateDoc)
    {
        $new = clone $this;
        $new->ConsolidateDoc = $ConsolidateDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getConvToPdfDoc()
    {
        return $this->ConvToPdfDoc;
    }

    /**
     * @param bool $ConvToPdfDoc
     * @return CardOperations
     */
    public function withConvToPdfDoc($ConvToPdfDoc)
    {
        $new = clone $this;
        $new->ConvToPdfDoc = $ConvToPdfDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCreateLinkArchivalCollation()
    {
        return $this->CreateLinkArchivalCollation;
    }

    /**
     * @param bool $CreateLinkArchivalCollation
     * @return CardOperations
     */
    public function withCreateLinkArchivalCollation($CreateLinkArchivalCollation)
    {
        $new = clone $this;
        $new->CreateLinkArchivalCollation = $CreateLinkArchivalCollation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDigestAtt()
    {
        return $this->DigestAtt;
    }

    /**
     * @param bool $DigestAtt
     * @return CardOperations
     */
    public function withDigestAtt($DigestAtt)
    {
        $new = clone $this;
        $new->DigestAtt = $DigestAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDigestDoc()
    {
        return $this->DigestDoc;
    }

    /**
     * @param bool $DigestDoc
     * @return CardOperations
     */
    public function withDigestDoc($DigestDoc)
    {
        $new = clone $this;
        $new->DigestDoc = $DigestDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDigitalCompliantCopyDoc()
    {
        return $this->DigitalCompliantCopyDoc;
    }

    /**
     * @param bool $DigitalCompliantCopyDoc
     * @return CardOperations
     */
    public function withDigitalCompliantCopyDoc($DigitalCompliantCopyDoc)
    {
        $new = clone $this;
        $new->DigitalCompliantCopyDoc = $DigitalCompliantCopyDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDigitalSign()
    {
        return $this->DigitalSign;
    }

    /**
     * @param bool $DigitalSign
     * @return CardOperations
     */
    public function withDigitalSign($DigitalSign)
    {
        $new = clone $this;
        $new->DigitalSign = $DigitalSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDigitalSignAtt()
    {
        return $this->DigitalSignAtt;
    }

    /**
     * @param bool $DigitalSignAtt
     * @return CardOperations
     */
    public function withDigitalSignAtt($DigitalSignAtt)
    {
        $new = clone $this;
        $new->DigitalSignAtt = $DigitalSignAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDuplicateCardIndexes()
    {
        return $this->DuplicateCardIndexes;
    }

    /**
     * @param bool $DuplicateCardIndexes
     * @return CardOperations
     */
    public function withDuplicateCardIndexes($DuplicateCardIndexes)
    {
        $new = clone $this;
        $new->DuplicateCardIndexes = $DuplicateCardIndexes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDuplicateCardIndexesAndDoc()
    {
        return $this->DuplicateCardIndexesAndDoc;
    }

    /**
     * @param bool $DuplicateCardIndexesAndDoc
     * @return CardOperations
     */
    public function withDuplicateCardIndexesAndDoc($DuplicateCardIndexesAndDoc)
    {
        $new = clone $this;
        $new->DuplicateCardIndexesAndDoc = $DuplicateCardIndexesAndDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getElectronicSign()
    {
        return $this->ElectronicSign;
    }

    /**
     * @param bool $ElectronicSign
     * @return CardOperations
     */
    public function withElectronicSign($ElectronicSign)
    {
        $new = clone $this;
        $new->ElectronicSign = $ElectronicSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getElectronicStampingSign()
    {
        return $this->ElectronicStampingSign;
    }

    /**
     * @param bool $ElectronicStampingSign
     * @return CardOperations
     */
    public function withElectronicStampingSign($ElectronicStampingSign)
    {
        $new = clone $this;
        $new->ElectronicStampingSign = $ElectronicStampingSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGlifoAtt()
    {
        return $this->GlifoAtt;
    }

    /**
     * @param bool $GlifoAtt
     * @return CardOperations
     */
    public function withGlifoAtt($GlifoAtt)
    {
        $new = clone $this;
        $new->GlifoAtt = $GlifoAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGlifoDoc()
    {
        return $this->GlifoDoc;
    }

    /**
     * @param bool $GlifoDoc
     * @return CardOperations
     */
    public function withGlifoDoc($GlifoDoc)
    {
        $new = clone $this;
        $new->GlifoDoc = $GlifoDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGraphometricSign()
    {
        return $this->GraphometricSign;
    }

    /**
     * @param bool $GraphometricSign
     * @return CardOperations
     */
    public function withGraphometricSign($GraphometricSign)
    {
        $new = clone $this;
        $new->GraphometricSign = $GraphometricSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMApprovalRefusal()
    {
        return $this->IMApprovalRefusal;
    }

    /**
     * @param bool $IMApprovalRefusal
     * @return CardOperations
     */
    public function withIMApprovalRefusal($IMApprovalRefusal)
    {
        $new = clone $this;
        $new->IMApprovalRefusal = $IMApprovalRefusal;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMChangeDatePlanSendInvoiceOnMainChannel()
    {
        return $this->IMChangeDatePlanSendInvoiceOnMainChannel;
    }

    /**
     * @param bool $IMChangeDatePlanSendInvoiceOnMainChannel
     * @return CardOperations
     */
    public function withIMChangeDatePlanSendInvoiceOnMainChannel($IMChangeDatePlanSendInvoiceOnMainChannel)
    {
        $new = clone $this;
        $new->IMChangeDatePlanSendInvoiceOnMainChannel = $IMChangeDatePlanSendInvoiceOnMainChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMChangeDatePlanSendInvoiceOnMainChannelPEC()
    {
        return $this->IMChangeDatePlanSendInvoiceOnMainChannelPEC;
    }

    /**
     * @param bool $IMChangeDatePlanSendInvoiceOnMainChannelPEC
     * @return CardOperations
     */
    public function withIMChangeDatePlanSendInvoiceOnMainChannelPEC($IMChangeDatePlanSendInvoiceOnMainChannelPEC)
    {
        $new = clone $this;
        $new->IMChangeDatePlanSendInvoiceOnMainChannelPEC = $IMChangeDatePlanSendInvoiceOnMainChannelPEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMChangeDatePlanSendInvoiceOnMainChannelPEO()
    {
        return $this->IMChangeDatePlanSendInvoiceOnMainChannelPEO;
    }

    /**
     * @param bool $IMChangeDatePlanSendInvoiceOnMainChannelPEO
     * @return CardOperations
     */
    public function withIMChangeDatePlanSendInvoiceOnMainChannelPEO($IMChangeDatePlanSendInvoiceOnMainChannelPEO)
    {
        $new = clone $this;
        $new->IMChangeDatePlanSendInvoiceOnMainChannelPEO = $IMChangeDatePlanSendInvoiceOnMainChannelPEO;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMChangeDatePlanSendInvoiceOnMainChannelSDI()
    {
        return $this->IMChangeDatePlanSendInvoiceOnMainChannelSDI;
    }

    /**
     * @param bool $IMChangeDatePlanSendInvoiceOnMainChannelSDI
     * @return CardOperations
     */
    public function withIMChangeDatePlanSendInvoiceOnMainChannelSDI($IMChangeDatePlanSendInvoiceOnMainChannelSDI)
    {
        $new = clone $this;
        $new->IMChangeDatePlanSendInvoiceOnMainChannelSDI = $IMChangeDatePlanSendInvoiceOnMainChannelSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMChannelSwitching()
    {
        return $this->IMChannelSwitching;
    }

    /**
     * @param bool $IMChannelSwitching
     * @return CardOperations
     */
    public function withIMChannelSwitching($IMChannelSwitching)
    {
        $new = clone $this;
        $new->IMChannelSwitching = $IMChannelSwitching;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMPlanSendInvoiceOnMainChannel()
    {
        return $this->IMPlanSendInvoiceOnMainChannel;
    }

    /**
     * @param bool $IMPlanSendInvoiceOnMainChannel
     * @return CardOperations
     */
    public function withIMPlanSendInvoiceOnMainChannel($IMPlanSendInvoiceOnMainChannel)
    {
        $new = clone $this;
        $new->IMPlanSendInvoiceOnMainChannel = $IMPlanSendInvoiceOnMainChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMPlanSendInvoiceOnMainChannelPEC()
    {
        return $this->IMPlanSendInvoiceOnMainChannelPEC;
    }

    /**
     * @param bool $IMPlanSendInvoiceOnMainChannelPEC
     * @return CardOperations
     */
    public function withIMPlanSendInvoiceOnMainChannelPEC($IMPlanSendInvoiceOnMainChannelPEC)
    {
        $new = clone $this;
        $new->IMPlanSendInvoiceOnMainChannelPEC = $IMPlanSendInvoiceOnMainChannelPEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMPlanSendInvoiceOnMainChannelPEO()
    {
        return $this->IMPlanSendInvoiceOnMainChannelPEO;
    }

    /**
     * @param bool $IMPlanSendInvoiceOnMainChannelPEO
     * @return CardOperations
     */
    public function withIMPlanSendInvoiceOnMainChannelPEO($IMPlanSendInvoiceOnMainChannelPEO)
    {
        $new = clone $this;
        $new->IMPlanSendInvoiceOnMainChannelPEO = $IMPlanSendInvoiceOnMainChannelPEO;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMPlanSendInvoiceOnMainChannelSDI()
    {
        return $this->IMPlanSendInvoiceOnMainChannelSDI;
    }

    /**
     * @param bool $IMPlanSendInvoiceOnMainChannelSDI
     * @return CardOperations
     */
    public function withIMPlanSendInvoiceOnMainChannelSDI($IMPlanSendInvoiceOnMainChannelSDI)
    {
        $new = clone $this;
        $new->IMPlanSendInvoiceOnMainChannelSDI = $IMPlanSendInvoiceOnMainChannelSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMReSendInvoiceOnSubChannel()
    {
        return $this->IMReSendInvoiceOnSubChannel;
    }

    /**
     * @param bool $IMReSendInvoiceOnSubChannel
     * @return CardOperations
     */
    public function withIMReSendInvoiceOnSubChannel($IMReSendInvoiceOnSubChannel)
    {
        $new = clone $this;
        $new->IMReSendInvoiceOnSubChannel = $IMReSendInvoiceOnSubChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMReSendInvoiceOnSubChannelPEC()
    {
        return $this->IMReSendInvoiceOnSubChannelPEC;
    }

    /**
     * @param bool $IMReSendInvoiceOnSubChannelPEC
     * @return CardOperations
     */
    public function withIMReSendInvoiceOnSubChannelPEC($IMReSendInvoiceOnSubChannelPEC)
    {
        $new = clone $this;
        $new->IMReSendInvoiceOnSubChannelPEC = $IMReSendInvoiceOnSubChannelPEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMReSendInvoiceOnSubChannelPEO()
    {
        return $this->IMReSendInvoiceOnSubChannelPEO;
    }

    /**
     * @param bool $IMReSendInvoiceOnSubChannelPEO
     * @return CardOperations
     */
    public function withIMReSendInvoiceOnSubChannelPEO($IMReSendInvoiceOnSubChannelPEO)
    {
        $new = clone $this;
        $new->IMReSendInvoiceOnSubChannelPEO = $IMReSendInvoiceOnSubChannelPEO;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendApprovalRefusalToSDI()
    {
        return $this->IMSendApprovalRefusalToSDI;
    }

    /**
     * @param bool $IMSendApprovalRefusalToSDI
     * @return CardOperations
     */
    public function withIMSendApprovalRefusalToSDI($IMSendApprovalRefusalToSDI)
    {
        $new = clone $this;
        $new->IMSendApprovalRefusalToSDI = $IMSendApprovalRefusalToSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendApprovalToSDI()
    {
        return $this->IMSendApprovalToSDI;
    }

    /**
     * @param bool $IMSendApprovalToSDI
     * @return CardOperations
     */
    public function withIMSendApprovalToSDI($IMSendApprovalToSDI)
    {
        $new = clone $this;
        $new->IMSendApprovalToSDI = $IMSendApprovalToSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnMainChannel()
    {
        return $this->IMSendInvoiceOnMainChannel;
    }

    /**
     * @param bool $IMSendInvoiceOnMainChannel
     * @return CardOperations
     */
    public function withIMSendInvoiceOnMainChannel($IMSendInvoiceOnMainChannel)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnMainChannel = $IMSendInvoiceOnMainChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnMainChannelADP()
    {
        return $this->IMSendInvoiceOnMainChannelADP;
    }

    /**
     * @param bool $IMSendInvoiceOnMainChannelADP
     * @return CardOperations
     */
    public function withIMSendInvoiceOnMainChannelADP($IMSendInvoiceOnMainChannelADP)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnMainChannelADP = $IMSendInvoiceOnMainChannelADP;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnMainChannelPEC()
    {
        return $this->IMSendInvoiceOnMainChannelPEC;
    }

    /**
     * @param bool $IMSendInvoiceOnMainChannelPEC
     * @return CardOperations
     */
    public function withIMSendInvoiceOnMainChannelPEC($IMSendInvoiceOnMainChannelPEC)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnMainChannelPEC = $IMSendInvoiceOnMainChannelPEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnMainChannelPEO()
    {
        return $this->IMSendInvoiceOnMainChannelPEO;
    }

    /**
     * @param bool $IMSendInvoiceOnMainChannelPEO
     * @return CardOperations
     */
    public function withIMSendInvoiceOnMainChannelPEO($IMSendInvoiceOnMainChannelPEO)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnMainChannelPEO = $IMSendInvoiceOnMainChannelPEO;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnMainChannelSDI()
    {
        return $this->IMSendInvoiceOnMainChannelSDI;
    }

    /**
     * @param bool $IMSendInvoiceOnMainChannelSDI
     * @return CardOperations
     */
    public function withIMSendInvoiceOnMainChannelSDI($IMSendInvoiceOnMainChannelSDI)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnMainChannelSDI = $IMSendInvoiceOnMainChannelSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnSubChannel()
    {
        return $this->IMSendInvoiceOnSubChannel;
    }

    /**
     * @param bool $IMSendInvoiceOnSubChannel
     * @return CardOperations
     */
    public function withIMSendInvoiceOnSubChannel($IMSendInvoiceOnSubChannel)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnSubChannel = $IMSendInvoiceOnSubChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnSubChannelADP()
    {
        return $this->IMSendInvoiceOnSubChannelADP;
    }

    /**
     * @param bool $IMSendInvoiceOnSubChannelADP
     * @return CardOperations
     */
    public function withIMSendInvoiceOnSubChannelADP($IMSendInvoiceOnSubChannelADP)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnSubChannelADP = $IMSendInvoiceOnSubChannelADP;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnSubChannelPEC()
    {
        return $this->IMSendInvoiceOnSubChannelPEC;
    }

    /**
     * @param bool $IMSendInvoiceOnSubChannelPEC
     * @return CardOperations
     */
    public function withIMSendInvoiceOnSubChannelPEC($IMSendInvoiceOnSubChannelPEC)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnSubChannelPEC = $IMSendInvoiceOnSubChannelPEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnSubChannelPEO()
    {
        return $this->IMSendInvoiceOnSubChannelPEO;
    }

    /**
     * @param bool $IMSendInvoiceOnSubChannelPEO
     * @return CardOperations
     */
    public function withIMSendInvoiceOnSubChannelPEO($IMSendInvoiceOnSubChannelPEO)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnSubChannelPEO = $IMSendInvoiceOnSubChannelPEO;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendInvoiceOnSubChannelSDI()
    {
        return $this->IMSendInvoiceOnSubChannelSDI;
    }

    /**
     * @param bool $IMSendInvoiceOnSubChannelSDI
     * @return CardOperations
     */
    public function withIMSendInvoiceOnSubChannelSDI($IMSendInvoiceOnSubChannelSDI)
    {
        $new = clone $this;
        $new->IMSendInvoiceOnSubChannelSDI = $IMSendInvoiceOnSubChannelSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMSendRefusalToSDI()
    {
        return $this->IMSendRefusalToSDI;
    }

    /**
     * @param bool $IMSendRefusalToSDI
     * @return CardOperations
     */
    public function withIMSendRefusalToSDI($IMSendRefusalToSDI)
    {
        $new = clone $this;
        $new->IMSendRefusalToSDI = $IMSendRefusalToSDI;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIMStopSendInvoiceOnMainChannel()
    {
        return $this->IMStopSendInvoiceOnMainChannel;
    }

    /**
     * @param bool $IMStopSendInvoiceOnMainChannel
     * @return CardOperations
     */
    public function withIMStopSendInvoiceOnMainChannel($IMStopSendInvoiceOnMainChannel)
    {
        $new = clone $this;
        $new->IMStopSendInvoiceOnMainChannel = $IMStopSendInvoiceOnMainChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getImportAddDoc()
    {
        return $this->ImportAddDoc;
    }

    /**
     * @param bool $ImportAddDoc
     * @return CardOperations
     */
    public function withImportAddDoc($ImportAddDoc)
    {
        $new = clone $this;
        $new->ImportAddDoc = $ImportAddDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getImportDoc()
    {
        return $this->ImportDoc;
    }

    /**
     * @param bool $ImportDoc
     * @return CardOperations
     */
    public function withImportDoc($ImportDoc)
    {
        $new = clone $this;
        $new->ImportDoc = $ImportDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIndexes()
    {
        return $this->Indexes;
    }

    /**
     * @param bool $Indexes
     * @return CardOperations
     */
    public function withIndexes($Indexes)
    {
        $new = clone $this;
        $new->Indexes = $Indexes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getInsModAtt()
    {
        return $this->InsModAtt;
    }

    /**
     * @param bool $InsModAtt
     * @return CardOperations
     */
    public function withInsModAtt($InsModAtt)
    {
        $new = clone $this;
        $new->InsModAtt = $InsModAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getInvalidation()
    {
        return $this->Invalidation;
    }

    /**
     * @param bool $Invalidation
     * @return CardOperations
     */
    public function withInvalidation($Invalidation)
    {
        $new = clone $this;
        $new->Invalidation = $Invalidation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsWf()
    {
        return $this->IsWf;
    }

    /**
     * @param bool $IsWf
     * @return CardOperations
     */
    public function withIsWf($IsWf)
    {
        $new = clone $this;
        $new->IsWf = $IsWf;

        return $new;
    }

    /**
     * @return bool
     */
    public function getLockDoc()
    {
        return $this->LockDoc;
    }

    /**
     * @param bool $LockDoc
     * @return CardOperations
     */
    public function withLockDoc($LockDoc)
    {
        $new = clone $this;
        $new->LockDoc = $LockDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPdfNativeSign()
    {
        return $this->PdfNativeSign;
    }

    /**
     * @param bool $PdfNativeSign
     * @return CardOperations
     */
    public function withPdfNativeSign($PdfNativeSign)
    {
        $new = clone $this;
        $new->PdfNativeSign = $PdfNativeSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPdfNativeSignAtt()
    {
        return $this->PdfNativeSignAtt;
    }

    /**
     * @param bool $PdfNativeSignAtt
     * @return CardOperations
     */
    public function withPdfNativeSignAtt($PdfNativeSignAtt)
    {
        $new = clone $this;
        $new->PdfNativeSignAtt = $PdfNativeSignAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPermalink()
    {
        return $this->Permalink;
    }

    /**
     * @param bool $Permalink
     * @return CardOperations
     */
    public function withPermalink($Permalink)
    {
        $new = clone $this;
        $new->Permalink = $Permalink;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPosteOnLine()
    {
        return $this->PosteOnLine;
    }

    /**
     * @param bool $PosteOnLine
     * @return CardOperations
     */
    public function withPosteOnLine($PosteOnLine)
    {
        $new = clone $this;
        $new->PosteOnLine = $PosteOnLine;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPressMarkDoc()
    {
        return $this->PressMarkDoc;
    }

    /**
     * @param bool $PressMarkDoc
     * @return CardOperations
     */
    public function withPressMarkDoc($PressMarkDoc)
    {
        $new = clone $this;
        $new->PressMarkDoc = $PressMarkDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getProtocolCard()
    {
        return $this->ProtocolCard;
    }

    /**
     * @param bool $ProtocolCard
     * @return CardOperations
     */
    public function withProtocolCard($ProtocolCard)
    {
        $new = clone $this;
        $new->ProtocolCard = $ProtocolCard;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRemoteSign()
    {
        return $this->RemoteSign;
    }

    /**
     * @param bool $RemoteSign
     * @return CardOperations
     */
    public function withRemoteSign($RemoteSign)
    {
        $new = clone $this;
        $new->RemoteSign = $RemoteSign;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRemoteSignAtt()
    {
        return $this->RemoteSignAtt;
    }

    /**
     * @param bool $RemoteSignAtt
     * @return CardOperations
     */
    public function withRemoteSignAtt($RemoteSignAtt)
    {
        $new = clone $this;
        $new->RemoteSignAtt = $RemoteSignAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSaveVersionDoc()
    {
        return $this->SaveVersionDoc;
    }

    /**
     * @param bool $SaveVersionDoc
     * @return CardOperations
     */
    public function withSaveVersionDoc($SaveVersionDoc)
    {
        $new = clone $this;
        $new->SaveVersionDoc = $SaveVersionDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getScanAddDoc()
    {
        return $this->ScanAddDoc;
    }

    /**
     * @param bool $ScanAddDoc
     * @return CardOperations
     */
    public function withScanAddDoc($ScanAddDoc)
    {
        $new = clone $this;
        $new->ScanAddDoc = $ScanAddDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getScanDoc()
    {
        return $this->ScanDoc;
    }

    /**
     * @param bool $ScanDoc
     * @return CardOperations
     */
    public function withScanDoc($ScanDoc)
    {
        $new = clone $this;
        $new->ScanDoc = $ScanDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendExtendedEmail()
    {
        return $this->SendExtendedEmail;
    }

    /**
     * @param bool $SendExtendedEmail
     * @return CardOperations
     */
    public function withSendExtendedEmail($SendExtendedEmail)
    {
        $new = clone $this;
        $new->SendExtendedEmail = $SendExtendedEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendExternalEmail()
    {
        return $this->SendExternalEmail;
    }

    /**
     * @param bool $SendExternalEmail
     * @return CardOperations
     */
    public function withSendExternalEmail($SendExternalEmail)
    {
        $new = clone $this;
        $new->SendExternalEmail = $SendExternalEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendInteropEmail()
    {
        return $this->SendInteropEmail;
    }

    /**
     * @param bool $SendInteropEmail
     * @return CardOperations
     */
    public function withSendInteropEmail($SendInteropEmail)
    {
        $new = clone $this;
        $new->SendInteropEmail = $SendInteropEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendInteropRefuseEmail()
    {
        return $this->SendInteropRefuseEmail;
    }

    /**
     * @param bool $SendInteropRefuseEmail
     * @return CardOperations
     */
    public function withSendInteropRefuseEmail($SendInteropRefuseEmail)
    {
        $new = clone $this;
        $new->SendInteropRefuseEmail = $SendInteropRefuseEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendInvoice()
    {
        return $this->SendInvoice;
    }

    /**
     * @param bool $SendInvoice
     * @return CardOperations
     */
    public function withSendInvoice($SendInvoice)
    {
        $new = clone $this;
        $new->SendInvoice = $SendInvoice;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendNotificationEC()
    {
        return $this->SendNotificationEC;
    }

    /**
     * @param bool $SendNotificationEC
     * @return CardOperations
     */
    public function withSendNotificationEC($SendNotificationEC)
    {
        $new = clone $this;
        $new->SendNotificationEC = $SendNotificationEC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendPECCourtesyCopy()
    {
        return $this->SendPECCourtesyCopy;
    }

    /**
     * @param bool $SendPECCourtesyCopy
     * @return CardOperations
     */
    public function withSendPECCourtesyCopy($SendPECCourtesyCopy)
    {
        $new = clone $this;
        $new->SendPECCourtesyCopy = $SendPECCourtesyCopy;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendPECPEOEmail()
    {
        return $this->SendPECPEOEmail;
    }

    /**
     * @param bool $SendPECPEOEmail
     * @return CardOperations
     */
    public function withSendPECPEOEmail($SendPECPEOEmail)
    {
        $new = clone $this;
        $new->SendPECPEOEmail = $SendPECPEOEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendPECPEOEmailForward()
    {
        return $this->SendPECPEOEmailForward;
    }

    /**
     * @param bool $SendPECPEOEmailForward
     * @return CardOperations
     */
    public function withSendPECPEOEmailForward($SendPECPEOEmailForward)
    {
        $new = clone $this;
        $new->SendPECPEOEmailForward = $SendPECPEOEmailForward;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendPECPEOEmailProtocolReply()
    {
        return $this->SendPECPEOEmailProtocolReply;
    }

    /**
     * @param bool $SendPECPEOEmailProtocolReply
     * @return CardOperations
     */
    public function withSendPECPEOEmailProtocolReply($SendPECPEOEmailProtocolReply)
    {
        $new = clone $this;
        $new->SendPECPEOEmailProtocolReply = $SendPECPEOEmailProtocolReply;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendPECPEOEmailReply()
    {
        return $this->SendPECPEOEmailReply;
    }

    /**
     * @param bool $SendPECPEOEmailReply
     * @return CardOperations
     */
    public function withSendPECPEOEmailReply($SendPECPEOEmailReply)
    {
        $new = clone $this;
        $new->SendPECPEOEmailReply = $SendPECPEOEmailReply;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSharing()
    {
        return $this->Sharing;
    }

    /**
     * @param bool $Sharing
     * @return CardOperations
     */
    public function withSharing($Sharing)
    {
        $new = clone $this;
        $new->Sharing = $Sharing;

        return $new;
    }

    /**
     * @return bool
     */
    public function getStandardCollation()
    {
        return $this->StandardCollation;
    }

    /**
     * @param bool $StandardCollation
     * @return CardOperations
     */
    public function withStandardCollation($StandardCollation)
    {
        $new = clone $this;
        $new->StandardCollation = $StandardCollation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getStoreInteropEmail()
    {
        return $this->StoreInteropEmail;
    }

    /**
     * @param bool $StoreInteropEmail
     * @return CardOperations
     */
    public function withStoreInteropEmail($StoreInteropEmail)
    {
        $new = clone $this;
        $new->StoreInteropEmail = $StoreInteropEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getStorePECPEOEmail()
    {
        return $this->StorePECPEOEmail;
    }

    /**
     * @param bool $StorePECPEOEmail
     * @return CardOperations
     */
    public function withStorePECPEOEmail($StorePECPEOEmail)
    {
        $new = clone $this;
        $new->StorePECPEOEmail = $StorePECPEOEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getTaskOnDemand()
    {
        return $this->TaskOnDemand;
    }

    /**
     * @param bool $TaskOnDemand
     * @return CardOperations
     */
    public function withTaskOnDemand($TaskOnDemand)
    {
        $new = clone $this;
        $new->TaskOnDemand = $TaskOnDemand;

        return $new;
    }

    /**
     * @return bool
     */
    public function getTimeStamp()
    {
        return $this->TimeStamp;
    }

    /**
     * @param bool $TimeStamp
     * @return CardOperations
     */
    public function withTimeStamp($TimeStamp)
    {
        $new = clone $this;
        $new->TimeStamp = $TimeStamp;

        return $new;
    }

    /**
     * @return bool
     */
    public function getTimeStampAtt()
    {
        return $this->TimeStampAtt;
    }

    /**
     * @param bool $TimeStampAtt
     * @return CardOperations
     */
    public function withTimeStampAtt($TimeStampAtt)
    {
        $new = clone $this;
        $new->TimeStampAtt = $TimeStampAtt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVisibility()
    {
        return $this->Visibility;
    }

    /**
     * @param bool $Visibility
     * @return CardOperations
     */
    public function withVisibility($Visibility)
    {
        $new = clone $this;
        $new->Visibility = $Visibility;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfAssignInChargeTo()
    {
        return $this->WfAssignInChargeTo;
    }

    /**
     * @param bool $WfAssignInChargeTo
     * @return CardOperations
     */
    public function withWfAssignInChargeTo($WfAssignInChargeTo)
    {
        $new = clone $this;
        $new->WfAssignInChargeTo = $WfAssignInChargeTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfForward()
    {
        return $this->WfForward;
    }

    /**
     * @param bool $WfForward
     * @return CardOperations
     */
    public function withWfForward($WfForward)
    {
        $new = clone $this;
        $new->WfForward = $WfForward;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfProcessInfo()
    {
        return $this->WfProcessInfo;
    }

    /**
     * @param bool $WfProcessInfo
     * @return CardOperations
     */
    public function withWfProcessInfo($WfProcessInfo)
    {
        $new = clone $this;
        $new->WfProcessInfo = $WfProcessInfo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfProcessRestore()
    {
        return $this->WfProcessRestore;
    }

    /**
     * @param bool $WfProcessRestore
     * @return CardOperations
     */
    public function withWfProcessRestore($WfProcessRestore)
    {
        $new = clone $this;
        $new->WfProcessRestore = $WfProcessRestore;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfProcessStart()
    {
        return $this->WfProcessStart;
    }

    /**
     * @param bool $WfProcessStart
     * @return CardOperations
     */
    public function withWfProcessStart($WfProcessStart)
    {
        $new = clone $this;
        $new->WfProcessStart = $WfProcessStart;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfProcessStop()
    {
        return $this->WfProcessStop;
    }

    /**
     * @param bool $WfProcessStop
     * @return CardOperations
     */
    public function withWfProcessStop($WfProcessStop)
    {
        $new = clone $this;
        $new->WfProcessStop = $WfProcessStop;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfProcessSuspend()
    {
        return $this->WfProcessSuspend;
    }

    /**
     * @param bool $WfProcessSuspend
     * @return CardOperations
     */
    public function withWfProcessSuspend($WfProcessSuspend)
    {
        $new = clone $this;
        $new->WfProcessSuspend = $WfProcessSuspend;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfRefuse()
    {
        return $this->WfRefuse;
    }

    /**
     * @param bool $WfRefuse
     * @return CardOperations
     */
    public function withWfRefuse($WfRefuse)
    {
        $new = clone $this;
        $new->WfRefuse = $WfRefuse;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfRemoveInChargeFrom()
    {
        return $this->WfRemoveInChargeFrom;
    }

    /**
     * @param bool $WfRemoveInChargeFrom
     * @return CardOperations
     */
    public function withWfRemoveInChargeFrom($WfRemoveInChargeFrom)
    {
        $new = clone $this;
        $new->WfRemoveInChargeFrom = $WfRemoveInChargeFrom;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWfTakeInCharge()
    {
        return $this->WfTakeInCharge;
    }

    /**
     * @param bool $WfTakeInCharge
     * @return CardOperations
     */
    public function withWfTakeInCharge($WfTakeInCharge)
    {
        $new = clone $this;
        $new->WfTakeInCharge = $WfTakeInCharge;

        return $new;
    }


}

