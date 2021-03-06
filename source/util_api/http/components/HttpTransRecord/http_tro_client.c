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

    module:	http_tro_client.c

        For HyperText Transfer Protocol Implementation (HTTP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2002
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the advanced process functions
        of the Http Trans Record Object.

        *   HttpTroQueryForClient
        *   HttpTroRecvFromClient
        *   HttpTroFinishedByClient
        *   HttpTroSendToClient
        *   HttpTroResumeTransaction

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        03/05/02    initial revision.

**********************************************************************/


#include "http_tro_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        HttpTroQueryForClient
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       buffer,
                ULONG                       ulSize,
                ANSC_HANDLE                 hBufferContext
            );

    description:

        This function is called to query the processing mode.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       buffer
                Specifies the data buffer to be processed.

                ULONG                       ulSize
                Specifies the size of data buffer to be processed.

                ANSC_HANDLE                 hBufferContext
                Specifies the context handle associated with the buffer.

    return:     process mode.

**********************************************************************/

ULONG
HttpTroQueryForClient
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hBufferContext
    )
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PHTTP_TRANS_RECORD_OBJECT       pMyObject      = (PHTTP_TRANS_RECORD_OBJECT     )hThisObject;
    PHTTP_ADVANCED_PROXY_OBJECT     pAdvancedProxy = (PHTTP_ADVANCED_PROXY_OBJECT   )pMyObject->hOwnerContext;
    PHTTP_WAM_INTERFACE             pWamIf         = (PHTTP_WAM_INTERFACE           )pMyObject->hWamIf;
    PHTTP_SBC_INTERFACE             pSbcIf         = (PHTTP_SBC_INTERFACE           )pMyObject->hSbcIf;
    PANSC_DAEMON_SOCKET_TCP_OBJECT  pClientSocket  = (PANSC_DAEMON_SOCKET_TCP_OBJECT)pMyObject->hClientSocket;
    PANSC_BUFFER_DESCRIPTOR         pBufferDesp    = (PANSC_BUFFER_DESCRIPTOR       )hBufferContext;
    PHTTP_BMO_REQ_OBJECT            pBmoReq        = (PHTTP_BMO_REQ_OBJECT          )pMyObject->hBmoReq;
    ULONG                           ulTroQmode     = HTTP_TRO_QMODE_FORWARD;
    ULONG                           ulBmoState1    = HTTP_BMO_STATE_EMPTY;
    ULONG                           ulBmoState2    = HTTP_BMO_STATE_EMPTY;

    /*
     * If the SBC (Server Behavior Controller) has allowed everything to be relayed internally by
     * the proxy object itself (or simply because there's no SBC registered), we SHALL pass payload
     * data from one socket to the other, whenever there's data available.
     */
    if ( (pMyObject->TransState == HTTP_TRO_STATE_ESTABLISHED) &&
         (pMyObject->SbcPmode   == HTTP_SBC_PMODE_RELAY2     ) )
    {
        return  HTTP_TRO_QMODE_FORWARD;
    }

    /*
     * The decision on how to process the received payload should be made based on two message
     * states: the message state before payload arrival and the state after. The caller must ensure
     * the consistency of the buffer descriptor.
     */
    buffer      = AnscBdoGetBlock    (pBufferDesp);
    ulSize      = AnscBdoGetBlockSize(pBufferDesp);
    ulBmoState1 = pBmoReq->GetState((ANSC_HANDLE)pBmoReq);
    ulBmoState2 =
        pBmoReq->Examine
            (
                (ANSC_HANDLE)pBmoReq,
                buffer,
                ulSize
            );

    switch ( ulBmoState2 )
    {
        case    HTTP_BMO_STATE_EMPTY :
        case    HTTP_BMO_STATE_PART_HEADER :

                ulTroQmode = HTTP_TRO_QMODE_COLLECT;

                break;

        case    HTTP_BMO_STATE_HEADER_ARRIVED :

                ulTroQmode = HTTP_TRO_QMODE_PROCESS;

                break;

        case    HTTP_BMO_STATE_PART_BODY :

                if ( ulBmoState1 == HTTP_BMO_STATE_PART_BODY )
                {
                    if ( AnscBdoGetLeftSize(pBufferDesp) > HTTP_SPO_RECV_BUFFER_ROOM )
                    {
                        ulTroQmode = HTTP_TRO_QMODE_COLLECT;
                    }
                    else
                    {
                        ulTroQmode = HTTP_TRO_QMODE_PROCESS;
                    }
                }
                else
                {
                    ulTroQmode = HTTP_TRO_QMODE_PROCESS;
                }

                break;

        case    HTTP_BMO_STATE_COMPLETE :
        case    HTTP_BMO_STATE_OVER_PACKED :

                ulTroQmode = HTTP_TRO_QMODE_PROCESS;

                break;

        case    HTTP_BMO_STATE_UNKNOWN :

                ulTroQmode = HTTP_TRO_QMODE_PROCESS;

                break;

        default :

                ulTroQmode = HTTP_TRO_QMODE_COLLECT;

                break;
    }

    return  ulTroQmode;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpTroRecvFromClient
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       buffer,
                ULONG                       ulSize,
                ANSC_HANDLE                 hBufferContext
            );

    description:

        This function is called to process received payloads.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       buffer
                Specifies the data buffer to be processed.

                ULONG                       ulSize
                Specifies the size of data buffer to be processed.

                ANSC_HANDLE                 hBufferContext
                Specifies the context handle associated with the buffer.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpTroRecvFromClient
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hBufferContext
    )
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PHTTP_TRANS_RECORD_OBJECT       pMyObject      = (PHTTP_TRANS_RECORD_OBJECT     )hThisObject;
    PHTTP_ADVANCED_PROXY_OBJECT     pAdvancedProxy = (PHTTP_ADVANCED_PROXY_OBJECT   )pMyObject->hOwnerContext;
    PHTTP_WAM_INTERFACE             pWamIf         = (PHTTP_WAM_INTERFACE           )pMyObject->hWamIf;
    PHTTP_SBC_INTERFACE             pSbcIf         = (PHTTP_SBC_INTERFACE           )pMyObject->hSbcIf;
    PANSC_DAEMON_SOCKET_TCP_OBJECT  pClientSocket  = (PANSC_DAEMON_SOCKET_TCP_OBJECT)pMyObject->hClientSocket;
    PANSC_BROKER_SOCKET_TCP_OBJECT  pServerSocket  = (PANSC_BROKER_SOCKET_TCP_OBJECT)pMyObject->hServerSocket;
    PANSC_BUFFER_DESCRIPTOR         pBufferDesp    = (PANSC_BUFFER_DESCRIPTOR       )hBufferContext;
    PHTTP_BMO_REQ_OBJECT            pBmoReq        = (PHTTP_BMO_REQ_OBJECT          )pMyObject->hBmoReq;
    ULONG                           ulBmoState     = HTTP_BMO_STATE_EMPTY;

    /*
     * At time like this, you will always have two options on how to proceed with the message
     * processing:
     *
     *      $ Examine the current object states and the content of the message payload
     *        to make the processing decisions in this object.
     *
     *      $ Offload the examination and certain state-transition functions to another
     *        object and provide an interface to be notified when something happens.
     *
     * Guess which one we're using here ...
     */
    buffer       = AnscBdoGetBlock    (pBufferDesp);
    ulSize       = AnscBdoGetBlockSize(pBufferDesp);
    returnStatus =
        pBmoReq->Process
            (
                (ANSC_HANDLE)pBmoReq,
                (ANSC_HANDLE)pBufferDesp
            );

    if ( (returnStatus != ANSC_STATUS_SUCCESS    ) &&
         (returnStatus != ANSC_STATUS_DO_IT_AGAIN) )
    {
        pMyObject->TransState = HTTP_TRO_STATE_FINISHED;
    }

    return  returnStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpTroFinishedByClient
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       buffer,
                ULONG                       ulSize,
                ANSC_HANDLE                 hBufferContext
            );

    description:

        This function is called when the client connection is being
        closed which indicates that no more data will be sent to the
        server from the client.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       buffer
                Specifies the data buffer to be processed.

                ULONG                       ulSize
                Specifies the size of data buffer to be processed.

                ANSC_HANDLE                 hBufferContext
                Specifies the context handle associated with the buffer.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpTroFinishedByClient
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hBufferContext
    )
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PHTTP_TRANS_RECORD_OBJECT       pMyObject      = (PHTTP_TRANS_RECORD_OBJECT     )hThisObject;
    PHTTP_ADVANCED_PROXY_OBJECT     pAdvancedProxy = (PHTTP_ADVANCED_PROXY_OBJECT   )pMyObject->hOwnerContext;
    PHTTP_WAM_INTERFACE             pWamIf         = (PHTTP_WAM_INTERFACE           )pMyObject->hWamIf;
    PHTTP_SBC_INTERFACE             pSbcIf         = (PHTTP_SBC_INTERFACE           )pMyObject->hSbcIf;
    PANSC_DAEMON_SOCKET_TCP_OBJECT  pClientSocket  = (PANSC_DAEMON_SOCKET_TCP_OBJECT)pMyObject->hClientSocket;
    PANSC_BROKER_SOCKET_TCP_OBJECT  pServerSocket  = (PANSC_BROKER_SOCKET_TCP_OBJECT)pMyObject->hServerSocket;
    PHTTP_BMO_REQ_OBJECT            pBmoReq        = (PHTTP_BMO_REQ_OBJECT          )pMyObject->hBmoReq;
    PANSC_BUFFER_DESCRIPTOR         pBufferDesp    = (PANSC_BUFFER_DESCRIPTOR       )hBufferContext;
    ULONG                           ulBmoState     = pBmoReq->GetState((ANSC_HANDLE)pBmoReq);

    if ( (ulBmoState == HTTP_BMO_STATE_COMPLETE   ) ||
         (ulBmoState == HTTP_BMO_STATE_OVER_PACKED) )
    {
        if ( pBufferDesp )
        {
            AnscFreeBdo((ANSC_HANDLE)pBufferDesp);
        }

        return  ANSC_STATUS_UNAPPLICABLE;
    }

    buffer       = AnscBdoGetBlock    (pBufferDesp);
    ulSize       = AnscBdoGetBlockSize(pBufferDesp);
    returnStatus =
        pBmoReq->CloseUp
            (
                (ANSC_HANDLE)pBmoReq,
                (ANSC_HANDLE)pBufferDesp
            );

    return  returnStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpTroSendToClient
            (
                ANSC_HANDLE                 hThisObject,
                ANSC_HANDLE                 hMessage,
                ULONG                       ulSendFlags
            );

    description:

        This function is called to send a message to client.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ANSC_HANDLE                 hMessage
                Specifies the message to be sent.

                ULONG                       ulSendFlags
                Specifies the operational flags for sending.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpTroSendToClient
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hMessage,
        ULONG                       ulSendFlags
    )
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PHTTP_TRANS_RECORD_OBJECT       pMyObject      = (PHTTP_TRANS_RECORD_OBJECT     )hThisObject;
    PHTTP_ADVANCED_PROXY_OBJECT     pAdvancedProxy = (PHTTP_ADVANCED_PROXY_OBJECT   )pMyObject->hOwnerContext;
    PANSC_DAEMON_SOCKET_TCP_OBJECT  pClientSocket  = (PANSC_DAEMON_SOCKET_TCP_OBJECT)pMyObject->hClientSocket;
    PANSC_BROKER_SOCKET_TCP_OBJECT  pServerSocket  = (PANSC_BROKER_SOCKET_TCP_OBJECT)pMyObject->hServerSocket;
    PHTTP_BMO_REP_OBJECT            pBmoRep        = (PHTTP_BMO_REP_OBJECT          )hMessage;
    ANSC_HANDLE                     hOrgTmhIf      = pBmoRep->GetTmhIf((ANSC_HANDLE)pBmoRep);

    if ( !pClientSocket )
    {
        return  ANSC_STATUS_INTERNAL_ERROR;
    }

    pBmoRep->SetTmhIf((ANSC_HANDLE)pBmoRep, pMyObject->hTmhClientIf);

    if ( ulSendFlags & HTTP_TRO_SFLAG_HEADERS )
    {
        returnStatus =
            pBmoRep->OutputHeaders
                (
                    (ANSC_HANDLE)pBmoRep,
                    (ANSC_HANDLE)pClientSocket
                );
    }

    if ( ulSendFlags & HTTP_TRO_SFLAG_BODY )
    {
        returnStatus =
            pBmoRep->OutputBody
                (
                    (ANSC_HANDLE)pBmoRep,
                    (ANSC_HANDLE)pClientSocket
                );
    }

    pBmoRep->SetTmhIf((ANSC_HANDLE)pBmoRep, hOrgTmhIf);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        HttpTroResumeTransaction
            (
                ANSC_HANDLE                 hThisObject,
                ANSC_HANDLE                 hReserved,
                ULONG                       ulSbcPmode
            );

    description:

        This function is called by a Behavior Controller Object to
        resume the transaction.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ANSC_HANDLE                 hReserved
                Specifies the reserved field for future use.

                ULONG                       ulSbcPmode
                Specifies the processing mode for SBC.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
HttpTroResumeTransaction
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hReserved,
        ULONG                       ulSbcPmode
    )
{
    ANSC_STATUS                     returnStatus   = ANSC_STATUS_SUCCESS;
    PHTTP_TRANS_RECORD_OBJECT       pMyObject      = (PHTTP_TRANS_RECORD_OBJECT     )hThisObject;
    PHTTP_ADVANCED_PROXY_OBJECT     pAdvancedProxy = (PHTTP_ADVANCED_PROXY_OBJECT   )pMyObject->hOwnerContext;
    PHTTP_ADVANCED_PROXY_PROPERTY   pSpoProperty   = (PHTTP_ADVANCED_PROXY_PROPERTY )&pAdvancedProxy->Property;
    PHTTP_WAM_INTERFACE             pWamIf         = (PHTTP_WAM_INTERFACE           )pMyObject->hWamIf;
    PANSC_DAEMON_SOCKET_TCP_OBJECT  pClientSocket  = (PANSC_DAEMON_SOCKET_TCP_OBJECT)pMyObject->hClientSocket;
    PANSC_BROKER_SOCKET_TCP_OBJECT  pServerSocket  = (PANSC_BROKER_SOCKET_TCP_OBJECT)pMyObject->hServerSocket;
    PHTTP_BMO_REQ_OBJECT            pBmoReq        = (PHTTP_BMO_REQ_OBJECT          )pMyObject->hBmoReq;

    if ( pMyObject->SbcPmode != HTTP_SBC_PMODE_QUEUE )
    {
        return  ANSC_STATUS_UNAPPLICABLE;
    }
    else if ( (ulSbcPmode != HTTP_SBC_PMODE_RELAY1) &&
              (ulSbcPmode != HTTP_SBC_PMODE_RELAY2) &&
              (ulSbcPmode != HTTP_SBC_PMODE_STORE ) )
    {
        return  ANSC_STATUS_UNAPPLICABLE;
    }

    pMyObject->AcquireAccess((ANSC_HANDLE)pMyObject);

    if ( !pServerSocket )
    {
        returnStatus =
            pMyObject->SetUpConnection
                (
                    (ANSC_HANDLE)pMyObject,
                    (ANSC_HANDLE)NULL
                );
    }

    if ( returnStatus != ANSC_STATUS_SUCCESS )
    {
        pMyObject->ReleaseAccess((ANSC_HANDLE)pMyObject);

        return  returnStatus;
    }
    else
    {
        pMyObject->SbcPmode = ulSbcPmode;
        returnStatus        =
            pMyObject->SendToServer
                (
                    (ANSC_HANDLE)pMyObject,
                    (ANSC_HANDLE)pBmoReq,
                    HTTP_TRO_SFLAG_HEADERS | HTTP_TRO_SFLAG_BODY
                );
    }

    if ( (ulSbcPmode == HTTP_SBC_PMODE_RELAY1) ||
         (ulSbcPmode == HTTP_SBC_PMODE_RELAY2) )
    {
        pBmoReq->SetMboMode((ANSC_HANDLE)pBmoReq, HTTP_MBO_MODE_RELAY);
    }
    else
    {
        pBmoReq->SetMboMode((ANSC_HANDLE)pBmoReq, HTTP_MBO_MODE_STORE);
    }

    pMyObject->ReleaseAccess((ANSC_HANDLE)pMyObject);

    return  returnStatus;
}
