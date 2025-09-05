# Instruction set:
All instruction use as input ADR2 and ADR3 and as an output ADR1 if not stated diffrently

<table>
  <thead>
    <tr>
      <th>Instruction</th>
      <th>Hex code</th>
      <th>use</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>NULL</strong></td>
      <td><code>0x0000</code></td>
      <td>no operation</td>
    </tr>
    <tr>
      <td><strong>ADD</strong></td>
      <td><code>0x0001</code></td>
      <td>adds 2 numbers</td>
    </tr>
    <tr>
      <td><strong>SUB</strong></td>
      <td><code>0x0002</code></td>
      <td>substracts two numbers</td>
    </tr>
    <tr>
      <td><strong>OR</strong></td>
      <td><code>0x0003</code></td>
      <td>Bitwise OR</td>
    </tr>
    <tr>
      <td><strong>NOT</strong></td>
      <td><code>0x0004</code></td>
      <td>Bitwise negation uses only R2 as input</td>
    </tr>
    <tr>
      <td><strong>AND</strong></td>
      <td><code>0x0005</code></td>
      <td>Bitwise AND</td>
    </tr>
    <tr>
      <td><strong>MUL</strong></td>
      <td><code>0x06</code></td>
      <td>multiplying</td>
    </tr>
    <tr>
      <td><strong>DIV</strong></td>
      <td><code>0x0007</code></td>
      <td>Divides</td>
    </tr>
    <tr>
      <td><strong>JE</strong></td>
      <td><code>0x0008</code></td>
      <td>jumps if R2 and R3 are equal</td>
    </tr>
    <tr>
      <td><strong>JG</strong></td>
      <td><code>0x0009</code></td>
      <td>Jumps if R2 is greater than r3 is line to jump</td>
    </tr>
    <tr>
      <td><strong>JL</strong></td>
      <td><code>0x0A</code></td>
      <td>jumps if R2 is less than R3, R1 is line to jump</td>
    </tr>
    <tr>
      <td><strong>JMP</strong></td>
      <td><code>0x000B</code></td>
      <td>jumps to R1</td>
    </tr>
    <tr>
      <td><strong>HLT</strong></td>
      <td><code>0x000F</code></td>
      <td>shuts down the program</td>
    </tr>
  </tbody>
</table>

Registers:
TODO: R0

4 registers
r0 - null register - 0x0000
r1 - 0x0001
r2 - 0x0002
r3 - 0x0003
r4 - 0x0004
<table>
   <thead>
      <tr>
         <th>Register</th>
         <th>hexcode</th>
         <th>special</th>
      </tr>
  </thead>
   <tbody>
      <tr>
         <td><strong>R0</strong></td>
         <td><code>UNDEFINED</code></td>
         <td>null register - outputs into void, not readable, TODO</td>
      </tr>
      <tr>
         <td><strong>R1</strong></td>
         <td><code>0006</code></td>
         <td></td>
      </tr>
      <tr>
         <td><strong>R2</strong></td>
         <td><code>000A</code></td>
         <td></td>
      </tr>
      <tr>
         <td><strong>R3</strong></td>
         <td><code>000E</code></td>
         <td></td>
      </tr>
      <tr>
         <td><strong>R4</strong></td>
         <td><code>0012</code></td>
         <td></td>
      </tr>
      
   </tbody>
</table>

## other:
in addresing Mode you can use 3 types of giving a value:

<table>
   <thead>
      <tr>
         <th>type</th>
         <th>example</th>
         <th>special</th>
      </tr>
  </thead>
   <tbody>
      <tr>
         <td><strong>Register</strong></td>
         <td><code>R3</code></td>
         <td>16 bit memory</td>
      </tr>
            <tr>
         <td><strong>Imm</strong></td>
         <td><code>15</code></td>
         <td>defined constant number</td>
      </tr>
            <tr>
         <td><strong>Memory Address</strong></td>
         <td><code>[0x015]</code></td>
         <td>read/write from addresable memory</td>
      </tr>
   </tbody>
</table>
