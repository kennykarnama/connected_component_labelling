# Connected Component Labelling
Implementation of Connected Component Labelling Algorithm explained in http://aishack.in/tutorials/connected-component-labelling/
using OpenCV

# Prerequites

- git
- CMake >= 2.8
- OpenCV >= 2.4
- C++ 11 support
- Visual Studio 2015 (for Windows users)

# Configuration Instruction

### Windows user

For windows user, please use CMakeLists_Windows.txt before running CMake to compile it. 
Steps 
1. Rename `CMakeLists_windows.txt` to `CMakeLists.txt`
2. Ensure that you have already installed OpenCV on your Windows operating system. And also you have already linked to system path 
   the `bin` directory of OpenCV.
3. Change variable `OpenCV_dir` inside `CMakeLists.txt` to conform with your OpenCV build directory
4. Ensure you have already included cmake executable in system path, so you are able to use it in PowerShell or CMD. (I suggest PowerShell)
5. Open your power shell, clone this repository by issuing 
   
   `git clone https://github.com/kennykarnama/connected_component_labelling.git` 

6. Once you done cloning it, just issue command inside the repository directory

  `cmake .`
  
 7. If it has finished compiling then open `connected_components.sln` using your visual studio editor. 
 8. Head to Build --> Rebuild ccl.
 9. After completing, head to `debug` directory, you will find `ccl.exe`
 10. Done :D
 
### Linux user
 
For Linux user, please use CMakeLists_Linux.txt before running CMake to compile it. 
 
1. Rename `CMakeLists_Linux.txt` to `CMakeLists.txt`
2. Ensure you have already installed OpenCV correctly. 
3. Just run `cmake .`
4. After CMake compiled successfully, build the executable using `make`
5. You are all set now

# Running the program

For executing this program, below are the pattern to run it :

 ` ./ccl [image path file] [dummy args]`
 
 - [image path file] --> path to your picture files (ensure it is in binary or black-white picture)
 - [dummy args] --> just past whatever string to this second argument (initially it was meant to support optional arguments, but 
   not finished yet)

# Demo
![Alt Text](https://media.giphy.com/media/1xkNYtuPhefNxrW5KL/giphy.gif)

# Contributions

Any contributions will be appreciated because this program is still not ideal in design pattern, algorithm efficiency and code structuring. 
It also lacks of tests !

# License 
MIT
