#pragma once

#include <string>
#include <set>

#define PARAGRAPH_SIZE 16;
#define PROGRAM_SEGMENT_PREFIX 0x0100h
#define MSDOS_PAGE_SIZE 0x0200h;

struct relocationEntry
{
  uint16_t offset;
};

class MZ
{
private:
  uint16_t m_lastPageBytes;         // 0002h  1 word   Number of bytes in last 512-byte page of executable
  uint16_t m_pages;                 // 0004h  1 word   Total number of 512-byte pages in executable (including the last page)
  uint16_t m_relocationEntries;     // 0006h  1 word   Number of relocation entries
  uint16_t m_headerSize;            // 0008h  1 word   Header size in paragraphs
  uint16_t m_minMemoryAllocated;    // 000Ah  1 word   Minimum paragraphs of memory allocated in addition to the code size
  uint16_t m_maxMemoryAllocated;    // 000Ch  1 word   Maximum number of paragraphs allocated in addition to the code size
  uint16_t m_initialSS;             // 000Eh  1 word   Initial SS relative to start of executable
  uint16_t m_initialSP;             // 0010h  1 word   Initial SP
  uint16_t m_checksum;              // 0012h  1 word   Checksum(or 0) of executable
  uint32_t m_initialCSIP;           // 0014h  1 dword  CS : IP relative to start of executable(entry point)
  uint16_t m_relocationTableOffset; // 0018h  1 word   Offset of relocation table;
                                    //                   40h for new-(NE,LE,LX,W3,PE etc.) executable
  uint16_t m_overlayNumber;         // 001Ah  1 word   Overlay number (0h = main program)
  uint16_t m_reserved[4];           // 001Ch  4 words  Reserved words  (TBD find doc)
  uint16_t m_oemIdentifier;         // 0024h  1 word   OEM Identifier  (TBD find doc)
  uint16_t m_oemInformation;        // 0026h  1 word   OEM Information, specific for m_oemIdentifier  (TBD find doc)
  uint16_t m_reserved2[4];          // 0028h  4 words  Reserved words  (TBD find doc)
  uint32_t m_newExeHeaderAddress;   // 003Ch  1 dword  File address of new exe header  (TBD find doc)

  uint32_t m_headerSizeBytes;
  uint32_t m_imageSizeBytes;

  uint8_t *m_image;
  uint16_t *m_relocationEntriesList;

public:
  MZ() : m_lastPageBytes(0),
         m_pages(0),
         m_relocationEntries(0),
         m_headerSize(0),
         m_minMemoryAllocated(0),
         m_maxMemoryAllocated(0),
         m_initialSS(0),
         m_initialSP(0),
         m_checksum(0),
         m_initialCSIP(0),
         m_relocationTableOffset(0),
         m_overlayNumber(0)
  {
  }
  ~MZ();

  bool load_file(const std::string &file_path);

  void parse_opcodes();

  void debug_dump();

  uint16_t memory_beword(uint32_t i);
  uint16_t memory_word(uint32_t i);
  uint8_t memory_byte(uint32_t i);
  int8_t memory_signedbyte(uint32_t i);

  void set_memory_word(uint32_t i, uint16_t value);
};
