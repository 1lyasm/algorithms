    CODE    SEGMENT PUBLIC 'CODE'
            ASSUME CS:CODE

    DATA SEGMENT PUBLIC 'DATA'
            ASSUME DS:DATA

            addr_8255_a = 00a8h
            addr_8255_b = 00aah
            addr_8255_c = 00ach
            addr_8255_ctrl = 00aeh
            cword_8255 = 00bch

            addr_8259_1 = 00a0h
            addr_8259_2 = 00a2h

            delay_cnt = 0ffffh

            intr_num = 38h
    DATA ENDS

    STACK SEGMENT STACK USE16 
            DW 20 DUP(?)
            ASSUME SS:STACK
    STACK ENDS

    set_8255 proc
        push dx
        push ax

        mov dx, addr_8255_ctrl

        mov al, 05h
        out dx, al
        mov al, cword_8255
        out dx, al

        pop ax
        pop dx
        ret
    set_8255 endp

    set_8259 proc
        push dx
        push ax

        MOV AL, 13H
        OUT addr_8259_1, AL
        MOV AL, intr_num
        OUT addr_8259_2, AL
        MOV AL, 0bH
        OUT addr_8259_2, AL

        pop ax
        pop dx
        ret
    set_8259 endp

    place_intr proc
        push dx
        push ax

        XOR AX, AX
        MOV ES, AX
        MOV AL, intr_num
        MOV AH, 4
        MUL AH
        MOV BX, AX
        LEA AX, button_inp_intr
        MOV WORD PTR ES:[BX], AX
        MOV AX, CS
        MOV WORD PTR ES:[BX+2], AX 

        pop ax
        pop dx
        ret
    place_intr endp

    delay PROC
            PUSH CX
            MOV CX, delay_cnt
            delay_1: LOOP delay_1
            POP CX
            RET
    delay ENDP

    button_inp_intr proc far
        mov dx, addr_8255_a
        in al, dx
        and al, 0fh
        iret
    button_inp_intr endp

    START:
        MOV AX, DATA
        MOV DS, AX
        MOV ES, AX
        cli
        call place_intr
        call set_8259

        mov dx, addr_8255_ctrl
        mov al, 09h     
        out dx, al

        mov dx, addr_8255_ctrl
        mov al, 0bch
        out dx, al

    L1: sti
        hlt
        jmp L1
    CODE    ENDS
            END START
