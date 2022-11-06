# STM32Cube Expansion Pack CAN Stack
Com-Stack for CAN using the [STM32ExpansionPack system](https://wiki.st.com/stm32mcu/wiki/Introduction_to_STM32Cube_Expansion_Packages).  

## Dependencies
+ The software using the STM32Cube system based on the STM32 HAL.
+ Because of the use of gcc compiler inside the STM32CubeIDE, this is my compiler. Adds are welcome.
+ Today the Expansion Pack is for STM32 controller with the bxCAN controller. To extend for other controller it needs to adjust the hardware interfacing class.  

## This isn't a compilable project at all
The including code is to build the ExpansionPack with the **STM32PackCreator**.  
There are some hand-made changes inside to use C++ instead of the plain-C. 
So be careful when you touching templates for code generation.

The "source" folder holds the source to build the STM32ExpansionPack (using the **STM32PackCreator**).
The "pack" folder is the working directory of the **STM32PackCreator**. So it holds the creator project file and the prepared templates for code generation.
There will be compileable projects inside the "projects" folder. These projects are intend as tutorials of the expansion pack. The "Sandbox" project is the project to develop the source code of the pack.

### Previous work
I started this project on my own. And changed the name and version numbering on publishing. I kept the old version log, so you can see work done and some experimental states. Maybe there are some points with deviating naming.

## Source code documentation
There will be also the doxygen generated [source code documentation](./html/index.html). This docu don't comes from the pack it self. You can build this docu inside a project using the ExpansionPack.  
Besides the normal source code documentation it includes a detailed description in german language for usage and internal behavior. If somebody can add a multi language support to doxygen it would be nice.