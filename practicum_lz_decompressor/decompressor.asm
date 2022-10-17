.cpu cortex-m0
.align 2                        // Align om te zorgen dat alle bits goed gespaced worden.
.bss                            // BSS segment    
buffer: .space 4096             // Buffer aanmaken.

.text                           // Dit is een text sectie
.global application             // Implementatie application functie vanuit main
.global decompressor            // Implementatie decompressor functie vanuit main

application:                    // Application functie
    push {r4 - r7, lr}          // Verplaats de huidige positie (pc) naar lr.
    ldr r5, =wilhelmus_string   // Laad dit label in op r5. Pointer naar waar de string in het geheugen begint.
    ldr r4, =buffer             // Laad label naar buffer geheugen adres naar r4. Pointer naar waar het buffer segment in het geheugen begint.
    bl decompressor             // Roep de decompressor functie aan. Functie krijgt r0 als parameter mee.

decompressor:                   // Decompressor functie
    ldrb r0, [r5]               // Schrijf de waarde die op geheugen r5 zit naar r0.
    add r0, r0, #0              // Vergelijk de waarde in r0 met 0.
    beq string_done             // Als dit het geval is break.
    cmp r0, #'@'                // Check if '@'
    beq buffer_callback         // Wanneer waar naar 'buffer_callback'
    strb r0, [r4]               // Store de waarde van r0 op de plek van r4 naartoe wijst (waar is de buffer op dat moment) --> schrijf char naar buffer
    bl uart_put_char            // Print ascii char
    add r5, r5, #1              // Huidige char index +1
    add r4, r4, #1              // Huidige buffer index +1
    b decompressor              // Herstart decompressor functie

string_done:
    pop {r4 - r7, pc}           // Haal de before register waarden op en de oude program counter.

buffer_callback:
    add r5, r5, #1              // Tel 1 op bij de string positie pointer om te weten hoeveel plekken terug
    ldrb r6, [r5]               // Laad de waarde op deze plek in in r6 (aantal plekken terug) --> F | klopt
    add r5, r5, #1              // Tel 1 op bij de string positie pointer voor aantal chars dat moet worden terug gezet
    ldrb r7, [r5]               // Sla de waarde op deze plek op in register 7 (aantal chars) --> 5 | klopt
    sub r6, r6, #47             // R6 = ascii 23 --> dus 23 posities terug; 0 wordt nummer 1
    sub r6, r4, r6              // Buffer pointer posities terug. De pointer naar waar de terug herhaling staat wordt in R6 gezet.
    sub r7, r7, #47             // Resultaat is int 5 ipv char 5
    b loop_buffer               // Start buffer loop

loop_buffer:
    cmp r7, #1                  // Vergelijk r7 met 1 
    beq buffer_done             // Branch wanneer r7 == 1 --> Aantal herhaalde chars zijn verwerkt. Spring naar buffer done (break).
    ldrb r0, [r6]               // Schrijf de waarde op r6 (plek van de eerdere herhaling) naar r0.
    strb r0, [r4]               // Schrijf de waarde in r0 naar de plek van de pointer van de buffer r4.
    bl uart_put_char            // Cout het karakter
    add r6, r6, #1              // Tel 1 op bij de herhaling pointer
    sub r7, r7, #1              // Haal 1 af bij r7 (aantal herhalingen -1)
    add r4, r4, #1              // Schuif de eind buffer pointer op met 1.
    b loop_buffer               // Herhaal de loop
    
buffer_done:
    add r5, r5, #1              // Tel 1 op bij de huidige char pointer
    b decompressor              // Ga terug de loop in voor het volgende char
    