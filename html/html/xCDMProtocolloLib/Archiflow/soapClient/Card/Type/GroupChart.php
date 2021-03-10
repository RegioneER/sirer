<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GroupChart implements RequestInterface
{

    /**
     * @var bool
     */
    private $PrivacyData = null;

    /**
     * Constructor
     *
     * @var bool $PrivacyData
     */
    public function __construct($PrivacyData)
    {
        $this->PrivacyData = $PrivacyData;
    }

    /**
     * @return bool
     */
    public function getPrivacyData()
    {
        return $this->PrivacyData;
    }

    /**
     * @param bool $PrivacyData
     * @return GroupChart
     */
    public function withPrivacyData($PrivacyData)
    {
        $new = clone $this;
        $new->PrivacyData = $PrivacyData;

        return $new;
    }


}

