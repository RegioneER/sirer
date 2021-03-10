<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class TabellaUtente implements RequestInterface
{

    /**
     * @var string
     */
    private $NomeTabella = null;

    /**
     * @var \IrideWS\Type\ArrayOfRecordUtente
     */
    private $Righe = null;

    /**
     * Constructor
     *
     * @var string $NomeTabella
     * @var \IrideWS\Type\ArrayOfRecordUtente $Righe
     */
    public function __construct($NomeTabella, $Righe)
    {
        $this->NomeTabella = $NomeTabella;
        $this->Righe = $Righe;
    }

    /**
     * @return string
     */
    public function getNomeTabella()
    {
        return $this->NomeTabella;
    }

    /**
     * @param string $NomeTabella
     * @return TabellaUtente
     */
    public function withNomeTabella($NomeTabella)
    {
        $new = clone $this;
        $new->NomeTabella = $NomeTabella;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfRecordUtente
     */
    public function getRighe()
    {
        return $this->Righe;
    }

    /**
     * @param \IrideWS\Type\ArrayOfRecordUtente $Righe
     * @return TabellaUtente
     */
    public function withRighe($Righe)
    {
        $new = clone $this;
        $new->Righe = $Righe;

        return $new;
    }


}

