#include <stdio.h>
#include <string.h>

#define INPUT_BUFFER_LENGTH 2
#define OUTPUT_LENGTH INPUT_BUFFER_LENGTH

/*
 *  input: Single numeric character
 *  output: Input character. Exits in case of invalid input.
 */

int main(void) {
  char prompt[] = "Enter a character: ";
  char prompt_format[] = "%s";
  // Print prompt
  __asm {
		lea eax, prompt
		push eax

		lea eax, prompt_format
		push eax

		call printf

                 // Clear stack
		pop ebx
		pop ebx
  }
  ;

  char input[INPUT_BUFFER_LENGTH];
  input[1] = '\0';
  char input_format[] = "%c";

  char output_message[] = "Mirror of the input: ";
  char output_format[] = "%s%s\n";

  char ignore_message[] = "Invalid input, ignored\n";
  char ignore_message_format[] = "%s";

  _asm {
    // Take input
		lea eax, input
		push eax

		lea eax, input_format
		push eax

		call scanf

            // Clean stack
		pop ebx
		pop ebx

                // Test input
		cmp input[0], '0'
		jb ignore_input

		cmp input[0], '9'
		ja ignore_input

        // Print input

		lea eax, input
		push eax

		lea eax, output_message
		push eax

		lea eax, output_format
		push eax

		call printf

            // Clean stack
		pop ebx
		pop ebx
		pop ebx

		jmp exit

	ignore_input:
		lea eax, ignore_message
		push eax

		lea eax, ignore_message_format
		push eax

		call printf

            // Clean stack
		pop ebx
		pop ebx

		exit:
  }

  return 0;
}
