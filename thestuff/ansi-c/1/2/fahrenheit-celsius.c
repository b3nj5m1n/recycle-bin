#include <stdio.h>

main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("\n\nFahrenheit Celsius\n");
    printf("|---------|------|\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f        %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    celsius = lower;
    printf("\n\nCelsius Fahrenheit\n");
    printf("|------|---------|\n");
    while (celsius <= upper) {
        fahr = (celsius / (5.0/9.0)) + 32.0;
        printf("%3.0f     %6.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
