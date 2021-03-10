<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class KeyVersion implements RequestInterface
{

    /**
     * @var string
     */
    private $Digest = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $Indexes = null;

    /**
     * @var \DateTime
     */
    private $ModificationDate = null;

    /**
     * @var string
     */
    private $NomeAllegato = null;

    /**
     * @var int
     */
    private $OperationalOfficeCode = null;

    /**
     * @var string
     */
    private $OperationalOfficeName = null;

    /**
     * @var int
     */
    private $TipoDato = null;

    /**
     * @var int
     */
    private $TipoOperazione = null;

    /**
     * @var int
     */
    private $UserCode = null;

    /**
     * @var string
     */
    private $UserName = null;

    /**
     * @var int
     */
    private $Version = null;

    /**
     * Constructor
     *
     * @var string $Digest
     * @var \ArchiflowWSCard\Type\ArrayOfField $Indexes
     * @var \DateTime $ModificationDate
     * @var string $NomeAllegato
     * @var int $OperationalOfficeCode
     * @var string $OperationalOfficeName
     * @var int $TipoDato
     * @var int $TipoOperazione
     * @var int $UserCode
     * @var string $UserName
     * @var int $Version
     */
    public function __construct($Digest, $Indexes, $ModificationDate, $NomeAllegato, $OperationalOfficeCode, $OperationalOfficeName, $TipoDato, $TipoOperazione, $UserCode, $UserName, $Version)
    {
        $this->Digest = $Digest;
        $this->Indexes = $Indexes;
        $this->ModificationDate = $ModificationDate;
        $this->NomeAllegato = $NomeAllegato;
        $this->OperationalOfficeCode = $OperationalOfficeCode;
        $this->OperationalOfficeName = $OperationalOfficeName;
        $this->TipoDato = $TipoDato;
        $this->TipoOperazione = $TipoOperazione;
        $this->UserCode = $UserCode;
        $this->UserName = $UserName;
        $this->Version = $Version;
    }

    /**
     * @return string
     */
    public function getDigest()
    {
        return $this->Digest;
    }

    /**
     * @param string $Digest
     * @return KeyVersion
     */
    public function withDigest($Digest)
    {
        $new = clone $this;
        $new->Digest = $Digest;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getIndexes()
    {
        return $this->Indexes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $Indexes
     * @return KeyVersion
     */
    public function withIndexes($Indexes)
    {
        $new = clone $this;
        $new->Indexes = $Indexes;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getModificationDate()
    {
        return $this->ModificationDate;
    }

    /**
     * @param \DateTime $ModificationDate
     * @return KeyVersion
     */
    public function withModificationDate($ModificationDate)
    {
        $new = clone $this;
        $new->ModificationDate = $ModificationDate;

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
     * @return KeyVersion
     */
    public function withNomeAllegato($NomeAllegato)
    {
        $new = clone $this;
        $new->NomeAllegato = $NomeAllegato;

        return $new;
    }

    /**
     * @return int
     */
    public function getOperationalOfficeCode()
    {
        return $this->OperationalOfficeCode;
    }

    /**
     * @param int $OperationalOfficeCode
     * @return KeyVersion
     */
    public function withOperationalOfficeCode($OperationalOfficeCode)
    {
        $new = clone $this;
        $new->OperationalOfficeCode = $OperationalOfficeCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getOperationalOfficeName()
    {
        return $this->OperationalOfficeName;
    }

    /**
     * @param string $OperationalOfficeName
     * @return KeyVersion
     */
    public function withOperationalOfficeName($OperationalOfficeName)
    {
        $new = clone $this;
        $new->OperationalOfficeName = $OperationalOfficeName;

        return $new;
    }

    /**
     * @return int
     */
    public function getTipoDato()
    {
        return $this->TipoDato;
    }

    /**
     * @param int $TipoDato
     * @return KeyVersion
     */
    public function withTipoDato($TipoDato)
    {
        $new = clone $this;
        $new->TipoDato = $TipoDato;

        return $new;
    }

    /**
     * @return int
     */
    public function getTipoOperazione()
    {
        return $this->TipoOperazione;
    }

    /**
     * @param int $TipoOperazione
     * @return KeyVersion
     */
    public function withTipoOperazione($TipoOperazione)
    {
        $new = clone $this;
        $new->TipoOperazione = $TipoOperazione;

        return $new;
    }

    /**
     * @return int
     */
    public function getUserCode()
    {
        return $this->UserCode;
    }

    /**
     * @param int $UserCode
     * @return KeyVersion
     */
    public function withUserCode($UserCode)
    {
        $new = clone $this;
        $new->UserCode = $UserCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getUserName()
    {
        return $this->UserName;
    }

    /**
     * @param string $UserName
     * @return KeyVersion
     */
    public function withUserName($UserName)
    {
        $new = clone $this;
        $new->UserName = $UserName;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersion()
    {
        return $this->Version;
    }

    /**
     * @param int $Version
     * @return KeyVersion
     */
    public function withVersion($Version)
    {
        $new = clone $this;
        $new->Version = $Version;

        return $new;
    }


}

