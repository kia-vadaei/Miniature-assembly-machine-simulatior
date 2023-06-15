<div dir='rtl' align="center">
             
</br>   
<img src="https://s28.picofile.com/file/8462130392/uni.png"  width="250"/>

<h2>🔷 UNIVERSITY OF ISFAHAN 🔷</h2>
<h3>LANGUAGES AND AUTOMATA THEORY COURSE</h3>
              <h3>AUTHOR:</h3>
          <h3>KIANOOSH VADAEI</h3>
</div>


</br>
<h1>Miniature</h1>

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
  <img src="https://s28.picofile.com/file/8462127968/sdaf.png"  width="500" height="324" />
  <img src="https://s29.picofile.com/file/8462127068/qwe.png"  width="300" height="324"/>
</div>
</br>
This project has 2 parts, both of which are equally important. The first part is design and implementation of assembler and the second part is testing and verification
Assembler written.
</br>

+ Designing and implementing an assembler in C language: for this machine, design and implement an assembler in C language that the name of the instructions of this
Convert microprocessors that are in assembly language to their binary equivalent. In addition, this assembler should include the tags that are used when writing the     program in the language
An assembly is used to convert them into their address equivalent.
The output of this assembler is a series of 32-bit instructions whose format is given below:

  label\<white>instruction\<white>field0,field1,field2\<white>\#comments
  
  Make sure that white is one or more spaces or tab. In the explanation, it should be mentioned that the first field is the label, which has a maximum of 6 characters
It is formed and although it must start with an English letter, it can also include numbers. Although the space after the label is necessary, but its existence
The logical label is optional. After the specified necessary interval, the instructions shown in table one appear. Finally, every instruction
It has its own fields and to display the registers, it is enough to specify only their number in the assembly command.
The number of fields in an instruction depends on its type, and the fields that are not used should be ignored. For example R type instructions
It has 3 fields, the first field is rd, the second field is rs and the third field is rt. Symbolic addresses refer to labels. For lw instructions
and sw, the assembler must calculate their label address and index the houses of an array with a non-zero base register.
collect If the base register is zero in lw and sw commands, the calculated label address is replaced in these commands. For instructions
beq, the assembler needs to convert the label to a numerical value offset (for which branching is necessary). It is worth noting that after the last field,
A space is placed and any description that appears optionally must be accompanied by a # sign. The description field ends with the end of each line.
In addition to miniature directives, an assembly program may also contain directives. The only directives of this machine are "fill" and
"space". The first places a number in the memory and the second stores the given number of memory cells, of course, their value is zero.
has been
In the example below, "start fill" places the value 2 in memory address 8. In addition, it should not be said that the StAddr label takes the value of 8.
The assembler you design needs to review the assembly code twice. In the (so-called) first scan, the assembler calculates the numerical equivalent of each label and each
It stores two labels and its numerical equivalent in a table called Table Symbol. In the second review, the assembler translates the assembly code into machine language and in
During translation, it uses the symbol table to replace the numerical equivalent of each label.
Below is an assembly program, the machine code of which is also given. Please read this program and its machine code equivalent carefully
Face fewer problems in designing and implementing assembler for Miniature.
<div dir='ltr' align="center">
  <img src="https://s29.picofile.com/file/8462127892/as.png"  width="500"/>
</div>
</br>

+ Running the assembler: Write the assembler in such a way that it receives two arguments in the command line (Line Command, as follows).
assemble program.as program.mc
As it is known, assemble is the executable file of the assembler, your assembly program is stored in as.program, and finally the assembler code
Translated into machine language and saved in mc.program. It is necessary to explain that exactly like the above example, each line of machine code in mc.program,
It is an integer (equivalent to decimal - instead of binary - assembly code). Any other output like the code meant for debugging that
It is written by you in assembler, it should be printed in standard output.

+ Errors detectable by the assembler: Your assembler must be able to detect the following errors:
5
A) Using an undefined label
b) Labels that are defined and used more than once
c) An offset that does not fit in 16 bits
d) opcode is not defined
If an error occurs, the assembler will stop the execution of the assembly operation with (1) exit, and if it does not detect any error, it will continue the assembly operation with (0) exit.
ends Pay attention that the assembler should not recognize errors during execution such as "branch to address 1" or "infinite loop".
to give

+ Verification: To verify the assembler you have written, it is necessary to prepare a set of assembly programs. This program collection, program
are almost short ones that are used as assembler input for testing purposes. Along with the assembly program, it is necessary to submit this collection as well
give Each test assembly program must be at least 10 lines long and 5 test samples are needed. Try to write any assembly program in such a way that
Test different parts of the assembler.
</div>
