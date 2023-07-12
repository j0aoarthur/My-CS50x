import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    person_file = sys.argv[1]
    dna_file = sys.argv[2]
    # TODO: Read database file into a variable
    people = []

    with open(person_file, newline="") as person_file:
        reader = csv.DictReader(person_file)
        for row in reader:
            people.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(dna_file, "r") as dna_file:
        reader = csv.reader(dna_file)
        dna = dna_file.read().strip()

    # TODO: Find longest match of each STR in DNA sequence
    strs = list(people[1].keys())[1:]  # all STRS of the csv file
    list_matches = {}

    for dna_str in strs:
        list_matches[dna_str] = longest_match(dna, dna_str)

    # TODO: Check database for matching profiles
    for index, person in enumerate(people):
        slice = {key: int(person[key]) for key in strs}
        if list_matches == slice:
            print(person["name"])
            exit(0)

    print("No match")


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
