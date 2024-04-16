.global _start

_start:

    # ----- Read input ----- #
    addi a7, zero, 56 # openat syscall
    addi a0, zero, 0  # TODO
    la a1, input        # Load address &input into a1
    addi a2, zero, 0  # I think this is the flags for open?
    ecall             # Syscall

    # ----- Print ----- #
    addi a7, zero, 64 # Put 64 in a7 (write syscall id)
    addi a0, zero, 1  # Put 1 (STDOUT FD) in a0
    la a1, helloworld # Load address &helloworld into a1
    addi a2, zero, 13 # Put string length in a2
    ecall             # Syscall

    # ----- Exit ----- #
    addi a7, zero, 93 # Put exit syscall id in a7
    addi a0, zero, 0  # Exit code to exit with
    ecall             # Syscall

helloworld:
    .ascii "Hello World!\n"

input:
    .ascii "input"
