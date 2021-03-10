<?php

namespace IrideWS;

use IrideWS\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class IrideWSClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\LeggiProtocollo $parameters
     * @return ResultInterface|Type\LeggiProtocolloResponse
     * @throws SoapException
     */
    public function leggiProtocollo(\IrideWS\Type\LeggiProtocollo $parameters) : \IrideWS\Type\LeggiProtocolloResponse
    {
        return $this->call('LeggiProtocollo', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiDocumento $parameters
     * @return ResultInterface|Type\LeggiDocumentoResponse
     * @throws SoapException
     */
    public function leggiDocumento(\IrideWS\Type\LeggiDocumento $parameters) : \IrideWS\Type\LeggiDocumentoResponse
    {
        return $this->call('LeggiDocumento', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciProtocolloEAnagrafiche $parameters
     * @return ResultInterface|Type\InserisciProtocolloEAnagraficheResponse
     * @throws SoapException
     */
    public function inserisciProtocolloEAnagrafiche(\IrideWS\Type\InserisciProtocolloEAnagrafiche $parameters) : \IrideWS\Type\InserisciProtocolloEAnagraficheResponse
    {
        return $this->call('InserisciProtocolloEAnagrafiche', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciDocumentoEAnagrafiche $parameters
     * @return ResultInterface|Type\InserisciDocumentoEAnagraficheResponse
     * @throws SoapException
     */
    public function inserisciDocumentoEAnagrafiche(\IrideWS\Type\InserisciDocumentoEAnagrafiche $parameters) : \IrideWS\Type\InserisciDocumentoEAnagraficheResponse
    {
        return $this->call('InserisciDocumentoEAnagrafiche', $parameters);
    }

    /**
     * @param RequestInterface|Type\AggiungiAllegati $parameters
     * @return ResultInterface|Type\AggiungiAllegatiResponse
     * @throws SoapException
     */
    public function aggiungiAllegati(\IrideWS\Type\AggiungiAllegati $parameters) : \IrideWS\Type\AggiungiAllegatiResponse
    {
        return $this->call('AggiungiAllegati', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiProtocolloMultiDB $parameters
     * @return ResultInterface|Type\LeggiProtocolloMultiDBResponse
     * @throws SoapException
     */
    public function leggiProtocolloMultiDB(\IrideWS\Type\LeggiProtocolloMultiDB $parameters) : \IrideWS\Type\LeggiProtocolloMultiDBResponse
    {
        return $this->call('LeggiProtocolloMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiDocumentoMultiDB $parameters
     * @return ResultInterface|Type\LeggiDocumentoMultiDBResponse
     * @throws SoapException
     */
    public function leggiDocumentoMultiDB(\IrideWS\Type\LeggiDocumentoMultiDB $parameters) : \IrideWS\Type\LeggiDocumentoMultiDBResponse
    {
        return $this->call('LeggiDocumentoMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciProtocolloEAnagraficheMultiDB $parameters
     * @return ResultInterface|Type\InserisciProtocolloEAnagraficheMultiDBResponse
     * @throws SoapException
     */
    public function inserisciProtocolloEAnagraficheMultiDB(\IrideWS\Type\InserisciProtocolloEAnagraficheMultiDB $parameters) : \IrideWS\Type\InserisciProtocolloEAnagraficheMultiDBResponse
    {
        return $this->call('InserisciProtocolloEAnagraficheMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciDocumentoEAnagraficheMultiDB $parameters
     * @return ResultInterface|Type\InserisciDocumentoEAnagraficheMultiDBResponse
     * @throws SoapException
     */
    public function inserisciDocumentoEAnagraficheMultiDB(\IrideWS\Type\InserisciDocumentoEAnagraficheMultiDB $parameters) : \IrideWS\Type\InserisciDocumentoEAnagraficheMultiDBResponse
    {
        return $this->call('InserisciDocumentoEAnagraficheMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\AggiungiAllegatiMultiDB $parameters
     * @return ResultInterface|Type\AggiungiAllegatiMultiDBResponse
     * @throws SoapException
     */
    public function aggiungiAllegatiMultiDB(\IrideWS\Type\AggiungiAllegatiMultiDB $parameters) : \IrideWS\Type\AggiungiAllegatiMultiDBResponse
    {
        return $this->call('AggiungiAllegatiMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\Login $parameters
     * @return ResultInterface|Type\LoginResponse
     * @throws SoapException
     */
    public function login(\IrideWS\Type\Login $parameters) : \IrideWS\Type\LoginResponse
    {
        return $this->call('Login', $parameters);
    }

    /**
     * @param RequestInterface|Type\LoginMultiDB $parameters
     * @return ResultInterface|Type\LoginMultiDBResponse
     * @throws SoapException
     */
    public function loginMultiDB(\IrideWS\Type\LoginMultiDB $parameters) : \IrideWS\Type\LoginMultiDBResponse
    {
        return $this->call('LoginMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\RicercaAmministrazione $parameters
     * @return ResultInterface|Type\RicercaAmministrazioneResponse
     * @throws SoapException
     */
    public function ricercaAmministrazione(\IrideWS\Type\RicercaAmministrazione $parameters) : \IrideWS\Type\RicercaAmministrazioneResponse
    {
        return $this->call('RicercaAmministrazione', $parameters);
    }

    /**
     * @param RequestInterface|Type\RicercaAmministrazioneMultiDB $parameters
     * @return ResultInterface|Type\RicercaAmministrazioneMultiDBResponse
     * @throws SoapException
     */
    public function ricercaAmministrazioneMultiDB(\IrideWS\Type\RicercaAmministrazioneMultiDB $parameters) : \IrideWS\Type\RicercaAmministrazioneMultiDBResponse
    {
        return $this->call('RicercaAmministrazioneMultiDB', $parameters);
    }

    /**
     * @param RequestInterface|Type\AggiungiAllegati2 $parameters
     * @return ResultInterface|Type\AggiungiAllegati2Response
     * @throws SoapException
     */
    public function aggiungiAllegati2(\IrideWS\Type\AggiungiAllegati2 $parameters) : \IrideWS\Type\AggiungiAllegati2Response
    {
        return $this->call('AggiungiAllegati2', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciDocumentoDaDM $parameters
     * @return ResultInterface|Type\InserisciDocumentoDaDMResponse
     * @throws SoapException
     */
    public function inserisciDocumentoDaDM(\IrideWS\Type\InserisciDocumentoDaDM $parameters) : \IrideWS\Type\InserisciDocumentoDaDMResponse
    {
        return $this->call('InserisciDocumentoDaDM', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModificaDocumentoEAnagrafiche $parameters
     * @return ResultInterface|Type\ModificaDocumentoEAnagraficheResponse
     * @throws SoapException
     */
    public function modificaDocumentoEAnagrafiche(\IrideWS\Type\ModificaDocumentoEAnagrafiche $parameters) : \IrideWS\Type\ModificaDocumentoEAnagraficheResponse
    {
        return $this->call('ModificaDocumentoEAnagrafiche', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaCopie $parameters
     * @return ResultInterface|Type\CreaCopieResponse
     * @throws SoapException
     */
    public function creaCopie(\IrideWS\Type\CreaCopie $parameters) : \IrideWS\Type\CreaCopieResponse
    {
        return $this->call('CreaCopie', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiBarcode $parameters
     * @return ResultInterface|Type\LeggiBarcodeResponse
     * @throws SoapException
     */
    public function leggiBarcode(\IrideWS\Type\LeggiBarcode $parameters) : \IrideWS\Type\LeggiBarcodeResponse
    {
        return $this->call('LeggiBarcode', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiDocumentoString $parameters
     * @return ResultInterface|Type\LeggiDocumentoStringResponse
     * @throws SoapException
     */
    public function leggiDocumentoString(\IrideWS\Type\LeggiDocumentoString $parameters) : \IrideWS\Type\LeggiDocumentoStringResponse
    {
        return $this->call('LeggiDocumentoString', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiProtocolloString $parameters
     * @return ResultInterface|Type\LeggiProtocolloStringResponse
     * @throws SoapException
     */
    public function leggiProtocolloString(\IrideWS\Type\LeggiProtocolloString $parameters) : \IrideWS\Type\LeggiProtocolloStringResponse
    {
        return $this->call('LeggiProtocolloString', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiBarcodeString $parameters
     * @return ResultInterface|Type\LeggiBarcodeStringResponse
     * @throws SoapException
     */
    public function leggiBarcodeString(\IrideWS\Type\LeggiBarcodeString $parameters) : \IrideWS\Type\LeggiBarcodeStringResponse
    {
        return $this->call('LeggiBarcodeString', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciDocumentoEAnagraficheString $parameters
     * @return ResultInterface|Type\InserisciDocumentoEAnagraficheStringResponse
     * @throws SoapException
     */
    public function inserisciDocumentoEAnagraficheString(\IrideWS\Type\InserisciDocumentoEAnagraficheString $parameters) : \IrideWS\Type\InserisciDocumentoEAnagraficheStringResponse
    {
        return $this->call('InserisciDocumentoEAnagraficheString', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciProtocolloEAnagraficheString $parameters
     * @return ResultInterface|Type\InserisciProtocolloEAnagraficheStringResponse
     * @throws SoapException
     */
    public function inserisciProtocolloEAnagraficheString(\IrideWS\Type\InserisciProtocolloEAnagraficheString $parameters) : \IrideWS\Type\InserisciProtocolloEAnagraficheStringResponse
    {
        return $this->call('InserisciProtocolloEAnagraficheString', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModificaDocumentoEAnagraficheString $parameters
     * @return ResultInterface|Type\ModificaDocumentoEAnagraficheStringResponse
     * @throws SoapException
     */
    public function modificaDocumentoEAnagraficheString(\IrideWS\Type\ModificaDocumentoEAnagraficheString $parameters) : \IrideWS\Type\ModificaDocumentoEAnagraficheStringResponse
    {
        return $this->call('ModificaDocumentoEAnagraficheString', $parameters);
    }

    /**
     * @param RequestInterface|Type\RicercaPerCodiceFiscaleString $parameters
     * @return ResultInterface|Type\RicercaPerCodiceFiscaleStringResponse
     * @throws SoapException
     */
    public function ricercaPerCodiceFiscaleString(\IrideWS\Type\RicercaPerCodiceFiscaleString $parameters) : \IrideWS\Type\RicercaPerCodiceFiscaleStringResponse
    {
        return $this->call('RicercaPerCodiceFiscaleString', $parameters);
    }

    /**
     * @param RequestInterface|Type\AggiungiAllegatiString $parameters
     * @return ResultInterface|Type\AggiungiAllegatiStringResponse
     * @throws SoapException
     */
    public function aggiungiAllegatiString(\IrideWS\Type\AggiungiAllegatiString $parameters) : \IrideWS\Type\AggiungiAllegatiStringResponse
    {
        return $this->call('AggiungiAllegatiString', $parameters);
    }

    /**
     * @param RequestInterface|Type\CreaCopieString $parameters
     * @return ResultInterface|Type\CreaCopieStringResponse
     * @throws SoapException
     */
    public function creaCopieString(\IrideWS\Type\CreaCopieString $parameters) : \IrideWS\Type\CreaCopieStringResponse
    {
        return $this->call('CreaCopieString', $parameters);
    }

    /**
     * @param RequestInterface|Type\PubblicazioneDocumento $parameters
     * @return ResultInterface|Type\PubblicazioneDocumentoResponse
     * @throws SoapException
     */
    public function pubblicazioneDocumento(\IrideWS\Type\PubblicazioneDocumento $parameters) : \IrideWS\Type\PubblicazioneDocumentoResponse
    {
        return $this->call('PubblicazioneDocumento', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiAnagrafica $parameters
     * @return ResultInterface|Type\LeggiAnagraficaResponse
     * @throws SoapException
     */
    public function leggiAnagrafica(\IrideWS\Type\LeggiAnagrafica $parameters) : \IrideWS\Type\LeggiAnagraficaResponse
    {
        return $this->call('LeggiAnagrafica', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiCopie $parameters
     * @return ResultInterface|Type\LeggiCopieResponse
     * @throws SoapException
     */
    public function leggiCopie(\IrideWS\Type\LeggiCopie $parameters) : \IrideWS\Type\LeggiCopieResponse
    {
        return $this->call('LeggiCopie', $parameters);
    }

    /**
     * @param RequestInterface|Type\EliminaAllegato $parameters
     * @return ResultInterface|Type\EliminaAllegatoResponse
     * @throws SoapException
     */
    public function eliminaAllegato(\IrideWS\Type\EliminaAllegato $parameters) : \IrideWS\Type\EliminaAllegatoResponse
    {
        return $this->call('EliminaAllegato', $parameters);
    }

    /**
     * @param RequestInterface|Type\AnnullaDocumento $parameters
     * @return ResultInterface|Type\AnnullaDocumentoResponse
     * @throws SoapException
     */
    public function annullaDocumento(\IrideWS\Type\AnnullaDocumento $parameters) : \IrideWS\Type\AnnullaDocumentoResponse
    {
        return $this->call('AnnullaDocumento', $parameters);
    }

    /**
     * @param RequestInterface|Type\CollegaDocumento $parameters
     * @return ResultInterface|Type\CollegaDocumentoResponse
     * @throws SoapException
     */
    public function collegaDocumento(\IrideWS\Type\CollegaDocumento $parameters) : \IrideWS\Type\CollegaDocumentoResponse
    {
        return $this->call('CollegaDocumento', $parameters);
    }

    /**
     * @param RequestInterface|Type\LeggiDocumentoPlus $parameters
     * @return ResultInterface|Type\LeggiDocumentoPlusResponse
     * @throws SoapException
     */
    public function leggiDocumentoPlus(\IrideWS\Type\LeggiDocumentoPlus $parameters) : \IrideWS\Type\LeggiDocumentoPlusResponse
    {
        return $this->call('LeggiDocumentoPlus', $parameters);
    }

    /**
     * @param RequestInterface|Type\InserisciDatiUtente $parameters
     * @return ResultInterface|Type\InserisciDatiUtenteResponse
     * @throws SoapException
     */
    public function inserisciDatiUtente(\IrideWS\Type\InserisciDatiUtente $parameters) : \IrideWS\Type\InserisciDatiUtenteResponse
    {
        return $this->call('InserisciDatiUtente', $parameters);
    }

    /**
     * @param RequestInterface|Type\RicercaPerCodiceFiscale $parameters
     * @return ResultInterface|Type\RicercaPerCodiceFiscaleResponse
     * @throws SoapException
     */
    public function ricercaPerCodiceFiscale(\IrideWS\Type\RicercaPerCodiceFiscale $parameters) : \IrideWS\Type\RicercaPerCodiceFiscaleResponse
    {
        return $this->call('RicercaPerCodiceFiscale', $parameters);
    }

    /**
     * @param RequestInterface|Type\RicercaPerCodiceFiscaleMultiDB $parameters
     * @return ResultInterface|Type\RicercaPerCodiceFiscaleMultiDBResponse
     * @throws SoapException
     */
    public function ricercaPerCodiceFiscaleMultiDB(\IrideWS\Type\RicercaPerCodiceFiscaleMultiDB $parameters) : \IrideWS\Type\RicercaPerCodiceFiscaleMultiDBResponse
    {
        return $this->call('RicercaPerCodiceFiscaleMultiDB', $parameters);
    }


}

