<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AllegatiInseritiOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdDocumento = null;

    /**
     * @var \IrideWS\Type\ArrayOfAllegatoInseritoOut
     */
    private $Allegati = null;

    /**
     * @var string
     */
    private $Messaggio = null;

    /**
     * @var string
     */
    private $Errore = null;

    /**
     * Constructor
     *
     * @var int $IdDocumento
     * @var \IrideWS\Type\ArrayOfAllegatoInseritoOut $Allegati
     * @var string $Messaggio
     * @var string $Errore
     */
    public function __construct($IdDocumento, $Allegati, $Messaggio, $Errore)
    {
        $this->IdDocumento = $IdDocumento;
        $this->Allegati = $Allegati;
        $this->Messaggio = $Messaggio;
        $this->Errore = $Errore;
    }

    /**
     * @return int
     */
    public function getIdDocumento()
    {
        return $this->IdDocumento;
    }

    /**
     * @param int $IdDocumento
     * @return AllegatiInseritiOut
     */
    public function withIdDocumento($IdDocumento)
    {
        $new = clone $this;
        $new->IdDocumento = $IdDocumento;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfAllegatoInseritoOut
     */
    public function getAllegati()
    {
        return $this->Allegati;
    }

    /**
     * @param \IrideWS\Type\ArrayOfAllegatoInseritoOut $Allegati
     * @return AllegatiInseritiOut
     */
    public function withAllegati($Allegati)
    {
        $new = clone $this;
        $new->Allegati = $Allegati;

        return $new;
    }

    /**
     * @return string
     */
    public function getMessaggio()
    {
        return $this->Messaggio;
    }

    /**
     * @param string $Messaggio
     * @return AllegatiInseritiOut
     */
    public function withMessaggio($Messaggio)
    {
        $new = clone $this;
        $new->Messaggio = $Messaggio;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrore()
    {
        return $this->Errore;
    }

    /**
     * @param string $Errore
     * @return AllegatiInseritiOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

