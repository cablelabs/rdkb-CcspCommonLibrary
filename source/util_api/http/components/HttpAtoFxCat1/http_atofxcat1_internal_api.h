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

    module:	http_atofxcat1_internal_api.h

        For HyperText Transfer Protocol Implementation (HTTP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2002
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the Http Ato FxCat1
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        03/20/02    initial revision.

**********************************************************************/


#ifndef  _HTTP_ATOFXCAT1_INTERNAL_API_
#define  _HTTP_ATOFXCAT1_INTERNAL_API_


/***********************************************************
     FUNCTIONS IMPLEMENTED IN HTTP_ATOFXCAT1_OPERATION.C
***********************************************************/

ANSC_STATUS
HttpAtoFxCat1CreateCodeTable
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
HttpAtoFxCat1CreateNameTable
    (
        ANSC_HANDLE                 hThisObject
    );

ULONG
HttpAtoFxCat1GetAtomCode
    (
        ANSC_HANDLE                 hThisObject,
        char*                       name
    );

char*
HttpAtoFxCat1GetAtomName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       code
    );


#endif
