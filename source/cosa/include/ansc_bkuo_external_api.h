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

    module:	ansc_bkuo_external_api.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco System  , Inc., 1997 ~ 2001
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the external functions provided by the Broker Socket Udp
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        01/13/02    initial revision.

**********************************************************************/


#ifndef  _ANSC_BKUO_EXTERNAL_API_
#define  _ANSC_BKUO_EXTERNAL_API_


/***********************************************************
       FUNCTIONS IMPLEMENTED IN ANSC_BKUO_INTERFACE.C
***********************************************************/

ANSC_HANDLE
AnscCreateBrokerSocketUdp
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
          FUNCTIONS IMPLEMENTED IN ANSC_BKUO_BASE.C
***********************************************************/

ANSC_HANDLE
AnscBkuoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

ANSC_STATUS
AnscBkuoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscBkuoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscBkuoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
