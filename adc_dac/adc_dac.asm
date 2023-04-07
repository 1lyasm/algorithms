CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE


DATA SEGMENT PUBLIC 'DATA'
        ASSUME DS:DATA

        addr_8255_a = 0000h
        addr_8255_b = 0002h
        addr_8255_c = 0004h
        addr_8255_ctrl = 0006h
        addr_adc = 0200h
        addr_adc_intr = 0400h
        addr_dac = 0600h
        addr_8253_cntr_0 = 0800h
        addr_8253_cntr_1 = 0802h
        addr_8253_cntr_2 = 0804h
        addr_8253_ctrl = 0806h

        cword_8255 = 10010000b
        cword_8253_wr_c0 = 00110100b
        cword_8253_rd_back_c0 = 11100010b
        count_8253 = 500

        sampled_sig db 100 dup(?)

        dac_delay = 000fh

DATA ENDS


STACK SEGMENT STACK USE16 
        DW 20 DUP(?)
        ASSUME SS:STACK
STACK ENDS

; input: delay amount is stored in cx before function is called
delay proc near
    delay_L1: loop delay_L1
    ret
delay endp

set_8253 proc near
    push dx
    push ax

    mov al, cword_8253_wr_c0
    mov dx, addr_8253_ctrl
    out dx, al

    mov ax, count_8253
    mov dx, addr_8253_cntr_0
    out dx, al
    mov al, ah
    out dx, al

    pop ax
    pop dx
    ret
set_8253 endp

wait_adc_conversion proc
    push dx
    push ax

    mov dx, addr_adc_intr
wait_adc_conversion_loop:
    in al, dx
    test al, 00010000b
    jnz wait_adc_conversion_loop

    pop ax
    pop dx
    ret
wait_adc_conversion endp

read_adc proc near
    push dx
    push ax
    push si

    xor si, si
    mov dx, addr_8255_a
read_adc_wait_pulse:
    in al, dx
    test al, 01h
    jz read_adc_exit_wait
    loop read_adc_wait_pulse

read_adc_exit_wait:
    cmp si, 100
    jae read_adc_exit
    mov dx, addr_adc
    mov al, 00h 
    out dx, al
    call wait_adc_conversion
    in al, dx
    mov sampled_sig[si], al
    inc si
    mov dx, addr_8255_a
    loop read_adc_wait_pulse
read_adc_exit:
    pop si
    pop ax
    pop dx
    ret
read_adc endp

wr_dac proc
    push dx
    push ax
    push si

    mov dx, addr_8255_a
wr_dac_wait_pulse:
    in al, dx
    test al, 01h
    jz wr_dac_exit_wait_pulse
    loop wr_dac_wait_pulse 
wr_dac_exit_wait_pulse:
    cmp si, 100
    jae wr_dac_exit
    mov dx, addr_dac
    mov al, sampled_sig[si]
    out dx, al
    inc si
    mov cx, dac_delay
    call delay
    xor al, al
    out dx, al
    mov dx, addr_8255_a
    loop wr_dac_wait_pulse
wr_dac_exit:

    pop si
    pop ax
    pop dx
    ret
wr_dac endp

set_8255 proc
    push dx
    push ax

    mov dx, addr_8255_ctrl
    mov al, cword_8255
    out dx, al

    pop ax
    pop dx
    ret
set_8255 endp

START:
    MOV AX, DATA
    MOV DS, AX
    MOV ES, AX

    call set_8253
    call set_8255
    call read_adc
ENDLESS:
    call wr_dac
    jmp ENDLESS

CODE    ENDS
        END START
