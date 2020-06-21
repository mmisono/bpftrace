; ModuleID = 'bpftrace'
source_filename = "bpftrace"
target datalayout = "e-m:e-p:64:64-i64:64-n32:64-S128"
target triple = "bpf-pc-linux"

%printf_t = type { i64, i64, i64, i64, i64 }

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

define i64 @BEGIN(i8*) section "s_BEGIN_1" {
entry:
  %"struct Foo.m16" = alloca i32
  %"||_result15" = alloca i64
  %"struct Foo.m8" = alloca i32
  %"||_result" = alloca i64
  %"struct Foo.m6" = alloca i32
  %"&&_result5" = alloca i64
  %"struct Foo.m" = alloca i32
  %"&&_result" = alloca i64
  %printf_args = alloca %printf_t
  %"$foo" = alloca [4 x i8]
  %1 = bitcast [4 x i8]* %"$foo" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %1)
  %2 = bitcast [4 x i8]* %"$foo" to i8*
  call void @llvm.memset.p0i8.i64(i8* align 1 %2, i8 0, i64 4, i1 false)
  %3 = bitcast [4 x i8]* %"$foo" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %3)
  %4 = bitcast [4 x i8]* %"$foo" to i8*
  %5 = bitcast i64 0 to i8 addrspace(64)*
  call void @llvm.memcpy.p0i8.p64i8.i64(i8* align 1 %4, i8 addrspace(64)* align 1 %5, i64 4, i1 false)
  %6 = bitcast %printf_t* %printf_args to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %6)
  %7 = bitcast %printf_t* %printf_args to i8*
  call void @llvm.memset.p0i8.i64(i8* align 1 %7, i8 0, i64 40, i1 false)
  %8 = getelementptr %printf_t, %printf_t* %printf_args, i32 0, i32 0
  store i64 0, i64* %8
  %9 = bitcast i64* %"&&_result" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %9)
  %10 = add [4 x i8]* %"$foo", i64 0
  %11 = bitcast i32* %"struct Foo.m" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %11)
  %probe_read = call i64 inttoptr (i64 4 to i64 (i32*, i32, [4 x i8]*)*)(i32* %"struct Foo.m", i32 4, [4 x i8]* %10)
  %12 = load i32, i32* %"struct Foo.m"
  %13 = bitcast i32* %"struct Foo.m" to i8*
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* %13)
  %lhs_true_cond = icmp ne i32 %12, 0
  br i1 %lhs_true_cond, label %"&&_lhs_true", label %"&&_false"

"&&_lhs_true":                                    ; preds = %entry
  br i1 false, label %"&&_true", label %"&&_false"

"&&_true":                                        ; preds = %"&&_lhs_true"
  store i64 1, i64* %"&&_result"
  br label %"&&_merge"

"&&_false":                                       ; preds = %"&&_lhs_true", %entry
  store i64 0, i64* %"&&_result"
  br label %"&&_merge"

"&&_merge":                                       ; preds = %"&&_false", %"&&_true"
  %14 = load i64, i64* %"&&_result"
  %15 = getelementptr %printf_t, %printf_t* %printf_args, i32 0, i32 1
  store i64 %14, i64* %15
  %16 = bitcast i64* %"&&_result5" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %16)
  br i1 true, label %"&&_lhs_true1", label %"&&_false3"

"&&_lhs_true1":                                   ; preds = %"&&_merge"
  %17 = add [4 x i8]* %"$foo", i64 0
  %18 = bitcast i32* %"struct Foo.m6" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %18)
  %probe_read7 = call i64 inttoptr (i64 4 to i64 (i32*, i32, [4 x i8]*)*)(i32* %"struct Foo.m6", i32 4, [4 x i8]* %17)
  %19 = load i32, i32* %"struct Foo.m6"
  %20 = bitcast i32* %"struct Foo.m6" to i8*
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* %20)
  %rhs_true_cond = icmp ne i32 %19, 0
  br i1 %rhs_true_cond, label %"&&_true2", label %"&&_false3"

"&&_true2":                                       ; preds = %"&&_lhs_true1"
  store i64 1, i64* %"&&_result5"
  br label %"&&_merge4"

"&&_false3":                                      ; preds = %"&&_lhs_true1", %"&&_merge"
  store i64 0, i64* %"&&_result5"
  br label %"&&_merge4"

"&&_merge4":                                      ; preds = %"&&_false3", %"&&_true2"
  %21 = load i64, i64* %"&&_result5"
  %22 = getelementptr %printf_t, %printf_t* %printf_args, i32 0, i32 2
  store i64 %21, i64* %22
  %23 = bitcast i64* %"||_result" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %23)
  %24 = add [4 x i8]* %"$foo", i64 0
  %25 = bitcast i32* %"struct Foo.m8" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %25)
  %probe_read9 = call i64 inttoptr (i64 4 to i64 (i32*, i32, [4 x i8]*)*)(i32* %"struct Foo.m8", i32 4, [4 x i8]* %24)
  %26 = load i32, i32* %"struct Foo.m8"
  %27 = bitcast i32* %"struct Foo.m8" to i8*
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* %27)
  %lhs_true_cond10 = icmp ne i32 %26, 0
  br i1 %lhs_true_cond10, label %"||_true", label %"||_lhs_false"

"||_lhs_false":                                   ; preds = %"&&_merge4"
  br i1 false, label %"||_true", label %"||_false"

"||_false":                                       ; preds = %"||_lhs_false"
  store i64 0, i64* %"||_result"
  br label %"||_merge"

"||_true":                                        ; preds = %"||_lhs_false", %"&&_merge4"
  store i64 1, i64* %"||_result"
  br label %"||_merge"

"||_merge":                                       ; preds = %"||_true", %"||_false"
  %28 = load i64, i64* %"||_result"
  %29 = getelementptr %printf_t, %printf_t* %printf_args, i32 0, i32 3
  store i64 %28, i64* %29
  %30 = bitcast i64* %"||_result15" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %30)
  br i1 false, label %"||_true13", label %"||_lhs_false11"

"||_lhs_false11":                                 ; preds = %"||_merge"
  %31 = add [4 x i8]* %"$foo", i64 0
  %32 = bitcast i32* %"struct Foo.m16" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* %32)
  %probe_read17 = call i64 inttoptr (i64 4 to i64 (i32*, i32, [4 x i8]*)*)(i32* %"struct Foo.m16", i32 4, [4 x i8]* %31)
  %33 = load i32, i32* %"struct Foo.m16"
  %34 = bitcast i32* %"struct Foo.m16" to i8*
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* %34)
  %rhs_true_cond18 = icmp ne i32 %33, 0
  br i1 %rhs_true_cond18, label %"||_true13", label %"||_false12"

"||_false12":                                     ; preds = %"||_lhs_false11"
  store i64 0, i64* %"||_result15"
  br label %"||_merge14"

"||_true13":                                      ; preds = %"||_lhs_false11", %"||_merge"
  store i64 1, i64* %"||_result15"
  br label %"||_merge14"

"||_merge14":                                     ; preds = %"||_true13", %"||_false12"
  %35 = load i64, i64* %"||_result15"
  %36 = getelementptr %printf_t, %printf_t* %printf_args, i32 0, i32 4
  store i64 %35, i64* %36
  %pseudo = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %get_cpu_id = call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, i64, i64, %printf_t*, i64)*)(i8* %0, i64 %pseudo, i64 %get_cpu_id, %printf_t* %printf_args, i64 40)
  %37 = bitcast %printf_t* %printf_args to i8*
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* %37)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p64i8.i64(i8* nocapture writeonly, i8 addrspace(64)* nocapture readonly, i64, i1) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
