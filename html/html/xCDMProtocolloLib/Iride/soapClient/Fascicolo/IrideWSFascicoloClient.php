<?php

namespace IrideWFFascicolo;

use IrideWFFascicolo\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class IrideWSFascicoloClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\FascicolaDocumento $parameters
     * @return ResultInterface|Type\FascicolaDocumentoResponse
     * @throws SoapException
     */
    public function fascicolaDocumento(\IrideWFFascicolo\Type\FascicolaDocumento $parameters) : \IrideWFFascicolo\Type\FascicolaDocumentoResponse
    {
        return $this->call('FascicolaDocumento', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaFascicolo $parameters
     * @return ResultInterface|Type\CreaFascicoloResponse
     * @throws SoapException
     */
    public function creaFascicolo(\IrideWFFascicolo\Type\CreaFascicolo $parameters) : \IrideWFFascicolo\Type\CreaFascicoloResponse
    {
        return $this->call('CreaFascicolo', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaSottoFascicolo $parameters
     * @return ResultInterface|Type\CreaSottoFascicoloResponse
     * @throws SoapException
     */
    public function creaSottoFascicolo(\IrideWFFascicolo\Type\CreaSottoFascicolo $parameters) : \IrideWFFascicolo\Type\CreaSottoFascicoloResponse
    {
        return $this->call('CreaSottoFascicolo', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiFascicolo $parameters
     * @return ResultInterface|Type\LeggiFascicoloResponse
     * @throws SoapException
     */
    public function leggiFascicolo(\IrideWFFascicolo\Type\LeggiFascicolo $parameters) : \IrideWFFascicolo\Type\LeggiFascicoloResponse
    {
        return $this->call('LeggiFascicolo', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaFascicoloString $parameters
     * @return ResultInterface|Type\CreaFascicoloStringResponse
     * @throws SoapException
     */
    public function creaFascicoloString(\IrideWFFascicolo\Type\CreaFascicoloString $parameters) : \IrideWFFascicolo\Type\CreaFascicoloStringResponse
    {
        return $this->call('CreaFascicoloString', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaSottoFascicoloString $parameters
     * @return ResultInterface|Type\CreaSottoFascicoloStringResponse
     * @throws SoapException
     */
    public function creaSottoFascicoloString(\IrideWFFascicolo\Type\CreaSottoFascicoloString $parameters) : \IrideWFFascicolo\Type\CreaSottoFascicoloStringResponse
    {
        return $this->call('CreaSottoFascicoloString', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiFascicoloString $parameters
     * @return ResultInterface|Type\LeggiFascicoloStringResponse
     * @throws SoapException
     */
    public function leggiFascicoloString(\IrideWFFascicolo\Type\LeggiFascicoloString $parameters) : \IrideWFFascicolo\Type\LeggiFascicoloStringResponse
    {
        return $this->call('LeggiFascicoloString', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciMetadati $parameters
     * @return ResultInterface|Type\InserisciMetadatiResponse
     * @throws SoapException
     */
    public function inserisciMetadati(\IrideWFFascicolo\Type\InserisciMetadati $parameters) : \IrideWFFascicolo\Type\InserisciMetadatiResponse
    {
        return $this->call('InserisciMetadati', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModificaFascicolo $parameters
     * @return ResultInterface|Type\ModificaFascicoloResponse
     * @throws SoapException
     */
    public function modificaFascicolo(\IrideWFFascicolo\Type\ModificaFascicolo $parameters) : \IrideWFFascicolo\Type\ModificaFascicoloResponse
    {
        return $this->call('ModificaFascicolo', $parameters);
    }


}

