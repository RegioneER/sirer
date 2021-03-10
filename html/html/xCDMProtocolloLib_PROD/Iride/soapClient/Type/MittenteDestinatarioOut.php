<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MittenteDestinatarioOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdSoggetto = null;

    /**
     * @var string
     */
    private $CognomeNome = null;

    /**
     * @var string
     */
    private $PartitaIVA = null;

    /**
     * @var string
     */
    private $ChiaveAlternativa = null;

    /**
     * Constructor
     *
     * @var int $IdSoggetto
     * @var string $CognomeNome
     * @var string $PartitaIVA
     * @var string $ChiaveAlternativa
     */
    public function __construct($IdSoggetto, $CognomeNome, $PartitaIVA, $ChiaveAlternativa)
    {
        $this->IdSoggetto = $IdSoggetto;
        $this->CognomeNome = $CognomeNome;
        $this->PartitaIVA = $PartitaIVA;
        $this->ChiaveAlternativa = $ChiaveAlternativa;
    }

    /**
     * @return int
     */
    public function getIdSoggetto()
    {
        return $this->IdSoggetto;
    }

    /**
     * @param int $IdSoggetto
     * @return MittenteDestinatarioOut
     */
    public function withIdSoggetto($IdSoggetto)
    {
        $new = clone $this;
        $new->IdSoggetto = $IdSoggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getCognomeNome()
    {
        return $this->CognomeNome;
    }

    /**
     * @param string $CognomeNome
     * @return MittenteDestinatarioOut
     */
    public function withCognomeNome($CognomeNome)
    {
        $new = clone $this;
        $new->CognomeNome = $CognomeNome;

        return $new;
    }

    /**
     * @return string
     */
    public function getPartitaIVA()
    {
        return $this->PartitaIVA;
    }

    /**
     * @param string $PartitaIVA
     * @return MittenteDestinatarioOut
     */
    public function withPartitaIVA($PartitaIVA)
    {
        $new = clone $this;
        $new->PartitaIVA = $PartitaIVA;

        return $new;
    }

    /**
     * @return string
     */
    public function getChiaveAlternativa()
    {
        return $this->ChiaveAlternativa;
    }

    /**
     * @param string $ChiaveAlternativa
     * @return MittenteDestinatarioOut
     */
    public function withChiaveAlternativa($ChiaveAlternativa)
    {
        $new = clone $this;
        $new->ChiaveAlternativa = $ChiaveAlternativa;

        return $new;
    }


}

