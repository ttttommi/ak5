#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Borysenko Tamila, IO-25");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_data {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(hello_list);

void print_hello(uint myparam)
{
	struct hello_data *entry;
	uint i;

	if (myparam == 0 || (myparam > 5 && myparam <= 10)) {
		pr_warn("Warning: myparam is 0 or between 5 and 10.\n");
	} else if (myparam > 10) {
		pr_err("Error: myparam is greater than 10. The module does not load.\n");
		return;
	}

	for (i = 0; i < myparam; i++) {
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry)
			return;

		entry->start_time = ktime_get();
		pr_info("Hello, world!\n");
		entry->end_time = ktime_get();
		list_add_tail(&entry->list, &hello_list);
	}
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Module hello1 loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_data *entry, *tmp;

	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		pr_info("Time: %lld\n",
			ktime_to_ns(
				ktime_sub(entry->end_time, entry->start_time)));
		list_del(&entry->list);
		kfree(entry);
	}
	pr_info("Module hello1 unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);