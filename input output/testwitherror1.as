.entry LIST
.extern W
MAIN:       add r3,LIST
LOOP:       prn #48
            lea r1, W
            inc r6
            mov r3, K
            sub r1, r4
            bne END
            cmp K, #-6

            bne &END
            dec W
.entry MAIN        
            jmp &LOOP
            add L3, L3
END:     stoppp
STR: .string "ab"cd"
LIST:       .data 6,-9-
            .data ,-100
K:          .data 3-1
.extern L3 
