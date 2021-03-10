<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CheckPrivacyVisibilityOutput implements RequestInterface
{

    /**
     * @var bool
     */
    private $IsEmptyVisibility = null;

    /**
     * Constructor
     *
     * @var bool $IsEmptyVisibility
     */
    public function __construct($IsEmptyVisibility)
    {
        $this->IsEmptyVisibility = $IsEmptyVisibility;
    }

    /**
     * @return bool
     */
    public function getIsEmptyVisibility()
    {
        return $this->IsEmptyVisibility;
    }

    /**
     * @param bool $IsEmptyVisibility
     * @return CheckPrivacyVisibilityOutput
     */
    public function withIsEmptyVisibility($IsEmptyVisibility)
    {
        $new = clone $this;
        $new->IsEmptyVisibility = $IsEmptyVisibility;

        return $new;
    }


}

