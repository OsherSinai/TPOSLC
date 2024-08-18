/*
	TPOSLC
	A LibC implementation for TPOS (Testing and Prototyping Operating System).

	Copyright © 2024 by Osher Sinai.

	This file is part of TPOSLC (Testing and Prototyping Operating System LibC).

	TPOSLC is free software:
	you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
	either version 3 of the License, or (at your option) any later version.

	TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with TPOSLC.
	If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef WIN32_PE32_STRUCTURES_H
#define WIN32_PE32_STRUCTURES_H
#include <include\stddef.h>

/*
FYI: this header and gimped pe32 utils exist to get the tls size
No other reason for it here as this library should be somewhat portable to my os.
This library doesnt implement the equivelant of LoadLibrary and FreeLibrary.
This library wont take into account dependencies and prior tls into account for needed tls calculation!
*/
#pragma pack(push, 1)
#define TOS_MSDOS_PE_OFFSET 0x3C

struct COFF_MSDOSStub {
	uint8_t Stub[0x3c];
	uint32_t PEOffset;
};
typedef struct{
	uint8_t signature[4];
	uint16_t Machine;
	uint16_t NumberOfSections;
	uint32_t TimeDateStamp;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint16_t SizeOfOptionalHeader;
	uint16_t Characteristics;
} COFF_Header;

#define PE32_OPTIONAL_HEADER_MAGIC_PE32 (0x10b)
#define PE32_OPTIONAL_HEADER_MAGIC_PE32P (0x20b)

typedef struct {
	uint32_t   VirtualAddress;
	uint32_t   Size;
} IMAGE_DATA_DIRECTORY;


typedef union {
	struct {
		IMAGE_DATA_DIRECTORY ExportTable;
		IMAGE_DATA_DIRECTORY ImportTable;
		IMAGE_DATA_DIRECTORY ResourceTable;
		IMAGE_DATA_DIRECTORY ExceptionTable;
		IMAGE_DATA_DIRECTORY CertificateTable;
		IMAGE_DATA_DIRECTORY BaseRelocationTable;
		IMAGE_DATA_DIRECTORY Debug;
		IMAGE_DATA_DIRECTORY Architecture;
		IMAGE_DATA_DIRECTORY GlobalPtr;
		IMAGE_DATA_DIRECTORY TLSTable;
		IMAGE_DATA_DIRECTORY LoadConfigTable;
		IMAGE_DATA_DIRECTORY BoundImport;
		IMAGE_DATA_DIRECTORY IAT;
		IMAGE_DATA_DIRECTORY DelayImportDescriptor;
		IMAGE_DATA_DIRECTORY CLRRuntimeHeader;
		IMAGE_DATA_DIRECTORY Reserved;
	};
	IMAGE_DATA_DIRECTORY array[16];
}PE32_Optional_Header_Data_Directories;

typedef struct {
	uint8_t Name[8];
	uint32_t VirtualSize;
	uint32_t VirtualAddress;
	uint32_t SizeOfRawData;
	uint32_t PointerToRawData;
	uint32_t PointerToRelocation;
	uint32_t PointerToLineNumbers;
	uint16_t NumberOfRelocations;
	uint16_t NumberOfLinenumbers;
	uint32_t Characteristics;
}PE32_Image_Section_Header;

typedef struct {
	uint8_t MajorLinkerVersion;
	uint8_t MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint32_t BaseOfData;

	uint32_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint32_t SizeOfStackReserve;
	uint32_t SizeOfStackCommit;
	uint32_t SizeOfHeapReserve;
	uint32_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;

	PE32_Optional_Header_Data_Directories Directories;
}PE32_Optional_Header;
typedef struct {
	uint8_t MajorLinkerVersion;
	uint8_t MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;

	uint64_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint64_t SizeOfStackReserve;
	uint64_t SizeOfStackCommit;
	uint64_t SizeOfHeapReserve;
	uint64_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;

	PE32_Optional_Header_Data_Directories Directories;
}PE32P_Optional_Header;
#pragma pack(pop)
#endif // !WIN32_PE32_STRUCTURES_H
