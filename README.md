# 🌾 Rice Saver — Smart Grain Storage & Pest Protection System

> **IEEE Arduino Challenge Sphere 2024 — Top 10 Finalist 🏆**
> Selected among **300+ participating teams** and advanced to the **Final Showcase at Trace Expert City, Maradana, Sri Lanka.**

---

## 📌 Overview

**Rice Saver** is an automated, Arduino-based smart grain-storage monitoring and protection system designed to reduce post-harvest losses caused by **excessive humidity, temperature fluctuations, fungal growth, insect infestations, rodents, and unauthorized access**.

Rice stored for long periods can deteriorate rapidly when environmental conditions are not properly controlled. Rice Saver addresses this problem by continuously monitoring the storage environment and automatically responding when potentially harmful conditions are detected.

The prototype combines **environmental sensing, automated control, pest management, intrusion detection, and a local user interface** into a single embedded system.

### 🎯 Main Objectives

* 🌡️ Monitor storage temperature continuously
* 💧 Monitor relative humidity and identify unsafe conditions
* 🍄 Reduce the risk of fungal and microbial growth
* 🪲 Detect and control red-weevil infestations
* 🐀 Detect rodents and physical intrusion
* ⚡ Automate heater and ventilation control
* 📟 Provide real-time information through an LCD interface
* 🚨 Alert operators when storage conditions become unsafe
* 🔧 Provide manual diagnostics for quick inspection

---

## 🏆 Competition Achievement

Rice Saver was developed for the **IEEE Arduino Challenge Sphere 2024**, a competitive Arduino-based engineering challenge.

The project successfully:

* 🥇 Reached the **Top 10 Finalists**
* 👥 Competed against **300+ teams**
* 🎤 Advanced to the **final project showcase**
* 📍 Presented the prototype at **Trace Expert City, Maradana**
* 🔩 Demonstrated a working embedded automation system combining sensing, control, and pest-management concepts

This competition provided an opportunity to transform an agricultural problem into a practical embedded-systems solution under real project constraints.

---

# 💡 The Problem

Traditional rice storage facilities can experience significant losses due to several environmental and biological factors.

### 🍄 1. Fungal Growth

High moisture and unsuitable storage conditions can encourage fungal growth and deterioration of stored rice.

### 🌡️ 2. Temperature Fluctuations

Temperature changes can affect the quality and storage stability of rice over long periods.

### 🪲 3. Insect Infestation

Stored-grain insects such as **rice weevils** can damage grains and reproduce inside storage facilities, making early detection and control important.

### 🐀 4. Rodent Activity

Rats and other rodents can consume or contaminate stored grain while also damaging storage infrastructure.

### 👨‍🔧 5. Manual Monitoring

Traditional storage facilities may rely heavily on periodic manual inspection. This can result in delayed detection of dangerous environmental conditions or infestations.

---

# 🚀 Our Solution

Rice Saver creates an automated monitoring and response loop:

```text
        ┌─────────────────────────┐
        │     Rice Storage Area   │
        └────────────┬────────────┘
                     │
          ┌──────────▼──────────┐
          │ Environmental       │
          │ Sensors             │
          │                     │
          │ • Temperature       │
          │ • Humidity          │
          │ • PIR Motion        │
          └──────────┬──────────┘
                     │
                     ▼
            ┌─────────────────┐
            │     Arduino     │
            │   Controller    │
            └───────┬─────────┘
                    │
       ┌────────────┼─────────────┐
       │            │             │
       ▼            ▼             ▼
   ┌───────┐    ┌────────┐   ┌──────────┐
   │  LCD  │    │ Alerts │   │  Relay   │
   │Display│    │ LED    │   │ Control  │
   └───────┘    └────────┘   └────┬─────┘
                                   │
                         ┌─────────┴─────────┐
                         ▼                   ▼
                    ┌─────────┐         ┌─────────┐
                    │ Heater  │         │ Exhaust │
                    │         │         │   Fan   │
                    └─────────┘         └─────────┘
```

The Arduino continuously collects sensor readings, compares them with predefined thresholds, and determines whether the storage environment is safe.

When an unsafe condition is detected, the system provides an immediate visual warning and can activate the appropriate control mechanism.

---

# ✨ Key Features

## 🌡️ Automated Temperature Monitoring

The system continuously measures the temperature inside the storage environment.

A predefined safe operating window is used by the controller:

**17°C – 22°C**

If the temperature moves outside the configured range, the system indicates a **Danger** condition through the user interface and LED indicators.

---

## 💧 Humidity Monitoring

Relative humidity is continuously monitored to identify conditions that could increase the risk of grain deterioration and fungal growth.

Configured monitoring range:

**35% – 45% RH**

When the measured humidity exceeds the configured safe limits:

```text
Normal Condition
      ↓
Humidity Measurement
      ↓
Threshold Comparison
      ↓
Unsafe?
  ↙        ↘
No          Yes
↓            ↓
Continue    LED Alert
Monitoring  + LCD Warning
```

---

## 🪲 Thermal Pest Eradication

One of the major features of Rice Saver is its proposed **thermal treatment cycle** for controlling stored-grain insects.

When a treatment cycle is initiated, the controller operates the heater and exhaust system through a relay.

### Thermal Treatment Concept

```text
Normal Storage
     │
     ▼
Treatment Initiated
     │
     ▼
Heater Activated
     │
     ▼
Temperature Increased
     │
     ▼
Target Temperature
     │
     ▼
Controlled Treatment Period
     │
     ▼
Exhaust / Ventilation
     │
     ▼
Temperature Reduced
     │
     ▼
Return to Normal Storage
```

The prototype was designed around a target treatment temperature of approximately **60°C for a controlled period**, with ventilation used to help manage heat and moisture.

> ⚠️ **Prototype Safety Note:** The competition prototype simulated the high-power heating/ventilation equipment using a relay and indicator load. Any real implementation would require appropriate thermal sensors, fail-safe control, insulation, electrical protection, ventilation engineering, and validation of treatment parameters before being used with stored food.

---

# 🐀 Rodent & Intrusion Detection

A **PIR (Passive Infrared) sensor** is used to detect movement around the storage area.

Whenever motion is detected:

* The event is registered by the Arduino
* The motion counter is incremented
* The current count is displayed through the LCD interface

Example:

```text
MOTION DETECTED!

Motion Count: 07
```

This provides a simple way to monitor repeated activity around the storage unit.

---

# 📟 LCD User Interface

The system uses an **I2C LCD** as the local monitoring interface.

The display can provide:

* 🌡️ Current temperature
* 💧 Current humidity
* 🚨 Safety status
* 🐀 Motion count
* 🪲 Pest-treatment status
* ⚠️ Warning messages

A push button allows the operator to request environmental readings whenever required.

---

# 🔘 Manual Diagnostics

Although the system is designed for automatic operation, a manual diagnostic function was included.

By pressing the push button, the operator can retrieve the latest:

```text
Temperature
Humidity
System Status
```

This provides a simple local interface without requiring a computer or external monitoring system.

---

# 🧠 System Logic

The overall control logic can be summarized as:

```text
                 START
                   │
                   ▼
          Initialize Sensors
                   │
                   ▼
          Read Temperature
          Read Humidity
          Read PIR
                   │
                   ▼
       ┌─────────────────────┐
       │ Check Temperature   │
       └──────────┬──────────┘
                  │
          Outside Safe Range?
             /          \
           No            Yes
           │              │
           │          Danger Alert
           │              │
           └──────┬───────┘
                  ▼
       ┌─────────────────────┐
       │ Check Humidity      │
       └──────────┬──────────┘
                  │
          Outside Safe Range?
             /          \
           No            Yes
           │              │
           │          Danger Alert
           │              │
           └──────┬───────┘
                  ▼
          Check PIR Sensor
                  │
                  ▼
          Motion Detected?
             /          \
           No            Yes
           │              │
           │       Increment Counter
           │              │
           └──────┬───────┘
                  ▼
          Update LCD
                  │
                  ▼
             Repeat Loop
```

---

# 🛠️ Hardware Components

| Component                   | Purpose                              |
| --------------------------- | ------------------------------------ |
| **Arduino Microcontroller** | Main control unit                    |
| **DHT11 / DHT22**           | Temperature and humidity measurement |
| **PIR Sensor**              | Motion and intrusion detection       |
| **I2C LCD**                 | Local system interface               |
| **Relay Module**            | Switching control for external loads |
| **Heater / Indicator Bulb** | Thermal treatment simulation         |
| **Exhaust Fan**             | Ventilation during treatment         |
| **Push Button**             | Manual diagnostics                   |
| **LED Indicators**          | System status and warning indication |
| **Styrofoam Enclosure**     | Prototype storage chamber            |

---

# 🔌 Hardware Architecture

```text
                    ┌─────────────────┐
                    │      DHT        │
                    │ Temperature &   │
                    │ Humidity Sensor │
                    └────────┬────────┘
                             │
                             ▼
┌────────────┐        ┌───────────────┐
│ PIR Sensor ├───────►│               │
└────────────┘        │    ARDUINO    │
                      │               │
┌────────────┐        │  Main Control │
│ Push Button├───────►│               │
└────────────┘        └───────┬───────┘
                              │
             ┌────────────────┼────────────────┐
             │                │                │
             ▼                ▼                ▼
        ┌─────────┐      ┌─────────┐     ┌─────────┐
        │   LCD   │      │   LED   │     │  Relay  │
        │ Display │      │ Alerts  │     │ Module  │
        └─────────┘      └─────────┘     └────┬────┘
                                               │
                                        ┌──────┴──────┐
                                        ▼             ▼
                                     Heater        Fan
```

---

# 🧰 Software & Technologies

* **Arduino IDE**
* **Embedded C/C++**
* **Arduino Microcontroller Platform**
* **DHT Sensor Library**
* **I2C Communication**
* **Digital GPIO Control**
* **Relay-Based Actuation**
* **Real-Time Sensor Monitoring**

---

# 🏗️ Prototype Design

The prototype was constructed using a **Styrofoam enclosure** to represent a small-scale rice storage environment.

The enclosure allowed the team to demonstrate:

* Environmental monitoring
* Temperature control
* Humidity monitoring
* Motion detection
* Automated relay control
* Local data display
* Thermal treatment concept

The prototype architecture was designed with scalability in mind, allowing the same sensing and control concepts to be extended to larger storage environments.

---

# 😤 Challenges We Faced During the Competition

Building the prototype for a competition under time constraints came with several challenges.

## 1. ⏱️ Limited Development Time

The system involved multiple subsystems that had to work together:

* Sensors
* LCD
* Arduino
* Relay
* Heater
* Fan
* PIR
* User interface

Integrating everything into a single stable system within the competition timeline required careful prioritization and testing.

---

## 2. 🔌 Hardware Integration Problems

Connecting multiple modules to a single Arduino introduced challenges involving:

* GPIO allocation
* Power distribution
* Sensor wiring
* Grounding
* Relay connections
* I2C communication

A failure in one subsystem could affect the behavior of the entire prototype.

We had to repeatedly test individual modules before integrating them into the complete system.

---

## 3. 📟 LCD & Sensor Reliability

During development, sensor readings were not always immediately stable.

Environmental sensors can produce fluctuating values, especially during changes in temperature and humidity.

We had to improve the program logic so that the system could distinguish between normal fluctuations and genuinely unsafe conditions.

---

## 4. 🔥 Managing the Thermal Treatment Concept

The thermal eradication mechanism introduced an additional challenge because the system needed to coordinate:

**Temperature → Heater → Fan → Treatment Duration → Safe Recovery**

This required careful consideration of timing, temperature monitoring, and relay control.

For the competition prototype, the high-power heating system was represented using a safer simulated load rather than exposing the demonstration setup to unnecessary electrical and thermal risks.

---

## 5. 🧩 Mechanical & Enclosure Constraints

Fitting sensors, wiring, LCD, switches, LEDs, and actuators into a compact Styrofoam prototype was challenging.

The physical layout had to allow:

* Sensors to measure the internal environment
* The LCD to remain visible
* Buttons to remain accessible
* Wires to remain organized
* Actuators to be demonstrated safely

This required several iterations of the prototype layout.

---

## 6. 🐛 Debugging Multiple Systems Simultaneously

When the complete system was connected, identifying the source of a problem became more difficult.

For example:

```text
Incorrect LCD reading
       ↓
Is the sensor wrong?
       ↓
Is the Arduino logic wrong?
       ↓
Is the I2C communication wrong?
       ↓
Is the power supply unstable?
       ↓
Is the wiring incorrect?
```

We therefore adopted a **module-by-module testing approach**, verifying each subsystem independently before combining them.

---

## 7. 🎤 Demonstrating the Project Under Competition Pressure

A working prototype is only one part of a competition.

The team also had to clearly explain:

* The agricultural problem
* Why the problem matters
* How the system works
* Why automation is useful
* How the thermal treatment works
* How the prototype could be scaled

Presenting a hardware project while simultaneously demonstrating its functionality under time pressure was an important learning experience.

---

# 📈 Future Improvements

Rice Saver was developed as a prototype, but the concept can be extended significantly.

### 🌐 IoT Connectivity

Add Wi-Fi/LoRa/GSM connectivity to allow remote monitoring of:

* Temperature
* Humidity
* Pest-treatment status
* Motion events
* Historical data

### 📊 Cloud Dashboard

A web or mobile dashboard could provide:

```text
Temperature ───────── 20.4°C
Humidity ──────────── 41.2%
Storage Status ────── SAFE
Motion Events ─────── 12
Treatment ─────────── INACTIVE
```

### 🤖 AI-Based Pest Detection

A camera could be added to detect:

* Weevils
* Rodents
* Mold
* Grain discoloration

Computer vision could potentially identify infestations earlier than manual inspection.

### 📡 Distributed Sensor Network

Large warehouses could use multiple sensor nodes distributed throughout the storage area instead of relying on a single sensor.

```text
              Storage Warehouse

      [Sensor 1]       [Sensor 2]

           │               │
           └──────┬────────┘
                  │
             Gateway
                  │
          ┌───────┴───────┐
          │ Cloud / Server│
          └───────────────┘

      [Sensor 3]       [Sensor 4]
```

This would allow environmental differences between different regions of a warehouse to be detected.

### ⚡ Improved Safety System

A production-scale system should include:

* Independent temperature cut-offs
* Multiple temperature sensors
* Thermal fuses
* Emergency shutdown
* Proper electrical isolation
* Industrial-grade relays/contactors
* Fire protection
* Controlled ventilation
* Fail-safe software
* Food-safety validation

---

# 🎓 What We Learned

The Rice Saver project gave us practical experience beyond simply programming an Arduino.

Through the project, we gained experience in:

* 🔧 Embedded system development
* 🔌 Hardware integration
* 📡 Sensor interfacing
* ⚡ Relay and actuator control
* 📟 LCD/I2C communication
* 🧠 Control-system logic
* 🐛 Hardware/software debugging
* 🏗️ Rapid prototyping
* 🌾 Applying engineering to agricultural problems
* 🎤 Technical presentation and project pitching
* 🤝 Teamwork under competition deadlines

Most importantly, the project taught us that **a good engineering solution is not only about making individual components work—it is about integrating them into a reliable system that addresses a real-world problem.**

---

# 📸 Project Showcase

> Add your project photographs here.

```text
📷 Prototype
📷 Team Photo
📷 Competition Presentation
📷 Circuit / Hardware
📷 Final Showcase
```

Example:

```markdown
![Rice Saver Prototype](images/rice-saver-prototype.jpg)

![Rice Saver Team](images/team.jpg)

![Competition Showcase](images/showcase.jpg)
```

---

# 📁 Project Structure

```text
Rice-Saver/
│
├── README.md
│
├── Arduino/
│   └── Rice_Saver.ino
│
├── Circuit/
│   ├── circuit_diagram.png
│   └── wiring_diagram.png
│
├── CAD/
│   └── enclosure/
│
├── Documentation/
│   ├── proposal.pdf
│   └── presentation.pdf
│
├── Images/
│   ├── prototype.jpg
│   ├── circuit.jpg
│   └── competition.jpg
│
└── LICENSE
```

---

# 👥 Team

**Rice Saver — IEEE Arduino Challenge Sphere 2024**

Developed as a collaborative engineering project for the IEEE Arduino Challenge Sphere 2024.

> 
| Member           | Role                                                                       |
| -----------------| -------------------------------------------------------------------------- |
| Inuka Jithmal(Me)| Embedded Systems,Hardware & Electronics,Mechanical Design , Documentation  |                 
| Vihanga Nimsara  | Software & Control                                                         |


---

# 🏆 Achievement

### IEEE Arduino Challenge Sphere 2024

**Top 10 Finalist**

**300+ Participating Teams**

**Final Showcase — Trace Expert City, Maradana**

---

# 📜 License

This project is intended for **educational, research, and prototype-development purposes**.

Before adapting the design for real grain-storage facilities, the thermal treatment system, electrical safety, food-safety requirements, pest-control effectiveness, and environmental operating limits should be independently validated.

---

## 🌾 Rice Saver

**Smart Monitoring. Automated Protection. Safer Grain Storage.**

> *Engineering technology to protect what we grow.*
