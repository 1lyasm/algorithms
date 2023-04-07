    CODE    SEGMENT PUBLIC 'CODE'
            ASSUME CS:CODE


    DATA SEGMENT PUBLIC 'DATA'
            ASSUME DS:DATA
            dac_addr = 0062h
            max_val = 00ffh
            min_val = 0001h
            delay_cnt = 0032h
            sin_table db 0, 11, 22, 33, 44, 54, 64, 73, 82, 91
                    db 98, 105, 111, 116, 120, 124, 126, 128,
                        128, 128, 126, 124, 120, 116, 111, 105,
                        98, 91, 82, 73, 64, 54, 44, 33, 22, 11, 0 
                    db -11, -22, -33, -44, -54, -64, -73, -82, -91
                    db -98, -105, -111, -116, -120, -124, -126, -127,
                        -127, -127, -126, -124, -120, -116, -111, -105,
                        -98, -91, -82, -73, -64, -54, -44, -33, -22, -11, 0
            table_len = 72
    DATA ENDS


    delay proc near
        nop
        nop
        nop
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
            mov bl, 127
    L1:
            xor si, si
    L2:
            cmp si, table_len
            ja L1
            mov al, sin_table[si]
            add al, bl
            out dx, al
            call delay
            inc si
            jmp L2

    CODE    ENDS
            END START
