<?php

namespace DocsuiteWS;

use DocsuiteWS\Type;
use Phpro\SoapClient\Soap\ClassMap\ClassMapCollection;
use Phpro\SoapClient\Soap\ClassMap\ClassMap;

class DocsuiteWSClassmap
{

    public static function getCollection() : \Phpro\SoapClient\Soap\ClassMap\ClassMapCollection
    {
        return new ClassMapCollection([
            new ClassMap('Insert', Type\Insert::class),
            new ClassMap('InsertResponse', Type\InsertResponse::class),
            new ClassMap('AddDocument', Type\AddDocument::class),
            new ClassMap('AddDocumentResponse', Type\AddDocumentResponse::class),
            new ClassMap('InsertCommit', Type\InsertCommit::class),
            new ClassMap('InsertCommitResponse', Type\InsertCommitResponse::class),
            new ClassMap('GetProtocolLink', Type\GetProtocolLink::class),
            new ClassMap('GetProtocolLinkResponse', Type\GetProtocolLinkResponse::class),
            new ClassMap('GetDocumentsViewerLink', Type\GetDocumentsViewerLink::class),
            new ClassMap('GetDocumentsViewerLinkResponse', Type\GetDocumentsViewerLinkResponse::class),
            new ClassMap('GetPecs', Type\GetPecs::class),
            new ClassMap('GetPecsResponse', Type\GetPecsResponse::class),
            new ClassMap('SetProtocolStatus', Type\SetProtocolStatus::class),
            new ClassMap('SetProtocolStatusResponse', Type\SetProtocolStatusResponse::class),
            new ClassMap('GetProtocolStatuses', Type\GetProtocolStatuses::class),
            new ClassMap('GetProtocolStatusesResponse', Type\GetProtocolStatusesResponse::class),
            new ClassMap('GetProtocolInfo', Type\GetProtocolInfo::class),
            new ClassMap('GetProtocolInfoResponse', Type\GetProtocolInfoResponse::class),
            new ClassMap('GetContact', Type\GetContact::class),
            new ClassMap('GetContactResponse', Type\GetContactResponse::class),
        ]);
    }


}

