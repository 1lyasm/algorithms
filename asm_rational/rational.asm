stack segment para stack 'stack'
    dw 20 dup(?)
stack ends


data segment para public 'data'
    P dw 27; 317
    Q dw 4; 49

    coeffs dw ?

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

    mov ax, P 
    mov bx, Q

L1:
    xor dx, dx
    div bx
    mov coeffs[si], ax
    mov ax, bx
    mov bx, dx
    add si, 2
    test bx, bx
    jz exit_
    jmp L1

exit_:

    retf
main endp

code ends
end main
