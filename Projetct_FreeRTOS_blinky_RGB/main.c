/*------------------------------------------------------------------------------*//**
    @file       <nome>

    @brief      <resumo>

    @version    <verção>
    @date       <data>

    @note       <observaçoes>

    @par        <implicaçoes legais>

-------------------------------------------------------------------------------------*/
/*-----------------------------------Headers-----------------------------------------*/
//  Compiler
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//  Project
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "drivers/rgb.h"
#include "drivers/buttons.h"

//  FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//  User

/*----------------------------Definition-System---------------------------------------*/
// The priorities of the various tasks.
//
#define PRIORITY_SWITCH_TASK    2
#define PRIORITY_LED_TASK       1
//
// The stack size for the LED toggle task.
//
#define LEDTASKSTACKSIZE        128         // Stack size in words
//
// The stack size for the display task.
//
#define SWITCHTASKSTACKSIZE        128         // Stack size in words
//
// The item size and queue size for the LED message queue.
//
#define LED_ITEM_SIZE           sizeof(uint8_t)
#define LED_QUEUE_SIZE          5
//
// Default LED toggle delay value. LED toggling frequency is twice this number.
//
#define LED_TOGGLE_DELAY        250
/*--------------------------------structs---------------------------------------------*/

/*----------------------------Global-Variables----------------------------------------*/
xQueueHandle g_pLEDQueue;
xSemaphoreHandle g_pUARTSemaphore;
//
// [G, R, B] range is 0 to 0xFFFF per color.
//
static uint32_t g_pui32Colors[3] = { 0x0000, 0x0000, 0x0000 };
static uint8_t g_ui8ColorsIndx;
/*-------------------------------Prototypes-------------------------------------------*/

void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName);
void ConfigureUART(void);
uint32_t LEDTaskInit(void);
uint32_t SwitchTaskInit(void);
/*---------------------------------Debug----------------------------------------------*/
//! The error routine that is called if the driver library encounters an error.
//
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

/*=================================Start==============================================*/
int main(void)
{
/*-----------------------------Main-Variables-----------------------------------------*/

/*---------------------------Peripheral Initialization--------------------------------*/
    // Set the clocking to run at 50 MHz from the PLL.
    //
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
    //
    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    //
    ConfigureUART();
    //
    // Print demo introduction.
    //
    UARTprintf("\n\nUART OK!\n");
    //
    // Create a mutex to guard the UART.
    //
    g_pUARTSemaphore = xSemaphoreCreateMutex();
    //
    // Create the LED task.
    //
    if(LEDTaskInit() != 0)
    {
        while(1)
        {
        }
    }
    //
    // Create the switch task.
    //
    if(SwitchTaskInit() != 0)
    {
        while(1)
        {
        }
    }
    //
    // Start the scheduler.  This should not return.
    //
    vTaskStartScheduler();
    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //
/*---------------------------------Loop-----------------------------------------------*/
    //
    // // Will not get here unless there is insufficient RAM.
    //
    while(1)
    {
    }
}

/*-----------------------------------Functions----------------------------------------*/
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //
    // Enable UART0
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //
    // Configure GPIO Pins for UART mode.
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

static void LEDTask(void *pvParameters)
{
    portTickType ui32WakeTime;
    uint32_t ui32LEDToggleDelay;
    uint8_t i8Message;
    //
    // Initialize the LED Toggle Delay to default value.
    //
    ui32LEDToggleDelay = LED_TOGGLE_DELAY;
    //
    // Get the current tick count.
    //
    ui32WakeTime = xTaskGetTickCount();
    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Read the next message, if available on queue.
        //
        if(xQueueReceive(g_pLEDQueue, &i8Message, 0) == pdPASS)
        {
            //
            // If left button, update to next LED.
            //
            if(i8Message == LEFT_BUTTON)
            {
                //
                // Update the LED buffer to turn off the currently working.
                //
                g_pui32Colors[g_ui8ColorsIndx] = 0x0000;
                //
                // Update the index to next LED
                g_ui8ColorsIndx++;
                if(g_ui8ColorsIndx > 2)
                {
                    g_ui8ColorsIndx = 0;
                }
                //
                // Update the LED buffer to turn on the newly selected LED.
                //
                g_pui32Colors[g_ui8ColorsIndx] = 0x8000;
                //
                // Configure the new LED settings.
                //
                RGBColorSet(g_pui32Colors);
                //
                // Guard UART from concurrent access. Print the currently
                // blinking LED.
                //
                xSemaphoreTake(g_pUARTSemaphore, portMAX_DELAY);
                UARTprintf("Led %d is blinking. [R, G, B]\n", g_ui8ColorsIndx);
                xSemaphoreGive(g_pUARTSemaphore);
            }
            //
            // If right button, update delay time between toggles of led.
            //
            if(i8Message == RIGHT_BUTTON)
            {
                ui32LEDToggleDelay *= 2;
                if(ui32LEDToggleDelay > 1000)
                {
                    ui32LEDToggleDelay = LED_TOGGLE_DELAY / 2;
                }
                //
                // Guard UART from concurrent access. Print the currently
                // blinking frequency.
                //
                xSemaphoreTake(g_pUARTSemaphore, portMAX_DELAY);
                UARTprintf("Led blinking frequency is %d ms.\n",
                           (ui32LEDToggleDelay * 2));
                xSemaphoreGive(g_pUARTSemaphore);
            }
        }
        //
        // Turn on the LED.
        //
        RGBEnable();
        //
        // Wait for the required amount of time.
        //
        vTaskDelayUntil(&ui32WakeTime, ui32LEDToggleDelay / portTICK_RATE_MS);
        //
        // Turn off the LED.
        //
        RGBDisable();
        //
        // Wait for the required amount of time.
        //
        vTaskDelayUntil(&ui32WakeTime, ui32LEDToggleDelay / portTICK_RATE_MS);
    }
}
//
// Initializes the LED task.
//
uint32_t LEDTaskInit(void)
{
    //
    // Initialize the GPIOs and Timers that drive the three LEDs.
    //
    RGBInit(1);
    RGBIntensitySet(0.3f);
    //
    // Turn on the Green LED
    //
    g_ui8ColorsIndx = 0;
    g_pui32Colors[g_ui8ColorsIndx] = 0x8000;
    RGBColorSet(g_pui32Colors);
    //
    // Print the current loggling LED and frequency.
    //
    UARTprintf("\nLed %d is blinking. [R, G, B]\n", g_ui8ColorsIndx);
    UARTprintf("Led blinking frequency is %d ms.\n", (LED_TOGGLE_DELAY * 2));
    //
    // Create a queue for sending messages to the LED task.
    //
    g_pLEDQueue = xQueueCreate(LED_QUEUE_SIZE, LED_ITEM_SIZE);
    //
    // Create the LED task.
    //
    if(xTaskCreate(LEDTask, (const portCHAR *)"LED", LEDTASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_LED_TASK, NULL) != pdTRUE)
    {
        return(1);
    }
    //
    // Success.
    //
    return(0);
}
//
// This task reads the buttons' state and passes this information to LEDTask.
//
static void SwitchTask(void *pvParameters)
{
    portTickType ui16LastTime;
    uint32_t ui32SwitchDelay = 25;
    uint8_t ui8CurButtonState, ui8PrevButtonState;
    uint8_t ui8Message;
    ui8CurButtonState = ui8PrevButtonState = 0;
    //
    // Get the current tick count.
    //
    ui16LastTime = xTaskGetTickCount();
    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Poll the debounced state of the buttons.
        //
        ui8CurButtonState = ButtonsPoll(0, 0);
        //
        // Check if previous debounced state is equal to the current state.
        //
        if(ui8CurButtonState != ui8PrevButtonState)
        {
            ui8PrevButtonState = ui8CurButtonState;
            //
            // Check to make sure the change in state is due to button press
            // and not due to button release.
            //
            if((ui8CurButtonState & ALL_BUTTONS) != 0)
            {
                if((ui8CurButtonState & ALL_BUTTONS) == LEFT_BUTTON)
                {
                    ui8Message = LEFT_BUTTON;
                    //
                    // Guard UART from concurrent access.
                    //
                    xSemaphoreTake(g_pUARTSemaphore, portMAX_DELAY);
                    UARTprintf("Left Button is pressed.\n");
                    xSemaphoreGive(g_pUARTSemaphore);
                }
                else if((ui8CurButtonState & ALL_BUTTONS) == RIGHT_BUTTON)
                {
                    ui8Message = RIGHT_BUTTON;
                    //
                    // Guard UART from concurrent access.
                    //
                    xSemaphoreTake(g_pUARTSemaphore, portMAX_DELAY);
                    UARTprintf("Right Button is pressed.\n");
                    xSemaphoreGive(g_pUARTSemaphore);
                }
                //
                // Pass the value of the button pressed to LEDTask.
                //
                if(xQueueSend(g_pLEDQueue, &ui8Message, portMAX_DELAY) !=
                   pdPASS)
                {
                    //
                    // Error. The queue should never be full. If so print the
                    // error message on UART and wait for ever.
                    //
                    UARTprintf("\nQueue full. This should never happen.\n");
                    while(1)
                    {
                    }
                }
            }
        }
        //
        // Wait for the required amount of time to check back.
        //
        vTaskDelayUntil(&ui16LastTime, ui32SwitchDelay / portTICK_RATE_MS);
    }
}
//
// Initializes the switch task.
//
uint32_t SwitchTaskInit(void)
{
    //
    // Unlock the GPIO LOCK register for Right button to work.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0xFF;
    //
    // Initialize the buttons
    //
    ButtonsInit();
    //
    // Create the switch task.
    //
//    #define xTaskCreate( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask )
//    xTaskGenericCreate( ( pvTaskCode ), ( pcName ), ( usStackDepth ), ( pvParameters ), ( uxPriority ),
//                        ( pxCreatedTask ), ( NULL ), ( NULL ) )
    if(xTaskCreate(SwitchTask,                               //pvTaskCode
                   (const portCHAR *)"Switch",               //pcName
                   SWITCHTASKSTACKSIZE,                      //usStackDepth
                   NULL,                                     //pvParameters
                   tskIDLE_PRIORITY + PRIORITY_SWITCH_TASK,  //uxPriority
                   NULL                                      //pxCreatedTask
                   ) != pdTRUE)
    {
        return(1);
    }
    //
    // Success.
    //
    return(0);
}
