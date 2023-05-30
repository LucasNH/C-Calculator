#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stdbool.h"


/**
 * This function determines if the input <n> is a numeric representation,
 * accounting for sign as well as decimal point.
 */
int is_numeric(bool *numeric, char *n) {
	*numeric = true;
	bool decimal_found = false;

	// handling first character, accounting for sign or decimal point
	if (!isdigit(n[0]) && (NULL == strchr("+-.", n[0]))) {
		*numeric = false;
		return 0;
	}
	for (int i = 1; n[i] != '\0'; i++) {
		if (!isdigit(n[i])) {
			if ('.' == n[i]) {
				// handling decimal point
				if (!decimal_found) {
					decimal_found = true;
				} else {
					*numeric = false;
					break;
				}
			} else {
				*numeric = false;
				break;
			}
		}
	}
	return 0;
}

/**
 * This function keeps prompting the user to input the operands until the inputs are valid.
 */
int input_operands(double *n1, double *n2) {
	bool valid_operand = false;
	char n1_str[128], n2_str[128];
	while(!valid_operand) {
		printf("Enter two operands (a b): ");
		scanf("%s %s", n1_str, n2_str);

		// validating first operand
		is_numeric(&valid_operand, n1_str);
		if (!valid_operand) {
			printf("The operand must be numeric.\n");
			continue;
		}

		// validating second operand
		is_numeric(&valid_operand, n2_str);
		if (!valid_operand) {
			printf("The operand must be numeric.\n");
		}
	}

	// convert inputs from string to double
	*n1 = strtod(n1_str, NULL);
	*n2 = strtod(n2_str, NULL);
	return 0;
}

/**
 * This main function prompts the user for a basic operation (either addition, subtraction, multiplication, 
 * or addition), then, given two valid operands, computes the corresponding calculation.
 */
int main() {
	printf("\nWelcome to the C Calculator v1.0.0\n");
	printf("This software is free for personal use, however, both\nprofessional and enterprise use require a license.\n\n");

	char operation;
	double n1, n2;

	while (1) {
		printf("Enter an operator (+, -, *, /) or quit (q): ");
		scanf(" %c", &operation);

		// quitting program
		if ('q' == operation) {
			break;
		}

		// validating operation
		if (NULL == strchr("+-*/", operation)) {
			printf("Invalid operation.\n");
			continue;
		}

		// inputting operands
		input_operands(&n1, &n2);

		// computing calculation
		switch (operation) {
			case '+':
				printf("%f + %f = %f\n\n", n1, n2, n1 + n2);
				break;
			case '-':
				printf("%f - %f = %f\n\n", n1, n2, n1 - n2);
				break;
			case '*':
				printf("%f * %f = %f\n\n", n1, n2, n1 * n2);
				break;
			case '/':
				printf("%f / %f = %f\n\n", n1, n2, n1 / n2);
				break;
		}
	}

    return 0;
}

