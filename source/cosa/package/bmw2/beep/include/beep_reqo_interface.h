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

    module:	beep_reqo_interface.h

        For BSP Execution Environment Plane Implementation (BEEP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2003
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the BEEP Request Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/23/03    initial revision.

**********************************************************************/


#ifndef  _BEEP_REQO_INTERFACE_
#define  _BEEP_REQO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "slap_co_interface.h"
#include "slap_co_exported_api.h"


/***********************************************************
     PLATFORM INDEPENDENT BEEP REQUEST OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
typedef  ANSC_HANDLE
(*PFN_BEEPREQO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_BEEPREQO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

typedef  ANSC_HANDLE
(*PFN_BEEPREQO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_BEEPREQO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

typedef  ANSC_STATUS
(*PFN_BEEPREQO_GET_VAR1)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       varName,
        char*                       varValue,
        PULONG                      pulSize
    );

typedef  ANSC_STATUS
(*PFN_BEEPREQO_GET_VAR2)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulCgiVarId,
        char*                       varValue,
        PULONG                      pulSize
    );

typedef  ULONG
(*PFN_BEEPREQO_GET_AUTH_TYPE)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ULONG
(*PFN_BEEPREQO_GET_LENGTH)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_STATUS
(*PFN_BEEPREQO_GET_TYPE)
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pulMediaType,
        PULONG                      pulSubType
    );

typedef  char*
(*PFN_BEEPREQO_GET_ROOT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_PATH_INFO)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_PATH_TRAN)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_QUERY_STR)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_FORM_CONT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  PUCHAR
(*PFN_BEEPREQO_GET_ADDR)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_HOST)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_USER)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ULONG
(*PFN_BEEPREQO_GET_METHOD)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_SCRIPT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_NAME)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  USHORT
(*PFN_BEEPREQO_GET_PORT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_PROTOCOL)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_SOFTWARE)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  ANSC_HANDLE
(*PFN_BEEPREQO_GET_INPUT)
    (
        ANSC_HANDLE                 hThisObject
    );

typedef  char*
(*PFN_BEEPREQO_GET_PARAM)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       name
    );

/*
 * HTTP messages consist of requests from client to server and responses from server to client.
 *
 *      HTTP-message = Request | Response ; HTTP/1.1 messages
 *
 * Request and Response messages use the generic message format of RFC 822 for transferring
 * entities (the payload of hte message). Both types of message consist of a start-line, zero or
 * more header fields (also known as "headers"), an empty line (i.e., a line with nothing preceding
 * the CRLF) indicating the end of the header fields, and possibly a message-body.
 *
 *      generic-message = start-line
 *                        *(message-header CRLF)
 *                        CRLF
 *                        [message-body]
 *      start-line      = Request-Line | Status-Line
 *
 * In the interest of robustness, servers SHOULD ignore any empty line(s) received where a Request-
 * Line is expected. In other words, if the server is reading the protocol stream at the begining
 * of a message and receives a CRLF first, it should ignore the CRLF.
 */
#define  BEEP_REQUEST_CLASS_CONTENT                                                         \
    /* duplication of the base object class content */                                      \
    SLAP_COMPONENT_CLASS_CONTENT                                                            \
    /* start of object class content */                                                     \
    ANSC_HANDLE                     hHttpBmoReq;                                            \
                                                                                            \
    PFN_BEEPREQO_GET_CONTEXT        GetHttpBmoReq;                                          \
    PFN_BEEPREQO_SET_CONTEXT        SetHttpBmoReq;                                          \
                                                                                            \
    PFN_BEEPREQO_GET_VAR1           GetEnvVariableByName;                                   \
    PFN_BEEPREQO_GET_VAR2           GetEnvVariableById;                                     \
    PFN_BEEPREQO_GET_AUTH_TYPE      GetAuthType;                                            \
    PFN_BEEPREQO_GET_LENGTH         GetContentLength;                                       \
    PFN_BEEPREQO_GET_TYPE           GetContentType;                                         \
    PFN_BEEPREQO_GET_ROOT           GetDocumentRoot;                                        \
    PFN_BEEPREQO_GET_PATH_INFO      GetPathInfo;                                            \
    PFN_BEEPREQO_GET_PATH_TRAN      GetPathTranslated;                                      \
    PFN_BEEPREQO_GET_QUERY_STR      GetQueryString;                                         \
    PFN_BEEPREQO_GET_FORM_CONT      GetFormContent;                                         \
    PFN_BEEPREQO_GET_ADDR           GetRemoteAddr;                                          \
    PFN_BEEPREQO_GET_HOST           GetRemoteHost;                                          \
    PFN_BEEPREQO_GET_USER           GetRemoteUser;                                          \
    PFN_BEEPREQO_GET_METHOD         GetRequestMethod;                                       \
    PFN_BEEPREQO_GET_SCRIPT         GetScriptName;                                          \
    PFN_BEEPREQO_GET_NAME           GetServerName;                                          \
    PFN_BEEPREQO_GET_PORT           GetServerPort;                                          \
    PFN_BEEPREQO_GET_PROTOCOL       GetServerProtocol;                                      \
    PFN_BEEPREQO_GET_SOFTWARE       GetServerSoftware;                                      \
    PFN_BEEPREQO_GET_INPUT          GetHtmlFormInput;                                       \
    PFN_BEEPREQO_GET_PARAM          GetHtmlFormParam;                                       \
    /* end of object class content */                                                       \

typedef  struct
_BEEP_REQUEST_OBJECT
{
    BEEP_REQUEST_CLASS_CONTENT
}
BEEP_REQUEST_OBJECT,  *PBEEP_REQUEST_OBJECT;

#define  ACCESS_BEEP_REQUEST_OBJECT(p)              \
         ACCESS_CONTAINER(p, BEEP_REQUEST_OBJECT, Linkage)


#endif
