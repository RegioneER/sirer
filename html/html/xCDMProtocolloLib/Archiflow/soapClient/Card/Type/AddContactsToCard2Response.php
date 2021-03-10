<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AddContactsToCard2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $AddContactsToCard2Result = null;

    /**
     * @var int
     */
    private $nAdded = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getAddContactsToCard2Result()
    {
        return $this->AddContactsToCard2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $AddContactsToCard2Result
     * @return AddContactsToCard2Response
     */
    public function withAddContactsToCard2Result($AddContactsToCard2Result)
    {
        $new = clone $this;
        $new->AddContactsToCard2Result = $AddContactsToCard2Result;

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
     * @return AddContactsToCard2Response
     */
    public function withNAdded($nAdded)
    {
        $new = clone $this;
        $new->nAdded = $nAdded;

        return $new;
    }


}

