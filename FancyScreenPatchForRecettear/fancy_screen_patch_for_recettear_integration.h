
/* SPDX-LICENSE-IDENTIFIER: BSL-1.0 */

/*
	Copyright Harry Gillanders 2024-2024.
	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef FancyScreenPatchForRecettearOldestVersion
#define FancyScreenPatchForRecettearOldestVersion 1
#endif

#ifndef FancyScreenPatchForRecettearNewestVersion
#define FancyScreenPatchForRecettearNewestVersion 5
#endif

#ifdef FancyScreenPatchForRecettearTargetVersion

#if FancyScreenPatchForRecettearTargetVersion > FancyScreenPatchForRecettearNewestVersion
#error `FancyScreenPatchForRecettearTargetVersion` must be no-more-than `FancyScreenPatchForRecettearNewestVersion`.
#endif

#if FancyScreenPatchForRecettearTargetVersion < FancyScreenPatchForRecettearOldestVersion
#error `FancyScreenPatchForRecettearTargetVersion` must be no-more-than `FancyScreenPatchForRecettearOldestVersion`.
#endif

#ifndef FancyScreenPatchForRecettearIntegration
#define FancyScreenPatchForRecettearIntegration

#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

#ifndef FancyScreenPatchForRecettearPrefix
#define FancyScreenPatchForRecettearPrefix FSP_
#endif

#define FancyScreenPatchForRecettearMacroConcatenateInternal(a, b) a ## b
#define FancyScreenPatchForRecettearMacroConcatenate(a, b) FancyScreenPatchForRecettearMacroConcatenateInternal(a, b)

#define FancyScreenPatchForRecettearSymbol(symbol) FancyScreenPatchForRecettearMacroConcatenate(FancyScreenPatchForRecettearPrefix, symbol)


static const void *FancyScreenPatchForRecettearSymbol(getAddressOfRecettearExecutable)(void)
{
	/* The value of an HMODULE is just the base address of the module,
	   as per the documentation of the `hinstDLL` parameter of `DllMain`:
	   https://learn.microsoft.com/windows/win32/dlls/dllmain#parameters */
	return GetModuleHandleW(NULL);
}


/* A UTF-8 code-unit. */
typedef uint8_t FancyScreenPatchForRecettearSymbol(Char);


/* A UTF-8 string. */
typedef struct
{
	FancyScreenPatchForRecettearSymbol(Char) *start;
	uint32_t length;
} FancyScreenPatchForRecettearSymbol(String);


#if FancyScreenPatchForRecettearTargetVersion >= 5
typedef void (*FancyScreenPatchForRecettearSymbol(StartDisablingLeftPillarbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StartDisablingRightPillarbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StartDisablingUpperLetterbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StartDisablingLowerLetterbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StopDisablingLeftPillarbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StopDisablingRightPillarbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StopDisablingUpperLetterbox)) (void);
typedef void (*FancyScreenPatchForRecettearSymbol(StopDisablingLowerLetterbox)) (void);


typedef struct
{
	FancyScreenPatchForRecettearSymbol(StartDisablingLeftPillarbox) startDisablingLeftPillarbox;
	FancyScreenPatchForRecettearSymbol(StartDisablingRightPillarbox) startDisablingRightPillarbox;
	FancyScreenPatchForRecettearSymbol(StartDisablingUpperLetterbox) startDisablingUpperLetterbox;
	FancyScreenPatchForRecettearSymbol(StartDisablingLowerLetterbox) startDisablingLowerLetterbox;
	FancyScreenPatchForRecettearSymbol(StopDisablingLeftPillarbox) stopDisablingLeftPillarbox;
	FancyScreenPatchForRecettearSymbol(StopDisablingRightPillarbox) stopDisablingRightPillarbox;
	FancyScreenPatchForRecettearSymbol(StopDisablingUpperLetterbox) stopDisablingUpperLetterbox;
	FancyScreenPatchForRecettearSymbol(StopDisablingLowerLetterbox) stopDisablingLowerLetterbox;
} FancyScreenPatchForRecettearSymbol(Functions);


typedef struct
{
	uint32_t length;
	FancyScreenPatchForRecettearSymbol(Functions) *functions;
	FancyScreenPatchForRecettearSymbol(String) *names;
} FancyScreenPatchForRecettearSymbol(FunctionTable);
#endif


typedef struct
{
	FancyScreenPatchForRecettearSymbol(Char) magic[16];
	uint32_t version;
#if FancyScreenPatchForRecettearTargetVersion >= 5
	const FancyScreenPatchForRecettearSymbol(FunctionTable) *functionTable;
#endif
} FancyScreenPatchForRecettearSymbol(DataHeader);


typedef struct
{
	const void *code;
	const FancyScreenPatchForRecettearSymbol(DataHeader) *data;
} FancyScreenPatchForRecettearSymbol(Addresses);


typedef struct
{
	const IMAGE_DOS_HEADER *baseAddress;
	const IMAGE_SECTION_HEADER *codeSection;
	const IMAGE_SECTION_HEADER *dataSection;
} FancyScreenPatchForRecettearSymbol(Sections);


static FancyScreenPatchForRecettearSymbol(Sections) FancyScreenPatchForRecettearSymbol(findSections)(const void *addressOfExecutable)
{
	const IMAGE_DOS_HEADER *dosStub = (const IMAGE_DOS_HEADER *) addressOfExecutable;
	const IMAGE_NT_HEADERS32 *exe = (const IMAGE_NT_HEADERS32 *) ((uintptr_t) addressOfExecutable + dosStub->e_lfanew);

	const IMAGE_SECTION_HEADER *sectionTable = (const IMAGE_SECTION_HEADER *) ((uintptr_t) &exe->OptionalHeader + exe->FileHeader.SizeOfOptionalHeader);
	const IMAGE_SECTION_HEADER *endOfSectionTable = sectionTable + exe->FileHeader.NumberOfSections;

	FancyScreenPatchForRecettearSymbol(Sections) found = {0};

	for (const IMAGE_SECTION_HEADER *section = sectionTable; section < endOfSectionTable; ++section)
	{
		if (!found.codeSection)
		{
			const BYTE *n = section->Name;

			if (
				   (section->Characteristics & (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_READ)) == (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_READ)
				&& ((n[0] == 'R') & (n[1] == 'e') & (n[2] == 'c') & (n[3] == 'e') & (n[4] == 't') & (n[5] == 'M') & (n[6] == 'o') & (n[7] == 'd'))
			)
			{
				found.codeSection = section;
				continue;
			}
		}

		if (!found.dataSection)
		{
			const BYTE *n = section->Name;

			if (
				   (section->Characteristics & (IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ)) == (IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ)
				&& ((n[0] == 'T') & (n[1] == 'e') & (n[2] == 'a') & (n[3] == 'r') & (n[4] == 'M') & (n[5] == 'o') & (n[6] == 'd') & (n[7] == '\0'))
			)
			{
				found.dataSection = section;
				continue;
			}
		}

		if (found.codeSection && found.dataSection)
		{
			goto foundAllSections;
		}
	}

	if (found.codeSection && found.dataSection)
	{
	foundAllSections:
		found.baseAddress = dosStub;
	}

	return found;
}


static FancyScreenPatchForRecettearSymbol(Addresses) FancyScreenPatchForRecettearSymbol(verifySectionsAndGetAddresses)(FancyScreenPatchForRecettearSymbol(Sections) sections)
{
	if (sections.codeSection && sections.dataSection && sections.dataSection->Misc.VirtualSize >= 20)
	{
		const FancyScreenPatchForRecettearSymbol(DataHeader) *header = (const FancyScreenPatchForRecettearSymbol(DataHeader) *) (
			(uintptr_t) sections.baseAddress + sections.dataSection->VirtualAddress
		);
		const FancyScreenPatchForRecettearSymbol(Char) *m = header->magic;

		if (
			  (m[0] == 'F') & (m[1] == 'a') & (m[2] == 'n') & (m[3] == 'c') & (m[4] == 'y')
			& (m[5] == 'S') & (m[6] == 'c') & (m[7] == 'r') & (m[8] == 'e') & (m[9] == 'e') & (m[10] == 'n')
			& (m[11] == 'P') & (m[12] == 'a') & (m[13] == 't') & (m[14] == 'c') & (m[15] == 'h')
		)
		{
			return {(const void *) ((uintptr_t) sections.baseAddress + sections.codeSection->VirtualAddress), header};
		}
	}

	return {0, 0};
}
#endif
#endif
