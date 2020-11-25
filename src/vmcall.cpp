#include <string>
#include <sys/mman.h>

#include "vmcall.h"
namespace bpftrace {

// TODO: AMD (vmmcall) support

call_vmm_ret_t vmcall(call_vmm_arg_t &arg)
{
  call_vmm_ret_t ret = {};
  register ull r8 asm("r8") = arg.r8;

  asm volatile("vmcall"
               : "=a"(ret.rax),
                 "=b"(ret.rbx),
                 "=c"(ret.rcx),
                 "=d"(ret.rdx),
                 "=S"(ret.rsi),
                 "=D"(ret.rdi),
                 "=r"(ret.r8)
               : "a"(arg.rax),
                 "b"(arg.rbx),
                 "c"(arg.rcx),
                 "d"(arg.rdx),
                 "S"(arg.rsi),
                 "D"(arg.rdi),
                 "r"(r8)
               : "memory");

  return ret;
}

ull get_vmcall_id(const std::string name)
{
  mlock(name.c_str(), name.size());
  struct call_vmm_arg_t arg = {};
  arg.rax = 0;
  arg.rbx = (ull)name.c_str();
  auto ret = vmcall(arg);
  return ret.rax;
}

} // namespace bpftrace
