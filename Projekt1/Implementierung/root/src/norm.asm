BITS 64
GLOBAL norm

section .data
        REL_ERROR: dd 0.005     ;needed for the (tolerant) floating point comparison

section .text

isCoeffZero:                    ;rdi=polynom* p, rsi=int i
  mov esi, esi                  ;clear esi register
  mov rax, QWORD [rdi+8]        ;rax = p->p_fCoefficients
  fld DWORD [rax+rsi*4]         ;push to stack p->p_fCoefficients[i]
  fabs                          ;take abs val of st0 (=p->p_fCoefficients[i])
  fld DWORD [REL_ERROR]         ;push 0.005 to stack, now st0=0.005
  fucomip st0, st1              ;compare st0=0.005 and st1=p->p_fCoefficents
  fstp st0                      ;pop fpu stack
  seta al                       ;set al=1 or al=0 taking in account the fucomip result
  ret

areAllCoeffZero:                ;rdi=polynom* p
  push r12                      ;save r12, rbp, rbx
  push rbp
  push rbx
  mov r12d, DWORD [rdi]         ;r12d=lower 32 bits , r12d=p->iDegree
  test r12d, r12d               ;test if r12d is 0
  js .coef_early_return
  mov rbp, rdi                  ;rbp=polynom* p
  mov ebx, 0                    ;ebx plays the role of int i loop variable

.coef_loop:
  mov esi, ebx                  ;rsi = i, needed to call isCoeffZero
  mov rdi, rbp                  ;isCoeffZero(rdi=p, rsi=int i)
  call isCoeffZero
  test al, al                   ;test if al is 0
  je .coef_normal_return
  add ebx, 1                    ;increment i
  cmp ebx, r12d                 ;if r12d > 0 loop again
  jle .coef_loop

.coef_normal_return:
  pop rbx                       ;restore the previous values
  pop rbp                       ;of the registers
  pop r12
  ret

.coef_early_return:
  mov eax, 1                    ;eax is the return register
  jmp .coef_normal_return

norm:
  push rbp
  push rbx
  sub rsp, 8                    ;save some space for local vars
  mov rbx, rdi                  ;rbx=polynom* input
  mov rbp, rsi                  ;rbp=polynom* ouput
  call areAllCoeffZero
  fldz                          ;push 0 to fpu stack
  test al, al                   ;if al=0 return (if allCoeffZero==0)
  jne .norm_return
  mov edi, DWORD [rbx]          ;edi=input->iDegree
  test edi, edi                 ;check if iDegree==0
  js .norm_return               ;if input->iDegree < 0
  fstp st0                      ;clear st0 register
  mov DWORD [rbp], edi          ;output->iDegree = input->iDegree
  movsx rax, edi                ;mov with sign extension from 32 to 64
  mov rdx, QWORD [rbx+8]        ;rdx=input->p_fCoefficients[0]
  fld DWORD [rdx+rax*4]         ;push to fpu stack input->p_fCoefficients[iDegree]
  mov eax, 0

.norm_loop:
  movsx rdx, eax                ;move with sign extension from 32 to 64
  mov rcx, QWORD [rbp+8]        ;rcx=output->p_fCoefficients[0]
  mov rsi, QWORD [rbx+8]        ;rsi=input->p_fCoefficients[0]
  fld st0                       ;push st0 to fpu stack (st0=a_N=input->p_fCoefficients[iDegree])
  fdivr DWORD [rsi+rdx*4]       ;st0=input->p_fCoefficients[i]/st0
  fstp DWORD [rcx+rdx*4]        ;store result in output->p_fCoefficients[i]  and pop fpu stack
  add eax, 1                    ;increment loop var i
  cmp edi, eax
  jge .norm_loop

.norm_return:
  fstp DWORD [rsp+4]            ;store the return value and pop fpu stack
  movss xmm0, DWORD [rsp+4]     ;move float to xmm0,xmm0 is the return register for float func.
				;rsp+4 needed because movss xmm0, st0 is not valid
  add rsp, 8                    ;restore rsp, rbp, rbx
  pop rbx
  pop rbp
  ret

