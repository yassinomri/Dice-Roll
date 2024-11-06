# Dice Roll Project 🎲

Welcome to the **Dice Roll Project**! 🎉 This project combines embedded systems with a graphical user interface (GUI) to simulate a dice roll. The dice roll is controlled by a simple button press or a USB command, and the result is displayed both on the STM32 microcontroller and the GUI.

## 🛠️ What is it?

This project is made up of two main components:
1. **STM32 Microcontroller (Board)**: Handles the dice rolling logic, animates the LEDs to simulate a dice roll, and communicates the result back to the host computer via USB serial.
2. **Qt-based GUI**: A simple graphical user interface that lets users press a button to roll the dice, then displays the rolled result received from the microcontroller.

## 💻 How Does It Work?

1. **Roll the Dice**: 
   - Click the "Roll Dice!" button in the GUI or send the `R` command via the USB serial to the STM32 board.
   - The STM32 board animates the LEDs and rolls a random number between 1 and 6.

2. **Result Display**:
   - After the roll, the result (a number between 1 and 6) is sent back from the STM32 board to the GUI.
   - The GUI updates to show the result of the roll.

## 🛠️ Components Used

- **STM32F407 Microcontroller (Discovery)**: Handles the dice roll logic and USB serial communication.
- **Built-in LEDs**: Used to display the animation of the dice roll.
- **Qt 6**: A cross-platform C++ framework used to build the graphical user interface.
- **USB Serial Communication**: Communication between the STM32 board and the GUI.

## 🔧 Getting Started

To get started with this project, follow these steps:

### 1. 📦 Clone the Repository

Clone the repository to your local machine:

```bash
git clone https://github.com/yassinomri/Dice-Roll.git
```

## 🖥️ Set Up the STM32 Microcontroller

1. Make sure you have **STM32CubeIDE** installed and set up to program your STM32 board.
2. Compile and flash the firmware to the STM32 microcontroller.
3. Connect the board to your PC via USB.

## 💻 Set Up the Qt GUI

1. Install **Qt Creator** on your machine (you can download it [here](https://www.qt.io/download)).
2. Open the project in **Qt Creator** and build the GUI.
3. Make sure the serial communication port matches the one used by the STM32 board.

## 🧑‍💻 Run the Application

1. Press the "**Roll Dice!**" button in the Qt GUI to trigger the dice roll.
2. The STM32 board will animate the LEDs and send the roll result back to the GUI.
3. The GUI will display the result of the roll!

## 💡 Features

- 🎲 **Dice Roll Animation**: See the dice roll with LED animation on the STM32.
- 🔄 **Serial Communication**: Use USB serial communication to send and receive dice roll commands and results.
- 🖥️ **Qt-based GUI**: A user-friendly interface that allows you to trigger the roll and view the result.

## ⚙️ Code Explanation

### STM32 Board Code:
- The STM32 microcontroller listens for an 'R' command over USB serial.
- Upon receiving the command, it simulates a dice roll by lighting up LEDs and generates a random number between 1 and 6.
- The result is sent back over USB serial to the connected GUI.

### GUI Code:
- The Qt GUI has a button labeled **"Roll Dice!"** that sends the `R` command to the STM32.
- Once the result is received, the GUI updates to display the rolled number.

## 🧑‍💻 Contributing

Feel free to contribute to this project! If you have any ideas for improvements or bug fixes, please fork the repo, create a branch, and submit a pull request.

## 📬 Contact

If you have any questions or feedback, feel free to open an issue or reach out to me directly.

---

Happy coding and rolling! 🎲✨
