/**
 * this will be used for next be linked with
 * androib module driver
 * for VB toolgate 
*/  

#define IN_RING0 // it is necessaty for code for R0 compiling
#define VBOX_WITH_HGCM
#include <VBox/VMMDev.h>
#include <VBox/VMMDev2.h>
#include <VBox/VBoxGuest.h>
//#include "hello.h"
//#include <linux/types.h>
void * memcpy ( void * destination, const void * source, size_t num );

static long vb_host_connect(struct file *, unsigned long);

static unsigned int L_IOC_SIZE( unsigned int uCmd){
    return (unsigned int)vmmdevGetRequestSize(uCmd);
}


static int common_HGCM_ioctl( uint32_t uCmd,void* memory1, void* memory2 ){
    switch (uCmd){
        case VBOXGUEST_IOCTL_HGCM_CONNECT:
            VBoxGuestCommonIOCtl_HGCMConnect(memory1, memory2);
            break;
        default:
            break;
    }
return 0;
   

}


static void VBoxGuestCommonIOCtl_HGCMConnect( void* memory1, void* memory2){
    VMMDevHGCMConnect *pReq = (VMMDevHGCMConnect *)memory2;
    VBoxGuestHGCMConnectInfo *pConnectInfo = (VBoxGuestHGCMConnectInfo *) memory1;
    VMMDevRequestHeader *temp = ( VMMDevRequestHeader*) pReq;
    temp->size        = sizeof (VMMDevHGCMConnect);
    temp->version     = VMMDEV_REQUEST_HEADER_VERSION;
    temp->requestType = VMMDevReq_HGCMConnect;
    temp->rc          = VERR_GENERAL_FAILURE;
    temp->reserved1   = 0;
    temp->reserved2   = 0;
    pReq->header.fu32Flags = 0;
    memcpy (&pReq->loc, &pConnectInfo->Loc, sizeof (HGCMServiceLocation));
    pReq->u32ClientID = 0;  
}
