/*
 *  hello-1.c - Простейший модуль ядра.
 */
#include <linux/module.h>       /* Необходим для любого модуля ядра */
#include <linux/kernel.h>       /* Здесь находится определение KERN_ALERT */
#include <linux/types.h>
#include <linux/fs.h>         //file operations structure 
//( pointers to open, read, write, close )
#include <asm/uaccess.h>      //copy to/from user addrSpace
#include <linux/cdev.h>       //char driver
#include <linux/semaphore.h>    //
#include <linux/slab.h>


#include "hello.h"

MODULE_LICENSE("Dual BSD/GPL");


int device_open( struct inode * inode, struct file* flip)
{
        printk(KERN_ALERT "hello:  open");
    flip->private_data = container_of(inode->i_cdev, struct fake_device , mcdev); 
    struct fake_device * virtual_device;
    virtual_device = flip->private_data;
    
    if( down_interruptible(&virtual_device->sem) != 0)
    {
        printk(KERN_ALERT "hello: could not lock device during open");
        return -1;
    }
    printk(KERN_INFO "hello: opened device");
    return 0;
}

static ssize_t device_read( struct file* flip,
                            char* bufStoreData,
                            size_t bufCount,
                            loff_t* curOffset)
{
    printk(KERN_ALERT "hello:  read");
    struct fake_device * virtual_device;
    virtual_device = flip->private_data;
    int ret = 0;
    if ( bufCount < 0) return -1;
    if ( *curOffset + bufCount > virtual_device->len )  // if read asks more
        bufCount = virtual_device->len - * curOffset;   // bytes then it is possible
    
    printk(KERN_INFO "hello: reading from device");
    if ( bufCount <= 100)
    {
        ret = copy_to_user(bufStoreData, virtual_device->data, bufCount);
    }
    if ( ret > 0 )
        *curOffset = *curOffset + ret;
    return ret;
}


static ssize_t device_write( struct file* flip,
                             const char* bufSourceData,
                             size_t bufCount,
                             loff_t* curOffset)
{
    printk(KERN_ALERT "hello:  write");
    struct fake_device * virtual_device;
    virtual_device = flip->private_data;
    int ret = 0;
    if ( bufCount < 0) return -1;
    if ( *curOffset + bufCount > DEVICE_BUFFER_SIZE )   // if read asks more
        bufCount = DEVICE_BUFFER_SIZE - * curOffset;   // bytes then it is possible
    
    printk(KERN_INFO "hello: writing to the device");
    if ( bufCount <= 100)
    {
        ret = copy_from_user(virtual_device->data, bufSourceData , bufCount);
    }
    if ( ret == 0)
        return -1;

    if ( ret > 0){
        *curOffset = *curOffset + ret;   
        virtual_device->len = *curOffset;
        return 0;
    }

    return ret;
}

static int device_close( struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "hello:  close");

    struct fake_device * virtual_device;
    virtual_device = filp->private_data;
    up(&virtual_device->sem);
    printk(KERN_INFO "hello: closed device");
    return 0;
}


