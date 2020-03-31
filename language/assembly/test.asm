section .text    ;section declaration

global _start

_start:

        mov     edx,len ;third argument: message length
        mov     ecx,msg ;second argument: pointer to message to write
        mov     ebx,1   ;first argument: file handle
        mov     eax,4   ;system call number (sys_write)
        int     0x80    ;call kernel

        mov     ebx,0   ;first syscall argument: exit code
        mov     eax,1   ;system call number (sys_exit)
        int     0x80    ;call kernel

section .data               ;section declaration

        msg     db      "Hello, World!",0xa ;our dear string
        len     equ     $ - msg                 ;length of our dear string
