
# **Parallelization of Job Scheduling Problem Optimization Using OpenMP**

## **Project Description**
This project was implemented as part of the ARTI 503 - Parallel Computer Architecture and Programming course at Imam Abdulrahman Bin Faisal University, where job scheduling algorithm implemented using OpenMP to optimize execution time and resource utilization. The program uses a greedy algorithm combined with recursive strategies to allocate job slots based on deadlines and profits. 
The combination of three methods (Critical, Atomic, and Reduction) was used to address race conditions in a job scheduling algorithm, leveraging OpenMP for parallelization. Therefore, achieves improved performance over traditional sequential methods, making it suitable for large-scale scheduling problems.

---

## **Team and Instructor**
**Team Members**:
  - [Sarah Alshaikhmohammed](https://www.linkedin.com/in/sarah-alshaikhmohammed-ab20a9252?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=ios_app)
  - [Alanoud Aldweesh]()
  - [Renad Alharbi](http://linkedin.com/in/iam-renad-alharbi)
  - [Maha Baaqil]()
  - [Fatimah Alkubaisi](https://sa.linkedin.com/in/fatimah-alkubaysi-8684612ab)
  - [Hind Aldossary]()

**Instructor**:  
  - Dr. Rabab Alkhalifa

---

## **Key Results**
### **Individual Parallelization Methods Results**
Individual parallelization methods (Critical, Atomic, and Reduction) were implemented and analyzed for performance and accuracy. Each method handled race conditions differently, and the results demonstrated their effectiveness in reducing execution time while maintaining accuracy. The performance of each method is summarized below:
1. **Execution Time Comparison of Parallelization Methods**:
   | Method    | Execution Time | Percent Error |
   |-----------|----------------|---------------|
   | Critical  | 0.131s         | 0.2%          |
   | Atomic    | 0.125s         | 0.15%         |
   | Reduction | 0.123s         | 0.12%         |
2.  **Execution Time of Different Cores**
![Execution Time of Different Cores](./Execution_Time.png)
3.  **Results of Different Cores**
![Results of Different Cores](./Results.png)  

The **Reduction Method** showed the best performance in terms of both execution time and accuracy, making it the most efficient individual method.

### **Combined Version Results**
The combined version integrates all three methods (Critical, Atomic, and Reduction) into a unified implementation to optimize the performance further. This approach balances the strengths of each method to deliver improved results. Below are the findings:
1. **Performance Comparison**:
   | Code                | Execution Time | Result               |
   |---------------------|----------------|----------------------|
   | Sequential          | 0.128s         | 13253.4              |
   | Parallel (Combined) | 0.126s         | 13271.6              |
   | Impact              | 1.56% improved | 0.137% percent error |
 
2. **Impact of Core Count on Performance**
![Impact of Core Count on Performance](./Combined.png)

The Combined Version optimized performance by integrating multiple methods and cores, where resulted the **best performance at 4 cores**.

---

## **Prerequisites**
To run this project, ensure you have the following:
1. GCC Compiler with OpenMP support.
2. Compatible OS (Windows/Linux/macOS).
3. Terminal or Command-Line Interface for compilation and execution.

---

## **Installation**
### **Windows Installation (Using MSYS2)**
1. Download and install [MSYS2](https://www.msys2.org/).
2. Open the MSYS2 terminal and install GCC:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```
3. Verify GCC installation:
```bash
gcc --version
```
4. Check OpenMP support:
```bash
g++ -fopenmp --version
```

### **Linux Installation**
1. Update your package list:
```bash
sudo apt update
```
2. Install GCC with OpenMP support:
```bash
sudo apt install gcc g++
```
3. Verify installation:
```bash
g++ -fopenmp --version
```

### **macOS Installation**
1. Install Homebrew (if not already installed):
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
2. Install GCC with OpenMP support:
```bash
brew install gcc
```
3. Verify installation:
```bash
g++<version> -fopenmp --version
```
*Note: (Replace <version> with the installed GCC version, e.g., g++-11)*
---

## **Run the Code**
### **Step 1: Clone the Repository**
Clone the repository from GitHub to your local machine:
```bash
git clone https://github.com/SarahAlshaikhmohammed/Job_Scheduling_Problem_Parallelization.git
cd job-scheduling
```

### **Step 2: Compile the Code**
Use the `g++` compiler to compile the program with OpenMP:
```bash
g++ -fopenmp -o job_scheduler file_name.cpp
```

### **Step 3: Run the Program**
Run the compiled program:
```bash
./job_scheduler
```

### **Step 4: Analyze Results**
The program outputs:
- Final job schedule.
- Total profit.
- Execution time for sequential and parallel methods.

---

## **Contributing**
Contributions to improve the project are welcome! Fork the repository, make changes, and submit a pull request.

