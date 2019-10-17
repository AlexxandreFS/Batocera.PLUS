/******************************************************************************/
/*                                                                            */
/*                    CATALYST 93C46 1K-BIT SERIAL EEPROM                     */
/*                                                                            */
/******************************************************************************/

#include "cat93c46.h"
#include "debug.h"

#define EPR_WAIT_START		0
#define EPR_READ_OPCODE		1
#define EPR_READ_OPCODE_EXT	2
#define EPR_INST_READ		3
#define EPR_INST_READ_2		4
#define EPR_INST_ERASE		5
#define EPR_INST_WRITE		6

static UINT32 eeprom_read;

UINT16 *eeprom_data;

UINT8 eeprom_93c46_rb(void)
{
   UINT8 ret;

   ret = eeprom_read;

   eeprom_read = 1;

   return ret;
}

UINT8 eeprom_93c46_rb_cave(void)
{
   return eeprom_read;
}

void eeprom_93c46_wb(UINT8 data)
{
   static UINT32 eeprom_input;
   static UINT32 eeprom_state;
   static UINT32 eeprom_count;
   static UINT32 eeprom_address;
   static UINT32 eeprom_output;

   switch(eeprom_state){
      case EPR_WAIT_START:
         if(data){
            eeprom_state = EPR_READ_OPCODE;
            eeprom_input = 0;
            eeprom_count = 0;
         }
      break;
      case EPR_READ_OPCODE:
            eeprom_input <<= 1;
            eeprom_input  |= data;

            eeprom_count ++;

            if(eeprom_count == 2){
               switch(eeprom_input){
                  case 0:
                     eeprom_state = EPR_READ_OPCODE_EXT;
                     eeprom_input = 0;
                     eeprom_count = 0;
                  break;
                  case 1:
                     eeprom_state = EPR_INST_WRITE;
                     eeprom_input = 0;
                     eeprom_count = 0;
                  break;
                  case 2:
                     eeprom_state = EPR_INST_READ;
                     eeprom_input = 0;
                     eeprom_count = 0;
                  break;
                  case 3:
                     eeprom_state = EPR_INST_ERASE;
                     eeprom_input = 0;
                     eeprom_count = 0;
                  break;
               }
            }
      break;
      case EPR_READ_OPCODE_EXT:
            eeprom_input <<= 1;
            eeprom_input  |= data;

            eeprom_count ++;

            if(eeprom_count == 6){
               switch(eeprom_input>>4){
                  case 0:
                     eeprom_state = EPR_WAIT_START;
                        print_debug("eeprom write disable...\n");
                  break;
                  case 1:
                     eeprom_state = EPR_WAIT_START;
                        print_debug("eeprom write all addresses...\n");
                  break;
                  case 2:
                     eeprom_state = EPR_WAIT_START;
                        print_debug("eeprom clear all addresses...\n");
                  break;
                  case 3:
                     eeprom_state = EPR_WAIT_START;
                        print_debug("eeprom write enable...\n");
                  break;
               }
            }
      break;
      case EPR_INST_READ:
            eeprom_input <<= 1;
            eeprom_input  |= data;

            eeprom_count ++;

            if(eeprom_count == 6){
                eeprom_address = eeprom_input & 0x3F;
                eeprom_output = eeprom_data[eeprom_address];
                eeprom_state = EPR_INST_READ_2;
                eeprom_count = 0;

                   print_debug("eeprom read(%02x,%04x)\n",eeprom_address,eeprom_data[eeprom_address]);
            }
      break;
      case EPR_INST_READ_2:
            eeprom_read = (eeprom_output >> 15) & 1;

            eeprom_output <<= 1;

            eeprom_count ++;

            if(eeprom_count == 16){
                eeprom_state = 0;
            }
      break;
      case EPR_INST_WRITE:
            eeprom_input <<= 1;
            eeprom_input  |= data;

            eeprom_count ++;

            if(eeprom_count == (6 + 16)){
                eeprom_address = (eeprom_input>>16) & 0x3F;
                eeprom_data[eeprom_address] = eeprom_input & 0xFFFF;
                eeprom_state = 0;
                eeprom_count = 0;

                   print_debug("eeprom write(%02x,%04x)\n",eeprom_address,eeprom_data[eeprom_address]);
            }
      break;
      case EPR_INST_ERASE:
            eeprom_input <<= 1;
            eeprom_input  |= data;

            eeprom_count ++;

            if(eeprom_count == 6){
                eeprom_address = eeprom_input & 0x3F;
                eeprom_data[eeprom_address] = 0x0000;
                eeprom_state = 0;
                eeprom_count = 0;
            }
      break;
   }
}
