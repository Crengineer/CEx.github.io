#include "vssalinc.h"

#define FIDELITY_CARD_OK         'A' /* -> int TGPCOK = 0; - Card Ok         -> ANSWER_DATA_READY */
#define FIDELITY_CARD_BLOCKED    'B' /* -> int TGPCBL = 1; - Card blocked    -> ANSWER_BLACK_LIST */
#define FIDELITY_CARD_BLACK_LIST 'I' /* -> int TGPNOA = 3; - Card not active -> ANSWER_BLACK_LIST */

BOOL ApiLoyaltyPosFind(long subStoreId, short terminalId, unsigned long transactionNumber, char storeLocation, char *queryDate, char *queryTime, char *fidelityCardCode, short selfScanData, FIDAPIMSG *fidapiMessage)
{
   short     dataIndex = 0;
// Pekxxx    short  initiativeIndex = 0, nbrOfLoyaltyLevels = 0, nbrOfBasketItems = 0, nbrOfLoyaltyCounters = 0;
   cJSON    *loyaltyLevelElement     = NULL;
   cJSON    *rspJsonSelfScanningData = NULL;
   cJSON    *rspJsonLoyaltyLevels    = NULL;
// Pekxxx    cJSON    *rspJsonBasketItems      = NULL;
   cJSON    *rspJsonLoyaltyCounters  = NULL;
   char      tempChar = 0;

   memset(fidapiMessage, 0x00, sizeof(FIDAPIMSG));

   if (fidapiMessage == NULL)
   {
      Syslog(ios_taskid, SLP_ERROR, "ERROR: ApiLoyaltyPosFind - fidapiMessage parameter cannot be NULL.");
      return(FALSE);
   }

   /*******************************************************************************************************************************/
   /*                                                                                                                             */
   /*                                                                                                                             */
   bufferSize = HTTP_RESTAPI_ANSWER_ALLOC_SIZE;
   jsonAnswerString = malloc(bufferSize);
   if (jsonAnswerString == NULL)
      return(FALSE);

   if (jsonRequest != NULL)
      cJSON_Delete(jsonRequest);

   jsonRequest = cJSON_CreateObject();
   if (jsonRequest == NULL)
   {
      free(jsonAnswerString);
      return(FALSE);
   }

   /* transaction json section */
   transactionData = cJSON_CreateObject();
   if (transactionData == NULL)
   {
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }

   cJSONex_SetLongToObject    (transactionData, HTTP_RESTAPI_STORE_ID,           subStoreId);
   cJSONex_SetShortToObject   (transactionData, HTTP_RESTAPI_TERM_ID,            terminalId);
   cJSONex_SetLongToObject    (transactionData, HTTP_RESTAPI_TRANSACTION_NUMBER, transactionNumber);
   JsonRequestAddFormattedDate(transactionData, HTTP_RESTAPI_TRANSACTION_DATE,   queryDate);
   JsonRequestAddFormattedTime(transactionData, HTTP_RESTAPI_TRANSACTION_TIME,   queryTime);
   cJSONex_SetStringToObject  (transactionData, HTTP_RESTAPI_CARD_CODE,          fidelityCardCode);
   cJSONex_SetBoolToObject    (transactionData, HTTP_RESTAPI_SELF_SCANNING_DATA, selfScanData);

   /* add json subsections */
   cJSON_AddItemToObject(jsonRequest, HTTP_RESTAPI_TRANSACTION, transactionData);

   /* WARNING: jsonRequestString has to be freed from the caller! */
   jsonRequestString = cJSON_PrintUnformatted(jsonRequest);

   memset(&restApiResponse, 0x00, sizeof(restApiResponse));

   SaveJsonRestCallToFile("ApiLoyaltyPosFind - jsonRequestString", jsonRequestString, FALSE);

   if (!RestExec(RESTOP_GET,
                 HTTP_API_LOYALTY_POS_FIND_DESCRIPTION,
                 HTTP_REST_API_INI_SECTION,
                 HTTP_RESTAPI_INI_FILE,
                 HTTP_API_LOYALTY_POS_FIND,
                 "",
                 jsonRequestString,
                 &jsonAnswerString,
                 &bufferSize,
                 NULL,
                 &restApiResponse.restCallResult))
   {
      Syslog(ios_taskid, SLP_ERROR, "ERROR: ApiLoyaltyPosFind - Error from RestExec execution.");
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }
   /*                                                                                                                             */
   /*                                                                                                                             */
   /*******************************************************************************************************************************/

   SaveJsonRestCallToFile("ApiLoyaltyPosFind - jsonAnswerString ", jsonAnswerString, FALSE);

   restApiAnswer = cJSON_Parse(jsonAnswerString);
   free(jsonRequestString);

   memset(restApiResponse.restApiMessage, 0x00, sizeof(restApiResponse.restApiMessage));
   if (cJSONex_GetShortFromObject(restApiAnswer, HTTP_RESTAPI_RSP_CODE, &restApiResponse.returnCode))
   {
      cJSONex_GetStringFromObject(restApiAnswer, HTTP_RESTAPI_RSP_MESSAGE, restApiResponse.restApiMessage, sizeof(restApiResponse.restApiMessage));
      if (restApiResponse.returnCode)
      {
         Syslog(ios_taskid, SLP_ERROR, "ERROR: ApiLoyaltyPosFind - Error code %hd returned in the answer, message %s.", restApiResponse.returnCode, restApiResponse.restApiMessage);
         cJSON_Delete(jsonRequest);
         jsonRequest = NULL;
         free(jsonAnswerString);
         return(FALSE);
      }
   }

   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.sFuncCode      = FMFC_QUERY;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.lStoreId       = subStoreId;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.sPosId         = terminalId;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.lXactNum       = transactionNumber;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.cSSXact        = (char)selfScanData;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.sCouponIndex   = 0;
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.cStoreLocation = storeLocation;

   memcpy(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szXactDate, queryDate,        sizeof(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szXactDate));
   memcpy(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szXactTime, queryTime,        sizeof(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szXactTime));
   memcpy(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szCardNum,  fidelityCardCode, sizeof(fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.szCardNum));

   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.cSequence      = FIRST_REC;  /* These fields needs to be removed */
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.cTotSeg        = FIRST_REC;  /* These fields needs to be removed */
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.cTypeSeg       = HEADER_REC; /* These fields needs to be removed */
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.sError         = FIDERR_OK;  /* These fields needs to be removed */
   fidapiMessage->tNewQuery.HeaderRecStruct.tHdr.sAck           = 0;          /* These fields needs to be removed */

   /*******************************************************************************************************************************/
   /*                                                                                                                             */
   /* Parse the answer received                                                                                                   */
   /*                                                                                                                             */
   cJSONex_GetStringFromObject(restApiAnswer, HTTP_RESTAPI_CUSTOMER_NAME,  fidapiMessage->tNewQuery.HeaderRecStruct.szCustomerId, sizeof(fidapiMessage->tNewQuery.HeaderRecStruct.szCustomerId));
   cJSONex_GetCharFromObject  (restApiAnswer, HTTP_RESTAPI_CARD_STATUS,   &tempChar);

   if (tempChar == FIDELITY_CARD_OK)
      fidapiMessage->tNewQuery.HeaderRecStruct.sCardStatus = ANSWER_DATA_READY;
   else if (tempChar == FIDELITY_CARD_BLOCKED)
      fidapiMessage->tNewQuery.HeaderRecStruct.sCardStatus = ANSWER_BLACK_LIST;
   else if (tempChar == FIDELITY_CARD_BLACK_LIST)
      fidapiMessage->tNewQuery.HeaderRecStruct.sCardStatus = ANSWER_BLACK_LIST;
   else
      fidapiMessage->tNewQuery.HeaderRecStruct.sCardStatus = ANSWER_ERROR;

   /* From fpxconv.c */
   //#1066a start temporaneamente in attesa del CLS che lo gestisca
   fidapiMessage->tNewQuery.HeaderRecStruct.cSSAllowed = (char)0xFF ;      //#1066a
   //#1066a end  temporaneamente in attesa del CLS che lo gestisca

   /*--------------------------------------------------------------------------------------------------------*/

   rspJsonLoyaltyLevels = cJSON_GetObjectItem(restApiAnswer, HTTP_RESTAPI_LOYALTY_LEVELS);
   if (rspJsonLoyaltyLevels != NULL)
   {
      /* iterate over ints */
      dataIndex = 0;
      cJSON_ArrayForEach(arrayIterator, rspJsonLoyaltyLevels)
      {
         if (cJSON_IsNumber(arrayIterator))
         {
            switch (++dataIndex)
            {
               case 1:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass1 = arrayIterator->valueint;
                  break;

               case 2:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass2 = arrayIterator->valueint;
                  break;

               case 3:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass3 = arrayIterator->valueint;
                  break;

               case 4:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass4 = arrayIterator->valueint;
                  break;

               case 5:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass5 = arrayIterator->valueint;
                  break;

               case 6:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass6 = arrayIterator->valueint;
                  break;

               case 7:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass7 = arrayIterator->valueint;
                  break;

               case 8:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass8 = arrayIterator->valueint;
                  break;

               case 9:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass9 = arrayIterator->valueint;
                  break;

               case 10:
                  fidapiMessage->tNewQuery.HeaderRecStruct.sCardClass10 = arrayIterator->valueint;
                  break;

               default:
                  Syslog(ios_taskid, SLP_WARNING, "WARNING: ApiLoyaltyPosFind - Too many loyalty levels (%hd).", dataIndex);
                  break;
            }
         }
         else
            Syslog(ios_taskid, SLP_WARNING, "WARNING: ApiLoyaltyPosFind - Invalid value found in loyalty levels array at index (%hd).", dataIndex);
      }
   }

   /*--------------------------------------------------------------------------------------------------------*/

   rspJsonSelfScanningData = cJSON_GetObjectItem(restApiAnswer, HTTP_RESTAPI_SELF_SCANNING);
   if (rspJsonSelfScanningData != NULL)
   {
      cJSONex_GetCharFromObject(loyaltyLevelElement, HTTP_RESTAPI_VALIDATION,            &fidapiMessage->tNewQuery.HeaderRecStruct.cSSValidation);
//    Pekxxx    cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_CUST_CLASS,            &fidelityCard->???);
      cJSONex_GetCharFromObject(loyaltyLevelElement, HTTP_RESTAPI_BLOCKED,               &fidapiMessage->tNewQuery.HeaderRecStruct.cSSBlocked);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_TRANS,             &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_TRANS_FROM_RESCAN, &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_TRANS_INCOMPLETE,  &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_TOTAL_TIME,            &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_RESCANS,           &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_FORCED_RESCANS,    &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_RESCANS_UP,        &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_RESCANS_EQUAL,     &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_NBR_RESCANS_DOWN,      &fidelityCard->???);
// Pekxxx       cJSONex_GetShortFromObject(loyaltyLevelElement, HTTP_RESTAPI_TIME_RESCAN_LAST,      &fidelityCard->???);
   }

   /*--------------------------------------------------------------------------------------------------------*/

// Pekxxx    rspJsonBasketItems = cJSON_GetObjectItem(rspData, HTTP_RESTAPI_BASKET_ITEMS);
// Pekxxx    if (rspJsonBasketItems == NULL)
// Pekxxx    {
// Pekxxx       /* iterate over ints */
// Pekxxx       dataIndex = 0;
// Pekxxx       cJSON_ArrayForEach(arrayIterator, rspJsonBasketItems)
// Pekxxx       {
// Pekxxx          if (cJSON_IsString(arrayIterator))
// Pekxxx          {
// Pekxxx             dataIndex++;
// Pekxxx             Syslog(ios_taskid, SLP_DEBUG, "DEBUG: ApiLoyaltyPosFind - Basket item found %s at index %hd.", arrayIterator->valuestring, dataIndex);
// Pekxxx          }
// Pekxxx          else
// Pekxxx             Syslog(ios_taskid, SLP_WARNING, "WARNING: ApiLoyaltyPosFind - Invalid value found in basket items array at index (%hd).", dataIndex);
// Pekxxx       }
// Pekxxx    }

   /*--------------------------------------------------------------------------------------------------------*/

   rspJsonLoyaltyCounters = cJSON_GetObjectItem(restApiAnswer, HTTP_RESTAPI_LOYALTY_COUNTERS);
   if (rspJsonLoyaltyCounters != NULL)
   {
      dataIndex = 0;
      cJSON_ArrayForEach(arrayIterator, rspJsonLoyaltyCounters)
      {
         cJSONex_GetCharFromObject  (arrayIterator, HTTP_RESTAPI_LOYALTY_COUNTER_TYPE,  &fidapiMessage->tNewQuery.HeaderRecStruct.iniziativa[dataIndex].chTipoIniz);
         cJSONex_GetStringFromObject(arrayIterator, HTTP_RESTAPI_LOYALTY_COUNTER_CODE,   fidapiMessage->tNewQuery.HeaderRecStruct.iniziativa[dataIndex].chCodeIniz, sizeof(fidapiMessage->tNewQuery.HeaderRecStruct.iniziativa[dataIndex].chCodeIniz));
         cJSONex_GetLongFromObject  (arrayIterator, HTTP_RESTAPI_LOYALTY_COUNTER_POINT, &fidapiMessage->tNewQuery.HeaderRecStruct.iniziativa[dataIndex].ulValue1);
// Pekxxx             cJSONex_GetLongFromObject  (arrayIterator, HTTP_RESTAPI_LOYALTY_COUNTER_POINT, &iniziatives[initiativeIndex].ulValue2); /* ??? */
         cJSONex_GetCharFromObject  (arrayIterator, HTTP_RESTAPI_LOYALTY_COUNTER_CHECK, &fidapiMessage->tNewQuery.HeaderRecStruct.iniziativa[dataIndex].InitiativeCheck);
         dataIndex++;

         if (dataIndex >= MAX_LOY_PROMO_HEADER)
         {
            Syslog(ios_taskid, SLP_WARNING, "WARNING: ApiLoyaltyPosFind - Too many loyalty counters received (%hd), limit it to first %hd.", dataIndex, MAX_LOY_PROMO_HEADER);
            break;
         }
      }
   }
   /*                                                                                                                             */
   /*                                                                                                                             */
   /*******************************************************************************************************************************/

   free(jsonAnswerString);
   cJSON_Delete(jsonRequest);
   jsonRequest = NULL;

//   SendToSales(MBMSGT_FIDELITYASYNC, (void *)&fidapiMessage, sizeof(fidapiMessage));

   return(TRUE);
}

BOOL ApiLoyaltyPosUse(long subStoreId, short terminalId, unsigned long transactionNumber, char *queryDate, char *queryTime, char *fidelityCardCode, short selfScanData, long totalAmount, char SSPosValidation, short SSItemsPlus, short SSItemsMinus, char Mss_Trx_Not_Payed, struct FCARDtmpl *fidelityCard, struct Ini *iniziatives)
{
   short  initiativeIndex = 0;
// Pekxxx    short  localTerminalId            = 0, initiativeIndex = 0;
// Pekxxx    long   localOperatorId            = 0;
   char  *jsonRequestString          = NULL, *jsonAnswerString  = NULL;
   cJSON *jsonRequestSelfScanning    = NULL;
   cJSON *jsonRequestBasketItems     = NULL;
   cJSON *jsonRequestLoyaltyCounters = NULL;
   cJSON *loyaltyLevelElement        = NULL;

   /*******************************************************************************************************************************/
   /*                                                                                                                             */
   /*                                                                                                                             */
   bufferSize = HTTP_RESTAPI_ANSWER_ALLOC_SIZE;
   jsonAnswerString = malloc(bufferSize);
   if (jsonAnswerString == NULL)
      return(FALSE);

   if (jsonRequest != NULL)
      cJSON_Delete(jsonRequest);

   jsonRequest = cJSON_CreateObject();
   if (jsonRequest == NULL)
   {
      free(jsonAnswerString);
      return(FALSE);
   }

   cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_TOTAL_AMOUNT, totalAmount);

   /*--------------------------------------------------------------------------------------------------------*/

   /* transaction json section */
   transactionData = cJSON_CreateObject();
   if (transactionData == NULL)
   {
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }

   cJSONex_SetLongToObject    (transactionData, HTTP_RESTAPI_STORE_ID,           subStoreId);
   cJSONex_SetShortToObject   (transactionData, HTTP_RESTAPI_TERM_ID,            terminalId);
   cJSONex_SetLongToObject    (transactionData, HTTP_RESTAPI_TRANSACTION_NUMBER, transactionNumber);
   JsonRequestAddFormattedDate(transactionData, HTTP_RESTAPI_TRANSACTION_DATE,   queryDate);
   JsonRequestAddFormattedTime(transactionData, HTTP_RESTAPI_TRANSACTION_TIME,   queryTime);
   cJSONex_SetStringToObject  (transactionData, HTTP_RESTAPI_CARD_CODE,          fidelityCardCode);
   cJSONex_SetBoolToObject    (transactionData, HTTP_RESTAPI_SELF_SCANNING_DATA, selfScanData);

   /*--------------------------------------------------------------------------------------------------------*/

   /* self scanning json section */
   jsonRequestSelfScanning = cJSON_CreateObject();
   if (jsonRequestSelfScanning == NULL)
   {
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      cJSON_Delete(transactionData);
      transactionData = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }

   cJSONex_SetCharToObject (jsonRequestSelfScanning, HTTP_RESTAPI_VALIDATION,       SSPosValidation);
// Pekxxx    cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_CUST_CLASS,       );
   cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_BLOCKED,          fidelityCard->cSSBlocked);
   cJSONex_SetLongToObject (jsonRequestSelfScanning, HTTP_RESTAPI_TOTAL_AMOUNT,     totalAmount);
   cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_NBR_ITEM_PLUS,    SSItemsPlus);
   cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_NBR_ITEM_MINUS,   SSItemsMinus);
// Pekxxx    cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_RESCAN_NEXT,      );
   cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_INCOMPLETE_TRANS, Mss_Trx_Not_Payed);
// Pekxxx    cJSONex_SetShortToObject(jsonRequestSelfScanning, HTTP_RESTAPI_TOTAL_TIME,       );

   /*--------------------------------------------------------------------------------------------------------*/

   /* basket items json section */

   // This is not an object, but an array => create an Array instead of an Object
  // jsonRequestBasketItems = cJSON_CreateArray();
   jsonRequestBasketItems = cJSON_CreateArray();
   if (jsonRequestBasketItems == NULL)
   {
       cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      cJSON_Delete(transactionData);
      transactionData = NULL;
      cJSON_Delete(jsonRequestSelfScanning);
      jsonRequestSelfScanning = NULL;
      cJSON_Delete(jsonRequestBasketItems);
      jsonRequestBasketItems = NULL;
      free(jsonAnswerString);
      return(FALSE);
       /* Previous lines written in this section
      jsonRequestBasketItems =  cJSON_CreateObject();
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      cJSON_Delete(transactionData);
      transactionData = NULL;
      cJSON_Delete(jsonRequestSelfScanning);
      jsonRequestSelfScanning = NULL;
      free(jsonAnswerString);
      return(FALSE);  
       */ 
   }

   /*--------------------------------------------------------------------------------------------------------*/

   /* loyalty counters json section */
   jsonRequestLoyaltyCounters = cJSON_CreateArray();
   if (jsonRequestLoyaltyCounters == NULL)
   {
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      cJSON_Delete(transactionData);
      transactionData = NULL;
      cJSON_Delete(jsonRequestSelfScanning);
      jsonRequestSelfScanning = NULL;
      cJSON_Delete(jsonRequestBasketItems);
      jsonRequestBasketItems = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }

   for (initiativeIndex = 0; initiativeIndex < MAX_LOY_PROMOTIONS; initiativeIndex++)
   {
      if (!strlen(iniziatives[initiativeIndex].chCodeIniz))
      {
         loyaltyLevelElement = cJSON_CreateObject();
         if (loyaltyLevelElement == NULL)
            continue;
         // set the "type" field of loyaltyLevelElement, which is a JSON file 
         cJSONex_SetCharToObject  (loyaltyLevelElement, HTTP_RESTAPI_LOYALTY_COUNTER_TYPE,  iniziatives[initiativeIndex].chTipoIniz);

         // Elimination of next line or change of it, because it bring to multiple "code":""
         cJSONex_SetStringToObject(loyaltyLevelElement, HTTP_RESTAPI_LOYALTY_COUNTER_CODE,  iniziatives[initiativeIndex].chCodeIniz);

         cJSONex_SetLongToObject  (loyaltyLevelElement, HTTP_RESTAPI_LOYALTY_COUNTER_POINT, iniziatives[initiativeIndex].ulValue1);
// Pekxxx          cJSONex_SetLongToObject  (loyaltyLevelElement, HTTP_RESTAPI_LOYALTY_COUNTER_POINT, iniziatives[initiativeIndex].ulValue2); /* ??? */
         cJSONex_SetCharToObject  (loyaltyLevelElement, HTTP_RESTAPI_LOYALTY_COUNTER_CHECK, iniziatives[initiativeIndex].InitiativeCheck);

         if (strlen(iniziatives[initiativeIndex].chCodeIniz) > 0)
         {
                cJSON_AddItemToArray(jsonRequestLoyaltyCounters, loyaltyLevelElement);
         } else {
              cJSON_Delete(loyaltyLevelElement);
      }
   }

   /*--------------------------------------------------------------------------------------------------------*/

   /* add json subsections */
   cJSON_AddItemToObject(jsonRequest, HTTP_RESTAPI_SELF_SCANNING,    jsonRequestSelfScanning);
   cJSON_AddItemToObject(jsonRequest, HTTP_RESTAPI_BASKET_ITEMS,     jsonRequestBasketItems);
   cJSON_AddItemToObject(jsonRequest, HTTP_RESTAPI_LOYALTY_COUNTERS, jsonRequestLoyaltyCounters);
   cJSON_AddItemToObject(jsonRequest, HTTP_RESTAPI_TRANSACTION,      transactionData);

   /* WARNING: jsonRequestString has to be freed from the caller! */
   jsonRequestString = cJSON_PrintUnformatted(jsonRequest);

   memset(&restApiResponse, 0x00, sizeof(restApiResponse));

   SaveJsonRestCallToFile("ApiLoyaltyPosUse - jsonRequestString", jsonRequestString, FALSE);

   if (!RestExec(RESTOP_PUT,
                 HTTP_API_LOYALTY_POS_USE_DESCRIPTION,
                 HTTP_REST_API_INI_SECTION,
                 HTTP_RESTAPI_INI_FILE,
                 HTTP_API_LOYALTY_POS_USE,
                 "",
                 jsonRequestString,
                 &jsonAnswerString,
                 &bufferSize,
                 NULL,
                 &restApiResponse.restCallResult))
   {
      Syslog(ios_taskid, SLP_ERROR, "ERROR: ApiLoyaltyPosUse - Error from RestExec execution.");
      cJSON_Delete(jsonRequest);
      jsonRequest = NULL;
      free(jsonAnswerString);
      return(FALSE);
   }
   /*                                                                                                                             */
   /*                                                                                                                             */
   /*******************************************************************************************************************************/

   SaveJsonRestCallToFile("ApiLoyaltyPosUse - jsonAnswerString ", jsonAnswerString, FALSE);

   restApiAnswer = cJSON_Parse(jsonAnswerString);
   free(jsonRequestString);

   memset(restApiResponse.restApiMessage, 0x00, sizeof(restApiResponse.restApiMessage));
   if (cJSONex_GetShortFromObject(restApiAnswer, HTTP_RESTAPI_RSP_CODE, &restApiResponse.returnCode))
   {
      cJSONex_GetStringFromObject(restApiAnswer, HTTP_RESTAPI_RSP_MESSAGE, restApiResponse.restApiMessage, sizeof(restApiResponse.restApiMessage));
      if (restApiResponse.returnCode)
      {
         Syslog(ios_taskid, SLP_ERROR, "ERROR: ApiLoyaltyPosUse - Error code %hd returned in the answer, message %s.", restApiResponse.returnCode, restApiResponse.restApiMessage);
         cJSON_Delete(jsonRequest);
         jsonRequest = NULL;
         free(jsonAnswerString);
         return(FALSE);
      }
   }

   /*******************************************************************************************************************************/
   /*                                                                                                                             */
   /* Parse the answer received                                                                                                   */
   /*                                                                                                                             */

   /*                                                                                                                             */
   /*                                                                                                                             */
   /*******************************************************************************************************************************/

   cJSON_Delete(jsonRequest);
   jsonRequest = NULL;
   free(jsonAnswerString);

   return(TRUE);
}

