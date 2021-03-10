<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SAPRegisterInvoiceResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RegisterInvoiceOutput
     */
    private $SAP_RegisterInvoiceResult = null;

    /**
     * @return \ArchiflowWSCard\Type\RegisterInvoiceOutput
     */
    public function getSAP_RegisterInvoiceResult()
    {
        return $this->SAP_RegisterInvoiceResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\RegisterInvoiceOutput $SAP_RegisterInvoiceResult
     * @return SAPRegisterInvoiceResponse
     */
    public function withSAP_RegisterInvoiceResult($SAP_RegisterInvoiceResult)
    {
        $new = clone $this;
        $new->SAP_RegisterInvoiceResult = $SAP_RegisterInvoiceResult;

        return $new;
    }


}

