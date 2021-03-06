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

    module:	sys_rroenum_access.c

        For BroadWay Runtime System Environment (SYS),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2002
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the advanced field-access functions
        of the Sys Rro Enum Object.

        *   SysRroEnumGetRecordData
        *   SysRroEnumSetRecordData
        *   SysRroEnumGetRecordValue
        *   SysRroEnumSetRecordValue

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        05/21/02    initial revision.

**********************************************************************/


#include "sys_rroenum_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroEnumGetRecordData
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       pDataBuffer,
                PULONG                      pulDataSize
            );

    description:

        This function is called to retrieve the record data.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       pDataBuffer
                Specifies the buffer holding the record data.

                PULONG                      pulDataSize
                Specifies the size of the record data buffer.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
SysRroEnumGetRecordData
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       pDataBuffer,
        PULONG                      pulDataSize
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_ENUM_OBJECT            pMyObject    = (PSYS_RRO_ENUM_OBJECT)hThisObject;

    if ( *pulDataSize < sizeof(ULONG) )
    {
        return  ANSC_STATUS_BAD_SIZE;
    }

    *(PULONG)pDataBuffer = pMyObject->RecordValue;
    *pulDataSize         = sizeof(ULONG);

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroEnumSetRecordData
            (
                ANSC_HANDLE                 hThisObject,
                PVOID                       pDataBuffer,
                ULONG                       ulDataSize
            );

    description:

        This function is called to configure the record data.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                PVOID                       pDataBuffer
                Specifies the buffer holding the record data.

                ULONG                       ulDataSize
                Specifies the size of the record data buffer.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
SysRroEnumSetRecordData
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       pDataBuffer,
        ULONG                       ulDataSize
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_ENUM_OBJECT            pMyObject    = (PSYS_RRO_ENUM_OBJECT)hThisObject;

    if ( ulDataSize != sizeof(ULONG) )
    {
        return  ANSC_STATUS_BAD_SIZE;
    }

    pMyObject->RecordValue = *(PULONG)pDataBuffer;

    return  ANSC_STATUS_SUCCESS;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        SysRroEnumGetRecordValue
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function is called to retrieve the record data.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

    return:     record value.

**********************************************************************/

ULONG
SysRroEnumGetRecordValue
    (
        ANSC_HANDLE                 hThisObject
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_ENUM_OBJECT            pMyObject    = (PSYS_RRO_ENUM_OBJECT)hThisObject;

    return  pMyObject->RecordValue;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SysRroEnumSetRecordValue
            (
                ANSC_HANDLE                 hThisObject,
                ULONG                       value
            );

    description:

        This function is called to configure the record data.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                ULONG                       value
                Specifies the record value to be configured.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
SysRroEnumSetRecordValue
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       value
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSYS_RRO_ENUM_OBJECT            pMyObject    = (PSYS_RRO_ENUM_OBJECT)hThisObject;

    pMyObject->RecordValue = value;

    return  ANSC_STATUS_SUCCESS;
}
