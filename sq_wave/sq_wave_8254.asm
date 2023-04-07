
gen_80_khz_sq proc near

    mov dx, CONTROL
    mov al, 10110110  ; CNTR_2 control word
    out dx, al

    mov dx, CNTR_2
    mov al, 100       ; LSB
    out dx, al

    mov al, 0         ; MSB
    out dx, al

    ret
gen_80_khz_sq endp
