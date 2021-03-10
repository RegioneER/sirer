<?php

namespace ArchiflowWSLogin;

use ArchiflowWSLogin\Type;
use Phpro\SoapClient\Soap\ClassMap\ClassMapCollection;
use Phpro\SoapClient\Soap\ClassMap\ClassMap;

class ArchiFlowLoginClientClassmap
{

    public static function getCollection() : \Phpro\SoapClient\Soap\ClassMap\ClassMapCollection
    {
        return new ClassMapCollection([
            new ClassMap('ArrayOfLicenseOptions', Type\ArrayOfLicenseOptions::class),
            new ClassMap('ArrayOfint', Type\ArrayOfint::class),
            new ClassMap('ArrayOfOfficeChart', Type\ArrayOfOfficeChart::class),
            new ClassMap('OfficeChart', Type\OfficeChart::class),
            new ClassMap('LoggableBase', Type\LoggableBase::class),
            new ClassMap('ConnectionInfo', Type\ConnectionInfo::class),
            new ClassMap('SessionInfo', Type\SessionInfo::class),
            new ClassMap('ArrayOfLicenseOption', Type\ArrayOfLicenseOption::class),
            new ClassMap('LicenseOption', Type\LicenseOption::class),
            new ClassMap('ArrayOfArchiflowDomain', Type\ArrayOfArchiflowDomain::class),
            new ClassMap('ArchiflowDomain', Type\ArchiflowDomain::class),
            new ClassMap('Login', Type\Login::class),
            new ClassMap('LoginResponse', Type\LoginResponse::class),
            new ClassMap('LoginWithDeviceId', Type\LoginWithDeviceId::class),
            new ClassMap('LoginWithDeviceIdResponse', Type\LoginWithDeviceIdResponse::class),
            new ClassMap('LoginWithCredentialAndDeviceIdWhiteList', Type\LoginWithCredentialAndDeviceIdWhiteList::class),
            new ClassMap('LoginWithCredentialAndDeviceIdWhiteListResponse', Type\LoginWithCredentialAndDeviceIdWhiteListResponse::class),
            new ClassMap('LoginWithCredentialAndDeviceToken', Type\LoginWithCredentialAndDeviceToken::class),
            new ClassMap('LoginWithCredentialAndDeviceTokenResponse', Type\LoginWithCredentialAndDeviceTokenResponse::class),
            new ClassMap('Logout', Type\Logout::class),
            new ClassMap('LogoutResponse', Type\LogoutResponse::class),
            new ClassMap('GetLicense', Type\GetLicense::class),
            new ClassMap('GetLicenseResponse', Type\GetLicenseResponse::class),
            new ClassMap('GetLicenses', Type\GetLicenses::class),
            new ClassMap('GetLicensesResponse', Type\GetLicensesResponse::class),
            new ClassMap('GetSingleLicense', Type\GetSingleLicense::class),
            new ClassMap('GetSingleLicenseResponse', Type\GetSingleLicenseResponse::class),
            new ClassMap('GetDomains', Type\GetDomains::class),
            new ClassMap('GetDomainsResponse', Type\GetDomainsResponse::class),
            new ClassMap('GetDatabase_Type', Type\GetDatabaseType::class),
            new ClassMap('GetDatabase_TypeResponse', Type\GetDatabaseTypeResponse::class),
            new ClassMap('GetDatabase_Type_Ex', Type\GetDatabaseTypeEx::class),
            new ClassMap('GetDatabase_Type_ExResponse', Type\GetDatabaseTypeExResponse::class),
            new ClassMap('LoginFault', Type\LoginFault::class),
            new ClassMap('BaseFault', Type\BaseFault::class),
            new ClassMap('UserAccountDisabledFault', Type\UserAccountDisabledFault::class),
            new ClassMap('ChangePasswordFault', Type\ChangePasswordFault::class),
            new ClassMap('InvalidSessionFault', Type\InvalidSessionFault::class),
            new ClassMap('InvalidPasswordFault', Type\InvalidPasswordFault::class),
            new ClassMap('InvalidPasswordLengthFault', Type\InvalidPasswordLengthFault::class),
            new ClassMap('InvalidPasswordFormatFault', Type\InvalidPasswordFormatFault::class),
            new ClassMap('InvalidExecutiveOfficeFault', Type\InvalidExecutiveOfficeFault::class),
            new ClassMap('LoginTicketSapFault', Type\LoginTicketSapFault::class),
            new ClassMap('ParamValidationFault', Type\ParamValidationFault::class),
            new ClassMap('ArchiflowServiceExceptionDetail', Type\ArchiflowServiceExceptionDetail::class),
        ]);
    }


}

