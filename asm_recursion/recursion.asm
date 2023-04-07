stack segment para stack 'stack'
    ; just enough to not overflow
    dw 64 dup(?)
stack ends  


data segment para public 'data'
    ; format strings for neat output
    fmt_str_1 db "D(", 0
    fmt_str_2 db ") = ", 0
data ends   


code segment para public 'code'
    assume cs:code, ds:data, ss:stack

; input: ax holds value to be printed
PRINTINT proc near
    push dx
    push ax
    push bx
    push cx

    ; cx counts number of digits in decimal form
    xor cx, cx
    ; divide hex number by 10 continuously
    mov bx, 0ah
PRINTINT_L1:
    xor dx, dx
    div bx
    ; push remainder to stack
    push dx
    ; increment number of digits
    inc cx
    ; end if quotient is zero
    test ax, ax
    jz end_div
    jmp PRINTINT_L1
    ; when digits are popped from stack and printed, 
    ; they are in right order
end_div:
    pop dx
    ; convert to ascii
    add dx, 30h
    ; ah: 02h -> character print
    mov ah, 02h
    ; put one digit to screen
    int 21h
    ; loop cx (number of digits) times 
    loop end_div

    pop cx
    pop bx
    pop ax
    pop dx
    ret
PRINTINT endp


; input: bx stores address of first element of null-terminated string
print_str proc near
    push si
    push dx
    xor si, si
print_str_1:
    mov dl, [bx]
    test dl, dl
    jz print_str_end
    mov si, bx
    mov ah, 02h
    int 21h
    mov bx, si
    inc bx
    jmp print_str_1
print_str_end: 
    pop dx
    pop si
    ret
print_str endp

; input: topmost element of stack
; output: topmost element of stack, overwrites input, so that
; pop gives result after the function call
DNUM proc far
    ; save bp, do not want recursive calls to change it
    push bp
    push ax
    push bx
    ; to be able to reference input value
    mov bp, sp
    
    ; + input, cs, offset, bp, ax, bx -
    ; bp points to bx, 10 above is input
    mov ax, [bp + 10]

    ; input = 0 -> return 0
    test ax, ax
    jz DNUM_1
    ; else if 1 or 2, return 1
    cmp ax, 3
    jb DNUM_2
    ; call recursively with n - 1
    dec ax
    push ax
    call DNUM
    ; D(n - 1) is on top of stack, call again
    ; without popping as D(n - 1) is the input anyways
    call DNUM
    ; bx becomes D(D(n - 1))
    pop bx
    mov ax, [bp + 10]
    ; to get D(n - 2)
    sub ax, 2
    push ax
    call DNUM
    ; ax = D(n - 2)
    pop ax
    ; ax = n - 1 - D(n - 2)
    neg ax
    dec ax
    add ax, word ptr [bp + 10]
    push ax
    ; to get D(n - 1 - D(n - 2))
    call DNUM
    pop ax
    ; ax = D(D(n - 1)) + D(n - 1 - D(n - 2))
    add ax, bx
    ; write result on location of input
    mov word ptr [bp + 10], ax
    jmp DNUM_3
DNUM_1:
    ; write 0 on top of input
    mov word ptr [bp + 10], 0
    jmp DNUM_3
DNUM_2:
    ; write 1 on top of input
    mov word ptr [bp + 10], 1
DNUM_3:
    pop bx
    pop ax
    pop bp
    retf 
DNUM endp


main proc far 
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    ; call with 1 to 10
    mov si, 1
    mov cx, 10
L1:
    ; formatting
    lea bx, fmt_str_1
    call print_str

    mov ax, si
    call PRINTINT

    lea bx, fmt_str_2
    call print_str

    ; si stores input (1 to 10)
    push si
    call DNUM
    ; DNUM wrote its output on top of input, so popping 
    ; gives result
    pop ax  
    call PRINTINT

    ; \n    
    mov dl, 13
    mov ah, 02h
    int 21h

    mov dl, 10
    mov ah, 02h
    int 21h

    inc si
    loop L1

    retf
main endp


code ends
end main