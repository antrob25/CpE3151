;
; toggleProject.asm
;
; Created: 1/29/2020 10:20:28 AM
; Author : argk4
; Device : ATmega324PB

		LDI R20,0 ; R20 <- 0
		LDI R16,0xFF ; R16 <- 0xFF
		OUT DDRD,R16 ; DDRD <- R16
		LDI R17,0x00 ; R17 <- 0x00
		OUT DDRA,R17 ; DDRA <- R17

L1:		OUT PORTD,R16 ; PORTD <- R16
		CALL QDELAY   ; Calls the QDELAY function
		OUT PORTD,R20 ; PORTD <- R20
		CALL QDELAY
		RJMP L1       ; Jumps to the top of the loop

QDELAY:
		LDI R21, 255 ; 
		L2:
			LDI R20, 255
			L3:
				LDI R18, 25
				L4:
					NOP
					NOP
					DEC R18
					BRNE L4
				DEC R20
				BRNE L3
			DEC R21
			BRNE L2
			RET
