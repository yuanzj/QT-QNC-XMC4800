/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup QiaoTian_XMC_Servo QiaoTian_XMC_Servo
@{
*/

/**
\file QiaoTian_XMC_Servo.c
\brief Implementation
 Created with SSC Tool application parser 1.6.4.0
\version 0.0.0.1
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _QIAO_TIAN__XMC__SERVO_ 1
#include "QiaoTian_XMC_Servo.h"
#undef _QIAO_TIAN__XMC__SERVO_
/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
/**
 * APPL_GenerateMapping_New记录TPDO和RPDO基础信息
 * APPL_InputMapping_New中执行TPDO回调
 * APPL_OutputMapping_New中执行RPDO回调
 */
#define PDO_MAP_NUM 4
#define PDO_SUB_MAX 32
typedef struct
{
    UINT16 index;
    UINT8 subindex;
    UINT8 size;
    UINT8 (*HandleCallback)(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
    UINT32 u32_buff;
}PdoCallbackStruct;

PdoCallbackStruct RxPdoList[PDO_MAP_NUM][PDO_SUB_MAX];
PdoCallbackStruct TxPdoList[PDO_MAP_NUM][PDO_SUB_MAX];
/* USER CODE END 1 */
/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                       register (0x204) when this function is succeeded. The event mask can be adapted
                       in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////
//extern void Get_Slave_CycleTime(void);
UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
//	Get_Slave_CycleTime();
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
   
#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;
#endif

#if MAX_PD_INPUT_SIZE > 0
    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;
#endif

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

UINT16 APPL_GenerateMapping_New(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;

    UINT32 value = 0;
    OBJCONST TOBJECT OBJMEM* pRxPDO = NULL;
    OBJCONST TOBJECT OBJMEM* pTxPDO = NULL;
#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                /* USER CODE BEGIN 2 */
                value = *pPDOEntry;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].index = value >> 16;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].subindex = (value & 0xFF00) >> 8;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].size = (value & 0xFF) >> 3;
                pRxPDO = OBJ_GetObjectHandle(value >> 16);
                if((0 == pRxPDO)||(NULL == pRxPDO))
                {
                    RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = NULL;
                }
                else
                {
                    RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = pRxPDO->Write;
                }
                /* USER CODE END 2 */
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;
#endif

#if MAX_PD_INPUT_SIZE > 0
    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                    /* USER CODE BEGIN 3 */
                    value = *pPDOEntry;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].index = value >> 16;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].subindex = (value & 0xFF00) >> 8;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].size = (value & 0xFF) >> 3;
                    pTxPDO = OBJ_GetObjectHandle(value >> 16);
                    if((0 == pTxPDO)||(NULL == pTxPDO))
                    {
                        TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = NULL;
                    }
                    else
                    {
                        TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = pTxPDO->Read;
                    }
                    /* USER CODE END 3 */
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;
#endif

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{
//	memcpy(pData,&(((UINT16 *)&IN_GENERIC0x6000)[1]),SIZEOF(IN_GENERIC0x6000)-2);
    UINT16 j = 0;
//    UINT8 *pTmpData = (UINT8 *)pData;
	UINT16 *pTmpData = (UINT16 *)pData;
    UINT8 AxisIndex;
    for (j = 0; j < sTxPDOassign.u16SubIndex0; j++)
    {
        /*The Axis index is based on the PDO mapping offset (0x10)*/
        AxisIndex = ((sTxPDOassign.aEntries[j] & 0xF0) >> 4);

        switch ((sTxPDOassign.aEntries[j] & 0x000F))
        {
        	case 0:    //Copy CSP/CSV TxPDO Entries
            {
                //Total 15Bytes
//            	*(UINT16*)pTmpData = Statusword0x6041;//2Bytes
//            	pTmpData += 2;
//            	*(UINT16*)pTmpData = Error_code0x603F;//2Bytes
//            	pTmpData += 2;
//            	*(INT32*)pTmpData = Position_actual_value0x6064;//4Bytes
//            	pTmpData += 4;
//            	*(INT32*)pTmpData = Velocity_actual_value0x606C;//4Bytes
//            	pTmpData += 4;
//            	*(INT16*)pTmpData = Torque_actual_value0x6077;//4Bytes
//            	pTmpData += 2;
//            	*(INT8*)pTmpData = Modes_of_operation_display0x6061;//1Bytes
//            	pTmpData += 1;

            	*pTmpData++ = Statusword0x6041;//2Bytes
            	*pTmpData++ = Error_code0x603F;//2Bytes
            	*pTmpData++ = Position_actual_value0x6064 & 0xFFFF;
            	*pTmpData++ = (Position_actual_value0x6064>>16) & 0xFFFF;
            	*pTmpData++ = Velocity_actual_value0x606C & 0xFFFF;
            	*pTmpData++ = (Velocity_actual_value0x606C>>16) & 0xFFFF;
            	*pTmpData++ = Torque_actual_value0x6077;
            	*pTmpData++ = Modes_of_operation_display0x6061 & 0x00FF;
            }
            break;

        	case 1://Copy PP TxPDO Entries
            {
                //Total 15Bytes
            	*pTmpData++ = Statusword0x6041;//2Bytes
            	*pTmpData++ = Error_code0x603F;//2Bytes
            	*pTmpData++ = Position_actual_value0x6064 & 0xFFFF;
            	*pTmpData++ = (Position_actual_value0x6064>>16) & 0xFFFF;
            	*pTmpData++ = Velocity_actual_value0x606C & 0xFFFF;
            	*pTmpData++ = (Velocity_actual_value0x606C>>16) & 0xFFFF;
            	*pTmpData++ = Torque_actual_value0x6077;
            	*pTmpData++ = Modes_of_operation_display0x6061 & 0x00FF;
            }
            break;

        	case 2://Copy PT TxPDO Entries
            {
            	*pTmpData++ = Statusword0x6041;//2Bytes
            	*pTmpData++ = Error_code0x603F;//2Bytes
            	*pTmpData++ = Torque_actual_value0x6077;
            	*pTmpData++ = Modes_of_operation_display0x6061 & 0x00FF;
            }
            break;
        }
    }
}

void APPL_InputMapping_New(UINT16* pData)
{
    UINT8 *pDataTemp = (UINT8 *)pData;
    UINT32 value = 0;
    UINT16 PDOAssignEntryCnt = 0;
    UINT16 PDOSubindex0 = 0;

    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        uint8_t pdo_order = sTxPDOassign.aEntries[PDOAssignEntryCnt] & 0x000F;
        switch (pdo_order)
        {
        case 0:
            PDOSubindex0 = TxPDO1CSPCSV0x1A00.u16SubIndex0;
            break;
        case 1:
            PDOSubindex0 = TxPDO2PP0x1A01.u16SubIndex0;
            break;
        case 2:
            PDOSubindex0 = TxPDO3PT0x1A02.u16SubIndex0;
            break;
        }
        for (uint8_t i = 0; i < PDOSubindex0; i++)
        {
            value = 0;
            if (NULL != TxPdoList[PDOAssignEntryCnt][i].HandleCallback)
            {
                TxPdoList[PDOAssignEntryCnt][i].HandleCallback(0, TxPdoList[PDOAssignEntryCnt][i].subindex, 0, (UINT16*)&value, 0);
            }
            switch (TxPdoList[PDOAssignEntryCnt][i].size)
            {
            case 1:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                break;
            case 2:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 8) & 0xFF;
                pDataTemp++;
                break;
            case 4:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 8) & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 16) & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 24) & 0xFF;
                pDataTemp++;
                break;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
//	memcpy(&(((UINT16 *)&OUT_GENERIC0x7000)[1]),pData,SIZEOF(OUT_GENERIC0x7000)-2);
    UINT16 j = 0;
//    UINT8 *pTmpData = (UINT8 *)pData;
	UINT16 *pTmpData = (UINT16 *)pData;
    UINT8 AxisIndex;
    for (j = 0; j < sRxPDOassign.u16SubIndex0; j++)
    {
        /*The Axis index is based on the PDO mapping offset (0x10)*/
        AxisIndex = ((sRxPDOassign.aEntries[j] & 0xF0) >> 4);

        switch ((sRxPDOassign.aEntries[j] & 0x000F))
        {
        	case 0:    //CSP/CSV RxPDO Entries
            {
            	Controlword0x6040      = SWAPWORD(*pTmpData++);
            	Target_position0x607A  =SWAPWORD(*pTmpData++);
            	Target_position0x607A +=(SWAPWORD(*pTmpData++) << 16);
            	Target_velocity0x60FF  =SWAPWORD(*pTmpData++);
            	Target_velocity0x60FF +=(SWAPWORD(*pTmpData++) << 16);
            	Profile_velocity0x6081  =SWAPWORD(*pTmpData++);
            	Profile_velocity0x6081 +=(SWAPWORD(*pTmpData++) << 16);
            	Profile_acceleration0x6083  =SWAPWORD(*pTmpData++);
            	Profile_acceleration0x6083 +=(SWAPWORD(*pTmpData++) << 16);
            	Profile_deceleration0x6084  =SWAPWORD(*pTmpData++);
            	Profile_deceleration0x6084 +=(SWAPWORD(*pTmpData++) << 16);
            	Modes_of_operation0x6060 = SWAPWORD(*pTmpData++) & 0xFF;
			}
            break;

        	case 1:    //PP RxPDO Entries
            {
            	Quick_stop_deceleration0x6085  =SWAPWORD(*pTmpData++);
            	Quick_stop_deceleration0x6085 +=(SWAPWORD(*pTmpData++) << 16);
            	Quick_stop_option_code0x605A  =SWAPWORD(*pTmpData++);
            	ShutdownOptionCode0x605B  =SWAPWORD(*pTmpData++);
            	DisableOperationOptionCode0x605C  =SWAPWORD(*pTmpData++);
            	HaltOptionCode0x605D  =SWAPWORD(*pTmpData++);
            	FaultReactionOptionCode0x605E  =SWAPWORD(*pTmpData++);

            }
            break;

        	case 2:    //PT RxPDO Entries
            {
            	Target_torque0x6071 = SWAPWORD(*pTmpData++);
            	Torque_slope0x6087  =SWAPWORD(*pTmpData++);
            	Torque_slope0x6087 +=(SWAPWORD(*pTmpData++) << 16);
            }
            break;
        }
    }
}

void APPL_OutputMapping_New(UINT16* pData)
{
	UINT16 *pTmpData = (UINT16 *)pData;
    UINT32 value = 0;
    UINT16 PDOAssignEntryCnt = 0;
    UINT16 PDOSubindex0 = 0;

    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        uint8_t pdo_order = sRxPDOassign.aEntries[PDOAssignEntryCnt] & 0x000F;
        switch (pdo_order)
        {
        case 0:
            PDOSubindex0 = RxPDO1CSPCSV0x1600.u16SubIndex0;
            break;
        case 1:
            PDOSubindex0 = RxPDO2PP0x1601.u16SubIndex0;
            break;
        case 2:
            PDOSubindex0 = RxPDO3PT0x1602.u16SubIndex0;
            break;
        }
        for (uint8_t i = 0; i < PDOSubindex0; i++)
        {
            value = 0;
            switch (RxPdoList[PDOAssignEntryCnt][i].size)
            {
            case 1:
                value = SWAPWORD(*pTmpData++) & 0xFF;
                break;
            case 2:
                value = SWAPWORD(*pTmpData++);
                break;
            case 4:
                value  =SWAPWORD(*pTmpData++);
                value +=(SWAPWORD(*pTmpData++) << 16);
                break;
            }
            if (NULL != RxPdoList[PDOAssignEntryCnt][i].HandleCallback)
            {
				RxPdoList[PDOAssignEntryCnt][i].HandleCallback(0, RxPdoList[PDOAssignEntryCnt][i].subindex, 0, (UINT16*)&value, 0);
                RxPdoList[PDOAssignEntryCnt][i].u32_buff = value;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void process_app(TOBJ7000 *OUT_GENERIC, TOBJ6000 *IN_GENERIC);
void APPL_Application(void)
{
//	process_app(&OUT_GENERIC0x7000, &IN_GENERIC0x6000);
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Read the Explicit Device ID (from an external ID switch)
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
#else
    #warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif



/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Read_0x203F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	*pData = SWAPWORD((UINT16)Fault_Code0x203F);
 return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Read_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	/*SSC V5.13 注册了读回调后OBJ_Read不再从 Pos_Loop_Kp0x2100 拷贝数据，在此处手动把变量值填入 pData（邮箱发送缓冲区）*/
	*pData = SWAPWORD((UINT16)Pos_Loop_Kp0x2100);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Read_0x2200_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	*pData = SWAPWORD((UINT16)Spd_Loop_Kp0x2200);
 return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Read_0x2201_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	*pData = SWAPWORD((UINT16)Spd_Loop_Ti0x2201);
 return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Write_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	INT16 newValue;
	/*SSC V5.13 注册了写回调后OBJ_Write不会把邮箱数据写入变量，在此处手动从 pData 取值并完成写入*/
	/*长度校验：0x2100 为 INT16（2字节）*/
	if (dataSize != 2)    return ABORTIDX_PARAM_LENGTH_ERROR; /* 0x0E -> 0x06070010h */

	/*从邮箱缓冲区取出待写入值（小端平台 SWAPWORD 为空操作，保证大端平台可移植）*/
	newValue = (INT16)SWAPWORD(*pData);

	/*参数范围检查：Kp 不允许为负，否则拒绝写入并回复 SDO Abort*/
	if (newValue < 0)    return ABORTIDX_VALUE_TOO_SMALL;   /* 0x14 -> 0x06090011h Value too small */

	/*写入对象字典变量并同步到伺服运动控制APP参数结构*/
	Pos_Loop_Kp0x2100 = newValue;
//	Axis.Pos_Loop_Kp  = newValue;

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Write_0x2200_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	INT16 newValue;

	/*SSC V5.13 接管模式：框架不会把邮箱数据写入变量，必须手动从 pData 取值并完成写入*/

	/*长度校验：0x2200 为 INT16（2字节）*/
	if (dataSize != 2)
	{
		return ABORTIDX_PARAM_LENGTH_ERROR; /* 0x0E -> 0x06070010h */
	}

	/*从邮箱缓冲区取出待写入值（小端平台 SWAPWORD 为空操作）*/
	newValue = (INT16)SWAPWORD(*pData);

	/*参数范围检查：速度环 Kp 不允许为负*/
	if (newValue < 0)
	{
		return ABORTIDX_VALUE_TOO_SMALL; /* 0x14 -> 0x06090011h Value too small */
	}

	/*写入对象字典变量并同步到运动控制参数结构*/
	Spd_Loop_Kp0x2200 = newValue;
//	Axis.Spd_Loop_Kp  = newValue;

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param     index               index of the requested object.
\param     subindex            subindex of the requested object.
\param     objSize             size of the requested object data, calculated with OBJ_GetObjectLength
\param     pData               Pointer to the buffer where the data can be copied to
\param     bCompleteAccess     Indicates if a complete read of all subindices of the
                               object shall be done or not

 \return    result of the read operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))
 *////////////////////////////////////////////////////////////////////////////////////////
UINT8 ECAT_Write_0x2201_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
	INT16 newValue;

	/*SSC V5.13 接管模式：框架不会把邮箱数据写入变量，必须手动从 pData 取值并完成写入*/

	/*长度校验：0x2201 为 INT16（2字节）*/
	if (dataSize != 2)
	{
		return ABORTIDX_PARAM_LENGTH_ERROR; /* 0x0E -> 0x06070010h */
	}

	/*从邮箱缓冲区取出待写入值（小端平台 SWAPWORD 为空操作）*/
	newValue = (INT16)SWAPWORD(*pData);

	/*参数范围检查：速度环 Ti 不允许为负（0 表示关闭积分作用）*/
	if (newValue < 0)
	{
		return ABORTIDX_VALUE_TOO_SMALL; /* 0x14 -> 0x06090011h Value too small */
	}

	/*写入对象字典变量并同步到运动控制参数结构*/
	Spd_Loop_Ti0x2201 = newValue;
//	Axis.Spd_Loop_Ti  = newValue;

	return 0;
}
#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////
#if _PIC24 && EL9800_HW
int main(void)
#elif _WIN32
int main(int argc, char* argv[])
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
#if _WIN32
    u16FcInstance = 0;
    if (argc > 1)
    {
        u16FcInstance = atoi(argv[1]);
    }
#endif
    if(HW_Init())
    {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();
        
    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
/** @} */

