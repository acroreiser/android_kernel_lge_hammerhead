/* drivers/misc/lowmemorykiller.c
 *
 * Dummy stub module keeping sysfs parameters for compatibility with AOSP lmkd
 * while actual killing is handled by userspace (e.g. Marco).
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/stat.h>

static int lowmem_cost = 32; /* DEFAULT_SEEKS (2) * 16 */

static int lowmem_adj[6] = {
	0,
	1,
	6,
	12,
};
static int lowmem_adj_size = 4;

static unsigned int lowmem_minfree[6] = {
	3 * 512,	/* 6MB */
	2 * 1024,	/* 8MB */
	4 * 1024,	/* 16MB */
	16 * 1024,	/* 64MB */
};
static int lowmem_minfree_size = 4;

static unsigned int lowmem_kill_timeout_ms = 100;
static unsigned int lowmem_disable = 0;
static unsigned int lowmem_debug_level = 1;

module_param_named(cost, lowmem_cost, int, S_IRUGO | S_IWUSR);
module_param_array_named(adj, lowmem_adj, int, &lowmem_adj_size,
			 S_IRUGO | S_IWUSR);
module_param_array_named(minfree, lowmem_minfree, uint, &lowmem_minfree_size,
			 S_IRUGO | S_IWUSR);
module_param_named(kill_timeout_ms, lowmem_kill_timeout_ms, uint,
		   S_IRUGO | S_IWUSR);
module_param_named(disable, lowmem_disable, uint, S_IRUGO | S_IWUSR);
module_param_named(debug_level, lowmem_debug_level, uint, S_IRUGO | S_IWUSR);

static int __init lowmem_init(void)
{
	return 0;
}

static void __exit lowmem_exit(void)
{
}

module_init(lowmem_init);
module_exit(lowmem_exit);

MODULE_LICENSE("GPL");