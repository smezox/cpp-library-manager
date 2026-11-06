# Object-Oriented Library Manager

A menu-driven C++ Library Management System built using Object-Oriented Programming, encapsulation, collections, and file persistence.

## Project Overview

This project provides an offline library management application for managing books, members, and borrowing records.

It imports fictional book records from a supplied CSV dataset and allows users to search books, register members, issue books, return books, and check availability.

## Features

- Add and display books.
- Search books by ID or title.
- Register and display library members.
- Issue books to registered members.
- Return borrowed books.
- Check book availability.
- Import initial records from CSV.
- Save and reload records using local CSV files.
- Reject duplicate book and member IDs.
- Handle missing records and invalid input.
- Validate publication years and borrowing dates.

## Technologies Used

- Language: C++
- Compiler: G++ (MinGW)
- Standard: C++17
- Editor: Visual Studio Code
- Storage: CSV files
- Collections: `std::vector`

## Project Structure

```text
cpp-library-manager/
│
├── main.cpp
├── Book.h
├── Book.cpp
├── Member.h
├── Member.cpp
├── Loan.h
├── Loan.cpp
├── Library.h
├── Library.cpp
├── README.md
│
├── data/
│   ├── library-records-sample.csv
│   ├── books.csv
│   ├── members.csv
│   └── loans.csv
│
└── screenshots/
    ├── menu.png
    ├── books.png
    ├── borrowing.png
    └── persistence.png
```

The three generated CSV files are created by the application. The original sample dataset is retained separately.

## Object-Oriented Design

The application uses four main classes.

### 1. Book

Stores book information:

- Book ID
- Title
- Author
- Category
- Publication year
- Availability
- Borrower ID
- Due date

### 2. Member

Stores member information:

- Member ID
- Member name

### 3. Loan

Stores borrowing information:

- Loan ID
- Book ID
- Member ID
- Issue date
- Due date
- Return status

### 4. Library

Manages the collections of books, members, and loans.

It provides functions for adding, searching, issuing, returning, importing, saving, and loading records.

## Menu Options

| Option | Operation |
|---|---|
| 1 | Add New Book |
| 2 | Display All Books |
| 3 | Search Book |
| 4 | Register Member |
| 5 | Display All Members |
| 6 | Issue Book |
| 7 | Return Book |
| 8 | Check Book Availability |
| 9 | Exit |

## How to Compile and Run

### Requirements

- Windows 10 or Windows 11
- Visual Studio Code
- G++ compiler installed and configured

### Step 1: Open the project

Open the `cpp-library-manager` folder in VS Code.

### Step 2: Open the terminal

Select Terminal → New Terminal.

Make sure the terminal is located in the project root directory.

### Step 3: Compile

Run:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp Book.cpp Member.cpp Loan.cpp Library.cpp -o library_manager.exe
```

### Step 4: Execute

Run:

```powershell
.\library_manager.exe
```

Keep the terminal's working directory at the project root so the application can access the `data` folder.

## Data Persistence

The application uses CSV files for local storage.

- `library-records-sample.csv`: Original supplied dataset.
- `books.csv`: Saved book records.
- `members.csv`: Saved member records.
- `loans.csv`: Saved borrowing records.

On first startup, the application imports the supplied dataset if no saved book file exists.
Subsequent startups load saved records. Changes are saved after menu operations and when exiting the application.

## Testing and Validation

The following manual tests were performed:

- Successful compilation using G++.
- Successful application startup.
- Importing six supplied book records.
- Searching for existing and nonexistent books.
- Registering members.
- Rejecting duplicate book IDs.
- Rejecting duplicate member IDs.
- Issuing available books.
- Rejecting already borrowed books.
- Returning borrowed books.
- Rejecting repeated returns.
- Checking book availability.
- Handling missing books and members.
- Rejecting invalid calendar dates.
- Rejecting due dates earlier than issue dates.
- Skipping malformed CSV records.
- Initializing records when the saved books file is missing.
- Verifying that member records survive application restarts.

## Sample Dataset

The project uses the fictional Library Records Seed CSV supplied with the assignment.
The dataset contains six sample books, including four available books and two borrowed books.

## Limitations

- The application is designed for offline, single-user use.
- Member contact details and authentication are not implemented.
- Existing borrowers without supplied names receive placeholder member names.
- The original dataset does not provide issue dates for existing loans, so these are recorded as `Unknown`.

## Conclusion

This project demonstrates practical C++ programming concepts, including classes, encapsulation, constructors, collections, functions, input validation, CSV processing, and file persistence.
It provides a foundation for a simple offline library management system and demonstrates how object-oriented design can be used to organize a real-world application.

---

**Project:** Object-Oriented Library Manager  
**Track:** C++ Programming  
**Language:** C++17