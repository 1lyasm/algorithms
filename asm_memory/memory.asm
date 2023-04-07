CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE

STACK SEGMENT STACK USE16 
        DW 100 DUP(?)
        ASSUME SS:STACK
STACK ENDS

; define labels at the location of functions
; to be able to do far call
f1_seg SEGMENT BYTE AT 2000H
    org 0000h
	; 2000h:0000h
	f1_lbl  LABEL FAR
f1_seg       ENDS

f2_seg SEGMENT BYTE AT 2800H
    org 0002h
	; 2800h:0002h
	f2_lbl  LABEL FAR
f2_seg       ENDS

START:
	; empty write to RAM to start it, ignore
	mov ax, 6000h
	mov ds, ax
	mov bx, 0000h
	mov word ptr [bx], 0000h

endless:    
    ; make far call to functions in ROM
	call far ptr f1_lbl
	call far ptr f2_lbl
    ; some values are written to RAM after these calls
    jmp endless

CODE    ENDS
        END START
