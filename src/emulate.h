#ifndef EMULATEDEFS
#define EMULATEDEFS

#include <stdlib.h>
#include <stdint.h>

typedef int bool;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef MEM16BIT
#define MEM16BIT 65536
#endif

//execute return values
const int EXE_HALT = 0;
const int EXE_CONTINUE = -1;
const int EXE_BRANCH = 1;

// Instruction types
const int BRANCH = 128;
const int DATA_TRANS = 64;
const int MULT = 32;
const int DATA_PROC = 16;
const int HALT = 0;

typedef struct {
  uint8_t cond;
  uint8_t instType;
  uint8_t opcode;
  uint8_t rn;
  uint8_t rd;
  uint8_t rm;
  uint8_t rs;
  int32_t operandOffset;
} DecodedInst;

struct regFile {
  uint32_t *reg; // registers 0-13 are general purpose.
  uint32_t *SP;
  uint32_t *LR;
  uint32_t *PC;
  uint32_t *CPSR;
};

const int NUM_REG = 17; // number of registers
const int NUM_GREG = 13; // number of general purpose registers
const int Nbit = 31; // position of status bits in CPSR
const int Zbit = 30;
const int Cbit = 29;
const int Vbit = 28;

// execute functions --
int execute(DecodedInst di);
void executeDataProcessing(uint8_t instType, uint8_t opcode, uint8_t Rn, uint8_t Rd, uint32_t operand);
uint32_t barrelShift(uint32_t valu, int shiftSeg, int s);
void setCPSRZN(int value, int trigger);
void executeMult(uint8_t instType, uint8_t rd, uint8_t rn, uint8_t rs, uint8_t rm);
void executeSingleDataTransfer(uint8_t instType, uint8_t rn, uint8_t rd, uint32_t offset);
void executeBranch(int offset);
void testingDataProc(void);
void testingExecute(void);
// --
void dealloc(void);
void loadFileToMem(char const *file);
void outputMemReg(void);
void clearRegfile (void);
// helper functions --
void printSpecialReg(uint32_t value, char message[]);
int64_t ipow(int x, int y);
int rotr8(uint8_t x, int n);
int rotr32(uint32_t x, int n);
void enterC(void);  //WILL REMOVE
void alterC(bool set);
void alterZ(bool set);
void alterV(bool set);
void alterN(bool set);
void testingHelpers(void);
int getBit(uint32_t x, int pos);
uint32_t getBinarySeg(uint32_t x, uint32_t start, uint32_t length);
//--
int32_t fetch(uint8_t *mem);
DecodedInst decode(int32_t instruction);
uint8_t getInstType(int32_t instruction);

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

// dont keep getFlags()
//***********************

void decodeForDataProc(int32_t instruction, DecodedInst *di);
void decodeForMult(int32_t instruction, DecodedInst *di);
void decodeForDataTrans(int32_t instruction, DecodedInst *di);
void decodeForBranch(int32_t instruction, DecodedInst *di);

#endif /* end of include guard: EMULATEDEFS */
