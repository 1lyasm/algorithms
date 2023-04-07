stack segment para stack 'stack'
    ; when input is 500, D(n - 2) is called 
    ; recursively until n - 2 < 3, so there will be 
    ; 500 / 2 = 250 calls without returns.
    ; there is 3 pushes in beginning of every call, 
    ; each far call is 2 pushes, and each input is 1 push
    ; so to not overflow, stack must at least be
    ; 250 * 6 = 1500 words 
    dw 1520 dup(?)
stack ends


data segment para public 'data'
    fmt_str_1 db "D(", 0
    fmt_str_2 db ") = ", 0
    ; n is input
    n dw ?
    ; to not recompute same recursive calls
    cache dw 501 dup(-1)
data ends   


code segment para public 'code'
    assume cs:code, ds:data, ss:stack

; ax holds value to be printed
PRINTINT proc near
    push dx
    push ax
    push bx
    push cx

    xor cx, cx
    mov bx, 0ah
PRINTINT_L1:
    xor dx, dx
    div bx
    push dx
    inc cx
    test ax, ax
    jz end_div
    jmp PRINTINT_L1
end_div:
    pop dx
    add dx, 30h
    mov ah, 02h
    int 21h
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
; output: topmost element of stack, overwrites input
DNUM_dynamic proc far
    push bp
    push ax
    push bx

    mov bp, sp
    ; input, cs, offset, bp, ax, bx
    ; bp -> bx, same as in a)
    mov bx, [bp + 10]
    ; cache is word array, so index with 2 * input
    shl bx, 1
    ; if cache has D(n), return it
    cmp cache[bx], -1
    jnz DNUM_dynamic_1
DNUM_dynamic_2:
    ; check if D(n - 2) is in cache
    cmp cache[bx - 4], -1
    jnz DNUM_dynamic_3
    ; if not, compute it and place in cache
    lea ax, [bx - 4]
    shr ax, 1
    ; push n - 2 as input
    push ax
    call DNUM_dynamic
    ; cache result
    pop cache[bx - 4]
DNUM_dynamic_3:
    ; check if D(n - 1) is in cache
    cmp cache[bx - 2], -1
    jnz DNUM_dynamic_4
    ; if not, compute it and place in cache
    lea ax, [bx - 2]
    shr ax, 1
    ; push n - 1 as input
    push ax
    call DNUM_dynamic
    ; cache result
    pop cache[bx - 2]
    jmp DNUM_dynamic_4
DNUM_dynamic_1:
    ; answer is already in cache, return it
    mov ax, cache[bx]
    mov word ptr [bp + 10], ax
    jmp DNUM_dynamic_end
; this label takes prepared or existent results from cache,
; computes final result, and returns it 
DNUM_dynamic_4:
    ; ax becomes D(n - 1 - D(n - 2))
    mov bx, cache[bx - 4]
    lea ax, [bx + 1]
    neg ax
    add ax, word ptr [bp + 10]
    mov bx, ax
    shl bx, 1
    mov ax, cache[bx]

    ; add D(D(n - 1)) to ax
    mov bx, [bp + 10]
    shl bx, 1
    mov bx, cache[bx - 2]
    shl bx, 1
    add ax, cache[bx]
    ; ax = D(D(n - 1)) + D(n - 1 - D(n - 2))
    mov word ptr [bp + 10], ax
DNUM_dynamic_end:
    pop bx
    pop ax
    pop bp
    retf
DNUM_dynamic endp


main proc far 
    push ds
    xor ax, ax
    push ax
    mov ax, data
    mov ds, ax

    ; set first elements
    mov cache[0], 0
    mov cache[2], 1
    mov cache[4], 1

    ; formatting
    lea bx, fmt_str_1
    call print_str

    mov n, 500
    mov ax, n
    call PRINTINT
    lea bx, fmt_str_2
    call print_str
    push n
    call DNUM_dynamic
    ; result is in ax
    pop ax
    call PRINTINT

    retf
main endp


code ends
end main
