
CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE


DATA SEGMENT PUBLIC 'DATA'
    cntr_0 = 0a9h
    cntr_1 = 0abh
    cntr_2 = 0adh
    control = 0afh

DATA ENDS


STACK SEGMENT STACK USE16 
        DW 20 DUP(?)
        ASSUME SS:STACK
STACK ENDS


START:
        ; INIT DS AND ES
        MOV AX, DATA
        MOV DS, AX
        MOV ES, AX

        ; set counter 0 control
        mov al, 34h
        out control, al       

        ; set counter 0 count
        mov ax, 2000
        out cntr_0, al
        mov al, ah
        out cntr_0, al 

        ; set counter 1 control
        mov al, 74h
        out control, al       

        ; set counter 1 count
        mov ax, 1000
        out cntr_1, al
        mov al, ah
        out cntr_1, al  

ENDLESS:
        JMP ENDLESS

CODE    ENDS
        END START

