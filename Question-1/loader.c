#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    struct bpf_object *obj;
    int err;

    obj = bpf_object__open_file("proc_port_filter.bpf.o", NULL);
    if (!obj) {
        printf("open failed\n");
        return 1;
    }

    err = bpf_object__load(obj);
    if (err) {
        printf("load failed\n");
        return 1;
    }

    int port_map = bpf_object__find_map_fd_by_name(obj, "allowed_port");
    int comm_map = bpf_object__find_map_fd_by_name(obj, "allowed_comm");

    __u32 key = 0;
    __u16 port = 4040;
    char comm[16] = "myprocess";

    bpf_map_update_elem(port_map, &key, &port, 0);
    bpf_map_update_elem(comm_map, &key, comm, 0);

    printf("eBPF loaded successfully\n");
    pause();
    return 0;
}
