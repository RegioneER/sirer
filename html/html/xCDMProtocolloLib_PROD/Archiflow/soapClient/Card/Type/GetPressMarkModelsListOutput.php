<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetPressMarkModelsListOutput implements RequestInterface
{

    /**
     * @var string
     */
    private $DafaultModel = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $Models = null;

    /**
     * Constructor
     *
     * @var string $DafaultModel
     * @var \ArchiflowWSCard\Type\ArrayOfstring $Models
     */
    public function __construct($DafaultModel, $Models)
    {
        $this->DafaultModel = $DafaultModel;
        $this->Models = $Models;
    }

    /**
     * @return string
     */
    public function getDafaultModel()
    {
        return $this->DafaultModel;
    }

    /**
     * @param string $DafaultModel
     * @return GetPressMarkModelsListOutput
     */
    public function withDafaultModel($DafaultModel)
    {
        $new = clone $this;
        $new->DafaultModel = $DafaultModel;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getModels()
    {
        return $this->Models;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $Models
     * @return GetPressMarkModelsListOutput
     */
    public function withModels($Models)
    {
        $new = clone $this;
        $new->Models = $Models;

        return $new;
    }


}

