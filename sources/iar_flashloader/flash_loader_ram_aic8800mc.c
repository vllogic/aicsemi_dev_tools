//------------------------------------------------------------------------------
//
// Copyright (c) 2008-2015 IAR Systems
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// $Revision: 38381 $
//
//------------------------------------------------------------------------------

#include "flash_loader.h"
#include "flash_loader_extra.h"

void strcopy(char *to, char* from);


#define ROM_APITBL_BASE             ((unsigned int *)0x00000164UL)

#define ROM_FlashChipIdGet          ((unsigned int (*)(void)) \
                                     ROM_APITBL_BASE[10])
#define ROM_FlashChipSizeGet        ((unsigned int (*)(void)) \
                                     ROM_APITBL_BASE[11])
#define ROM_FlashChipErase          ((void (*)(void)) \
                                     ROM_APITBL_BASE[12])
#define ROM_FlashErase              ((int (*)(unsigned int a4k, unsigned int len)) \
                                     ROM_APITBL_BASE[13])
#define ROM_FlashWrite              ((int (*)(unsigned int adr, unsigned int len, unsigned int buf)) \
                                     ROM_APITBL_BASE[14])
#define ROM_FlashRead               ((int (*)(unsigned int adr, unsigned int len, unsigned int buf)) \
                                     ROM_APITBL_BASE[15])
#define ROM_FlashCacheInvalidAll    ((void (*)(void)) \
                                     ROM_APITBL_BASE[16])
#define ROM_FlashCacheInvalidRange  ((void (*)(unsigned int adr, unsigned int len)) \
                                     ROM_APITBL_BASE[17])

uint32_t FlashInit(void *base_of_flash, uint32_t image_size,
                   uint32_t link_address, uint32_t flags,
                   int argc, char const *argv[])
{
//  strcopy(LAYOUT_OVERRIDE_BUFFER,"2 0x100,7 0x200,7 0x1000");
//  SET_BUFSIZE_OVERRIDE(&FlashBufferEnd-&FlashBufferStart+1);
//  SET_PAGESIZE_OVERRIDE(128);
//  return OVERRIDE_LAYOUT | OVERRIDE_BUFEND | OVERRIDE_PAGESIZE;
//  if (flags & FLAG_ERASE_ONLY)
//  {
//    perform full erase
//    return RESULT_ERASE_DONE;
//  }
    return RESULT_OK;
}

uint32_t FlashWrite(void *block_start,
                    uint32_t offset_into_block,
                    uint32_t count,
                    char const *buffer)
{
    unsigned int adr;
    unsigned int len;
    unsigned int buf;
    adr = (uint32_t)block_start + offset_into_block;
    len = count;
    buf = (uint32_t)buffer;
    ROM_FlashWrite(adr, len, buf);
    ROM_FlashCacheInvalidRange((uint32_t)adr, len);
    return 0;
}

uint32_t FlashErase(void *block_start,
                    uint32_t block_size)
{
    ROM_FlashErase((uint32_t)block_start, block_size);
    ROM_FlashCacheInvalidRange((uint32_t)block_start, block_size);
    return 0;
}

OPTIONAL_CHECKSUM
uint32_t FlashChecksum(void const *begin, uint32_t count)
{
  return Crc16((uint8_t const *)begin, count);
}

OPTIONAL_SIGNOFF
uint32_t FlashSignoff(void)
{
  return 0;
}

void strcopy(char *to, char* from)
{
  while (*to++ = *from++) ;
}

