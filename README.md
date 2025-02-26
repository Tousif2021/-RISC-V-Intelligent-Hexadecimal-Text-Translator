# 🚀 RISC-V Intelligent Hexadecimal Text Translator

## 📌 Overview
This project is developed for an embedded system using a RISC-V card (IO-Card REV C). It allows users to input hexadecimal values, which are then converted into their corresponding text characters and displayed on an output screen. A reset function is included to clear the display and restart the input process.

## 🎯 Features
- ✅ **Hexadecimal Input:** Users can enter hex codes through a keypad or input interface.
- ✅ **Text Display:** The corresponding characters are displayed as text/SMS in the output zone.
- ✅ **Reset Function:** A reset button clears the displayed text and allows a new input sequence.
- ✅ **Real-time Conversion:** Converts hex input to text dynamically as the user enters values.

## 🛠 Hardware Requirements
- 🖥 **RISC-V IO-Card REV C**
- 📟 **8x8 LED Matrix or LCD Display**
- ⌨️ **4x4 Keypad (for hex input)**
- 🔌 **GPIO Pins for interfacing**

## 💻 Software Requirements
- 📝 **Embedded C for RISC-V programming**
- 🛠 **Pre-configured GPIO subroutines**
- 📡 **Serial or display driver integration**

## ⚙️ How It Works
1. **User Input:**
   - The system awaits user input through a keypad.
   - Users enter hexadecimal values (e.g., `41 42 43` for `ABC`).
2. **Processing:**
   - The system maps each hex value to its corresponding ASCII character.
   - The text output updates dynamically.
3. **Output Display:**
   - The processed text is displayed in the output zone.
   - Users can continue entering hex values to extend the message.
4. **Reset Function:**
   - Pressing the reset button clears the display and input buffer.
   
## 📝 Example Usage
| 🔢 Hex Input  | 📝 ASCII Output |
|------------|-------------|
| 41 42 43   | ABC         |
| 48 45 4C 4C 4F | HELLO |

## 🚀 Installation & Deployment
1. **Clone the repository:**
   ```sh
   git clone https://github.com/Tousif2021/riscv-hex-to-text.git
   ```
2. **Navigate to the project directory:**
   ```sh
   cd riscv-hex-to-text
   ```
3. **Compile and flash the firmware to the RISC-V card:**
   ```sh
   make flash
   ```
4. **Power on the board and interact with the input system.**

## 🔮 Future Improvements
- ✨ Support for special characters and punctuation.
- 🖥 GUI-based interface for better visualization.
- 💾 EEPROM support to store previous messages.

## 📜 License
This project is open-source and available under the MIT License.

## 👤 Author
**MY PROFILE** - [Your GitHub Profile](https://github.com/yourusername)

