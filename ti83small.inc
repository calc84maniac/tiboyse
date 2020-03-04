#define bcall(xxxx) rst 28h \ .dw xxxx

_JForceCmdNoChar	.equ 4027h
_ChkFindSym		.equ 42F1h
_EnoughMem		.equ 42FDh
_PutC			.equ 4504h
_DispHL			.equ 4507h
_PutS			.equ 450Ah
_ClrScrnFull		.equ 4546h
_HomeUp			.equ 4558h
_getkey			.equ 4972h
_CreateAppVar		.equ 4E6Ah
_FlashWriteDisable	.equ 4F3Ch
_DelVarArc		.equ 4FC6h
_Arc_Unarc		.equ 4FD8h ;checks for low battery
_FindSwapSector		.equ 5095h
_CopyFlashPage		.equ 5098h
_FindAppNumPages	.equ 509Bh

arcInfo			.equ 83EEh
contrast		.equ 8447h
OP1			.equ 8478h
OP4			.equ 8499h
iMathPtr5		.equ 84DBh
onSP			.equ 85BCh
saveSScreen		.equ 86ECh
flags			.equ 89F0h
pagedCount		.equ 9834h
pagedBuf		.equ 983Ah
appBackUpScreen		.equ 9872h

AppVarObj		.equ 15h	;application variable

previousEntriesMP .equ 977Eh
gbufMP .equ 9A7Eh