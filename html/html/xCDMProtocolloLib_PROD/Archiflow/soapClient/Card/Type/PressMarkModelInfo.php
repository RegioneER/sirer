<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class PressMarkModelInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Base64Binary
     */
    private $RawBytes = null;

    /**
     * @var string
     */
    private $Text = null;

    /**
     * @var string
     */
    private $TextXml = null;

    /**
     * @var bool
     */
    private $UseEndorser = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Base64Binary $RawBytes
     * @var string $Text
     * @var string $TextXml
     * @var bool $UseEndorser
     */
    public function __construct($RawBytes, $Text, $TextXml, $UseEndorser)
    {
        $this->RawBytes = $RawBytes;
        $this->Text = $Text;
        $this->TextXml = $TextXml;
        $this->UseEndorser = $UseEndorser;
    }

    /**
     * @return \ArchiflowWSCard\Type\Base64Binary
     */
    public function getRawBytes()
    {
        return $this->RawBytes;
    }

    /**
     * @param \ArchiflowWSCard\Type\Base64Binary $RawBytes
     * @return PressMarkModelInfo
     */
    public function withRawBytes($RawBytes)
    {
        $new = clone $this;
        $new->RawBytes = $RawBytes;

        return $new;
    }

    /**
     * @return string
     */
    public function getText()
    {
        return $this->Text;
    }

    /**
     * @param string $Text
     * @return PressMarkModelInfo
     */
    public function withText($Text)
    {
        $new = clone $this;
        $new->Text = $Text;

        return $new;
    }

    /**
     * @return string
     */
    public function getTextXml()
    {
        return $this->TextXml;
    }

    /**
     * @param string $TextXml
     * @return PressMarkModelInfo
     */
    public function withTextXml($TextXml)
    {
        $new = clone $this;
        $new->TextXml = $TextXml;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUseEndorser()
    {
        return $this->UseEndorser;
    }

    /**
     * @param bool $UseEndorser
     * @return PressMarkModelInfo
     */
    public function withUseEndorser($UseEndorser)
    {
        $new = clone $this;
        $new->UseEndorser = $UseEndorser;

        return $new;
    }


}

