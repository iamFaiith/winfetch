# WinFetch

---

WinFetch is a small **Windows-only CLI tool** inspired by FastFetch. It shows basic system information directly in the terminal in a clean and simple way.

This tool is made **only for Windows** and focuses on being lightweight and easy to understand.

Please forgive me because **my code** is trash.

---

## ✨ Features

* Shows Windows OS information
* Displays system details like CPU, memory, gpu and drive 
* Simple and clean terminal output
* No extra dependencies
* Made completely using **C++ and Windows API**

---

## 🖥️ Supported Platforms

* ✅ Windows 10
* ✅ Windows 11

> ❌ Not supported on Linux or macOS

---

## 📦 Installation

### Using Winget (if available)

```bash
winget install winfetch
```

> If Winget support is not available yet, you can build it from source.

---

## 🛠️ Build From Source

### Requirements

* Windows OS
* C++ compiler (MSVC / MinGW / Clang)
* Git

### Steps

```bash
git clone https://github.com/iamfaiith/winfetch.git
cd winfetch
```

#### Build using Makefile (to make you smile)

Run to build:

```bash
make
```

After building, run:

```bash
winfetch
```

---

## 📂 Project Structure

```
winfetch/
│── src/ 
│── Makefile  
│── README.md
│── .gitignore
```

---

## 🎯 Why I Built This

I built WinFetch as a **learning project** to:

* Practice C++ on Windows
* Learn Windows system APIs
* Understand how CLI tools work
* Build something useful and fun
* It may face some bugs

This project is still improving, and I’m learning as I go 🚀

---

## 📜 License

This project is open-source and available under the **MIT License**.

---

## ❤️ Credits

Inspired by **FastFetch**

Crafted with ❤️ by a noob developer called faith.
