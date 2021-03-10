<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AllegatoIn implements RequestInterface
{

    /**
     * @var string
     */
    private $TipoFile = null;

    /**
     * @var string
     */
    private $ContentType = null;

    /**
     * @var \IrideWS\Type\Base64Binary
     */
    private $Image = null;

    /**
     * @var string
     */
    private $Commento = null;

    /**
     * @var string
     */
    private $IdAllegatoPrincipale = null;

    /**
     * @var string
     */
    private $Schema = null;

    /**
     * @var string
     */
    private $NomeAllegato = null;

    /**
     * @var string
     */
    private $TipoAllegato = null;

    /**
     * @var string
     */
    private $URI = null;

    /**
     * @var string
     */
    private $Hash = null;

    /**
     * Constructor
     *
     * @var string $TipoFile
     * @var string $ContentType
     * @var \IrideWS\Type\Base64Binary $Image
     * @var string $Commento
     * @var string $IdAllegatoPrincipale
     * @var string $Schema
     * @var string $NomeAllegato
     * @var string $TipoAllegato
     * @var string $URI
     * @var string $Hash
     */
    public function __construct($TipoFile, $ContentType, $Image, $Commento, $IdAllegatoPrincipale, $Schema, $NomeAllegato, $TipoAllegato, $URI, $Hash)
    {
        $this->TipoFile = $TipoFile;
        $this->ContentType = $ContentType;
        $this->Image = $Image;
        $this->Commento = $Commento;
        $this->IdAllegatoPrincipale = $IdAllegatoPrincipale;
        $this->Schema = $Schema;
        $this->NomeAllegato = $NomeAllegato;
        $this->TipoAllegato = $TipoAllegato;
        $this->URI = $URI;
        $this->Hash = $Hash;
    }

    /**
     * @return string
     */
    public function getTipoFile()
    {
        return $this->TipoFile;
    }

    /**
     * @param string $TipoFile
     * @return AllegatoIn
     */
    public function withTipoFile($TipoFile)
    {
        $new = clone $this;
        $new->TipoFile = $TipoFile;

        return $new;
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return $this->ContentType;
    }

    /**
     * @param string $ContentType
     * @return AllegatoIn
     */
    public function withContentType($ContentType)
    {
        $new = clone $this;
        $new->ContentType = $ContentType;

        return $new;
    }

    /**
     * @return \IrideWS\Type\Base64Binary
     */
    public function getImage()
    {
        return $this->Image;
    }

    /**
     * @param \IrideWS\Type\Base64Binary $Image
     * @return AllegatoIn
     */
    public function withImage($Image)
    {
        $new = clone $this;
        $new->Image = $Image;

        return $new;
    }

    /**
     * @return string
     */
    public function getCommento()
    {
        return $this->Commento;
    }

    /**
     * @param string $Commento
     * @return AllegatoIn
     */
    public function withCommento($Commento)
    {
        $new = clone $this;
        $new->Commento = $Commento;

        return $new;
    }

    /**
     * @return string
     */
    public function getIdAllegatoPrincipale()
    {
        return $this->IdAllegatoPrincipale;
    }

    /**
     * @param string $IdAllegatoPrincipale
     * @return AllegatoIn
     */
    public function withIdAllegatoPrincipale($IdAllegatoPrincipale)
    {
        $new = clone $this;
        $new->IdAllegatoPrincipale = $IdAllegatoPrincipale;

        return $new;
    }

    /**
     * @return string
     */
    public function getSchema()
    {
        return $this->Schema;
    }

    /**
     * @param string $Schema
     * @return AllegatoIn
     */
    public function withSchema($Schema)
    {
        $new = clone $this;
        $new->Schema = $Schema;

        return $new;
    }

    /**
     * @return string
     */
    public function getNomeAllegato()
    {
        return $this->NomeAllegato;
    }

    /**
     * @param string $NomeAllegato
     * @return AllegatoIn
     */
    public function withNomeAllegato($NomeAllegato)
    {
        $new = clone $this;
        $new->NomeAllegato = $NomeAllegato;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoAllegato()
    {
        return $this->TipoAllegato;
    }

    /**
     * @param string $TipoAllegato
     * @return AllegatoIn
     */
    public function withTipoAllegato($TipoAllegato)
    {
        $new = clone $this;
        $new->TipoAllegato = $TipoAllegato;

        return $new;
    }

    /**
     * @return string
     */
    public function getURI()
    {
        return $this->URI;
    }

    /**
     * @param string $URI
     * @return AllegatoIn
     */
    public function withURI($URI)
    {
        $new = clone $this;
        $new->URI = $URI;

        return $new;
    }

    /**
     * @return string
     */
    public function getHash()
    {
        return $this->Hash;
    }

    /**
     * @param string $Hash
     * @return AllegatoIn
     */
    public function withHash($Hash)
    {
        $new = clone $this;
        $new->Hash = $Hash;

        return $new;
    }


}

