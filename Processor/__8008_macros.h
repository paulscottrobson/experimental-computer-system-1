static BYTE8  A,B,C,D,E,H,L,Halt,Carry,pszValue,PCP;
static WORD16  PC[8],Cycles,temp16;
static void Reset8008()
{
 A = B = C = D = E = H = L = Halt = 0;Carry = pszValue = PCP = Cycles = 0;
 for (BYTE8 i = 0;i < 8;i++) PC[i] = 0;
}
#define FETCH() READ(PC[PCP]++)
#define HL()   ((((WORD16)H) << 8)|L)
static BYTE8 __parity(BYTE8 n)
{
 BYTE8 p = 0;
 while (n != 0) {
  if (n & 1) p = p ^ 1;
  n = n >> 1;
 }
 return p;
}
#define ADD(n1,n2,n3) { temp16 = (n1)+(n2)+(n3);A = pszValue = temp16 & 0xFF;Carry = (temp16 >> 8) & 1; }
#define SUB(n1,n2,n3)  { temp16 = (n1)-(n2)-(n3);A = pszValue = temp16 & 0xFF;Carry = (temp16 >> 8) & 1; }
#define CMP(n1,n2)   { temp16 = (n1)-(n2);pszValue = temp16 & 0xFF;Carry = (temp16 >> 8) & 1; }
#define FETCH16()  { temp16 = FETCH();temp16 |= (FETCH() << 8); }
#define JUMP()  PC[PCP] = temp16 & 0x3FFF;
#define CALL()  { PC[++PCP] = temp16 & 0x3FFF;PCP &= 7; }
#define RETURN() PCP = (PCP-1) & 7;