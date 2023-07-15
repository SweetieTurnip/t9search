# T9search

T9search is a command-line utility that searches for contacts based on name and phone number. It supports various search options like substring matching, letter replacements, missed letters, and extra letters.

## Usage

To use the T9search utility, follow the steps below:

1. Build the project: Run the following command in the terminal: gcc -o t9search t9search.c
2. 2. Run the program: Execute the following command in the terminal: ./t9search [arguments] <file.txt

Replace '<file.txt' with txt file which contains a list of contacts in the format the first line is the name of the contact, the next line is the phone number, and so on 

Replace `[arguments]` with the desired command-line options. The available options are:

- `-s`: Search for contacts using a specific number or substring.
- `-l <n>`: Perform a fuzzy search with a maximum of `n` letter replacements, missed letters, or extra letters.
- `<search_string>`: Specify the search string for exact or substring matching.

Note: The order of the arguments is significant. `-s` and `-l` cannot be used together.

3. View the results: The program will output the contacts that match the specified search criteria.

## Examples

Here are some examples of how to use the T9search utility:

1. Search for contacts with a specific phone number: ./t9search -s 123456789 <file.txt
2. Perform a fuzzy search with a maximum of 2 letter replacements: ./t9search -l 2 abcd <file.txt
3. Search for contacts using a substring: ./t9search substring <file.txt
4. Display all contacts without any search criteria: ./t9search <file.txt

## Error Codes

The T9search utility may return the following error codes:

- `1`: Argument fault
- `2`: String is too big fault
- `3`: Invalid number

## Contact

For any questions or feedback, please contact sasha.postelga@gmail.com.
