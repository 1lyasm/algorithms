#include <stdio.h>

/*
 *	input: Nonempty C-string
 *	output: String printed to stdout with each word in newline
 */
int main() {
  char input_string[] =
      "In order to exist, man must rebel, but rebellion must respect\
 limits that it discovers in itself";

  char new_line[] = "\n";
  char string_output_format[] = "%s";
  int i = 0;
  char unit_length_string[] = "0";
  while (input_string[i] != '\0') {
    _asm {
      // Put current character in dl
			mov edx, i
			mov dl, input_string[edx]

			cmp dl, ' '
			jne print_character

          // Print new_line
			lea eax, new_line
			push eax

			lea eax, string_output_format
			push eax

			call printf

              // Clear stack
			pop ebx
			pop ebx
			
			jmp end

		print_character:
			mov unit_length_string[0], dl
			lea eax, unit_length_string
			push eax

			lea eax, string_output_format
			push eax

			call printf

              // Clear stack
			pop ebx
			pop ebx
		end:
    }
    ;
    _asm {inc i}
    ;
  }

  printf("%s", "\n");
  return 0;
}
