#pragma once
#include <string>

namespace bpftrace {

typedef unsigned long long ull;

struct call_vmm_arg_t
{
  call_vmm_arg_t(ull rax = 0,
                 ull rbx = 0,
                 ull rcx = 0,
                 ull rdx = 0,
                 ull rsi = 0,
                 ull rdi = 0,
                 ull r8 = 0)
      : rax(rax), rbx(rbx), rcx(rcx), rdx(rdx), rsi(rsi), rdi(rdi), r8(r8)
  {
  }
  ull rax, rbx, rcx, rdx, rsi, rdi, r8;
};

struct call_vmm_ret_t
{
  call_vmm_ret_t(ull rax = 0,
                 ull rbx = 0,
                 ull rcx = 0,
                 ull rdx = 0,
                 ull rsi = 0,
                 ull rdi = 0,
                 ull r8 = 0)
      : rax(rax), rbx(rbx), rcx(rcx), rdx(rdx), rsi(rsi), rdi(rdi), r8(r8)
  {
  }
  ull rax, rbx, rcx, rdx, rsi, rdi, r8;
};

call_vmm_ret_t vmcall(call_vmm_arg_t &arg);
ull get_vmcall_id(const std::string name);

} // namespace bpftrace
