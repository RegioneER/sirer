<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCardAddressInfo implements RequestInterface
{

    /**
     * @var string
     */
    private $City = null;

    /**
     * @var string
     */
    private $Country = null;

    /**
     * @var bool
     */
    private $IsMain = null;

    /**
     * @var string
     */
    private $Number = null;

    /**
     * @var string
     */
    private $Province = null;

    /**
     * @var string
     */
    private $Street = null;

    /**
     * @var string
     */
    private $ZIPCode = null;

    /**
     * Constructor
     *
     * @var string $City
     * @var string $Country
     * @var bool $IsMain
     * @var string $Number
     * @var string $Province
     * @var string $Street
     * @var string $ZIPCode
     */
    public function __construct($City, $Country, $IsMain, $Number, $Province, $Street, $ZIPCode)
    {
        $this->City = $City;
        $this->Country = $Country;
        $this->IsMain = $IsMain;
        $this->Number = $Number;
        $this->Province = $Province;
        $this->Street = $Street;
        $this->ZIPCode = $ZIPCode;
    }

    /**
     * @return string
     */
    public function getCity()
    {
        return $this->City;
    }

    /**
     * @param string $City
     * @return AgrafCardAddressInfo
     */
    public function withCity($City)
    {
        $new = clone $this;
        $new->City = $City;

        return $new;
    }

    /**
     * @return string
     */
    public function getCountry()
    {
        return $this->Country;
    }

    /**
     * @param string $Country
     * @return AgrafCardAddressInfo
     */
    public function withCountry($Country)
    {
        $new = clone $this;
        $new->Country = $Country;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsMain()
    {
        return $this->IsMain;
    }

    /**
     * @param bool $IsMain
     * @return AgrafCardAddressInfo
     */
    public function withIsMain($IsMain)
    {
        $new = clone $this;
        $new->IsMain = $IsMain;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumber()
    {
        return $this->Number;
    }

    /**
     * @param string $Number
     * @return AgrafCardAddressInfo
     */
    public function withNumber($Number)
    {
        $new = clone $this;
        $new->Number = $Number;

        return $new;
    }

    /**
     * @return string
     */
    public function getProvince()
    {
        return $this->Province;
    }

    /**
     * @param string $Province
     * @return AgrafCardAddressInfo
     */
    public function withProvince($Province)
    {
        $new = clone $this;
        $new->Province = $Province;

        return $new;
    }

    /**
     * @return string
     */
    public function getStreet()
    {
        return $this->Street;
    }

    /**
     * @param string $Street
     * @return AgrafCardAddressInfo
     */
    public function withStreet($Street)
    {
        $new = clone $this;
        $new->Street = $Street;

        return $new;
    }

    /**
     * @return string
     */
    public function getZIPCode()
    {
        return $this->ZIPCode;
    }

    /**
     * @param string $ZIPCode
     * @return AgrafCardAddressInfo
     */
    public function withZIPCode($ZIPCode)
    {
        $new = clone $this;
        $new->ZIPCode = $ZIPCode;

        return $new;
    }


}

