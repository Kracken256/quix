---
layout: page
title: Structs
permalink: /docs/structs/
parent: Documentation
nav_order: 7
---

Structs
---

J sturctures are user-defined composite types that are used to group related data together into an ordered set. A struct can contain fields of any type, including other structs (except for itself). The fields of a struct are accessed using the dot operator (`.`). Structures are a core building block of J and are used to define complex data types such as linked lists, trees, and graphs.

Structures may be packed or unpacked. A packed structure is a structure that has no padding between its fields. An unpacked structure is a structure that may have padding between its fields. The size of a packed structure is the sum of the sizes of its fields. The size of an unpacked structure is the sum of the sizes of its fields plus any padding.

Structures are declared using the `struct` keyword. For example:

```c
struct ASTNode {
    kind: ASTNodeKind;
    value: i32;
    next: &ASTNode?;
};
```

For convenience, J has a special keyword for creating packed structures called `region`. The `region` keyword is used to create a packed structure. For example:

```c
region UdpHeader {
    sourcePort: u16;
    destinationPort: u16;
    length: u16;
    checksum: u16;
};
```

The `region` keyword is used to create a packed structure. The `region` keyword is followed by the name of the structure and a block of fields. Each field is declared using the field name followed by a colon and the field type. The fields are separated by semicolons. Default values may be assigned to fields using the `=` operator. For example:

```c
region UdpHeader {
    sourcePort: u16 = 0x1234;
    destinationPort: u16;
    length: u16;
    checksum: u16;
};
```

If a default value is not assigned to a field, the following rules apply:
- If the field is a primitive type, the default value is zero.
- If the field is a composite type, the default value is the default value of the composite type.

J does not allow constructors or destructors for structures. However, J does allow structure methods. Structure methods are used to define functions that operate on a structure instance. Structure methods have the following syntax:

```c
region UdpHeader {
    sourcePort: u16;
    destinationPort: u16;
    length: u16;
    checksum: u16;

    new: (sourcePort: u16, destinationPort: u16): UdpHeader;
};
```

The `this` parameter is a reference to the structure instance. It does not need to be typed. All structure methods that don't have a `this` parameter are static methods. The `this` parameter must be the first parameter if it is present. If the `this` parameter is a reference `&this` then the method may modify the structure instance. If the `this` parameter is a constant `this` then the method may not modify the structure instance.


```rs
impl UdpHeader {
    new: (sourcePort: u16, destinationPort: u16): UdpHeader {
        return UdpHeader {
            sourcePort: sourcePort,
            destinationPort: destinationPort,
        };
    }
};
```

Some method names have special meaning. For example, the `add` method is used to define the addition operator for a structure. The `add` method has the following syntax:

```c
struct String {
    str: &i8[];

    add: (this, other: &String): String;
};

fn main() {
    let a: String = "Hello";
    let b: String = " World";
    let c: String = a + b;
}
```
