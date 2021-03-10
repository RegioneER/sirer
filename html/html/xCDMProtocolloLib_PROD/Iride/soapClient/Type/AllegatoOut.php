<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AllegatoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $Serial = null;

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
     * @var int
     */
    private $IDBase = null;

    /**
     * @var int
     */
    private $Versione = null;

    /**
     * @var string
     */
    private $TipoAllegato = null;

    /**
     * @var string
     */
    private $Schema = null;

    /**
     * @var string
     */
    private $SottoEstensione = null;

    /**
     * @var string
     */
    private $Firmato = null;

    /**
     * @var string
     */
    private $NomeAllegato = null;

    /**
     * @var string
     */
    private $Principale = null;

    /**
     * @var string
     */
    private $Pubblicato = null;

    /**
     * @var string
     */
    private $CommentoBilingue = null;

    /**
     * @var string
     */
    private $Uri = null;

    /**
     * @var bool
     */
    private $UriImportato = null;

    /**
     * @var float
     */
    private $Size = null;

    /**
     * Constructor
     *
     * @var int $Serial
     * @var string $TipoFile
     * @var string $ContentType
     * @var \IrideWS\Type\Base64Binary $Image
     * @var string $Commento
     * @var int $IDBase
     * @var int $Versione
     * @var string $TipoAllegato
     * @var string $Schema
     * @var string $SottoEstensione
     * @var string $Firmato
     * @var string $NomeAllegato
     * @var string $Principale
     * @var string $Pubblicato
     * @var string $CommentoBilingue
     * @var string $Uri
     * @var bool $UriImportato
     * @var float $Size
     */
    public function __construct($Serial, $TipoFile, $ContentType, $Image, $Commento, $IDBase, $Versione, $TipoAllegato, $Schema, $SottoEstensione, $Firmato, $NomeAllegato, $Principale, $Pubblicato, $CommentoBilingue, $Uri, $UriImportato, $Size)
    {
        $this->Serial = $Serial;
        $this->TipoFile = $TipoFile;
        $this->ContentType = $ContentType;
        $this->Image = $Image;
        $this->Commento = $Commento;
        $this->IDBase = $IDBase;
        $this->Versione = $Versione;
        $this->TipoAllegato = $TipoAllegato;
        $this->Schema = $Schema;
        $this->SottoEstensione = $SottoEstensione;
        $this->Firmato = $Firmato;
        $this->NomeAllegato = $NomeAllegato;
        $this->Principale = $Principale;
        $this->Pubblicato = $Pubblicato;
        $this->CommentoBilingue = $CommentoBilingue;
        $this->Uri = $Uri;
        $this->UriImportato = $UriImportato;
        $this->Size = $Size;
    }

    /**
     * @return int
     */
    public function getSerial()
    {
        return $this->Serial;
    }

    /**
     * @param int $Serial
     * @return AllegatoOut
     */
    public function withSerial($Serial)
    {
        $new = clone $this;
        $new->Serial = $Serial;

        return $new;
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
     * @return AllegatoOut
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
     * @return AllegatoOut
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
     * @return AllegatoOut
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
     * @return AllegatoOut
     */
    public function withCommento($Commento)
    {
        $new = clone $this;
        $new->Commento = $Commento;

        return $new;
    }

    /**
     * @return int
     */
    public function getIDBase()
    {
        return $this->IDBase;
    }

    /**
     * @param int $IDBase
     * @return AllegatoOut
     */
    public function withIDBase($IDBase)
    {
        $new = clone $this;
        $new->IDBase = $IDBase;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersione()
    {
        return $this->Versione;
    }

    /**
     * @param int $Versione
     * @return AllegatoOut
     */
    public function withVersione($Versione)
    {
        $new = clone $this;
        $new->Versione = $Versione;

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
     * @return AllegatoOut
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
    public function getSchema()
    {
        return $this->Schema;
    }

    /**
     * @param string $Schema
     * @return AllegatoOut
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
    public function getSottoEstensione()
    {
        return $this->SottoEstensione;
    }

    /**
     * @param string $SottoEstensione
     * @return AllegatoOut
     */
    public function withSottoEstensione($SottoEstensione)
    {
        $new = clone $this;
        $new->SottoEstensione = $SottoEstensione;

        return $new;
    }

    /**
     * @return string
     */
    public function getFirmato()
    {
        return $this->Firmato;
    }

    /**
     * @param string $Firmato
     * @return AllegatoOut
     */
    public function withFirmato($Firmato)
    {
        $new = clone $this;
        $new->Firmato = $Firmato;

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
     * @return AllegatoOut
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
    public function getPrincipale()
    {
        return $this->Principale;
    }

    /**
     * @param string $Principale
     * @return AllegatoOut
     */
    public function withPrincipale($Principale)
    {
        $new = clone $this;
        $new->Principale = $Principale;

        return $new;
    }

    /**
     * @return string
     */
    public function getPubblicato()
    {
        return $this->Pubblicato;
    }

    /**
     * @param string $Pubblicato
     * @return AllegatoOut
     */
    public function withPubblicato($Pubblicato)
    {
        $new = clone $this;
        $new->Pubblicato = $Pubblicato;

        return $new;
    }

    /**
     * @return string
     */
    public function getCommentoBilingue()
    {
        return $this->CommentoBilingue;
    }

    /**
     * @param string $CommentoBilingue
     * @return AllegatoOut
     */
    public function withCommentoBilingue($CommentoBilingue)
    {
        $new = clone $this;
        $new->CommentoBilingue = $CommentoBilingue;

        return $new;
    }

    /**
     * @return string
     */
    public function getUri()
    {
        return $this->Uri;
    }

    /**
     * @param string $Uri
     * @return AllegatoOut
     */
    public function withUri($Uri)
    {
        $new = clone $this;
        $new->Uri = $Uri;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUriImportato()
    {
        return $this->UriImportato;
    }

    /**
     * @param bool $UriImportato
     * @return AllegatoOut
     */
    public function withUriImportato($UriImportato)
    {
        $new = clone $this;
        $new->UriImportato = $UriImportato;

        return $new;
    }

    /**
     * @return float
     */
    public function getSize()
    {
        return $this->Size;
    }

    /**
     * @param float $Size
     * @return AllegatoOut
     */
    public function withSize($Size)
    {
        $new = clone $this;
        $new->Size = $Size;

        return $new;
    }


}

