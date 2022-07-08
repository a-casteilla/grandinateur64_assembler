/**
 * \file mnemonic.h
 * \brief All definition related to mnemonic translation
 * \author Aurélien Casteilla
 * \version 0.1
 * \date 22th may 2022
 *
 */

#ifndef MNEMONIC_H

#define MNEMONIC_H

#include <stdint.h>

/**
 * \enum family
 * \brief List of the different families of instructions
 *
 * The families of instruction are defined by the syntax of the instruction and
 * the effect on the memory of the instruction (the size and influence on the
 * pc)
 */
enum family {
  mem_family,            /*!< memory instructions (load and store)*/
  alu_family,            /*!< arithmetic and logic instructions (add, subtract, and, or, etc.)*/
  brc_family,            /*!< branch instructions (bal, blk, and conditionnal branches)*/
  sta_family,            /*!< status instructions (tsr, trs, tcr, trc, rti) */
  sys_family,            /*!< the sys instruction */
  dd_directive,          /*!< the data double-word directive */
  dw_directive,          /*!< the data word directive */
  dh_directive,          /*!< the data half-word directive */
  db_directive,          /*!< the data byte directive */
  ascii_directive,       /*!< the ascii directive */
  asciz_directive,       /*!< the ascii zero directive */
  align_directive,       /*!< the align directive */
  ad_directive,          /*!< the align double-word directive */
  aw_directive,          /*!< the align word directive */
  ah_directive,          /*!< the align half-word directive */
  pc_directive,          /*!< the pc directive */
  bin_directive,         /*!< the insert binary directive */
  def_directive,         /*!< the define constant directive */
  no_mnemonic,           /*!< the line doesn't contain something meaningful */
  open_scope_directive,  /*!< the '{' to open a scope */
  close_scope_directive, /*!< the '}' to close a scope */
  import_directive,      /*!< the import directive */
  export_directive,      /*!< the export directive */
  npc_directive          /*!< the next pc directive */
};

/**
 * \def SUFFIX_BIT
 * \brief the bit corresponding to an instruction with the -S suffix 
 */
#define SUFFIX_BIT         0x00100000

/**
 * \struct mnemo
 * \brief The mnemonic translation table
 *
 * This table contains each mnemonic associated with its opcode and with its
 * family
 */
static const struct {
  uint32_t word;
  char mnemo[8];
  int family;
} mnemo[] = {
  { 0, "", no_mnemonic },            /*!< No instruction */
  { 0x0f000000, "LDW", mem_family },
  { 0x0e800000, "LWS", mem_family },
  { 0x0e000000, "LWU", mem_family },
  { 0x0d800000, "LHS", mem_family },
  { 0x0d000000, "LHU", mem_family },
  { 0x0c800000, "LBS", mem_family },
  { 0x0c000000, "LBU", mem_family },
  { 0x0b000000, "STD", mem_family },
  { 0x0a000000, "STW", mem_family },
  { 0x09000000, "STH", mem_family },
  { 0x08000000, "STB", mem_family },
  { 0x0a800000, "STW", mem_family },
  { 0x09800000, "STH", mem_family },
  { 0x08800000, "STB", mem_family },
  { 0x0f800000, "LLD", mem_family },
  { 0x0b800000, "SCD", mem_family },

  { 0x00600000, "ADD", alu_family },
  { 0x00e00000, "SUB", alu_family },
  { 0x04600000, "AND", alu_family },
  { 0x04e00000, "ORR", alu_family },
  { 0x05600000, "EOR", alu_family },
  { 0x01600000, "ASL", alu_family },
  { 0x02600000, "LSR", alu_family },
  { 0x01e00000, "ASR", alu_family },
  { 0x03600000, "ROL", alu_family },
  { 0x02e00000, "ROR", alu_family },
  { 0x05e00000, "MUL", alu_family },
  { 0x03800000, "ADC", alu_family },
  { 0x03a00000, "SBC", alu_family },
  { 0x03e00000, "RLC", alu_family },
  { 0x03c00000, "RRC", alu_family },

  { 0x00600000, "ADDD", alu_family }, /*!< unused in disassembly */
  { 0x00400000, "ADDW", alu_family },
  { 0x00200000, "ADDH", alu_family },
  { 0x00000000, "ADDB", alu_family },

  { 0x00e00000, "SUBD", alu_family }, /*!< unused in disassembly */
  { 0x00c00000, "SUBW", alu_family },
  { 0x00a00000, "SUBH", alu_family },
  { 0x00800000, "SUBB", alu_family },

  { 0x01600000, "ASLD", alu_family }, /*!< unused in disassembly */
  { 0x01400000, "ASLW", alu_family },
  { 0x01200000, "ASLH", alu_family },
  { 0x01000000, "ASLB", alu_family },

  { 0x01e00000, "ASRD", alu_family }, /*!< unused in disassembly */
  { 0x01c00000, "ASRW", alu_family },
  { 0x01a00000, "ASRH", alu_family },
  { 0x01800000, "ASRB", alu_family },

  { 0x02600000, "LSRD", alu_family }, /*!< unused in disassembly */
  { 0x02400000, "LSRW", alu_family },
  { 0x02200000, "LSRH", alu_family },
  { 0x02000000, "LSRB", alu_family },

  { 0x03600000, "ROLD", alu_family }, /*!< unused in disassembly */
  { 0x03400000, "ROLW", alu_family },
  { 0x03200000, "ROLH", alu_family },
  { 0x03000000, "ROLB", alu_family },

  { 0x02e00000, "RORD", alu_family }, /*!< unused in disassembly */
  { 0x02c00000, "RORW", alu_family },
  { 0x02a00000, "RORH", alu_family },
  { 0x02800000, "RORB", alu_family },

  { 0x05c00000, "SUMW", alu_family },
  { 0x05a00000, "SUMH", alu_family },
  { 0x05800000, "SUMB", alu_family },

  { 0x06000000, "BAL", brc_family },
  { 0x56000000, "BEQ", brc_family },
  { 0x46000000, "BNE", brc_family },
  { 0xf6000000, "BMI", brc_family },
  { 0xe6000000, "BPL", brc_family },
  { 0xd6000000, "BVS", brc_family },
  { 0xc6000000, "BVC", brc_family },
  { 0x36000000, "BCS", brc_family },
  { 0x26000000, "BCC", brc_family },
  { 0xb6000000, "BHI", brc_family },
  { 0xa6000000, "BLQ", brc_family },
  { 0x76000000, "BGT", brc_family },
  { 0x66000000, "BLE", brc_family },
  { 0x96000000, "BGE", brc_family },
  { 0x86000000, "BLT", brc_family },
  { 0x36000000, "BHQ", brc_family }, /*!< unused in disassembly */
  { 0x26000000, "BLO", brc_family }, /*!< unused in disassembly */

  { 0x06200000, "BLK", brc_family },

  { 0x07400000, "TCR", sta_family },
  { 0x07600000, "TRC", sta_family },
  { 0x07800000, "TSR", sta_family },
  { 0x07a00000, "TRS", sta_family },
  { 0x07c00000, "RTI", sys_family },
  { 0x07e00000, "SYS", sys_family },

  { 0x04000000, "ILG", sys_family }, /*!< Official ILG instruction, but any invalid opcode is illegal */

  /* List of the suffixed mnemonics */
  { 0x0f000000 | SUFFIX_BIT, "LDWS", mem_family },
  { 0x0e800000 | SUFFIX_BIT, "LWSS", mem_family },
  { 0x0e000000 | SUFFIX_BIT, "LWUS", mem_family },
  { 0x0d800000 | SUFFIX_BIT, "LHSS", mem_family },
  { 0x0d000000 | SUFFIX_BIT, "LHUS", mem_family },
  { 0x0c800000 | SUFFIX_BIT, "LBSS", mem_family },
  { 0x0c000000 | SUFFIX_BIT, "LBUS", mem_family },
  { 0x0b000000 | SUFFIX_BIT, "STDS", mem_family },
  { 0x0a000000 | SUFFIX_BIT, "STWS", mem_family },
  { 0x09000000 | SUFFIX_BIT, "STHS", mem_family },
  { 0x08000000 | SUFFIX_BIT, "STBS", mem_family },
  { 0x0a800000 | SUFFIX_BIT, "STWS", mem_family },
  { 0x09800000 | SUFFIX_BIT, "STHS", mem_family },
  { 0x08800000 | SUFFIX_BIT, "STBS", mem_family },
  { 0x0f800000 | SUFFIX_BIT, "LLDS", mem_family },
  { 0x0b800000 | SUFFIX_BIT, "SCDS", mem_family },

  { 0x00600000 | SUFFIX_BIT, "ADDS", alu_family },
  { 0x00e00000 | SUFFIX_BIT, "SUBS", alu_family },
  { 0x04600000 | SUFFIX_BIT, "ANDS", alu_family },
  { 0x04e00000 | SUFFIX_BIT, "ORRS", alu_family },
  { 0x05600000 | SUFFIX_BIT, "EORS", alu_family },
  { 0x01600000 | SUFFIX_BIT, "ASLS", alu_family },
  { 0x02600000 | SUFFIX_BIT, "LSRS", alu_family },
  { 0x01e00000 | SUFFIX_BIT, "ASRS", alu_family },
  { 0x03600000 | SUFFIX_BIT, "ROLS", alu_family },
  { 0x02e00000 | SUFFIX_BIT, "RORS", alu_family },
  { 0x05e00000 | SUFFIX_BIT, "MULS", alu_family },
  { 0x03800000 | SUFFIX_BIT, "ADCS", alu_family },
  { 0x03a00000 | SUFFIX_BIT, "SBCS", alu_family },
  { 0x03e00000 | SUFFIX_BIT, "RLCS", alu_family },
  { 0x03c00000 | SUFFIX_BIT, "RRCS", alu_family },

  { 0x00600000 | SUFFIX_BIT, "ADDDS", alu_family }, /*!< unused in disassembly */
  { 0x00400000 | SUFFIX_BIT, "ADDWS", alu_family },
  { 0x00200000 | SUFFIX_BIT, "ADDHS", alu_family },
  { 0x00000000 | SUFFIX_BIT, "ADDBS", alu_family },

  { 0x00e00000 | SUFFIX_BIT, "SUBDS", alu_family }, /*!< unused in disassembly */
  { 0x00c00000 | SUFFIX_BIT, "SUBWS", alu_family },
  { 0x00a00000 | SUFFIX_BIT, "SUBHS", alu_family },
  { 0x00800000 | SUFFIX_BIT, "SUBBS", alu_family },

  { 0x01600000 | SUFFIX_BIT, "ASLDS", alu_family }, /*!< unused in disassembly */
  { 0x01400000 | SUFFIX_BIT, "ASLWS", alu_family },
  { 0x01200000 | SUFFIX_BIT, "ASLHS", alu_family },
  { 0x01000000 | SUFFIX_BIT, "ASLBS", alu_family },

  { 0x01e00000 | SUFFIX_BIT, "ASRDS", alu_family }, /*!< unused in disassembly */
  { 0x01c00000 | SUFFIX_BIT, "ASRWS", alu_family },
  { 0x01a00000 | SUFFIX_BIT, "ASRHS", alu_family },
  { 0x01800000 | SUFFIX_BIT, "ASRBS", alu_family },

  { 0x02600000 | SUFFIX_BIT, "LSRDS", alu_family }, /*!< unused in disassembly */
  { 0x02400000 | SUFFIX_BIT, "LSRWS", alu_family },
  { 0x02200000 | SUFFIX_BIT, "LSRHS", alu_family },
  { 0x02000000 | SUFFIX_BIT, "LSRBS", alu_family },

  { 0x03600000 | SUFFIX_BIT, "ROLDS", alu_family }, /*!< unused in disassembly */
  { 0x03400000 | SUFFIX_BIT, "ROLWS", alu_family },
  { 0x03200000 | SUFFIX_BIT, "ROLHS", alu_family },
  { 0x03000000 | SUFFIX_BIT, "ROLBS", alu_family },

  { 0x02e00000 | SUFFIX_BIT, "RORDS", alu_family }, /*!< unused in disassembly */
  { 0x02c00000 | SUFFIX_BIT, "RORWS", alu_family },
  { 0x02a00000 | SUFFIX_BIT, "RORHS", alu_family },
  { 0x02800000 | SUFFIX_BIT, "RORBS", alu_family },

  { 0x05c00000 | SUFFIX_BIT, "SUMWS", alu_family },
  { 0x05a00000 | SUFFIX_BIT, "SUMHS", alu_family },
  { 0x05800000 | SUFFIX_BIT, "SUMBS", alu_family },

  /* */
  { 0, "DD",     dd_directive },          /*!< Assembler directives: Data double-word */
  { 0, "DW",     dw_directive },          /*!< Assembler directives: Data word */
  { 0, "DH",     dh_directive },          /*!< Assembler directives: Data half-word */
  { 0, "DB",     db_directive },          /*!< Assembler directives: Data byte */
  { 0, "ASCII",  ascii_directive },       /*!< Assembler directives: ascii string */
  { 0, "ASCIZ",  asciz_directive },       /*!< Assembler directives: ascii string */
  { 0, "ALIGN",  align_directive },       /*!< Assembler directives: align */
  { 0, "AD",     ad_directive },          /*!< Assembler directives: align on double-word */
  { 0, "AW",     aw_directive },          /*!< Assembler directives: align on word */
  { 0, "AH",     ah_directive },          /*!< Assembler directives: align on half-word */
  { 0, "PC",     pc_directive },          /*!< Assembler directives: set the PC */
  { 0, "BIN",    bin_directive },         /*!< Assembler directives: insertion of binary file */
  { 0, "DEF",    def_directive },         /*!< Assembler directives: constant definition */
  { 0, "{",      open_scope_directive },  /*!< Assembler directives: open a scope for local labels */
  { 0, "}",      close_scope_directive }, /*!< Assembler directives: open a scope for local labels */
  { 0, "IMPORT", import_directive },      /*!< Assembler directives: open a scope for local labels */
  { 0, "EXPORT", export_directive },      /*!< Assembler directives: open a scope for local labels */
  { 0, "NPC",    npc_directive }          /*!< Assembler directives: attach the code to the next PC */
};

/**
 * \struct prefix
 * \brief The prefix translation table
 *
 * This table contains each prefix associated with its opcode. The point after
 * the prefix is implicit
 */
static const struct {
  uint32_t word;
  char prefix[4];
} prefix[] = {
  { 0x00000000, "AL" }, /*!< unused in disassembly */
  { 0x10000000, "BR" }, /*!< used for breakpoints but makes the instruction illegal */
  { 0x50000000, "EQ" },
  { 0x40000000, "NE" },
  { 0xf0000000, "MI" },
  { 0xe0000000, "PL" },
  { 0xd0000000, "VS" },
  { 0xc0000000, "VC" },
  { 0x30000000, "CS" },
  { 0x20000000, "CC" },
  { 0xb0000000, "HI" },
  { 0xa0000000, "LQ" },
  { 0x70000000, "GT" },
  { 0x60000000, "LE" },
  { 0x90000000, "GE" },
  { 0x80000000, "LT" },
  { 0x30000000, "HQ" }, /*!< unused in disassembly */
  { 0x20000000, "LO" }, /*!< unused in disassembly */

};

static const char * reg_name[] = {
  "R0",
  "R1",
  "R2",
  "R3",
  "R4",
  "R5",
  "R6",
  "R7",
  "R8",
  "R9",
  "R10",
  "R11",
  "R12",
  "R13",
  "R14",
  "PC",
  "R16",
  "R17",
  "R18",
  "R19",
  "R20",
  "R21",
  "R22",
  "R23",
  "R24",
  "R25",
  "R26",
  "R27",
  "R28",
  "R29",
  "SP",
  "LR"
};

enum {
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  PC,
  R16,
  R17,
  R18,
  R19,
  R20,
  R21,
  R22,
  R23,
  R24,
  R25,
  R26,
  R27,
  R28,
  R29,
  SP,
  LR
};

/*! All values below are masks */
#define CONDITION_MASK     0xf0000000 /* used to select conditionnal prefixes */
#define SUFFIX_BIT         0x00100000 /* used to select the suffix -S bit */
#define MEMORY_BIT         0x08000000 /* used to determine if the instruction is
                                         a load/store */ 
#define MEMORY_MASK        0x0f800000 /* used to select the bits that correspond
                                         to a memory instruction, without the 
                                         addressing mode */
#define ALU_MASK           0x0fe00000 /* used to select the bits that correspond
                                         to a register/ALU instruction */
#define DEST_MASK          0x0000001f /* used to select the destination register*/
#define REGX_MASK          0x000003e0 /* used to select the first register
                                         operand in case of a register operation.
                                         Select the base register in case of a
                                         load/store */
#define REGY_MASK          0x00007c00 /* used to select the second register
                                         operand in case of a register operation.
                                         Select the index register in case of a
                                         load/store */
#define ALU_MODE_MASK      0x00080000 /* used to select the addressing mode of an
                                         ALU operation (immediate or second
                                         register) */
#define ALU_IMM_MASK       0x0007fc00 /* determine the immediate value for an
                                         ALU operation */
#define ALU_SHIFT_MASK     0x00078000 /* determine the shift amount for an
                                         ALU operation */
#define MEMORY_MODE_MASK   0x00600000 /* used to select the addressing mode of a
                                         load/store (direct, indexed, base index
                                         shifted, auto-indexing mode) */
#define MEMORY_SHIFT_MASK  0x000f8000 /* used to know the shift amount in case
                                         of a load/store with the base index
                                         shifted addressing mode */
#define MEMORY_DIRECT_MASK 0x000fffe0 /* used to determine the address in case
                                         of a load/store with direct addressing
                                         mode */
#define MEMORY_AUTO_MASK   0x000c0000 /* used to know if the index is
                                         pre(post)inc(dec)remented */
#define MEMORY_I_OFF_MASK  0x000ffc00 /* used to select the offset if the
                                         addressing mode is the indexed mode */
#define BRANCH_MASK        0xffe00000 /* selects the bits for conditionnal
                                         branches */
#define BRANCH_OFF_MASK    0x0007ffe0 /* selects the offset bits of a branch
                                         instruction*/
/* Macro-instructions definition */
/* The macro-instruction below is used to determine if the instruction is a
 * conditionnal branch or not. This macro is useful because I don't want to see
 * cc.BAL instead of Bcc in our dissasembled code. For example I prefer to BEQ
 * and not EQ.BAL */
#define is_branch_instruction(a) !(((a) ^ 0x06000000) & ALU_MASK)
/* Selects the bits and shift them to know the condionnal prefix between 0 and
 * 15 */
#define extract_condition(a) ((a) & CONDITION_MASK)
/* Determine if the instruction is a load/store or not */
#define is_memory_instruction(a) ((a) & MEMORY_BIT)
/* Returns the destination register */
#define extract_rd(a) ((a) & DEST_MASK)
/* Returns Rx */
#define extract_rx(a) (((a) & REGX_MASK) >> 5)
/* Returns Ry */
#define extract_ry(a) (((a) & REGY_MASK) >> 10)
/* returns true if there is the suffix bit */
#define is_suffix(a) ((a) & SUFFIX_BIT)
/* returns true if the the addressing mode is immediate */
#define is_immediate(a) !((a) & ALU_MODE_MASK)
/* returns the immediate value */
#define extract_imm(a) (((a) & ALU_IMM_MASK) >> 10)

#endif // MNEMONIC_H
