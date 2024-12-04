#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Borysenko Tamila, IO-25");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint myparam = 1;

module_param(myparam, uint, 0644);
MODULE_PARM_DESC(myparam, "The number of times to print the message 'Hello, world!'");

static int __init hello2_init(void)
{
	pr_info("Module hello2 loaded\n");
	print_hello(myparam);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Module hello2 unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);