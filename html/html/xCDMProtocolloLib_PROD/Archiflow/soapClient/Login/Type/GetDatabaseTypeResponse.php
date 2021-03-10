<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDatabaseTypeResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetDatabase_TypeResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\DatabaseType
     */
    private $eDatabase_Type = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetDatabase_TypeResult()
    {
        return $this->GetDatabase_TypeResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetDatabase_TypeResult
     * @return GetDatabaseTypeResponse
     */
    public function withGetDatabase_TypeResult($GetDatabase_TypeResult)
    {
        $new = clone $this;
        $new->GetDatabase_TypeResult = $GetDatabase_TypeResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\DatabaseType
     */
    public function getEDatabase_Type()
    {
        return $this->eDatabase_Type;
    }

    /**
     * @param \ArchiflowWSLogin\Type\DatabaseType $eDatabase_Type
     * @return GetDatabaseTypeResponse
     */
    public function withEDatabase_Type($eDatabase_Type)
    {
        $new = clone $this;
        $new->eDatabase_Type = $eDatabase_Type;

        return $new;
    }


}

