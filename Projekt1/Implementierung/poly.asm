BITS 64
;assm 64 bits follows up

; Das Label (= Funktionsname ) soll als Symbol e x p o r t i e r t werden.
GLOBAL addNum
;rdi = 1st rsi = 2nd param
addNum:
  fld [rdi]
  fld [rsi]
                ;lwc1  rax, rdi
  fadd qword st0, st1
  fst qword rax
ret
