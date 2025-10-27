#pragma once
#include "PatternScanners.h"

DWORD64 SCAN(const char* sig, DWORD64 start_address, DWORD64 end_length)
{
    static auto pattern_to_byte = [](const char* pattern)
        {
            auto bytes = std::vector<int>{};
            auto Start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto current = Start; current < end; ++current)
            {
                if (*current == '?')
                {
                    ++current;
                    if (*current == '?')
                        ++current;

                    bytes.push_back(-1);
                }
                else
                    bytes.push_back(strtoul(current, &current, 16));
            }
            return bytes;
        };

    const auto module_handle = GetModuleHandleA(NULL);
    if (!module_handle)
        return {};

    MODULEINFO module_info;
    GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

    DWORD64 image_size = (DWORD64)module_handle + module_info.SizeOfImage;

    auto pattern_bytes = pattern_to_byte(sig);
    const auto image_bytes = reinterpret_cast<byte*>(module_handle);

    const auto signature_size = pattern_bytes.size();
    const auto signature_bytes = pattern_bytes.data();

    auto page_information = MEMORY_BASIC_INFORMATION{};
    for (auto current_page = reinterpret_cast<byte*>(module_handle); current_page < reinterpret_cast<byte*>(image_size); current_page = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(page_information.BaseAddress) + page_information.RegionSize))
    {
        auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

        if (page_information.Protect != PAGE_EXECUTE_READWRITE)
            continue;

        for (auto i = reinterpret_cast<uintptr_t>(page_information.BaseAddress) - reinterpret_cast<uintptr_t>(module_handle); i < page_information.RegionSize; ++i)
        {
            auto byte_sequence_found = true;

            if (end_length != 0) {
                if (DWORD64(&image_bytes[i]) <= start_address)
                    continue;

                if (DWORD64(&image_bytes[i]) >= DWORD64((start_address + end_length)))
                    return 0;
            }

            if (i + signature_size == page_information.RegionSize)
            {
                auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

                if (page_information.Protect != PAGE_EXECUTE_READ)
                    break;
            }

            for (auto j = 0ul; j < signature_size; ++j)
            {
                if (image_bytes[i + j] != signature_bytes[j] && signature_bytes[j] != -1)
                {
                    byte_sequence_found = false;
                    break;
                }
            }

            if (byte_sequence_found) {
                return DWORD64(&image_bytes[i]);
            }
        }
    }
    return 0;
}

DWORD64 RESOLVE(DWORD64 instr, DWORD offset, DWORD instrSize) {
    return instr == 0ui64 ? 0ui64 : (instr + instrSize + *(int*)(instr + offset));
}

void DECODE(DWORD64 addr, ZydisDecodedInstruction* instruction, ZydisDecodedOperand* operands)
{
    static ZydisDecoder decoder;
    if (static bool init = false; !init)
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
        init = true;
    }

    ZydisDecoderDecodeFull(&decoder, (void*)addr, 20, instruction, operands);
}