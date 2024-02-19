---
layout: page
title: Statements
permalink: /docs/statements/
parent: Documentation
nav_order: 6
---

Statements
---

J statements are classified into the following categories:
- [Declaration Statements](#declaration-statements)
- [Definition Statements](#definition-statements)
- [Control Flow Statements](#control-flow-statements)

### Declaration Statements
Declaration statements are used to forward declare types and functions.
There are ten types of declaration statements:
- [Typedef](#typedef)
- [Struct](#struct-declaration)
- [Union](#union-declaration)
- [Enum](#enum-declaration)
- [Function](#function-declaration)
    - [External Function](#external-function)
- [Class](#class-declaration)
- [Interface](#interface-declaration)
- [Abstract](#abstract-declaration)
- [Subsystem](#subsystem-declaration)
- [Variable](#variable-declaration)

#### Typedef
The `typedef` statement is used to create an alias for a type. For example:
```c
typedef i32 int32;
```

#### Struct Declaration
The `struct` forward declaration is used to forward declare a struct type. For example:
```c
struct StructA;

struct StructB {
    o: StructA;
};

struct StructA {
    a: i32;
    b: f32;
};
```

#### Union Declaration
The `union` forward declaration is used to forward declare a union type. For example:
```c
union UnionA;

union UnionB {
    o: UnionA;
};

union UnionA {
    a: i32;
    b: f32;
};
```
#### Enum Declaration
The `enum` forward declaration is used to forward declare an enum type. For example:
```c
enum EnumA;
```

#### Function Declaration
The function forward declaration is used to forward declare a function.
For example:
```c
fn add(a: i32, b: i32): i32;
```

##### External Function
The external function forward declaration is used to forward declare an external function.
For example:
```rs
import "C" {
    fn printf(format: *u8, ...);
}
```

#### Class Declaration
The `class` forward declaration is used to forward declare a class type. For example:
```cs
class ClassA;
```

#### Interface Declaration
The `interface` forward declaration is used to forward declare an interface type. For example:
```cs
interface InterfaceA;
```

#### Abstract Declaration
The `abstract` forward declaration is used to forward declare an abstract type. For example:
```cs
abstract AbstractA;
```

#### Subsystem Declaration
The `subsystem` forward declaration is used to forward declare a subsystem type. For example:
```cs
subsystem SubsystemA;
```

#### Variable Declaration
The variable declaration is used to declare a variable. For example:
```swift
var a: i32;
let b: f32 = 3.14;
```

### Definition Statements
Definition statements are used to define types and functions.
There are 10 types of definition statements:
- [Struct](#struct-definition)
- [Union](#union-definition)
- [Enum](#enum-definition)
- [Function](#function-definition)
    - [External Function](#external-function-definition)
- [Class](#class-definition)
- [Interface](#interface-definition)
- [Abstract](#abstract-definition)
- [Subsystem](#subsystem-definition)
- [Block](#block-definition)

#### Struct Definition
The `struct` definition is used to define a struct type. For example:
```c
struct StructA {
    a: i32;
    b: f32;
};
```

J structs are complex and have several notable features:
- [Struct Attributes](#struct-attributes)
- [Struct Methods](#struct-methods)
- [Struct Default Values](#struct-default-values)
- [Bitfields](#bitfields)

##### Struct Attributes
Struct attributes are used to set metadata on a struct. Certain attributes may alter the behavior and layout of a struct.
Attributes have the following syntax:
```
@attribute_name(constant_expression)
```

An example of a struct with attributes:
```ts
struct Uuid {
    @endian("big")
    @serial("%08x-")
    a: u32;
    @endian("big")
    @serial("%04x-")
    b: u16;
    @endian("big")
    @serial("%04x-")
    c: u16;
    @endian("big")
    @serial("%04x-")
    d: u16;
    @endian("big")
    @serial("%04x")
    e: u16;
    @endian("big")
    @serial("%08x")
    g: u32;
};
```

##### Struct Methods
Struct methods are used to define functions that operate on a struct instance. Struct methods have the following syntax:
```c
struct your_struct {
    your_method: (this, ...): return_type;
};
```

The `this` parameter is a reference to the struct instance. It does not need to be typed. All structure methods that don't have a `this` parameter are static methods.
The `this` parameter must be the first parameter if it is present.

##### Struct Default Values
Struct default values are used to set the default value of a struct field. 
Default values must be constant expressions.
For example:
```rs
struct StructA {
    a: i32 = 10;
    b: f32 = 3.14;
};
```

##### Bitfields
Bitfields are used to define a struct field with a specific bit width.
For example:
```rs
struct Bitfield {
    a: u8: 4;
    b: u8: 4;
};

region Bitfield2 {
    a: u8: 4 = 0b1010;
    b: u8: 4 = 0b0101;
};

struct BitfieldStruct {
    a: Bitfield;
    b: Bitfield2: 7; // first 7 bits of packed Bitfield2

    union u {
        c: f32;
        region p { // these offsets might be wrong, but the syntax is correct
            sign: u32: 1;
            mantissa: u32: 23;
            exponent: u32: 8;
        };
    };
};
```

#### Union Definition
