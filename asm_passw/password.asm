CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE


DATA SEGMENT PUBLIC 'DATA'
        ASSUME DS:DATA

        addr_a = 00a8h
        addr_b = 00aah
        addr_c = 00ach
        addr_ctrl = 00aeh
        cword = 10000010b

        u_ptrn = 01000001b
        l_ptrn = 01000111b

        ; holds input password
        inp_buffer db 5 dup(?)

        hash_idx = 0bh

        ; 2004 - birth year
        master_key db 01h, 0ah, 0ah, 03h

        ; holds tried password after lock
        passw_trial db 4 dup(?)
DATA ENDS


STACK SEGMENT STACK USE16 
        DW 20 DUP(?)
        ASSUME SS:STACK
STACK ENDS


set_8255 proc
    push dx
    push ax

    mov dx, addr_ctrl
    mov al, cword
    out dx, al

    pop ax
    pop dx
    ret
set_8255 endp

; input pattern is in al
out_7seg_letter proc 
    push dx

    mov dx, addr_a
    out dx, al

    pop dx
    ret
out_7seg_letter endp 

; result is written to al
inp_press proc
    push dx
    push di
    push si
    push cx

reset_al:
    mov al, 1
; activate columns one-by-one and check rows
activate_col:
    cmp al, 8
    jae reset_al
    mov dx, addr_c
    out dx, al
    mov dx, addr_b
    push ax
    in al, dx
    cmp al, 00f0h
    jnz save_inp
    pop ax
    shl al, 1
    jmp activate_col

; row info -> di, col info -> si
save_inp:
    and ax, 0fh
    mov di, ax
    pop si
wait_depress:
    in al, dx
    cmp al, 0f0h
    jne wait_depress

; clear higher bytes
    mov ax, di
    xor ah, ah
    mov di, ax

    mov ax, si
    xor ah, ah
    mov si, ax

; convert from bit activation to col/row index
    xor cx, cx
shift_loop_si:
    shr si, 1
    test si, si
    jz end_shift_loop_si
    inc cx
    jmp shift_loop_si
end_shift_loop_si:
    mov al, cl
    xor cx, cx
shift_loop_di:
    shr di, 1
    test di, di
    jz end_shift_loop_di
    inc cx
    jmp shift_loop_di
end_shift_loop_di:
    ; find index of the pressed button idx = 3 * row_idx + col_idx
    xchg al, cl 
    mov dl, 3
    mul dl
    ; index of pressed button is in al
    add al, cl

    pop cx
    pop si
    pop di
    pop dx
    ret
inp_press endp


inp_passw proc
    push cx
    push si
    push ax

    ; start by taking 5 inputs
    mov cx, 5
    xor si, si
inp_passw_L1:
    call inp_press
    mov inp_buffer[si], al
    inc si
    loop inp_passw_L1

    mov al, inp_buffer[4]
    cmp al, hash_idx
    jz end_inp_passw
    ; if last press was not #, assume that as first input
    ; and take 4 more inputs 
    mov cx, 4
    mov si, 1
    mov inp_buffer[0], al
    jmp inp_passw_L1

end_inp_passw:
    pop ax
    pop si
    pop cx
    ret
inp_passw endp


inp_passw_trial proc
    push ax
    push si
    push cx

    ; take 4 inputs, and save it in passw_trial array
    mov cx, 4
    xor si, si
inp_passw_trial_L1:
    call inp_press
    mov passw_trial[si], al
    inc si
    loop inp_passw_trial_L1

    pop cx
    pop si
    pop ax
    ret
inp_passw_trial endp

; unlock: al = 1, lock: al = 0
verify_trial proc
    push si
    push cx

    ; first entered sequence with defined password, 
    ; if is not correct, compare with master key, 
    ; if is false again, al = 0, otherwise, al = 1
    mov cx, 4
    xor si, si
compare_passw:
    mov al, inp_buffer[si]
    cmp al, byte ptr passw_trial[si]
    jne false_passw
    inc si
    loop compare_passw

    mov al, 1
    jmp end_verify_trial
false_passw:
    xor si, si
    mov cx, 4
compare_master:
    mov al, master_key[si]
    cmp al, byte ptr passw_trial[si]
    jne incorrect
    inc si
    loop compare_master

    mov al, 1
    jmp end_verify_trial
incorrect:
    xor ax, ax

end_verify_trial:
    pop cx
    pop si
    ret
verify_trial endp


START:
    MOV AX, DATA
    MOV DS, AX
    MOV ES, AX

    call set_8255
L1:
    ; display U
    mov al, u_ptrn
    call out_7seg_letter
    ; take password
    call inp_passw
    ; display L
    mov al, l_ptrn
    call out_7seg_letter
L2:
    ; locked, take trial
    call inp_passw_trial
    ; check if it should be unlocked
    call verify_trial
    test al, al
    ; if trial was not correct, continue by taking another 
    jz L2
    ; if answer was correct, go back,
    ; display U, and input a password again
    jmp L1

CODE    ENDS
        END START
