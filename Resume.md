# Resume - Minishell Project

## Project Overview
**Minishell** - A complete shell implementation in C  
**Duration:** 2025  
**Role:** Co-developer  
**Collaboration:** Team project with [ayameur](https://profile.intra.42.fr/users/ayameur)

---

## 🚀 Project Description

Developed a fully functional command-line interpreter that replicates core bash functionality, demonstrating advanced systems programming skills and deep understanding of Unix/Linux internals. This project showcases expertise in process management, memory management, and low-level system programming.

---

## 🛠️ Technical Skills Demonstrated

### **Systems Programming**
- **Process Management**: Implemented fork/exec pattern for command execution
- **Signal Handling**: Developed robust signal management (SIGINT, SIGQUIT)
- **File Descriptors**: Advanced file descriptor manipulation and redirection
- **Memory Management**: Custom memory allocator with leak detection and sanitization

### **C Programming**
- **Data Structures**: Designed complex linked lists and tree structures
- **Pointer Management**: Advanced pointer arithmetic and memory manipulation
- **Error Handling**: Comprehensive error checking and recovery mechanisms
- **Code Organization**: Modular architecture with clean separation of concerns

### **Shell Features Implemented**
- **Command Parsing**: Lexical analysis and tokenization engine
- **Variable Expansion**: Environment variable substitution and expansion
- **Redirections**: Input/output redirection (`<`, `>`, `>>`)
- **Pipes**: Multi-process pipeline implementation
- **Here Documents**: Heredoc functionality for multi-line input
- **Built-in Commands**: echo, cd, pwd, export, unset, env, exit

---

## 🏗️ Architecture & Design

### **Core Components**
- **Lexer**: Tokenizes input into semantic units
- **Parser**: Builds command structures from tokens
- **Expander**: Handles variable expansion and quote processing
- **Executor**: Manages process creation and execution
- **Built-ins**: Native command implementations

### **Data Structures**
- **t_shell**: Main shell state management
- **t_token**: Token representation with type classification
- **t_cmd**: Command structure with redirection support
- **t_env**: Environment variable management

---

## 🎯 Key Achievements

### **Performance & Reliability**
- ✅ Zero memory leaks (verified with AddressSanitizer)
- ✅ Proper signal handling preventing shell crashes
- ✅ Robust error handling with appropriate exit codes
- ✅ Full compliance with 42 coding standards

### **Advanced Features**
- ✅ Complex pipe chains with multiple processes
- ✅ Nested quote handling (single and double quotes)
- ✅ Environment variable expansion with `${VAR}` syntax
- ✅ Heredoc implementation with delimiter processing
- ✅ Custom memory management system

### **Code Quality**
- ✅ Modular, maintainable codebase (2000+ lines)
- ✅ Comprehensive error checking
- ✅ Clean separation of concerns
- ✅ Extensive use of function pointers and callbacks

---

## 🔧 Technical Implementation Details

### **Memory Management**
```c
// Custom memory allocator with leak detection
void *ft_malloc(size_t size, t_call call);
// Address sanitizer integration
CFLAGS = -fsanitize=address
```

### **Process Management**
```c
// Fork/exec pattern for command execution
pid_t pid = fork();
if (pid == 0)
    execve(cmd_path, cmd_args, env_array);
```

### **Signal Handling**
```c
// Proper signal management
void handle_sigint(int sig);
void setup_signals(void);
```

---

## 📊 Project Metrics

- **Lines of Code**: 2000+ lines
- **Files**: 45+ source files
- **Functions**: 100+ custom functions
- **Data Structures**: 4 major structures
- **Built-in Commands**: 7 implemented
- **Redirection Types**: 4 supported
- **Memory Management**: Custom allocator with leak detection

---

## 🎓 Learning Outcomes

### **Systems Programming**
- Deep understanding of Unix process model
- Mastery of file descriptor manipulation
- Signal handling and process communication
- Memory management and debugging techniques

### **Software Engineering**
- Large-scale C project organization
- Team collaboration and version control
- Code review and quality assurance
- Documentation and testing practices

### **Problem Solving**
- Complex parsing and tokenization challenges
- Memory leak detection and prevention
- Race condition handling in multi-process applications
- Error recovery and graceful failure handling

---

## 🏆 Skills Validation

This project demonstrates proficiency in:
- **C Programming** (Advanced)
- **Systems Programming** (Advanced)
- **Unix/Linux Internals** (Intermediate-Advanced)
- **Memory Management** (Advanced)
- **Process Management** (Advanced)
- **Shell Scripting Concepts** (Advanced)
- **Debugging & Profiling** (Intermediate-Advanced)

---

## 🔗 Project Links

- **GitHub Repository**: [Minishell Project](https://github.com/boughatat911/minishell)
- **42 Intra Profile**: [nbougrin](https://profile.intra.42.fr/users/nbougrin)
- **Collaborator**: [ayameur](https://profile.intra.42.fr/users/ayameur)

---

## 💼 Professional Impact

This project showcases the ability to:
- Work on complex, multi-component systems
- Implement low-level system functionality
- Debug and optimize performance-critical code
- Collaborate effectively on technical projects
- Write production-quality C code
- Understand and implement Unix system concepts

---

*This project represents a significant milestone in systems programming education, demonstrating both technical depth and practical implementation skills in C and Unix system programming.*
