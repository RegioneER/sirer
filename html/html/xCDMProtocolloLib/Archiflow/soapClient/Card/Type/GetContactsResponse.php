<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetContactsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetContactsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    private $contacts = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetContactsResult()
    {
        return $this->GetContactsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetContactsResult
     * @return GetContactsResponse
     */
    public function withGetContactsResult($GetContactsResult)
    {
        $new = clone $this;
        $new->GetContactsResult = $GetContactsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardContact
     */
    public function getContacts()
    {
        return $this->contacts;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardContact $contacts
     * @return GetContactsResponse
     */
    public function withContacts($contacts)
    {
        $new = clone $this;
        $new->contacts = $contacts;

        return $new;
    }


}

