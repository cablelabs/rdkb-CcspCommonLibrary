/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/


/**********************************************************************

    module: dslh_objco_internal_api.h

        For DSL Home Model Implementation (DSLH),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco System  , Inc.,
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the Dslh Obj Controller
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        10/03/2005    initial revision.
        09/22/2011    Bin added GetBulkParamValue apis;

**********************************************************************/


#ifndef  _DSLH_OBJCO_INTERNAL_API_
#define  _DSLH_OBJCO_INTERNAL_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN DSLH_OBJCO_STATES.C
***********************************************************/

ANSC_HANDLE
DslhObjcoGetInsContext
    (
        ANSC_HANDLE                 hThisObject
    );

BOOL
DslhObjcoCheckInstance
    (
        ANSC_HANDLE                 hThisObject
    );

BOOL
DslhObjcoCheckParamExistence
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pParamName
    );

ULONG
DslhObjcoCheckParamWritability
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pParamName
    );

BOOL
DslhObjcoValidateHierarchyInterface
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pParamName,
        ULONG                       uType
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN DSLH_OBJCO_ACCESS.C
***********************************************************/

ANSC_STATUS
DslhObjcoEngage
    (
        ANSC_HANDLE                 hThisObject
    );

BOOL
DslhObjcoValidate
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDslhRvqIf,
        char**                      ppFaultParamName
    );

ANSC_STATUS
DslhObjcoCommit
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDslhRvqIf
    );

ANSC_STATUS
DslhObjcoRollback
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
DslhObjcoGetParamValueByName
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName,
        PSLAP_VARIABLE              pVariable
    );

ANSC_STATUS
DslhObjcoGetBulkParamValue
    (
        ANSC_HANDLE                 hInsContext,
        char**                      pParamArray,
        PSLAP_VARIABLE*             ppVarArray,
        ULONG                       ulArraySize
    );

#endif
