

.section	.ctors
	.p2align	3
	.quad	OPENSSL_cpuid_setup


.comm	OPENSSL_ia32cap_P,16,4

.text	

.globl	OPENSSL_atomic_add
.def	OPENSSL_atomic_add;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_atomic_add:
	movl	(%rcx),%eax
.Lspin:	leaq	(%rdx,%rax,1),%r8
.byte	0xf0
	cmpxchgl	%r8d,(%rcx)
	jne	.Lspin
	movl	%r8d,%eax
.byte	0x48,0x98
	.byte	0xf3,0xc3


.globl	OPENSSL_rdtsc
.def	OPENSSL_rdtsc;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_rdtsc:
	rdtsc
	shlq	$32,%rdx
	orq	%rdx,%rax
	.byte	0xf3,0xc3


.globl	OPENSSL_ia32_cpuid
.def	OPENSSL_ia32_cpuid;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_ia32_cpuid:
	movq	%rdi,8(%rsp)
	movq	%rsi,16(%rsp)
	movq	%rsp,%rax
.LSEH_begin_OPENSSL_ia32_cpuid:
	movq	%rcx,%rdi

	movq	%rbx,%r8

	xorl	%eax,%eax
	movl	%eax,8(%rdi)
	cpuid
	movl	%eax,%r11d

	xorl	%eax,%eax
	cmpl	$1970169159,%ebx
	setne	%al
	movl	%eax,%r9d
	cmpl	$1231384169,%edx
	setne	%al
	orl	%eax,%r9d
	cmpl	$1818588270,%ecx
	setne	%al
	orl	%eax,%r9d
	jz	.Lintel

	cmpl	$1752462657,%ebx
	setne	%al
	movl	%eax,%r10d
	cmpl	$1769238117,%edx
	setne	%al
	orl	%eax,%r10d
	cmpl	$1145913699,%ecx
	setne	%al
	orl	%eax,%r10d
	jnz	.Lintel


	movl	$2147483648,%eax
	cpuid
	cmpl	$2147483649,%eax
	jb	.Lintel
	movl	%eax,%r10d
	movl	$2147483649,%eax
	cpuid
	orl	%ecx,%r9d
	andl	$2049,%r9d

	cmpl	$2147483656,%r10d
	jb	.Lintel

	movl	$2147483656,%eax
	cpuid
	movzbq	%cl,%r10
	incq	%r10

	movl	$1,%eax
	cpuid
	btl	$28,%edx
	jnc	.Lgeneric
	shrl	$16,%ebx
	cmpb	%r10b,%bl
	ja	.Lgeneric
	andl	$4026531839,%edx
	jmp	.Lgeneric

.Lintel:
	cmpl	$4,%r11d
	movl	$-1,%r10d
	jb	.Lnocacheinfo

	movl	$4,%eax
	movl	$0,%ecx
	cpuid
	movl	%eax,%r10d
	shrl	$14,%r10d
	andl	$4095,%r10d

	cmpl	$7,%r11d
	jb	.Lnocacheinfo

	movl	$7,%eax
	xorl	%ecx,%ecx
	cpuid
	movl	%ebx,8(%rdi)

.Lnocacheinfo:
	movl	$1,%eax
	cpuid
	andl	$3220176895,%edx
	cmpl	$0,%r9d
	jne	.Lnotintel
	orl	$1073741824,%edx
	andb	$15,%ah
	cmpb	$15,%ah
	jne	.Lnotintel
	orl	$1048576,%edx
.Lnotintel:
	btl	$28,%edx
	jnc	.Lgeneric
	andl	$4026531839,%edx
	cmpl	$0,%r10d
	je	.Lgeneric

	orl	$268435456,%edx
	shrl	$16,%ebx
	cmpb	$1,%bl
	ja	.Lgeneric
	andl	$4026531839,%edx
.Lgeneric:
	andl	$2048,%r9d
	andl	$4294965247,%ecx
	orl	%ecx,%r9d

	movl	%edx,%r10d
	btl	$27,%r9d
	jnc	.Lclear_avx
	xorl	%ecx,%ecx
.byte	0x0f,0x01,0xd0
	andl	$6,%eax
	cmpl	$6,%eax
	je	.Ldone
.Lclear_avx:
	movl	$4026525695,%eax
	andl	%eax,%r9d
	andl	$4294967263,8(%rdi)
.Ldone:
	shlq	$32,%r9
	movl	%r10d,%eax
	movq	%r8,%rbx
	orq	%r9,%rax
	movq	8(%rsp),%rdi
	movq	16(%rsp),%rsi
	.byte	0xf3,0xc3
.LSEH_end_OPENSSL_ia32_cpuid:

.globl	OPENSSL_cleanse
.def	OPENSSL_cleanse;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_cleanse:
	xorq	%rax,%rax
	cmpq	$15,%rdx
	jae	.Lot
	cmpq	$0,%rdx
	je	.Lret
.Little:
	movb	%al,(%rcx)
	subq	$1,%rdx
	leaq	1(%rcx),%rcx
	jnz	.Little
.Lret:
	.byte	0xf3,0xc3
.p2align	4
.Lot:
	testq	$7,%rcx
	jz	.Laligned
	movb	%al,(%rcx)
	leaq	-1(%rdx),%rdx
	leaq	1(%rcx),%rcx
	jmp	.Lot
.Laligned:
	movq	%rax,(%rcx)
	leaq	-8(%rdx),%rdx
	testq	$-8,%rdx
	leaq	8(%rcx),%rcx
	jnz	.Laligned
	cmpq	$0,%rdx
	jne	.Little
	.byte	0xf3,0xc3

.globl	OPENSSL_wipe_cpu
.def	OPENSSL_wipe_cpu;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_wipe_cpu:
	pxor	%xmm0,%xmm0
	pxor	%xmm1,%xmm1
	pxor	%xmm2,%xmm2
	pxor	%xmm3,%xmm3
	pxor	%xmm4,%xmm4
	pxor	%xmm5,%xmm5
	xorq	%rcx,%rcx
	xorq	%rdx,%rdx
	xorq	%r8,%r8
	xorq	%r9,%r9
	xorq	%r10,%r10
	xorq	%r11,%r11
	leaq	8(%rsp),%rax
	.byte	0xf3,0xc3

.globl	OPENSSL_ia32_rdrand
.def	OPENSSL_ia32_rdrand;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_ia32_rdrand:
	movl	$8,%ecx
.Loop_rdrand:
.byte	72,15,199,240
	jc	.Lbreak_rdrand
	loop	.Loop_rdrand
.Lbreak_rdrand:
	cmpq	$0,%rax
	cmoveq	%rcx,%rax
	.byte	0xf3,0xc3


.globl	OPENSSL_ia32_rdseed
.def	OPENSSL_ia32_rdseed;	.scl 2;	.type 32;	.endef
.p2align	4
OPENSSL_ia32_rdseed:
	movl	$8,%ecx
.Loop_rdseed:
.byte	72,15,199,248
	jc	.Lbreak_rdseed
	loop	.Loop_rdseed
.Lbreak_rdseed:
	cmpq	$0,%rax
	cmoveq	%rcx,%rax
	.byte	0xf3,0xc3

