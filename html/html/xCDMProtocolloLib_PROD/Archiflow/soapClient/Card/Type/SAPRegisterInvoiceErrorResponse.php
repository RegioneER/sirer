<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SAPRegisterInvoiceErrorResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RegisterInvoiceErrorOutput
     */
    private $SAP_RegisterInvoiceErrorResult = null;

    /**
     * @return \ArchiflowWSCard\Type\RegisterInvoiceErrorOutput
     */
    public function getSAP_RegisterInvoiceErrorResult()
    {
        return $this->SAP_RegisterInvoiceErrorResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\RegisterInvoiceErrorOutput
     * $SAP_RegisterInvoiceErrorResult
     * @return SAPRegisterInvoiceErrorResponse
     */
    public function withSAP_RegisterInvoiceErrorResult($SAP_RegisterInvoiceErrorResult)
    {
        $new = clone $this;
        $new->SAP_RegisterInvoiceErrorResult = $SAP_RegisterInvoiceErrorResult;

        return $new;
    }


}

