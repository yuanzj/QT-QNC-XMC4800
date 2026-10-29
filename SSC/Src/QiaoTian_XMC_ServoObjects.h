/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup QiaoTian_XMC_Servo QiaoTian_XMC_Servo
* @{
*/

/**
\file QiaoTian_XMC_ServoObjects
\author ET9300Utilities.ApplicationHandler (Version 1.6.4.0) | EthercatSSC@beckhoff.com

\brief QiaoTian_XMC_Servo specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : RxPDO1 CSP/CSV
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | RxPDO1 CSP/CSV
* @{
* \brief Object 0x1600 (RxPDO1 CSP/CSV) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Control Word<br>
* SubIndex 2 - Target Position<br>
* SubIndex 3 - Target Velocity<br>
* SubIndex 4 - Profile_velocity<br>
* SubIndex 5 - Profile_acceleration<br>
* SubIndex 6 - Profile_deceleration<br>
* SubIndex 7 - Modes of Operation<br>
* SubIndex 8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Control Word */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 - Target Position */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 - Target Velocity */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 - Profile_velocity */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex5 - Profile_acceleration */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex6 - Profile_deceleration */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex7 - Modes of Operation */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "RxPDO1 CSP/CSV\000"
"Control Word\000"
"Target Position\000"
"Target Velocity\000"
"Profile_velocity\000"
"Profile_acceleration\000"
"Profile_deceleration\000"
"Modes of Operation\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
UINT32 SI7; /* Subindex7 -  */
UINT32 SI8; /* Subindex8 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 RxPDO1CSPCSV0x1600
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={8,0x60400010,0x607A0020,0x60FF0020,0x60810020,0x60830020,0x60840020,0x60600008,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1601 : RxPDO2 PP
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | RxPDO2 PP
* @{
* \brief Object 0x1601 (RxPDO2 PP) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Quick_stop_deceleration<br>
* SubIndex 2 - Quick_stop_option_code<br>
* SubIndex 3 - Shutdown_Option_Code<br>
* SubIndex 4 - Disable_Operation_OptionCode<br>
* SubIndex 5 - Halt_Option_Code<br>
* SubIndex 6 - FaultReactionOptionCode<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Quick_stop_deceleration */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 - Quick_stop_option_code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 - Shutdown_Option_Code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 - Disable_Operation_OptionCode */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex5 - Halt_Option_Code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex6 - FaultReactionOptionCode */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "RxPDO2 PP\000"
"Quick_stop_deceleration\000"
"Quick_stop_option_code\000"
"Shutdown_Option_Code\000"
"Disable_Operation_OptionCode\000"
"Halt_Option_Code\000"
"FaultReactionOptionCode\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 RxPDO2PP0x1601
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={6,0x60850020,0x605A0010,0x605B0010,0x605C0010,0x605D0010,0x605E0010}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1602 : RxPDO3 PT
******************************************************************************/
/**
* \addtogroup 0x1602 0x1602 | RxPDO3 PT
* @{
* \brief Object 0x1602 (RxPDO3 PT) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Target_torque<br>
* SubIndex 2 - Torque_slope<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1602[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Target_torque */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex2 - Torque_slope */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1602[] = "RxPDO3 PT\000"
"Target_torque\000"
"Torque_slope\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1602;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1602 RxPDO3PT0x1602
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0x60710010,0x60870020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : TxPDO1 CSP/CSV
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | TxPDO1 CSP/CSV
* @{
* \brief Object 0x1A00 (TxPDO1 CSP/CSV) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Status Word<br>
* SubIndex 2 - Error Code<br>
* SubIndex 3 - Actual Position<br>
* SubIndex 4 - Actual Velocity<br>
* SubIndex 5 - Torque_actual_value<br>
* SubIndex 6 - Modes of operation display<br>
* SubIndex 7<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Status Word */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 - Error Code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 - Actual Position */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 - Actual Velocity */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex5 - Torque_actual_value */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex6 - Modes of operation display */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex7 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "TxPDO1 CSP/CSV\000"
"Status Word\000"
"Error Code\000"
"Actual Position\000"
"Actual Velocity\000"
"Torque_actual_value\000"
"Modes of operation display\000"
"SubIndex 007\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
UINT32 SI7; /* Subindex7 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 TxPDO1CSPCSV0x1A00
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={7,0x60410010,0x603F0010,0x60640020,0x606C0020,0x60770010,0x60610008,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A01 : TxPDO2 PP
******************************************************************************/
/**
* \addtogroup 0x1A01 0x1A01 | TxPDO2 PP
* @{
* \brief Object 0x1A01 (TxPDO2 PP) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Status Word<br>
* SubIndex 2 - Error Code<br>
* SubIndex 3 - Actual Position<br>
* SubIndex 4 - Actual Velocity<br>
* SubIndex 5 - Torque_actual_value<br>
* SubIndex 6 - Modes of operation display<br>
* SubIndex 7<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A01[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Status Word */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 - Error Code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 - Actual Position */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 - Actual Velocity */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex5 - Torque_actual_value */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex6 - Modes of operation display */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex7 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A01[] = "TxPDO2 PP\000"
"Status Word\000"
"Error Code\000"
"Actual Position\000"
"Actual Velocity\000"
"Torque_actual_value\000"
"Modes of operation display\000"
"SubIndex 007\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
UINT32 SI7; /* Subindex7 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A01 TxPDO2PP0x1A01
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={7,0x60410010,0x603F0010,0x60640020,0x606C0020,0x60770010,0x60610008,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A02 : TxPDO3 PT
******************************************************************************/
/**
* \addtogroup 0x1A02 0x1A02 | TxPDO3 PT
* @{
* \brief Object 0x1A02 (TxPDO3 PT) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Status Word<br>
* SubIndex 2 - Error Code<br>
* SubIndex 3 - Torque_actual_value<br>
* SubIndex 4 - Modes of operation display<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A02[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 - Status Word */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 - Error Code */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 - Torque_actual_value */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 - Modes of operation display */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A02[] = "TxPDO3 PT\000"
"Status Word\000"
"Error Code\000"
"Torque_actual_value\000"
"Modes of operation display\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A02 TxPDO3PT0x1A02
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={5,0x60410010,0x603F0010,0x60770010,0x60610008,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : Obj0x1C12
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | Obj0x1C12
* @{
* \brief Object 0x1C12 (Obj0x1C12) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "Obj0x1C12\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[3];  /**< \brief Subindex 1 - 3 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={3,{0x1600,0x1601,0x1602}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : Obj0x1C13
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | Obj0x1C13
* @{
* \brief Object 0x1C13 (Obj0x1C13) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "Obj0x1C13\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[3];  /**< \brief Subindex 1 - 3 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={3,{0x1A00,0x1A01,0x1A02}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x203F : Fault_Code
******************************************************************************/
/**
* \addtogroup 0x203F 0x203F | Fault_Code
* @{
* \brief Object 0x203F (Fault_Code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x203F = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x203F[] = "Fault_Code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Fault_Code0x203F;
/** @}*/



/******************************************************************************
*                    Object 0x205A : Quick_stop_Test
******************************************************************************/
/**
* \addtogroup 0x205A 0x205A | Quick_stop_Test
* @{
* \brief Object 0x205A (Quick_stop_Test) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x205A = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x205A[] = "Quick_stop_Test\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Quick_stop_Test0x205A;
/** @}*/



/******************************************************************************
*                    Object 0x205B : Shutdown option_Test
******************************************************************************/
/**
* \addtogroup 0x205B 0x205B | Shutdown option_Test
* @{
* \brief Object 0x205B (Shutdown option_Test) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x205B = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x205B[] = "Shutdown option_Test\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 ShutdownOption_Test0x205B;
/** @}*/



/******************************************************************************
*                    Object 0x205C : Disable operation_Test
******************************************************************************/
/**
* \addtogroup 0x205C 0x205C | Disable operation_Test
* @{
* \brief Object 0x205C (Disable operation_Test) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x205C = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x205C[] = "Disable operation_Test\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 DisableOperation_Test0x205C;
/** @}*/



/******************************************************************************
*                    Object 0x205D : Halt option_Test
******************************************************************************/
/**
* \addtogroup 0x205D 0x205D | Halt option_Test
* @{
* \brief Object 0x205D (Halt option_Test) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x205D = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x205D[] = "Halt option_Test\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 HaltOption_Test0x205D;
/** @}*/



/******************************************************************************
*                    Object 0x205E : Fault reaction_Test
******************************************************************************/
/**
* \addtogroup 0x205E 0x205E | Fault reaction_Test
* @{
* \brief Object 0x205E (Fault reaction_Test) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x205E = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x205E[] = "Fault reaction_Test\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 FaultReaction_Test0x205E;
/** @}*/



/******************************************************************************
*                    Object 0x2100 : Pos_Loop_Kp
******************************************************************************/
/**
* \addtogroup 0x2100 0x2100 | Pos_Loop_Kp
* @{
* \brief Object 0x2100 (Pos_Loop_Kp) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2100 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2100[] = "Pos_Loop_Kp\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Pos_Loop_Kp0x2100;
/** @}*/



/******************************************************************************
*                    Object 0x2200 : Spd_Loop_Kp
******************************************************************************/
/**
* \addtogroup 0x2200 0x2200 | Spd_Loop_Kp
* @{
* \brief Object 0x2200 (Spd_Loop_Kp) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2200 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2200[] = "Spd_Loop_Kp\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Spd_Loop_Kp0x2200;
/** @}*/



/******************************************************************************
*                    Object 0x2201 : Spd_Loop_Ti
******************************************************************************/
/**
* \addtogroup 0x2201 0x2201 | Spd_Loop_Ti
* @{
* \brief Object 0x2201 (Spd_Loop_Ti) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2201 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2201[] = "Spd_Loop_Ti\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Spd_Loop_Ti0x2201;
/** @}*/



/******************************************************************************
*                    Object 0x2300 : Cur_Loop_IqKp
******************************************************************************/
/**
* \addtogroup 0x2300 0x2300 | Cur_Loop_IqKp
* @{
* \brief Object 0x2300 (Cur_Loop_IqKp) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2300 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2300[] = "Cur_Loop_IqKp\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Cur_Loop_IqKp0x2300;
/** @}*/



/******************************************************************************
*                    Object 0x2301 : Cur_Loop_IqKi
******************************************************************************/
/**
* \addtogroup 0x2301 0x2301 | Cur_Loop_IqKi
* @{
* \brief Object 0x2301 (Cur_Loop_IqKi) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2301 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2301[] = "Cur_Loop_IqKi\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Cur_Loop_IqKi0x2301;
/** @}*/



/******************************************************************************
*                    Object 0x2302 : Cur_Loop_IdKp
******************************************************************************/
/**
* \addtogroup 0x2302 0x2302 | Cur_Loop_IdKp
* @{
* \brief Object 0x2302 (Cur_Loop_IdKp) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2302 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2302[] = "Cur_Loop_IdKp\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Cur_Loop_IdKp0x2302;
/** @}*/



/******************************************************************************
*                    Object 0x2303 : Cur_Loop_IdKi
******************************************************************************/
/**
* \addtogroup 0x2303 0x2303 | Cur_Loop_IdKi
* @{
* \brief Object 0x2303 (Cur_Loop_IdKi) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2303 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2303[] = "Cur_Loop_IdKi\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Cur_Loop_IdKi0x2303;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : IN_GENERIC
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | IN_GENERIC
* @{
* \brief Object 0x6000 (IN_GENERIC) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - IN_GEN_INT1<br>
* SubIndex 2 - IN_GEN_INT2<br>
* SubIndex 3 - IN_GEN_INT3<br>
* SubIndex 4 - IN_GEN_INT4<br>
* SubIndex 5 - IN_GEN_Bit1<br>
* SubIndex 6 - IN_GEN_Bit2<br>
* SubIndex 7 - IN_GEN_Bit3<br>
* SubIndex 8 - IN_GEN_Bit4<br>
* SubIndex 9 - IN_GEN_Bit5<br>
* SubIndex 10 - IN_GEN_Bit6<br>
* SubIndex 11 - IN_GEN_Bit7<br>
* SubIndex 12 - IN_GEN_Bit8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - IN_GEN_INT1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex2 - IN_GEN_INT2 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex3 - IN_GEN_INT3 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex4 - IN_GEN_INT4 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex5 - IN_GEN_Bit1 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex6 - IN_GEN_Bit2 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex7 - IN_GEN_Bit3 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex8 - IN_GEN_Bit4 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex9 - IN_GEN_Bit5 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex10 - IN_GEN_Bit6 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }, /* Subindex11 - IN_GEN_Bit7 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READ }}; /* Subindex12 - IN_GEN_Bit8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "IN_GENERIC\000"
"IN_GEN_INT1\000"
"IN_GEN_INT2\000"
"IN_GEN_INT3\000"
"IN_GEN_INT4\000"
"IN_GEN_Bit1\000"
"IN_GEN_Bit2\000"
"IN_GEN_Bit3\000"
"IN_GEN_Bit4\000"
"IN_GEN_Bit5\000"
"IN_GEN_Bit6\000"
"IN_GEN_Bit7\000"
"IN_GEN_Bit8\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IN_GEN_INT1; /* Subindex1 - IN_GEN_INT1 */
UINT16 IN_GEN_INT2; /* Subindex2 - IN_GEN_INT2 */
UINT16 IN_GEN_INT3; /* Subindex3 - IN_GEN_INT3 */
UINT16 IN_GEN_INT4; /* Subindex4 - IN_GEN_INT4 */
BOOLEAN(IN_GEN_Bit1); /* Subindex5 - IN_GEN_Bit1 */
BOOLEAN(IN_GEN_Bit2); /* Subindex6 - IN_GEN_Bit2 */
BOOLEAN(IN_GEN_Bit3); /* Subindex7 - IN_GEN_Bit3 */
BOOLEAN(IN_GEN_Bit4); /* Subindex8 - IN_GEN_Bit4 */
BOOLEAN(IN_GEN_Bit5); /* Subindex9 - IN_GEN_Bit5 */
BOOLEAN(IN_GEN_Bit6); /* Subindex10 - IN_GEN_Bit6 */
BOOLEAN(IN_GEN_Bit7); /* Subindex11 - IN_GEN_Bit7 */
BOOLEAN(IN_GEN_Bit8); /* Subindex12 - IN_GEN_Bit8 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 IN_GENERIC0x6000
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={12,0x0000,0x0000,0x0000,0x0000,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x603F : Error_code
******************************************************************************/
/**
* \addtogroup 0x603F 0x603F | Error_code
* @{
* \brief Object 0x603F (Error_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x603F = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x603F[] = "Error_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Error_code0x603F;
/** @}*/



/******************************************************************************
*                    Object 0x6040 : Controlword
******************************************************************************/
/**
* \addtogroup 0x6040 0x6040 | Controlword
* @{
* \brief Object 0x6040 (Controlword) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6040 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6040[] = "Controlword\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Controlword0x6040;
/** @}*/



/******************************************************************************
*                    Object 0x6041 : Statusword
******************************************************************************/
/**
* \addtogroup 0x6041 0x6041 | Statusword
* @{
* \brief Object 0x6041 (Statusword) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6041 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6041[] = "Statusword\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Statusword0x6041;
/** @}*/



/******************************************************************************
*                    Object 0x605A : Quick_stop_option_code
******************************************************************************/
/**
* \addtogroup 0x605A 0x605A | Quick_stop_option_code
* @{
* \brief Object 0x605A (Quick_stop_option_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605A = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605A[] = "Quick_stop_option_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Quick_stop_option_code0x605A
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x0000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x605B : Shutdown option code
******************************************************************************/
/**
* \addtogroup 0x605B 0x605B | Shutdown option code
* @{
* \brief Object 0x605B (Shutdown option code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605B = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605B[] = "Shutdown option code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 ShutdownOptionCode0x605B
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x0000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x605C : Disable operation option code
******************************************************************************/
/**
* \addtogroup 0x605C 0x605C | Disable operation option code
* @{
* \brief Object 0x605C (Disable operation option code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605C = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605C[] = "Disable operation option code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 DisableOperationOptionCode0x605C
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x0000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x605D : Halt option code
******************************************************************************/
/**
* \addtogroup 0x605D 0x605D | Halt option code
* @{
* \brief Object 0x605D (Halt option code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605D = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605D[] = "Halt option code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 HaltOptionCode0x605D
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x0000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x605E : Fault reaction option code
******************************************************************************/
/**
* \addtogroup 0x605E 0x605E | Fault reaction option code
* @{
* \brief Object 0x605E (Fault reaction option code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605E = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605E[] = "Fault reaction option code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 FaultReactionOptionCode0x605E
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x0000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6060 : Modes_of_operation
******************************************************************************/
/**
* \addtogroup 0x6060 0x6060 | Modes_of_operation
* @{
* \brief Object 0x6060 (Modes_of_operation) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6060 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6060[] = "Modes_of_operation\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Modes_of_operation0x6060;
/** @}*/



/******************************************************************************
*                    Object 0x6061 : Modes_of_operation_display
******************************************************************************/
/**
* \addtogroup 0x6061 0x6061 | Modes_of_operation_display
* @{
* \brief Object 0x6061 (Modes_of_operation_display) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6061 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6061[] = "Modes_of_operation_display\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Modes_of_operation_display0x6061;
/** @}*/



/******************************************************************************
*                    Object 0x6062 : Position_demand_value
******************************************************************************/
/**
* \addtogroup 0x6062 0x6062 | Position_demand_value
* @{
* \brief Object 0x6062 (Position_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6062 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6062[] = "Position_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_demand_value0x6062;
/** @}*/



/******************************************************************************
*                    Object 0x6063 : Position_actual_value_inc
******************************************************************************/
/**
* \addtogroup 0x6063 0x6063 | Position_actual_value_inc
* @{
* \brief Object 0x6063 (Position_actual_value_inc) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6063 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6063[] = "Position_actual_value_inc\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_actual_value_inc0x6063;
/** @}*/



/******************************************************************************
*                    Object 0x6064 : Position_actual_value
******************************************************************************/
/**
* \addtogroup 0x6064 0x6064 | Position_actual_value
* @{
* \brief Object 0x6064 (Position_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6064 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6064[] = "Position_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_actual_value0x6064;
/** @}*/



/******************************************************************************
*                    Object 0x6065 : Following_error_window
******************************************************************************/
/**
* \addtogroup 0x6065 0x6065 | Following_error_window
* @{
* \brief Object 0x6065 (Following_error_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6065 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6065[] = "Following_error_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Following_error_window0x6065;
/** @}*/



/******************************************************************************
*                    Object 0x6066 : Following_error_time_out
******************************************************************************/
/**
* \addtogroup 0x6066 0x6066 | Following_error_time_out
* @{
* \brief Object 0x6066 (Following_error_time_out) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6066 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6066[] = "Following_error_time_out\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Following_error_time_out0x6066;
/** @}*/



/******************************************************************************
*                    Object 0x6067 : Position_window
******************************************************************************/
/**
* \addtogroup 0x6067 0x6067 | Position_window
* @{
* \brief Object 0x6067 (Position_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6067 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6067[] = "Position_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Position_window0x6067;
/** @}*/



/******************************************************************************
*                    Object 0x6068 : Position_window_time
******************************************************************************/
/**
* \addtogroup 0x6068 0x6068 | Position_window_time
* @{
* \brief Object 0x6068 (Position_window_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6068 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6068[] = "Position_window_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Position_window_time0x6068;
/** @}*/



/******************************************************************************
*                    Object 0x606B : Velocity_demand_value
******************************************************************************/
/**
* \addtogroup 0x606B 0x606B | Velocity_demand_value
* @{
* \brief Object 0x606B (Velocity_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606B = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606B[] = "Velocity_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_demand_value0x606B;
/** @}*/



/******************************************************************************
*                    Object 0x606C : Velocity_actual_value
******************************************************************************/
/**
* \addtogroup 0x606C 0x606C | Velocity_actual_value
* @{
* \brief Object 0x606C (Velocity_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606C = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606C[] = "Velocity_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_actual_value0x606C;
/** @}*/



/******************************************************************************
*                    Object 0x606D : Velocity_window
******************************************************************************/
/**
* \addtogroup 0x606D 0x606D | Velocity_window
* @{
* \brief Object 0x606D (Velocity_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606D = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606D[] = "Velocity_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_window0x606D;
/** @}*/



/******************************************************************************
*                    Object 0x606E : Velocity_window_time
******************************************************************************/
/**
* \addtogroup 0x606E 0x606E | Velocity_window_time
* @{
* \brief Object 0x606E (Velocity_window_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606E = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606E[] = "Velocity_window_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_window_time0x606E;
/** @}*/



/******************************************************************************
*                    Object 0x606F : Velocity_threshold
******************************************************************************/
/**
* \addtogroup 0x606F 0x606F | Velocity_threshold
* @{
* \brief Object 0x606F (Velocity_threshold) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606F = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606F[] = "Velocity_threshold\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_threshold0x606F;
/** @}*/



/******************************************************************************
*                    Object 0x6070 : Velocity_threshold_time
******************************************************************************/
/**
* \addtogroup 0x6070 0x6070 | Velocity_threshold_time
* @{
* \brief Object 0x6070 (Velocity_threshold_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6070 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6070[] = "Velocity_threshold_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_threshold_time0x6070;
/** @}*/



/******************************************************************************
*                    Object 0x6071 : Target_torque
******************************************************************************/
/**
* \addtogroup 0x6071 0x6071 | Target_torque
* @{
* \brief Object 0x6071 (Target_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6071 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6071[] = "Target_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Target_torque0x6071;
/** @}*/



/******************************************************************************
*                    Object 0x6072 : Max_torque
******************************************************************************/
/**
* \addtogroup 0x6072 0x6072 | Max_torque
* @{
* \brief Object 0x6072 (Max_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6072 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6072[] = "Max_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Max_torque0x6072;
/** @}*/



/******************************************************************************
*                    Object 0x6073 : Max_current
******************************************************************************/
/**
* \addtogroup 0x6073 0x6073 | Max_current
* @{
* \brief Object 0x6073 (Max_current) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6073 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6073[] = "Max_current\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Max_current0x6073;
/** @}*/



/******************************************************************************
*                    Object 0x6074 : Torque_demand_value
******************************************************************************/
/**
* \addtogroup 0x6074 0x6074 | Torque_demand_value
* @{
* \brief Object 0x6074 (Torque_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6074 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6074[] = "Torque_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_demand_value0x6074;
/** @}*/



/******************************************************************************
*                    Object 0x6075 : Motor_rated_current
******************************************************************************/
/**
* \addtogroup 0x6075 0x6075 | Motor_rated_current
* @{
* \brief Object 0x6075 (Motor_rated_current) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6075 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6075[] = "Motor_rated_current\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Motor_rated_current0x6075;
/** @}*/



/******************************************************************************
*                    Object 0x6076 : Motor_rated_torque
******************************************************************************/
/**
* \addtogroup 0x6076 0x6076 | Motor_rated_torque
* @{
* \brief Object 0x6076 (Motor_rated_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6076 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6076[] = "Motor_rated_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Motor_rated_torque0x6076;
/** @}*/



/******************************************************************************
*                    Object 0x6077 : Torque_actual_value
******************************************************************************/
/**
* \addtogroup 0x6077 0x6077 | Torque_actual_value
* @{
* \brief Object 0x6077 (Torque_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6077 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6077[] = "Torque_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_actual_value0x6077;
/** @}*/



/******************************************************************************
*                    Object 0x6078 : Current_actual_value
******************************************************************************/
/**
* \addtogroup 0x6078 0x6078 | Current_actual_value
* @{
* \brief Object 0x6078 (Current_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6078 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6078[] = "Current_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Current_actual_value0x6078;
/** @}*/



/******************************************************************************
*                    Object 0x6079 : DC_link_circuit_voltage
******************************************************************************/
/**
* \addtogroup 0x6079 0x6079 | DC_link_circuit_voltage
* @{
* \brief Object 0x6079 (DC_link_circuit_voltage) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6079 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6079[] = "DC_link_circuit_voltage\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 DC_link_circuit_voltage0x6079;
/** @}*/



/******************************************************************************
*                    Object 0x607A : Target_position
******************************************************************************/
/**
* \addtogroup 0x607A 0x607A | Target_position
* @{
* \brief Object 0x607A (Target_position) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607A = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607A[] = "Target_position\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Target_position0x607A;
/** @}*/



/******************************************************************************
*                    Object 0x607B : Position_range_limit
******************************************************************************/
/**
* \addtogroup 0x607B 0x607B | Position_range_limit
* @{
* \brief Object 0x607B (Position_range_limit) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Position_range_limit_Minimal_position_limit<br>
* SubIndex 2 - Position_range_limit_Maximal_position_limit<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x607B[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Position_range_limit_Minimal_position_limit */
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Position_range_limit_Maximal_position_limit */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x607B[] = "Position_range_limit\000"
"Position_range_limit_Minimal_position_limit\000"
"Position_range_limit_Maximal_position_limit\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 Position_range_limit_Minimal_position_limit; /* Subindex1 - Position_range_limit_Minimal_position_limit */
INT32 Position_range_limit_Maximal_position_limit; /* Subindex2 - Position_range_limit_Maximal_position_limit */
} OBJ_STRUCT_PACKED_END
TOBJ607B;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ607B Position_range_limit0x607B
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x607D : Software_position_limit
******************************************************************************/
/**
* \addtogroup 0x607D 0x607D | Software_position_limit
* @{
* \brief Object 0x607D (Software_position_limit) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Software_position_limit_Minimal_position_limit<br>
* SubIndex 2 - Software_position_limit_Maximal_position_limit<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x607D[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Software_position_limit_Minimal_position_limit */
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Software_position_limit_Maximal_position_limit */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x607D[] = "Software_position_limit\000"
"Software_position_limit_Minimal_position_limit\000"
"Software_position_limit_Maximal_position_limit\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 Software_position_limit_Minimal_position_limit; /* Subindex1 - Software_position_limit_Minimal_position_limit */
INT32 Software_position_limit_Maximal_position_limit; /* Subindex2 - Software_position_limit_Maximal_position_limit */
} OBJ_STRUCT_PACKED_END
TOBJ607D;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ607D Software_position_limit0x607D
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x607E : Polarity
******************************************************************************/
/**
* \addtogroup 0x607E 0x607E | Polarity
* @{
* \brief Object 0x607E (Polarity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607E = { DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607E[] = "Polarity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 Polarity0x607E;
/** @}*/



/******************************************************************************
*                    Object 0x607F : Max_profile_velocity
******************************************************************************/
/**
* \addtogroup 0x607F 0x607F | Max_profile_velocity
* @{
* \brief Object 0x607F (Max_profile_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607F = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607F[] = "Max_profile_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_profile_velocity0x607F;
/** @}*/



/******************************************************************************
*                    Object 0x6080 : Max_motor_speed
******************************************************************************/
/**
* \addtogroup 0x6080 0x6080 | Max_motor_speed
* @{
* \brief Object 0x6080 (Max_motor_speed) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6080 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6080[] = "Max_motor_speed\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_motor_speed0x6080;
/** @}*/



/******************************************************************************
*                    Object 0x6081 : Profile_velocity
******************************************************************************/
/**
* \addtogroup 0x6081 0x6081 | Profile_velocity
* @{
* \brief Object 0x6081 (Profile_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6081 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6081[] = "Profile_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_velocity0x6081;
/** @}*/



/******************************************************************************
*                    Object 0x6083 : Profile_acceleration
******************************************************************************/
/**
* \addtogroup 0x6083 0x6083 | Profile_acceleration
* @{
* \brief Object 0x6083 (Profile_acceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6083 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6083[] = "Profile_acceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_acceleration0x6083;
/** @}*/



/******************************************************************************
*                    Object 0x6084 : Profile_deceleration
******************************************************************************/
/**
* \addtogroup 0x6084 0x6084 | Profile_deceleration
* @{
* \brief Object 0x6084 (Profile_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6084 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6084[] = "Profile_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_deceleration0x6084;
/** @}*/



/******************************************************************************
*                    Object 0x6085 : Quick_stop_deceleration
******************************************************************************/
/**
* \addtogroup 0x6085 0x6085 | Quick_stop_deceleration
* @{
* \brief Object 0x6085 (Quick_stop_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6085 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6085[] = "Quick_stop_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Quick_stop_deceleration0x6085;
/** @}*/



/******************************************************************************
*                    Object 0x6087 : Torque_slope
******************************************************************************/
/**
* \addtogroup 0x6087 0x6087 | Torque_slope
* @{
* \brief Object 0x6087 (Torque_slope) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6087 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6087[] = "Torque_slope\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Torque_slope0x6087;
/** @}*/



/******************************************************************************
*                    Object 0x608F : Position_encoder_resolution
******************************************************************************/
/**
* \addtogroup 0x608F 0x608F | Position_encoder_resolution
* @{
* \brief Object 0x608F (Position_encoder_resolution) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Position_encoder_resolution_Encoder_increments<br>
* SubIndex 2 - Position_encoder_resolution_Motor_revolutions<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x608F[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Position_encoder_resolution_Encoder_increments */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Position_encoder_resolution_Motor_revolutions */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x608F[] = "Position_encoder_resolution\000"
"Position_encoder_resolution_Encoder_increments\000"
"Position_encoder_resolution_Motor_revolutions\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Position_encoder_resolution_Encoder_increments; /* Subindex1 - Position_encoder_resolution_Encoder_increments */
UINT32 Position_encoder_resolution_Motor_revolutions; /* Subindex2 - Position_encoder_resolution_Motor_revolutions */
} OBJ_STRUCT_PACKED_END
TOBJ608F;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ608F Position_encoder_resolution0x608F
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6091 : Gear_ratio
******************************************************************************/
/**
* \addtogroup 0x6091 0x6091 | Gear_ratio
* @{
* \brief Object 0x6091 (Gear_ratio) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Motor_revolutions<br>
* SubIndex 2 - Shaft_revolutions<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6091[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Motor_revolutions */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Shaft_revolutions */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6091[] = "Gear_ratio\000"
"Motor_revolutions\000"
"Shaft_revolutions\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Motor_revolutions; /* Subindex1 - Motor_revolutions */
UINT32 Shaft_revolutions; /* Subindex2 - Shaft_revolutions */
} OBJ_STRUCT_PACKED_END
TOBJ6091;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6091 Gear_ratio0x6091
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6098 : Homing_method
******************************************************************************/
/**
* \addtogroup 0x6098 0x6098 | Homing_method
* @{
* \brief Object 0x6098 (Homing_method) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6098 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6098[] = "Homing_method\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Homing_method0x6098;
/** @}*/



/******************************************************************************
*                    Object 0x60B0 : Position_offset
******************************************************************************/
/**
* \addtogroup 0x60B0 0x60B0 | Position_offset
* @{
* \brief Object 0x60B0 (Position_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B0 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B0[] = "Position_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_offset0x60B0;
/** @}*/



/******************************************************************************
*                    Object 0x60B1 : Velocity_offset
******************************************************************************/
/**
* \addtogroup 0x60B1 0x60B1 | Velocity_offset
* @{
* \brief Object 0x60B1 (Velocity_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B1 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B1[] = "Velocity_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_offset0x60B1;
/** @}*/



/******************************************************************************
*                    Object 0x60B2 : Torque_offset
******************************************************************************/
/**
* \addtogroup 0x60B2 0x60B2 | Torque_offset
* @{
* \brief Object 0x60B2 (Torque_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B2 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B2[] = "Torque_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_offset0x60B2;
/** @}*/



/******************************************************************************
*                    Object 0x60C2 : Interpolation_time_period
******************************************************************************/
/**
* \addtogroup 0x60C2 0x60C2 | Interpolation_time_period
* @{
* \brief Object 0x60C2 (Interpolation_time_period) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Interpolation_time_period_Ip_time_units<br>
* SubIndex 2 - Interpolation_time_period_Ip_time_index<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C2[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Interpolation_time_period_Ip_time_units */
{ DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Interpolation_time_period_Ip_time_index */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x60C2[] = "Interpolation_time_period\000"
"Interpolation_time_period_Ip_time_units\000"
"Interpolation_time_period_Ip_time_index\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 Interpolation_time_period_Ip_time_units; /* Subindex1 - Interpolation_time_period_Ip_time_units */
INT8 Interpolation_time_period_Ip_time_index; /* Subindex2 - Interpolation_time_period_Ip_time_index */
} OBJ_STRUCT_PACKED_END
TOBJ60C2;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ60C2 Interpolation_time_period0x60C2
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60C5 : Max_acceleration
******************************************************************************/
/**
* \addtogroup 0x60C5 0x60C5 | Max_acceleration
* @{
* \brief Object 0x60C5 (Max_acceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C5 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60C5[] = "Max_acceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_acceleration0x60C5;
/** @}*/



/******************************************************************************
*                    Object 0x60C6 : Max_deceleration
******************************************************************************/
/**
* \addtogroup 0x60C6 0x60C6 | Max_deceleration
* @{
* \brief Object 0x60C6 (Max_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C6 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60C6[] = "Max_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_deceleration0x60C6;
/** @}*/



/******************************************************************************
*                    Object 0x60F4 : Following_error_actual_value
******************************************************************************/
/**
* \addtogroup 0x60F4 0x60F4 | Following_error_actual_value
* @{
* \brief Object 0x60F4 (Following_error_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60F4 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60F4[] = "Following_error_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Following_error_actual_value0x60F4;
/** @}*/



/******************************************************************************
*                    Object 0x60FD : Digital_inputs
******************************************************************************/
/**
* \addtogroup 0x60FD 0x60FD | Digital_inputs
* @{
* \brief Object 0x60FD (Digital_inputs) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FD = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60FD[] = "Digital_inputs\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Digital_inputs0x60FD;
/** @}*/



/******************************************************************************
*                    Object 0x60FE : Digital_outputs
******************************************************************************/
/**
* \addtogroup 0x60FE 0x60FE | Digital_outputs
* @{
* \brief Object 0x60FE (Digital_outputs) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Digital_outputs_Physical_outputs<br>
* SubIndex 2 - Digital_outputs_Bit_mask<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FE[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Digital_outputs_Physical_outputs */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Digital_outputs_Bit_mask */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x60FE[] = "Digital_outputs\000"
"Digital_outputs_Physical_outputs\000"
"Digital_outputs_Bit_mask\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Digital_outputs_Physical_outputs; /* Subindex1 - Digital_outputs_Physical_outputs */
UINT32 Digital_outputs_Bit_mask; /* Subindex2 - Digital_outputs_Bit_mask */
} OBJ_STRUCT_PACKED_END
TOBJ60FE;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ60FE Digital_outputs0x60FE
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60FF : Target_velocity
******************************************************************************/
/**
* \addtogroup 0x60FF 0x60FF | Target_velocity
* @{
* \brief Object 0x60FF (Target_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FF = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60FF[] = "Target_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Target_velocity0x60FF;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : OUT_GENERIC
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | OUT_GENERIC
* @{
* \brief Object 0x7000 (OUT_GENERIC) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - OUT_GEN_INT1<br>
* SubIndex 2 - OUT_GEN_INT2<br>
* SubIndex 3 - OUT_GEN_INT3<br>
* SubIndex 4 - OUT_GEN_INT4<br>
* SubIndex 5 - OUT_GEN_Bit1<br>
* SubIndex 6 - OUT_GEN_Bit2<br>
* SubIndex 7 - OUT_GEN_Bit3<br>
* SubIndex 8 - OUT_GEN_Bit4<br>
* SubIndex 9 - OUT_GEN_Bit5<br>
* SubIndex 10 - OUT_GEN_Bit6<br>
* SubIndex 11 - OUT_GEN_Bit7<br>
* SubIndex 12 - OUT_GEN_Bit8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }, /* Subindex1 - OUT_GEN_INT1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }, /* Subindex2 - OUT_GEN_INT2 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }, /* Subindex3 - OUT_GEN_INT3 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }, /* Subindex4 - OUT_GEN_INT4 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex5 - OUT_GEN_Bit1 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex6 - OUT_GEN_Bit2 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex7 - OUT_GEN_Bit3 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex8 - OUT_GEN_Bit4 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex9 - OUT_GEN_Bit5 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex10 - OUT_GEN_Bit6 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }, /* Subindex11 - OUT_GEN_Bit7 */
{ DEFTYPE_BOOLEAN , 0x01 , ACCESS_READWRITE }}; /* Subindex12 - OUT_GEN_Bit8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "OUT_GENERIC\000"
"OUT_GEN_INT1\000"
"OUT_GEN_INT2\000"
"OUT_GEN_INT3\000"
"OUT_GEN_INT4\000"
"OUT_GEN_Bit1\000"
"OUT_GEN_Bit2\000"
"OUT_GEN_Bit3\000"
"OUT_GEN_Bit4\000"
"OUT_GEN_Bit5\000"
"OUT_GEN_Bit6\000"
"OUT_GEN_Bit7\000"
"OUT_GEN_Bit8\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 OUT_GEN_INT1; /* Subindex1 - OUT_GEN_INT1 */
UINT16 OUT_GEN_INT2; /* Subindex2 - OUT_GEN_INT2 */
UINT16 OUT_GEN_INT3; /* Subindex3 - OUT_GEN_INT3 */
UINT16 OUT_GEN_INT4; /* Subindex4 - OUT_GEN_INT4 */
BOOLEAN(OUT_GEN_Bit1); /* Subindex5 - OUT_GEN_Bit1 */
BOOLEAN(OUT_GEN_Bit2); /* Subindex6 - OUT_GEN_Bit2 */
BOOLEAN(OUT_GEN_Bit3); /* Subindex7 - OUT_GEN_Bit3 */
BOOLEAN(OUT_GEN_Bit4); /* Subindex8 - OUT_GEN_Bit4 */
BOOLEAN(OUT_GEN_Bit5); /* Subindex9 - OUT_GEN_Bit5 */
BOOLEAN(OUT_GEN_Bit6); /* Subindex10 - OUT_GEN_Bit6 */
BOOLEAN(OUT_GEN_Bit7); /* Subindex11 - OUT_GEN_Bit7 */
BOOLEAN(OUT_GEN_Bit8); /* Subindex12 - OUT_GEN_Bit8 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 OUT_GENERIC0x7000
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={12,0x0000,0x0000,0x0000,0x0000,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7010 : OutputCounter
******************************************************************************/
/**
* \addtogroup 0x7010 0x7010 | OutputCounter
* @{
* \brief Object 0x7010 (OutputCounter) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7010 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7010[] = "OutputCounter\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 OutputCounter0x7010
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
= 0x00000000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/





PROTO UINT8 ECAT_Read_0x203F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2200_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2201_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2200_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2201_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);


#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &RxPDO1CSPCSV0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &RxPDO2PP0x1601 , NULL , NULL , 0x0000 },
/* Object 0x1602 */
{NULL , NULL ,  0x1602 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1602 , aName0x1602 , &RxPDO3PT0x1602 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &TxPDO1CSPCSV0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &TxPDO2PP0x1A01 , NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &TxPDO3PT0x1A02 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x203F */
{NULL , NULL ,  0x203F , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x203F , aName0x203F , &Fault_Code0x203F , ECAT_Read_0x203F_Callback , NULL , 0x0000 },
/* Object 0x205A */
{NULL , NULL ,  0x205A , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x205A , aName0x205A , &Quick_stop_Test0x205A , NULL , NULL , 0x0000 },
/* Object 0x205B */
{NULL , NULL ,  0x205B , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x205B , aName0x205B , &ShutdownOption_Test0x205B , NULL , NULL , 0x0000 },
/* Object 0x205C */
{NULL , NULL ,  0x205C , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x205C , aName0x205C , &DisableOperation_Test0x205C , NULL , NULL , 0x0000 },
/* Object 0x205D */
{NULL , NULL ,  0x205D , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x205D , aName0x205D , &HaltOption_Test0x205D , NULL , NULL , 0x0000 },
/* Object 0x205E */
{NULL , NULL ,  0x205E , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x205E , aName0x205E , &FaultReaction_Test0x205E , NULL , NULL , 0x0000 },
/* Object 0x2100 */
{NULL , NULL ,  0x2100 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2100 , aName0x2100 , &Pos_Loop_Kp0x2100 , ECAT_Read_0x2100_Callback , ECAT_Write_0x2100_Callback , 0x0000 },
/* Object 0x2200 */
{NULL , NULL ,  0x2200 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2200 , aName0x2200 , &Spd_Loop_Kp0x2200 , ECAT_Read_0x2200_Callback , ECAT_Write_0x2200_Callback , 0x0000 },
/* Object 0x2201 */
{NULL , NULL ,  0x2201 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2201 , aName0x2201 , &Spd_Loop_Ti0x2201 , ECAT_Read_0x2201_Callback , ECAT_Write_0x2201_Callback , 0x0000 },
/* Object 0x2300 */
{NULL , NULL ,  0x2300 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2300 , aName0x2300 , &Cur_Loop_IqKp0x2300 , NULL , NULL , 0x0000 },
/* Object 0x2301 */
{NULL , NULL ,  0x2301 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2301 , aName0x2301 , &Cur_Loop_IqKi0x2301 , NULL , NULL , 0x0000 },
/* Object 0x2302 */
{NULL , NULL ,  0x2302 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2302 , aName0x2302 , &Cur_Loop_IdKp0x2302 , NULL , NULL , 0x0000 },
/* Object 0x2303 */
{NULL , NULL ,  0x2303 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2303 , aName0x2303 , &Cur_Loop_IdKi0x2303 , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 12 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &IN_GENERIC0x6000 , NULL , NULL , 0x0000 },
/* Object 0x603F */
{NULL , NULL ,  0x603F , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x603F , aName0x603F , &Error_code0x603F , NULL , NULL , 0x0000 },
/* Object 0x6040 */
{NULL , NULL ,  0x6040 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6040 , aName0x6040 , &Controlword0x6040 , NULL , NULL , 0x0000 },
/* Object 0x6041 */
{NULL , NULL ,  0x6041 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6041 , aName0x6041 , &Statusword0x6041 , NULL , NULL , 0x0000 },
/* Object 0x605A */
{NULL , NULL ,  0x605A , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605A , aName0x605A , &Quick_stop_option_code0x605A , NULL , NULL , 0x0000 },
/* Object 0x605B */
{NULL , NULL ,  0x605B , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605B , aName0x605B , &ShutdownOptionCode0x605B , NULL , NULL , 0x0000 },
/* Object 0x605C */
{NULL , NULL ,  0x605C , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605C , aName0x605C , &DisableOperationOptionCode0x605C , NULL , NULL , 0x0000 },
/* Object 0x605D */
{NULL , NULL ,  0x605D , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605D , aName0x605D , &HaltOptionCode0x605D , NULL , NULL , 0x0000 },
/* Object 0x605E */
{NULL , NULL ,  0x605E , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605E , aName0x605E , &FaultReactionOptionCode0x605E , NULL , NULL , 0x0000 },
/* Object 0x6060 */
{NULL , NULL ,  0x6060 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6060 , aName0x6060 , &Modes_of_operation0x6060 , NULL , NULL , 0x0000 },
/* Object 0x6061 */
{NULL , NULL ,  0x6061 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6061 , aName0x6061 , &Modes_of_operation_display0x6061 , NULL , NULL , 0x0000 },
/* Object 0x6062 */
{NULL , NULL ,  0x6062 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6062 , aName0x6062 , &Position_demand_value0x6062 , NULL , NULL , 0x0000 },
/* Object 0x6063 */
{NULL , NULL ,  0x6063 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6063 , aName0x6063 , &Position_actual_value_inc0x6063 , NULL , NULL , 0x0000 },
/* Object 0x6064 */
{NULL , NULL ,  0x6064 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6064 , aName0x6064 , &Position_actual_value0x6064 , NULL , NULL , 0x0000 },
/* Object 0x6065 */
{NULL , NULL ,  0x6065 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6065 , aName0x6065 , &Following_error_window0x6065 , NULL , NULL , 0x0000 },
/* Object 0x6066 */
{NULL , NULL ,  0x6066 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6066 , aName0x6066 , &Following_error_time_out0x6066 , NULL , NULL , 0x0000 },
/* Object 0x6067 */
{NULL , NULL ,  0x6067 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6067 , aName0x6067 , &Position_window0x6067 , NULL , NULL , 0x0000 },
/* Object 0x6068 */
{NULL , NULL ,  0x6068 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6068 , aName0x6068 , &Position_window_time0x6068 , NULL , NULL , 0x0000 },
/* Object 0x606B */
{NULL , NULL ,  0x606B , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606B , aName0x606B , &Velocity_demand_value0x606B , NULL , NULL , 0x0000 },
/* Object 0x606C */
{NULL , NULL ,  0x606C , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606C , aName0x606C , &Velocity_actual_value0x606C , NULL , NULL , 0x0000 },
/* Object 0x606D */
{NULL , NULL ,  0x606D , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606D , aName0x606D , &Velocity_window0x606D , NULL , NULL , 0x0000 },
/* Object 0x606E */
{NULL , NULL ,  0x606E , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606E , aName0x606E , &Velocity_window_time0x606E , NULL , NULL , 0x0000 },
/* Object 0x606F */
{NULL , NULL ,  0x606F , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606F , aName0x606F , &Velocity_threshold0x606F , NULL , NULL , 0x0000 },
/* Object 0x6070 */
{NULL , NULL ,  0x6070 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6070 , aName0x6070 , &Velocity_threshold_time0x6070 , NULL , NULL , 0x0000 },
/* Object 0x6071 */
{NULL , NULL ,  0x6071 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6071 , aName0x6071 , &Target_torque0x6071 , NULL , NULL , 0x0000 },
/* Object 0x6072 */
{NULL , NULL ,  0x6072 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6072 , aName0x6072 , &Max_torque0x6072 , NULL , NULL , 0x0000 },
/* Object 0x6073 */
{NULL , NULL ,  0x6073 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6073 , aName0x6073 , &Max_current0x6073 , NULL , NULL , 0x0000 },
/* Object 0x6074 */
{NULL , NULL ,  0x6074 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6074 , aName0x6074 , &Torque_demand_value0x6074 , NULL , NULL , 0x0000 },
/* Object 0x6075 */
{NULL , NULL ,  0x6075 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6075 , aName0x6075 , &Motor_rated_current0x6075 , NULL , NULL , 0x0000 },
/* Object 0x6076 */
{NULL , NULL ,  0x6076 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6076 , aName0x6076 , &Motor_rated_torque0x6076 , NULL , NULL , 0x0000 },
/* Object 0x6077 */
{NULL , NULL ,  0x6077 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6077 , aName0x6077 , &Torque_actual_value0x6077 , NULL , NULL , 0x0000 },
/* Object 0x6078 */
{NULL , NULL ,  0x6078 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6078 , aName0x6078 , &Current_actual_value0x6078 , NULL , NULL , 0x0000 },
/* Object 0x6079 */
{NULL , NULL ,  0x6079 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6079 , aName0x6079 , &DC_link_circuit_voltage0x6079 , NULL , NULL , 0x0000 },
/* Object 0x607A */
{NULL , NULL ,  0x607A , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607A , aName0x607A , &Target_position0x607A , NULL , NULL , 0x0000 },
/* Object 0x607B */
{NULL , NULL ,  0x607B , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x607B , aName0x607B , &Position_range_limit0x607B , NULL , NULL , 0x0000 },
/* Object 0x607D */
{NULL , NULL ,  0x607D , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x607D , aName0x607D , &Software_position_limit0x607D , NULL , NULL , 0x0000 },
/* Object 0x607E */
{NULL , NULL ,  0x607E , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607E , aName0x607E , &Polarity0x607E , NULL , NULL , 0x0000 },
/* Object 0x607F */
{NULL , NULL ,  0x607F , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607F , aName0x607F , &Max_profile_velocity0x607F , NULL , NULL , 0x0000 },
/* Object 0x6080 */
{NULL , NULL ,  0x6080 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6080 , aName0x6080 , &Max_motor_speed0x6080 , NULL , NULL , 0x0000 },
/* Object 0x6081 */
{NULL , NULL ,  0x6081 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6081 , aName0x6081 , &Profile_velocity0x6081 , NULL , NULL , 0x0000 },
/* Object 0x6083 */
{NULL , NULL ,  0x6083 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6083 , aName0x6083 , &Profile_acceleration0x6083 , NULL , NULL , 0x0000 },
/* Object 0x6084 */
{NULL , NULL ,  0x6084 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6084 , aName0x6084 , &Profile_deceleration0x6084 , NULL , NULL , 0x0000 },
/* Object 0x6085 */
{NULL , NULL ,  0x6085 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6085 , aName0x6085 , &Quick_stop_deceleration0x6085 , NULL , NULL , 0x0000 },
/* Object 0x6087 */
{NULL , NULL ,  0x6087 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6087 , aName0x6087 , &Torque_slope0x6087 , NULL , NULL , 0x0000 },
/* Object 0x608F */
{NULL , NULL ,  0x608F , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x608F , aName0x608F , &Position_encoder_resolution0x608F , NULL , NULL , 0x0000 },
/* Object 0x6091 */
{NULL , NULL ,  0x6091 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x6091 , aName0x6091 , &Gear_ratio0x6091 , NULL , NULL , 0x0000 },
/* Object 0x6098 */
{NULL , NULL ,  0x6098 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6098 , aName0x6098 , &Homing_method0x6098 , NULL , NULL , 0x0000 },
/* Object 0x60B0 */
{NULL , NULL ,  0x60B0 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B0 , aName0x60B0 , &Position_offset0x60B0 , NULL , NULL , 0x0000 },
/* Object 0x60B1 */
{NULL , NULL ,  0x60B1 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B1 , aName0x60B1 , &Velocity_offset0x60B1 , NULL , NULL , 0x0000 },
/* Object 0x60B2 */
{NULL , NULL ,  0x60B2 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B2 , aName0x60B2 , &Torque_offset0x60B2 , NULL , NULL , 0x0000 },
/* Object 0x60C2 */
{NULL , NULL ,  0x60C2 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x60C2 , aName0x60C2 , &Interpolation_time_period0x60C2 , NULL , NULL , 0x0000 },
/* Object 0x60C5 */
{NULL , NULL ,  0x60C5 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60C5 , aName0x60C5 , &Max_acceleration0x60C5 , NULL , NULL , 0x0000 },
/* Object 0x60C6 */
{NULL , NULL ,  0x60C6 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60C6 , aName0x60C6 , &Max_deceleration0x60C6 , NULL , NULL , 0x0000 },
/* Object 0x60F4 */
{NULL , NULL ,  0x60F4 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60F4 , aName0x60F4 , &Following_error_actual_value0x60F4 , NULL , NULL , 0x0000 },
/* Object 0x60FD */
{NULL , NULL ,  0x60FD , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60FD , aName0x60FD , &Digital_inputs0x60FD , NULL , NULL , 0x0000 },
/* Object 0x60FE */
{NULL , NULL ,  0x60FE , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x60FE , aName0x60FE , &Digital_outputs0x60FE , NULL , NULL , 0x0000 },
/* Object 0x60FF */
{NULL , NULL ,  0x60FF , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60FF , aName0x60FF , &Target_velocity0x60FF , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 12 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &OUT_GENERIC0x7000 , NULL , NULL , 0x0000 },
/* Object 0x7010 */
{NULL , NULL ,  0x7010 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7010 , aName0x7010 , &OutputCounter0x7010 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

#undef PROTO

/** @}*/
#define _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
