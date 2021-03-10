<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AddContactsToCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $AddContactsToCardResult = null;

    /**
     * @var int
     */
    private $nAdded = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getAddContactsToCardResult()
    {
        return $this->AddContactsToCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $AddContactsToCardResult
     * @return AddContactsToCardResponse
     */
    public function withAddContactsToCardResult($AddContactsToCardResult)
    {
        $new = clone $this;
        $new->AddContactsToCardResult = $AddContactsToCardResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNAdded()
    {
        return $this->nAdded;
    }

    /**
     * @param int $nAdded
     * @return AddContactsToCardResponse
     */
    public function withNAdded($nAdded)
    {
        $new = clone $this;
        $new->nAdded = $nAdded;

        return $new;
    }


}

