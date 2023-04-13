<div dir='ltr' align="justify">
  In this project, you are asked to write an assembler for a simple microprocessor called Miniature. The features of this microprocessor are as follows:
  A) This processor is a 32-bit machine (each word is 32 bits).
  B) Miniature has 16 registers, each of which has 32 bits (R15-R0) and R0 register always has zero value.
  c) Each addressing unit of this machine is one word and since each instruction is also one word, PC+1 to the next instruction in the series of program instructions.
  Refers.
  d) Miniature has 65536 words of memory
  e) This microprocessor has three types of instructions and 15 instructions, whose format is as follows:
  
<div dir='ltr' align="center">
  </br>
  <img src="https://s28.picofile.com/file/8462126950/Screenshot_2023_04_13_154733.png"  width="500"/>
</div>
  </br>
  Pay attention that the rs field of the lui instruction and the offset field of the jalr instruction are both zero.
  The details of the instructions of this microprocessor are given in Table 1 and the miniature memory scheme is shown in Figure 1.
  
  <div dir='ltr' align="center">
    </br>
    <img src="[https://s28.picofile.com/file/8462126950/Screenshot_2023_04_13_154733.png](https://s28.picofile.com/file/8462127042/Screenshot_2023_04_13_155250.png)"  width="500"/>
  </div>
</div>
