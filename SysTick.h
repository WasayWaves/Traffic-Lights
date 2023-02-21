    AREA    Reset, CODE, READONLY
    ENTRY

Reset_Handler   PROC
                ; set up GPIO ports
                LDR     R0, =0x400FE608 ; system control base address
                MOV     R1, #0x10      ; enable GPIO port B
                STR     R1, [R0, #0x608]
                MOV     R1, #0x04      ; enable GPIO port A
                STR     R1, [R0, #0x608]

                ; set up GPIO pins
                LDR     R0, =0x40004400 ; GPIO port B base address
                MOV     R1, #0x3F      ; set PB5-PB0 as outputs
                STR     R1, [R0, #0x400]
                LDR     R0, =0x40004000 ; GPIO port A base address
                MOV     R1, #0x00      ; set PA5-3 as inputs
                STR     R1, [R0, #0x400]

loop            ; read switch input and turn on corresponding LED
                LDR     R0, =0x40004010 ; read switch input from PA5-3
                LDR     R1, [R0, #0x400]
                LSL     R1, R1, #3     ; shift input to bits 5-3
                LDR     R0, =0x400043FC ; GPIO port B output data register
                STR     R1, [R0, #0x400]

                ; walk LED sequence
                LDR     R0, =0x400253FC ; GPIO port F output data register
                MOV     R1, #0x0A      ; turn on "walk" light
                STR     R1, [R0, #0x400]
                BL      delay          ; wait
                MOV     R1, #0x08      ; turn off "walk" light
                STR     R1, [R0, #0x400]
                BL      delay          ; wait
                MOV     R1, #0x0A      ; turn on "walk" light
                STR     R1, [R0, #0x400]
                BL      delay          ; wait
                MOV     R1, #0x08      ; turn off "walk" light
                STR     R1, [R0, #0x400]
                BL      delay          ; wait
                B       loop           ; repeat

delay           ; delay subroutine
                MOV     R2, #0x00      ; initialize delay counter
delay_loop      SUBS    R2, R2, #1     ; decrement counter
                BNE     delay_loop     ; loop until counter reaches 0
                BX      LR

                END
