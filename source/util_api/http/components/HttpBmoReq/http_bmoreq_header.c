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

    module:	http_bmoreq_header.c

        For HyperText Transfer Protocol Implementation (HTTP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2002
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the advanced state-access functions
        of the Http Bmo Req Object.

        *   HttpBmoReqDelStartLine
        *   HttpBmoReqParseStartLine
        *   HttpBmoReqCopyStartLineFrom

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        02/27/02    initial revision.

**********************************************************************/


#include "http_bmoreq_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpBmoReqDelStartLine
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to clean start line information.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpBmoReqDelStartLine
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PHTTP_BMO_REQ_OBJECT            pMyObject    = (PHTTP_BMO_REQ_OBJECT)hThisObject;
    PHTTP_HFP_INTERFACE             pHfpIf       = (PHTTP_HFP_INTERFACE )pMyObject->hHfpIf;
    PHTTP_REQUEST_INFO              pReqInfo     = (PHTTP_REQUEST_INFO  )pMyObject->hReqInfo;

    if ( pReqInfo )
    {
        AnscFreeMemory(pReqInfo);

        pMyObject->hReqInfo = (ANSC_HANDLE)NULL;
    }

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpBmoReqParseStartLine
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to parse start line information.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpBmoReqParseStartLine
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus  = ANSC_STATUS_SUCCESS;
    PHTTP_BMO_REQ_OBJECT            pMyObject     = (PHTTP_BMO_REQ_OBJECT   )hThisObject;
    PHTTP_HFP_INTERFACE             pHfpIf        = (PHTTP_HFP_INTERFACE    )pMyObject->hHfpIf;
    PANSC_BUFFER_DESCRIPTOR         pHeaderBdo    = (PANSC_BUFFER_DESCRIPTOR)pMyObject->hHeaderBdo;
    PHTTP_REQUEST_INFO              pReqInfo      = (PHTTP_REQUEST_INFO     )pMyObject->hReqInfo;
    PVOID                           pHeaderBuffer = NULL;
    ULONG                           ulBufferSize  = 0;
    char*                           pHfStart      = NULL;
    ULONG                           ulSkipSize    = 0;
    char*                           pRawHfLine    = NULL;
    char*                           pStdHfLine    = (char*)pMyObject->ScratchPad1;
    ULONG                           ulRawLineSize = 0;
    ULONG                           ulStdLineSize = 0;

    pMyObject->DelStartLine((ANSC_HANDLE)pMyObject);

    if ( !pHeaderBdo )
    {
        return  ANSC_STATUS_UNAPPLICABLE;
    }
    else
    {
        pHeaderBuffer = AnscBdoGetBlock    (pHeaderBdo);
        ulBufferSize  = AnscBdoGetBlockSize(pHeaderBdo);
    }

    AnscHttpFindHfStart(pHeaderBuffer, ulBufferSize, pHfStart);

    if ( !pHfStart )
    {
        return  ANSC_STATUS_UNAPPLICABLE;
    }
    else
    {
        ulSkipSize    = (ULONG)pHfStart - (ULONG)pHeaderBuffer;
        ulBufferSize -= ulSkipSize;
        pRawHfLine    = pHfStart;
    }

    AnscHttpGetHfLineSize(pRawHfLine, ulBufferSize, ulRawLineSize);

    if ( ulRawLineSize <= pMyObject->PadSize1 )
    {
        AnscHttpPrepareHeader(pRawHfLine, ulRawLineSize, pStdHfLine, ulStdLineSize);

        pStdHfLine[ulStdLineSize + 0] = HTTP_CARRIAGE_RETURN;
        pStdHfLine[ulStdLineSize + 1] = HTTP_LINE_FEED;

        pReqInfo =
            (PHTTP_REQUEST_INFO)pHfpIf->ParseRequestLine
                (
                    pHfpIf->hOwnerContext,
                    pStdHfLine,
                    ulStdLineSize
                );
    }
    else
    {
        pReqInfo = NULL;
    }

    if ( !pReqInfo )
    {
        return  ANSC_STATUS_BAD_PAYLOAD;
    }
    else
    {
        pMyObject->hReqInfo = (ANSC_HANDLE)pReqInfo;
    }

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpBmoReqCopyStartLineFrom
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       buffer,
                PULONG                      pulSize
            );

    description:

        This function is called to copy the start line from the
        internal buffer into an external buffer.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       buffer
                Specifies the external buffer where the data to be
                copied to.

                PULONG                      pulSize
                Specifies the size of the external buffer as the
                inbound parameter and size of copied payload data as
                the outbound parameter.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpBmoReqCopyStartLineFrom
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        PULONG                      pulSize
    )
{
    ANSC_STATUS                     returnStatus    = ANSC_STATUS_SUCCESS;
    PHTTP_BMO_REQ_OBJECT            pMyObject       = (PHTTP_BMO_REQ_OBJECT)hThisObject;
    PHTTP_HFP_INTERFACE             pHfpIf          = (PHTTP_HFP_INTERFACE )pMyObject->hHfpIf;
    PHTTP_REQUEST_INFO              pReqInfo        = (PHTTP_REQUEST_INFO  )pMyObject->hReqInfo;
    ULONG                           ulStartLineSize = pMyObject->GetStartLineSize((ANSC_HANDLE)pMyObject);

    if ( *pulSize < ulStartLineSize )
    {
        return  ANSC_STATUS_BAD_SIZE;
    }

    returnStatus =
        pHfpIf->BuildRequestLine
            (
                pHfpIf->hOwnerContext,
                (ANSC_HANDLE)pReqInfo,
                buffer,
                ulStartLineSize
            );

    *pulSize = ulStartLineSize;

    return  returnStatus;
}
