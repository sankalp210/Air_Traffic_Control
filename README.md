# ✈️ Air Traffic Control System

A real-time command-line Air Traffic Management system developed in C. It simulates an air traffic controller's dashboard with efficient flight scheduling, cancellation, and real-time updates using ETA buckets and linked lists.

---

## 🧠 Project Goals

- Simulate a basic real-time **Air Traffic Control** dashboard.
- Efficiently **manage, insert, cancel**, and **view flight plans** based on Estimated Time of Arrival (ETA).
- Rearrange and visualize flights in **hour-based ETA buckets**.
- Practice hands-on **data structure and file handling** concepts in C.

---

## ⚙️ How It Works

- **Linked Lists** are used to represent dynamic flight entries.
- **24 ETA Buckets** are created (one for each hour of the day).
- Flight plans are loaded from `input.txt` and placed in the relevant ETA bucket.
- Each bucket contains a **sorted list of flights** based on departure time.
- Users can:
  - Add or cancel flights
  - View status by Flight ID
  - Print all flights
  - Rearrange dashboard based on current time
- All interactions are through a command-line menu.

---

## ✨ Key Features

- 🛬 **ETA-based Bucketing System:**  
  Flights are sorted into buckets based on their ETA (hour intervals).

- 🧾 **File-based Bulk Input:**  
  Load flight data from `input.txt`, supporting up to 200 entries.

- 🧮 **Sorted Insertion by Departure Time:**  
  Inside each bucket, flights are sorted for efficient access.

- 🗑️ **Flight Cancellation:**  
  Remove a flight by ID with clean memory management.

- 🔄 **Live Reorganization:**  
  Rearranges buckets dynamically based on current time to display upcoming flights.

---

## 🧩 Code Structure

```bash
air-traffic-control/
├── main.c              # Entire program logic
├── input.txt           # Input file with 200 flight entries
├── README.md           # Project overview (you're here)
