stack segment para stack 'stack'
    dw 40 dup(?)
stack ends

data segment para public 'data'
    inp_prmpt_1 db "Enter first number: ", 0
    inp_prmpt_2 db "Enter second number: ", 0
    dbg_prmpt_1 db "You first entered: ", 0
    dbg_prmpt_2 db "You secondly entered: ", 0
    result_prompt db "Product of those numbers is: ", 0

    op1 db 0
    op2 db 0
data ends


code segment para public 'code'
    assume cs:code, ds:data, ss:stack

; input: bx stores address of first element of null-terminated string
print_str proc near
    push ax
    push si
    push dx
    xor si, si
print_str_L1:
    mov dl, [bx]
    test dl, dl
    jz print_str_end_str
    mov si, bx
    ; char print
    mov ah, 02h
    int 21h
    mov bx, si
    inc bx
    jmp print_str_L1
print_str_end_str: 
    pop dx
    pop si
    pop ax
    ret
print_str endp

print_nl proc near
    push ax
    push dx

    mov dl, 10
    mov ah, 02h
    int 21h

    mov dl, 13
    mov ah, 02h
    int 21h

    pop dx
    pop ax
    ret
print_nl endp

; input: al stores operand 1, dl stores operand 2
; output: ax stores product
multiply proc near
    push cx

    xor cx, cx
    mov cl, al
    xor ax, ax
multiply_L1:
    add al, dl
    adc ah, 0
    loop multiply_L1

    pop cx
    ret
multiply endp

; input: al stores integer
; output: al stores character version of input
int_to_char proc near
    add al, 48
    ret
int_to_char endp

; input: al stores character
; output: al stores integer version of input
char_to_int proc near
    sub al, 48
    ret
char_to_int endp

; input: al stores integer
print_int proc near
    push si
    push ax
    push bx
    push cx
    push dx

    xor si, si
    mov cl, 10
print_int_push_rep:
    test al, al
    jz print_int_push_end
    xor ah, ah
    div cl
    mov bl, ah
    xor bh, bh
    push bx
    inc si
    jmp print_int_push_rep
    ; ah: remainder
    ; al: result
print_int_push_end:
    mov cx, si
    mov ah, 02h
print_int_pop_rep:
    pop dx
    mov al, dl
    call int_to_char
    mov dl, al
    int 21h
    loop print_int_pop_rep

    pop dx
    pop cx
    pop bx
    pop ax
    pop si
    ret
print_int endp

; output: dl stores read character
read_char proc near
    push ax
    mov ah, 1
    int 21h
    mov dl, al
    pop ax
    ret
read_char endp

main proc far
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    mov di, 0fbh 

    lea bx, inp_prmpt_1
    call print_str

    call read_char
    mov al, dl
    call char_to_int
    mov op1, al
    call print_nl

    lea bx, dbg_prmpt_1
    call print_str
    mov al, op1
    call print_int
    call print_nl
    
    lea bx, inp_prmpt_2
    call print_str

    call read_char
    mov al, dl
    call char_to_int
    mov op2, al

    call print_nl
    lea bx, dbg_prmpt_2
    call print_str
    mov al, op2
    call print_int
    call print_nl

    mov al, op1
    mov dl, op2
    call multiply
    lea bx, result_prompt 
    call print_str
    call print_int
    call print_nl

    retf
main endp 

code ends
end main
