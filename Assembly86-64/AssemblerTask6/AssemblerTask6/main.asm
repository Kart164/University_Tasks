extrn GetStdHandle: proc, ;дискриптер потока
	  WriteConsoleA: proc, ;функция для записи строки в поток
	  ReadConsoleA: proc, ;чтение строки
	  lstrlenA: proc, ;длина строки
	  ExitProcess :proc ;функция с 4ch

.data
const1 equ 2569h
const2 equ 12h
STD_OUTPUT_HANDLE equ -11
STD_INPUT_HANDLE equ -10
hStdInput qword ?
hStdOutput qword ?
sum dq ?
aSymb db 'a=', 0
bSymb db 'b=', 0
f db '2569-(12+A+B)=', 0
errorStr db 'Invalid character', 0
exitStr db 'Press any key to exit...', 0
.code
STACKALLOC macro arg
  push R15
  mov R15, RSP
  sub RSP, 8*4
  if arg
    sub RSP, 8*arg
  endif
  and SPL, 0F0h
endm

STACKFREE macro arg
mov rsp,R15
pop R15
endm

NULL_FIFTH_ARG macro arg
mov qword ptr [RSP + 32], 0
endm

ReadNumb proc
    local readStr[64]: byte,
      bytesRead:   dword
    STACKALLOC 1
    mov RCX, hStdInput
    lea RDX, readStr
    mov R8, 64
    lea R9, bytesRead
    NULL_FIFTH_ARG
    call ReadConsoleA
    mov rcx, 0 
    mov ecx, bytesRead
    sub rcx,2
    mov readStr[RCX], 0
    mov rbx,0
    mov r8, 1
    label1:
        dec rcx
        cmp rcx, -1
        je scanningComplete
        mov rax, 0
        mov AL, readStr[RCX]
        cmp al, '-'
        je scanningProcessing
        
            cmp AL, 30h
            jl error
            cmp AL, 39h
            jg error
            jmp eval
            scanningProcessing:
                xor al, al
                mov rbx, rax
                jmp scanningComplete

        eval:
            sub RAX, 30h
            mul R8
            add RBX, RAX
            mov RAX, 10
            mul R8
            mov R8, RAX
            jmp label1
    label12:
    neg rbx
    jmp scanningComplete
    error:
        mov r10, 0
        STACKFREE
        ret
    scanningComplete:
        mov r10,1
        mov rax,rbx
        STACKFREE
        ret 8*2
ReadNumb endp

PrintString proc uses RAX RCX RDX R8 R9, string: qword
local bytesWritten: qword
STACKALLOC 1
mov RCX, string
call lstrlenA
mov RCX, hStdOutput
mov RDX, string
mov R8, RAX
lea R9, bytesWritten
NULL_FIFTH_ARG
call WriteConsoleA
STACKFREE
ret 8
PrintString endp

PrintNumb proc
local numberStr[22]:BYTE
mov r8, 0
mov RAX, sum
cmp sum[63],0 
jne L2
L1:
mov numberStr[r8],'-'
inc r8
neg rax
L2:
mov rbx,10
mov rcx,0
divLabel:
mov rdx,0
div rbx
add rdx, 30h
push rdx
inc rcx
cmp rax,0
jne divLabel
toStack:
pop rdx
mov numberStr[r8],dl
inc r8
loop toStack
mov numberStr[R8], 0
lea rax, numberStr
push rax
call PrintString
STACKFREE
ret 8
PrintNumb endp

Endproc proc
local readStr: byte,
       bytesRead: dword
STACKALLOC 2
lea rax, exitStr
push rax
call PrintString 
mov RCX, hStdInput
lea RDX, readStr
mov R8, 64
lea R9, bytesRead
NULL_FIFTH_ARG
call ReadConsoleA
STACKFREE
ret
Endproc endp


Start proc
STACKALLOC 2
mov rcx, STD_OUTPUT_HANDLE
call GetStdHandle
mov hStdOutput, rax
mov rcx, STD_INPUT_HANDLE
call GetStdHandle
mov hStdInput, rax
lea rax, aSymb
push rax
call PrintString
call ReadNumb
cmp R10, 0
JE m1
mov r8,R10
lea rax, bSymb
push rax
call PrintString
call ReadNumb
cmp R10, 0
JE m1
mov sum, const1
add r8, r10
add r8, const2
sub sum, r8
lea rax, f
push rax
call PrintString
call PrintNumb

call Endproc
call ExitProcess


m1:
lea rax, errorStr
push rax
call PrintString
call ExitProcess
Start endp
End