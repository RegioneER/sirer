<?php

namespace ArchiflowWSFolder;

use ArchiflowWSFolder\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class ArchiFlowFolderClientClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\GetFolder $parameters
     * @return ResultInterface|Type\GetFolderResponse
     * @throws SoapException
     */
    public function getFolder(\ArchiflowWSFolder\Type\GetFolder $parameters) : \ArchiflowWSFolder\Type\GetFolderResponse
    {
        return $this->call('GetFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetFolders $parameters
     * @return ResultInterface|Type\GetFoldersResponse
     * @throws SoapException
     */
    public function getFolders(\ArchiflowWSFolder\Type\GetFolders $parameters) : \ArchiflowWSFolder\Type\GetFoldersResponse
    {
        return $this->call('GetFolders', $parameters);
    }

    /**
     * @param RequestInterface|Type\SearchFolders $parameters
     * @return ResultInterface|Type\SearchFoldersResponse
     * @throws SoapException
     */
    public function searchFolders(\ArchiflowWSFolder\Type\SearchFolders $parameters) : \ArchiflowWSFolder\Type\SearchFoldersResponse
    {
        return $this->call('SearchFolders', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetFolderVisibility $parameters
     * @return ResultInterface|Type\GetFolderVisibilityResponse
     * @throws SoapException
     */
    public function getFolderVisibility(\ArchiflowWSFolder\Type\GetFolderVisibility $parameters) : \ArchiflowWSFolder\Type\GetFolderVisibilityResponse
    {
        return $this->call('GetFolderVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertFolder $parameters
     * @return ResultInterface|Type\InsertFolderResponse
     * @throws SoapException
     */
    public function insertFolder(\ArchiflowWSFolder\Type\InsertFolder $parameters) : \ArchiflowWSFolder\Type\InsertFolderResponse
    {
        return $this->call('InsertFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\AddFolderInDrawer $parameters
     * @return ResultInterface|Type\AddFolderInDrawerResponse
     * @throws SoapException
     */
    public function addFolderInDrawer(\ArchiflowWSFolder\Type\AddFolderInDrawer $parameters) : \ArchiflowWSFolder\Type\AddFolderInDrawerResponse
    {
        return $this->call('AddFolderInDrawer', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendFolder $parameters
     * @return ResultInterface|Type\SendFolderResponse
     * @throws SoapException
     */
    public function sendFolder(\ArchiflowWSFolder\Type\SendFolder $parameters) : \ArchiflowWSFolder\Type\SendFolderResponse
    {
        return $this->call('SendFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyFolder $parameters
     * @return ResultInterface|Type\ModifyFolderResponse
     * @throws SoapException
     */
    public function modifyFolder(\ArchiflowWSFolder\Type\ModifyFolder $parameters) : \ArchiflowWSFolder\Type\ModifyFolderResponse
    {
        return $this->call('ModifyFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteFolder $parameters
     * @return ResultInterface|Type\DeleteFolderResponse
     * @throws SoapException
     */
    public function deleteFolder(\ArchiflowWSFolder\Type\DeleteFolder $parameters) : \ArchiflowWSFolder\Type\DeleteFolderResponse
    {
        return $this->call('DeleteFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDrawers $parameters
     * @return ResultInterface|Type\GetDrawersResponse
     * @throws SoapException
     */
    public function getDrawers(\ArchiflowWSFolder\Type\GetDrawers $parameters) : \ArchiflowWSFolder\Type\GetDrawersResponse
    {
        return $this->call('GetDrawers', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDrawerVisibility $parameters
     * @return ResultInterface|Type\GetDrawerVisibilityResponse
     * @throws SoapException
     */
    public function getDrawerVisibility(\ArchiflowWSFolder\Type\GetDrawerVisibility $parameters) : \ArchiflowWSFolder\Type\GetDrawerVisibilityResponse
    {
        return $this->call('GetDrawerVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertDrawer $parameters
     * @return ResultInterface|Type\InsertDrawerResponse
     * @throws SoapException
     */
    public function insertDrawer(\ArchiflowWSFolder\Type\InsertDrawer $parameters) : \ArchiflowWSFolder\Type\InsertDrawerResponse
    {
        return $this->call('InsertDrawer', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyDrawer $parameters
     * @return ResultInterface|Type\ModifyDrawerResponse
     * @throws SoapException
     */
    public function modifyDrawer(\ArchiflowWSFolder\Type\ModifyDrawer $parameters) : \ArchiflowWSFolder\Type\ModifyDrawerResponse
    {
        return $this->call('ModifyDrawer', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteDrawer $parameters
     * @return ResultInterface|Type\DeleteDrawerResponse
     * @throws SoapException
     */
    public function deleteDrawer(\ArchiflowWSFolder\Type\DeleteDrawer $parameters) : \ArchiflowWSFolder\Type\DeleteDrawerResponse
    {
        return $this->call('DeleteDrawer', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCabinets $parameters
     * @return ResultInterface|Type\GetCabinetsResponse
     * @throws SoapException
     */
    public function getCabinets(\ArchiflowWSFolder\Type\GetCabinets $parameters) : \ArchiflowWSFolder\Type\GetCabinetsResponse
    {
        return $this->call('GetCabinets', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCabinetVisibility $parameters
     * @return ResultInterface|Type\GetCabinetVisibilityResponse
     * @throws SoapException
     */
    public function getCabinetVisibility(\ArchiflowWSFolder\Type\GetCabinetVisibility $parameters) : \ArchiflowWSFolder\Type\GetCabinetVisibilityResponse
    {
        return $this->call('GetCabinetVisibility', $parameters);
    }

    /**
     * @param RequestInterface|Type\InsertCabinet $parameters
     * @return ResultInterface|Type\InsertCabinetResponse
     * @throws SoapException
     */
    public function insertCabinet(\ArchiflowWSFolder\Type\InsertCabinet $parameters) : \ArchiflowWSFolder\Type\InsertCabinetResponse
    {
        return $this->call('InsertCabinet', $parameters);
    }

    /**
     * @param RequestInterface|Type\ModifyCabinet $parameters
     * @return ResultInterface|Type\ModifyCabinetResponse
     * @throws SoapException
     */
    public function modifyCabinet(\ArchiflowWSFolder\Type\ModifyCabinet $parameters) : \ArchiflowWSFolder\Type\ModifyCabinetResponse
    {
        return $this->call('ModifyCabinet', $parameters);
    }

    /**
     * @param RequestInterface|Type\DeleteCabinet $parameters
     * @return ResultInterface|Type\DeleteCabinetResponse
     * @throws SoapException
     */
    public function deleteCabinet(\ArchiflowWSFolder\Type\DeleteCabinet $parameters) : \ArchiflowWSFolder\Type\DeleteCabinetResponse
    {
        return $this->call('DeleteCabinet', $parameters);
    }

    /**
     * @param RequestInterface|Type\AddCardInFolder $parameters
     * @return ResultInterface|Type\AddCardInFolderResponse
     * @throws SoapException
     */
    public function addCardInFolder(\ArchiflowWSFolder\Type\AddCardInFolder $parameters) : \ArchiflowWSFolder\Type\AddCardInFolderResponse
    {
        return $this->call('AddCardInFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\RemoveCardFromFolder $parameters
     * @return ResultInterface|Type\RemoveCardFromFolderResponse
     * @throws SoapException
     */
    public function removeCardFromFolder(\ArchiflowWSFolder\Type\RemoveCardFromFolder $parameters) : \ArchiflowWSFolder\Type\RemoveCardFromFolderResponse
    {
        return $this->call('RemoveCardFromFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\SetCardsFolders $parameters
     * @return ResultInterface|Type\SetCardsFoldersResponse
     * @throws SoapException
     */
    public function setCardsFolders(\ArchiflowWSFolder\Type\SetCardsFolders $parameters) : \ArchiflowWSFolder\Type\SetCardsFoldersResponse
    {
        return $this->call('SetCardsFolders', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetCardsInFolder $parameters
     * @return ResultInterface|Type\GetCardsInFolderResponse
     * @throws SoapException
     */
    public function getCardsInFolder(\ArchiflowWSFolder\Type\GetCardsInFolder $parameters) : \ArchiflowWSFolder\Type\GetCardsInFolderResponse
    {
        return $this->call('GetCardsInFolder', $parameters);
    }

    /**
     * @param RequestInterface|Type\SearchFoldersByParam $parameters
     * @return ResultInterface|Type\SearchFoldersByParamResponse
     * @throws SoapException
     */
    public function searchFoldersByParam(\ArchiflowWSFolder\Type\SearchFoldersByParam $parameters) : \ArchiflowWSFolder\Type\SearchFoldersByParamResponse
    {
        return $this->call('SearchFoldersByParam', $parameters);
    }

    /**
     * @param RequestInterface|Type\SendFolderByParam $parameters
     * @return ResultInterface|Type\SendFolderByParamResponse
     * @throws SoapException
     */
    public function sendFolderByParam(\ArchiflowWSFolder\Type\SendFolderByParam $parameters) : \ArchiflowWSFolder\Type\SendFolderByParamResponse
    {
        return $this->call('SendFolderByParam', $parameters);
    }


}

