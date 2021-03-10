<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoadAutoCollationTemplatesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $LoadAutoCollationTemplatesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAutoCollationTemplate
     */
    private $autoCollationTemplates = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getLoadAutoCollationTemplatesResult()
    {
        return $this->LoadAutoCollationTemplatesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $LoadAutoCollationTemplatesResult
     * @return LoadAutoCollationTemplatesResponse
     */
    public function withLoadAutoCollationTemplatesResult($LoadAutoCollationTemplatesResult)
    {
        $new = clone $this;
        $new->LoadAutoCollationTemplatesResult = $LoadAutoCollationTemplatesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAutoCollationTemplate
     */
    public function getAutoCollationTemplates()
    {
        return $this->autoCollationTemplates;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAutoCollationTemplate
     * $autoCollationTemplates
     * @return LoadAutoCollationTemplatesResponse
     */
    public function withAutoCollationTemplates($autoCollationTemplates)
    {
        $new = clone $this;
        $new->autoCollationTemplates = $autoCollationTemplates;

        return $new;
    }


}

