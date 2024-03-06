/*
* SPDX-License-Identifier: ISC
*
* Copyright (c) 2024 Afonso L. Morais <moraisafonso@protonmail.com>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*==== WL-Random.H ======================================	

	This is the header file for WL-Random.c enables the
	use of the key word 'CLEAR' to clear the screen in
	both windows and Unix based systems.
	Also has the declaration of the functions.
	
	Date: 28-02-2024
	Author: Afonso Morais
=========================================================*/

#ifdef _WIN32	// CASE THE OS IS WINDOWS

#include <stdlib.h>
#include <conio.h>

#define CLEAR "cls"
void clearInputBuffer() {
    while (_kbhit()) {
        _getch();
    }
}
#else		// CASE IS UNIX BASED

#include <unistd.h>
#include <unistd.h>
#include <termios.h>

#define CLEAR "clear"
void clearInputBuffer() {
    tcflush(STDIN_FILENO, TCIFLUSH);
}
#endif

// Functions
void drawFiles(const char *programName);		// Draws files tree
void openFile();					// Reads input options for file and opens chosen file/wordlist
void getRandomWord();					// Gets random word from the file/wordlist
void waitForInput();					// Waits for user to press ENTER (continue)
