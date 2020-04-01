;
; lab2.asm
;
; Created: 2/19/2020 9:59:22 AM
; Author : argk4
;

; port made configs
LDI R16, 0xFF
LDI R17, 0x00
OUT DDRD, R16
OUT PORTD, R16
OUT DDRA, R17
OUT PORTA, R16

MAIN:
	IN R20, PINA
	COM R20	; switches are active low

	LDI R16, 0x00
	LDI R17, 0x00

	CLC
	ROR R20
	ROL R16
	CLC
	ROR R20
	ROL R16
	CLC
	ROR R20
	ROL R16

	LSR R20
	LSR R20

	; serialization 3 times on R17
	IN R28, PINA
	CLC
	ROR R28
	ROL R17
	CLC
	ROR R28
	ROL R17
	CLC
	ROR R28
	ROL R17

	LDI R21, 0x00
	MULT:
		ADD R21, R16
		DEC R17
		BRNE MULT

	; Reverse bits of R20 into R22
	LDI R22, 0x00

	CLC
	ROR R21
	ROL R22

	CLC
	ROR R21
	ROL R22

	CLC
	ROR R21
	ROL R22

	LSR R21
	LSR R21

	; Complement and output the Result to PORTD since active low
	COM R22
	OUT PORTD, R22
	CALL DELAY
	RJMP MAIN

DELAY:
	LDI R24, 255
	D1:
		LDI R25, 255 
		D2:
			LDI R26, 25
			D3:
				NOP
				NOP
				DEC R26
				BRNE D3
			DEC R25
			BRNE D2
		DEC R24
		BRNE D1
		RET









