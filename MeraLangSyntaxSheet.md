Sure! Here's an **official syntax sheet for MeraLang (`.mera` files)** covering all core language elements, keywords, operators, literals, macros, and directives, formatted cleanly for reference and easy extension.

---

# MeraLang Syntax Sheet (`.mera`)

---

## 1. **File Extension**

```
.mera
```

---

## 2. **Basic Structure**

```mera
capsule CapsuleName {
    // Code here
    func functionName(params...) -> ReturnType {
        // Statements
    }

    var variableName: Type = initialValue

    // Entry point
    func main() {
        // Execution starts here
    }
}
```

---

## 3. **Keywords**

| Keyword          | Description                      |
| ---------------- | -------------------------------- |
| `capsule`        | Define a module or namespace     |
| `func`           | Define a function                |
| `var`            | Define a variable                |
| `const`          | Define a constant                |
| `import`         | Import another capsule/module    |
| `return`         | Return from function             |
| `if` / `else`    | Conditional branching            |
| `while`          | Looping                          |
| `for`            | Looping with index               |
| `break`          | Exit loop                        |
| `continue`       | Continue to next loop iteration  |
| `macro`          | Define a macro                   |
| `endmacro`       | End macro definition             |
| `when`           | Conditional block (event-driven) |
| `true` / `false` | Boolean literals                 |

---

## 4. **Comments**

* Single-line: `// This is a comment`
* Multi-line:

  ```mera
  /* 
     This is a
     multi-line comment
  */
  ```

---

## 5. **Identifiers**

* Start with letter or underscore, followed by letters, digits, or underscores
* Case-sensitive
* Examples: `myVar`, `_temp`, `CalculateSum`

---

## 6. **Data Types**

| Type     | Description           |
| -------- | --------------------- |
| `int`    | 32-bit signed integer |
| `int64`  | 64-bit signed integer |
| `float`  | 32-bit floating point |
| `double` | 64-bit floating point |
| `bool`   | Boolean               |
| `string` | Unicode text string   |
| `bytes`  | Byte array            |
| `void`   | No return type        |

---

## 7. **Literals**

| Literal        | Example           | Notes              |
| -------------- | ----------------- | ------------------ |
| Integer        | `123`, `0x7B`     | Decimal or hex     |
| Floating-point | `3.14`, `2.0e-3`  | Standard notation  |
| Boolean        | `true`, `false`   |                    |
| String         | `"Hello, world!"` | Double quotes only |
| Bytes          | `b"\x01\x02\x03"` | Byte literal       |

---

## 8. **Operators**

| Operator | Description            | Example  |            |     |   |     |
| -------- | ---------------------- | -------- | ---------- | --- | - | --- |
| `+`      | Addition               | `a + b`  |            |     |   |     |
| `-`      | Subtraction            | `a - b`  |            |     |   |     |
| `*`      | Multiplication         | `a * b`  |            |     |   |     |
| `/`      | Division               | `a / b`  |            |     |   |     |
| `%`      | Modulo                 | `a % b`  |            |     |   |     |
| `==`     | Equality               | `a == b` |            |     |   |     |
| `!=`     | Inequality             | `a != b` |            |     |   |     |
| `<`      | Less than              | `a < b`  |            |     |   |     |
| `<=`     | Less or equal          | `a <= b` |            |     |   |     |
| `>`      | Greater than           | `a > b`  |            |     |   |     |
| `>=`     | Greater or equal       | `a >= b` |            |     |   |     |
| `&&`     | Logical AND            | `a && b` |            |     |   |     |
| \`       |                        | \`       | Logical OR | \`a |   | b\` |
| `!`      | Logical NOT            | `!a`     |            |     |   |     |
| `=`      | Assignment             | `a = 5`  |            |     |   |     |
| `+=`     | Addition assignment    | `a += 2` |            |     |   |     |
| `-=`     | Subtraction assignment | `a -= 1` |            |     |   |     |

---

## 9. **Function Declaration**

```mera
func functionName(param1: int, param2: string) -> int {
    // function body
    return 0
}
```

---

## 10. **Control Flow**

```mera
if condition {
    // do something
} else if other_condition {
    // do something else
} else {
    // default case
}

while condition {
    // loop body
}

for i from 0 to 10 {
    // loop with index i
}

switch value {
    case 1: doSomething()
    case 2: doSomethingElse()
    default: doDefault()
}
```

---

## 11. **Macros**

```mera
macro MacroName(param1, param2) {
    // macro body
    say("Param1 is {param1}, Param2 is {param2}")
}
endmacro

// Usage
MacroName("Hello", "World")
```

* Supports recursion, conditionals (`if`, `else`) inside macro bodies
* Parameters can be substituted text or expressions

---

## 12. **Capsules and Imports**

```mera
capsule CapsuleA {
    func greet() {
        say("Hello from CapsuleA")
    }
}

capsule CapsuleB {
    import CapsuleA

    func main() {
        CapsuleA.greet()
    }
}
```

---

## 13. **File I/O**

```mera
var content: string = file_read_text("file.txt")
file_write_text("out.txt", content)
file_write_binary("bin.dat", b"\xDE\xAD\xBE\xEF")
```

---

## 14. **Example `.mera` File**

```mera
capsule Example {
    func main() {
        var x: int = 10
        if x > 5 {
            say("x is greater than 5")
        } else {
            say("x is 5 or less")
        }

        macro HelloMacro(name) {
            say("Hello, {name}!")
        }
        endmacro

        HelloMacro("MeraLang")
    }
}
```

---

### Summary

| Feature            | Syntax Example                    | Notes                        |
| ------------------ | --------------------------------- | ---------------------------- |
| Variable           | `var x: int = 5`                  | Typed variable declaration   |
| Function           | `func foo() -> void { ... }`      | Typed functions              |
| Capsule            | `capsule Name { ... }`            | Modules or namespaces        |
| Macro              | `macro M(param) { ... } endmacro` | Compile-time code generation |
| Control Structures | `if`, `while`, `for`, `switch`    | Standard control flow        |
| Comments           | `// comment` or `/* comment */`   | Single & multi-line          |
| Import             | `import OtherCapsule`             | Access external modules      |

---

