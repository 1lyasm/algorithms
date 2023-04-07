stack segment para stack 'stack'
    db 20 dup(?)
stack ends

data segment para public 'data'
    m dw 8191
    a dw 884
    c dw 1
    rand db ?
data ends

code segment para public 'code'
    assume cs:code, ds:data, ss:stack

main proc near
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    mov ax, cs:[23]
L1: xor dx, dx
    mov bx, a
    mul bx
    add ax, c
    adc dx, 0
    mov bx, m
    div bx
    mov ax, dx
    cmp ax, 255
    ja L1
    mov rand, al
    ret
main endp
code ends
end main

