#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/device.h>

struct cdev *mem_cdev;

int mem_open(struct inode *inode, struct file *filp)
{
    printk("mem_open\n");

    return 0;
}

ssize_t mem_write(struct file *filp, const char __user *buff, size_t length, loff_t *offset)
{
    printk("mem_write\n");

    int r;
    int _length;
    char buffer[128] = {0};
    r = copy_from_user(buffer, buff, length);
    if(r == 0)
    {
        printk("men_write:%s\n", buffer);
        _length = length;
    }
    else
    {
        printk("mem_write fail\n");
    }

    return _length;
}

ssize_t mem_read(struct file *filp, char __user *buff, size_t length, loff_t *offset)
{
    int r;
    int _length;
    r = copy_to_user(buff, " gyt I love you ", strlen(" gyt I love you "));
    if(r == 0)
    {
        printk("copy to user completed\n");
        _length = strlen(" gyt I love you ");
        printk("read data length: %zd\n", length);
    }
    else
    {
        printk("copy to user fail\n");
        _length = 0;
    }
    printk("mem_read\n");

    return _length;
}

int mem_release(struct inode *inode, struct file *filp)
{
    printk("men_release\n");

    return 0;
}

struct file_operations fops =
{
    .open = mem_open,
    .write = mem_write,
    .read = mem_read,
    .release = mem_release,
};

struct class *mem_class;

static int __init gtstore_init(void)
{
    /*mem_cdev = cdev_alloc();
    if(mem_cdev != NULL)
    {
        printk("state_in_sysfs:%d\n", mem_cdev->kobj.state_in_sysfs);
        printk("initialized:%d\n", mem_cdev->kobj.state_initialized);
        printk("add_uevent_sent:%d\n", mem_cdev->kobj.state_add_uevent_sent);
        printk("count:%d\n", mem_cdev->count);

        cdev_init(mem_cdev, &fops);
        mem_cdev->owner = THIS_MODULE;
        cdev_add(mem_cdev, MKDEV(12, 1), 1);
    }
    else
    {
        printk("mem_cdev alloc fail\n");
    }*/

    //static inline int register_chrdev(unsigned int major, const char *name,const struct file_operations *fops)
    int r;
    r = register_chrdev(12, "gtdev", &fops);
    if(r != 0)
    {
        printk("register gtdev fail\n");
        return -1;
    }

    mem_class = class_create(THIS_MODULE, "gtdev");
    if(IS_ERR(mem_class))
    {
        printk("create class fail\n");
    }
    else
    {
        printk("create class success\n");
    }

    device_create(mem_class, NULL, MKDEV(12, 0), NULL, "gtdev");

    printk("gtstore_init\n");

    return 0;
}

static void __exit gtstore_exit(void)
{
    /*if(mem_cdev != NULL)
    {
        cdev_del(mem_cdev);
        //kfree(mem_cdev);
    }*/

    device_destroy(mem_class, MKDEV(12, 0));

    unregister_chrdev(12, "gtdev");

    if(mem_class != NULL)
    {
        class_destroy(mem_class);
    }

    printk("gtstore_exit\n");
}

module_init(gtstore_init);
module_exit(gtstore_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("yite.gu");
