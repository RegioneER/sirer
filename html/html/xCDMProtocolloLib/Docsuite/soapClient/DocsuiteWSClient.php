<?php

namespace DocsuiteWS;

use DocsuiteWS\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class DocsuiteWSClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\Insert $parameters
     * @return ResultInterface|Type\InsertResponse
     * @throws SoapException
     */
    public function insert(\DocsuiteWS\Type\Insert $parameters) : \DocsuiteWS\Type\InsertResponse
    {
        return $this->call('Insert', $parameters);
    }

    /**
     * @param RequestInterface|Type\AddDocument $parameters
     * @return ResultInterface|Type\AddDocumentResponse
     * @throws SoapException
     */
    public function addDocument(\DocsuiteWS\Type\AddDocument $parameters) : \DocsuiteWS\Type\AddDocumentResponse
    {
        return $this->call('AddDocument', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCommit $parameters
     * @return ResultInterface|Type\InsertCommitResponse
     * @throws SoapException
     */
    public function insertCommit(\DocsuiteWS\Type\InsertCommit $parameters) : \DocsuiteWS\Type\InsertCommitResponse
    {
        return $this->call('InsertCommit', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetProtocolLink $parameters
     * @return ResultInterface|Type\GetProtocolLinkResponse
     * @throws SoapException
     */
    public function getProtocolLink(\DocsuiteWS\Type\GetProtocolLink $parameters) : \DocsuiteWS\Type\GetProtocolLinkResponse
    {
        return $this->call('GetProtocolLink', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDocumentsViewerLink $parameters
     * @return ResultInterface|Type\GetDocumentsViewerLinkResponse
     * @throws SoapException
     */
    public function getDocumentsViewerLink(\DocsuiteWS\Type\GetDocumentsViewerLink $parameters) : \DocsuiteWS\Type\GetDocumentsViewerLinkResponse
    {
        return $this->call('GetDocumentsViewerLink', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetPecs $parameters
     * @return ResultInterface|Type\GetPecsResponse
     * @throws SoapException
     */
    public function getPecs(\DocsuiteWS\Type\GetPecs $parameters) : \DocsuiteWS\Type\GetPecsResponse
    {
        return $this->call('GetPecs', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetProtocolStatus $parameters
     * @return ResultInterface|Type\SetProtocolStatusResponse
     * @throws SoapException
     */
    public function setProtocolStatus(\DocsuiteWS\Type\SetProtocolStatus $parameters) : \DocsuiteWS\Type\SetProtocolStatusResponse
    {
        return $this->call('SetProtocolStatus', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetProtocolStatuses $parameters
     * @return ResultInterface|Type\GetProtocolStatusesResponse
     * @throws SoapException
     */
    public function getProtocolStatuses(\DocsuiteWS\Type\GetProtocolStatuses $parameters) : \DocsuiteWS\Type\GetProtocolStatusesResponse
    {
        return $this->call('GetProtocolStatuses', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetProtocolInfo $parameters
     * @return ResultInterface|Type\GetProtocolInfoResponse
     * @throws SoapException
     */
    public function getProtocolInfo(\DocsuiteWS\Type\GetProtocolInfo $parameters) : \DocsuiteWS\Type\GetProtocolInfoResponse
    {
        return $this->call('GetProtocolInfo', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetContact $parameters
     * @return ResultInterface|Type\GetContactResponse
     * @throws SoapException
     */
    public function getContact(\DocsuiteWS\Type\GetContact $parameters) : \DocsuiteWS\Type\GetContactResponse
    {
        return $this->call('GetContact', $parameters);
    }


}

