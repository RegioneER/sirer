<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RicercaAmministrazioneMultiDB implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceAmmSoggetto = null;

    /**
     * @var string
     */
    private $CodiceAOOSoggetto = null;

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
     * @var string $CodiceAmmSoggetto
     * @var string $CodiceAOOSoggetto
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($CodiceAmmSoggetto, $CodiceAOOSoggetto, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->CodiceAmmSoggetto = $CodiceAmmSoggetto;
        $this->CodiceAOOSoggetto = $CodiceAOOSoggetto;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getCodiceAmmSoggetto()
    {
        return $this->CodiceAmmSoggetto;
    }

    /**
     * @param string $CodiceAmmSoggetto
     * @return RicercaAmministrazioneMultiDB
     */
    public function withCodiceAmmSoggetto($CodiceAmmSoggetto)
    {
        $new = clone $this;
        $new->CodiceAmmSoggetto = $CodiceAmmSoggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAOOSoggetto()
    {
        return $this->CodiceAOOSoggetto;
    }

    /**
     * @param string $CodiceAOOSoggetto
     * @return RicercaAmministrazioneMultiDB
     */
    public function withCodiceAOOSoggetto($CodiceAOOSoggetto)
    {
        $new = clone $this;
        $new->CodiceAOOSoggetto = $CodiceAOOSoggetto;

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
     * @return RicercaAmministrazioneMultiDB
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
     * @return RicercaAmministrazioneMultiDB
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

