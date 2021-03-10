<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDatabaseTypeExResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetDatabase_Type_ExResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\DatabaseTypeEx
     */
    private $eDatabase_Type_Ex = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetDatabase_Type_ExResult()
    {
        return $this->GetDatabase_Type_ExResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetDatabase_Type_ExResult
     * @return GetDatabaseTypeExResponse
     */
    public function withGetDatabase_Type_ExResult($GetDatabase_Type_ExResult)
    {
        $new = clone $this;
        $new->GetDatabase_Type_ExResult = $GetDatabase_Type_ExResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\DatabaseTypeEx
     */
    public function getEDatabase_Type_Ex()
    {
        return $this->eDatabase_Type_Ex;
    }

    /**
     * @param \ArchiflowWSLogin\Type\DatabaseTypeEx $eDatabase_Type_Ex
     * @return GetDatabaseTypeExResponse
     */
    public function withEDatabase_Type_Ex($eDatabase_Type_Ex)
    {
        $new = clone $this;
        $new->eDatabase_Type_Ex = $eDatabase_Type_Ex;

        return $new;
    }


}

