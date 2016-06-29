#
#	8008 Processor.
#

import re

def process(s,opcode,offset):
	s = s.replace("@S","ABCDEHLM"[offset & 7])
	s = s.replace("@P","{0:02X}".format((opcode >> 1) & 0x1F))
	s = s.replace("@V","{0:02X}".format(opcode & 0x38))
	s = s.replace("@R","A,B,C,D,E,H,L,READ(HL())".split(",")[offset & 7])
	s = s.replace("@C","NC,NZ,P,PO,C,Z,M,PE".split(",")[offset & 7])
	tst = "Carry == 0,pszValue != 0,(pszValue &0x80) == 0,__parity(pszValue) != 0,"
	tst += "Carry != 0,pszValue == 0,(pszValue &0x80) != 0,__parity(pszValue) == 0"
	s = s.replace("@T",tst.split(",")[offset & 7])
	return s

code = [ None ] * 256
mnemonics = [ None ] * 256
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in open("8008.def").readlines()]		
src = [x.replace("\t"," ").strip() for x in src if x.strip() != ""]
open("__8008_macros.h","w").write("\n".join([x[1:] for x in src if x[0] == ':']))
for l in [x for x in src if x[0] != ':']:
	m = re.match('^([0-9A-F\\-\\,]+)\\s*(\\d+)\\s*\\"(.*)\\"\\s*(.*)$',l)
	assert m is not None,"Syntax "+l
	r = m.group(1) if len(m.group(1)) != 2 else m.group(1)+"-"+m.group(1)
	r = r if len(m.group(1)) == 7 else r+",1"

	for opcode in range(int(r[:2],16),int(r[3:5],16)+1,int(r[-1])):
		offset = opcode / int(r[-1])
		assert mnemonics[opcode] is None,"Duplicate "+l
		mnemonics[opcode] = process(m.group(3),opcode,offset).lower()
		cycles = int(m.group(2))
		if opcode >= 0x80 and opcode < 0xF8 and (opcode & 7) == 7:
			cycles += 3
		code[opcode] = process(m.group(4),opcode,offset)+";Cycles += {0};break;".format(cycles)

for i in range(0,256):
	if mnemonics[i] is None:
		mnemonics[i] = "db {0:02x}".format(i)

open("__8008_mnemonics.h","w").write(",".join(['"'+x+'"' for x in mnemonics]))

h = open("__8008_opcodes.h","w")
for i in range(0,256):
	if code[i] is not None:
		h.write("case 0x{0:02x}: /**** {1} ****/\n".format(i,mnemonics[i]))
		x = ["    "+x+";" for x in code[i].split(";") if x != ""]
		h.write("\n".join(x)+"\n\n")
h.close()

h = open("__8008_ports.h","w")
for i in range(0,8):
	h.write("#ifndef INPORT{0:02X}\n#define INPORT{0:02X}() (0)\n#endif\n".format(i))
for i in range(8,32):
	h.write("#ifndef OUTPORT{0:02X}\n#define OUTPORT{0:02X}(d) {{}}\n#endif\n".format(i))	

print("Generation completed.")