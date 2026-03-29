# Smart Shower Assistant

## Project Description
This project is a **smart shower assistant** built using **Arduino** and the **Rich Shield**. It helps monitor shower conditions by displaying **humidity** and **temperature**, while also providing a **shower timer** with visual **LED indicators** and **buzzer alerts**.

---

## Main Features
- Reads humidity using the **DHT sensor**
- Reads temperature using the **NTC temperature sensor**
- Displays values on the **4-digit TM1637 display**
- Uses a **potentiometer knob** to switch between humidity mode and button-controlled mode
- Uses **Button K1** to start a shower timer
- Uses **Button K2** to display temperature
- Turns on different **LED colors** based on timer stages
- Plays a melody when the temperature is too high
- Plays another melody when the timer ends

---

## How It Works

### 1. Humidity Display Mode
The potentiometer value is continuously read from **analog pin A0**.

- When the knob value is **800 or above**, the system reads the humidity from the **DHT sensor**
- The humidity value is then shown on the **4-digit display** with an **H** symbol
- The humidity value is also printed to the **Serial Monitor**

### 2. Button-Controlled Mode
When the knob value is **below 800**, the display is cleared and the system waits for button input:

- **Button K1** starts the timer
- **Button K2** reads and displays the temperature from the **NTC sensor**

### 3. Temperature Monitoring
When **Button K2** is pressed:

- The code reads the temperature from the **NTC sensor**
- It displays the temperature on the **4-digit display** with a **C** symbol
- It also prints both **temperature** and **humidity** values to **Serial** for monitoring or graphing
- If the temperature is **greater than 33°C**, the buzzer plays a warning song **("Two Tigers")**

### 4. Shower Timer
When **Button K1** is pressed, the `timer()` function starts:

- The timer counts from **0 to 20**
- It increases by **0.5** each step
- Each step is shown on the display
- The LEDs change color based on the timer stage:
  - **0 to 5** → Blue LED
  - **5 to 10** → Green LED
  - **10 to 15** → Yellow LED
  - **15 to 20** → Red LED

This gives the user a visual warning about how long they have been showering.

### 5. End-of-Timer Alert
At the end of the timer:

- The display is cleared
- All LEDs are turned off
- The buzzer plays another melody as an alert to indicate the shower time is over

---

## Components Used
- Arduino / Rich Shield
- DHT humidity sensor
- NTC temperature sensor
- TM1637 4-digit display
- Potentiometer
- 2 push buttons
- 4 LEDs (**Red, Green, Blue, Yellow**)
- Passive buzzer

---

## Purpose of the Project
The purpose of this project is to create a **smart bathroom/shower monitoring system** that helps users:

- Check humidity levels
- Monitor water temperature
- Manage shower duration
- Receive alerts when conditions become unsafe or when shower time is too long

---

## Possible Applications
- Smart bathroom monitoring
- Shower safety system
- Water usage awareness
- Educational Arduino project

---

## Author
**Your Name Here**
