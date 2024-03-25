UNI-CRYPTO
=================================

> The repo is also available on github: [repo link](https://github.com/yaserMow89/uni-Crypto)

## Setting up the Environment for MS Windows <br>
For windows environment there are only two things needed to run the code (C,C++) on the **ESP chip**, being:
### IDE (Arduino_ide):
Arduino IDE is used in this case to run the code,
the IDE is available to download online, the following link:
[Arduino IDE Download Link](https://www.arduino.cc/en/software)
directs you to the official IDE's page, and there you can select windows
download and downlaod and install it.
### Installing the Drivers: 
The Drivers for the specific chip being used in our case are available online through the link:
[ESP-32 Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
Once you get to the link please download the: **CP210x Universal Windows Driver**
And install it on your computer.
Once you are done with Installing both the drivers and the IDE,
open the IDE, at the first run it will ask for permission to install
some packages and also will ask for permissions on your machine, and once they are all
done you are all set, to run the code.
> Note: The windows Environment setup only works with the `Arduino/` directory; Meaning you can only run the Arduino codes on a Windows machine with the above given instructions
## Selecting the board within the IDE (Linux and Windows):
Once the environment is set up, and you want to run the code, the board should be selected
to run the code on it and also see the output, in order to do that:
* Make sure that the Board is connected to the computer
    * In case of windows, you can also look at the device manager to make sure the drivers are installed and the device is recognized
* In the top Horizontal ribbon, there is a dropdown stating: **Select other board and port...**, open it
* A mini window pops up, with two sections:
    * **BOARDS**: select the **ESP32-S3-USB-OTG** as board
    * **PORTS**: Select the available serial port for the device, and click ok
* Above was for **Board** and **Port** selection
* For looking at the output results, in the same horizontal bar at the very right of it
there is a **Magnifier** symbol, when you hover mouse over it, will say **Serial Monitor**,
Press on it
* Once the Serial Monitor opens, at the right side of the ribbon there is a Line Manager with two elements:
    * **New Line**
        * Leave it with *New Line*
    * **Number baud**
        * For the *Number baud* select *115200 baud*
* Once all these steps are done, you should be able to see the output from the ESP Device
> Note: While trying to access the device, it is better to close all the windows of the IDE apart from the running one, because sometimes one instance of the IDE locks the device, and does not give access to other running instances of the IDE
## Running the code on Arduino IDE:
Once you are done with the sections **Selecting the board within the IDE (Linux and Windows)** (and also **Setting up the Environment for MS Windows** for windows), you can just open the *Arduino IDE* and open each of the codes that you want to run. You can find a *check mark* and a *Directional Sign* on the top horizontal ribbon at the very left of the application.
- The *Check mark* is for verifying (Compiling) the code.
- The *Directional Sign* flashes (uploades) the code on the chip. 
You can simply Compile the code and flash it on the device, everytime you wish to run.
> Note: The IDE for Linux can also be downloaded from the link: [Arduino IDE Download Link](https://www.arduino.cc/en/software). Once downloaded, it can be extracted and will give you executable file for openning the IDE, can be opened by the command `./arduino-ide` inside the IDE's directory

## Setting up the Environment for Linux and running the code:
> Note: The following guidelines only apply to the codes that are **Not** intended to run on **Arduino IDE**.
* This applies only to the following directories inside the repository:
```
    Library/3DES
    Library/DES
    Library/RSA
    Scratch/3DES
    Scratch/DES
    Scratch/RSA    
```
> Note: The instructions on how to run the *AES-CBC* & *AES-ECB* is given within the directories themselves, in a *README* file
* We used the *Visual Studio Code* for our linux environment as IDE, it can be installed using the command `sudo snap install code --classic` 
* Visual Studio Code was used for all the languages apart from the *Rust*.
* Running the **C/C++** codes:
    * Install the C/C++ extension by Microsoft inside the VSCode
    * Nothing else should be done while running the code *without the libraries*, only make sure that you are usng `g++` as your compiler
    * Running **C/C++** code written in the libraries.
        * Since DES and 3DES are not considered secure practices these days, running C/C++ code with the openssl library is done differently.
            * For running the *C++* codes, run the following command to make the binary:
                * `g++ -w CodeFileName.cpp -lssl -lcrypto -o binaryOutputCPP`
                * Now execute the binary file: `./binaryOutputCPP`
            * For running the *C* codes, run the following command to make the binary:
                * `gcc -w CodeFileName.c -lssl -lcrypto -o binaryOutputC`
                * Now execute the binary file: `./binaryOutputC`
* Running **Java** codes:
    * Install the extension *Extension Pack for Java* by Microsoft (inside the VSCode)
    * Install *JDK* for Ubuntu:
        * Can be installed using the following commands:
            ```
            sudo apt update
            sudo apt install default-jre
            ```
    * Then, you can run the code from the `Main` method
* Running the **Python** codes:
    * Install the Python Extension by Microsoft and run the code
* Running the **Rust** codes:
    * It is different with *Rust*, compared to other languages
    * That is why, projects' Cargo directory is submitted (without Libraries)
    * Still there are some steps to be followed in order to run the code
    * Below is step-by-step guide for running the code **without the libraries**:
        * Install the Cargo using the command:
            * `sudo apt install cargo`
        * Build the project:
            * Go to the project directory, it could be for example `uni-Crypto/Scratch/3DES/Rust`
            * Build the project using: `cargo build`
            * Run the project using: `cargo run`
    * For running the *Rust* Code written in *libraries*, an online playground should be used. Please copy the source code and paste it in [Rust Play-ground](https://play.rust-lang.org/) and run it.
> Note: DES and 3DES codes without libraries, work perfectly when the input data is a block of 64 bits or a multiplication of 64 bits. When it is not divisable by 64 bits, it will padd the data to make it divisable by 64 bits, and in that case the padded data will be with the decrypted data, after the encryption and decryption is done; please ignore it.

