<?php

namespace IrideWFFascicolo\Type;

class DocumentoFascicoloOut
{

    /**
     * @var int
     */
    private $IdDocumento = null;

    /**
     * @var string
     */
    private $TipoDocumento = null;

    /**
     * @var \DateTime
     */
    private $DataInserimento = null;

    /**
     * @var string
     */
    private $DestinatarioInterno = null;

    /**
     * @var \DateTime
     */
    private $DataInvioDestinatario = null;

    /**
     * @var bool
     */
    private $Copia = null;

    /**
     * @var string
     */
    private $AnnoProtocollo = null;

    /**
     * @var string
     */
    private $NumeroProtocollo = null;

    /**
     * @var bool
     */
    private $IterAttivo = null;

    /**
     * @var string
     */
    private $Oggetto = null;

    /**
     * @var \DateTime
     */
    private $DataAnnullamento = null;

    /**
     * @var string
     */
    private $Origine = null;

    /**
     * @return int
     */
    public function getIdDocumento()
    {
        return $this->IdDocumento;
    }

    /**
     * @param int $IdDocumento
     * @return DocumentoFascicoloOut
     */
    public function withIdDocumento($IdDocumento)
    {
        $new = clone $this;
        $new->IdDocumento = $IdDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoDocumento()
    {
        return $this->TipoDocumento;
    }

    /**
     * @param string $TipoDocumento
     * @return DocumentoFascicoloOut
     */
    public function withTipoDocumento($TipoDocumento)
    {
        $new = clone $this;
        $new->TipoDocumento = $TipoDocumento;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataInserimento()
    {
        return $this->DataInserimento;
    }

    /**
     * @param \DateTime $DataInserimento
     * @return DocumentoFascicoloOut
     */
    public function withDataInserimento($DataInserimento)
    {
        $new = clone $this;
        $new->DataInserimento = $DataInserimento;

        return $new;
    }

    /**
     * @return string
     */
    public function getDestinatarioInterno()
    {
        return $this->DestinatarioInterno;
    }

    /**
     * @param string $DestinatarioInterno
     * @return DocumentoFascicoloOut
     */
    public function withDestinatarioInterno($DestinatarioInterno)
    {
        $new = clone $this;
        $new->DestinatarioInterno = $DestinatarioInterno;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataInvioDestinatario()
    {
        return $this->DataInvioDestinatario;
    }

    /**
     * @param \DateTime $DataInvioDestinatario
     * @return DocumentoFascicoloOut
     */
    public function withDataInvioDestinatario($DataInvioDestinatario)
    {
        $new = clone $this;
        $new->DataInvioDestinatario = $DataInvioDestinatario;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCopia()
    {
        return $this->Copia;
    }

    /**
     * @param bool $Copia
     * @return DocumentoFascicoloOut
     */
    public function withCopia($Copia)
    {
        $new = clone $this;
        $new->Copia = $Copia;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnoProtocollo()
    {
        return $this->AnnoProtocollo;
    }

    /**
     * @param string $AnnoProtocollo
     * @return DocumentoFascicoloOut
     */
    public function withAnnoProtocollo($AnnoProtocollo)
    {
        $new = clone $this;
        $new->AnnoProtocollo = $AnnoProtocollo;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroProtocollo()
    {
        return $this->NumeroProtocollo;
    }

    /**
     * @param string $NumeroProtocollo
     * @return DocumentoFascicoloOut
     */
    public function withNumeroProtocollo($NumeroProtocollo)
    {
        $new = clone $this;
        $new->NumeroProtocollo = $NumeroProtocollo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIterAttivo()
    {
        return $this->IterAttivo;
    }

    /**
     * @param bool $IterAttivo
     * @return DocumentoFascicoloOut
     */
    public function withIterAttivo($IterAttivo)
    {
        $new = clone $this;
        $new->IterAttivo = $IterAttivo;

        return $new;
    }

    /**
     * @return string
     */
    public function getOggetto()
    {
        return $this->Oggetto;
    }

    /**
     * @param string $Oggetto
     * @return DocumentoFascicoloOut
     */
    public function withOggetto($Oggetto)
    {
        $new = clone $this;
        $new->Oggetto = $Oggetto;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataAnnullamento()
    {
        return $this->DataAnnullamento;
    }

    /**
     * @param \DateTime $DataAnnullamento
     * @return DocumentoFascicoloOut
     */
    public function withDataAnnullamento($DataAnnullamento)
    {
        $new = clone $this;
        $new->DataAnnullamento = $DataAnnullamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getOrigine()
    {
        return $this->Origine;
    }

    /**
     * @param string $Origine
     * @return DocumentoFascicoloOut
     */
    public function withOrigine($Origine)
    {
        $new = clone $this;
        $new->Origine = $Origine;

        return $new;
    }


}

