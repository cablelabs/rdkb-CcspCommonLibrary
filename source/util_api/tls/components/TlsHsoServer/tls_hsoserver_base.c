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

    module:	tls_hsoserver_base.c

        For Transport Layer Security Implementation (TLS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2003
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the basic container object functions
        of the TLS Hso Server Object.

        *   TlsHsoServerCreate
        *   TlsHsoServerRemove
        *   TlsHsoServerEnrollObjects
        *   TlsHsoServerInitialize

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        06/05/03    initial revision.

**********************************************************************/


#include "tls_hsoserver_global.h"


/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        TlsHsoServerCreate
            (
                ANSC_HANDLE                 hContainerContext,
                ANSC_HANDLE                 hOwnerContext,
                ANSC_HANDLE                 hAnscReserved
            );

    description:

        This function constructs the TLS Hso Server Object and
        initializes the member variables and functions.

    argument:   ANSC_HANDLE                 hContainerContext
                This handle is used by the container object to interact
                with the outside world. It could be the real container
                or an target object.

                ANSC_HANDLE                 hOwnerContext
                This handle is passed in by the owner of this object.

                ANSC_HANDLE                 hAnscReserved
                This handle is passed in by the owner of this object.

    return:     newly created container object.

**********************************************************************/

ANSC_HANDLE
TlsHsoServerCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    )
{
    PANSC_COMPONENT_OBJECT          pBaseObject  = NULL;
    PTLS_HSO_SERVER_OBJECT          pMyObject    = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PTLS_HSO_SERVER_OBJECT)AnscAllocateMemory(sizeof(TLS_HSO_SERVER_OBJECT));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }
    else
    {
        pBaseObject = (PANSC_COMPONENT_OBJECT)pMyObject;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    /* AnscCopyString(pBaseObject->Name, TLS_HSO_SERVER_NAME); */

    pBaseObject->hContainerContext = hContainerContext;
    pBaseObject->hOwnerContext     = hOwnerContext;
    pBaseObject->Oid               = TLS_HSO_SERVER_OID;
    pBaseObject->Create            = TlsHsoServerCreate;
    pBaseObject->Remove            = TlsHsoServerRemove;
    pBaseObject->EnrollObjects     = TlsHsoServerEnrollObjects;
    pBaseObject->Initialize        = TlsHsoServerInitialize;

    pBaseObject->EnrollObjects((ANSC_HANDLE)pBaseObject);
    pBaseObject->Initialize   ((ANSC_HANDLE)pBaseObject);

    return  (ANSC_HANDLE)pMyObject;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsHsoServerRemove
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function destroys the object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsHsoServerRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    TlsHsoRemove((ANSC_HANDLE)hThisObject);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsHsoServerEnrollObjects
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function enrolls all the objects required by this object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsHsoServerEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PTLS_HSO_SERVER_OBJECT          pMyObject      = (PTLS_HSO_SERVER_OBJECT       )hThisObject;
    PANSC_TDO_CLIENT_OBJECT         pStateTimerIf  = (PANSC_TDO_CLIENT_OBJECT      )pMyObject->hStateTimerIf;

    TlsHsoEnrollObjects((ANSC_HANDLE)pMyObject);

    if ( TRUE )
    {
        pStateTimerIf = (PANSC_TDO_CLIENT_OBJECT)pMyObject->hStateTimerIf;

        if ( pStateTimerIf )
        {
            pStateTimerIf->Invoke = TlsHsoServerStateTimerInvoke;
        }
    }

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        TlsHsoServerInitialize
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function first calls the initialization member function
        of the base class object to set the common member fields
        inherited from the base class. It then initializes the member
        fields that are specific to this object.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
TlsHsoServerInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PTLS_HSO_SERVER_OBJECT          pMyObject    = (PTLS_HSO_SERVER_OBJECT)hThisObject;

    /*
     * Until you have to simulate C++ object-oriented progtlsming style with standard C, you don't
     * appreciate all the nice little things come with C++ language and all the dirty works that
     * have been done by the C++ compilers. Member initialization is one of these things. While in
     * C++ you don't have to initialize all the member fields inherited from the base class since
     * the compiler will do it for you, such is not the case with C.
     */
    TlsHsoInitialize((ANSC_HANDLE)pMyObject);

    /*
     * Although we have initialized some of the member fields in the "create" member function, we
     * repeat the work here for completeness. While this simulation approach is pretty stupid from
     * a C++/Java progtlsmer perspective, it's the best we can get for universal embedded network
     * progtlsming. Before we develop our own operating system (don't expect that to happen any
     * time soon), this is the way things gonna be.
     */
    pMyObject->Oid                   = TLS_HSO_SERVER_OID;
    pMyObject->Create                = TlsHsoServerCreate;
    pMyObject->Remove                = TlsHsoServerRemove;
    pMyObject->EnrollObjects         = TlsHsoServerEnrollObjects;
    pMyObject->Initialize            = TlsHsoServerInitialize;

    pMyObject->Reset                 = TlsHsoServerReset;
    pMyObject->Start                 = TlsHsoServerStart;

    pMyObject->Recv                  = TlsHsoServerRecv;
    pMyObject->Send                  = TlsHsoServerSend;

    pMyObject->StateTimerInvoke      = TlsHsoServerStateTimerInvoke;

    pMyObject->HsServerState         = TLS_HSS_STATE_idle;

    pMyObject->RecvClientHello       = TlsHsoServerRecvClientHello;
    pMyObject->RecvCertificate       = TlsHsoServerRecvCertificate;
    pMyObject->RecvClientKeyExchange = TlsHsoServerRecvClientKeyExchange;
    pMyObject->RecvCertVerify        = TlsHsoServerRecvCertVerify;
    pMyObject->RecvFinished          = TlsHsoServerRecvFinished;

    pMyObject->SendHelloRequest      = TlsHsoServerSendHelloRequest;
    pMyObject->SendServerHello       = TlsHsoServerSendServerHello;
    pMyObject->SendCertificate       = TlsHsoServerSendCertificate;
    pMyObject->SendServerKeyExchange = TlsHsoServerSendServerKeyExchange;
    pMyObject->SendCertRequest       = TlsHsoServerSendCertRequest;
    pMyObject->SendServerHelloDone   = TlsHsoServerSendServerHelloDone;
    pMyObject->SendFinished          = TlsHsoServerSendFinished;

    return  ANSC_STATUS_SUCCESS;
}
