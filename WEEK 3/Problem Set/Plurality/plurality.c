#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) // 1 through argc - 1
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int j = 0;
    bool sort = false;
    do
    {
        sort = false;
        for (int i = 0; i < (candidate_count - 1 - j); i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                int temp = candidates[i].votes;
                string s_temp = candidates[i].name;

                candidates[i].votes = candidates[i + 1].votes;
                candidates[i].name = candidates[i + 1].name;

                candidates[i + 1].votes = temp;
                candidates[i + 1].name = s_temp;

                sort = true;
            }
        }
        j++;
    }
    while (sort);

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[0].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}