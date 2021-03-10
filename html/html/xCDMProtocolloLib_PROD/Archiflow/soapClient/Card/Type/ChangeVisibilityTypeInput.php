<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ChangeVisibilityTypeInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $SetVisOnlyDoc = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $SetVisOnlyDoc
     */
    public function __construct($CardId, $SetVisOnlyDoc)
    {
        $this->CardId = $CardId;
        $this->SetVisOnlyDoc = $SetVisOnlyDoc;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return ChangeVisibilityTypeInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSetVisOnlyDoc()
    {
        return $this->SetVisOnlyDoc;
    }

    /**
     * @param bool $SetVisOnlyDoc
     * @return ChangeVisibilityTypeInput
     */
    public function withSetVisOnlyDoc($SetVisOnlyDoc)
    {
        $new = clone $this;
        $new->SetVisOnlyDoc = $SetVisOnlyDoc;

        return $new;
    }


}

