<?php

namespace ArchiflowWSLogin;

use ArchiflowWSLogin\Type;
use Phpro\SoapClient\Type\RequestInterface;
use Phpro\SoapClient\Type\ResultInterface;
use Phpro\SoapClient\Exception\SoapException;

class ArchiFlowLoginClientClient extends \Phpro\SoapClient\Client
{

    /**
     * @param RequestInterface|Type\Login $parameters
     * @return ResultInterface|Type\LoginResponse
     * @throws SoapException
     */
    public function login(\ArchiflowWSLogin\Type\Login $parameters) : \ArchiflowWSLogin\Type\LoginResponse
    {
        return $this->call('Login', $parameters);
    }

    /**
     * @param RequestInterface|Type\LoginWithDeviceId $parameters
     * @return ResultInterface|Type\LoginWithDeviceIdResponse
     * @throws SoapException
     */
    public function loginWithDeviceId(\ArchiflowWSLogin\Type\LoginWithDeviceId $parameters) : \ArchiflowWSLogin\Type\LoginWithDeviceIdResponse
    {
        return $this->call('LoginWithDeviceId', $parameters);
    }

    /**
     * @param RequestInterface|Type\LoginWithCredentialAndDeviceIdWhiteList $parameters
     * @return ResultInterface|Type\LoginWithCredentialAndDeviceIdWhiteListResponse
     * @throws SoapException
     */
    public function loginWithCredentialAndDeviceIdWhiteList(\ArchiflowWSLogin\Type\LoginWithCredentialAndDeviceIdWhiteList $parameters) : \ArchiflowWSLogin\Type\LoginWithCredentialAndDeviceIdWhiteListResponse
    {
        return $this->call('LoginWithCredentialAndDeviceIdWhiteList', $parameters);
    }

    /**
     * @param RequestInterface|Type\LoginWithCredentialAndDeviceToken $parameters
     * @return ResultInterface|Type\LoginWithCredentialAndDeviceTokenResponse
     * @throws SoapException
     */
    public function loginWithCredentialAndDeviceToken(\ArchiflowWSLogin\Type\LoginWithCredentialAndDeviceToken $parameters) : \ArchiflowWSLogin\Type\LoginWithCredentialAndDeviceTokenResponse
    {
        return $this->call('LoginWithCredentialAndDeviceToken', $parameters);
    }

    /**
     * @param RequestInterface|Type\Logout $parameters
     * @return ResultInterface|Type\LogoutResponse
     * @throws SoapException
     */
    public function logout(\ArchiflowWSLogin\Type\Logout $parameters) : \ArchiflowWSLogin\Type\LogoutResponse
    {
        return $this->call('Logout', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetLicense $parameters
     * @return ResultInterface|Type\GetLicenseResponse
     * @throws SoapException
     */
    public function getLicense(\ArchiflowWSLogin\Type\GetLicense $parameters) : \ArchiflowWSLogin\Type\GetLicenseResponse
    {
        return $this->call('GetLicense', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetLicenses $parameters
     * @return ResultInterface|Type\GetLicensesResponse
     * @throws SoapException
     */
    public function getLicenses(\ArchiflowWSLogin\Type\GetLicenses $parameters) : \ArchiflowWSLogin\Type\GetLicensesResponse
    {
        return $this->call('GetLicenses', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetSingleLicense $parameters
     * @return ResultInterface|Type\GetSingleLicenseResponse
     * @throws SoapException
     */
    public function getSingleLicense(\ArchiflowWSLogin\Type\GetSingleLicense $parameters) : \ArchiflowWSLogin\Type\GetSingleLicenseResponse
    {
        return $this->call('GetSingleLicense', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDomains $parameters
     * @return ResultInterface|Type\GetDomainsResponse
     * @throws SoapException
     */
    public function getDomains(\ArchiflowWSLogin\Type\GetDomains $parameters) : \ArchiflowWSLogin\Type\GetDomainsResponse
    {
        return $this->call('GetDomains', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDatabaseType $parameters
     * @return ResultInterface|Type\GetDatabaseTypeResponse
     * @throws SoapException
     */
    public function getDatabase_Type(\ArchiflowWSLogin\Type\GetDatabaseType $parameters) : \ArchiflowWSLogin\Type\GetDatabaseTypeResponse
    {
        return $this->call('GetDatabase_Type', $parameters);
    }

    /**
     * @param RequestInterface|Type\GetDatabaseTypeEx $parameters
     * @return ResultInterface|Type\GetDatabaseTypeExResponse
     * @throws SoapException
     */
    public function getDatabase_Type_Ex(\ArchiflowWSLogin\Type\GetDatabaseTypeEx $parameters) : \ArchiflowWSLogin\Type\GetDatabaseTypeExResponse
    {
        return $this->call('GetDatabase_Type_Ex', $parameters);
    }


}

