
---

# HexDump 🛠️

![C](https://img.shields.io/badge/Language-C-blue) ![License](https://img.shields.io/badge/License-Free-brightgreen) ![Platform](https://img.shields.io/badge/Platform-Cross--Platform-orange)

**HexDump** is a fast, portable, and interactive file hexdump tool written purely in **C**. View files in hexadecimal and ASCII with colorized output, runtime interaction, and flexible formatting.

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
git clone <repo_url>
cd <repo_name>
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

* **Windows (PowerShell)**:

```powershell
$env:PATH += ";$((Get-Location).Path)"
```

> After this, you can run `hexdump` from any directory without specifying the path.
> Note: On Windows, this change lasts only for the current PowerShell session. For a permanent change, update your user or system PATH via Environment Variables.

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
| `-g <number>` | Group size (bytes without spaces). -1 = default (4) Example: `2` → `FFFF`.                               | 4       |
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

Free to use and modify.

---
