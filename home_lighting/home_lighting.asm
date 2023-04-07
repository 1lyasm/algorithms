CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE


DATA SEGMENT PUBLIC 'DATA'
        ASSUME DS:DATA
        addr_dac = 0062h
        addr_adc = 006ah
        addr_adc_intr = 0068h

        delay_cnt = 0fh

DATA ENDS


delay PROC NEAR
        PUSH CX
        MOV CX, delay_cnt
        COUNT:
        LOOP COUNT
        POP CX
        RET
delay ENDP


STACK SEGMENT STACK USE16 
        DW 40 DUP(?)
        ASSUME SS:STACK
STACK ENDS


START:
        MOV AX, DATA
        MOV DS, AX
        MOV ES, AX

L1:
        mov dx, addr_adc  
        mov al, 00H
        out dx, al

L2:
        mov dx, 00h
        in al, dx
        mov dx, addr_adc_intr
        in al, dx
        test al, 80H
        JNZ L2

        mov dx, addr_adc
        in al, dx
        call delay

        mov dx, addr_dac
        mov bl, 0ffh
        sub bl, al
        mov al, bl
        out dx, al
        call delay


        JMP L1

CODE    ENDS
        END START