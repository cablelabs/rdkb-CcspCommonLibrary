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

    module:	ansc_uint_array_co_internal_api.h

        For UInt Array object,
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2001
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the Object Array component
        object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        03/14/02    initial revision.


    ---------------------------------------------------------------

    last modified:  
    

**********************************************************************/

#ifndef  _ANSC_UINT_ARRAY_CO_INTERNAL_API
#define  _ANSC_UINT_ARRAY_CO_INTERNAL_API


ULONG
AnscUIntArrayGetSize
    (
        ANSC_HANDLE                 hThisObject
    );


void
AnscUIntArraySetSize
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulNewSize,
        ULONG                       ulGrowBy
    );


void
AnscUIntArrayRemoveAll
    (
        ANSC_HANDLE                 hThisObject
    );


ANSC_OBJECT_ARRAY_DATA
AnscUIntArrayGetAt
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulIndex
    );


void
AnscUIntArraySetAt
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulIndex,
        ANSC_OBJECT_ARRAY_DATA      Data
    );

void
AnscUIntArrayInsertAt
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulIndex,
        ANSC_OBJECT_ARRAY_DATA      Data,
        ULONG                       ulCount
    );


void
AnscUIntArrayRemoveAt
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulIndex,
        ULONG                       ulCount
    );


ULONG
AnscUIntArrayAdd
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_OBJECT_ARRAY_DATA      Data
    );


void
AnscUIntArrayEnlargeStorage
    (   
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulNewSize
    );

LONG
AnscUIntArrayFind
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_OBJECT_ARRAY_DATA      Data
    );

#endif

