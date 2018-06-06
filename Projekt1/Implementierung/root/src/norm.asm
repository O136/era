BITS 64
GLOBAL norm



norm:
;;; float norm(struct polynom *input, struct polynom *output)
        push    rbp		     ;work with rbp instead of rsp directly
        mov     rbp, rsp
        mov     QWORD  [rbp-24], rdi ;*input param pointer
        mov     QWORD  [rbp-32], rsi ;*output param pointer


;;; int degree = input->iDegree
        mov     rax, QWORD  [rbp-24] ;move raw *input pointer into rax
        mov     eax, DWORD  [rax]    ;dereference *input pointer and move 32 bits(int) into eax
        mov     DWORD  [rbp-8], eax  ;local variable int degree=eax


;;; output->iDegree = degree;
        mov     rax, QWORD  [rbp-32] ;move raw *output pointer into rax
        mov     edx, DWORD  [rbp-8]  ;move int degree into edx
        mov     DWORD  [rax], edx    ;dereference *output pointer and move 32 edx bits
				     ;*output->iDegree = edx

;;; float a_N = input->p_fCoefficients[degree]
        mov     rax, QWORD  [rbp-24] ;move *input pointer into rax
        mov     rax, QWORD  [rax+8]  ;rax = input->p_fCoefficients
        mov     edx, DWORD  [rbp-8]  ;move int degree into edx
        movsx   rdx, edx             ;move edx into rdx preserving the sign
        shl     rdx, 2               ;shift 2 bits from rdx to the left (multiplication by 4)
				     ;we're accesing an array of float coefficients, so we need
				     ;offset of 4 bytes
        add     rax, rdx	     ;(p_fCoefficients+degree)
        fld     DWORD  [rax]         ;push *(input->p_fCoefficients+degree)=a_N on the fpu stack(ST(0))
                                     ;fld automatically converts to double precision floating format
        fstp    DWORD  [rbp-12]      ;copy & pop value from ST(0) register into local variable [rb-12]=a_N,
				     ;using DWORD because a_N is a 4Byte float


;;; for (int i=0; i <= degree;
        mov     DWORD  [rbp-4], 0    ;create local variable int i=0
.START_LOOP:
        mov     eax, DWORD  [rbp-4]  ;eax = i
        cmp     eax, DWORD  [rbp-8]  ;if i > local variable int degree
        jg      .FINISH_LOOP	     ;then jump to FINISH_LOOP


;;; output->p_fCoefficients[i] = input->p_fCoefficients[i] / a_N;
        mov     rax, QWORD  [rbp-24] ;rax=input
        mov     rax, QWORD  [rax+8]  ;rax=input+8 which is also rax=input->p_fCoefficients
        mov     edx, DWORD  [rbp-4]  ;edx = local variable int i
        movsx   rdx, edx             ;sign extend the 32bit edx to 64bit rdx
        shl     rdx, 2               ;rdx=rdx*4 (needed in order to iterate float array of p_fCoefficients)
        add     rax, rdx             ;inp=inp+i which is also input[i]
        fld     DWORD  [rax]         ;dereference inp, namely push *inp on the FPU stack
        mov     rax, QWORD  [rbp-32] ;rax=output pointer
        mov     rax, QWORD  [rax+8]  ;rax=output+8 which is also rax=output->p_Coefficients
        mov     edx, DWORD  [rbp-4]  ;edx=local variable int i
        movsx   rdx, edx             ;sign extend the 32bit edx to 64bit edx
        shl     rdx, 2               ;rdx=rdx*4, needed to iterate the 4byte float array of p_fCoefficients
        add     rax, rdx             ;rax=input[i] which is also rax=input+i
        fdiv    DWORD  [rbp-12]      ;divides input->p_fCoefficients[i] by a_N which is also ST(0)
				     ;and store it in ST(0), input[i] was pushed to ST(0) earlier
        fstp    DWORD  [rax]         ;copy & pop from ST(0) to *(output->p_fCoefficients[i])
        add     DWORD  [rbp-4], 1    ;increment local variable int i
        jmp     .START_LOOP
.FINISH_LOOP:

;;; return a_N (normalizing constant c);
        fld     DWORD  [rbp-12]      ;push local variable float a_N to the FPU stack
				     ;(ST(0) is top of FPU stack)
        fstp    DWORD  [rbp-36]      ;copy & pop from ST(0) to address where return value is located
        movss   xmm0, DWORD  [rbp-36];move floating point return value(a_N) to xmm0(return register)
				     ;also DWORD [rbp-12] could've been possible
				     ;but fstp DWORD xmm0 is not allowed
        pop     rbp
        ret
