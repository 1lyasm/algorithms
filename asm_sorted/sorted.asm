stack segment para stack 'stack'
    dw 20 dup(?)
stack ends

data segment para public 'data'
    arr dw -5, -4, -3, 0, -2
    len_arr dw 5

    is_increasing db 0
data ends

code segment para public 'code'
    assume ss:stack, ds:data, cs:code
main proc far
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    xor si, si
    mov cx, len_arr
    dec cx

L1:
    mov bx, arr[si]
    mov dx, arr[si + 2]
    cmp bx, dx
    jnl last
    add si, 2
    loop L1

    inc is_increasing

last:

    retf
main endp

code ends
end main

