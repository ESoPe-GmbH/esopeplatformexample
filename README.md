# Example Project ESP32S3 with BT817

This example software shows the version number, one counter for the seconds till system start and a button which increments a counter. This is only used to demonstrate the combination of ESP32S3 and BT817.

## Hardware

This project uses the Espressif ESP32S3 microcontroller in combination with the bridgetek BT817 graphic controller. The PCB used in this example is the ESoPe [ESP32S3_BT817](https://esope.de/de/produkte/esope-plattform?view=article&id=78&catid=11) board in combination with a Glyn family concept display. The software can be flashed using the ESP-PROG from Espressif.

Supported displays are:

- ETML035023UDRA (3,5" | 320 x 240)
- ETML043023UDRA (4,3" | 480 x 272)
- ETML050023UDRA (5" | 800 x 480)
- ETML070023UDRA (7" | 800 x 480)

Connect the display:

![image](https://github.com/user-attachments/assets/aa533fbd-98b3-42f7-afb2-a4ca6bd44f4f)
	
1.	Open the black lid on 50-pin X3.
2.	Push the ZIF cable of the display in the slot on the other side. The contacts are visible to the user.
3.	Close the black lid.

Connect the touch:

![image](https://github.com/user-attachments/assets/6b97d137-5b20-4289-bd20-4c28879cde87)

1.	Open the black lid on 6-pin X4.
2.	Push the ZIF cable of the display in the slot on the other side. The contacts are not visible to the user.
3.	Close the black lid.

## Usage

To compile this software, the Espressif ESP-IDF is needed. The software was tested using version 4.4.6 and 5.2.1. The current sdkconfig is created using 4.4.6.

Steps to use this project:

1. Copy this project into a Git repository of your own.
   1. Make sure the repository is initialized with `git init` or is a subfolder of a git repository.
2. Open CMakeLists.txt in the root folder.
   1. Replace the ESoPePlatformExample with the name of your project.
3. Modify the config files under components/config to match your own project.
4. Open the esp-idf command prompt.
5. Change with `cd "C:\..."` to the directory where this README can be found.
6. Call `idf.py build` to compile the software.
7. Use `idf.py flash` to flash the software to the pcb.

Alternative to step 4 you can also use Visual Studio Code with the ESP-IDF extension to compile the software instead.
