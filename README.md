# 🖥️ CLI Project

[![C Badge](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.kernel.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)](#) 

---

## 📌 Project Links
- **Jira Board:** [CLI Project](https://swinga.atlassian.net/jira/software/projects/CLI/boards/35)  
- **Commands Documentation:** [Linux Man Pages](https://man7.org/linux/man-pages/index.html)  
- **ANSI Escape Codes:** [Build Your Own CLI](https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html?utm_source=chatgpt.com#colors)

---

## ⚡ Features
- Fully functional CLI built in **C**
- Supports commands: `mkdir`, `rmdir`, `touch`, `cd`, `ls`, `rm`, `clear`, `exit`, `help`
- Colorized output using **ANSI escape codes**
- Cross-platform support (Linux recommended)
- Modular design: commands are easy to add/modify

---

## 🛠️ Usage
```bash
# Clone the repo
git clone <your-repo-url>
cd <repo-directory>

# Build (using gcc or make)
make
# or
gcc main.c -o cli

# Run
./cli
