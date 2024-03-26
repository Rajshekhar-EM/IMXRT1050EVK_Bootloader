If i want to boot the device from any RAMs(ITC,DTC,NCACHE_REGION or etc) first i need to store the code in hyperflash to do this follow the below procedure
1. unlink the Bootloader project from RAM
2. debug the bootloader project using MCU Xpresso use simple led project to jump to application address
3. if you want to load Display project(i.e Big project) the link the bootloader project to RAM then execute 

This is because RAMs are volatile memories they lost their data whenever there is a power off(i.e they hold the data till there is a power on)
so here program should be stored in the hyperflash(non volatile memory) 
then whenever there is a power off and then power on data which is stored in hyperflash 
which will loaded to RAMs(which ever is configured)memory and start executing from that memory if bootloader project is linked to RAM otherwise it wont.