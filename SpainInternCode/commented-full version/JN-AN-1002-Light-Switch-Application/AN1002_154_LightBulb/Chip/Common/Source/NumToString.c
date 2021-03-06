/****************************************************************************
 *
 * MODULE:             Driver for UC1601 and UC1606 LCD Driver-Controller
 *
 * COMPONENT:          NumToString.c,v
 *
 * VERSION:            Build_Release_030308_RC1
 *
 * REVISION:           1.2
 *
 * DATED:              2008/02/29 18:25:58
 *
 * STATUS:             Exp
 *
 * AUTHOR:             CJG
 *
 * DESCRIPTION:
 * Provides API for driving LCD panels using UC1601 or UC1606 LCD
 * Driver-Controller.
 *
 * LAST MODIFIED BY:   dclar
 *                     $Modtime: $
 *
 ****************************************************************************
 *
 *  (c) Copyright 2005 JENNIC Ltd
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "Utilities.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vNumToString
 *
 * DESCRIPTION:
 * Converts a 32 bit value to a hexadecimal string.
 *
 * PARAMETERS:  Name      RW  Usage
 *              u32Data   R   Value to convert
 *              pcString  W   Store for string. Must be at least 9 characters
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vUTIL_NumToString(uint32 u32Data, char *pcString)
{
    int    i;
    uint8  u8Nybble;

    for (i = 28; i >= 0; i -= 4)
    {
        u8Nybble = (uint8)((u32Data >> i) & 0x0f);
        u8Nybble += 0x30;
        if (u8Nybble > 0x39)
            u8Nybble += 7;

        *pcString = u8Nybble;
        pcString++;
    }
    *pcString = 0;
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
