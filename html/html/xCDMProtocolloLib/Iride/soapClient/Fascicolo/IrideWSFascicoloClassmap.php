<?php

namespace IrideWFFascicolo;

use IrideWFFascicolo\Type;
use Phpro\SoapClient\Soap\ClassMap\ClassMapCollection;
use Phpro\SoapClient\Soap\ClassMap\ClassMap;

class IrideWSFascicoloClassmap
{

    public static function getCollection() : \Phpro\SoapClient\Soap\ClassMap\ClassMapCollection
    {
        return new ClassMapCollection([
            new ClassMap('FascicolaDocumento', Type\FascicolaDocumento::class),
            new ClassMap('FascicolaDocumentoResponse', Type\FascicolaDocumentoResponse::class),
            new ClassMap('EsitoOperazione', Type\EsitoOperazione::class),
            new ClassMap('CreaFascicolo', Type\CreaFascicolo::class),
            new ClassMap('FascicoloIn', Type\FascicoloIn::class),
            new ClassMap('CreaFascicoloResponse', Type\CreaFascicoloResponse::class),
            new ClassMap('DocumentoFascicoloOut', Type\DocumentoFascicoloOut::class),
            new ClassMap('ArrayOfDocumentoFascicoloOut', Type\ArrayOfDocumentoFascicoloOut::class),
            new ClassMap('FascicoloOut', Type\FascicoloOut::class),
            new ClassMap('CreaSottoFascicolo', Type\CreaSottoFascicolo::class),
            new ClassMap('CreaSottoFascicoloResponse', Type\CreaSottoFascicoloResponse::class),
            new ClassMap('LeggiFascicolo', Type\LeggiFascicolo::class),
            new ClassMap('LeggiFascicoloResponse', Type\LeggiFascicoloResponse::class),
            new ClassMap('CreaFascicoloString', Type\CreaFascicoloString::class),
            new ClassMap('CreaFascicoloStringResponse', Type\CreaFascicoloStringResponse::class),
            new ClassMap('CreaSottoFascicoloString', Type\CreaSottoFascicoloString::class),
            new ClassMap('CreaSottoFascicoloStringResponse', Type\CreaSottoFascicoloStringResponse::class),
            new ClassMap('LeggiFascicoloString', Type\LeggiFascicoloString::class),
            new ClassMap('LeggiFascicoloStringResponse', Type\LeggiFascicoloStringResponse::class),
            new ClassMap('InserisciMetadati', Type\InserisciMetadati::class),
            new ClassMap('InserisciMetadatiResponse', Type\InserisciMetadatiResponse::class),
            new ClassMap('ModificaFascicolo', Type\ModificaFascicolo::class),
            new ClassMap('ModificaFascicoloResponse', Type\ModificaFascicoloResponse::class),
        ]);
    }


}

