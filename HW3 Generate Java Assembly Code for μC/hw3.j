.source hw3.j
.class public Main
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	ldc 0
	istore 0
	iload 0
	ldc	0
	istore 0
	iload 0
	ldc	10
	ifeq L_for_exit_-1
	iload 0
	ldc 1
	iadd
	istore 0
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 0
	ldc	1
	istore 0
L_for_begin_0 :
	iload 0
	ldc	0
	isub
	ifgt L_cmp_0
	iconst_0
	goto L_cmp_1
L_cmp_0:
	iconst_1
L_cmp_1:
	ifeq L_for_exit_0
	iload 0
	ldc 1
	isub
	istore 0
	ldc	3
	newarray int
	astore 0
	aload 10
	ldc	0
	iaload
	ldc	1
	ldc	21
	iadd
	iastore
	aload 10
	ldc	1
	iaload
	aload 10
	ldc	0
	iaload
	ldc	1
	isub
	iastore
	aload 10
	ldc	2
	iaload
	aload 10
	ldc	1
	iaload
	ldc	3
	idiv
	iastore
	aload 10
	ldc	2
	iaload
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	ldc	3
	ldc	4
	ldc	5
	ldc	8
	ineg
	iadd
	imul
	isub
	ldc	10
	ldc	7
	idiv
	isub
	ldc	4
	ineg
	ldc	3
	irem
	isub
	ifgt L_cmp_2
	iconst_0
	goto L_cmp_3
L_cmp_2:
	iconst_1
L_cmp_3:
	iconst_1
	iconst_1
	ixor
	iconst_0
	iconst_1
	ixor
	iconst_1
	ixor
	iand
	ior
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	ifne L_cmp_4
	ldc "false"
	goto L_cmp_5
L_cmp_4:
	ldc "true"
L_cmp_5:
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	ldc	"\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	ldc	3
	newarray float
	astore 1
	aload 11
	ldc	0
	faload
	ldc	1.100000
	ldc	2.100000
	fadd
	fastore
	aload 11
	ldc	0
	faload
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(F)V
	ldc	"\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	goto L_for_begin_0
L_for_exit_0 :
	ldc 0
	istore 1
	iload 1
	ldc	10
	istore 1
L_for_begin_1 :
	iload 1
	ldc	0
	isub
	ifgt L_cmp_6
	iconst_0
	goto L_cmp_7
L_cmp_6:
	iconst_1
L_cmp_7:
	ifeq L_for_exit_1
	iload 1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"\t"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 1
	ldc 1
	isub
	istore 1
	iload 1
	ldc	0
	ifeq L_for_exit_1
	ldc	3.140000
	fstore 20
	fload 20
	iload 1
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(F)V
	ldc	6.600000
	fstore 20
	ldc	"If x == "
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	ldc	0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	fload 20
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(F)V
	ldc	1
	istore 10
L_for_begin_2 :
	iload 10
	ldc	3
	ifeq L_for_exit_2
	ldc	"\t"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"*"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 10
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"="
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 1
	iload 10
	imul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(I)V
	ldc	"\t"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload 10
	ldc 1
	iadd
	istore 10
	goto L_for_begin_2
L_for_exit_2 :
	ldc	"\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	goto L_for_begin_1
L_for_exit_1 :
	return
.end method
