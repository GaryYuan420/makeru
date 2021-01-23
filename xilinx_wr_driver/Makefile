

ROOTFS_DIR = /home/z/nfs/drv

APP_NAME = pcie_tmp

ifeq ($(KERNELRELEASE), )

KERNEL_DIR = /media/z/plusfile/linux-xlnx-xilinx-v2017.3
#/media/z/plusfile/linux-xlnx-xilinx-v2017.3
#/media/z/plusfile/linux-xlnx-xilinx-v2016.2
CUR_DIR = $(shell pwd)

all :
	make -C  $(KERNEL_DIR) M=$(CUR_DIR) modules
	#$(CC) $(APP_NAME).c  -o $(APP_NAME)
app :
	arm-xilinx-linux-gnueabi-gcc $(APP_NAME).c -o $(APP_NAME) -lpcap -lpthread -L/home/z/arm_pcap/lib -I/home/z/arm_pcap/include  -static
clean :
	make -C  $(KERNEL_DIR) M=$(CUR_DIR) clean
	rm $(APP_NAME)
install:
	cp -raf *.ko $(APP_NAME)   $(ROOTFS_DIR)
	#cp -raf *.ko  $(ROOTFS_DIR)

else

obj-m += pcie_drv.o
#obj-m += pcie_test.o


endif
