<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class PubblicazioneDocumento implements RequestInterface
{

    /**
     * @var string
     */
    private $Pubblicazione = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * Constructor
     *
     * @var string $Pubblicazione
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($Pubblicazione, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->Pubblicazione = $Pubblicazione;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getPubblicazione()
    {
        return $this->Pubblicazione;
    }

    /**
     * @param string $Pubblicazione
     * @return PubblicazioneDocumento
     */
    public function withPubblicazione($Pubblicazione)
    {
        $new = clone $this;
        $new->Pubblicazione = $Pubblicazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAmministrazione()
    {
        return $this->CodiceAmministrazione;
    }

    /**
     * @param string $CodiceAmministrazione
     * @return PubblicazioneDocumento
     */
    public function withCodiceAmministrazione($CodiceAmministrazione)
    {
        $new = clone $this;
        $new->CodiceAmministrazione = $CodiceAmministrazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAOO()
    {
        return $this->CodiceAOO;
    }

    /**
     * @param string $CodiceAOO
     * @return PubblicazioneDocumento
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

