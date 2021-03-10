<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsVisibilityInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var \ArchiflowWSCard\Type\UserRights
     */
    private $VisUserRight = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var \ArchiflowWSCard\Type\UserRights $VisUserRight
     */
    public function __construct($CardIds, $VisUserRight)
    {
        $this->CardIds = $CardIds;
        $this->VisUserRight = $VisUserRight;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return GetCardsVisibilityInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserRights
     */
    public function getVisUserRight()
    {
        return $this->VisUserRight;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserRights $VisUserRight
     * @return GetCardsVisibilityInput
     */
    public function withVisUserRight($VisUserRight)
    {
        $new = clone $this;
        $new->VisUserRight = $VisUserRight;

        return $new;
    }


}

