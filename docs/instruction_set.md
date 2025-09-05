DictEntry instruction_set_dict[] = {
    {.key = "NULL", .value = 0x00}, {.key = "ADD", .value = 0x01},
    {.key = "SUB", .value = 0x02},  {.key = "OR", .value = 0x03},
    {.key = "NOT", .value = 0x04},  {.key = "AND", .value = 0x05},
    {.key = "MUL", .value = 0x06},  {.key = "DIV", .value = 0x07},
    {.key = "JE", .value = 0x08},   {.key = "JG", .value = 0x09},
    {.key = "JL", .value = 0x0A},   {.key = "JMP", .value = 0x0B},
    {.key = "HLT", .value = 0x0F},  {.key = NULL, .value = -1}};

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
      <td><code>0x00</code></td>
      <td>no operation</td>
    </tr>
    <tr>
      <td><strong>ADD</strong></td>
      <td><code>0x01</code></td>
      <td>adds 2 numbers</td>
    </tr>
    <tr>
      <td><strong>SUB</strong></td>
      <td><code>0x02</code></td>
      <td>substracts two numbers</td>
    </tr>
    <tr>
      <td><strong>OR</strong></td>
      <td><code>0x03</code></td>
      <td>Bitwise OR</td>
    </tr>
    <tr>
      <td><strong>NOT</strong></td>
      <td><code>0x04</code></td>
      <td>Bitwise negation uses only R2 as input</td>
    </tr>
    <tr>
      <td><strong>AND</strong></td>
      <td><code>0x05</code></td>
      <td>Bitwise AND</td>
    </tr>
    <tr>
      <td><strong>MUL</strong></td>
      <td><code>0x06</code></td>
      <td>multiplying</td>
    </tr>
    <tr>
      <td><strong>DIV</strong></td>
      <td><code>0x07</code></td>
      <td>Divides</td>
    </tr>
    <tr>
      <td><strong>JE</strong></td>
      <td><code>0x08</code></td>
      <td>jumps if R2 and R3 are equal</td>
    </tr>
    <tr>
      <td><strong>JG</strong></td>
      <td><code>0x09</code></td>
      <td>Jumps if R2 is greater than r3 is line to jump</td>
    </tr>
    <tr>
      <td><strong>JL</strong></td>
      <td><code>0x0A</code></td>
      <td>jumps if R2 is less than R3, R1 is line to jump</td>
    </tr>
    <tr>
      <td><strong>JMP</strong></td>
      <td><code>0x0B</code></td>
      <td>jumps to R1</td>
    </tr>
    <tr>
      <td><strong>HLT</strong></td>
      <td><code>0x0F</code></td>
      <td>shuts down the program</td>
    </tr>
  </tbody>
</table>
