bits 16 ; tells NASM that this is 16 bit code
org 0x7c00 ; BIOS jumps to location 0x7C00 of device to transfer control to bootloader, this tells NASM to start outputting at this offset

boot:
    mov si,hello ; si is the source index register used for string operations
    mov ah,0x0e ; this is to tell the interrupt call later to output a character to the screen

.loop:
    lodsb ; loads byte at address ds:si, as I understand it, it will load the address of the hello bytes + an offset
    or al,al ; this tests if we've reached the 0 byte
    jz halt ; this tests if the result from before was 0 (i.e., we've reached the end of the string), if so, it jumps to the halt label
    int 0x10 ; BIOS interrupt call to video services, this uses the 0e set earlier to write character in tty mode https://en.wikipedia.org/wiki/BIOS_interrupt_call#Interrupt_table
    jmp .loop ; start at the beginning of the loop again

halt:
    cli ; clears interrupt flag
    hlt ; puts the processor into an idle state

hello: db "Hello, world!",0 ; db places the bytes in the executable, in this case the bytes for the string "Hello, world!", and a 0, which we use to check if we've reached the end of the string

times 510 - ($-$$) db 0 ; pad remaining 510 bytes with zeroes, $ = current address (current byte), $$ = address of start of current section
dw 0xaa55 ; When the BIOS sees that the last 2 bytes of the 512 byte sector it read are 0xaa55, it jumpts to 0x7c00
