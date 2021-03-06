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

    module:	slap_scostd_content.c

        For Service Logic Aggregation Plane Implementation (SLAP),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 1997 ~ 2003
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This module implements the advanced object content-import
        and export functions of the Slap Sco Standard Object.

        *   SlapScoStdImportMe
        *   SlapScoStdExportMe

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        09/29/03    initial revision.

**********************************************************************/


#include "slap_scostd_global.h"


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SlapScoStdImportMe
            (
                ANSC_HANDLE                 hThisObject,
                SLAP_PARAMETER_LIST*        param_list
            );

    description:

        This function is called to import the object data content.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                SLAP_PARAMETER_LIST*        param_list
                Specifies the parameter list that encapsulates the
                object data content.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
SlapScoStdImportMe
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_PARAMETER_LIST*        param_list
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSLAP_SCO_STANDARD_OBJECT       pMyObject    = (PSLAP_SCO_STANDARD_OBJECT)hThisObject;
    PSLAP_OLA_INTERFACE             pSlapOlaIf   = (PSLAP_OLA_INTERFACE      )pMyObject->hSlapOlaIf;

    return  ANSC_STATUS_UNAPPLICABLE;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_STATUS
        SlapScoStdExportMe
            (
                ANSC_HANDLE                 hThisObject,
                SLAP_PARAMETER_LIST**       param_list
            );

    description:

        This function is called to export the object data content.

    argument:   ANSC_HANDLE                 hThisObject
                This handle is actually the pointer of this object
                itself.

                SLAP_PARAMETER_LIST**       param_list
                Specifies the parameter list to be returned that
                encapsulates the object data content.

    return:     status of operation.

**********************************************************************/

ANSC_STATUS
SlapScoStdExportMe
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_PARAMETER_LIST**       param_list
    )
{
    ANSC_STATUS                     returnStatus = ANSC_STATUS_SUCCESS;
    PSLAP_SCO_STANDARD_OBJECT       pMyObject    = (PSLAP_SCO_STANDARD_OBJECT)hThisObject;
    PSLAP_OLA_INTERFACE             pSlapOlaIf   = (PSLAP_OLA_INTERFACE      )pMyObject->hSlapOlaIf;

    *param_list = NULL;

    return  ANSC_STATUS_UNAPPLICABLE;
}
