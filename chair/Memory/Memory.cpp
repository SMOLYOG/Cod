#pragma once
#include "Memory.h"

namespace Memory {
    uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t Start, uintptr_t size, const char* sig, const char* mask)
    {
        BYTE* data = new BYTE[size];
        SIZE_T bytesRead;

        ReadProcessMemory(hProcess, (LPVOID)Start, data, size, &bytesRead);

        for (uintptr_t i = 0; i < size; i++)
        {
            if (MemCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
                return Start + i;
            }
        }
        delete[] data;
        return NULL;
    }

    bool MemCompare(const BYTE* bData, const BYTE* bMask, const char* szMask) {
        for (; *szMask; ++szMask, ++bData, ++bMask) {
            if (*szMask == 'x' && *bData != *bMask) {
                return false;
            }
        }
        return (*szMask == NULL);
    }

    DWORD GetProcId(LPCSTR procName)
    {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32 procEntry;
            procEntry.dwSize = sizeof(procEntry);

            if (Process32First(hSnap, &procEntry))
            {
                do
                {
                    if (!_stricmp(procEntry.szExeFile, procName))
                    {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;
    }

   shared::address_t find_ida_sig(const char* mod, const char* sig)
    {
        /// Credits: MarkHC, although slightly modified by me and also documented

        static auto pattern_to_byte = [](const char* pattern)
            {
                /// Prerequisites
                auto bytes = std::vector<int>{};
                auto start = const_cast<char*>(pattern);
                auto end = const_cast<char*>(pattern) + strlen(pattern);

                /// Convert signature into corresponding bytes
                for (auto current = start; current < end; ++current)
                {
                    /// Is current byte a wildcard? Simply ignore that that byte later
                    if (*current == '?')
                    {
                        ++current;

                        /// Check if following byte is also a wildcard
                        if (*current == '?')
                            ++current;

                        /// Dummy byte
                        bytes.push_back(-1);
                    }
                    else
                    {
                        /// Convert character to byte on hexadecimal base
                        bytes.push_back(strtoul(current, &current, 16));
                    }
                }
                return bytes;
            };

        const auto module_handle = GetModuleHandleA(mod);
        if (!module_handle)
            return {};

        /// Get module information to search in the given module
        MODULEINFO module_info;
        GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

        /// The region where we will search for the byte sequence
        const auto image_size = module_info.SizeOfImage;

        /// Check if the image is faulty
        if (!image_size)
            return {};

        /// Convert IDA-Style signature to a byte sequence
        auto pattern_bytes = pattern_to_byte(sig);

        const auto image_bytes = reinterpret_cast<byte*>(module_handle);

        const auto signature_size = pattern_bytes.size();
        const auto signature_bytes = pattern_bytes.data();

        /// Loop through all pages and check the accessable pages
        auto page_information = MEMORY_BASIC_INFORMATION{};
        for (auto current_page = reinterpret_cast<byte*>(module_handle); current_page < reinterpret_cast<byte*>(module_handle + image_size); current_page = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(page_information.BaseAddress) + page_information.RegionSize))
        {
            auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

            if (page_information.Protect != PAGE_EXECUTE_READWRITE)
                continue;

            /// Now loop through all bytes and check if the byte sequence matches
            for (auto i = reinterpret_cast<uintptr_t>(page_information.BaseAddress) - reinterpret_cast<uintptr_t>(module_handle); i < page_information.RegionSize; ++i)
            {
                auto byte_sequence_found = true;

                if (i + signature_size == page_information.RegionSize)
                {
                    auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

                    if (page_information.Protect != PAGE_EXECUTE_READ)
                        break;
                }

                /// Go through all bytes from the signature and check if it matches
                for (auto j = 0ul; j < signature_size; ++j)
                {
                    if (image_bytes[i + j] != signature_bytes[j] /// Bytes don't match
                        && signature_bytes[j] != -1) /// Byte isn't a wildcard either, WHAT THE HECK
                    {
                        byte_sequence_found = false;
                        break;
                    }
                }

                if (byte_sequence_found)

                /// All good, now return the right address
                if (byte_sequence_found)
                    return shared::address_t(uintptr_t(&image_bytes[i]));
            }
        }
        /// Byte sequence wasn't found
        return {};
    }


};