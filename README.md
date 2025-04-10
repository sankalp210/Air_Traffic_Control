# ✈️ Air Traffic Control System

A real-time air traffic management system developed using C programming and Linked List data structures. The system ensures efficient flight operations, dynamic scheduling, and data integrity through robust design and architecture.

## 📌 Project Goals

- Develop a real-time flight tracking and scheduling system.
- Implement an efficient and responsive system using core data structures.
- Provide reliable and scalable operations using persistent file storage.

## 🛠️ Tech Stack & Tools

- **Language:** C
- **Data Structures:** Linked List
- **Persistence:** File-based storage
- **Algorithmic Techniques:** ETA-based scheduling, CRUD operations

## 🚀 Features

- 🛫 **Real-Time Scheduling:**  
  Implements a dynamic flight scheduling system based on ETA using bucket-based organization.

- 📋 **Flight Management:**  
  Allows addition, deletion, and update of flight operations using CRUD functionalities.

- 💾 **Persistent Storage:**  
  Flight data is stored in files, ensuring durability across sessions.

- 🧑‍✈️ **Responsive Interface:**  
  Provides a simple command-line interface for controlling and monitoring flights.

- 🛡️ **Data Integrity:**  
  Implements error-handling and validation mechanisms to ensure correctness of operations.

## ⚙️ How It Works

1. Each flight is represented using a node in a linked list.
2. Flights are inserted into buckets based on ETA for optimized scheduling.
3. User can perform operations like:
   - Add new flight
   - Delete existing flight
   - View all flights
   - Schedule flights based on ETA
4. All changes are saved to a file and loaded on startup.

## 📂 File Structure

```bash
.
├── main.c              # Main driver code
├── flights.c           # Flight operations (CRUD)
├── schedule.c          # Scheduling logic
├── storage.c           # File persistence functions
├── utils.c             # Utility and validation functions
├── README.md           # You're here!
