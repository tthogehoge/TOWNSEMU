						ASSUME	CS:CODE

						PUBLIC	VNDRV_PRINT
						PUBLIC	VNDRV_DUMP

CODE					SEGMENT

TOWNSIO_VNDRV_AUXCOMMAND		EQU		2F18H
TOWNS_VNDRV_AUXCOMMAND_PRINT	EQU		09H
TOWNS_VNDRV_AUXCOMMAND_DUMP		EQU		0AH



VNDRV_PRINT				PROC
;	[EBP+4] Return EIP   [EBP+8] Pointer to c_str
						PUSH	EBP
						MOV		EBP,ESP
						PUSH	EAX
						PUSH	EBX
						PUSH	EDX

						MOV		EBX,[EBP+8]
						MOV		AL,TOWNS_VNDRV_AUXCOMMAND_PRINT
						MOV		DX,TOWNSIO_VNDRV_AUXCOMMAND
						OUT		DX,AL

						POP		EDX
						POP		EBX
						POP		EAX
						POP		EBP
						RET
VNDRV_PRINT				ENDP



VNDRV_DUMP				PROC
;	[EBP+4] Return EIP   [EBP+8] Pointer    [EBP+0CH] Length
						PUSH	EBP
						MOV		EBP,ESP
						PUSH	EAX
						PUSH	EBX
						PUSH	ECX
						PUSH	EDX

						MOV		EBX,[EBP+8]
						MOV		ECX,[EBP+0CH]
						MOV		AL,TOWNS_VNDRV_AUXCOMMAND_DUMP
						MOV		DX,TOWNSIO_VNDRV_AUXCOMMAND
						OUT		DX,AL

						POP		EDX
						POP		ECX
						POP		EBX
						POP		EAX
						POP		EBP
						RET
VNDRV_DUMP				ENDP



CODE					ENDS
						END

