case 0x00: /**** hlt ****/
    Halt = 1;
    Cycles += 4;
    break;

case 0x01: /**** hlt ****/
    Halt = 1;
    Cycles += 4;
    break;

case 0x02: /**** rlc ****/
    Carry = (A >> 7) & 1;
    A = (A << 1) | Carry;
    Cycles += 5;
    break;

case 0x03: /**** rnc ****/
    if (Carry == 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x04: /**** adi .1 ****/
    ADD(A,FETCH(),0);
    Cycles += 5;
    break;

case 0x05: /**** rst 00 ****/
    temp16 = 0x00;
    CALL();
    Cycles += 5;
    break;

case 0x06: /**** mvi a,.1 ****/
    A = FETCH();
    Cycles += 8;
    break;

case 0x07: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x08: /**** inr b ****/
    pszValue = ++B;
    Cycles += 5;
    break;

case 0x09: /**** dcr b ****/
    pszValue = --B;
    Cycles += 5;
    break;

case 0x0a: /**** rrc ****/
    Carry = A & 1;
    A = (A >> 1) | (Carry << 7);
    Cycles += 5;
    break;

case 0x0b: /**** rnz ****/
    if (pszValue != 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x0c: /**** aci .1 ****/
    ADD(A,FETCH(),Carry);
    Cycles += 5;
    break;

case 0x0d: /**** rst 08 ****/
    temp16 = 0x08;
    CALL();
    Cycles += 5;
    break;

case 0x0e: /**** mvi b,.1 ****/
    B = FETCH();
    Cycles += 8;
    break;

case 0x0f: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x10: /**** inr c ****/
    pszValue = ++C;
    Cycles += 5;
    break;

case 0x11: /**** dcr c ****/
    pszValue = --C;
    Cycles += 5;
    break;

case 0x12: /**** ral ****/
    temp16 = (A << 1) | Carry;
    Carry = (A >> 8) & 1;
    A = temp16;
    Cycles += 5;
    break;

case 0x13: /**** rp ****/
    if ((pszValue &0x80) == 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x14: /**** sub .1 ****/
    SUB(A,FETCH(),0);
    Cycles += 5;
    break;

case 0x15: /**** rst 10 ****/
    temp16 = 0x10;
    CALL();
    Cycles += 5;
    break;

case 0x16: /**** mvi c,.1 ****/
    C = FETCH();
    Cycles += 8;
    break;

case 0x17: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x18: /**** inr d ****/
    pszValue = ++D;
    Cycles += 5;
    break;

case 0x19: /**** dcr d ****/
    pszValue = --D;
    Cycles += 5;
    break;

case 0x1a: /**** rar ****/
    temp16 = A | (Carry << 8);
    Carry = A & 1;
    A = temp16 >> 1;
    Cycles += 5;
    break;

case 0x1b: /**** rpo ****/
    if (__parity(pszValue) != 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x1c: /**** sbi .1 ****/
    SUB(A,FETCH(),Carry);
    Cycles += 5;
    break;

case 0x1d: /**** rst 18 ****/
    temp16 = 0x18;
    CALL();
    Cycles += 5;
    break;

case 0x1e: /**** mvi d,.1 ****/
    D = FETCH();
    Cycles += 8;
    break;

case 0x1f: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x20: /**** inr e ****/
    pszValue = ++E;
    Cycles += 5;
    break;

case 0x21: /**** dcr e ****/
    pszValue = --E;
    Cycles += 5;
    break;

case 0x23: /**** rc ****/
    if (Carry != 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x24: /**** ani .1 ****/
    A = pszValue = A & FETCH();
    Carry = 0;
    Cycles += 5;
    break;

case 0x25: /**** rst 20 ****/
    temp16 = 0x20;
    CALL();
    Cycles += 5;
    break;

case 0x26: /**** mvi e,.1 ****/
    E = FETCH();
    Cycles += 8;
    break;

case 0x27: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x28: /**** inr h ****/
    pszValue = ++H;
    Cycles += 5;
    break;

case 0x29: /**** dcr h ****/
    pszValue = --H;
    Cycles += 5;
    break;

case 0x2b: /**** rz ****/
    if (pszValue == 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x2c: /**** xri .1 ****/
    A = pszValue = A ^ FETCH();
    Carry = 0;
    Cycles += 5;
    break;

case 0x2d: /**** rst 28 ****/
    temp16 = 0x28;
    CALL();
    Cycles += 5;
    break;

case 0x2e: /**** mvi h,.1 ****/
    H = FETCH();
    Cycles += 8;
    break;

case 0x2f: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x30: /**** inr l ****/
    pszValue = ++L;
    Cycles += 5;
    break;

case 0x31: /**** dcr l ****/
    pszValue = --L;
    Cycles += 5;
    break;

case 0x33: /**** rm ****/
    if ((pszValue &0x80) != 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x34: /**** ori .1 ****/
    A = pszValue = A | FETCH();
    Carry = 0;
    Cycles += 5;
    break;

case 0x35: /**** rst 30 ****/
    temp16 = 0x30;
    CALL();
    Cycles += 5;
    break;

case 0x36: /**** mvi l,.1 ****/
    L = FETCH();
    Cycles += 8;
    break;

case 0x37: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x3b: /**** rpe ****/
    if (__parity(pszValue) == 0) { RETURN();
     };
    Cycles += 4;
    break;

case 0x3c: /**** cpi .1 ****/
    CMP(A,FETCH());
    Cycles += 5;
    break;

case 0x3d: /**** rst 38 ****/
    temp16 = 0x38;
    CALL();
    Cycles += 5;
    break;

case 0x3e: /**** mvi m,.1 ****/
    WRITE(HL(),FETCH());
    Cycles += 9;
    break;

case 0x3f: /**** ret ****/
    RETURN();
    Cycles += 5;
    break;

case 0x40: /**** jnc .2 ****/
    FETCH16();
    if (Carry == 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x41: /**** inp 00 ****/
    A = INPORT00();
    Cycles += 8;
    break;

case 0x42: /**** cnc .2 ****/
    FETCH16();
    if (Carry == 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x43: /**** inp 01 ****/
    A = INPORT01();
    Cycles += 8;
    break;

case 0x44: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x45: /**** inp 02 ****/
    A = INPORT02();
    Cycles += 8;
    break;

case 0x46: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x47: /**** inp 03 ****/
    A = INPORT03();
    Cycles += 8;
    break;

case 0x48: /**** jnz .2 ****/
    FETCH16();
    if (pszValue != 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x49: /**** inp 04 ****/
    A = INPORT04();
    Cycles += 8;
    break;

case 0x4a: /**** cnz .2 ****/
    FETCH16();
    if (pszValue != 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x4b: /**** inp 05 ****/
    A = INPORT05();
    Cycles += 8;
    break;

case 0x4c: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x4d: /**** inp 06 ****/
    A = INPORT06();
    Cycles += 8;
    break;

case 0x4e: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x4f: /**** inp 07 ****/
    A = INPORT07();
    Cycles += 8;
    break;

case 0x50: /**** jp .2 ****/
    FETCH16();
    if ((pszValue &0x80) == 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x51: /**** out 08 ****/
    OUTPORT08(A);
    Cycles += 8;
    break;

case 0x52: /**** cp .2 ****/
    FETCH16();
    if ((pszValue &0x80) == 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x53: /**** out 09 ****/
    OUTPORT09(A);
    Cycles += 8;
    break;

case 0x54: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x55: /**** out 0a ****/
    OUTPORT0A(A);
    Cycles += 8;
    break;

case 0x56: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x57: /**** out 0b ****/
    OUTPORT0B(A);
    Cycles += 8;
    break;

case 0x58: /**** jpo .2 ****/
    FETCH16();
    if (__parity(pszValue) != 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x59: /**** out 0c ****/
    OUTPORT0C(A);
    Cycles += 8;
    break;

case 0x5a: /**** cpo .2 ****/
    FETCH16();
    if (__parity(pszValue) != 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x5b: /**** out 0d ****/
    OUTPORT0D(A);
    Cycles += 8;
    break;

case 0x5c: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x5d: /**** out 0e ****/
    OUTPORT0E(A);
    Cycles += 8;
    break;

case 0x5e: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x5f: /**** out 0f ****/
    OUTPORT0F(A);
    Cycles += 8;
    break;

case 0x60: /**** jc .2 ****/
    FETCH16();
    if (Carry != 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x61: /**** out 10 ****/
    OUTPORT10(A);
    Cycles += 8;
    break;

case 0x62: /**** cc .2 ****/
    FETCH16();
    if (Carry != 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x63: /**** out 11 ****/
    OUTPORT11(A);
    Cycles += 8;
    break;

case 0x64: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x65: /**** out 12 ****/
    OUTPORT12(A);
    Cycles += 8;
    break;

case 0x66: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x67: /**** out 13 ****/
    OUTPORT13(A);
    Cycles += 8;
    break;

case 0x68: /**** jz .2 ****/
    FETCH16();
    if (pszValue == 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x69: /**** out 14 ****/
    OUTPORT14(A);
    Cycles += 8;
    break;

case 0x6a: /**** cz .2 ****/
    FETCH16();
    if (pszValue == 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x6b: /**** out 15 ****/
    OUTPORT15(A);
    Cycles += 8;
    break;

case 0x6c: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x6d: /**** out 16 ****/
    OUTPORT16(A);
    Cycles += 8;
    break;

case 0x6e: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x6f: /**** out 17 ****/
    OUTPORT17(A);
    Cycles += 8;
    break;

case 0x70: /**** jm .2 ****/
    FETCH16();
    if ((pszValue &0x80) != 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x71: /**** out 18 ****/
    OUTPORT18(A);
    Cycles += 8;
    break;

case 0x72: /**** cm .2 ****/
    FETCH16();
    if ((pszValue &0x80) != 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x73: /**** out 19 ****/
    OUTPORT19(A);
    Cycles += 8;
    break;

case 0x74: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x75: /**** out 1a ****/
    OUTPORT1A(A);
    Cycles += 8;
    break;

case 0x76: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x77: /**** out 1b ****/
    OUTPORT1B(A);
    Cycles += 8;
    break;

case 0x78: /**** jpe .2 ****/
    FETCH16();
    if (__parity(pszValue) == 0) { JUMP();
     };
    Cycles += 10;
    break;

case 0x79: /**** out 1c ****/
    OUTPORT1C(A);
    Cycles += 8;
    break;

case 0x7a: /**** cpe .2 ****/
    FETCH16();
    if (__parity(pszValue) == 0) { CALL();
     };
    Cycles += 10;
    break;

case 0x7b: /**** out 1d ****/
    OUTPORT1D(A);
    Cycles += 8;
    break;

case 0x7c: /**** jmp .2 ****/
    FETCH16();
    JUMP();
    Cycles += 11;
    break;

case 0x7d: /**** out 1e ****/
    OUTPORT1E(A);
    Cycles += 8;
    break;

case 0x7e: /**** call .2 ****/
    FETCH16();
    CALL();
    Cycles += 11;
    break;

case 0x7f: /**** out 1f ****/
    OUTPORT1F(A);
    Cycles += 8;
    break;

case 0x80: /**** add a ****/
    ADD(A,A,0);
    Cycles += 5;
    break;

case 0x81: /**** add b ****/
    ADD(A,B,0);
    Cycles += 5;
    break;

case 0x82: /**** add c ****/
    ADD(A,C,0);
    Cycles += 5;
    break;

case 0x83: /**** add d ****/
    ADD(A,D,0);
    Cycles += 5;
    break;

case 0x84: /**** add e ****/
    ADD(A,E,0);
    Cycles += 5;
    break;

case 0x85: /**** add h ****/
    ADD(A,H,0);
    Cycles += 5;
    break;

case 0x86: /**** add l ****/
    ADD(A,L,0);
    Cycles += 5;
    break;

case 0x87: /**** add m ****/
    ADD(A,READ(HL()),0);
    Cycles += 8;
    break;

case 0x88: /**** adc a ****/
    ADD(A,A,Carry);
    Cycles += 5;
    break;

case 0x89: /**** adc b ****/
    ADD(A,B,Carry);
    Cycles += 5;
    break;

case 0x8a: /**** adc c ****/
    ADD(A,C,Carry);
    Cycles += 5;
    break;

case 0x8b: /**** adc d ****/
    ADD(A,D,Carry);
    Cycles += 5;
    break;

case 0x8c: /**** adc e ****/
    ADD(A,E,Carry);
    Cycles += 5;
    break;

case 0x8d: /**** adc h ****/
    ADD(A,H,Carry);
    Cycles += 5;
    break;

case 0x8e: /**** adc l ****/
    ADD(A,L,Carry);
    Cycles += 5;
    break;

case 0x8f: /**** adc m ****/
    ADD(A,READ(HL()),Carry);
    Cycles += 8;
    break;

case 0x90: /**** sub a ****/
    SUB(A,A,0);
    Cycles += 5;
    break;

case 0x91: /**** sub b ****/
    SUB(A,B,0);
    Cycles += 5;
    break;

case 0x92: /**** sub c ****/
    SUB(A,C,0);
    Cycles += 5;
    break;

case 0x93: /**** sub d ****/
    SUB(A,D,0);
    Cycles += 5;
    break;

case 0x94: /**** sub e ****/
    SUB(A,E,0);
    Cycles += 5;
    break;

case 0x95: /**** sub h ****/
    SUB(A,H,0);
    Cycles += 5;
    break;

case 0x96: /**** sub l ****/
    SUB(A,L,0);
    Cycles += 5;
    break;

case 0x97: /**** sub m ****/
    SUB(A,READ(HL()),0);
    Cycles += 8;
    break;

case 0x98: /**** sbb a ****/
    SUB(A,A,Carry);
    Cycles += 5;
    break;

case 0x99: /**** sbb b ****/
    SUB(A,B,Carry);
    Cycles += 5;
    break;

case 0x9a: /**** sbb c ****/
    SUB(A,C,Carry);
    Cycles += 5;
    break;

case 0x9b: /**** sbb d ****/
    SUB(A,D,Carry);
    Cycles += 5;
    break;

case 0x9c: /**** sbb e ****/
    SUB(A,E,Carry);
    Cycles += 5;
    break;

case 0x9d: /**** sbb h ****/
    SUB(A,H,Carry);
    Cycles += 5;
    break;

case 0x9e: /**** sbb l ****/
    SUB(A,L,Carry);
    Cycles += 5;
    break;

case 0x9f: /**** sbb m ****/
    SUB(A,READ(HL()),Carry);
    Cycles += 8;
    break;

case 0xa0: /**** and a ****/
    A = pszValue = A & A;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa1: /**** and b ****/
    A = pszValue = A & B;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa2: /**** and c ****/
    A = pszValue = A & C;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa3: /**** and d ****/
    A = pszValue = A & D;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa4: /**** and e ****/
    A = pszValue = A & E;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa5: /**** and h ****/
    A = pszValue = A & H;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa6: /**** and l ****/
    A = pszValue = A & L;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa7: /**** and m ****/
    A = pszValue = A & READ(HL());
    Carry = 0;
    Cycles += 8;
    break;

case 0xa8: /**** xor a ****/
    A = pszValue = A ^ A;
    Carry = 0;
    Cycles += 5;
    break;

case 0xa9: /**** xor b ****/
    A = pszValue = A ^ B;
    Carry = 0;
    Cycles += 5;
    break;

case 0xaa: /**** xor c ****/
    A = pszValue = A ^ C;
    Carry = 0;
    Cycles += 5;
    break;

case 0xab: /**** xor d ****/
    A = pszValue = A ^ D;
    Carry = 0;
    Cycles += 5;
    break;

case 0xac: /**** xor e ****/
    A = pszValue = A ^ E;
    Carry = 0;
    Cycles += 5;
    break;

case 0xad: /**** xor h ****/
    A = pszValue = A ^ H;
    Carry = 0;
    Cycles += 5;
    break;

case 0xae: /**** xor l ****/
    A = pszValue = A ^ L;
    Carry = 0;
    Cycles += 5;
    break;

case 0xaf: /**** xor m ****/
    A = pszValue = A ^ READ(HL());
    Carry = 0;
    Cycles += 8;
    break;

case 0xb0: /**** ora a ****/
    A = pszValue = A | A;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb1: /**** ora b ****/
    A = pszValue = A | B;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb2: /**** ora c ****/
    A = pszValue = A | C;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb3: /**** ora d ****/
    A = pszValue = A | D;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb4: /**** ora e ****/
    A = pszValue = A | E;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb5: /**** ora h ****/
    A = pszValue = A | H;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb6: /**** ora l ****/
    A = pszValue = A | L;
    Carry = 0;
    Cycles += 5;
    break;

case 0xb7: /**** ora m ****/
    A = pszValue = A | READ(HL());
    Carry = 0;
    Cycles += 8;
    break;

case 0xb8: /**** cmp a ****/
    CMP(A,A);
    Cycles += 5;
    break;

case 0xb9: /**** cmp b ****/
    CMP(A,B);
    Cycles += 5;
    break;

case 0xba: /**** cmp c ****/
    CMP(A,C);
    Cycles += 5;
    break;

case 0xbb: /**** cmp d ****/
    CMP(A,D);
    Cycles += 5;
    break;

case 0xbc: /**** cmp e ****/
    CMP(A,E);
    Cycles += 5;
    break;

case 0xbd: /**** cmp h ****/
    CMP(A,H);
    Cycles += 5;
    break;

case 0xbe: /**** cmp l ****/
    CMP(A,L);
    Cycles += 5;
    break;

case 0xbf: /**** cmp m ****/
    CMP(A,READ(HL()));
    Cycles += 8;
    break;

case 0xc0: /**** mov a,a ****/
    A = A;
    Cycles += 5;
    break;

case 0xc1: /**** mov a,b ****/
    A = B;
    Cycles += 5;
    break;

case 0xc2: /**** mov a,c ****/
    A = C;
    Cycles += 5;
    break;

case 0xc3: /**** mov a,d ****/
    A = D;
    Cycles += 5;
    break;

case 0xc4: /**** mov a,e ****/
    A = E;
    Cycles += 5;
    break;

case 0xc5: /**** mov a,h ****/
    A = H;
    Cycles += 5;
    break;

case 0xc6: /**** mov a,l ****/
    A = L;
    Cycles += 5;
    break;

case 0xc7: /**** mov a,m ****/
    A = READ(HL());
    Cycles += 8;
    break;

case 0xc8: /**** mov b,a ****/
    B = A;
    Cycles += 5;
    break;

case 0xc9: /**** mov b,b ****/
    B = B;
    Cycles += 5;
    break;

case 0xca: /**** mov b,c ****/
    B = C;
    Cycles += 5;
    break;

case 0xcb: /**** mov b,d ****/
    B = D;
    Cycles += 5;
    break;

case 0xcc: /**** mov b,e ****/
    B = E;
    Cycles += 5;
    break;

case 0xcd: /**** mov b,h ****/
    B = H;
    Cycles += 5;
    break;

case 0xce: /**** mov b,l ****/
    B = L;
    Cycles += 5;
    break;

case 0xcf: /**** mov b,m ****/
    B = READ(HL());
    Cycles += 8;
    break;

case 0xd0: /**** mov c,a ****/
    C = A;
    Cycles += 5;
    break;

case 0xd1: /**** mov c,b ****/
    C = B;
    Cycles += 5;
    break;

case 0xd2: /**** mov c,c ****/
    C = C;
    Cycles += 5;
    break;

case 0xd3: /**** mov c,d ****/
    C = D;
    Cycles += 5;
    break;

case 0xd4: /**** mov c,e ****/
    C = E;
    Cycles += 5;
    break;

case 0xd5: /**** mov c,h ****/
    C = H;
    Cycles += 5;
    break;

case 0xd6: /**** mov c,l ****/
    C = L;
    Cycles += 5;
    break;

case 0xd7: /**** mov c,m ****/
    C = READ(HL());
    Cycles += 8;
    break;

case 0xd8: /**** mov d,a ****/
    D = A;
    Cycles += 5;
    break;

case 0xd9: /**** mov d,b ****/
    D = B;
    Cycles += 5;
    break;

case 0xda: /**** mov d,c ****/
    D = C;
    Cycles += 5;
    break;

case 0xdb: /**** mov d,d ****/
    D = D;
    Cycles += 5;
    break;

case 0xdc: /**** mov d,e ****/
    D = E;
    Cycles += 5;
    break;

case 0xdd: /**** mov d,h ****/
    D = H;
    Cycles += 5;
    break;

case 0xde: /**** mov d,l ****/
    D = L;
    Cycles += 5;
    break;

case 0xdf: /**** mov d,m ****/
    D = READ(HL());
    Cycles += 8;
    break;

case 0xe0: /**** mov e,a ****/
    E = A;
    Cycles += 5;
    break;

case 0xe1: /**** mov e,b ****/
    E = B;
    Cycles += 5;
    break;

case 0xe2: /**** mov e,c ****/
    E = C;
    Cycles += 5;
    break;

case 0xe3: /**** mov e,d ****/
    E = D;
    Cycles += 5;
    break;

case 0xe4: /**** mov e,e ****/
    E = E;
    Cycles += 5;
    break;

case 0xe5: /**** mov e,h ****/
    E = H;
    Cycles += 5;
    break;

case 0xe6: /**** mov e,l ****/
    E = L;
    Cycles += 5;
    break;

case 0xe7: /**** mov e,m ****/
    E = READ(HL());
    Cycles += 8;
    break;

case 0xe8: /**** mov h,a ****/
    H = A;
    Cycles += 5;
    break;

case 0xe9: /**** mov h,b ****/
    H = B;
    Cycles += 5;
    break;

case 0xea: /**** mov h,c ****/
    H = C;
    Cycles += 5;
    break;

case 0xeb: /**** mov h,d ****/
    H = D;
    Cycles += 5;
    break;

case 0xec: /**** mov h,e ****/
    H = E;
    Cycles += 5;
    break;

case 0xed: /**** mov h,h ****/
    H = H;
    Cycles += 5;
    break;

case 0xee: /**** mov h,l ****/
    H = L;
    Cycles += 5;
    break;

case 0xef: /**** mov h,m ****/
    H = READ(HL());
    Cycles += 8;
    break;

case 0xf0: /**** mov l,a ****/
    L = A;
    Cycles += 5;
    break;

case 0xf1: /**** mov l,b ****/
    L = B;
    Cycles += 5;
    break;

case 0xf2: /**** mov l,c ****/
    L = C;
    Cycles += 5;
    break;

case 0xf3: /**** mov l,d ****/
    L = D;
    Cycles += 5;
    break;

case 0xf4: /**** mov l,e ****/
    L = E;
    Cycles += 5;
    break;

case 0xf5: /**** mov l,h ****/
    L = H;
    Cycles += 5;
    break;

case 0xf6: /**** mov l,l ****/
    L = L;
    Cycles += 5;
    break;

case 0xf7: /**** mov l,m ****/
    L = READ(HL());
    Cycles += 8;
    break;

case 0xf8: /**** mov m,a ****/
    WRITE(HL(),A);
    Cycles += 7;
    break;

case 0xf9: /**** mov m,b ****/
    WRITE(HL(),B);
    Cycles += 7;
    break;

case 0xfa: /**** mov m,c ****/
    WRITE(HL(),C);
    Cycles += 7;
    break;

case 0xfb: /**** mov m,d ****/
    WRITE(HL(),D);
    Cycles += 7;
    break;

case 0xfc: /**** mov m,e ****/
    WRITE(HL(),E);
    Cycles += 7;
    break;

case 0xfd: /**** mov m,h ****/
    WRITE(HL(),H);
    Cycles += 7;
    break;

case 0xfe: /**** mov m,l ****/
    WRITE(HL(),L);
    Cycles += 7;
    break;

case 0xff: /**** hlt ****/
    Halt = 1;
    Cycles += 4;
    break;

