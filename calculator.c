#include <stdio.h>

int main(void) {
    char s[100], op = '+';
    int i = 0, number, sum = 0, term = 0, needNumber = 1;

    printf("Enter an expression: ");
    fgets(s, sizeof(s), stdin);

    while (s[i] != '\0' && s[i] != '\n') {
        if (s[i] == ' ') {
            i++;
        }
        else if (s[i] >= '0' && s[i] <= '9') {
            if (!needNumber) {
                printf("Error: Invalid expression.\n");
                return 0;
            }

            number = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                number = number * 10 + (s[i] - '0');
                i++;
            }

            if (op == '+') term = number;
            else if (op == '-') term = -number;
            else if (op == '*') term = term * number;
            else {
                if (number == 0) {
                    printf("Error: Division by zero.\n");
                    return 0;
                }
                term = term / number;
            }
            needNumber = 0;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            if (needNumber) {
                printf("Error: Invalid expression.\n");
                return 0;
            }

            if (s[i] == '+' || s[i] == '-')
                sum = sum + term;

            op = s[i];
            needNumber = 1;
            i++;
        }
        else {
            printf("Error: Invalid expression.\n");
            return 0;
        }
    }

    if (needNumber)
        printf("Error: Invalid expression.\n");
    else
        printf("%d\n", sum + term);

    return 0;
}
