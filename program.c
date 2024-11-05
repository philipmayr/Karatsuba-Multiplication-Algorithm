// Karatsuba Multiplication Algorithm

#include <stdio.h>

int find_greater_of_twain(int a, int b)
{
    return a > b ? a : b;
}

int count_bits(long long bit_stream)
{
    int bit_length = 0;
    
    while (bit_stream) 
    {    
        bit_length++;
        bit_stream >>= 1;
    }
    
    return bit_length;
}

long long exponentiate(long long base, long long index)
{
    long long power = 1;
    
    if (index == 0) return power;
    if (index == 1) return base;
    
    while (index)
    {
        if (index & 1) power *= base;
        
        base *= base;
        index >>= 1;
    }
    
    return power;    
}

long long multiply(long long multiplicand, long long multiplier)
{
    int threshold = 32;
    
    if (multiplicand < threshold && multiplier < threshold) 
        return multiplicand * multiplier;

    int multiplicand_bit_length = count_bits(multiplicand);
    int multiplier_bit_length = count_bits(multiplier);
    
    int halved_bit_length = find_greater_of_twain(multiplicand_bit_length, multiplier_bit_length) / 2;
    int two_exponentiated_by_halved_bit_length = exponentiate(2, halved_bit_length);

    long long multiplicand_low_order_bits = multiplicand % two_exponentiated_by_halved_bit_length;
    long long multiplier_low_order_bits = multiplier % two_exponentiated_by_halved_bit_length;

    long long multiplicand_high_order_bits = multiplicand >> halved_bit_length;
    long long multiplier_high_order_bits = multiplier >> halved_bit_length;
    
    long long first_product = multiply(multiplicand_low_order_bits, multiplier_low_order_bits);
    long long second_product = multiply(multiplicand_high_order_bits, multiplier_high_order_bits);
    long long third_product = multiply(multiplicand_low_order_bits + multiplicand_high_order_bits, multiplier_low_order_bits + multiplier_high_order_bits);

    long long first_summand = second_product * exponentiate(2, 2 * halved_bit_length);
    long long second_summand = (third_product - second_product - first_product) * two_exponentiated_by_halved_bit_length;
    long long third_summand = first_product;

    long long sum = first_summand + second_summand + third_summand;
    
    return sum;
}

int main()
{
    long long multiplicand = 0;
    long long multiplier = 0;
    long long product = 0;
    
    for (;;)
    {    
        printf("Enter integer multiplicand: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        long long input, status, buffer;

      	status = scanf("%lld", &input);
      	
      	while (status != 1)
      	{
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter integer multiplicand: ");
              
              status = scanf("%lld", &input);
      	}
      
      	multiplicand = input;
      	
      	printf("Enter integer multiplier: ");
        
      	status = scanf("%lld", &input);
      	
      	while (status != 1)
      	{
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter integer multiplier: ");
              
              status = scanf("%lld", &input);
      	}
      
      	multiplier = input;

        product = multiply(multiplicand, multiplier);
      	
      	printf("\n");
    	
    	printf("%lld ⋅ %lld æ %lld", multiplier, multiplicand, product);
        
        printf("\n\n");
    }

    return 0;
}
