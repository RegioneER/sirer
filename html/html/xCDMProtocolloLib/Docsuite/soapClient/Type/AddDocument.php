<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AddDocument implements RequestInterface
{

    /**
     * @var int
     */
    private $year = null;

    /**
     * @var int
     */
    private $number = null;

    /**
     * @var string
     */
    private $base64DocumentStream = null;

    /**
     * @var string
     */
    private $documentName = null;

    /**
     * @var bool
     */
    private $isMain = null;


    /**
     * Constructor
     *
     * @var int $year
     * @var int $number
     * @var string $base64DocumentStream
     * @var string $documentName
     * @var bool $isMain
     */
    public function __construct($year, $number, $base64DocStream, $docName, $isMain)
    {
        $this->year = $year;
        $this->number = $number;
        $this->base64DocumentStream = $base64DocStream;
        $this->documentName = $docName;
        $this->isMain = $isMain;
    }

    /**
     * @return int
     */
    public function getYear()
    {
        return $this->year;
    }

    /**
     * @param int $year
     * @return AddDocument
     */
    public function withYear($year)
    {
        $new = clone $this;
        $new->year = $year;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumber()
    {
        return $this->number;
    }

    /**
     * @param int $number
     * @return AddDocument
     */
    public function withNumber($number)
    {
        $new = clone $this;
        $new->number = $number;

        return $new;
    }

    /**
     * @return string
     */
    public function getBase64DocumentStream()
    {
        return $this->base64DocumentStream;
    }

    /**
     * @param string $base64DocumentStream
     * @return AddDocument
     */
    public function withBase64DocumentStream($base64DocumentStream)
    {
        $new = clone $this;
        $new->base64DocumentStream = $base64DocumentStream;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocumentName()
    {
        return $this->documentName;
    }

    /**
     * @param string $documentName
     * @return AddDocument
     */
    public function withDocumentName($documentName)
    {
        $new = clone $this;
        $new->documentName = $documentName;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsMain()
    {
        return $this->isMain;
    }

    /**
     * @param bool $isMain
     * @return AddDocument
     */
    public function withIsMain($isMain)
    {
        $new = clone $this;
        $new->isMain = $isMain;

        return $new;
    }


}

