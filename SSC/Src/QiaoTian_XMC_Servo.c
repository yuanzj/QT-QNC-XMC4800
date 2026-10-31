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
/* simulated slave 1 ms model + Pset/工步引擎 (Motion_Control/DOCH_cyclic_sync_position.c) */
extern void SimulatedSlave_Tick(void);
#include "DOCH_cyclic_sync_position.h"

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
    /* S2/M1: TxPDO 40 B —— 客户文档表 4-1（v2 §3.1），全部小端逐字节写 */
    UINT8 *p = (UINT8 *)pData;

    /* 0x00 status_code U32 (0x2200) */
    p[0]  = (UINT8)(status_code0x2200 & 0xFF);
    p[1]  = (UINT8)((status_code0x2200 >> 8) & 0xFF);
    p[2]  = (UINT8)((status_code0x2200 >> 16) & 0xFF);
    p[3]  = (UINT8)((status_code0x2200 >> 24) & 0xFF);
    /* 0x04 status_code2 U32 (0x2201) TODO(OPEN-3) 第二状态码索引为本方暂定 */
    p[4]  = (UINT8)(status_code20x2201 & 0xFF);
    p[5]  = (UINT8)((status_code20x2201 >> 8) & 0xFF);
    p[6]  = (UINT8)((status_code20x2201 >> 16) & 0xFF);
    p[7]  = (UINT8)((status_code20x2201 >> 24) & 0xFF);
    /* 0x08 torque_actual I16 (0x6077) */
    p[8]  = (UINT8)((UINT16)Torque_actual_value0x6077 & 0xFF);
    p[9]  = (UINT8)(((UINT16)Torque_actual_value0x6077 >> 8) & 0xFF);
    /* 0x0A statusword U16 (0x6041) */
    p[10] = (UINT8)(Statusword0x6041 & 0xFF);
    p[11] = (UINT8)((Statusword0x6041 >> 8) & 0xFF);
    /* 0x0C position_actual I32 (0x6064) */
    p[12] = (UINT8)((UINT32)Position_actual_value0x6064 & 0xFF);
    p[13] = (UINT8)(((UINT32)Position_actual_value0x6064 >> 8) & 0xFF);
    p[14] = (UINT8)(((UINT32)Position_actual_value0x6064 >> 16) & 0xFF);
    p[15] = (UINT8)(((UINT32)Position_actual_value0x6064 >> 24) & 0xFF);
    /* 0x10 velocity_actual I32 (0x606C) */
    p[16] = (UINT8)((UINT32)Velocity_actual_value0x606C & 0xFF);
    p[17] = (UINT8)(((UINT32)Velocity_actual_value0x606C >> 8) & 0xFF);
    p[18] = (UINT8)(((UINT32)Velocity_actual_value0x606C >> 16) & 0xFF);
    p[19] = (UINT8)(((UINT32)Velocity_actual_value0x606C >> 24) & 0xFF);
    /* 0x14 pset_echo U16 (0x220B)：高 8 = Pset 号，低 8 = 工步号 */
    p[20] = (UINT8)(pset_echo0x220B & 0xFF);
    p[21] = (UINT8)((pset_echo0x220B >> 8) & 0xFF);
    /* 0x16 step_echo U8 (0x220C) */
    p[22] = step_echo0x220C;
    /* 0x17 step_result U8 (0x220D) TODO(OPEN-4) */
    p[23] = step_result0x220D;
    /* 0x18 current_sample I32 (0x2208) */
    p[24] = (UINT8)((UINT32)current_sample0x2208 & 0xFF);
    p[25] = (UINT8)(((UINT32)current_sample0x2208 >> 8) & 0xFF);
    p[26] = (UINT8)(((UINT32)current_sample0x2208 >> 16) & 0xFF);
    p[27] = (UINT8)(((UINT32)current_sample0x2208 >> 24) & 0xFF);
    /* 0x1C/0x20/0x24 三个 32 位填充（PDO 0x0000） */
    p[28] = 0; p[29] = 0; p[30] = 0; p[31] = 0;
    p[32] = 0; p[33] = 0; p[34] = 0; p[35] = 0;
#if SIMULATION_TX_PDO_BYTES == 40
    p[36] = 0; p[37] = 0; p[38] = 0; p[39] = 0;
#endif
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
    /* RxPDO 12 B —— docx 表 4-2 主口径（C 方案）：
     *   0x00 0x2001:00 controller_status UINT32（主站→从站的控制器状态）
     *   0x04 备用 U32（PDO 填充）
     *   0x08 备用 U32（PDO 填充）
     * 运动指令不走 PDO：主站经 SDO 下发 Pset(0x2030) + 0x2031 启停，工步引擎按 Pset 参数运行。
     * CiA402 的 0x6040/0x607A/0x60FF/0x6060 仍在 OD 中，但不再进任何 PDO（只供 SDO 直驱调试）。
     */
    UINT8 *p = (UINT8 *)pData;

    controller_status0x2001 = ((UINT32)p[0]) |
                              ((UINT32)p[1] << 8) |
                              ((UINT32)p[2] << 16) |
                              ((UINT32)p[3] << 24);
    /* p[4..11]：备用 U32 ×2，忽略 */
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
/* =====================================================================================
   S2/M1: 客户 SDO 对象访问（v2 §4.2/§5）
   - 5 个对象含 U8+U32 混排子索引，32 位条目在 SSC 默认访问下必须 WORD 对齐，
     故注册对象级 Read/Write 回调，按字节偏移打包/解包（SSC ET9300 推荐做法）。
   - 0x2030:01 为 OCTET_STRING(<=1528 B)，分段 SDO 下载收完后一次性回调 Write。
   - TODO(OPEN-7): Pset 拆步与执行在 M2；本文件只做接收与长度记录。
   ===================================================================================== */
typedef struct
{
    UINT8  size;      /* 1 / 2 / 4 / 16 字节 */
    UINT16 offset;    /* 相对对象变量起点（已含 u16SubIndex0 的 2 B） */
    UINT8  writable;  /* 0 = 只读 */
} TOBJ_SDOFIELD;

static const TOBJ_SDOFIELD sSdoFields0x2000[12] = {
    { 16, 2, 0 }  /* sub1 tool_sn */,
    { 1, 18, 0 }  /* sub2 model */,
    { 4, 19, 0 }  /* sub3 max_torque */,
    { 4, 23, 0 }  /* sub4 max_speed */,
    { 1, 27, 0 }  /* sub5 max_temp */,
    { 1, 28, 0 }  /* sub6 maintenance */,
    { 4, 29, 0 }  /* sub7 service_interval */,
    { 4, 33, 0 }  /* sub8 used_life */,
    { 4, 37, 0 }  /* sub9 max_life */,
    { 4, 41, 0 }  /* sub10 torque_cal */,
    { 4, 45, 0 }  /* sub11 reserved1 */,
    { 4, 49, 0 }  /* sub12 reserved2 */
};

static const TOBJ_SDOFIELD sSdoFields0x2010[5] = {
    { 1, 2, 1 }  /* sub1 maintenance */,
    { 4, 3, 1 }  /* sub2 torque_cal */,
    { 4, 7, 1 }  /* sub3 reserved1 */,
    { 4, 11, 1 }  /* sub4 reserved2 */,
    { 4, 15, 1 }  /* sub5 reserved3 */
};

static const TOBJ_SDOFIELD sSdoFields0x2021[12] = {
    { 1, 2, 1 }  /* sub1 mode */,
    { 4, 3, 1 }  /* sub2 target_angle */,
    { 4, 7, 1 }  /* sub3 angle_threshold */,
    { 4, 11, 1 }  /* sub4 target_torque */,
    { 4, 15, 1 }  /* sub5 safe_torque */,
    { 4, 19, 1 }  /* sub6 safe_angle */,
    { 1, 23, 1 }  /* sub7 angle_reset */,
    { 1, 24, 1 }  /* sub8 torque_reset */,
    { 1, 25, 1 }  /* sub9 auto_adjust */,
    { 4, 26, 1 }  /* sub10 speed_adjust_ratio */,
    { 4, 30, 1 }  /* sub11 auto_sensitivity */,
    { 4, 34, 1 }  /* sub12 target_brake_ratio */
};

static const TOBJ_SDOFIELD sSdoFields0x2022[15] = {
    { 1, 2, 1 }  /* sub1 strategy */,
    { 4, 3, 1 }  /* sub2 target_torque */,
    { 4, 7, 1 }  /* sub3 max_torque */,
    { 4, 11, 1 }  /* sub4 min_torque */,
    { 4, 15, 1 }  /* sub5 angle_threshold */,
    { 4, 19, 1 }  /* sub6 min_angle */,
    { 4, 23, 1 }  /* sub7 max_angle */,
    { 4, 27, 1 }  /* sub8 safe_angle */,
    { 4, 31, 1 }  /* sub9 safe_torque */,
    { 4, 35, 1 }  /* sub10 target_angle */,
    { 4, 39, 1 }  /* sub11 start_torque */,
    { 1, 43, 1 }  /* sub12 torque_value_mode */,
    { 1, 44, 1 }  /* sub13 angle_value_mode */,
    { 1, 45, 1 }  /* sub14 angle_reset */,
    { 1, 46, 1 }  /* sub15 torque_reset */
};

static const TOBJ_SDOFIELD sSdoFields0x2023[10] = {
    { 1, 2, 1 }  /* sub1 strategy */,
    { 4, 3, 1 }  /* sub2 target_torque */,
    { 4, 7, 1 }  /* sub3 max_torque */,
    { 4, 11, 1 }  /* sub4 min_angle */,
    { 4, 15, 1 }  /* sub5 max_angle */,
    { 4, 19, 1 }  /* sub6 safe_torque */,
    { 4, 23, 1 }  /* sub7 target_angle */,
    { 4, 27, 1 }  /* sub8 min_torque */,
    { 4, 31, 1 }  /* sub9 angle_threshold */,
    { 4, 35, 1 }  /* sub10 safe_angle */
};

static UINT8 SdoField_Read(const UINT8 *base, const TOBJ_SDOFIELD *map,
                           UINT8 maxSubIndex, UINT8 subindex,
                           UINT32 dataSize, UINT16 MBXMEM *pData)
{
    const TOBJ_SDOFIELD *f;
    UINT16 i;

    if (subindex == 0)
    {
        /* SubIndex0 = 条目数（UINT16，按 1 字节 SDO 返回低字节） */
        pData[0] = (UINT16)((const UINT16 *)base)[0];
        return 0;
    }
    if (subindex > maxSubIndex)
    {
        return ABORTIDX_SUBINDEX_NOT_EXISTING;
    }
    f = &map[subindex - 1];
    if (dataSize != f->size)
    {
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    switch (f->size)
    {
    case 1:
        pData[0] = (UINT16)base[f->offset];
        break;
    case 2:
        pData[0] = (UINT16)base[f->offset] | ((UINT16)base[f->offset + 1] << 8);
        break;
    case 4:
        pData[0] = (UINT16)base[f->offset] | ((UINT16)base[f->offset + 1] << 8);
        pData[1] = (UINT16)base[f->offset + 2] | ((UINT16)base[f->offset + 3] << 8);
        break;
    case 16:
        for (i = 0; i < 16; i++)
        {
            ((UINT8 *)pData)[i] = base[f->offset + i];
        }
        break;
    default:
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    return 0;
}

static UINT8 SdoField_Write(UINT8 *base, const TOBJ_SDOFIELD *map,
                            UINT8 maxSubIndex, UINT8 subindex,
                            UINT32 dataSize, UINT16 MBXMEM *pData)
{
    const TOBJ_SDOFIELD *f;
    UINT16 i;

    if (subindex == 0)
    {
        /* 条目数固定，忽略对 SubIndex0 的写 */
        return 0;
    }
    if (subindex > maxSubIndex)
    {
        return ABORTIDX_SUBINDEX_NOT_EXISTING;
    }
    f = &map[subindex - 1];
    if (dataSize != f->size)
    {
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    if (f->writable == 0)
    {
        return ABORTIDX_READ_ONLY_ENTRY;
    }
    switch (f->size)
    {
    case 1:
        base[f->offset] = (UINT8)(pData[0] & 0xFF);
        break;
    case 2:
        base[f->offset]     = (UINT8)(pData[0] & 0xFF);
        base[f->offset + 1] = (UINT8)((pData[0] >> 8) & 0xFF);
        break;
    case 4:
        base[f->offset]     = (UINT8)(pData[0] & 0xFF);
        base[f->offset + 1] = (UINT8)((pData[0] >> 8) & 0xFF);
        base[f->offset + 2] = (UINT8)(pData[1] & 0xFF);
        base[f->offset + 3] = (UINT8)((pData[1] >> 8) & 0xFF);
        break;
    case 16:
        for (i = 0; i < 16; i++)
        {
            base[f->offset + i] = ((const UINT8 *)pData)[i];
        }
        break;
    default:
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    return 0;
}

UINT8 ECAT_Read_0x2000_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Read((const UINT8 *)&Tool_Spec0x2000, sSdoFields0x2000, 12, subindex, dataSize, pData);
}

UINT8 ECAT_Write_0x2000_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Write((UINT8 *)&Tool_Spec0x2000, sSdoFields0x2000, 12, subindex, dataSize, pData);
}

UINT8 ECAT_Read_0x2010_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Read((const UINT8 *)&Maintenance_Cal0x2010, sSdoFields0x2010, 5, subindex, dataSize, pData);
}

UINT8 ECAT_Write_0x2010_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Write((UINT8 *)&Maintenance_Cal0x2010, sSdoFields0x2010, 5, subindex, dataSize, pData);
}

UINT8 ECAT_Read_0x2021_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Read((const UINT8 *)&Rundown0x2021, sSdoFields0x2021, 12, subindex, dataSize, pData);
}

UINT8 ECAT_Write_0x2021_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Write((UINT8 *)&Rundown0x2021, sSdoFields0x2021, 12, subindex, dataSize, pData);
}

UINT8 ECAT_Read_0x2022_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Read((const UINT8 *)&Snug0x2022, sSdoFields0x2022, 15, subindex, dataSize, pData);
}

UINT8 ECAT_Write_0x2022_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Write((UINT8 *)&Snug0x2022, sSdoFields0x2022, 15, subindex, dataSize, pData);
}

UINT8 ECAT_Read_0x2023_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Read((const UINT8 *)&Loosen0x2023, sSdoFields0x2023, 10, subindex, dataSize, pData);
}

UINT8 ECAT_Write_0x2023_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index;
    if (bCompleteAccess != 0)
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    return SdoField_Write((UINT8 *)&Loosen0x2023, sSdoFields0x2023, 10, subindex, dataSize, pData);
}

/* C12 §5.4: CRC-32/ISO-HDLC 实现在 Motion_Control/DOCH_cyclic_sync_position.c（宿主可对拍）。 */
extern uint32_t Pset_Crc32_Calc(const uint8_t * p, uint16_t len);

/* TODO(OPEN-7): Pset 通道按 SDO 写 0x2030:01 整串；这里只接收并记录长度 */
/* S2/M2/P1: 0x2030:01 可变长度上传（Architect 硬问题 2）
 * entry desc 固定 1528 B，但主站要读回“实际收到的 Pset 长度 + 内容”（含 0x4402 CRC）。
 * 做法：第一次 OBJ_Read 回调返回 ABORTIDX_WORKING（SSC 挂起，pStoreData 里只记下邮箱数据区
 * 指针）；COE_Main 再次回调本函数，用 SDOS_SdoRes(0, 实际长度, 缓冲) 以实际 objLength
 * 生成响应，从而 CompleteSize = 实际长度（1..1528），未收到数据时为 0。
 *
 * 缓冲归属（SSC 5.13 的坑，P1 v1 曾踩中）：
 * - 第一次回调里的 pData 是收到请求的邮箱内部数据区，可用空间只有一个邮箱帧
 *   （u16SendMbxSize - MBX_HEADER_SIZE - UPLOAD_NORM_RES_SIZE，128 B 邮箱时 = 112 B），
 *   所以第一次回调不能往里拷 Pset，否则 148 B 及以上会写穿邮箱块。
 * - SDOS_SdoRes 遇到 objLength > 单帧容量会做分段上传，并把传入的 pData 直接存成
 *   pSdoSegData，分段结束后由 SSC 对 pSdoSegData 调 FREEMEM。传邮箱内部指针（不是
 *   ALLOCMEM 得到的块起始地址）就会在分段结束时 free 一个非法指针，破坏堆。
 *   因此 > 单帧容量时必须传 ALLOCMEM 的整段缓冲（SSC 负责释放），<= 单帧容量直接传 pData。
 */
UINT8 ECAT_Read_0x2030_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    UINT16 len = Pset_Buffer_Length0x2030;
    UINT16 segLimit;
    UINT16 i;

    (void)index;
    (void)dataSize;

    if ((bCompleteAccess != 0u) || (subindex != 0u))
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }

    /* 第一次（SDOS handler 内）：只挂起，不拷贝（pData 容量只有一个邮箱帧） */
    if (pSdoPendFunc == NULL)
    {
        return ABORTIDX_WORKING;
    }

    if (len > 1528u)
    {
        len = 1528u;
    }

    /* 单帧可容纳的 Pset 字节数；邮箱未初始化时按 0 处理，强制走分段缓冲，避免误判 */
    if (u16SendMbxSize > (UINT16)(MBX_HEADER_SIZE + UPLOAD_NORM_RES_SIZE))
    {
        segLimit = (UINT16)(u16SendMbxSize - (UINT16)(MBX_HEADER_SIZE + UPLOAD_NORM_RES_SIZE));
    }
    else
    {
        segLimit = 0u;
    }

    /* 第二次（COE_Main 内）：按实际长度生成上传响应 */
    if (len <= segLimit)
    {
        for (i = 0u; i < len; i++)
        {
            ((UINT8 *)pData)[i] = Pset_buffer0x2030[i];
        }
        SDOS_SdoRes(0u, (UINT32)len, pData);
    }
    else
    {
        UINT8 *pSegBuf = (UINT8 *)ALLOCMEM(ROUNDUPBYTE2WORD(len));

        if (pSegBuf == NULL)
        {
            return ABORTIDX_OUT_OF_MEMORY;
        }
        for (i = 0u; i < len; i++)
        {
            pSegBuf[i] = Pset_buffer0x2030[i];
        }
        /* 分段上传：SSC 把 pSegBuf 记为 pSdoSegData，最后一个 segment 后 FREEMEM 释放 */
        SDOS_SdoRes(0u, (UINT32)len, (UINT16 MBXMEM *)pSegBuf);
    }
    return 0u;
}

UINT8 ECAT_Write_0x2030_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    UINT32 i;
    uint32_t primask;
    uint32_t crc;
    (void)index;
    if ((bCompleteAccess != 0) || (subindex != 0))
    {
        return ABORTIDX_UNSUPPORTED_ACCESS;
    }
    if ((dataSize == 0) || (dataSize > 1528))
    {
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    /* CRC 在关中断前计算，临界区只做准入、复制和提交。 */
    crc = dataSize >= 3u ? Pset_Crc32_Calc((const UINT8 *)pData, (UINT16)dataSize) : 0u;
    /* 邮箱主循环与同步 ISR 共用参数缓冲；原子准入并提交，活动程序保持不可变。 */
    primask = __get_PRIMASK();
    __disable_irq();
    if (Pset_IsRunning())
    {
        __set_PRIMASK(primask);
        return ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED;
    }
    for (i = 0; i < dataSize; i++)
    {
        Pset_buffer0x2030[i] = ((const UINT8 *)pData)[i];
    }
    Pset_Buffer_Length0x2030 = (UINT16)dataSize;
    /* S2/C12 §5.4: 先写 CRC，最后写 length 作提交标志（单 owner 读 length->CRC）；
     * 长度 <3 B 视为无效（契约：length 有效范围 3..1528，0=无效/无 Pset）。
     * 0x2031:01=3 复位不清这两个值（Architect 2026-10-24 更正：它们描述最后一次收到的 Pset）。 */
    if (dataSize >= 3u)
    {
        Pset_CRC32_0x2039 = crc;
        __asm__ __volatile__("" ::: "memory");
        Pset_Length_0x203A = (UINT16)dataSize;
    }
    else
    {
        Pset_CRC32_0x2039 = 0u;
        __asm__ __volatile__("" ::: "memory");
        Pset_Length_0x203A = 0u;
    }
    /* S2/M2: 仅打标记，解析/执行在下一个 1 ms tick（避免邮箱上下文长循环） */
    Pset_OnBufferReceived((uint16_t)dataSize);
    __DMB();
    __set_PRIMASK(primask);
    return 0;
}

UINT8 ECAT_Read_0x2210_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index; (void)subindex; (void)dataSize; (void)bCompleteAccess;
    *pData = SWAPWORD((UINT16)Spd_Loop_Kp0x2210);
    return 0;
}

UINT8 ECAT_Write_0x2210_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    INT16 newValue;
    (void)index; (void)subindex; (void)bCompleteAccess;
    if (dataSize != 2)
    {
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    newValue = (INT16)SWAPWORD(*pData);
    if (newValue < 0)
    {
        return ABORTIDX_VALUE_TOO_SMALL; /* Kp 不允许为负 */
    }
    Spd_Loop_Kp0x2210 = newValue;
    return 0;
}

UINT8 ECAT_Read_0x2211_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    (void)index; (void)subindex; (void)dataSize; (void)bCompleteAccess;
    *pData = SWAPWORD((UINT16)Spd_Loop_Ti0x2211);
    return 0;
}

UINT8 ECAT_Write_0x2211_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess)
{
    INT16 newValue;
    (void)index; (void)subindex; (void)bCompleteAccess;
    if (dataSize != 2)
    {
        return ABORTIDX_PARAM_LENGTH_ERROR;
    }
    newValue = (INT16)SWAPWORD(*pData);
    if (newValue < 0)
    {
        return ABORTIDX_VALUE_TOO_SMALL; /* Ti 不允许为负 */
    }
    Spd_Loop_Ti0x2211 = newValue;
    return 0;
}

/* S2/M2: 1 ms 引擎访问对象字段的访问器（避免 Motion 层依赖 TOBJ 结构体类型） */
UINT8 App_JobCtrl_GetControl(void)
{
    return Job_Pset_Ctrl0x2031.control;
}

void App_JobCtrl_SetControl(UINT8 v)
{
    Job_Pset_Ctrl0x2031.control = v;   /* 命令锁存消费后清 0，主站可重复下发 */
}

UINT8 App_JobCtrl_GetPsetNo(void)
{
    return Job_Pset_Ctrl0x2031.pset_no;
}

UINT32 App_Tool_GetMaxTorque_mNm(void)
{
    return Tool_Spec0x2000.max_torque;   /* 0x2000:03，mN·m；扭矩换算基准 */
}

/* S2/M2-R1: 链路/看门狗联锁（Architect R1）
 * 只有 AL 状态 = OP 且 ESC 过程数据看门狗未过期时，工步引擎才允许运动。
 * 看门狗语义（与 SSC CheckIfEcatError 一致）：ESC 0x0440 bit0 = 1 表示看门狗仍在被触发/未过期；
 * bit0 = 0 表示过程数据看门狗已过期（SSC 自身会把 AL 拉回 SAFEOP 并报 0x001B）。
 * 注意：不依赖 TxPDO 的任何位；AL/SM 看门狗是协议状态机给出的硬条件。
 */
UINT8 App_Link_IsOperational(void)
{
    UINT16 wd_status = 0u;

    /* nAlStatus 定义在 ecatslv.c；STATE_MASK/STATE_OP 来自 ecatslv.h */
    if ((nAlStatus & STATE_MASK) != STATE_OP)
    {
        return 0u;
    }

    /* ESC_PD_WD_STATE = 0x0440，ESC_PD_WD_TRIGGER_MASK = 0x0001（esc.h） */
    HW_EscReadWord(wd_status, ESC_PD_WD_STATE);
    wd_status = SWAPWORD(wd_status);

    if ((wd_status & ESC_PD_WD_TRIGGER_MASK) == 0u)
    {
        return 0u;   /* 过程数据看门狗过期 */
    }
    return 1u;
}

void APPL_Application(void)
{
    /* 1 ms 模拟模型（Motion_Control/DOCH_cyclic_sync_position.c） */
    SimulatedSlave_Tick();

    /* 0x2001 遥测快照（SDO 读取；0x2209 不再进 PDO，v2 §3.1/§5.2） */
    Telemetry0x2002.current     = current_sample0x2208;
    Telemetry0x2002.temperature = temperature_sample0x2209;
    /* TODO(OPEN-2): 母线电压/STO 目前为固定模拟值 */
    Telemetry0x2002.bus_voltage = 0u; /* simulation: unavailable */
    Telemetry0x2002.sto_state   = 0u;
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

