# C Programming: Array Manipulate

## Tasks
Write the function `arrayManipulate` that updates an array based on the [update rules](#update-rules) below. The
function must iterate over the array using an integer pointer and pointer arithmetic (required) to access each array
element.

**PARAMETERS:**
1. `arr`: a pointer to an array of integers
2. `size`: an unsigned int indicating the size of the array

**RETURN:** the middle element's content if `size` is odd, the sum of the two middle elements if `size` is even, or `-1`
if `arr` is NULL or `size` is less than 2

- Assume all values in the array are greater than or equal to zero.

### Update Rules
Iterate through each element in the array. Check if the element's value applies to rule 1. If rule 1 does not apply
then check rule 2. If neither rule applies then do nothing. After each element has been updated in place, sort the
array in ascending order using any sorting algorithm.

- Rule 1: If the value in the element is an even number and greater than six (6), then square the contents of the
  element and move on to the next element.
- Rule 2: If the value in the element is an odd number or it is greater than two (2), then double the contents in the
  element.

### Examples
- The element is 12. Rule 1 applies, and it will be updated to 144 and iteration will continue to the next element.
- The element is 5. Rule 2 applies, and it will be updated to 10 and iteration will continue on.
- The element is 4. Rule 2 applies, and it will be updated to 8 and iteration will continue on.

`int arrayManipulate(int *arr, unsigned int size);`



# C Programming: Binary/Hex String to Integer

## Tasks
Implement a function `bin_hex_StrToInt32` that converts a string, containing either a hexadecimal or binary number,
into the string's integer value (base 10) and returns the converted value.

**PARAMETERS:**
1. `s`: a const char pointer representing a string containing either a binary or hexadecimal number.
2. `out_num`: an int pointer that will contain the base 10 value of the hex or binary string;
2. `mode`: an int representing the conversion mode: 1 is for binary and 2 is for hexadecimal.

**RETURN:** `SUCCESS` if the function successfully converts `s` or `ERROR_INVALID` if the input
parameter is null, empty, or an invalid mode

- Assume a mode value other than 1 or 2 is invalid.

**Note:** Do not call built-in library functions that accomplish these tasks automatically.

`int bin_hex_StrToInt32(const char *s,int *out_num, int mode);`



# C Programming: Buy Groceries

## Tasks
Implement a function `buyGroceries` that calculates the cost of a grocery shopping list and returns the rounded total
cost.

**PARAMETERS:**
1. `stuff`: an array of int containing paired values representing an item number and quantity respectively
2. `size`: an int representing the number of elements in the `stuff` array

**RETURN:** an int containing the cost of the groceries rounded to the nearest dollar; or ERROR_INVALID_PARAMETER for one of the
conditions below

- Assume there will be no duplicate entries for an item number.
- Assume the array is of the given size if a valid even number is passed in.
- If the size passed for the array is not an even number > 0, the function should return ERROR_INVALID_PARAMETER.
- If the array is NULL, the function should return ERROR_INVALID_PARAMETER.
- If any item number is not a 1, 2, 3, or 4, the function should return ERROR_INVALID_PARAMETER.
- If any quantity is 0 or less, the function should return ERROR_INVALID_PARAMETER.

There are four valid items.

| item # | item | Cost |
| --- | --- | --- |
| 1   | eggs   | 3.50 |
| 2   | milk   | 2.25 |
| 3   | bread  | 1.99 |
| 4   | sugar  | 4.15 |

Consider the following array declaration.

`int cart[] = {1, 5, 2, 3, 4, 4};`

The `cart` array item/quantity pairs are as follows: 1/5, 2/3, and 4/4. So, item 1 (eggs) with a quantity of 5, item 2
(milk) with a quantity of 3, and item 4 (sugar) with a quantity of 4. This would total to 40.85 with a rounded
total of 41. The cost of each item is seen in the table above by referencing the item number.

The `buyGroceries` function will iterate the array and determine the total cost of groceries as a floating point
number based on the item number, quantity of each item, and cost of each item. If there is a quantity of 5 or more for
an item, a 5% discount is applied on those items; so, the above example would have a 5% discount applied to the eggs,
changing the total to 39.975 rounded to 40.

Once the total is computed, use a math library function to round the value to an integer and return it.

`int buyGroceries(int stuff[], int size);`



# C Programming: C Palindrome

## Tasks
Implement a function `palindrome` that determines whether a string is a palindrome and returns a status code.

**PARAMETERS:**
1. `phrase`: a constant character pointer to a string containing a potential palindrome

**RETURN:** an int containing `1` if `phrase` is a palindrome, `0` if it's not a palindrome, or `-1` if it's null

## Palindrome
A palindrome is a text phrase (excluding punctuation, spaces, and capitalization/case) that reads the same backwards
or forwards. For example each of the following are palindromes:

```text
Able was I ere I saw Elba.
A nut for a jar of tuna
Taco cat
Was it a car or a cat I saw?
Ed, I saw Harpo Marx ram Oprah W. aside.
```

`int palindrome(const char *phrase);`



# C Programming: Check Hand

## Tasks
Implement the function `checkHand` that determines the best type of hand in a set of poker cards and returns the best
hand.

**PARAMETERS:**
1. `hand`: a 5 element integer array that contains the poker hand

**RETURN:** character pointer to an array containing the best hand, as explained below

- The valid values for this array are the numbers 1 through 13.
- There are only three types of hands worth noting: three of a kind, four of a kind, or a straight.
  - A straight involves all 5 cards being in a sequence such as 3, 4, 5, 6, 7 etc. 
  - A four of a kind and a three of a kind involves 4 of the cards and 3 of the cards being the same respectively.
- Evaluate the array to determine the best hand. The precedence of hands is:
  1. straight (best)
  2. four of a kind
  3. three of a kind
  4. nothing (worst)
- Return one of the following strings based on analysis: `straight`, `four`, `three`, `nothing`, or `invalid`.
- Return `invalid` if any of the values are < 1 or > 13 or if the input array is NULL.

`char *checkHand(int hand[]);`



# C Programming: Delete Word

## Tasks
Implement a function `deleteWord` that deletes (in place) the first occurrence of `word` in the sentence and returns a
status code when finished.

**PARAMETERS:**
1. `sentence`: a character pointer to a string with the sentence containing the word to delete
2. `word`: a character pointer to the string containing the word to delete

**RETURN:** an integer containing the status code for the function, as explained below

- The `word` should be deleted if it is found regardless of the other surrounding characters
- If the task is successful return ERROR_SUCCESS (0)
- If the sentence or word is an empty string the function should return ERROR_EMPTY_STRING (-1)
- If the provided parameters are bad return ERROR_INVALID_PARAMETER (87)
- If the provided 'word' is not part of `sentence` return ERROR_NOT_FOUND (1168)

`int deleteWord(char *sentence, const char *word);`



# C Programming: Make Sentence

## Tasks
Implement the function `makeSentence` that splits up a long string of letters into words and returns a new string with the
words separated.

**PARAMETERS:**
1. `str`: An array of char pointers that contain no spaces

**RETURN:** A new char pointer with spaces in between each word with only the first word capitalized

- Capital letters in the string of characters represents a start of a word.
- The string returned should be a newly allocated array.
- The string will represent a sentence and therefore needs to end with a period.
- If the first word of the sentence begins with the words Who, What, Where, When, Why, or How the sentence should end
  with a question mark.
- Assume that the provided string contains no spaces.

### Example
```text
ILikeCheese   should result in:  I like cheese.
WhereAreYou   should result in:  Where are you?
```

`char *makeSentence(const char *str);`



# C Programming: Lo Shu Magic Square

## Tasks
Implement the function `isMagicSquare` that determines whether an array contains a Lo Shu Magic Square and returns a
status code.

**PARAMETERS:**
1. `values`: a two-dimensional array of int

**RETURN:** an int of `1` if the array meets all the requirements of a magic square; otherwise, `0`

## Lo Shu Magic Square
The Lo Shu Magic Square is a grid with 3 rows and 3 columns like the example shown below:

```text
4 9 2
3 5 7
8 1 6
```

The Lo Shu Magic Square has the following properties:

1. The grid contains each of the numbers 1 through 9 exactly once.
2. The sum of each row, each column, and each diagonal all add up to the same number.
   - so, for the previous example, all rows, columns, and diagonals gives sum = 15

`int isMagicSquare(int values[][COLS]);`



# C Programming: Vigenere Cipher

## Tasks
Implement the function `encryptVigenere` that encrypts a string of plain text with a key and returns the resulting
encrypted string.

**PARAMETERS:**
1. `input`: A character pointer to the plaintext string to encrypt
2. `key`: A character pointer to a string that will be used as the cipher's key

**RETURN:** A character pointer to the allocated string containing the encrypted message, or `NULL` if `input` or `key`
are `NULL` or zero length arrays

- You must convert all uppercase letters to lowercase letters.
- Use a Vigenere cipher, detailed below, to encrypt `input`.

### The Vigenere cipher
The Vigenere cipher is a method of encrypting alphabetic text. To encrypt a message, a key is needed that is as long
as the message. Usually, the key is a ***repeating*** keyword. The encryption is done by adding a letter from the
plain text to a letter of the key. Each letter in the alphabet is given an index:

- a = 0, b = 1, c = 2, d = 3, e = 4,........, w = 22, x = 23, y = 24, and z = 25

For example, if the keyword is `deceptive`, the message `we are discovered save yourself` is encrypted as:

```text
plaintext:    we are discovered save yourself
key:          de cep tivedecept ived eceptive
ciphertext:   zi cvt wqngrzgvtw avzh cqyglmgj
```

The cipher letter `z` is the result of `w` + `d`, which is 22 + 3 = 25. ***Note:*** that `y` + `e` = `c` because
(24 + 4) mod 26 = 2, which is c. In general, the encryption is done as follows:

```text
Plaintext  P = (p0, p1, ...,pn-1)
Key        K = (k0, k1, ...,km-1)   ----> The original key length is m and the key will be repeated to match length of the plaintext
Ciphertext C = (c0, c1, ...,cn-1)
```

ENCRYPTION FORMULA: `ci = [pi + k(i mod m)] mod 26`

`const char *encryptVigenere(const char *input, const char *key);`



# C Programming: Function Pointers

## Tasks
Create two comparison functions, `ascending` and `descending` and a use them as arguments in a `sort` function.

### Task 1
Create a function that compares two items to see which is larger and returns whether they are in ascending order. Then
create a function pointer `ascending` that points to this function.

**PARAMETERS:**
1. an integer that contains the first item to compare
2. an integer that contains the second item to compare

**RETURN:** an int indicating if an ascending sort is needed

- You must declare your function pointer in the header file.

### Task 2
Create a function that compares two items to see which is larger and returns whether they are in descending order. Then
create a function pointer `descending` that points to this function.

**PARAMETERS:**
1. an integer that contains the first item to compare
2. an integer that contains the second item to compare

**RETURN:** an int indicating if a descending sort is needed

- This function should end up returning the opposite result of the equivalent `ascending` function call.
- You must declare your function pointer in the header file.

### Task 3
Create a function, called `sort()`, that will sort an array of integers according to a function pointer that is passed
into it as an input parameter.

**PARAMETERS:**
1. an array of int
2. an int specifying the length of the array
3. a function pointer to a comparison function

**RETURN:** void

- The `sort` function should not have any return values and must modify the input array.
- The `sort` function will run the comparison function to determine the sorting order when comparing during the sort.
- You may use any sorting algorithm to sort the array, so long as it uses the aforementioned function pointers when
  comparing elements.
- The function needs to be compatible with the passed in `ascending` and `descending` function pointers.
- These function pointers must each point to their corresponding comparison function that sort can use.
- When sort is passed ascending, the function will modify the data set to be in ascending order e.g. 1, 2, 3, 4, 5.
- When passed descending, the data set will be modified in descending order e.g. 5, 4, 3, 2, 1.







