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

    MODULE: ansc_asn1_Certificate_internal.h

        ASN.1 ANSC Code Generated by Cisco Systems, Inc.

    ---------------------------------------------------------------

    COPYRIGHT:

        Cisco Systems, Inc., 1999 ~ 2003

        All Rights Reserved.

    ---------------------------------------------------------------

    DESCRIPTION:

        The Internal functions defined for ASN.1 objects

        *   ANSC_ASN1_CERTIFICATE
        *   ANSC_ASN1_TBSCERTIFICATE
        *   ANSC_ASN1_CERTIFICATESERIALNUMBER
        *   ANSC_ASN1_VALIDITY
        *   ANSC_ASN1_TIME
        *   ANSC_ASN1_UNIQUEIDENTIFIER
        *   ANSC_ASN1_SUBJECTPUBLICKEYINFO
        *   ANSC_ASN1_DSASIGNATURE
        *   ANSC_ASN1_ALSTRING
        *   ANSC_ASN1_ATTRIBUTES

    ---------------------------------------------------------------

    ENVIRONMENT:

        platform independent

    ---------------------------------------------------------------

    AUTHOR:

        ASNMAGIC ANSC CODE GENERATOR 1.0

    ---------------------------------------------------------------

    REVISION HISTORY:

        *   05/07/2002  initial revision
        *   05/09/2002  more functions are added for Certificate object.
        *   08/08/2002  more functions are added for Certificate object.
        *   11/25/2003  add function to check the cert expired, in the
                        future or valid now.

 **********************************************************************/


#ifndef  _ANSC_ASN1_CERTIFICATE_INTERNAL_H
#define  _ANSC_ASN1_CERTIFICATE_INTERNAL_H

/**********************************************************************

 OBJECT -- ANSC_ASN1_CERTIFICATE

 Certificate ::= Sequence 
     {
                    tbsCertificate TBSCertificate 
                signatureAlgorithm SignatureAlgorithmIdentifier 
                    signatureValue BitString 
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1CertificateCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1CertificateGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1CertificateCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1CertificateGetTbsCertificate
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertificateGetSignatureAlgorithm
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertificateGetSignatureValue
    (
        ANSC_HANDLE                 hThisObject
    );

/*
 *  Manually added functions;
 */
ANSC_STATUS
AnscAsn1CertificateFree
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscAsn1CertCheckValidity
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bCheckTime
    );

BOOLEAN
AnscAsn1CertIsSelfSigned
    (
        ANSC_HANDLE                 hThisObject
    );

BOOLEAN
AnscAsn1CertIsTimeValid
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       year,
        ULONG                       month,
        ULONG                       day,
        ULONG                       hour,
        ULONG                       minute,
        ULONG                       second
    );

BOOLEAN
AnscAsn1CertIsValidNow
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscAsn1CertGetExpirationTime
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hTime
    );

ANSC_STATUS
AnscAsn1CertGetNotBeforeTime
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hTime
    );

ULONG
AnscAsn1CertCheckTime
    (
        ANSC_HANDLE                 hThisObject
    );


PKI_KEY_TYPE
AnscAsn1CertGetKeyType
    (
        ANSC_HANDLE                 hThisObject
    );

SIGNATURE_TYPE
AnscAsn1CertGetSignatureType
    (
        ANSC_HANDLE                 hThisObject
    );

BOOLEAN
AnscAsn1CertSetSignatureType
    (
        ANSC_HANDLE                 hThisObject,
        SIGNATURE_TYPE              signType
    );

BOOLEAN
AnscAsn1CertSetPublicKeyInfo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyHandle
    );

BOOLEAN
AnscAsn1CertVerify
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hPublicKeyHandle
    );

BOOLEAN
AnscAsn1CertIsPathValid
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       pathLength
    );

ANSC_STATUS
AnscAsn1CertVerifyChildCert
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hChildCert
    );

ANSC_STATUS
AnscAsn1CertBeforeDecodingChild
    (
        ANSC_HANDLE                 hThisObject,
        int                         index,
        PVOID*                      ppEncoding
    );

ANSC_STATUS
AnscAsn1CertAfterDecodingChild
    (
        ANSC_HANDLE                 hThisObject,
        int                         index,
        PVOID*                      ppEncoding
    );

ANSC_STATUS
AnscAsn1CertAfterDecoding
    (
        ANSC_HANDLE                 hThisObject,
        PVOID*                      ppEncoding
    );

ANSC_HANDLE
AnscAsn1CertGetSerialNumber
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertGetPublicKeyInfo
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertGetIssuerHandle
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertGetSubjectHandle
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1CertGetExtensionsHandle
    (
        ANSC_HANDLE                 hThisObject
    );

BOOLEAN
AnscAsn1CertSignWithPrivateKeyInfo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hPrivateKey
    );

BOOLEAN
AnscAsn1CertSignWithKeyParam
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyParam
    );

BOOLEAN
AnscAsn1CertSignWithCryptAPI
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCryptAPI
    );

BOOLEAN
AnscAsn1CertIsThisTheIssuer
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hIssuerCert
    );

ANSC_HANDLE
AnscAsn1CertFindExtensionWithOID
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pOIDValueString,
        BOOLEAN                     bReturnValueHandle
    );

ANSC_HANDLE
AnscAsn1CertFindExtensionWithType
    (
        ANSC_HANDLE                 hThisObject,
        UINT                        uExtentionType,
        BOOLEAN                     bReturnValueHandle
    );

ANSC_HANDLE
AnscAsn1CertGetSubjectAltName
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bReturnValueHandle
    );

ANSC_STATUS
AnscAsn1CertGetBasicConstraint
    (
        ANSC_HANDLE                 hThisObject,
        PBOOLEAN                    pIsCA,
        PLONG                       pPathLength
    );

ANSC_STATUS
AnscAsn1CertGetSubjectKeyIdentifier
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR*                     ppBuffer,
        PULONG                      pLength
    );

ANSC_STATUS
AnscAsn1CertGetAuthorityIdentifier
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR*                     ppBuffer,
        PULONG                      pLength
    );

ANSC_STATUS
AnscAsn1CertGetKeyUsage
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pKeyUsage
    );

ANSC_STATUS
AnscAsn1CertAddExtension
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pOIDValueString,
        BOOLEAN                     bCritical,
        ANSC_HANDLE                 hExtensionValue
    );    

ANSC_STATUS
AnscAsn1CertAddSubjectkeyIdentifier
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscAsn1CertAddAuthorityIdentifier
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pKeyIden,
        ULONG                       length
    );

ANSC_STATUS
AnscAsn1CertAddKeyUsage
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulKeyUsage
    );

ANSC_STATUS
AnscAsn1CertAddBasicConstraint
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bIsCA,
        LONG                        pathLen
    );

ANSC_STATUS
AnscAsn1CertAddSubjectAltName
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pAltName
    );

ANSC_STATUS
AnscAsn1CertAddKerberosSubAltName
    (
        ANSC_HANDLE                 hThisObject,        
        ANSC_HANDLE                 hRealnName,
        ANSC_HANDLE                 hPrinName
    );

ANSC_STATUS
AnscAsn1CertGetCDPString
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       cdpType,
        PCHAR                       pBuffer,
        PULONG                      pLength
    );

BOOLEAN
AnscAsn1CertIsExtKeyusageIncluded
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pOIDString
    );

BOOLEAN
AnscAsn1CertIsKeyMatching
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyHandle
    );

ANSC_STATUS
AnscAsn1CertExportPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenParams
    );

BOOLEAN
AnscAsn1CertGetCommonName
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pString,
        PULONG                      pLength
    );

BOOLEAN
AnscAsn1CertGetNameByOID
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pOIDString,
        PCHAR                       pString,
        PULONG                      pLength
    );

ULONG
AnscAsn1CertGetKeyBits
    (
        ANSC_HANDLE                 hThisObject
    );

/**********************************************************************
 *
 * This function is to get the encoding of DN name of the certificate,
 * the subjectAltName will be used if the DN name is empty.
 *
 **********************************************************************/
ANSC_STATUS
AnscAsn1CertGetNameEncoding
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       pNameEncoding,
        PULONG                      pulNameEncodingSize
    );

BOOLEAN
AnscAsn1CertIsRDNNameEmpty
    (
        ANSC_HANDLE                 hThisObject
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_TBSCERTIFICATE

 TBSCertificate ::= Sequence 
     {
                           version [CON 0] Integer DEF
                      serialNumber CertificateSerialNumber 
                         signature AlgorithmIdentifier 
                            issuer Name 
                          validity Validity 
                           subject Name 
              subjectPublicKeyInfo SubjectPublicKeyInfo 
                    issuerUniqueID [CON 1] IMP UniqueIdentifier OPT
                   subjectUniqueID [CON 2] IMP UniqueIdentifier OPT
                        extensions [CON 3] Extensions OPT
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1TBSCertificateCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1TBSCertificateGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1TBSCertificateCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );


/**********************************************************************

 OBJECT -- ANSC_ASN1_CERTIFICATESERIALNUMBER

 CertificateSerialNumber ::= Integer 

 **********************************************************************/

 /* No internal function is required for this object. */    

/**********************************************************************

 OBJECT -- ANSC_ASN1_VALIDITY

 Validity ::= Sequence 
     {
                         notBefore Time 
                          notAfter Time 
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1ValidityCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1ValidityGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1ValidityCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_TIME

 Time ::= Choice 
     {
                           utcTime UniversalTime 
                       generalTime GeneralizedTime 
     }

 **********************************************************************/

ANSC_HANDLE
AnscAsn1TimeCreateSelection
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PANSC_ATTR_OBJECT
AnscAsn1TimeCreateSelectionAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       selType
    );

PCHAR
AnscAsn1TimeGetSelectionName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       selType
    );

BOOLEAN
AnscAsn1TimeGetChoiceTagValue
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       uIndex,
        PASN_OBJECT_FORM_TYPE       pAttr,
        PULONG                      pTagValue
    );

ANSC_STATUS
AnscAsn1TimeSetTime
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_UNIVERSAL_TIME         uniTime
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_UNIQUEIDENTIFIER

 UniqueIdentifier ::= BitString 

 **********************************************************************/

 /* No internal function is required for this object. */    

/**********************************************************************

 OBJECT -- ANSC_ASN1_SUBJECTPUBLICKEYINFO

 SubjectPublicKeyInfo ::= Sequence 
     {
                         algorithm AlgorithmIdentifier 
                  subjectPublicKey BitString 
         EXTRA:
                          publicKey PublicKey 
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1SubjectPublicKeyInfoCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1SubjectPublicKeyInfoGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1SubjectPublicKeyInfoCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1SubjectPublicKeyInfoGetExtraChildName
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
AnscAsn1SubjectPublicKeyInfoCreateExtraChild
    (
        ANSC_HANDLE                 hThisObject
    );

/*
 *  Manually added functions;
 */
BOOLEAN
AnscAsn1SubjectPublicKeyInfoInitPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyHandle,
        ANSC_HANDLE                 hParamHandle
    );

BOOLEAN
AnscAsn1SubjectPublicKeyInfoGenerateKey
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyGenHandle
    );


ANSC_STATUS
AnscAsn1SubjectPublicKeyInfoVerify
    (
        ANSC_HANDLE                 hThisHandle,
        PUCHAR                      pDataSigned,
        ULONG                       lengthOfData,
        SIGNATURE_TYPE              signType,
        PUCHAR                      pSignature,
        ULONG                       uLength
    );

PKI_KEY_TYPE
AnscAsn1SubjectPublicKeyInfoGetKeyType
    (
        ANSC_HANDLE                 hThisObject
    );

ULONG
AnscAsn1SubjectPublicKeyInfoGetKeyBits
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
AnscAsn1SubjectPublicKeyInfoExportPublicKey
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hKeyGenParams
    );

BOOLEAN
AnscAsn1SubjectPublicKeyInfoIsKeyMatching
    (
        ANSC_HANDLE                 hThisObject,
        PKI_KEY_TYPE                keyType,
        ANSC_HANDLE                 hKeyHandle
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_DSASIGNATURE

 DSASignature ::= Sequence 
     {
                                 r Integer 
                                 s Integer 
     }

 **********************************************************************/

PANSC_ATTR_OBJECT
AnscAsn1DSASignatureCreateChildAttr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

PCHAR
AnscAsn1DSASignatureGetChildName
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

ANSC_HANDLE
AnscAsn1DSASignatureCreateChildObject
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       index
    );

/**********************************************************************

 OBJECT -- ANSC_ASN1_ALSTRING

 ALString ::=[UNI 15] IMP OctetString 

 **********************************************************************/

 /* No internal function is required for this object. */    
/**********************************************************************

 OBJECT -- ANSC_ASN1_ATTRIBUTES

 Attributes ::= SetOf Attribute  {}

 **********************************************************************/

ANSC_STATUS
AnscAsn1AttributesIsChildValid
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hChild
    );

ANSC_HANDLE
AnscAsn1AttributesCreateChild
    (
        ANSC_HANDLE                 hThisObject,
        BOOLEAN                     bAddItIn
    );


#endif  /*_ANSC_ASN1_CERTIFICATE_INTERNAL_H*/

