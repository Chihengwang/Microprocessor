.syntax unified
.cpu cortex-m4
.thumb

.data
    Leds: .byte 0

.text
    .global main
    .include "../src/pin.s"  // import GPIO constants

DisplayLED:
    PUSH {r1, r2, lr}
    ldr r1, =GPIOB_ODR
    ldr r2, [r1]          // Get Current Output
    and r2, #0x0   // Clear PB3 to PB6
    orr r2, #0xDF          // Set the output bits
    str r2, [r1]          // Write back to Output Reg
    POP {r1, r2, pc}
GPIO_init:
    // Enable AHB2 clock
    movs r0, #0x6
    ldr r1, =RCC_AHB2ENR
    str r0, [r1]
    // Set PB3 ~ PB6 to output mode
    ldr r1, =GPIOB_MODER
    ldr r0, [r1]
    and r0, #0xFFFFC03F
    orr r0, #0x1540
    str r0, [r1]
    // Set PB3 ~ PB6 to high speed
    ldr r1, =GPIOB_OSPEEDR
    ldr r0, [r1]
    and r0, #0xFFFFC03F
    orr r0, #0x2A80
    str r0, [r1]
    // Set PB3 ~ PB6 to pullup
    ldr r1, =GPIOB_PUPDR
    ldr r0, [r1]
    and r0, #0xFFFFC03F
    orr r0, #0x1540
    str r0, [r1]
    // Set PC13 to input mode
    ldr r1, =GPIOC_MODER
    ldr r0, [r1]
    and r0, #0xF3FFFFFF
    orr r0, #0x0
    str r0, [r1]
    bx lr
main:
    bl GPIO_init    // Setup GPIO
    b DisplayLED

L: b L
