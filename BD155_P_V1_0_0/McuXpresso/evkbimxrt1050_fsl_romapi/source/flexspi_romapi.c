/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*****************USB related************************/
/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "usb_host_config.h"
#include "usb_host.h"
#include "fsl_device_registers.h"
#include "usb_host_msd.h"
#include "host_msd_fatfs.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
#include "fsl_sysmpu.h"
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

#if ((!USB_HOST_CONFIG_KHCI) && (!USB_HOST_CONFIG_EHCI) && (!USB_HOST_CONFIG_OHCI) && (!USB_HOST_CONFIG_IP3516HS))
#error Please enable USB_HOST_CONFIG_KHCI, USB_HOST_CONFIG_EHCI, USB_HOST_CONFIG_OHCI, or USB_HOST_CONFIG_IP3516HS in file usb_host_config.
#endif

#include "usb_phy.h"
#include "app.h"

extern uint8_t usb_attached;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief host callback function.
 *
 * device attach/detach callback function.
 *
 * @param deviceHandle        device handle.
 * @param configurationHandle attached device's configuration descriptor information.
 * @param eventCode           callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The application don't support the configuration.
 */
static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode);

/*!
 * @brief app initialization.
 */
static void USB_HostApplicationInit(void);

extern void USB_HostClockInit(void);
extern void USB_HostIsrEnable(void);
extern void USB_HostTaskFn(void *param);
void BOARD_InitHardware(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief USB host msd fatfs instance global variable */
extern usb_host_msd_fatfs_instance_t g_MsdFatfsInstance;
usb_host_handle g_HostHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

void USB_OTG1_IRQHandler(void)
{
    USB_HostEhciIsrFunction(g_HostHandle);
}

void USB_OTG2_IRQHandler(void)
{
    USB_HostEhciIsrFunction(g_HostHandle);
}

void USB_HostClockInit(void)
{
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    if (CONTROLLER_ID == kUSB_ControllerEhci0)
    {
        CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);
    }
    else
    {
        CLOCK_EnableUsbhs1PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs1Clock(kCLOCK_Usb480M, 480000000U);
    }
    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

void USB_HostIsrEnable(void)
{
    uint8_t irqNumber;

    uint8_t usbHOSTEhciIrq[] = USBHS_IRQS;
    irqNumber                = usbHOSTEhciIrq[CONTROLLER_ID - kUSB_ControllerEhci0];
/* USB_HOST_CONFIG_EHCI */

/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

void USB_HostTaskFn(void *param)
{
    USB_HostEhciTaskFunction(param);
}

/*!
 * @brief USB isr function.
 */

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
extern usb_status_t USB_HostTestEvent(usb_device_handle deviceHandle,
                                      usb_host_configuration_handle configurationHandle,
                                      uint32_t eventCode);
#endif

static usb_status_t USB_HostEvent(usb_device_handle deviceHandle,
                                  usb_host_configuration_handle configurationHandle,
                                  uint32_t eventCode)
{
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
    usb_host_configuration_t *configuration;
    usb_status_t status1;
    usb_status_t status2;
    uint8_t interfaceIndex = 0;
#endif
    usb_status_t status = kStatus_USB_Success;
    switch (eventCode & 0x0000FFFFU)
    {
        case kUSB_HostEventAttach:
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
            status1 = USB_HostTestEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 == kStatus_USB_NotSupported) && (status2 == kStatus_USB_NotSupported))
            {
                status = kStatus_USB_NotSupported;
            }
#else
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
#endif
            break;

        case kUSB_HostEventNotSupported:
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
            configuration = (usb_host_configuration_t *)configurationHandle;
            for (interfaceIndex = 0; interfaceIndex < configuration->interfaceCount; ++interfaceIndex)
            {
                if (((usb_descriptor_interface_t *)configuration->interfaceList[interfaceIndex].interfaceDesc)
                        ->bInterfaceClass == 9U) /* 9U is hub class code */
                {
                    break;
                }
            }

            if (interfaceIndex < configuration->interfaceCount)
            {
                usb_echo("unsupported hub\r\n");
            }
            else
            {
                usb_echo("Unsupported Device\r\n");
            }
#else
            usb_echo("Unsupported Device\r\n");
#endif
            break;

        case kUSB_HostEventEnumerationDone:
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
            status1 = USB_HostTestEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 != kStatus_USB_Success) && (status2 != kStatus_USB_Success))
            {
                status = kStatus_USB_Error;
            }
#else
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
#endif
            break;

        case kUSB_HostEventDetach:
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
            status1 = USB_HostTestEvent(deviceHandle, configurationHandle, eventCode);
            status2 = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
            if ((status1 != kStatus_USB_Success) && (status2 != kStatus_USB_Success))
            {
                status = kStatus_USB_Error;
            }
#else
            status = USB_HostMsdEvent(deviceHandle, configurationHandle, eventCode);
#endif
            break;

        case kUSB_HostEventEnumerationFail:
            usb_echo("enumeration failed\r\n");
            break;

        default:
            break;
    }
    return status;
}

static void USB_HostApplicationInit(void)
{
    usb_status_t status = kStatus_USB_Success;

    USB_HostClockInit();

#if ((defined FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    status = USB_HostInit(CONTROLLER_ID, &g_HostHandle, USB_HostEvent);
    if (status != kStatus_USB_Success)
    {
        usb_echo("host init error\r\n");
        return;
    }
    USB_HostIsrEnable();

    usb_echo("host init done\r\n");
}
/********************************************************************************/
/*********************************HyperFlash***********************************/
#include "fsl_romapi.h"
#include "fsl_debug_console.h"
#include "fsl_cache.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"
/*${header:start}*/
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
#define PRGM_PAGE_SIZE 			  	512//added by Raj
#define FlexSpiInstance           	0U
#define EXAMPLE_FLEXSPI_AMBA_BASE 	FlexSPI_AMBA_BASE
#define FLASH_SIZE                	0x4000000UL /* 64MBytes */
#define FLASH_PAGE_SIZE           	PRGM_PAGE_SIZE//512UL       /* 512Bytes */
#define FLASH_SECTOR_SIZE         	0x40000UL   /* 256KBytes */
#define FLASH_BLOCK_SIZE          	0x40000UL   /* 256KBytes */

#define BUFFER_LEN 				  	FLASH_PAGE_SIZE

#define APP_WRITE_START_ADDR	  	0//0x80000
// Define the address to jump to in HyperFlash memory
#define JUMP_ADDRESS  				0x6002305//0x60080305

#define DATA_RECORD					0x00
#define E_O_F						0x01
#define EXTENDED_LINEAR_ADDR		0x04
#define APP_ENTRY_ADDR				0x05

uint32_t extended_address = 0;
uint32_t jump_address = 0;

uint8_t extnd_addr_arr[10];
uint8_t jump_addr_arr[10];

uint32_t hyperflash_addr = 0;
uint16_t hyper_sec_no = 0, gh = 0, ij = 0, kg = 0;
uint8_t no_bytes = 0, record_type = 0;
uint32_t address = 0;
uint8_t data_temp = 0;

uint32_t NorAddress;        /* Address of the serial nor device location */
uint32_t FlexSPINorAddress; /* Address of the serial nor device in FLEXSPI memory */

uint8_t bl_pwr_on = 0;
uint16_t bl_tm_cntr = 0;

uint8_t f_bufferRead[33];
uint8_t lineBuffer[128];
uint8_t programable_buffer[BUFFER_LEN];
uint8_t temp_buffer[16];

FRESULT error;
FIL g_fileObject1;


uint32_t AsciiToDecimal(uint16_t starting_index,uint8_t no_of_digits);
uint8_t ASCII2HEX(uint8_t character);
void HyperFlash(void);
void ReadFromPendrive(void);
void jump_to_hyperflash_location(uint32_t applicationAddress);
void funcDelayUs(uint32_t llTick);
uint8_t decimalToBCD(uint8_t decimal);
void dummy(void);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if !(defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
void BOARD_SetupFlexSpiClock(void);
#endif
/* Get FlexSPI NOR Configuration Block */
void FLEXSPI_NorFlash_GetConfig(flexspi_nor_config_t *config);
void error_trap(void);
void app_finalize(void);

#if !defined(XIP_EXTERNAL_FLASH) || (XIP_EXTERNAL_FLASH != 1)
extern status_t FLEXSPI_NorFlash_VerifyID(uint32_t instance);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief FLEXSPI NOR flash driver Structure */
static flexspi_nor_config_t norConfig;
/*! @brief Buffer for program */
static uint8_t s_buffer[BUFFER_LEN];
/*! @brief Buffer for readback */
static uint8_t s_buffer_rbc[BUFFER_LEN];

typedef struct _flexspi_cache_status
{
    volatile bool DCacheEnableFlag;
    volatile bool ICacheEnableFlag;
} flexspi_cache_status_t;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Get FLEXSPI NOR Configuration Block */
void FLEXSPI_NorFlash_GetConfig(flexspi_nor_config_t *config)
{
    config->memConfig.tag              = FLEXSPI_CFG_BLK_TAG;
    config->memConfig.version          = FLEXSPI_CFG_BLK_VERSION;
    config->memConfig.readSampleClkSrc = kFLEXSPIReadSampleClk_ExternalInputFromDqsPad;
    config->memConfig.serialClkFreq =
        kFLEXSPISerialClk_30MHz; /* Serial Flash Frequencey.See System Boot Chapter for more details */
    config->memConfig.lutCustomSeqEnable = true;
    config->memConfig.sflashA1Size       = FLASH_SIZE;
    config->memConfig.csHoldTime         = 3U;                       /* Data hold time, default value: 3 */
    config->memConfig.csSetupTime        = 3U;                       /* Date setup time, default value: 3 */
    config->memConfig.deviceType     = kFLEXSPIDeviceType_SerialNOR; /* Flash device type default type: Serial NOR */
    config->memConfig.deviceModeType = kDeviceConfigCmdType_Generic;
    config->memConfig.columnAddressWidth  = 3U;
    config->memConfig.deviceModeCfgEnable = 0U;
    config->memConfig.waitTimeCfgCommands = 0U;
    config->memConfig.configCmdEnable     = 0U;
    config->memConfig.busyOffset          = 15U;
    config->memConfig.busyBitPolarity     = 1U;
    /* Always enable Safe configuration Frequency */
    config->memConfig.controllerMiscOption = FSL_ROM_FLEXSPI_BITMASK(kFLEXSPIMiscOffset_DiffClkEnable) |
                                             FSL_ROM_FLEXSPI_BITMASK(kFLEXSPIMiscOffset_WordAddressableEnable) |
                                             FSL_ROM_FLEXSPI_BITMASK(kFLEXSPIMiscOffset_SafeConfigFreqEnable) |
                                             FSL_ROM_FLEXSPI_BITMASK(kFLEXSPIMiscOffset_DdrModeEnable);
    config->memConfig.sflashPadType = kSerialFlash_8Pads; /* Pad Type: 1 - Single, 2 - Dual, 4 - Quad, 8 - Octal */
    config->pageSize                = FLASH_PAGE_SIZE;
    config->sectorSize              = FLASH_SECTOR_SIZE;
    config->blockSize               = FLASH_BLOCK_SIZE;
    config->isUniformBlockSize      = true;
    config->ipcmdSerialClkFreq      = kFLEXSPISerialClk_30MHz; /* Clock frequency for IP command */
    config->serialNorType           = kSerialNorType_HyperBus;

    // Read
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READ + 0U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0xA0U, RADDR_DDR, FLEXSPI_8PAD, 0x18U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READ + 1U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10U, DUMMY_DDR, FLEXSPI_8PAD, 0x06U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READ + 2U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(READ_DDR, FLEXSPI_8PAD, 0x04U, STOP, FLEXSPI_1PAD, 0x0U);

    // Read Status
    // 0
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 1U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 2U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x05U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 3U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x70U);
    // 1
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 4U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0xA0U, RADDR_DDR, FLEXSPI_8PAD, 0x18U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 5U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10U, DUMMY_RWDS_DDR, FLEXSPI_8PAD, 0x0BU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_READSTATUS + 6U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(READ_DDR, FLEXSPI_8PAD, 0x04U, STOP, FLEXSPI_1PAD, 0x00U);

    // Write Enable
    // 0
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 1U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 2U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x05U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 3U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    // 1
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 4U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 5U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x55U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 6U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x02U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE + 7U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x55U);

    // Page Program
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 2U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x05U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 3U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xA0U);
    // 1
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 4U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, RADDR_DDR, FLEXSPI_8PAD, 0x18U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 5U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10U, WRITE_DDR, FLEXSPI_8PAD, 0x80U);

    // Erase Sector
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 1U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 2U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x05U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 3U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x80U);
    // 1
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 4U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 5U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 6U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x05U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 7U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0xAAU);
    // 2
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 8U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 9U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x55U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 10U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x02U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 11U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, CMD_DDR, FLEXSPI_8PAD, 0x55U);
    // 3
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 12U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00U, RADDR_DDR, FLEXSPI_8PAD, 0x18U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 13U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10U, CMD_DDR, FLEXSPI_8PAD, 0x00U);
    config->memConfig.lookupTable[4U * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 14U] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x30U, STOP, FLEXSPI_1PAD, 0x0U);

    // Erase Chip
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x00);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 1] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0xAA);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 2] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x05);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 3] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x80);
    // 1
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 4] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x00);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 5] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0xAA);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 6] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x05);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 7] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0xAA);
    // 2
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 8] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x00);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 9] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x55);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 10] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x02);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 11] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x55);
    // 3
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 12] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x00);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 13] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0xAA);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 14] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x05);
    config->memConfig.lookupTable[4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE + 15] =
        FSL_ROM_FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0x00, CMD_DDR, FLEXSPI_8PAD, 0x10);

    // LUT customized sequence
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_WRITEENABLE].seqNum = 2U;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_WRITEENABLE].seqId  = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_READSTATUS].seqNum  = 2U;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_READSTATUS].seqId   = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_PAGEPROGRAM].seqNum = 2U;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_PAGEPROGRAM].seqId  = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_ERASESECTOR].seqNum = 4U;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_ERASESECTOR].seqId  = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_CHIPERASE].seqNum   = 4U;
    config->memConfig.lutCustomSeq[NOR_CMD_INDEX_CHIPERASE].seqId    = NOR_CMD_LUT_SEQ_IDX_CHIPERASE;
}
#if !(defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
/* Configure clock for FlexSPI peripheral */
void BOARD_SetupFlexSpiClock(void)
{
    /* Disable FlexSPI peripheral */
    FLEXSPI->MCR0 |= FLEXSPI_MCR0_MDIS_MASK;
    CLOCK_DisableClock(kCLOCK_FlexSpi);

    /* Init Usb1 PLL3 to 480MHZ. */
    CLOCK_InitUsb1Pll(&usb1PllConfig_BOARD_BootClockRUN);
    /* Init Usb1 PLL3->pfd0 360MHZ. */
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd0, 24);
    /* Enable Usb1 PLL output for USBPHY1. */
    CCM_ANALOG->PLL_USB1 |= CCM_ANALOG_PLL_USB1_EN_USB_CLKS_MASK;

    /* Set FLEXSPI_PODF, FlexSPI out clock is 60MHZ. */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 5);
    /* Set flexspi clock source to PLL3->pfd0 */
    CLOCK_SetMux(kCLOCK_FlexspiMux, 3);

    CLOCK_EnableClock(kCLOCK_FlexSpi);
    /* Enable FlexSPI peripheral */
    FLEXSPI->MCR0 &= ~FLEXSPI_MCR0_MDIS_MASK;
}
#endif


/*
 * @brief Gets called when an error occurs.
 *
 * @details Print error message and trap forever.
 */
void error_trap(void)
{
    PRINTF("\r\n\r\n\r\n\t---- HALTED DUE TO FLEXSPI NOR ERROR! ----");
    while (1)
    {
    }
}

/*
 * @brief Gets called when the app is complete.
 *
 * @details Print finshed message and trap forever.
 */
/*void app_finalize(void)
{
     Print finished message.
    PRINTF("\r\n End of FLEXSPI NOR Example! \r\n");
    while (1)
    {
    }
}*/

void app_finalize(void)
{
	/* Print finished message. */
	PRINTF("\r\n End of FLEXSPI NOR Example! \r\n");
	while (1)
	{
		USB_HostTaskFn(g_HostHandle);
		USB_HostMsdTask(&g_MsdFatfsInstance);

		if(usb_attached == 1)
		{
			usb_attached = 0;
			ReadFromPendrive();
		}
	}
}

void get_cache_status(flexspi_cache_status_t *cacheStatus)
{
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        cacheStatus->DCacheEnableFlag = true;
    }
    else
    {
        cacheStatus->DCacheEnableFlag = false;
    }

    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        cacheStatus->ICacheEnableFlag = true;
    }
    else
    {
        cacheStatus->ICacheEnableFlag = false;
    }
}

void flexspi_nor_handle_cache(bool isPre, flexspi_cache_status_t cacheStatus)
{
    if (isPre)
    {
        if (cacheStatus.DCacheEnableFlag == true)
        {
            SCB_DisableDCache();
        }
        else
        {
            ; /* Do nothing */
        }

        if (cacheStatus.ICacheEnableFlag == true)
        {
            SCB_DisableICache();
        }
        else
        {
            ; /* Do nothing */
        }
    }
    else
    {
        if (cacheStatus.DCacheEnableFlag == true)
        {
            SCB_EnableDCache();
        }
        else
        {
            ; /* Do nothing */
        }

        if (cacheStatus.ICacheEnableFlag == true)
        {
            SCB_EnableICache();
        }
        else
        {
            ; /* Do nothing */
        }
    }
}



void HyperFlash(void)
{
	status_t status;
	uint32_t i = 0U;
	uint32_t serialNorAddress;        /* Address of the serial nor device location */
	uint32_t FlexSPISerialNorAddress; /* Address of the serial nor device in FLEXSPI memory */
	uint32_t serialNorTotalSize;
	uint32_t serialNorSectorSize;
	uint32_t serialNorPageSize;

	/*//BOARD_ConfigMPU();
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		USB_HostApplicationInit();
	#if !(defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
		BOARD_SetupFlexSpiClock();
	#endif
		BOARD_InitDebugConsole();
	*/

	PRINTF("\r\n FLEXSPI NOR example started!\r\n");

	flexspi_cache_status_t cacheStatus;
	get_cache_status(&cacheStatus);

	/* Clean up FLEXSPI NOR flash driver Structure */
	memset(&norConfig, 0, sizeof(flexspi_nor_config_t));

	/* Setup FLEXSPI NOR Configuration Block */
	FLEXSPI_NorFlash_GetConfig(&norConfig);

	/* Initializes the FLEXSPI module for the other FLEXSPI APIs */
	status = ROM_FLEXSPI_NorFlash_Init(FlexSpiInstance, &norConfig);
	if (status == kStatus_Success)
	{
		PRINTF("\r\n Successfully init FLEXSPI serial NOR flash\r\n ");
	}
	else
	{
		PRINTF("\r\n Erase sector failure !\r\n");
		error_trap();
	}

	/* Perform software reset after initializing flexspi module */
	ROM_FLEXSPI_NorFlash_ClearCache(FlexSpiInstance);


	serialNorTotalSize  = norConfig.memConfig.sflashA1Size;
	serialNorSectorSize = norConfig.sectorSize;
	serialNorPageSize   = norConfig.pageSize;

	/* Print HyperFlash information */
	PRINTF("\r\n HyperFlash Information: ");
	PRINTF("\r\n Total program flash size:\t%d KB, Hex: (0x%x)", (serialNorTotalSize / 1024U), serialNorTotalSize);
	PRINTF("\r\n Program flash sector size:\t%d KB, Hex: (0x%x) ", (serialNorSectorSize / 1024U), serialNorSectorSize);
	PRINTF("\r\n Program flash page size:\t%d B, Hex: (0x%x)\r\n", serialNorPageSize, serialNorPageSize);

	/*
	 * SECTOR_INDEX_FROM_END = 1 means the last sector,
	 * SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
	 */
	#ifndef SECTOR_INDEX_FROM_END
	#define SECTOR_INDEX_FROM_END 1U
	#endif
	/* Erase one sector. */
	PRINTF("\r\n Erasing serial NOR flash over FLEXSPI");
	for(hyper_sec_no = 1, hyperflash_addr = APP_WRITE_START_ADDR; hyper_sec_no < 255, hyperflash_addr < FLASH_SIZE; hyper_sec_no++, hyperflash_addr+= FLASH_SECTOR_SIZE)
	{
		 /* Erase a sector from target device dest address */
		serialNorAddress        = hyperflash_addr;
		FlexSPISerialNorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + serialNorAddress;

		flexspi_nor_handle_cache(true, cacheStatus);
		status = ROM_FLEXSPI_NorFlash_Erase(FlexSpiInstance, &norConfig, serialNorAddress, serialNorSectorSize);
		flexspi_nor_handle_cache(false, cacheStatus);
		if (status == kStatus_Success)
		{
			/* Print message for user. */
			//PRINTF("\r\n Successfully erased one sector of NOR flash device 0x%x -> 0x%x\r\n", serialNorAddress,
				   //(serialNorAddress + serialNorSectorSize));
			PRINTF("\r\n sec no %d\r\n",hyper_sec_no);
		}
		else
		{
			PRINTF("\r\n Erase sector failure!\r\n");
			error_trap();
		}
		funcDelayUs(5);
	}
}

void ReadFromPendrive(void)
{
	status_t status;
	uint32_t i = 0U;
	uint32_t serialNorTotalSize;
	uint32_t serialNorSectorSize;
	uint32_t serialNorPageSize;

	uint8_t ix = 0,fg = 0;

	flexspi_cache_status_t cacheStatus;

	FATFS pendrive_fatfs;      /* Work area (filesystem object) for logical drives */
	DIR pendrive_dir;

	uint8_t *pendrive_filename;

	/* Register work area for logical drive 1*/
	error = f_mount(&pendrive_fatfs, "1:", 0);

	/*
	 Create file on the pendrive
	error = f_mkdir(_T("1:/EM"));

	if (error == FR_EXIST)
	{
		error = f_opendir(&pendrive_dir,_T("1:/EM"));
	}
	else
	{

	}
	pendrive_filename = pendrive_filename_creation("DataLogging");
	error = f_open(&g_fileObject1,_T(pendrive_filename), FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_EXISTING);
	*/
//	error = f_open(&g_fileObject1,_T("1:pwm.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:led.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMS_ND.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMS.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMSE.hex"), FA_READ | FA_OPEN_EXISTING);
	error = f_open(&g_fileObject1,_T("1:VMSE0.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMSEP.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMSP.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMSP0.hex"), FA_READ | FA_OPEN_EXISTING);
//	error = f_open(&g_fileObject1,_T("1:VMS_BH60.hex"), FA_READ | FA_OPEN_EXISTING);

	if(error == FR_OK)
	{
		kg = 0;
		NorAddress = APP_WRITE_START_ADDR;
		FlexSPINorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + NorAddress;
		while(f_gets((char *)lineBuffer, sizeof(lineBuffer), &g_fileObject1))
		{
			if(lineBuffer[0] == ':')
			{
				no_bytes = AsciiToDecimal(1,2);
				address  = AsciiToDecimal(3,4);
				record_type = AsciiToDecimal(7,2);

				if(record_type == DATA_RECORD || record_type == E_O_F)
				{
					/*Data record*/
					gh = 9;
					for(ij = 0; ij < no_bytes;ij++,gh+=2,kg++)
					{
						temp_buffer[ij] = AsciiToDecimal(gh,2);
						programable_buffer[kg] = temp_buffer[ij];
						funcDelayUs(1);
					}

					if(kg >= PRGM_PAGE_SIZE || record_type == E_O_F)
					{
						if(record_type == E_O_F)
						{
							/*End of file record*/
							PRINTF("\r\n Program a buffer to a page of NOR flash");
							/* Prepare user buffer. */
							for (i = 0; i < kg; i++)
							{
								s_buffer[i] = programable_buffer[i];
							}

							norConfig.pageSize = kg;
							/* Program user buffer into FLEXSPI NOR flash */
							status =
								ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, NorAddress, (const uint32_t *)s_buffer);
							if (status != kStatus_Success)
							{
								PRINTF("\r\n Page program failure!\r\n");
								error_trap();
							}

							funcDelayUs(1);

							DCACHE_InvalidateByRange(FlexSPINorAddress, kg);
							/* Verify programming by reading back from FLEXSPI memory directly */
							memcpy(s_buffer_rbc, (void *)(FlexSPINorAddress), kg);
							if (memcmp(s_buffer_rbc, s_buffer, kg) == 0)
							{
								PRINTF("\r\n Successfully programmed and verified location FLEXSPI memory 0x%x -> 0x%x \r\n",
									   (FlexSPINorAddress), (FlexSPINorAddress + kg));
							}
							else
							{
								PRINTF("\r\n Program data -  read out data value incorrect!\r\n ");
								error_trap();
							}
						}
						else
						{
							kg = 0;

							PRINTF("\r\n Program a buffer to a page of NOR flash");
							/* Prepare user buffer. */
							for (i = 0; i < BUFFER_LEN; i++)
							{
								s_buffer[i] = programable_buffer[i];
							}

							/* Program user buffer into FLEXSPI NOR flash */
							status =
								ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, NorAddress, (const uint32_t *)s_buffer);
							if (status != kStatus_Success)
							{
								PRINTF("\r\n Page program failure!\r\n");
								error_trap();
							}

							funcDelayUs(1);
							DCACHE_InvalidateByRange(FlexSPINorAddress, sizeof(s_buffer_rbc));
							/* Verify programming by reading back from FLEXSPI memory directly */
							memcpy(s_buffer_rbc, (void *)(FlexSPINorAddress), sizeof(s_buffer_rbc));
							if (memcmp(s_buffer_rbc, s_buffer, sizeof(s_buffer)) == 0)
							{
								PRINTF("\r\n Successfully programmed and verified location FLEXSPI memory 0x%x -> 0x%x \r\n",
									   (FlexSPINorAddress), (FlexSPINorAddress + sizeof(s_buffer)));
							}
							else
							{
								PRINTF("\r\n Program data -  read out data value incorrect!\r\n ");
								error_trap();
							}

							NorAddress        = PRGM_PAGE_SIZE + NorAddress;
							FlexSPINorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + NorAddress;
						}

						memset(&programable_buffer,0,sizeof(programable_buffer));
						memset(&temp_buffer,0,sizeof(temp_buffer));
						memset(&s_buffer,0,sizeof(s_buffer));
						memset(&s_buffer_rbc,0,sizeof(s_buffer_rbc));
						funcDelayUs(1);
					}
				}
				else if(record_type == EXTENDED_LINEAR_ADDR)
				{
					/*Extended linear address record*/
					ix = 9;
					for(fg = 0; fg < no_bytes;ix+=2/*1byte*/,fg++)
					{
						extnd_addr_arr[fg] = AsciiToDecimal(ix,2);
					}
					/*
					extended_address = extnd_addr_arr[0];
					extended_address = (extended_address << 8) | extnd_addr_arr[1];
					*/
					extended_address = extnd_addr_arr[0];
					extended_address = extended_address << 8;
					extended_address = extended_address | extnd_addr_arr[1];
					memset(&extnd_addr_arr,0,sizeof(extnd_addr_arr));
				}
				else if(record_type == APP_ENTRY_ADDR)
				{
					/*Jump address mentioned in the address field*/
					ix = 9;
					for(fg = 0; fg < no_bytes;ix+=2/*1byte*/,fg++)
					{
						jump_addr_arr[fg] = AsciiToDecimal(ix,2);
					}

					jump_address = jump_addr_arr[0];
					jump_address = jump_address << 8;
					jump_address = jump_address | jump_addr_arr[1];
					jump_address = jump_address << 8;
					jump_address = jump_address | jump_addr_arr[2];
					jump_address = jump_address << 8;
					jump_address = jump_address | jump_addr_arr[3];
					memset(&jump_addr_arr,0,sizeof(jump_addr_arr));
				}

				f_sync(&g_fileObject1);
				memset(&lineBuffer,0,sizeof(lineBuffer));
			}
		}
	}

#if 0
	if(error == FR_OK)
	{
		kg = 0;
		NorAddress = 0x80000;
		FlexSPINorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + NorAddress;
		while(f_gets((char *)lineBuffer, sizeof(lineBuffer), &g_fileObject1))
		{
			if(lineBuffer[0] == ':')
			{
				no_bytes = AsciiToDecimal(1,2);
				address  = AsciiToDecimal(3,4);
				record_type = AsciiToDecimal(7,2);

				if(record_type == 0x00 || record_type == 0x01)
				{
					/*Data record*//*End of file record*/
					gh = 9;
					for(ij = 0; ij < no_bytes;ij++,gh+=2,kg++)
					{
						temp_buffer[ij] = AsciiToDecimal(gh,2);
						programable_buffer[kg] = temp_buffer[ij];
						funcDelayUs(5);
					}

					if(kg >= 512 || record_type == 0x01)
					{
						if(record_type == 0x01)
						{

							PRINTF("\r\n Program a buffer to a page of NOR flash");
							/* Prepare user buffer. */
							for (i = 0; i < kg; i++)
							{
								s_buffer[i] = programable_buffer[i];
							}

							norConfig.pageSize = kg;
							/* Program user buffer into FLEXSPI NOR flash */
							status =
								ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, NorAddress, (const uint32_t *)s_buffer);
							if (status != kStatus_Success)
							{
								PRINTF("\r\n Page program failure!\r\n");
								error_trap();
							}

							funcDelayUs(5);
							DCACHE_InvalidateByRange(FlexSPINorAddress, kg);
							/* Verify programming by reading back from FLEXSPI memory directly */
							memcpy(s_buffer_rbc, (void *)(FlexSPINorAddress), kg);
							if (memcmp(s_buffer_rbc, s_buffer, kg) == 0)
							{
								PRINTF("\r\n Successfully programmed and verified location FLEXSPI memory 0x%x -> 0x%x \r\n",
									   (FlexSPINorAddress), (FlexSPINorAddress + kg));
							}
							else
							{
								PRINTF("\r\n Program data -  read out data value incorrect!\r\n ");
								error_trap();
							}

//								NorAddress        = 512 + NorAddress;
//								FlexSPINorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + NorAddress;
						}
						else
						{
							kg = 0;

							PRINTF("\r\n Program a buffer to a page of NOR flash");
							/* Prepare user buffer. */
							for (i = 0; i < BUFFER_LEN; i++)
							{
								s_buffer[i] = programable_buffer[i];
							}

							/* Program user buffer into FLEXSPI NOR flash */
							status =
								ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, NorAddress, (const uint32_t *)s_buffer);
							if (status != kStatus_Success)
							{
								PRINTF("\r\n Page program failure!\r\n");
								error_trap();
							}

							funcDelayUs(5);
							DCACHE_InvalidateByRange(FlexSPINorAddress, sizeof(s_buffer_rbc));
							/* Verify programming by reading back from FLEXSPI memory directly */
							memcpy(s_buffer_rbc, (void *)(FlexSPINorAddress), sizeof(s_buffer_rbc));
							if (memcmp(s_buffer_rbc, s_buffer, sizeof(s_buffer)) == 0)
							{
								PRINTF("\r\n Successfully programmed and verified location FLEXSPI memory 0x%x -> 0x%x \r\n",
									   (FlexSPINorAddress), (FlexSPINorAddress + sizeof(s_buffer)));
							}
							else
							{
								PRINTF("\r\n Program data -  read out data value incorrect!\r\n ");
								error_trap();
							}

							NorAddress        = 512 + NorAddress;
							FlexSPINorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + NorAddress;
						}

						memset(&programable_buffer,0,sizeof(programable_buffer));
						memset(&temp_buffer,0,sizeof(temp_buffer));
						memset(&s_buffer,0,sizeof(s_buffer));
						memset(&s_buffer_rbc,0,sizeof(s_buffer_rbc));
						funcDelayUs(5);
					}
				}

				}
				else if(record_type == 0x04)
				{
					/*Extended linear address record*/
				}
				else if(record_type == 0x05)
				{
					/*Jump address mentioned in the address field*/
				}

			f_sync(&g_fileObject1);
			memset(&lineBuffer,0,sizeof(lineBuffer));
		}
	}
#endif
	f_close(&g_fileObject1);
	//f_closedir(&pendrive_dir);

	/* Unregister work area prior to discard it */
	f_mount(0, "1:", 0);

	// Perform the jump to the desired location in HyperFlash memory
	jump_to_hyperflash_location(jump_address);
}

uint32_t AsciiToDecimal(uint16_t starting_index,uint8_t no_of_digits)
{
	uint32_t Decimal_data = 0,DecimalMSB = 0,DecimalLSB = 0;
	switch(no_of_digits)
	{
		case 1: Decimal_data  = ASCII2HEX(lineBuffer[starting_index]);
				break;
		case 2:
				data_temp =  ASCII2HEX(lineBuffer[starting_index]);
				if(data_temp > 9)
				{
					Decimal_data = data_temp * 16;
				}
				else
				{
					Decimal_data = data_temp * 10;
					Decimal_data = decimalToBCD(Decimal_data);
				}
				Decimal_data += ASCII2HEX(lineBuffer[starting_index+1]);
				break;
		case 3:
				break;
		case 4:
				data_temp =  ASCII2HEX(lineBuffer[starting_index]);
				if(data_temp > 9)
				{
					DecimalMSB = data_temp * 16;
				}
				else
				{
					DecimalMSB = data_temp * 10;

					DecimalMSB = decimalToBCD(DecimalMSB);
				}
				DecimalMSB += ASCII2HEX(lineBuffer[starting_index+1]);

				data_temp =  ASCII2HEX(lineBuffer[starting_index+2]);
				if(data_temp > 9)
				{
					DecimalLSB = data_temp * 16;
				}
				else
				{
					DecimalLSB = data_temp * 10;

					DecimalLSB = decimalToBCD(DecimalLSB);
				}
				DecimalLSB += ASCII2HEX(lineBuffer[starting_index+3]);

				Decimal_data = (DecimalMSB << 8) | DecimalLSB;
				break;
		default:break;
	}
	return (Decimal_data);
}

uint8_t decimalToBCD(uint8_t decimal)
{
	uint8_t tens = decimal / 10;
	uint8_t ones = decimal % 10;
	uint8_t bcd = (tens << 4) | ones;
	return bcd;
}

uint8_t ASCII2HEX(uint8_t character)
{
	uint8_t mem_sel_data = 0;

	if(character >= 'A')
	{
		mem_sel_data = character - 55;
	}
	else
	{
		mem_sel_data = character- 48;
	}

	return mem_sel_data;
}
static OSA_SR_ALLOC();
	// Function to perform the jump
void jump_to_hyperflash_location(uint32_t applicationAddress)
{
	// Turn off global interrupt
	OSA_ENTER_CRITICAL();

	// Shutdown microseconds driver.
//	    PIT->CHANNEL[1].TCTRL = 0; // stop timer 1
//	    PIT->CHANNEL[0].TCTRL = 0; // stop timer 1
//	    PIT->CHANNEL[1].LDVAL = 0;
//	    PIT->CHANNEL[0].LDVAL = 0;
//	    PIT->MCR |= PIT_MCR_MDIS_MASK;

	// Clear any IRQs that may be enabled, we only want the IRQs we enable to be active
	//NVIC_ClearEnabledIRQs();
	NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICER[1] = 0xFFFFFFFF;
	NVIC->ICER[2] = 0xFFFFFFFF;
	NVIC->ICER[3] = 0xFFFFFFFF;
	NVIC->ICER[4] = 0xFFFFFFFF;
	NVIC->ICER[5] = 0xFFFFFFFF;
	NVIC->ICER[6] = 0xFFFFFFFF;
	NVIC->ICER[7] = 0xFFFFFFFF;

	// Clear any pending IRQs that may have been set
	//NVIC_ClearAllPendingIRQs();
	NVIC->ICPR[0] = 0xFFFFFFFF;
	NVIC->ICPR[1] = 0xFFFFFFFF;
	NVIC->ICPR[2] = 0xFFFFFFFF;
	NVIC->ICPR[3] = 0xFFFFFFFF;
	NVIC->ICPR[4] = 0xFFFFFFFF;
	NVIC->ICPR[5] = 0xFFFFFFFF;
	NVIC->ICPR[6] = 0xFFFFFFFF;
	NVIC->ICPR[7] = 0xFFFFFFFF;
#if 1
	 uint32_t stackPointer;// = 0x60080000;
//	 get_user_application_entry(&applicationAddress, &stackPointer);
	// Create the function call to the user application.
	// Static variables are needed since changed the stack pointer out from under the compiler
	// we need to ensure the values we are using are not stored on the previous stack
	static uint32_t s_stackPointer = 0;
	s_stackPointer = stackPointer;
	static void (*farewellBootloader)(void) = 0;
//    farewellBootloader = (void (*)(void))applicationAddress;
    farewellBootloader = (void (*)(void))JUMP_ADDRESS;

	// Set the VTOR to the application vector table address.
//    SCB->VTOR = (uint32_t)APP_VECTOR_TABLE;
//	SCB->VTOR = (uint32_t)0x60001000;

    // Define the new IVT location in memory
    #define NEW_IVT_LOCATION 0x60001000

    uint32_t *old_ivt = (uint32_t *)SCB->VTOR; // Get the current IVT location
    uint32_t *new_ivt = (uint32_t *)NEW_IVT_LOCATION;

    // Copy the IVT to the new location
#define NVIC_NUM_VECTORS 16
    for (int i = 0; i < NVIC_NUM_VECTORS; i++) {
        new_ivt[i] = old_ivt[i];
    }

    // Update the VTOR to point to the new IVT location
    SCB->VTOR = NEW_IVT_LOCATION;

	 // Restore global interrupt.
	 __enable_irq();

	// Memory barriers for good measure.
	__ISB();
	__DSB();


	// Set stack pointers to the application stack pointer.
	__set_MSP(s_stackPointer);
	__set_PSP(s_stackPointer);

	// Jump to the application.
	farewellBootloader();
#endif

#if 0
	// Set the VTOR to default.
//	SCB->VTOR = 0;//kDefaultVectorTableAddress;
	SCB->VTOR = 0x60080000;//kDefaultVectorTableAddress;
	extern uint32_t g_pfnVectors[];  // Vector table defined in startup code
//    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    unsigned int * pSCB_VTOR = (unsigned int *) 0x60080000;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
	*pSCB_VTOR = (unsigned int)g_pfnVectors;
    }


	 CLOCK_DisableClock(kCLOCK_UsbOh3);

	 // Restore global interrupt.
	 __enable_irq();

	// Memory barriers for good measure.
	__ISB();
	__DSB();

	static void (*farewellBootloader)(void) = 0;
	farewellBootloader = (void (*)(void))JUMP_ADDRESS;//applicationAddress

	//Jump to the application.
	farewellBootloader();
#endif

	#if 0
			//__asm("ldr pc, =0x60082305");
			__asm("ldr r0, =0x60082305"); // Load the address into register r0
			__asm("bx r0");               // Branch to the address stored in r0

			while(1)
			{

			}
	#endif

	#if 0
	//! @brief Defines a constant for the default vector table.
	enum _vector_table_address
	{
		//! @brief Address of the default vector table, which is always 0.
		kDefaultVectorTableAddress = 0
	};
	#define APP_VECTOR_TABLE ((uint32_t *)kDefaultVectorTableAddress)

	//    shutdown_cleanup(kShutdownType_Shutdown);

		// Create the function call to the user application.
		// Static variables are needed since changed the stack pointer out from under the compiler
		// we need to ensure the values we are using are not stored on the previous stack
		static uint32_t s_stackPointer = 0;
		s_stackPointer = 0;
		static void (*farewellBootloader)(void) = 0;
	//    farewellBootloader = (void (*)(void))applicationAddress;
		farewellBootloader = (void (*)(void))JUMP_ADDRESS;
		// Set the VTOR to the application vector table address.
		SCB->VTOR = (uint32_t)APP_VECTOR_TABLE;//0xa000

		// Set stack pointers to the application stack pointer.
		__set_MSP(s_stackPointer);
		__set_PSP(s_stackPointer);

		// Jump to the application.
		farewellBootloader();
	#endif
}

void funcDelayUs(uint32_t llTick)
{
	uint32_t liDelayLoop = 0;
	uint32_t llLoopUs1 = 0;

	for(liDelayLoop = 0; liDelayLoop < llTick; liDelayLoop++)
	{
		for(llLoopUs1 = 0; llLoopUs1 < 100; llLoopUs1++)
		{}
	}
}
/******************************HyperFlash End*********************************/
int main(void)
{
	bl_pwr_on = 1;
    //BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    USB_HostApplicationInit();
#if !(defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
    BOARD_SetupFlexSpiClock();
#endif
    BOARD_InitDebugConsole();
    //SysTick_Config(SystemCoreClock); //1ms systick
#if 0
    status_t status;
    uint32_t i = 0U;
    uint32_t serialNorAddress;        /* Address of the serial nor device location */
    uint32_t FlexSPISerialNorAddress; /* Address of the serial nor device in FLEXSPI memory */
    uint32_t serialNorTotalSize;
    uint32_t serialNorSectorSize;
    uint32_t serialNorPageSize;

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
#if !(defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
    BOARD_SetupFlexSpiClock();
#endif
    BOARD_InitDebugConsole();

    PRINTF("\r\n FLEXSPI NOR example started!\r\n");

    flexspi_cache_status_t cacheStatus;
    get_cache_status(&cacheStatus);

    /* Clean up FLEXSPI NOR flash driver Structure */
    memset(&norConfig, 0, sizeof(flexspi_nor_config_t));

    /* Setup FLEXSPI NOR Configuration Block */
    FLEXSPI_NorFlash_GetConfig(&norConfig);

    /* Initializes the FLEXSPI module for the other FLEXSPI APIs */
    status = ROM_FLEXSPI_NorFlash_Init(FlexSpiInstance, &norConfig);
    if (status == kStatus_Success)
    {
        PRINTF("\r\n Successfully init FLEXSPI serial NOR flash\r\n ");
    }
    else
    {
        PRINTF("\r\n Erase sector failure !\r\n");
        error_trap();
    }

    /* Perform software reset after initializing flexspi module */
    ROM_FLEXSPI_NorFlash_ClearCache(FlexSpiInstance);

#if !defined(XIP_EXTERNAL_FLASH) || (XIP_EXTERNAL_FLASH != 1)
    /* Read ID-CFI Parameters */
    status = FLEXSPI_NorFlash_VerifyID(FlexSpiInstance);
    if (status == kStatus_Success)
    {
        PRINTF("\r\n HyperFlash has been found successfully\r\n ");
    }
    else
    {
        PRINTF("\r\n HyperFlash can not be found!\r\n");
        error_trap();
    }
#endif // XIP_EXTERNAL_FLASH

    serialNorTotalSize  = norConfig.memConfig.sflashA1Size;
    serialNorSectorSize = norConfig.sectorSize;
    serialNorPageSize   = norConfig.pageSize;

    /* Print HyperFlash information */
    PRINTF("\r\n HyperFlash Information: ");
    PRINTF("\r\n Total program flash size:\t%d KB, Hex: (0x%x)", (serialNorTotalSize / 1024U), serialNorTotalSize);
    PRINTF("\r\n Program flash sector size:\t%d KB, Hex: (0x%x) ", (serialNorSectorSize / 1024U), serialNorSectorSize);
    PRINTF("\r\n Program flash page size:\t%d B, Hex: (0x%x)\r\n", serialNorPageSize, serialNorPageSize);

/*
 * SECTOR_INDEX_FROM_END = 1 means the last sector,
 * SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
 */
#ifndef SECTOR_INDEX_FROM_END
#define SECTOR_INDEX_FROM_END 1U
#endif
    /* Erase a sector from target device dest address */
    serialNorAddress        = serialNorTotalSize - (SECTOR_INDEX_FROM_END * serialNorSectorSize);
    FlexSPISerialNorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + serialNorAddress;

    /* Erase one sector. */
    PRINTF("\r\n Erasing serial NOR flash over FLEXSPI");
    flexspi_nor_handle_cache(true, cacheStatus);
    status = ROM_FLEXSPI_NorFlash_Erase(FlexSpiInstance, &norConfig, serialNorAddress, serialNorSectorSize);
    flexspi_nor_handle_cache(false, cacheStatus);
    if (status == kStatus_Success)
    {
        /* Print message for user. */
        PRINTF("\r\n Successfully erased one sector of NOR flash device 0x%x -> 0x%x\r\n", serialNorAddress,
               (serialNorAddress + serialNorSectorSize));
    }
    else
    {
        PRINTF("\r\n Erase sector failure!\r\n");
        error_trap();
    }

    PRINTF("\r\n Program a buffer to a page of NOR flash");
    /* Prepare user buffer. */
    for (i = 0; i < BUFFER_LEN; i++)
    {
        s_buffer[i] = i;
    }

    /* Program user buffer into FLEXSPI NOR flash */
    status =
        ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, serialNorAddress, (const uint32_t *)s_buffer);
    if (status != kStatus_Success)
    {
        PRINTF("\r\n Page program failure!\r\n");
        error_trap();
    }

    DCACHE_InvalidateByRange(FlexSPISerialNorAddress, sizeof(s_buffer_rbc));
    /* Verify programming by reading back from FLEXSPI memory directly */
    memcpy(s_buffer_rbc, (void *)(FlexSPISerialNorAddress), sizeof(s_buffer_rbc));
    if (memcmp(s_buffer_rbc, s_buffer, sizeof(s_buffer)) == 0)
    {
        PRINTF("\r\n Successfully programmed and verified location FLEXSPI memory 0x%x -> 0x%x \r\n",
               (FlexSPISerialNorAddress), (FlexSPISerialNorAddress + sizeof(s_buffer)));
    }
    else
    {
        PRINTF("\r\n Program data -  read out data value incorrect!\r\n ");
        error_trap();
    }

    /* Erase the context we have progeammed before*/
    status = ROM_FLEXSPI_NorFlash_Erase(FlexSpiInstance, &norConfig, serialNorAddress, serialNorSectorSize);

    app_finalize();

    return 0;

#endif
    dummy();
}

void dummy(void)
{
	if(bl_pwr_on == 0)
	{
		HyperFlash();//initialization and erasing
		app_finalize();
	}
	else if(bl_pwr_on == 1)
	{
		jump_to_hyperflash_location(JUMP_ADDRESS);
	}
}
