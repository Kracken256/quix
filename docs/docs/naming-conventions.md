---
layout: page
title: Naming Conventions
permalink: /docs/naming-conventions/
parent: Documentation
nav_order: 2
---

Naming conventions
---

The following naming conventions are used in J:
- User defined type names should be in PascalCase.
- Function names should be in snake_case.
- Variable names should be in camelCase.
- Constants should be in SCREAMING_SNAKE_CASE.
- Enum values should be in PascalCase.
- Source file names should be in snake_case.
- Source directory names should be in snake_case.

**Note:** These conventions are not mandatory, but are used by the J project.

The following table provides examples of each naming convention:

```c++
    // User defined type names
    struct PascalCase {};
    struct VPNConnection {};
    struct UserAccount {};
    struct EFI {};
    struct HTTPRequest {};
    struct ALongStructName {};
```

```swift
    // Function names
    func snake_case() {}
    func get_user() {}
    func get_user_account() {}
    func get_http_request() {}
    func initital_efi_system_table(handle: &ImageHandle, table: &SystemTable) {}
```

```swift
    // Variable names
    func snake_case() {
        var camelCase: int;
        var userAccount: UserAccount;
        var httpRequest: HTTPRequest;
        var efi: EFI;
        let aLongVariableName: dword;
    }
```

```ts
    // Constants
    const SCREAMING_SNAKE_CASE: int = 0;
    const MAX_CONNECTIONS: int = 10;
    const MAX_USERS: int = 100;
    const MAX_REQUESTS: int = 1000;
    const MAX_EFI_TABLES: int = 10000;
```

```swift
    // Enum values
    enum PascalCase {
        FirstValue = 0;
        SecondValue;
        ThirdValue;
        FourthValue;
    };
```

```
- project
    - src
        - smb_server
            - smb_server.q
            - smb_server.qh
        - app
            - app.q
            - app.qh
    - README.md

```