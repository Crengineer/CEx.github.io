#include "vssalinc.h"

int    bufferSize        = HTTP_RESTAPI_ANSWER_ALLOC_SIZE;
char  *jsonRequestString = NULL;
char  *jsonAnswerString  = NULL;

cJSON *jsonRequest       = NULL;
cJSON *transactionData   = NULL;
cJSON *restApiAnswer     = NULL;
cJSON *arrayIterator     = NULL;

RESTAPIRESPONSE restApiResponse;

MBID ios_taskid = 0;

BOOL bMemTrace  = FALSE;

#define JSON_TRANSACTION_FILE_NAME "jsonRestDebug.log"

void SaveJsonRestCallToFile(char *descriptionMessage, char *jsosString, BOOL saveAlsoToSystemLog)
{
   FILE  *jsonTransactionFile = NULL;
   short rc = 0;

   if ((descriptionMessage == NULL) && (jsosString == NULL))
      return;

   jsonTransactionFile = fopen(JSON_TRANSACTION_FILE_NAME, "a+t");
   if (jsonTransactionFile == NULL)
      return;

   rc = fseek(jsonTransactionFile, 0, SEEK_END);

   if ((descriptionMessage != NULL) && (jsosString != NULL))
   {
      rc = fprintf(jsonTransactionFile, "%s - %s\n", descriptionMessage, jsosString);

      if (saveAlsoToSystemLog)
         Syslog(ios_taskid, SLP_DEBUG, "%s - %s", descriptionMessage, jsosString);
   }
   else if ((descriptionMessage != NULL) && (jsosString == NULL))
   {
      rc = fprintf(jsonTransactionFile, "%s\n", descriptionMessage);

      if (saveAlsoToSystemLog)
         Syslog(ios_taskid, SLP_DEBUG, "%s", descriptionMessage);
   }
   else if ((descriptionMessage == NULL) && (jsosString != NULL))
   {
      rc = fprintf(jsonTransactionFile, "%s\n", jsosString);

      if (saveAlsoToSystemLog)
         Syslog(ios_taskid, SLP_DEBUG, "%s", jsosString);
   }
   rc = fclose(jsonTransactionFile);
}

RESTAPIRESPONSE *GetLastRestApiResponse(void)
{
   return(&restApiResponse);
}

short GetRestApiResponseReturnCode(void)
{
   return(restApiResponse.returnCode);
}

BOOL AnyRestApiResponseMessage(void)
{
   return(strlen(restApiResponse.restApiMessage) ? TRUE : FALSE);
}

char *GetRestApiResponseMessage(void)
{
   return(restApiResponse.restApiMessage);
}

void DebugLog(char *cBuff)
{
//   if ((bShowTrace) || (bMemTrace))
//      FLog(&DebugLogHandle, "%s", cBuff);
}

void RestApiInitialize(MBID taskid)
{
   ios_taskid = taskid;
//   FLogInitialize(&DebugLogHandle, "RestApi", PROGRAM_NAME, LFL_KEEPCLOSED | LFL_MILLISECS );
}

void RestApiDestroy(void)
{
}

void JsonRequestAddStoreId(cJSON *jsonRequest, long storeId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddStoreId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_STORE_ID, storeId);
}

void JsonRequestAddTerminalId(cJSON *jsonRequest, short terminalId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddTerminalId - NULL jsonRequest.");
   else
      cJSONex_SetShortToObject(jsonRequest, HTTP_RESTAPI_TERM_ID, terminalId);
}

void JsonRequestAddOperatorId(cJSON *jsonRequest, long operatorId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddOperatorId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_OPERATOR_ID, operatorId);
}

void JsonRequestAddDepositId(cJSON *jsonRequest, long depositId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddDepositId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_DEPOSIT_ID, depositId);
}

void JsonRequestAddTrxId(cJSON *jsonRequest, long trxId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddTrxId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_TRX_ID, trxId);
}

void JsonRequestAddOrderId(cJSON *jsonRequest, long orderId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddOrderId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_ORDER_ID, orderId);
}

void JsonRequestAddAmount(cJSON *jsonRequest, long amount)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddAmount - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_AMOUNT, amount);
}

void JsonRequestAddNewDepositId(cJSON *jsonRequest, long newDepositId)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddNewDepositId - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_NEW_DEPOSIT_ID, newDepositId);
}

void JsonRequestAddRequestType(cJSON *jsonRequest, long requestType)
{
   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddRequestType - NULL jsonRequest.");
   else
      cJSONex_SetLongToObject(jsonRequest, HTTP_RESTAPI_NEW_DEPOSIT_ID, requestType);
}

void JsonRequestAddFormattedDate(cJSON *jsonRequest, char *jsonTag, char *date)
{
   char tmpDate[11];

   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedData - NULL jsonRequest.");
   else if (date == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedData - NULL date.");
   else if (jsonTag == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedData - NULL jsonTag.");
   else
   {
      memset(tmpDate, 0x00, sizeof(tmpDate));
      sprintf(tmpDate, "%4.4s-%2.2s-%2.2s", date, date + 4, date + 6);
      cJSONex_SetStringToObject(jsonRequest, jsonTag, tmpDate);
   }
}

void JsonRequestAddFormattedTime(cJSON *jsonRequest, char *jsonTag, char *time)
{
   char tmpTime[9];

   if (jsonRequest == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedTime - NULL jsonRequest.");
   else if (time == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedTime - NULL time.");
   else if (jsonTag == NULL)
      Syslog(ios_taskid, SLP_ERROR, "ERROR: JsonRequestAddFormattedData - NULL jsonTag.");
   else
   {
      memset(tmpTime, 0x00, sizeof(tmpTime));
      sprintf(tmpTime, "%2.2s:%2.2s:%2.2s", time, time + 2, time + 4);
      cJSONex_SetStringToObject(jsonRequest, jsonTag, tmpTime);
   }
}

