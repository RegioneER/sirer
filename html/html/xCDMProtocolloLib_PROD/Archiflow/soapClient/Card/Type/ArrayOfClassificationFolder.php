<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfClassificationFolder implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ClassificationFolder
     */
    private $ClassificationFolder = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ClassificationFolder $ClassificationFolder
     */
    public function __construct($ClassificationFolder)
    {
        $this->ClassificationFolder = $ClassificationFolder;
    }

    /**
     * @return \ArchiflowWSCard\Type\ClassificationFolder
     */
    public function getClassificationFolder()
    {
        return $this->ClassificationFolder;
    }

    /**
     * @param \ArchiflowWSCard\Type\ClassificationFolder $ClassificationFolder
     * @return ArrayOfClassificationFolder
     */
    public function withClassificationFolder($ClassificationFolder)
    {
        $new = clone $this;
        $new->ClassificationFolder = $ClassificationFolder;

        return $new;
    }


}

