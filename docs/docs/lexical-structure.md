---
layout: page
title: Lexical Structure
permalink: /docs/lexical-structure/
parent: Documentation
nav_order: 3
---

Lexical Structure
---

This table contains the types of tokens that are used in J:

| Token | Type | Description |
| ---- | ---- | ---- |
| += | operator | Plus Equals |
| -= | operator | Minus Equals |
| \*= | operator | Times Equals |
| /= | operator | Divide Equals |
| %= | operator | Modulo Equals |
| ^^= | operator | Logical XOR Equals |
| \|\|= | operator | Logical OR Equals |
| &&= | operator | Logical AND Equals |
| <<= | operator | Left Shift Equals |
| >>= | operator | Right Shift Equals |
| \|= | operator | Bitwise OR Equals |
| &= | operator | Bitwise AND Equals |
| ^= | operator | Bitwise XOR Equals |
| << | operator | Left Shift |
| >> | operator | Right Shift |
| == | operator | Equals |
| != | operator | Not Equals |
| && | operator | Logical AND |
| \|\| | operator | Logical OR |
| ^^ | operator | Logical XOR |
| <= | operator | Less Than or Equal |
| >= | operator | Greater Than or Equal |
| < | operator | Less Than |
| > | operator | Greater Than |
| = | operator | Assign |
| @ | operator | At |
| // | operator | Floor Divide |
| ++ | operator | Increment |
| -- | operator | Decrement |
| + | operator | Plus |
| - | operator | Minus |
| \* | operator | Times |
| / | operator | Divide |
| % | operator | Modulus |
| & | operator | Bitwise AND |
| \| | operator | Bitwise OR |
| ^ | operator | Bitwise XOR |
| ~ | operator | Bitwise NOT |
| ! | operator | Logical NOT |
| ? | operator | Ternary |
| subsystem | keyword | Create an annotated namespace |
| import | keyword | Import modules |
| export | keyword | Export items |
| let | keyword | Declare variable on the stack |
| var | keyword | Declare a variable on the heap |
| struct | keyword | Define or declare a structure |
| region | keyword | Define or declare a packed structure |
| union | keyword | Define or declare a union |
| packet | keyword | Define or declare a packed union |
| fn | keyword | Define or declare a function |
| typedef | keyword | Alias a type name |
| const | keyword | Declare a constant |
| static | keyword | Create a region of shared memory (like in C) |
| volatile | keyword | Define a block optimization-excempt code |
| enum | keyword | Define or declare an enum |
| class | keyword | Define or declare a class |
| bundle | keyword | Define or declare a packed class |
| public | keyword | Set visibility to public |
| private | keyword | Set visibility to private |
| protected | keyword | Set visibility to protected |
| override | keyword | Override an inherited method |
| virtual | keyword | Declare a virtual method |
| abstract | keyword | Define or declare an abstract class |
| friend | keyword | Mark class as a friend |
| interface | keyword | Define or declare an interface |
| delete | keyword | Delete construct |
| if | keyword | Create an if statement |
| else | keyword | Create an else statement |
| for | keyword | Create a for loop |
| while | keyword | Create a while loop |
| do | keyword | Create a do-while loop or create a functional block |
| switch | keyword | Create a switch statement |
| case | keyword | Crease a case in a switch statement |
| default | keyword | Default case |
| break | keyword | Break control flow |
| continue | keyword | Jump to next iteration |
| return | keyword | Return from function |
| retif | keyword | Return from function if an expression evaluates to true |
| abortif | keyword | Abort function if an expression evaluates to true |
| retz | keyword | Return if an expression evaluates to 0 |
| void | keyword | Absence of value (like in C) |
| null | type | Null Object |
| true | type | True |
| false | type | False |
| u8 | type | Unsigned 8-bit integer |
| u16 | type | Unsigned 16-bit integer |
| u32 | type | Unsigned 32-bit integer |
| u64 | type | Unsigned 64-bit integer |
| u128 | type | Unsigned 128-bit integer |
| u256 | type | Unsigned 256-bit integer |
| i8 | type | Signed 8-bit integer |
| i16 | type | Signed 16-bit integer |
| i32 | type | Signed 32-bit integer |
| i64 | type | Signed 64-bit integer |
| i128 | type | Signed 128-bit integer |
| i256 | type | Signed 256-bit integer |
| f32 | type | Signed 32-bit floating point |
| f64 | type | Signed 64-bit floating point |
| f128 | type | Signed 128-bit floating point |
| f256 | type | Signed 256-bit floating point |
| char | type | Can store any UTF-8 character |
| real | type | Arbitrary precision floating point |
| unsafe_ptr | type | Can store any non-executable memory address |
| unsafe_exec_ptr | type | Can store any memory address |
| buildconf | reserved | Reserved |
| cti | reserved | Reserved |
| j_* | reserved | Reserved |
| _Z* | reserved | Reserved |
| _ | keyword | Discard something |
| \[a-zA-Z_]\[a-zA-Z0-9_]* | identifier | Names for things |
| ( | punctuator | Opening parenthesis |
| ) | punctuator | Closing  parenthesis |
| \[ | punctuator | Opening bracket |
| ] | punctuator | Closed bracket |
| { | punctuator | Opening brace |
| } | punctuator | Closing brace |
| ; | punctuator | Semicolon |
| : | punctuator | Colon |
| . | punctuator | Period |
| , | punctuator | Comma |
