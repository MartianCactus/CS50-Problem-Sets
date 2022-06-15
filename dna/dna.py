import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCES")

    # Read database file into a variable
    DNAbase = []
    header = []
    with open(sys.argv[1], 'r') as file:

        reader = csv.reader(file)
        line1 = next(reader)
        header = line1

    with open(sys.argv[1], 'r') as file:

        dreader = csv.DictReader(file)
        for lines in dreader:
            DNAbase.append(lines)

    # Read DNA sequence file into a variable
    seq = ''
    with open(sys.argv[2], 'r') as file:
        seq = file.read()

    # Find longest match of each STR in DNA sequence
    match = [' ']
    for i in header[1:]:
        longestmatch = longest_match(seq, i)
        match.append(longestmatch)

    # Check database for matching profiles
    potential = []
    for i in DNAbase:
        sus = True
        for j in header[1:]:
            if int(i[j]) != match[header.index(j)]:
                sus = False
        if sus == True:
            potential.append(i['name'])

    if len(potential) == 0:
        print('No match')

    else:
        print(potential[0])

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
