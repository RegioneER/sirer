<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardOperationsFromList implements RequestInterface
{

    /**
     * @var bool
     */
    private $ArchivalCollation = null;

    /**
     * @var bool
     */
    private $Cancellation = null;

    /**
     * @var bool
     */
    private $DigitalSign = null;

    /**
     * @var bool
     */
    private $GraphometricSign = null;

    /**
     * @var bool
     */
    private $PdfNativeSign = null;

    /**
     * @var bool
     */
    private $RemoteSign = null;

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
    private $Sharing = null;

    /**
     * @var bool
     */
    private $StandardCollation = null;

    /**
     * @var bool
     */
    private $TimeStamp = null;

    /**
     * @var bool
     */
    private $WfForward = null;

    /**
     * @var bool
     */
    private $WfRefuse = null;

    /**
     * @var bool
     */
    private $WfTakeInCharge = null;

    /**
     * Constructor
     *
     * @var bool $ArchivalCollation
     * @var bool $Cancellation
     * @var bool $DigitalSign
     * @var bool $GraphometricSign
     * @var bool $PdfNativeSign
     * @var bool $RemoteSign
     * @var bool $SendExtendedEmail
     * @var bool $SendExternalEmail
     * @var bool $Sharing
     * @var bool $StandardCollation
     * @var bool $TimeStamp
     * @var bool $WfForward
     * @var bool $WfRefuse
     * @var bool $WfTakeInCharge
     */
    public function __construct($ArchivalCollation, $Cancellation, $DigitalSign, $GraphometricSign, $PdfNativeSign, $RemoteSign, $SendExtendedEmail, $SendExternalEmail, $Sharing, $StandardCollation, $TimeStamp, $WfForward, $WfRefuse, $WfTakeInCharge)
    {
        $this->ArchivalCollation = $ArchivalCollation;
        $this->Cancellation = $Cancellation;
        $this->DigitalSign = $DigitalSign;
        $this->GraphometricSign = $GraphometricSign;
        $this->PdfNativeSign = $PdfNativeSign;
        $this->RemoteSign = $RemoteSign;
        $this->SendExtendedEmail = $SendExtendedEmail;
        $this->SendExternalEmail = $SendExternalEmail;
        $this->Sharing = $Sharing;
        $this->StandardCollation = $StandardCollation;
        $this->TimeStamp = $TimeStamp;
        $this->WfForward = $WfForward;
        $this->WfRefuse = $WfRefuse;
        $this->WfTakeInCharge = $WfTakeInCharge;
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
     * @return CardOperationsFromList
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
    public function getCancellation()
    {
        return $this->Cancellation;
    }

    /**
     * @param bool $Cancellation
     * @return CardOperationsFromList
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
    public function getDigitalSign()
    {
        return $this->DigitalSign;
    }

    /**
     * @param bool $DigitalSign
     * @return CardOperationsFromList
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
    public function getGraphometricSign()
    {
        return $this->GraphometricSign;
    }

    /**
     * @param bool $GraphometricSign
     * @return CardOperationsFromList
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
    public function getPdfNativeSign()
    {
        return $this->PdfNativeSign;
    }

    /**
     * @param bool $PdfNativeSign
     * @return CardOperationsFromList
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
    public function getRemoteSign()
    {
        return $this->RemoteSign;
    }

    /**
     * @param bool $RemoteSign
     * @return CardOperationsFromList
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
    public function getSendExtendedEmail()
    {
        return $this->SendExtendedEmail;
    }

    /**
     * @param bool $SendExtendedEmail
     * @return CardOperationsFromList
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
     * @return CardOperationsFromList
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
    public function getSharing()
    {
        return $this->Sharing;
    }

    /**
     * @param bool $Sharing
     * @return CardOperationsFromList
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
     * @return CardOperationsFromList
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
    public function getTimeStamp()
    {
        return $this->TimeStamp;
    }

    /**
     * @param bool $TimeStamp
     * @return CardOperationsFromList
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
    public function getWfForward()
    {
        return $this->WfForward;
    }

    /**
     * @param bool $WfForward
     * @return CardOperationsFromList
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
    public function getWfRefuse()
    {
        return $this->WfRefuse;
    }

    /**
     * @param bool $WfRefuse
     * @return CardOperationsFromList
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
    public function getWfTakeInCharge()
    {
        return $this->WfTakeInCharge;
    }

    /**
     * @param bool $WfTakeInCharge
     * @return CardOperationsFromList
     */
    public function withWfTakeInCharge($WfTakeInCharge)
    {
        $new = clone $this;
        $new->WfTakeInCharge = $WfTakeInCharge;

        return $new;
    }


}

