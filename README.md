
---

# HexDump 🛠️

![C](https://img.shields.io/badge/Language-C-blue) ![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg) ![Platform](https://img.shields.io/badge/Platform-Cross--Platform-orange)

**HexDump** is a fast, portable, and interactive file hexdump tool written purely in **C**. View files in hexadecimal and ASCII with colorized output for non-printable bytes, customizable line width, grouping, offsets, and runtime interactive input. Supports very large files on 32-bit and 64-bit systems, and works across virtually any operating system.

---

## 🚀 Features

* **Single-file C executable** – Compile once, run anywhere, no dependencies.
* **Portable & OS-agnostic** – Carefully chosen data types make it work on virtually any system.
* **Colorized ASCII output** – Printable characters displayed normally; non-printable bytes shown as **red dots**.
* **Interactive Mode** – Enter file paths and options dynamically at runtime.
* **Customizable Display** – Control:

  * Line width (`-w`)
  * Grouping (`-g`)
  * Number of bytes (`-n`)
  * Offset (`-s`)
* **Large file support** – Handles full 32-bit file sizes (~3.9 GiB) and unlimited 64-bit files.

---

## ⚙️ Installation & Setup

1. **Clone the repository**:

```bash
git clone https://github.com/Gitter150/HexDump.git
cd HexDump
```

2. **Compile**:

```bash
gcc hexdump.c -o hexdump
```

3. **Add the compiled directory to your PATH** (so `hexdump` works from anywhere):

* **Linux / macOS**:

```bash
export PATH="$PATH:$(pwd)"
```

* **Windows (PowerShell)**

  **Temporary (current session only):**

```powershell
$env:PATH += ";$((Get-Location).Path)"
```

**Permanent (user PATH, new sessions):**

```powershell
[Environment]::SetEnvironmentVariable("PATH", $env:PATH + ";$((Get-Location).Path)", "User")
```

> After this, you can run `hexdump` from any directory without specifying the path. On Windows, the permanent method ensures new terminals recognize it automatically.

---

## 💻 Usage

### Command-line

```bash
hexdump <file_path> [OPTIONS]
```

### Options

| Option        | Description                                                                             | Default |
| ------------- | --------------------------------------------------------------------------------------- | ------- |
| `-n <number>` | Number of bytes to read. `-1` reads entire file.                                        | `-1`    |
| `-w <number>` | Bytes per line. `-1` = default (16).                                                    | 16      |
| `-g <number>` | Group size (bytes without spaces). Example: `2` → `FFFF`.                               | 4       |
| `-s <number>` | Offset to start reading. Positive = from start, negative = from end (`-1` = last byte). | 0       |
| `-S`          | Display file size.                                                                      | Off     |

---

### Interactive Mode

Run **without arguments**:

```bash
hexdump
```

You’ll be prompted for file path and options on the fly.

---

## 🔍 Example

File `hello.txt`:

```
hello
world
```

Command:

```powershell
./hexdump hello.txt -w 5 -g 1
```

Output:

```
00000000: 68 65 6C 6C 6F |hello|
00000005: 0D 0A 77 6F 72 |..wor|
0000000A: 6C 64 |ld|
```

---

## ⚠️ Notes

* 32-bit systems: Maximum readable size ~3.9 GiB; offsets may display incorrectly beyond this.
* 64-bit systems: Practically unlimited size.
* Non-printable ASCII bytes → **red dots**, printable dots → **white dots**.

---

## 👤 Author

**Gitter150** – Creator and maintainer.

---

## 📄 License

This project is licensed under the **MIT License** – see the [LICENSE](./LICENSE) file for details.
Feel free to use, modify, and distribute this tool under the terms of the MIT License.

---
