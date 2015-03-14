#ifndef _HELLO_
#define _HELLO_

#define DEV_NAME "hello"
#include <linux/types.h>
#include <linux/semaphore.h>  

#define DEVICE_BUFFER_SIZE  ( 4*1024*1024 )
struct fake_device
{
    char *data;
    struct semaphore sem;
    loff_t len;
    struct cdev mcdev;
};


static int device_open( struct inode * , struct file* );
static ssize_t device_read( struct file* ,
                            char* ,
                            size_t ,
                            loff_t*);
static ssize_t device_write( struct file* ,
                             const char* ,
                             size_t ,
                             loff_t* );
static long device_ioctl(struct file *, unsigned int, unsigned long);
static int device_close(struct inode *, struct file *);

static long vb_host_connect(struct file *, unsigned long);


// this is functions from cpp lib
static unsigned int L_IOC_SIZE( unsigned int);
static int common_HGCM_ioctl( uint32_t ,void* , void*);

#endif // _HELLO_
