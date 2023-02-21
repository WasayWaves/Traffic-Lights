// SysTick.c
// Runs on TM4C123
// Put your names here
// Last Modified: 8/21/2022
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

;=======================================================================
; Function: SysTick_Init
; Description: Initialize SysTick with busy wait running at bus clock.
;=======================================================================
SysTick_Init PROC
    ; enable SysTick interrupt and clock
    LDR R0, =0xE000E010
    MOV R1, #0x00000007 ; set enable, interrupt, and clock source bits
    STR R1, [R0]

    ; set SysTick reload value to maximum
    LDR R0, =0xE000E014
    MOV R1, #0x00FFFFFF ; set reload value
    STR R1, [R0]

    ; enable SysTick
    LDR R0, =0xE000E010
    MOV R1, #0x00000001 ; set enable bit
    STR R1, [R0]

    BX LR ; return from subroutine
ENDP

;=======================================================================
; Function: SysTick_Wait
; Description: Wait for a specified number of core clock cycles using busy
;              wait with the SysTick timer.
; Input: R0 = delay
;=======================================================================
SysTick_Wait PROC
    ; load delay value into SysTick reload value register
    LDR R1, =0xE000E014
    STR R0, [R1]

    ; clear SysTick current value register
    LDR R1, =0xE000E018
    MOV R2, #0x00000000 ; set current value to zero
    STR R2, [R1]

    ; wait for count flag to be set (indicates time has elapsed)
    LDR R1, =0xE000E010
    MOV R2, #0x00000001 ; set count flag bit
wait_loop
    LDR R3, [R1]
    TST R3, R2 ; test count flag bit
    BEQ wait_loop

    BX LR ; return from subroutine
ENDP

;=======================================================================
; Function: SysTick_Wait10ms
; Description: Wait for a specified number of 10ms intervals using
;              SysTick_Wait subroutine.
; Input: R0 = delay
;=======================================================================
SysTick_Wait10ms PROC
    ; divide delay by 10 to get number of 10ms intervals
    MOV R1, R0
    MOV R2, #0x0000000A ; divide by 10
    SDIV R0, R1, R2

    ; loop for number of 10ms intervals, calling SysTick_Wait each time
delay_loop
    CBZ R0, done
    BL SysTick_Wait
    SUB R0, R0, #0x00000001 ; decrement delay counter
    B delay_loop

done
    BX LR ; return from subroutine
ENDP

