<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DurationSearchCriteria implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfint5F2dSckg
     */
    private $Duration = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $ExpirationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\ExpirationMethodType
     */
    private $ExpirationMethod = null;

    /**
     * @var bool
     */
    private $UnlimitedDuration = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfint5F2dSckg $Duration
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $ExpirationDate
     * @var \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @var bool $UnlimitedDuration
     */
    public function __construct($Duration, $ExpirationDate, $ExpirationMethod, $UnlimitedDuration)
    {
        $this->Duration = $Duration;
        $this->ExpirationDate = $ExpirationDate;
        $this->ExpirationMethod = $ExpirationMethod;
        $this->UnlimitedDuration = $UnlimitedDuration;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfint5F2dSckg
     */
    public function getDuration()
    {
        return $this->Duration;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfint5F2dSckg $Duration
     * @return DurationSearchCriteria
     */
    public function withDuration($Duration)
    {
        $new = clone $this;
        $new->Duration = $Duration;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getExpirationDate()
    {
        return $this->ExpirationDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $ExpirationDate
     * @return DurationSearchCriteria
     */
    public function withExpirationDate($ExpirationDate)
    {
        $new = clone $this;
        $new->ExpirationDate = $ExpirationDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExpirationMethodType
     */
    public function getExpirationMethod()
    {
        return $this->ExpirationMethod;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @return DurationSearchCriteria
     */
    public function withExpirationMethod($ExpirationMethod)
    {
        $new = clone $this;
        $new->ExpirationMethod = $ExpirationMethod;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUnlimitedDuration()
    {
        return $this->UnlimitedDuration;
    }

    /**
     * @param bool $UnlimitedDuration
     * @return DurationSearchCriteria
     */
    public function withUnlimitedDuration($UnlimitedDuration)
    {
        $new = clone $this;
        $new->UnlimitedDuration = $UnlimitedDuration;

        return $new;
    }


}

