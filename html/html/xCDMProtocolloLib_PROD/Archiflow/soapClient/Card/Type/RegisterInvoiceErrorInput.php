<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RegisterInvoiceErrorInput implements RequestInterface
{

    /**
     * @var string
     */
    private $ErrorDescription = null;

    /**
     * @var string
     */
    private $ErrorNote = null;

    /**
     * @var string
     */
    private $Group = null;

    /**
     * Constructor
     *
     * @var string $ErrorDescription
     * @var string $ErrorNote
     * @var string $Group
     */
    public function __construct($ErrorDescription, $ErrorNote, $Group)
    {
        $this->ErrorDescription = $ErrorDescription;
        $this->ErrorNote = $ErrorNote;
        $this->Group = $Group;
    }

    /**
     * @return string
     */
    public function getErrorDescription()
    {
        return $this->ErrorDescription;
    }

    /**
     * @param string $ErrorDescription
     * @return RegisterInvoiceErrorInput
     */
    public function withErrorDescription($ErrorDescription)
    {
        $new = clone $this;
        $new->ErrorDescription = $ErrorDescription;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrorNote()
    {
        return $this->ErrorNote;
    }

    /**
     * @param string $ErrorNote
     * @return RegisterInvoiceErrorInput
     */
    public function withErrorNote($ErrorNote)
    {
        $new = clone $this;
        $new->ErrorNote = $ErrorNote;

        return $new;
    }

    /**
     * @return string
     */
    public function getGroup()
    {
        return $this->Group;
    }

    /**
     * @param string $Group
     * @return RegisterInvoiceErrorInput
     */
    public function withGroup($Group)
    {
        $new = clone $this;
        $new->Group = $Group;

        return $new;
    }


}

