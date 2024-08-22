#include <assert.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

typedef struct {
    int32_t command;
    int32_t data;
    int8_t isBusy;
} MyHardwareGadget;

void SendCommand(MyHardwareGadget* gadget, int command, int data)
{
    // wait while the gadget is busy:
    while (gadget->isBusy) {
    }

    // set data first before starting the action
    gadget->data = data;

    // writing the command starts the action
    gadget->command = command;
}

int main()
{
    int fd = open("dev.bin", O_RDWR);
    assert(fd >= 0);

    MyHardwareGadget* gadget = (MyHardwareGadget*) mmap(NULL, sizeof(MyHardwareGadget), 
                                                        PROT_READ | PROT_WRITE, MAP_SHARED, 
                                                        fd, 0);
    assert(gadget != MAP_FAILED);

    printf("dev->cmd : %d\ndev->data: %d\ndev->busy: %d\n", 
           gadget->command, gadget->data, gadget->isBusy);

    SendCommand(gadget, 0x41, 0x42);
}
