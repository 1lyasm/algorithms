CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE


DATA SEGMENT PUBLIC 'DATA'
        ASSUME DS:DATA
        dac_addr = 0062h
        max_val = 00ffh
        min_val = 0001h
        delay_cnt = 0006h

DATA ENDS

delay proc near
    nop
    push cx
    mov cx, delay_cnt
    delay_1: loop delay_1
    pop cx
    ret
delay endp


STACK SEGMENT STACK USE16 
        DW 20 DUP(?)
        ASSUME SS:STACK
STACK ENDS


START:
        MOV AX, DATA
        MOV DS, AX
        MOV ES, AX

        mov dx, dac_addr
        mov al, 1
        mov bl, 1
L1:
        cmp al, max_val
        jb below_max
        mov bl, -1
below_max:
        cmp al, min_val
        ja above_min
        mov bl, 1
above_min:
        out dx, al
        call delay
        add al, bl
        jmp L1


CODE    ENDS
        END START
