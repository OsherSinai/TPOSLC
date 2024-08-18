/*
	TPOSLC
	A LibC implementation for TPOS (Testing and Prototyping Operating System).

	Copyright © 2024 by Osher Sinai.

	This file is part of TPOSLC (Testing and Prototyping Operating System LibC).

	TPOSLC is free software:
	you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
	either version 3 of the License, or (at your option) any later version.

	TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with TPOSLC.
	If not, see <https://www.gnu.org/licenses/>.
*/
#include <include\ctype.h>
extern "C" {

int isalnum(int c){
	return isalpha(c) != 0 || isdigit(c) != 0;
}

int isalpha(int c){
	return isupper(c) != 0 || islower(c) != 0;
}

int isblank(int c) {
	return (c == (int)' ') || (c == (int)'\t');
}

int iscntrl(int c) {
	return (c < (int)' ') || (c == 127);
}

int isdigit(int c) {
	return ((c >= (int)'0') && (c <= (int)'9'));
}

int isgraph(int c) {
	return  (((int)' ' < c) && (c < 127));
}

int islower(int c) {
	return (((int)'a' <= c) && ((int)'z' >= c));
}

int isprint(int c) {
	return (((int)' ' <= c) && (c < 127));
}

int isspace(int c) {
	return (c == ' ') || (c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v');
}

int ispunct(int c) {
	return isprint(c) != 0 && !(isspace(c) != 0 || isalnum(c) != 0);
}

int isupper(int c) {
	return (((int)'A' <= c) && ((int)'Z' >= c));
}

int isxdigit(int c) {
	return
		isdigit(c) ||
		(((int)'A' <= c) && ((int)'F' >= c)) ||
			(((int)'a' <= c) && ((int)'f' >= c));

}

int tolower(int c) {
	if (isupper(c))
		c += 0x20;
	return c;
}
int toupper(int c) {
	if (islower(c))
		c -= 0x20;
	return c;
}

}