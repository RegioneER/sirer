<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SignCardAdditiveGetImageResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SignCardAdditiveGetImageResult = null;

    /**
     * @var string
     */
    private $base64image = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSignCardAdditiveGetImageResult()
    {
        return $this->SignCardAdditiveGetImageResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SignCardAdditiveGetImageResult
     * @return SignCardAdditiveGetImageResponse
     */
    public function withSignCardAdditiveGetImageResult($SignCardAdditiveGetImageResult)
    {
        $new = clone $this;
        $new->SignCardAdditiveGetImageResult = $SignCardAdditiveGetImageResult;

        return $new;
    }

    /**
     * @return string
     */
    public function getBase64image()
    {
        return $this->base64image;
    }

    /**
     * @param string $base64image
     * @return SignCardAdditiveGetImageResponse
     */
    public function withBase64image($base64image)
    {
        $new = clone $this;
        $new->base64image = $base64image;

        return $new;
    }


}

