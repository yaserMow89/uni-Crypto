# uni-Crypto


## Setting up the Environment for MS Windows <br>
For windows environment there are only two things needed to run
the code (C,C++) on the **ESP chip**, being: <br>
### IDE (Arduino_ide):<br>
Arduino IDE is used in this case to run the code,
the IDE is available to download online, the following link:
[Arduino IDE Download Link](https://www.arduino.cc/en/software)
directs you to the official IDE's page, and there you can select windows
download and downlaod it. <br>
### Installing the Drivers: <br>
The Drivers for the specific chip being used in our case are available online through the link:
[ESP-32 Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
Once you get to the link please download the: **CP210x Universal Windows Driver**
And install it on your computer.
Once you are done with Installing both the drivers and the IDE,
open the IDE, at the first run it will ask for permission to install
some packages and also will ask for permissions on your machine, and once they are all
done you are all set, to run the code. <br>
## Setting up the Environment for Linxu (DES and 3DES code):
This applies only to the following directories inside the repository:
```
     3DES-OpenSSL/
     3DES-Scratch/
     DES-OpenSSL/
     DES-Scratch/
```
We used *Visual Studio Code* for our linux environment as IDE, can<br>
be installed using the command `sudo snap install code --classic`
    * Visual Studio Code was used for all the languages apart from <br>
    the *Rust* <br>
### Running the codes without the libraries:
Running the **C/C++** codes written from the scratch (without libraries):<br>
* Install the C/C++ extension by Microsoft in VSCode
* While running the code make sure that you are using `g++` as <br>
    your compiler<br>
Running **Java** codes written from the scratch (without libraries):<br>
* Install the extension *Extension Pack for Java* by Microsoft
* Install *JDK* for Ubuntu:
    * Can be installed using the following commands:
        ```
        sudo apt update 
        sudo apt install default-jre
        ```
        <br>
Running the **Python** codes written from the scratch (without libraries):<br>
* Install the Python Extension by Microsoft and run the code<br>
Running the **Rust** codes written from the scratch (without libraries):<br>
* It is different with Rust, compared to other languages;
* That is why, projects' Cargo directory is submitted
* Still there are some steps to be followed in order to run the code:
    * Install the Cargo using the command:
        * `sudo apt install cargo`
    * Build the project:
        * Go to the project directory, it could be for example `uni-Crypto/DES-Scratch/Rust`
        * Build the project using: `cargo build`
        * Run the project using: `cargo run`

## Selecting the board within the IDE (Linux and Windows):
Once the environment is set up, and you want to run the code, the board should be selected
to run the code on it and also see the output, in order to do that:<br>
* Make sure that the Board is connected to the computer
    * In case of windows, you can also look at the device manager to make sure the drivers
    are installed and the device is recognized
* In the top Horizontal ribbon, there is a dropdown stating:
  **Select other board and port...**
* A mini window pops up, with two sections:
    * **BOARDS**: select the **ESP32-S#-USB-OTG** as board
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
