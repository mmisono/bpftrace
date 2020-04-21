#include "gtest/gtest.h"
#include "tracepoint_format_parser.h"

namespace bpftrace {
namespace test {
namespace tracepoint_format_parser {

class MockTracepointFormatParser : public TracepointFormatParser
{
public:
  static std::string get_tracepoint_struct_public(std::istream &format_file, const std::string &category, const std::string &event_name)
  {
    return get_tracepoint_struct(format_file, category, event_name);
  }
  static std::set<std::string> get_struct_name_in_tracepoint_struct_public(
      std::istream &format_file)
  {
    return get_struct_name_in_tracepoint_struct(format_file);
  }
};

TEST(tracepoint_format_parser, tracepoint_struct)
{
  std::string input =
    "name: sys_enter_read\n"
    "ID: 650\n"
    "format:\n"
    "	field:unsigned short common_type;	offset:0;	size:2;	signed:0;\n"
    "	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;\n"
    "	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;\n"
    "	field:int common_pid;	offset:4;	size:4;	signed:1;\n"
    "\n"
    "	field:int __syscall_nr;	offset:8;	size:4;	signed:1;\n"
    "	field:unsigned int fd;	offset:16;	size:8;	signed:0;\n"
    "	field:char * buf;	offset:24;	size:8;	signed:0;\n"
    "	field:size_t count;	offset:32;	size:8;	signed:0;\n"
    "\n"
    "print fmt: \"fd: 0x%08lx, buf: 0x%08lx, count: 0x%08lx\", ((unsigned long)(REC->fd)), ((unsigned long)(REC->buf)), ((unsigned long)(REC->count))\n";

  std::string expected = "struct _tracepoint_syscalls_sys_enter_read\n"
                         "{\n"
                         "  unsigned short common_type;\n"
                         "  unsigned char common_flags;\n"
                         "  unsigned char common_preempt_count;\n"
                         "  int common_pid;\n"
                         "  int __syscall_nr;\n"
                         "  char __pad_12;\n"
                         "  char __pad_13;\n"
                         "  char __pad_14;\n"
                         "  char __pad_15;\n"
                         "  u64 fd;\n"
                         "  char * buf;\n"
                         "  size_t count;\n"
                         "};\n";

  std::istringstream format_file(input);

  std::string result = MockTracepointFormatParser::get_tracepoint_struct_public(format_file, "syscalls", "sys_enter_read");

  EXPECT_EQ(expected, result);
}

TEST(tracepoint_format_parser, array)
{
  std::string input =
    "	field:char char_array[8];	offset:0;	size:8;	signed:1;\n"
    "	field:int int_array[2];	offset:8;	size:8;	signed:1;\n";

  std::string expected =
    "struct _tracepoint_syscalls_sys_enter_read\n"
    "{\n"
    "  char char_array[8];\n"
    "  int int_array[2];\n"
    "};\n";

  std::istringstream format_file(input);

  std::string result = MockTracepointFormatParser::get_tracepoint_struct_public(format_file, "syscalls", "sys_enter_read");

  EXPECT_EQ(expected, result);
}

TEST(tracepoint_format_parser, data_loc)
{
  std::string input = "	field:__data_loc char[] msg;	offset:8;	size:4;	signed:1;";

  std::string expected =
    "struct _tracepoint_syscalls_sys_enter_read\n"
    "{\n"
    "  int data_loc_msg;\n"
    "};\n";

  std::istringstream format_file(input);

  std::string result = MockTracepointFormatParser::get_tracepoint_struct_public(format_file, "syscalls", "sys_enter_read");

  EXPECT_EQ(expected, result);
}

TEST(tracepoint_format_parser, adjust_integer_types)
{
  std::string input =
    "	field:int arr[8];	offset:0;	size:32;	signed:1;\n"

    "	field:int int_a;	offset:0;	size:4;	signed:1;\n"
    "	field:int int_b;	offset:0;	size:8;	signed:1;\n"

    "	field:u32 u32_a;	offset:0;	size:4;	signed:0;\n"
    "	field:u32 u32_b;	offset:0;	size:8;	signed:0;\n"

    "	field:unsigned int uint_a;	offset:0;	size:4;	signed:0;\n"
    "	field:unsigned int uint_b;	offset:0;	size:8;	signed:0;\n"

    "	field:unsigned unsigned_a;	offset:0;	size:4;	signed:0;\n"
    "	field:unsigned unsigned_b;	offset:0;	size:8;	signed:0;\n"

    "	field:uid_t uid_a;	offset:0;	size:4;	signed:0;\n"
    "	field:uid_t uid_b;	offset:0;	size:8;	signed:0;\n"

    "	field:gid_t gid_a;	offset:0;	size:4;	signed:0;\n"
    "	field:gid_t gid_b;	offset:0;	size:8;	signed:0;\n"

    "	field:pid_t pid_a;	offset:0;	size:4;	signed:1;\n"
    "	field:pid_t pid_b;	offset:0;	size:8;	signed:0;\n";

  std::string expected =
    "struct _tracepoint_syscalls_sys_enter_read\n"
    "{\n"
    "  int arr[8];\n"

    "  int int_a;\n"
    "  s64 int_b;\n"

    "  u32 u32_a;\n"
    "  u64 u32_b;\n"

    "  unsigned int uint_a;\n"
    "  u64 uint_b;\n"

    "  unsigned unsigned_a;\n"
    "  u64 unsigned_b;\n"

    "  uid_t uid_a;\n"
    "  u64 uid_b;\n"

    "  gid_t gid_a;\n"
    "  u64 gid_b;\n"

    "  pid_t pid_a;\n"
    "  u64 pid_b;\n"
    "};\n";

  std::istringstream format_file(input);

  std::string result = MockTracepointFormatParser::get_tracepoint_struct_public(format_file, "syscalls", "sys_enter_read");

  EXPECT_EQ(expected, result);
}

TEST(tracepoint_format_parser, padding)
{
  std::string input =
      " field:unsigned short common_type;       offset:0;       size:2; "
      "signed:0;\n"
      " field:unsigned char common_flags;       offset:2;       size:1; "
      "signed:0;\n"
      " field:unsigned char common_preempt_count;       offset:3;       "
      "size:1; signed:0;\n"
      " field:int common_pid;   offset:4;       size:4; signed:1;\n"
      " field:unsigned char common_migrate_disable;     offset:8;       "
      "size:1; signed:0;\n"
      " field:unsigned char common_preempt_lazy_count;  offset:9;       "
      "size:1; signed:0;\n"

      " field:char comm[16];    offset:12;      size:16;        signed:1;\n"
      " field:pid_t pid;        offset:28;      size:4; signed:1;\n"
      " field:int prio; offset:32;      size:4; signed:1;\n"
      " field:int success;      offset:36;      size:4; signed:1;\n"
      " field:int target_cpu;   offset:40;      size:4; signed:1;\n";

  std::string expected = "struct _tracepoint_sched_sched_wakeup\n"
                         "{\n"
                         "  unsigned short common_type;\n"
                         "  unsigned char common_flags;\n"
                         "  unsigned char common_preempt_count;\n"
                         "  int common_pid;\n"
                         "  unsigned char common_migrate_disable;\n"
                         "  unsigned char common_preempt_lazy_count;\n"
                         "  char __pad_10;\n"
                         "  char __pad_11;\n"
                         "  char comm[16];\n"
                         "  pid_t pid;\n"
                         "  int prio;\n"
                         "  int success;\n"
                         "  int target_cpu;\n"
                         "};\n";

  std::istringstream format_file(input);

  std::string result = MockTracepointFormatParser::get_tracepoint_struct_public(
      format_file, "sched", "sched_wakeup");

  EXPECT_EQ(expected, result);
}

TEST(tracepoint_format_parser, sturct_name)
{
  // clang-format off
  std::string input =
    "name: sys_enter_io_pgetevents\n"
    "ID: 899\n"
    "format:\n"
    "	field:unsigned short common_type;	offset:0;	size:2;	signed:0;\n"
    "	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;\n"
    "	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;\n"
    "	field:int common_pid;	offset:4;	size:4;	signed:1;\n"
    "\n"
    "	field:int __syscall_nr;	offset:8;	size:4;	signed:1;\n"
    "	field:aio_context_t ctx_id;	offset:16;	size:8;	signed:0;\n"
    "	field:long min_nr;	offset:24;	size:8;	signed:0;\n"
    "	field:long nr;	offset:32;	size:8;	signed:0;\n"
    "	field:struct io_event * events;	offset:40;	size:8;	signed:0;\n"
    "	field:struct __kernel_timespec * timeout;	offset:48;	size:8;	signed:0;\n"
    "	field:const struct __aio_sigset * usig;	offset:56;	size:8;	signed:0;\n"
    "\n"
    "print fmt: \"ctx_id: 0x%08lx, min_nr: 0x%08lx, nr: 0x%08lx, events: 0x%08lx, timeout: 0x%08lx, usig: 0x%08lx\", ((unsigned long)(REC->ctx_id)), ((unsigned long)(REC->min_nr)), ((unsigned long)(REC->nr)), ((unsigned long)(REC->events)), ((unsigned long)(REC->timeout)), ((unsigned long)(REC->usig))\n";
  // clang-format on

  std::set<std::string> expected = { "struct io_event",
                                     "struct __kernel_timespec",
                                     "struct __aio_sigset" };

  std::istringstream format_file(input);

  std::set<std::string> result =
      MockTracepointFormatParser::get_struct_name_in_tracepoint_struct_public(
          format_file);

  EXPECT_EQ(expected, result);
}

} // namespace tracepoint_format_parser
} // namespace test
} // namespace bpftrace
