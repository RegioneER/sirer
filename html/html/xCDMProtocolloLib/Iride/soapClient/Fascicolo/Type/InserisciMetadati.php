<?php

namespace IrideWFFascicolo\Type;

class InserisciMetadati
{

    /**
     * @var string
     */
    private $Contesto = null;

    /**
     * @var string
     */
    private $IDFascicolo = null;

    /**
     * @var string
     */
    private $MetadatiStr = null;

    /**
     * @var string
     */
    private $ConnectionString = null;

    /**
     * @return string
     */
    public function getContesto()
    {
        return $this->Contesto;
    }

    /**
     * @param string $Contesto
     * @return InserisciMetadati
     */
    public function withContesto($Contesto)
    {
        $new = clone $this;
        $new->Contesto = $Contesto;

        return $new;
    }

    /**
     * @return string
     */
    public function getIDFascicolo()
    {
        return $this->IDFascicolo;
    }

    /**
     * @param string $IDFascicolo
     * @return InserisciMetadati
     */
    public function withIDFascicolo($IDFascicolo)
    {
        $new = clone $this;
        $new->IDFascicolo = $IDFascicolo;

        return $new;
    }

    /**
     * @return string
     */
    public function getMetadatiStr()
    {
        return $this->MetadatiStr;
    }

    /**
     * @param string $MetadatiStr
     * @return InserisciMetadati
     */
    public function withMetadatiStr($MetadatiStr)
    {
        $new = clone $this;
        $new->MetadatiStr = $MetadatiStr;

        return $new;
    }

    /**
     * @return string
     */
    public function getConnectionString()
    {
        return $this->ConnectionString;
    }

    /**
     * @param string $ConnectionString
     * @return InserisciMetadati
     */
    public function withConnectionString($ConnectionString)
    {
        $new = clone $this;
        $new->ConnectionString = $ConnectionString;

        return $new;
    }


}

