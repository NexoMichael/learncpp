#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <set>

#include "mz.hpp"
#include "log.hpp"

#define MAGIC_MZ (('Z' << 8) | 'M')

template <typename T>
std::string hex(T i)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}
std::string hex(uint8_t i)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(uint8_t) * 2) << std::hex << uint32_t(i);
    return stream.str();
}

struct FileNotFoundException : public std::exception
{
    const char *what() const throw()
    {
        return "File is not found";
    }
};

class FileReader
{
  private:
    std::ifstream m_inStream;
    uint32_t m_offset;
    uint32_t m_fileSize;

  public:
    FileReader(const std::string &filePath) : m_offset(0)
    {
        log(LogLevel::Debug) << "load " << filePath << "\n";
        m_inStream = std::ifstream(filePath, std::ios::in | std::ios::binary);

        if (!m_inStream.good())
            throw FileNotFoundException{};

        m_inStream.seekg(0, m_inStream.end);
        m_fileSize = m_inStream.tellg();
        m_inStream.seekg(0, m_inStream.beg);
    }

    ~FileReader()
    {
        if (m_inStream)
        {
            log(LogLevel::Debug) << "close opened file stream\n";
            m_inStream.close();
        }
    }

    uint32_t offset()
    {
        return m_inStream.tellg();
    }

    uint32_t size()
    {

        return m_fileSize;
    }

    void seek(uint32_t pos)
    {
        m_inStream.seekg(pos, m_inStream.beg);
    }

    uint8_t byte()
    {
        uint8_t v = m_inStream.get();
        // log(LogLevel::Debug) << "[" << hex(m_offset) << "] read byte: " << hex(v) << "\n";
        m_offset++;
        return v;
    }

    void bytes(uint8_t *buf, uint32_t n)
    {
        for (uint32_t i = 0; i < n; i++)
        {
            buf[i] = m_inStream.get();
        }
        // log(LogLevel::Debug) << "read " << n << " bytes\n";
    }

    uint16_t word()
    {
        uint16_t v;
        uint8_t c1 = m_inStream.get();
        uint8_t c2 = m_inStream.get();
        v = (c2 << 8) | c1;
        // log(LogLevel::Debug) << "[" << hex(m_offset) << "] read word: " << hex(v) << "\n";
        m_offset += 2;
        return v;
    }

    uint16_t word2()
    {
        uint16_t v;
        uint8_t c1 = m_inStream.get();
        uint8_t c2 = m_inStream.get();
        v = (c1 << 8) | c2;
        // log(LogLevel::Debug) << "[" << hex(m_offset) << "] read word: " << hex(v) << "\n";
        m_offset += 2;
        return v;
    }

    uint32_t dword()
    {
        uint32_t v;
        auto c1 = word();
        auto c2 = word();
        v = (uint32_t)((c1 << 16) | c2);
        // log(LogLevel::Debug) << "read dword: " << hex(v) << "\n";
        return v;
    }
};

MZ::~MZ()
{
    if (m_image)
    {
        log(LogLevel::Debug) << "drop image from memory\n";
        delete[] m_image;
    }
    if (m_relocationEntriesList)
    {
        log(LogLevel::Debug) << "drop relocation entries list from memory\n";
        delete[] m_relocationEntriesList;
    }
}

uint16_t MZ::memory_word(uint32_t i)
{
    return (m_image[i] << 8) | m_image[i + 1];
}

uint16_t MZ::memory_beword(uint32_t i)
{
    return (m_image[i + 1] << 8) | m_image[i];
}

uint8_t MZ::memory_byte(uint32_t i)
{
    return m_image[i];
}

int8_t MZ::memory_signedbyte(uint32_t i)
{
    return (int8_t)m_image[i];
}

void MZ::set_memory_word(uint32_t i, uint16_t value)
{
    m_image[i + 1] = value & 0xFF;
    m_image[i] = value >> 8;
}

bool MZ::load_file(const std::string &filePath)
{
    FileReader reader = FileReader(filePath);

    if (reader.word() != MAGIC_MZ)
        return false;

    m_lastPageBytes = reader.word();
    m_pages = reader.word();
    m_relocationEntries = reader.word();
    m_headerSize = reader.word();
    m_minMemoryAllocated = reader.word();
    m_maxMemoryAllocated = reader.word();
    m_initialSS = reader.word();
    m_initialSP = reader.word();
    m_checksum = reader.word();
    m_initialCSIP = reader.dword();
    m_relocationTableOffset = reader.word();
    m_overlayNumber = reader.word();
    for (int i = 0; i < 4; i++)
        m_reserved[i] = reader.word();
    m_oemIdentifier = reader.word();
    m_oemInformation = reader.word();
    for (int i = 0; i < 4; i++)
        m_reserved2[i] = reader.word();
    m_newExeHeaderAddress = reader.word();

    if (m_pages & ~0x07ff)
    {
        log(LogLevel::Error) << "weird header size (> 1 MB)";
    }
    m_pages &= 0x07ff;

    m_headerSizeBytes = m_headerSize * PARAGRAPH_SIZE;
    m_imageSizeBytes = (m_pages - 1) * 512 + m_lastPageBytes - m_headerSizeBytes;

    std::cout << "physical file size: " << reader.size() << "\n";
    std::cout << "file size: " << m_headerSizeBytes + m_imageSizeBytes << " header size: " << m_headerSizeBytes << " image size: " << m_imageSizeBytes << "\n";

    if (reader.size() != m_headerSizeBytes + m_imageSizeBytes)
    {
        log(LogLevel::Error) << "physical file size is not equal to computed one\n";
        return false;
    }
    // TBD: check for COM file

    // uint32_t minsize = m_imageSizeBytes + m_minMemoryAllocated * PARAGRAPH_SIZE;
    // uint32_t maxsize = 0xffff0; // 1 MB
    // if (m_maxMemoryAllocated > 0)
    //     maxsize = m_imageSizeBytes + m_maxMemoryAllocated * PARAGRAPH_SIZE;
    // if (maxsize > 0xffff0)
    //     maxsize = 0xffff0;

    reader.seek(m_headerSizeBytes);
    m_image = new uint8_t[m_imageSizeBytes];
    reader.bytes(m_image, m_imageSizeBytes);

    reader.seek(m_relocationTableOffset);

    uint16_t start_address = 0x010;

    m_relocationEntriesList = new uint16_t[m_relocationEntries];
    for (int i = 0; i < m_relocationEntries; i++)
    {
        uint16_t offset = reader.word();
        uint16_t segmentOffset = reader.word() * 0x0010;
        uint16_t address = offset + segmentOffset;
        m_relocationEntriesList[i] = address;
        set_memory_word(address, memory_word(address) + start_address);
    }

    std::cout << hex(memory_word(m_relocationEntriesList[0])) << "\n";

    log(LogLevel::Debug)
        << "skip header: " << hex(m_headerSizeBytes) << " bytes \n";

    // for (int i = 0; i < 2; i++)
    // {
    //     std::cout << "[" << std::dec << m_relocationEntriesList[i] << " - " << m_relocationEntriesList[i + 1] << "] ";
    //     for (int j = m_relocationEntriesList[i]; j < m_relocationEntriesList[i + 1]; j++)
    //     {
    //         std::cout << std::hex << uint32_t(m_image[j]) << " ";
    //     }
    //     std::cout << "\n";2
    // }

    return true;
}

void MZ::parse_opcodes()
{
    std::cout << "\n\n\n";

    uint32_t pos = 0;
    while (pos < m_imageSizeBytes)
    {
        std::cout << hex(pos) << "\t";
        uint16_t opcode = memory_byte(pos++);

        uint8_t op_8;
        uint8_t op_8_2;
        uint16_t op_16;
        int8_t op_8int;

        switch (opcode)
        {
        case 0x2e:
            std::cout << " -> cs\n";
            break;
        case 0x26:
            std::cout << " -> es\n";
            break;
        case 0x38:
            op_8 = memory_byte(pos++);
            switch (op_8)
            {
            case 0x05:
                std::cout << "mov :[di], al\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x38 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0x43:
            std::cout << "inc bx\n";
            break;
        case 0x75:
            op_8int = memory_signedbyte(pos++);
            op_8 = (uint8_t)((int)pos + (int)op_8int);
            std::cout << "jnz " << hex(op_8) << "\n";
            break;
        case 0x80:
            op_8 = memory_byte(pos++);
            op_8_2 = memory_byte(pos++);

            switch (op_8)
            {
            case 0xcd:
                std::cout << "or ch, " << hex(op_8_2) << "\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x80 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0x83:
            op_8 = memory_byte(pos++);

            switch (op_8)
            {
            case 0xc3:
                op_8 = memory_byte(pos++);
                std::cout << "add bx, " << hex(op_8) << "\n";
                break;
            case 0xe3:
                op_8 = memory_byte(pos++);
                op_16 = 0xff00 | op_8;
                std::cout << "and bx, " << hex(op_16) << "\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x83 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;

            break;
        case 0x89:
            op_8 = memory_byte(pos++);
            op_16 = memory_beword(pos);
            pos += 2;

            switch (op_8)
            {
            case 0x16:
                std::cout << "mov " << hex(op_16) << ", dx\n";
                break;
            case 0x0e:
                std::cout << "mov " << hex(op_16) << ", cx\n";
                break;
            case 0x1e:
                std::cout << "mov " << hex(op_16) << ", bx\n";
                break;
            case 0x2e:
                std::cout << "mov " << hex(op_16) << ", bp\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x89 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0x8b:
            op_8 = memory_byte(pos++);

            switch (op_8)
            {
            case 0x1e:
                op_16 = memory_beword(pos);
                pos += 2;
                std::cout << "mov bp, " << hex(op_16) << "\n";
                break;
            case 0x2e:
                op_16 = memory_beword(pos);
                pos += 2;
                std::cout << "mov bx, " << hex(op_16) << "\n";
                break;
            case 0xc7:
                std::cout << "mov ax, di\n";
                break;
            case 0xd8:
                std::cout << "mov bx, ax\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x8b opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0x8c:
            op_8 = memory_byte(pos++);

            switch (op_8)
            {
            case 0x06:
                op_16 = memory_beword(pos);
                pos += 2;
                std::cout << "mov " << hex(op_16) << ", es\n";
                break;
            case 0xd2:
                std::cout << "mov dx, ss\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x8c opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0x8e:
            op_8 = memory_byte(pos++);
            switch (op_8)
            {
            case 0xda:
                std::cout << "mov ds, dx\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0x8e opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0xb4:
            op_8 = memory_byte(pos++);
            std::cout << "mov ah, [ds:" << hex(op_8) << "]\n";
            break;
        case 0xb9:
            op_16 = memory_beword(pos);
            pos += 2;
            std::cout << "mov cx, " << hex(op_16) << "\n";
            break;

        case 0xa3:
            op_16 = memory_beword(pos);
            pos += 2;
            std::cout << "mov [ds:" << hex(op_16) << "], ax\n";
            break;
        case 0xba:
            op_16 = memory_beword(pos);
            pos += 2;
            std::cout << "mov dx, [ds:" << hex(op_16) << "]\n";
            break;
        case 0xc4:
            op_8 = memory_byte(pos++);
            op_16 = memory_beword(pos);
            pos += 2;

            switch (op_8)
            {
            case 0x3e:
                std::cout << "les di, " << hex(op_16) << "\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0xc4 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0xcd:
            op_8 = memory_byte(pos++);
            std::cout << "int " << hex(op_8) << "\n";
            break;
        case 0xd3:
            op_8 = memory_byte(pos++);
            switch (op_8)
            {
            case 0xe3:
                std::cout << "shl bx, cl\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0xc4 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0xe3:
            op_8 = memory_byte(pos++);
            op_8 += pos;
            std::cout << "jcxz " << hex(op_8) << "\n";
            break;
        case 0xe8:
            op_16 = memory_beword(pos);
            pos += 2;
            op_16 += pos;
            std::cout << "call " << hex(op_16) << "\n";
            break;
        case 0xf2:
            op_8 = memory_byte(pos++);
            switch (op_8)
            {
            case 0xae:
                std::cout << "repne scasb\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0xf2 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0xf7:
            op_8 = memory_byte(pos++);
            switch (op_8)
            {
            case 0xd9:
                std::cout << "neg cx\n";
                break;
            default:
                std::cout << "\n\n\nUnknown for 0xf7 opcode :" << hex(op_8) << "\n\n\n\n";
                return;
            }
            break;
        case 0xfc:
            std::cout << "cld\n";
            break;
        default:
            std::cout << "\n\n\nUnknown opcode :" << hex(opcode) << "\n\n\n\n";
            return;
        }
    }
}

void MZ::debug_dump()
{
    std::cout << "Pages: " << m_pages << " last page size: " << m_lastPageBytes << "\n";
    std::cout << "Header size: " << m_headerSize << "\n";
    std::cout << "Relocation entries: " << m_relocationEntries << " offset: " << hex(m_relocationTableOffset) << "\n";
    std::cout << "Min memory: " << m_minMemoryAllocated << " max memory: " << m_maxMemoryAllocated << "\n";
    std::cout << " SS: " << hex(m_initialSS)
              << " SP: " << hex(m_initialSP)
              << " CS:IP: " << hex((uint16_t)(m_initialCSIP & 0xFF00)) << ":" << hex((uint16_t)(m_initialCSIP & 0x00FF)) << "\n";
    std::cout << "Checksum: " << m_checksum << "\n";
    std::cout << "Overlay: " << m_overlayNumber << "\n";
}