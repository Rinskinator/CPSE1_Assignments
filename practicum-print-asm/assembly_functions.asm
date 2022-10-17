.cpu cortex-m0
.text                       // Dit is een text sectie
.align 2                    // Align om te zorgen dat alle bits goed gespaced worden.
.global print_asciz
.global application

print_asciz:
    push {r5, lr}           // r0 verwijst naar de eerste parameter en push de huidige pc naar lr. R0 is de pointer (het adres waar het eerste karakter van de string staat) naar het begin van de string.
    mov r5, r0              // Verplaats de inhoud van r0 naar R5, omdat R5 niet zomaar mag worden veranderd.
asciz_loop:
    ldrb r0, [r5]           // Schrijf de waarde die op geheugen adres 5 zit naar r0.
    add r0, r0, #0          // Vergelijk de waarde in r0 met 0.
    beq asciz_done          // Als dit het geval is break.
    bl uart_put_char        // Als dit niet het geval is roep dan uart_put_char functie aan.
    add r5, r5, #1          // Tel 1 op bij de pointer naar de string.
    b asciz_loop            // begin de loop opnieuw
asciz_done:
    pop {r5, pc}            // Haal de before waarde van r5 op en de oude program counter.


application:
    push {lr}               // Verplaats de huidige positie (pc) naar lr.
    ldr r0, =asciz_string   // Laad dit label in op r0.
    bl print_asciz          // Roep de print_asciz functie aan. Functie krijgt r0 als parameter mee.
    pop {pc}

.data                       // Data sectie
asciz_string:                        
    .ascii "Hello world, the ANSWER is 42! @[]`{}~\n"
    .align 1                // Zorg dat het register is gevuld.
