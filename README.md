# virtual-memory-manager
Implemented a simulator for a virtual memory management scheme on a multicore system

## **Overview**  
This project implements a **Virtual Memory Manager (VMM)** that simulates **page fetching, page replacement, and fault handling** in a multiprogramming system. The simulation models how modern operating systems manage memory using paging, handling multiple processes with virtual memory, and efficiently managing page faults.  

## **Features**  
- Simulates **demand paging** with page fetching on access.  
- Implements **page replacement algorithms** (e.g., FIFO, LRU, OPT).  
- Tracks **page faults** and memory accesses.  
- Supports multiple processes, each with its own virtual address space.  
- Configurable **frame allocation policies**.  
- Command-line interface for running simulations with different configurations.  

## **How It Works**  
1. Each process generates memory access requests.  
2. The VMM checks if the requested page is in memory.  
   - If **present**, it updates relevant data structures.  
   - If **absent (page fault)**, the page is fetched into memory.  
3. If memory is **full**, the VMM applies a **page replacement algorithm** to evict a page.  
4. The system logs **page faults, memory accesses, and evictions** for analysis.  

## **Installation & Usage**  
### **Prerequisites**  
- C++ (compiled with `g++`)  
- Linux/macOS (for performance evaluation)  

### **Build Instructions**  
```sh
g++ -o vmm vmm.cpp -std=c++17
```

### **Run the Simulation**  
```sh
./vmm input_file.txt
```
- `input_file.txt` should contain a list of memory access requests and process IDs.  

## **Future Enhancements**  
- Implement **working set model** for adaptive replacement.  
- Add **TLB caching** to reduce access latency.  
- Support **additional page replacement algorithms**.  

## **License**  
This project is released under **The Unlicense**, allowing unrestricted use.  
```

This keeps the structure clean while reflecting your requested changes. Let me know if you need further refinements!
