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

    module:	cf_bmo_co_util.h

        For Content Filtering Utilities,
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2001
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the content filtering
        basic message component object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        03/13/02    initial revision.

    ---------------------------------------------------------------

    last modified:  
    

**********************************************************************/


#ifndef  _CF_BMO_CO_UTIL_API_
#define  _CF_BMO_CO_UTIL_API_

typedef
enum _CF_MESSAGE_CATEGORY
{
    CF_MSG_AUTHENTICATION = 0,
    CF_MSG_FILTERING,
    CF_MSG_REPORTING
}
CF_MESSAGE_CATEGORY;

ANSC_HANDLE
ParseCfMessage
    ( 
        PCHAR                       pBuffer, 
        ULONG                       ulBufferLen, 
        BOOLEAN                     bIsRequest,
        CF_MESSAGE_CATEGORY         Category
    );

ANSC_HANDLE
ParseCfAuthMessage
    (
        PANSC_XML_DOM_NODE_OBJECT   pRootNode,
        BOOL                        bIsRequest
    );

ANSC_HANDLE
ParseCfFilterMessage
    (
        PANSC_XML_DOM_NODE_OBJECT   pRootNode,
        BOOL                        bIsRequest
    );

ANSC_HANDLE
ParseCfReportMessage
    (
        PANSC_XML_DOM_NODE_OBJECT   pRootNode,
        BOOL                        bIsRequest
    );

#endif
