#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/delay.h>  
#include <linux/spinlock.h>  
#include <linux/spinlock_types.h>  


static unsigned int dev_major = 55;
static int i = 0;
struct pcie_desc{
	//unsigned int dev_major;
	struct class *cls;
	struct device *dev;
	void *bar0_read;
	void *bar0_write;
	void *bar0_status;
	void *bar1_read;
	void *bar1_write;
	void *bar2_speed_status;
	void *bar2_available_status;
	void *bar2_mac_status;
	void *bar2_mac_addr;
	void *bar2_alarm_status;
	void *bar2_alarm_data;
};

spinlock_t s_lock;

struct pcie_desc *pcie_dev;

#define BAR2_SPEED_STATUS_ADDR 0x70000000

#define BAR2_AVAILABLE_STATUS_ADDR 0x70000001

#define BAR2_MAC_STATUS_ADDR 0x70000004

#define BAR2_MAC_ADDR 0x70000006

#define BAR2_ALARM_STATUS_ADDR 0x70000400

#define BAR2_ALARM_DATA_ADDR 0x70000401

#define BAR1_READ_ADDR 0x60010000

#define BAR1_WRITE_ADDR 0x60000000

#define BAR0_STATUS_ADDR 0x58000010

#define BAR0_READ_ADDR 0x58000008

#define BAR0_WRITE_ADDR 0x58000000
 
#define DATA_SIZE 65536

#define REGISTER_SIZE 4

#define STATUS_SIZE 1

#define MAC_SIZE 6

#define READED_FLAG 2


#define PCIE_SPEED_STATUS  0x100
#define PCIE_AVAILABLE_STATUS  0x101
#define PCIE_READ_SPEED  0x102
#define PCIE_READ_AVAILABLE  0x103
#define SET_MAC  0x104
#define ALARM_RW 0x105
#define ALARM_RW_DEBUG 0x106

static int pcie_drv_open(struct inode *inode, struct file *filp)
{
	//printk("-------%s-------\n", __FUNCTION__);
	
	return 0;
}


static int pcie_drv_close(struct inode *inode, struct file *filp)
{
	//printk("-------%s-------\n", __FUNCTION__);
	return 0;

}


static long pcie_drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ioctl_ret;
	//printk("-------%s-------\n", __FUNCTION__);
	switch (cmd)
		{
		case PCIE_SPEED_STATUS:
			ioctl_ret = copy_from_user(pcie_dev->bar2_speed_status,  (int *)arg, 1);
			break;

		case PCIE_AVAILABLE_STATUS:
			ioctl_ret = copy_from_user(pcie_dev->bar2_available_status,  (int *)arg, 1);
			break;
			
		case PCIE_READ_SPEED:
			ioctl_ret = copy_to_user((int *)arg, pcie_dev->bar2_speed_status, 1);
			break;
		
		case PCIE_READ_AVAILABLE:
			ioctl_ret = copy_to_user((int *)arg, pcie_dev->bar2_available_status, 1);
			break;

		case SET_MAC:
			if( (readb(pcie_dev->bar2_mac_status) & 0xff)  != 1)
			{
				//printk("status is %d\n", (readl(pcie_dev->bar2_mac_status) & 0xff));
				return -1;
			}
			//printk("status is %d", readl(pcie_dev->bar2_mac_status));
			ioctl_ret = copy_to_user((char *)arg, pcie_dev->bar2_mac_addr, 6);
			writeb( READED_FLAG , pcie_dev->bar2_mac_status );
			break;

		
		case ALARM_RW:
			if( (readb(pcie_dev->bar2_alarm_status) & 0xff)  != 1)
			{
				//printk("status is %d\n", (readl(pcie_dev->bar2_mac_status) & 0xff));
				return -1;
			}
			printk("ALARM_RW data is %d\n", readb(pcie_dev->bar2_alarm_data));
			ioctl_ret = copy_to_user((char *)arg, pcie_dev->bar2_alarm_data, 1);
			writeb( 0 , pcie_dev->bar2_alarm_status );
			break;

			
		case ALARM_RW_DEBUG:
			printk("alarm_status is %d\n", (readb(pcie_dev->bar2_alarm_status) & 0xff));
			//printk("status is %d", readl(pcie_dev->bar2_mac_status));
			ioctl_ret = copy_from_user(pcie_dev->bar2_alarm_data,  (char *)arg , 1);
			printk("ALARM_RW_DEBUG data is %d\n", readb(pcie_dev->bar2_alarm_data));
			writeb( 1 , pcie_dev->bar2_alarm_status );
			break;
		
		default:
		return -ENOTTY;
		}
	return ioctl_ret;

}





//  read(fd, buf, size);
static ssize_t pcie_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *fpos)
{

	int r_ret;
	u32 status;
	u32 bar0_RdValue;
	u32 offset;
	u32 size;

	status =( readl(pcie_dev->bar0_status) & 0x01);
	if(status == 1){
		//printk("read empty\n");
		return -EFAULT;
	}
	bar0_RdValue = readl(pcie_dev->bar0_read);
	
	offset = (bar0_RdValue & 0xffff0000) >>16;
	size = bar0_RdValue & 0x0000ffff;
	r_ret = copy_to_user(buf, &bar0_RdValue, 4);
	r_ret = copy_to_user(buf + 4, pcie_dev->bar1_read + offset, size);
	//printk("bar0_RrValue %lx,offset %lx,size %x\n",bar0_RdValue , offset,size);
	if(r_ret > 0)
	{
		printk("copy_to_user error\n");
		return -EFAULT;
	}

	return 0;

}

static ssize_t pcie_drv_write(struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
	int w_ret;
	u32 offset , size , bar0_WrValue;
	//int status;
	while( 2 ==  (readl(pcie_dev->bar0_status) & 0x02)){
		printk("wait\n");
		//return -EFAULT;
	}
	//udelay(100);
	//printk("on\n");
	spin_lock(&s_lock); 
	i ++;
	offset = (i%32) * 0x600;
	size = count;
	bar0_WrValue = (offset << 16) + size;
	//printk("bar0_WrValue %lx,offset %lx,i %x\n",bar0_WrValue , offset,i);
	//status =( readl(pcie_dev->bar0_status) & 0x02);
	
	w_ret = copy_from_user(pcie_dev->bar1_write + offset,  buf, size);
	if(w_ret > 0)
	{
		printk("copy_to_user error\n");
		spin_unlock(&s_lock);   //释放锁
		return -EFAULT;
	}
	writel( bar0_WrValue, pcie_dev->bar0_write );
	spin_unlock(&s_lock);   //释放锁
	printk("on\n");
	return 0;
	
}



const struct file_operations my_fops = {
	.open = pcie_drv_open,
	.read = pcie_drv_read,
	.write = pcie_drv_write,
	.release = pcie_drv_close,
	.unlocked_ioctl = pcie_drv_ioctl,
};

static int __init pcie_dev_init(void){
	static int ret;
	//u32 value;
	
	printk("----lock_print_1220_ioremap----\n",__FUNCTION__);

	pcie_dev = kmalloc(sizeof(struct pcie_desc),GFP_KERNEL);
	if(pcie_dev == NULL){
		printk(KERN_ERR "malloc error\n");
		return -ENOMEM;
	}
	
	ret = register_chrdev(dev_major, "pcie_drv", &my_fops);
	if(ret == 0){
		printk("register ok\n");
	}else{
		printk("register failed\n");
		return -EINVAL;
	}

	pcie_dev->cls = class_create(THIS_MODULE, "pcie_cls");
	if(IS_ERR(pcie_dev->cls))
	{
		printk(KERN_ERR "class_create error\n");
		ret = PTR_ERR(pcie_dev->cls); //将指针出错的具体原因转换成一个出错码
		goto err1;
	}

	// /dev/chr2
	pcie_dev->dev = device_create(pcie_dev->cls, NULL, 
							MKDEV(dev_major, 0), NULL, "pcie_drv");
	if(IS_ERR(pcie_dev->dev))
	{
		printk(KERN_ERR "device_create error\n");
		ret = PTR_ERR(pcie_dev->dev); //将指针出错的具体原因转换成一个出错码
		goto err2;
	}

	spin_lock_init(&s_lock);

	pcie_dev->bar0_read  = ioremap(BAR0_READ_ADDR, REGISTER_SIZE);
		if(pcie_dev->bar0_read == NULL)
	{
		printk(KERN_ERR "ioremap BAR0_READ_ADDR error\n");
		ret = -ENOMEM;
		goto err3;
	}

	
	pcie_dev->bar0_write  = ioremap(BAR0_WRITE_ADDR, REGISTER_SIZE);
		if(pcie_dev->bar0_write == NULL)
	{
		printk(KERN_ERR "ioremap BAR0_WRITE_ADDR error\n");
		ret = -ENOMEM;
		goto err3;
	}

	
	pcie_dev->bar0_status  = ioremap(BAR0_STATUS_ADDR,REGISTER_SIZE);
		if(pcie_dev->bar0_status == NULL)
	{
		printk(KERN_ERR "ioremap BAR0_STATUS_ADDR error\n");
		ret = -ENOMEM;
		goto err3;
	}

	pcie_dev->bar1_read  = ioremap(BAR1_READ_ADDR,DATA_SIZE);
		if(pcie_dev->bar1_read == NULL)
	{
		printk(KERN_ERR "ioremap BAR1_READ_ADDR error\n");
		ret = -ENOMEM;
		goto err3;
	}
	pcie_dev->bar1_write  = ioremap(BAR1_WRITE_ADDR,DATA_SIZE);
		if(pcie_dev->bar1_read == NULL)
	{
		printk(KERN_ERR "ioremap BAR1_READ_ADDR error\n");
		ret = -ENOMEM;
		goto err3;
	}

	pcie_dev->bar2_speed_status  = ioremap(BAR2_SPEED_STATUS_ADDR,STATUS_SIZE);
		if(pcie_dev->bar2_speed_status == NULL)
	{
		printk(KERN_ERR "ioremap bar2_speed_status error\n");
		ret = -ENOMEM;
		goto err3;
	}

	pcie_dev->bar2_available_status  = ioremap(BAR2_AVAILABLE_STATUS_ADDR,STATUS_SIZE);
		if(pcie_dev->bar2_available_status == NULL)
	{
		printk(KERN_ERR "ioremap bar2_available_status error\n");
		ret = -ENOMEM;
		goto err3;
	}
	
		pcie_dev->bar2_mac_status  = ioremap(BAR2_MAC_STATUS_ADDR,STATUS_SIZE);
		if(pcie_dev->bar2_mac_status == NULL)
	{
		printk(KERN_ERR "ioremap bar2_mac_status error\n");
		ret = -ENOMEM;
		goto err3;
	}

	
		pcie_dev->bar2_mac_addr  = ioremap(BAR2_MAC_ADDR,MAC_SIZE);
		if(pcie_dev->bar2_mac_addr == NULL)
	{
		printk(KERN_ERR "ioremap bar2_mac_addr error\n");
		ret = -ENOMEM;
		goto err3;
	}

		
		pcie_dev->bar2_alarm_status  = ioremap(BAR2_ALARM_STATUS_ADDR,STATUS_SIZE);
		if(pcie_dev->bar2_alarm_status == NULL)
	{
		printk(KERN_ERR "ioremap bar2_alarm_status error\n");
		ret = -ENOMEM;
		goto err3;
	}


		pcie_dev->bar2_alarm_data  = ioremap(BAR2_ALARM_DATA_ADDR,STATUS_SIZE);
		if(pcie_dev->bar2_alarm_data == NULL)
	{
		printk(KERN_ERR "ioremap bar2_alarm_data error\n");
		ret = -ENOMEM;
		goto err3;
	}

	
	return 0;


err3:

	device_destroy(pcie_dev->cls,  MKDEV(dev_major, 0));
err2:

	class_destroy(pcie_dev->cls);
err1:

	unregister_chrdev(dev_major, "pcie_dev");


	kfree(pcie_dev);

	return ret;
}


static void __exit pcie_dev_exit(void){
	printk("----%s----\n",__FUNCTION__);
	iounmap(pcie_dev->bar2_alarm_status);
	iounmap(pcie_dev->bar2_alarm_data);
	iounmap(pcie_dev->bar2_mac_status);
	iounmap(pcie_dev->bar2_mac_addr);
	iounmap(pcie_dev->bar2_speed_status);
	iounmap(pcie_dev->bar2_available_status);
	iounmap(pcie_dev->bar1_read);
	iounmap(pcie_dev->bar1_write);
	iounmap(pcie_dev->bar0_read);
	iounmap(pcie_dev->bar0_status);
	iounmap(pcie_dev->bar0_write);
	device_destroy(pcie_dev->cls,  MKDEV(dev_major, 0));
	class_destroy(pcie_dev->cls);
	unregister_chrdev(dev_major, "pcie_drv");
	kfree(pcie_dev);

}



	

module_init(pcie_dev_init);
module_exit(pcie_dev_exit);
MODULE_LICENSE("GPL");

