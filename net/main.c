#include "lib.h"
#include "tap.h"
#include "net.h"
#include "eth.h"
#include "arp.h"
#include "icmp.h"


pthread_t threads[4];

int newthread(pfunc_t thread_func)
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, thread_func, NULL)){
        perror("create thread failed");
    }
    return tid;
}

void net_stack_init(void)
{
    eth_init();
    arp_cache_init();
}

void net_stack_run(void)
{
    threads[0] = newthread((pfunc_t)eth_in);
    threads[1] = newthread((pfunc_t)net_timer);
    unsigned char ip[4] = {10,0,0,2};
    sleep(1);
    while (1)
    {
        // icmp_echo(ip);
        sleep(2);
    }
}

int main()
{
    net_stack_init();
    net_stack_run();
    return 0;
}