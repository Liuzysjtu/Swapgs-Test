


;edx:eax
.code
my_rdmsr proc
	rdmsr
	shl rdx, 20h
	or rax, rdx
	ret
my_rdmsr endp ;rax 保存的是返回值


; rcx 第一个参数
; rdx 第二个参数
my_swapgs proc
push rbx
push rsi

mov rbx, rcx
mov rsi, rdx

mov rcx, 0C0000101h ;IA32_GS_BASE
call my_rdmsr
mov [rbx], rax

mov rcx, 0C0000102h ;IA32_KERNEL_GS_BASE
call my_rdmsr
mov [rsi], rax

swapgs

pop rsi
pop rbx
ret
my_swapgs endp

end