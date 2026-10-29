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
* SubIndex 1 - mapped entry 0x20010020<br>
* SubIndex 2 - mapped entry 0x00000020<br>
* SubIndex 3 - mapped entry 0x00000020<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x20010020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x00000020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* 0x00000020 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "RxPDO1 CSP/CSV\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 */
UINT32 SI2; /* Subindex2 */
UINT32 SI3; /* Subindex3 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 RxPDO1CSPCSV0x1600
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={3,0x20010020,0x00000020,0x00000020}
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
*                    Object 0x1A00 : TxPDO 40B
******************************************************************************/

/**
* \addtogroup 0x1A00 0x1A00 | TxPDO 40B
* @{
* \brief Object 0x1A00 (TxPDO 40B) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - mapped entry 0x22000020<br>
* SubIndex 2 - mapped entry 0x22010020<br>
* SubIndex 3 - mapped entry 0x60770010<br>
* SubIndex 4 - mapped entry 0x60410010<br>
* SubIndex 5 - mapped entry 0x60640020<br>
* SubIndex 6 - mapped entry 0x606C0020<br>
* SubIndex 7 - mapped entry 0x220B0010<br>
* SubIndex 8 - mapped entry 0x220C0008<br>
* SubIndex 9 - mapped entry 0x220D0008<br>
* SubIndex 10 - mapped entry 0x22080020<br>
* SubIndex 11 - mapped entry 0x00000020<br>
* SubIndex 12 - mapped entry 0x00000020<br>
* SubIndex 13 - mapped entry 0x00000020<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x22000020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x22010020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x60770010 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x60410010 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x60640020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x606C0020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x220B0010 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x220C0008 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x220D0008 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x22080020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x00000020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* 0x00000020 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* 0x00000020 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "TxPDO 40B\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 */
UINT32 SI2; /* Subindex2 */
UINT32 SI3; /* Subindex3 */
UINT32 SI4; /* Subindex4 */
UINT32 SI5; /* Subindex5 */
UINT32 SI6; /* Subindex6 */
UINT32 SI7; /* Subindex7 */
UINT32 SI8; /* Subindex8 */
UINT32 SI9; /* Subindex9 */
UINT32 SI10; /* Subindex10 */
UINT32 SI11; /* Subindex11 */
UINT32 SI12; /* Subindex12 */
UINT32 SI13; /* Subindex13 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 TxPDO1CSPCSV0x1A00
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={13,0x22000020,0x22010020,0x60770010,0x60410010,0x60640020,0x606C0020,0x220B0010,0x220C0008,0x220D0008,0x22080020,0x00000020,0x00000020,0x00000020}
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
={1,{0x1600,0x0000,0x0000}}
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
={1,{0x1A00,0x0000,0x0000}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x2039 : pset_crc32
******************************************************************************/
/**
* \addtogroup 0x2039 0x2039 | pset_crc32
* @{
* \brief Object 0x2039 (pset_crc32) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2039 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2039[] = "pset_crc32\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Pset_CRC32_0x2039;
/** @}*/

/******************************************************************************
*                    Object 0x203A : pset_length
******************************************************************************/
/**
* \addtogroup 0x203A 0x203A | pset_length
* @{
* \brief Object 0x203A (pset_length) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x203A = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x203A[] = "pset_length\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Pset_Length_0x203A;
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
*                    Object 0x2200 : status_code
******************************************************************************/

/**
* \addtogroup 0x2200 0x2200 | status_code
* @{
* \brief Object 0x2200 (status_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2200 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2200[] = "status_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 status_code0x2200;
/** @}*/

/******************************************************************************
*                    Object 0x2201 : status_code2
******************************************************************************/

/**
* \addtogroup 0x2201 0x2201 | status_code2
* @{
* \brief Object 0x2201 (status_code2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2201 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2201[] = "status_code2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 status_code20x2201;
/** @}*/

/******************************************************************************
*                    Object 0x2202 : status_code
******************************************************************************/
/**
* \addtogroup 0x2202 0x2202 | status_code
* @{
* \brief Object 0x2202 (status_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2202 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2202[] = "status_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 status_code0x2202;
/** @}*/
/******************************************************************************
*                    Object 0x2203 : fail_code
******************************************************************************/
/**
* \addtogroup 0x2203 0x2203 | fail_code
* @{
* \brief Object 0x2203 (fail_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2203 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2203[] = "fail_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 fail_code0x2203;
/** @}*/
/******************************************************************************
*                    Object 0x2208 : current_sample
******************************************************************************/
/**
* \addtogroup 0x2208 0x2208 | current_sample
* @{
* \brief Object 0x2208 (current_sample) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2208 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2208[] = "current_sample\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 current_sample0x2208;
/** @}*/
/******************************************************************************
*                    Object 0x2209 : temperature_sample
******************************************************************************/
/**
* \addtogroup 0x2209 0x2209 | temperature_sample
* @{
* \brief Object 0x2209 (temperature_sample) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2209 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2209[] = "temperature_sample\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 temperature_sample0x2209;
/** @}*/
/******************************************************************************
*                    Object 0x220B : pset_echo
******************************************************************************/

/**
* \addtogroup 0x220B 0x220B | pset_echo
* @{
* \brief Object 0x220B (pset_echo) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x220B = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x220B[] = "pset_echo\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 pset_echo0x220B;
/** @}*/

/******************************************************************************
*                    Object 0x220C : step_echo
******************************************************************************/
/**
* \addtogroup 0x220C 0x220C | step_echo
* @{
* \brief Object 0x220C (step_echo) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x220C = { DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x220C[] = "step_echo\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 step_echo0x220C;
/** @}*/
/******************************************************************************
*                    Object 0x220D : step_result
******************************************************************************/
/**
* \addtogroup 0x220D 0x220D | step_result
* @{
* \brief Object 0x220D (step_result) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x220D = { DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x220D[] = "step_result\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 step_result0x220D;
/** @}*/



/******************************************************************************
*                    Object 0x2210 : Spd_Loop_Kp
******************************************************************************/

/**
* \addtogroup 0x2210 0x2210 | Spd_Loop_Kp
* @{
* \brief Object 0x2210 (Spd_Loop_Kp) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2210 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2210[] = "Spd_Loop_Kp\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Spd_Loop_Kp0x2210;
/** @}*/

/******************************************************************************
*                    Object 0x2211 : Spd_Loop_Ti
******************************************************************************/

/**
* \addtogroup 0x2211 0x2211 | Spd_Loop_Ti
* @{
* \brief Object 0x2211 (Spd_Loop_Ti) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2211 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2211[] = "Spd_Loop_Ti\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Spd_Loop_Ti0x2211;
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
={2,8388608,1}
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
={2,30,1}
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





/* TODO(OPEN-2): 0x2000 按 docx 表 5-1（12 sub / 51 B）实现；xlsx 另一套字段未采用 */
/* TODO(OPEN-5): 0x2000/0x2010/0x2020-0x2024/0x2030/0x2031/0x2032 索引为本方分配；0x2002 遥测
   注意：0x2001 按 Architect 复核（B1 未确认）不定义任何东西，留空 */

/******************************************************************************
*                    Object 0x2000 : Tool_Spec
******************************************************************************/

/**
* \addtogroup 0x2000 0x2000 | Tool_Spec
* @{
* \brief Object 0x2000 (Tool_Spec) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - tool_sn<br>
* SubIndex 2 - model<br>
* SubIndex 3 - max_torque<br>
* SubIndex 4 - max_speed<br>
* SubIndex 5 - max_temp<br>
* SubIndex 6 - maintenance<br>
* SubIndex 7 - service_interval<br>
* SubIndex 8 - used_life<br>
* SubIndex 9 - max_life<br>
* SubIndex 10 - torque_cal<br>
* SubIndex 11 - reserved1<br>
* SubIndex 12 - reserved2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_OCTETSTRING , 0x80 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2000[] = "Tool_Spec\000"
"tool_sn\000"
"model\000"
"max_torque\000"
"max_speed\000"
"max_temp\000"
"maintenance\000"
"service_interval\000"
"used_life\000"
"max_life\000"
"torque_cal\000"
"reserved1\000"
"reserved2\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 tool_sn[16]; /* Subindex1 - tool_sn */
UINT8 model; /* Subindex2 - model */
UINT32 max_torque; /* Subindex3 - max_torque */
UINT32 max_speed; /* Subindex4 - max_speed */
UINT8 max_temp; /* Subindex5 - max_temp */
UINT8 maintenance; /* Subindex6 - maintenance */
UINT32 service_interval; /* Subindex7 - service_interval */
UINT32 used_life; /* Subindex8 - used_life */
UINT32 max_life; /* Subindex9 - max_life */
UINT32 torque_cal; /* Subindex10 - torque_cal */
UINT32 reserved1; /* Subindex11 - reserved1 */
UINT32 reserved2; /* Subindex12 - reserved2 */
} OBJ_STRUCT_PACKED_END
TOBJ2000;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2000 Tool_Spec0x2000
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={12,"QIAOTIAN-TW-0001",1,30000,500000,60,0,1000000,0,5000000,1000,0,0}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2001 : Controller_Status
******************************************************************************/

/**
* \addtogroup 0x2001 0x2001 | Controller_Status
* @{
* \brief Object 0x2001 (Controller_Status) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2001 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2001[] = "Controller_Status\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 controller_status0x2001;
/** @}*/

/******************************************************************************
*                    Object 0x2002 : Telemetry
******************************************************************************/

/**
* \addtogroup 0x2002 0x2002 | Telemetry
* @{
* \brief Object 0x2002 (Telemetry) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - current<br>
* SubIndex 2 - temperature<br>
* SubIndex 3 - bus_voltage<br>
* SubIndex 4 - sto_state<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2002[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2002[] = "Telemetry\000"
"current\000"
"temperature\000"
"bus_voltage\000"
"sto_state\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 current; /* Subindex1 - current */
INT32 temperature; /* Subindex2 - temperature */
UINT32 bus_voltage; /* Subindex3 - bus_voltage */
UINT8 sto_state; /* Subindex4 - sto_state */
} OBJ_STRUCT_PACKED_END
TOBJ2002;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2002 Telemetry0x2002
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={4,0,24500,48000,0}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2010 : Maintenance_Cal
******************************************************************************/

/**
* \addtogroup 0x2010 0x2010 | Maintenance_Cal
* @{
* \brief Object 0x2010 (Maintenance_Cal) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - maintenance<br>
* SubIndex 2 - torque_cal<br>
* SubIndex 3 - reserved1<br>
* SubIndex 4 - reserved2<br>
* SubIndex 5 - reserved3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2010[] = "Maintenance_Cal\000"
"maintenance\000"
"torque_cal\000"
"reserved1\000"
"reserved2\000"
"reserved3\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 maintenance; /* Subindex1 - maintenance */
UINT32 torque_cal; /* Subindex2 - torque_cal */
UINT32 reserved1; /* Subindex3 - reserved1 */
UINT32 reserved2; /* Subindex4 - reserved2 */
UINT32 reserved3; /* Subindex5 - reserved3 */
} OBJ_STRUCT_PACKED_END
TOBJ2010;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2010 Maintenance_Cal0x2010
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={5,0,1000,0,0,0}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2020 : Socket_Identify
******************************************************************************/

/**
* \addtogroup 0x2020 0x2020 | Socket_Identify
* @{
* \brief Object 0x2020 (Socket_Identify) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - stop_torque<br>
* SubIndex 2 - rotate_angle<br>
* SubIndex 3 - repeat_delay_ms<br>
* SubIndex 4 - repeat_count<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2020[] = "Socket_Identify\000"
"stop_torque\000"
"rotate_angle\000"
"repeat_delay_ms\000"
"repeat_count\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 stop_torque; /* Subindex1 - stop_torque */
INT32 rotate_angle; /* Subindex2 - rotate_angle */
UINT32 repeat_delay_ms; /* Subindex3 - repeat_delay_ms */
UINT8 repeat_count; /* Subindex4 - repeat_count */
} OBJ_STRUCT_PACKED_END
TOBJ2020;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2020 Socket_Identify0x2020
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={4,1500,3000,100,1}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2021 : Rundown
******************************************************************************/

/**
* \addtogroup 0x2021 0x2021 | Rundown
* @{
* \brief Object 0x2021 (Rundown) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - mode<br>
* SubIndex 2 - target_angle<br>
* SubIndex 3 - angle_threshold<br>
* SubIndex 4 - target_torque<br>
* SubIndex 5 - safe_torque<br>
* SubIndex 6 - safe_angle<br>
* SubIndex 7 - angle_reset<br>
* SubIndex 8 - torque_reset<br>
* SubIndex 9 - auto_adjust<br>
* SubIndex 10 - speed_adjust_ratio<br>
* SubIndex 11 - auto_sensitivity<br>
* SubIndex 12 - target_brake_ratio<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2021[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2021[] = "Rundown\000"
"mode\000"
"target_angle\000"
"angle_threshold\000"
"target_torque\000"
"safe_torque\000"
"safe_angle\000"
"angle_reset\000"
"torque_reset\000"
"auto_adjust\000"
"speed_adjust_ratio\000"
"auto_sensitivity\000"
"target_brake_ratio\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 mode; /* Subindex1 - mode */
INT32 target_angle; /* Subindex2 - target_angle */
INT32 angle_threshold; /* Subindex3 - angle_threshold */
INT32 target_torque; /* Subindex4 - target_torque */
INT32 safe_torque; /* Subindex5 - safe_torque */
INT32 safe_angle; /* Subindex6 - safe_angle */
UINT8 angle_reset; /* Subindex7 - angle_reset */
UINT8 torque_reset; /* Subindex8 - torque_reset */
UINT8 auto_adjust; /* Subindex9 - auto_adjust */
UINT32 speed_adjust_ratio; /* Subindex10 - speed_adjust_ratio */
UINT32 auto_sensitivity; /* Subindex11 - auto_sensitivity */
UINT32 target_brake_ratio; /* Subindex12 - target_brake_ratio */
} OBJ_STRUCT_PACKED_END
TOBJ2021;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2021 Rundown0x2021
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={12,1,180000,1500,1500,1500,360000,1,1,0,500,1000,990}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2022 : Snug
******************************************************************************/

/**
* \addtogroup 0x2022 0x2022 | Snug
* @{
* \brief Object 0x2022 (Snug) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - strategy<br>
* SubIndex 2 - target_torque<br>
* SubIndex 3 - max_torque<br>
* SubIndex 4 - min_torque<br>
* SubIndex 5 - angle_threshold<br>
* SubIndex 6 - min_angle<br>
* SubIndex 7 - max_angle<br>
* SubIndex 8 - safe_angle<br>
* SubIndex 9 - safe_torque<br>
* SubIndex 10 - target_angle<br>
* SubIndex 11 - start_torque<br>
* SubIndex 12 - torque_value_mode<br>
* SubIndex 13 - angle_value_mode<br>
* SubIndex 14 - angle_reset<br>
* SubIndex 15 - torque_reset<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2022[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2022[] = "Snug\000"
"strategy\000"
"target_torque\000"
"max_torque\000"
"min_torque\000"
"angle_threshold\000"
"min_angle\000"
"max_angle\000"
"safe_angle\000"
"safe_torque\000"
"target_angle\000"
"start_torque\000"
"torque_value_mode\000"
"angle_value_mode\000"
"angle_reset\000"
"torque_reset\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 strategy; /* Subindex1 - strategy */
INT32 target_torque; /* Subindex2 - target_torque */
INT32 max_torque; /* Subindex3 - max_torque */
INT32 min_torque; /* Subindex4 - min_torque */
INT32 angle_threshold; /* Subindex5 - angle_threshold */
INT32 min_angle; /* Subindex6 - min_angle */
INT32 max_angle; /* Subindex7 - max_angle */
INT32 safe_angle; /* Subindex8 - safe_angle */
INT32 safe_torque; /* Subindex9 - safe_torque */
INT32 target_angle; /* Subindex10 - target_angle */
INT32 start_torque; /* Subindex11 - start_torque */
UINT8 torque_value_mode; /* Subindex12 - torque_value_mode */
UINT8 angle_value_mode; /* Subindex13 - angle_value_mode */
UINT8 angle_reset; /* Subindex14 - angle_reset */
UINT8 torque_reset; /* Subindex15 - torque_reset */
} OBJ_STRUCT_PACKED_END
TOBJ2022;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2022 Snug0x2022
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={15,0,15000,30000,0,1500,10000,20000,100000,30000,15000,1000,0,1,1,1}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2023 : Loosen
******************************************************************************/

/**
* \addtogroup 0x2023 0x2023 | Loosen
* @{
* \brief Object 0x2023 (Loosen) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - strategy<br>
* SubIndex 2 - target_torque<br>
* SubIndex 3 - max_torque<br>
* SubIndex 4 - min_angle<br>
* SubIndex 5 - max_angle<br>
* SubIndex 6 - safe_torque<br>
* SubIndex 7 - target_angle<br>
* SubIndex 8 - min_torque<br>
* SubIndex 9 - angle_threshold<br>
* SubIndex 10 - safe_angle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2023[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2023[] = "Loosen\000"
"strategy\000"
"target_torque\000"
"max_torque\000"
"min_angle\000"
"max_angle\000"
"safe_torque\000"
"target_angle\000"
"min_torque\000"
"angle_threshold\000"
"safe_angle\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 strategy; /* Subindex1 - strategy */
INT32 target_torque; /* Subindex2 - target_torque */
INT32 max_torque; /* Subindex3 - max_torque */
INT32 min_angle; /* Subindex4 - min_angle */
INT32 max_angle; /* Subindex5 - max_angle */
INT32 safe_torque; /* Subindex6 - safe_torque */
INT32 target_angle; /* Subindex7 - target_angle */
INT32 min_torque; /* Subindex8 - min_torque */
INT32 angle_threshold; /* Subindex9 - angle_threshold */
INT32 safe_angle; /* Subindex10 - safe_angle */
} OBJ_STRUCT_PACKED_END
TOBJ2023;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2023 Loosen0x2023
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={10,0,15000,30000,10000,20000,30000,15000,0,1500,100000}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2024 : Socket_Release
******************************************************************************/

/**
* \addtogroup 0x2024 0x2024 | Socket_Release
* @{
* \brief Object 0x2024 (Socket_Release) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - torque_limit<br>
* SubIndex 2 - release_threshold<br>
* SubIndex 3 - release_angle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2024[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2024[] = "Socket_Release\000"
"torque_limit\000"
"release_threshold\000"
"release_angle\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 torque_limit; /* Subindex1 - torque_limit */
INT32 release_threshold; /* Subindex2 - release_threshold */
INT32 release_angle; /* Subindex3 - release_angle */
} OBJ_STRUCT_PACKED_END
TOBJ2024;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2024 Socket_Release0x2024
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={3,1500,0,500}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2031 : Job_Pset_Ctrl
******************************************************************************/

/**
* \addtogroup 0x2031 0x2031 | Job_Pset_Ctrl
* @{
* \brief Object 0x2031 (Job_Pset_Ctrl) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - control<br>
* SubIndex 2 - pset_no<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2031[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2031[] = "Job_Pset_Ctrl\000"
"control\000"
"pset_no\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 control; /* Subindex1 - control */
UINT8 pset_no; /* Subindex2 - pset_no */
} OBJ_STRUCT_PACKED_END
TOBJ2031;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2031 Job_Pset_Ctrl0x2031
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={2,0,0}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2032 : KB_Cal
******************************************************************************/

/**
* \addtogroup 0x2032 0x2032 | KB_Cal
* @{
* \brief Object 0x2032 (KB_Cal) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - cal_type<br>
* SubIndex 2 - pset_no<br>
* SubIndex 3 - k_value<br>
* SubIndex 4 - b_value<br>
* SubIndex 5 - cycle_limit<br>
* SubIndex 6 - commit<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x2032[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE }};

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x2032[] = "KB_Cal\000"
"cal_type\000"
"pset_no\000"
"k_value\000"
"b_value\000"
"cycle_limit\000"
"commit\000\377";
#endif //#ifdef _OBJD_

#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 cal_type; /* Subindex1 - cal_type */
UINT8 pset_no; /* Subindex2 - pset_no */
UINT32 k_value; /* Subindex3 - k_value */
INT32 b_value; /* Subindex4 - b_value */
UINT32 cycle_limit; /* Subindex5 - cycle_limit */
UINT8 commit; /* Subindex6 - commit */
} OBJ_STRUCT_PACKED_END
TOBJ2032;
#endif //#ifndef _QIAO_TIAN__XMC__SERVO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ2032 KB_Cal0x2032
#if defined(_QIAO_TIAN__XMC__SERVO_) && (_QIAO_TIAN__XMC__SERVO_ == 1)
={6,0,0,1000,0,250000,0}
#endif
;
/** @}*/


/******************************************************************************
*                    Object 0x2030 : Pset_Buffer
******************************************************************************/

/**
* \addtogroup 0x2030 0x2030 | Pset_Buffer
* @{
* \brief Object 0x2030 (Pset_Buffer) definition：OCTET_STRING <=1528 B，下载用自定义 Write
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2030 = { DEFTYPE_OCTETSTRING , 0x2FC0 , ACCESS_READWRITE };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2030[] = "Pset_Buffer\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable：1528 B 影子缓冲（M1 只接收，M2 拆步执行）
*/
PROTO UINT8 Pset_buffer0x2030[1528];
PROTO UINT16 Pset_Buffer_Length0x2030;
/** @}*/

PROTO UINT8 ECAT_Read_0x203F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2100_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2000_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2000_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2010_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2010_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2021_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2021_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2022_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2022_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2023_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2023_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2030_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2030_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2210_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2210_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Read_0x2211_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 ECAT_Write_0x2211_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);


#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &RxPDO1CSPCSV0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &RxPDO2PP0x1601 , NULL , NULL , 0x0000 },
/* Object 0x1602 */
{NULL , NULL ,  0x1602 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1602 , aName0x1602 , &RxPDO3PT0x1602 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 13 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &TxPDO1CSPCSV0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &TxPDO2PP0x1A01 , NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &TxPDO3PT0x1A02 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2000 , {DEFTYPE_RECORD , 12 | (OBJCODE_REC << 8)} , asEntryDesc0x2000 , aName0x2000 , &Tool_Spec0x2000 , ECAT_Read_0x2000_Callback , ECAT_Write_0x2000_Callback , 0x0000 },
{NULL , NULL ,  0x2001 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2001 , aName0x2001 , &controller_status0x2001 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2002 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x2002 , aName0x2002 , &Telemetry0x2002 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2010 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x2010 , aName0x2010 , &Maintenance_Cal0x2010 , ECAT_Read_0x2010_Callback , ECAT_Write_0x2010_Callback , 0x0000 },
{NULL , NULL ,  0x2020 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x2020 , aName0x2020 , &Socket_Identify0x2020 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2021 , {DEFTYPE_RECORD , 12 | (OBJCODE_REC << 8)} , asEntryDesc0x2021 , aName0x2021 , &Rundown0x2021 , ECAT_Read_0x2021_Callback , ECAT_Write_0x2021_Callback , 0x0000 },
{NULL , NULL ,  0x2022 , {DEFTYPE_RECORD , 15 | (OBJCODE_REC << 8)} , asEntryDesc0x2022 , aName0x2022 , &Snug0x2022 , ECAT_Read_0x2022_Callback , ECAT_Write_0x2022_Callback , 0x0000 },
{NULL , NULL ,  0x2023 , {DEFTYPE_RECORD , 10 | (OBJCODE_REC << 8)} , asEntryDesc0x2023 , aName0x2023 , &Loosen0x2023 , ECAT_Read_0x2023_Callback , ECAT_Write_0x2023_Callback , 0x0000 },
{NULL , NULL ,  0x2024 , {DEFTYPE_RECORD , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x2024 , aName0x2024 , &Socket_Release0x2024 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2031 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x2031 , aName0x2031 , &Job_Pset_Ctrl0x2031 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2032 , {DEFTYPE_RECORD , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x2032 , aName0x2032 , &KB_Cal0x2032 , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2030 , {DEFTYPE_OCTETSTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2030 , aName0x2030 , &Pset_buffer0x2030 , ECAT_Read_0x2030_Callback , ECAT_Write_0x2030_Callback , 0x0000 },
/* Object 0x2039 */
{NULL , NULL ,  0x2039 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2039 , aName0x2039 , &Pset_CRC32_0x2039 , NULL , NULL , 0x0000 },
/* Object 0x203A */
{NULL , NULL ,  0x203A , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x203A , aName0x203A , &Pset_Length_0x203A , NULL , NULL , 0x0000 },
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
{NULL , NULL ,  0x2200 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2200 , aName0x2200 , &status_code0x2200 , NULL , NULL , 0x0000 },
/* Object 0x2201 */
{NULL , NULL ,  0x2201 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2201 , aName0x2201 , &status_code20x2201 , NULL , NULL , 0x0000 },
/* Object 0x2202 */
{NULL , NULL ,  0x2202 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2202 , aName0x2202 , &status_code0x2202 , NULL , NULL , 0x0000 },
/* Object 0x2203 */
{NULL , NULL ,  0x2203 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2203 , aName0x2203 , &fail_code0x2203 , NULL , NULL , 0x0000 },
/* Object 0x2208 */
{NULL , NULL ,  0x2208 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2208 , aName0x2208 , &current_sample0x2208 , NULL , NULL , 0x0000 },
/* Object 0x2209 */
{NULL , NULL ,  0x2209 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2209 , aName0x2209 , &temperature_sample0x2209 , NULL , NULL , 0x0000 },
/* Object 0x220B */
{NULL , NULL ,  0x220B , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x220B , aName0x220B , &pset_echo0x220B , NULL , NULL , 0x0000 },
/* Object 0x220C */
{NULL , NULL ,  0x220C , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x220C , aName0x220C , &step_echo0x220C , NULL , NULL , 0x0000 },
/* Object 0x220D */
{NULL , NULL ,  0x220D , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x220D , aName0x220D , &step_result0x220D , NULL , NULL , 0x0000 },
{NULL , NULL ,  0x2210 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2210 , aName0x2210 , &Spd_Loop_Kp0x2210 , ECAT_Read_0x2210_Callback , ECAT_Write_0x2210_Callback , 0x0000 },
{NULL , NULL ,  0x2211 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2211 , aName0x2211 , &Spd_Loop_Ti0x2211 , ECAT_Read_0x2211_Callback , ECAT_Write_0x2211_Callback , 0x0000 },

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
