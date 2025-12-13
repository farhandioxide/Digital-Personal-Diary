# 📔 Personal Diary Program (C)

A **console-based personal diary application written in C**, featuring **user authentication**, **colored terminal UI**, and full **CRUD operations** for diary entries.
Each user gets their own private diary stored locally using file handling.

---

#  Features

*  **User Authentication**

  * Signup & Login system
  * Multiple users supported
  * Credentials stored locally

*  **Diary Management**

  * Add new diary entries (date, title, content)
  * View all entries
  * Search entries by entry number
  * Edit existing entries
  * Delete entries with confirmation

*  **Export Functionality**

  * Export all diary entries to a separate text file

*  **Colorful Terminal Interface**

  * Uses ANSI escape codes for better readability

*  **File-Based Storage**

  * Each user has their own diary file
  * No external database required

---

##  Technologies Used

* **Language:** C
* **Concepts:**

  * File handling (`fopen`, `fprintf`, `fgets`, `fscanf`)
  * String manipulation
  * Structures of modular programming
  * Input validation
  * ANSI terminal colors

---

##  File Structure

```
├── main.c              # Source code
├── user.txt            # Stores usernames and passwords
├── <username>_diary.txt # Individual user diary files
├── <username>_export.txt # Exported diary entries
```

#  How It Works

1. **Signup / Login**

   * Users register with a username and password.
   * Credentials are stored in `user.txt`.

2. **Diary Menu**

   * After login, users can manage diary entries.
   * Each entry is stored in a user-specific diary file.

3. **Entry Format**

```
DATE: DD/MM/YYYY
TITLE: Entry Title
CONTENT:
Your diary text...
---
```

---

#  Sample Actions

* Add entries until you type `~` on a new line to finish content.
* Edit or delete entries by selecting their entry number.
* Export all entries with one command.

---

##  Future Improvements

*  Password hashing
*  Search by date or title
*  Better file structure
*  Improved input validation
*  Cross-platform enhancements

---

##  License

This project is open-source and available for educational use.

---
