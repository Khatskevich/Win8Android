/*
 *  hello-1.c - Простейший модуль ядра.
 */
#include <linux/module.h>       /* Необходим для любого модуля ядра */
#include <linux/kernel.h>       /* Здесь находится определение KERN_ALERT */
#include <linux/types.h>
#include <linux/fs.h> 	        //file operations structure 
				//( pointers to open, read, write, close )
#include <asm/uaccess.h>     	//copy to/from user addrSpace
#include <linux/cdev.h>      	//char driver
#include <linux/semaphore.h>    //

#include <linux/slab.h>     //kmalloc()

//#include <VMMDev.h>
#include "hello.h" // includeing the main hello header file

//#include <sys/io.h>
#include <asm/io.h>







// #define DEBUG
#define BASEPORT (0xd020)



MODULE_LICENSE("Dual BSD/GPL");

VMMDevRequestHeader *temp;

static struct fake_device v_dev;
static struct fake_device* virtual_device= &v_dev;

static int major_number;
static dev_t dev_num;
static void* memory1;
static void* memory2;

struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_close,
    .write = device_write,
    .read = device_read,
    .unlocked_ioctl = device_ioctl
};

//static int driver_entry(void)
int driver_entry(void)
{
    int ret = 0;
    unsigned int count = 1, firstminor = 0;
    ret = alloc_chrdev_region( &dev_num, firstminor, count, DEV_NAME);
    if (ret < 0)
    {
        printk(KERN_ALERT "Hello world 1.\nres = %d\n", ret);
        return ret;
    }
    major_number = MAJOR(dev_num);
#ifdef DEBUG
    #define \
    printk(KERN_INFO "Hello world 1.\nmajor = %u\nminor = %u\n", \
           MAJOR(dev_num), \
           MINOR(dev_num) );
#endif
    // cdev initialization
    cdev_init(&virtual_device->mcdev, &fops);
    virtual_device->mcdev.ops = &fops;
    virtual_device->mcdev.owner = THIS_MODULE; // is it MACROS?
   
    virtual_device->data = (char*) kmalloc( DEVICE_BUFFER_SIZE , GFP_KERNEL); 
    
    virtual_device->len = 0;
    sema_init( &virtual_device->sem, 1); //semapthre initialization
    
    ret = cdev_add(&virtual_device->mcdev, dev_num, 1);
    if ( ret < 0)
    {
        printk(KERN_ALERT "hello: umable to add cdev to kernel");
        return ret;
    }
    
    
    memory1 = (void*) kmalloc( DEVICE_BUFFER_SIZE , GFP_KERNEL);
    memory2 = (void*) kmalloc( DEVICE_BUFFER_SIZE , GFP_KERNEL);
    
    return 0;
}

//static void driver_exit(void)
void driver_exit(void)
{
    kfree(virtual_device->data);
    kfree(memory1);
    kfree(memory2);
    cdev_del(&virtual_device->mcdev);
    unregister_chrdev_region( dev_num , 1);
    printk(KERN_ALERT "Goodbye world 1.\n");
}

// Macroses which are giving information about INIT and EXIT driver functions
module_init(driver_entry);
module_exit(driver_exit);

static int device_open( struct inode * inode, struct file* filp)
{
    struct fake_device * virtual_device;
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: open");
#endif
    filp->private_data = container_of(inode->i_cdev, struct fake_device , mcdev); 
    virtual_device = filp->private_data;
    
    if( down_interruptible(&virtual_device->sem) != 0)
    {
        printk(KERN_ALERT "hello: could not lock device during open");
        return -1;
    }
    printk(KERN_INFO "hello: opened device");




    
    
    return 0;
}

static ssize_t device_read( struct file* filp,
                            char* bufStoreData,
                            size_t bufCount,
                            loff_t* curOffset)
{
    struct fake_device * virtual_device;
    ssize_t ret = 0;
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: read\n");
#endif
    virtual_device = filp->private_data;
    if ( bufCount < 0) return -1;
    if ( *curOffset + bufCount > virtual_device->len )  // if read asks more
        bufCount = virtual_device->len - * curOffset;   // bytes then it is possible
    
    printk(KERN_INFO "hello: reading from device\n");
    if (copy_to_user(bufStoreData, virtual_device->data, bufCount) ){
        ret = -EFAULT;
        goto out;
    }

    *curOffset = *curOffset + bufCount;
    ret = bufCount;

out:
    return ret;
}


static ssize_t device_write( struct file* filp,
                             const char* bufSourceData,
                             size_t bufCount,
                             loff_t* curOffset)
{
    struct fake_device * virtual_device;
    int ret = 0;
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: write\n");
#endif
    virtual_device = filp->private_data;
    if ( bufCount < 0) return -1;
    if ( *curOffset + bufCount > DEVICE_BUFFER_SIZE )   // if read asks more
        bufCount = DEVICE_BUFFER_SIZE - * curOffset;   // bytes then it is possible
    
    printk(KERN_INFO "hello: writing to the device\n");
    if (copy_from_user(virtual_device->data, bufSourceData , bufCount)){
        ret = -EFAULT;
        goto out;
    }

    *curOffset = *curOffset + bufCount;   
    virtual_device->len = *curOffset;
    ret = bufCount;
out:
    return ret;
}


static long device_ioctl(struct file *filp, unsigned int UCmd, unsigned long UAddr)
{
    //struct fake_device * virtual_device;
    int ret = 0;
    //virtual_device = filp->private_data;
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: ioctl\n");
#endif
    uint32_t cbData   = L_IOC_SIZE(uCmd);
    copy_from_user( memory1 , (void*) Uaddr , cbData );
    ret = common_HGCM_ioctl(uCmd, memory1, memory2);
    return ret;
}


static int device_close( struct inode *inode, struct file *filp)
{
    struct fake_device * virtual_device;
    kfree(temp);
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: close");
#endif
    virtual_device = filp->private_data;
    up(&virtual_device->sem);
    printk(KERN_INFO "hello: closed device");
    return 0;
}


static long vb_host_connect(void * memory)
{
    int ret = 0;
    //ioperm(BASEPORT, 32, 1);
    //void *ioremap((unsigned long)temp, 4);
    //void iounmap(void *virt_addr);
    outl((unsigned long)temp, BASEPORT);
    //ioperm(BASEPORT, 32, 0);
    
#ifdef DEBUG
    #define \
    printk(KERN_ALERT "hello: ioctl: vb_host_connect\n");
#endif	
     return ret;
}

