# Bank & ATM Management System

A console-based **Bank & ATM Management System** built in C++. It supports admin-controlled bank operations (create accounts, deposit, withdraw, transfer, bill payment) and a self-service ATM module (balance check, withdraw, view account details) — all customer transactions are authenticated using a **4-digit PIN**, and account data is persisted to a local text file.

## Features

- **Admin Login** — Email + Password protected access to Bank Management.
- **New User Registration** — Create an account with a PIN (no password stored per account).
- **Already User** — View account details after PIN verification.
- **Deposit** — Add funds to an account (PIN protected).
- **Withdraw** — Withdraw funds with balance validation (PIN protected).
- **Transfer** — Move funds between two accounts with sender/receiver validation (PIN protected).
- **Bill Payment** — Pay bills from account balance; logged to `bill.txt` (PIN protected).
- **ATM Management** — Independent self-service module:
  - Check balance
  - Withdraw cash
  - View account details
- Masked PIN/password input (shows `*` while typing) using `conio.h`.
- All account data stored in and loaded from `bank.txt` (created automatically on first run).

## Tech Stack

- **Language:** C++ (C++11 or later)
- **Libraries:** `iostream`, `fstream`, `string`, `vector`, `conio.h`, `cstdlib`
- **Storage:** Plain text files (`bank.txt` for accounts, `bill.txt` for bill payment logs)
- **Platform:** Windows (uses `conio.h` and `system("cls")`, both Windows-specific)

## Project Structure

```
Bank & ATM Management/
├── Bank & ATM Management System.cpp   # Main source code
├── bank.txt                           # Account records (auto-created/updated at runtime)
├── bill.txt                           # Bill payment logs (auto-created at runtime)
└── README.md                          # This file
```

## Requirements

- Windows OS
- A C++ compiler with `conio.h` support (e.g. MinGW-w64 `g++`, or MSVC via Visual Studio)
- VS Code (optional, for the IDE workflow) with the C/C++ extension, or Visual Studio

## Setup & Running

### Option A — Compile via terminal (MinGW / g++)

```bash
g++ "Bank & ATM Management System.cpp" -o bank.exe
.\bank.exe
```

### Option B — Visual Studio

1. Open the `.cpp` file in a Visual Studio project (or create a new empty C++ console project and add the file).
2. Build the solution (`Ctrl+Shift+B`).
3. Run with `Ctrl+F5` (Start Without Debugging).

### Option C — VS Code

1. Install the **C/C++** extension (Microsoft) and ensure MinGW `g++` is on your system `PATH`.
2. Open the project folder in VS Code.
3. Use the built-in terminal to run the commands from Option A, or use the Run ▷ button on the file.

## Admin Credentials (default)

| Field    | Value              |
|----------|---------------------|
| Email    | `m.ahmad@gmail.com` |
| Password | `ahmad123`           |


## Usage Notes

- On first run, `bank.txt` doesn't need to exist — it will be created automatically once a new user is added.
- PIN is always 4 digits and is required for every customer-facing transaction (deposit, withdraw, transfer, bill payment, balance check, view details).
- Admin Email + Password is only required to enter the **Bank Management** module from the main Control Panel; it is not tied to any individual customer account.
- If you're upgrading from an older version of this project (where accounts stored a password instead of a PIN), delete or rename the old `bank.txt` before running — the file formats aren't compatible and mismatched fields will cause login/lookup failures.

## Known Limitations

- `conio.h` and `system("cls")` are Windows-only; the project will need modification (e.g. replacing with a cross-platform input/clear-screen approach) to run on Linux/macOS.
- Data is stored in plain text with no encryption — not suitable for production or real financial use, intended for academic/demo purposes only.

## Author

Muhammad Ahmad
