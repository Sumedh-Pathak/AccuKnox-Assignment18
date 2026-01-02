#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

char LICENSE[] SEC("license") = "GPL";

#define TARGET_PORT 4040

SEC("cgroup/connect4")
int cg_connect4(struct bpf_sock_addr *ctx)
{
    char comm[16];

    bpf_get_current_comm(comm, sizeof(comm));

    if (comm[0]!='m'||comm[1]!='y'||comm[2]!='p'||
        comm[3]!='r'||comm[4]!='o'||comm[5]!='c'||
        comm[6]!='e'||comm[7]!='s'||comm[8]!='s')
        return 1;

    if (bpf_ntohs(ctx->user_port) != TARGET_PORT)
        return 0;

    return 1;
}

SEC("cgroup/connect6")
int cg_connect6(struct bpf_sock_addr *ctx)
{
    char comm[16];

    bpf_get_current_comm(comm, sizeof(comm));

    if (comm[0]!='m'||comm[1]!='y'||comm[2]!='p'||
        comm[3]!='r'||comm[4]!='o'||comm[5]!='c'||
        comm[6]!='e'||comm[7]!='s'||comm[8]!='s')
        return 1;

    if (bpf_ntohs(ctx->user_port) != TARGET_PORT)
        return 0;

    return 1;
}
