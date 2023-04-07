stack segment para stack 'stack'
    dw 20 dup(?)

stack ends  

data segment para public 'data'
    grades db 35, 44, 55, 66, 77, 55, 88, 12, 99, 91
    n_grades dw 10
    avg db 0

    n_fail dw 0
    n_excuse dw 0
    n_success dw 0

data ends

code segment para public 'code'
    assume cs:code, ds:data, ss:stack

main proc far
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    xor si, si
    xor ax, ax
    mov cx, n_grades

L1:
    mov bl, grades[si]
    cmp bl, 40
    jb L2
    add al, bl
    adc ah, 0
L2:
    inc si
    loop L1

    div n_grades
    mov avg, al

    xor si, si
    mov cx, n_grades

L3:
    mov bl, grades[si]
    cmp bl, 40
    jb fail 
    cmp bl, avg
    jb excuse
    inc n_success 
    jmp L4

fail:
    inc n_fail
    jmp L4

excuse: 
    inc n_excuse
    
L4:
    inc si
    loop L3
    
    retf
main endp

code ends
end main