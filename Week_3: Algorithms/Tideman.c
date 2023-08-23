//Tideman Problem
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes.
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];


        string name;
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// What is a vote? An array of preferences from 1 to MAX candidates with name
//How is vote organised? By user input to terminal
//What does update ranks mean? Assign a candidate a rank
//How are candidates organised? By number where number 0 to 9 corresponds to a candidate
//How is this implemented therefore?
//Which variable are we changing here? ranks
//How is ranks going to be changed?
//Each candidate name will correspond to a number in the list of candidates
//This number is then found in the list of candidates,
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //What am I struggling to understand?
    //The variables
    //How can I break this into more steps?
    //0 is false
    //1 is true
    string ca;
    int comparison = 1;
    for (int a = 0; a < candidate_count; a++)
    {

    ca = candidates[a];
    comparison = strcmp(name,ca);

        if (comparison == 0) //Name on list of candidates
        {
        ranks[rank] = a; //Update leaderboard not with name but with candidate number? If ranks takes an integer
        return true;
        }

        else
        {

        //Do nothing

        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //What data type are we changing for record_preferences?
    //Int of number of voters (only) who prefer i to j
    //E.g. preferences[1][2] = 3 (separate voters -> separate instances of vote function)
    //ranks[i] is voter's ith preference e.g. rank[0] = 1


    int wins = 0;
    int loses = 0;
    for (int i = 0; i < candidate_count; i++)
    {
    wins = ranks[i];
    for (int j = i + 1; j < candidate_count; j++)
    {
    loses = ranks[j];
    preferences[wins][loses] += 1;
    }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
//Where are we measuring this and how? Adding to pairs array where
//winner = winning_candidate_number + loser = losing_candidate_number

//How are measuring this? If [i][j] != [j][i] where i = candidate_1
//and j = candidate_2

for (int i = 0; i < candidate_count;i++)
{
for (int j = i + 1; j < candidate_count; j++)
if (preferences[i][j] != preferences[j][i]) //One candidate beats the other
{
    if (preferences[i][j] > preferences[j][i])
    {
    pairs[pair_count].winner = i;
    pairs[pair_count].loser = j;
    pair_count += 1;
    }
    else
    {
    pairs[pair_count].winner = j;
    pairs[pair_count].loser = i;
    pair_count += 1;
    }
}
}

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
        // TODO
        //Bubble sort
    int winning_candidate_number_placeholder = 0;
    int losing_candidate_number_placeholder = 0;

    for (int i = 0; i < pair_count; i++)
    {
    for (int j = i + 1; j < pair_count; j++)
    {
    if ((preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]) > (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]))
    {
    winning_candidate_number_placeholder = pairs[j].winner;
    losing_candidate_number_placeholder = pairs[j].loser;
    pairs[j].winner = pairs[i].winner;
    pairs[j].loser = pairs[i].loser;
    pairs[i].winner = winning_candidate_number_placeholder;
    pairs[i].loser = losing_candidate_number_placeholder;
    }
    else
    {

    }
    }
    //What are we measuring? The difference between preferences[i][j]
    //and preferences[i][j]
    //How are we getting this data? From pair winners and pair losers
    //How are we comparing? index + 1
    //What happens if later is bigger, they swap places?
    //How do they swap places? By being stored in a separate struct
    }
    return;
}


// Lock pairs into the candidate graph in order, without creating cycles

void lock_pairs(void)
{
//Lock the first two pairs since it is impossible to create a cycle from two pairs alone
for (int i = 0; i < 2; i++)
{
    locked[pairs[i].winner][pairs[i].loser] = true;
}
//This is going to be our counter to progress till the end of pair count
int index2 = 0 ;
int index3 = 0;

int index = 0;
int back_track[pair_count];
int back_track_storage[pair_count];

for (int a = 2; a < pair_count; a++) //Beginning of for loop
{
locked[pairs[a].winner][pairs[a].loser] = true;

for (int q = 0; q < pair_count; q++) // Resets back track and back track storage
{
back_track[q] = 10;
back_track_storage[q] = 10;
}

index = 0; //Resetting index to 0, so that back_track[0] always evaluates as something if sb beats winner

for (int i = 0; i < pair_count; i++) //Checking all other possible candidate to see if winner is already part of candidate graph
{

if (locked[i][pairs[a].winner] == true) //If winner is part of existing graph
{
if (locked[pairs[a].loser][i] == true) //If loser beats i which beats winner who beats loser - Cycle
{
locked[pairs[a].winner][pairs[a].loser] = false;
i += pair_count;
}
else
{
back_track[index] = i; //Add winner to back track index
index += 1;
}
}

else
{

}

}

index2 = 0 ;
index3 = 0;
while (back_track[0] != 10) //This evaluates whether the backtrack array is "empty" + when "empty" moves to next code
{


while (back_track[index2] != 10)
{

for (int chain_follow = 0; chain_follow < pair_count; chain_follow++) //Chain follow is whether the back_track numbers found have been beaten
{


if (locked[chain_follow][back_track[index2]] == true)
{
if (chain_follow == pairs[a].loser)
{
locked[pairs[a].winner][pairs[a].loser] = false; //Cycle created, thus not locking in
back_track[0] = 10;
}
else
{
back_track_storage[index3] = chain_follow; //Store chain_follow to back_track_storage array which is to be copied to back_track_array
index3 += 1;
}
}
else
{
//Do nothing
}

}

if (back_track[index + 1] == 10)
{
//End of back_track - copy back_track_storage to back_track

for (int i = 0; i < pair_count; i++) //Copy contents of back_track_storage which stores chain_follow to back_track
{
back_track[i] = back_track_storage[i];
}

for (int w = 0; w < pair_count; w++) //"Emptying" of back_track_storage
{
back_track_storage[w] = 10;
}

index2 = 0; //Reset index2 to 0
}

else //Progress to next number in back_track
{
index2++;
}


}//No more chains to be explored, thus able to break out of loop




index2 = 0;
}



} //End of for loop

} //Speculate that reasoning is right but implementation needs adjustment

//How does locked pairs work?
//First, lock in the winning candidate
/*/locked[pairs[0].winner][pairs[0].loser] = true;
locked[pairs[1].winner][pairs[1].winner] = true;
bool annul_locked_pair = false;
int storage_location = 0;
int temp_storage[pair_count * 2];
for (int i = 0; i < pair_count * 2; i += 2)
{
temp_storage[i] = 10;
}
bool add = true;
int index = 0;
for (int i = 0; i < pair_count; i++) //Adds winners
{
while (temp_storage[index] != 10)
{
if (temp_storage[index] == pairs[i].winner)
{
add = false;
}
index++; // This checks if candidate already exists in list
}
if (add == true)
{
temp_storage[storage_location] = pairs[i].winner;
storage_location++;
}
else
{
}
index = 0;
while (temp_storage[index] != 10)
{
if (temp_storage[index] == pairs[i].loser)
{
add = false;
}
index++;
}
if (add == true)
{
temp_storage[storage_location] = pairs[i].loser;
storage_location++;
}
else
{
}
}
//Where are we taking the key information from? Taking key info from pairs
for (int cycle1 = 2; cycle1 < pair_count; cycle1++)
{
    //Add change //Then if incorrect, remove change
    locked[pairs[cycle1].winner][pairs[cycle1].loser] = true;
    for (int cycle2 = 0; cycle2 < pair_count; cycle2++)
    {
    if (locked[pairs[cycle1].loser][cycle2] == true)
    {
    for (int cycle3 = 0; cycle3 < pair_count; cycle3++)
    {
    if (locked[cycle2][pairs[cycle1].winner] == true) //Cycle created
    {
    locked[pairs[cycle1].winner][pairs[cycle1].loser] = false;
    cycle2 += pair_count; //Move to next pair in list
    }
    else if (locked[cycle2][cycle3] == true)
    {
    for (int cycle4 = 0; cycle4 < pair_count; cycle4++)
    {
    if (locked[cycle3][pairs[cycle1].winner] == true)
    {
    locked[pairs[cycle1].winner][pairs[cycle1].loser] = false;
    cycle2 += pair_count; //Move to next pair in list
    }
    else if (locked[cycle3][cycle4] == true)
    {
    for (int cycle4 = 0; cycle4 < pair_count; cycle4++)
    {
    if (locked[cycle3][pairs[cycle1].winner] == true)
    {
    locked[pairs[cycle1].winner][pairs[cycle1].loser] = false;
    cycle2 += pair_count; //Move to next pair in list
    }
    else if (locked[cycle3][cycle4] == true)
    {
    for (int cycle5 = 0; cycle5 < pair_count; cycle5++)
    {
    if (locked[cycle4][pairs[cycle1].winner == true])
    {
    locked[pairs[cycle1].winner][pairs[cycle1].loser] = false;
    cycle2 += pair_count; //Move to next pair in list
    }
    else
    {
    }
    }
    }
    else
    {
    //Do nothing
    }
    }
    }
    else
    {
    //Do nothing
    }
    }
    }
    else
    {
    //Do nothing
    }
    }
    }
    else
    {
    //Do nothing
    }
    }
}
}
//Next, add a locked pair, then test to see if a cycle has been created i.e. throughout the locked pairs, there must be one unsurpassed candidate
//If not, the locked pair needs removing - what data are we using to create these locked pairs?
//What are we doing to test whether there is no winner?
//Firstly, we augment a until locked evaluates as true
//If locked evaluates as true, we augment b - if by the end, locked[j][i] has evaluated as false for every case we keep the lock
//Otherwise we break the lock
//No winner is present in the list of locked pairs
/*/
/*/
int winning_candidate_present = 0;
int lock_pair = 0;
locked[pairs[0].winner][pairs[0].loser] = true;
for (int a = 1; a < pair_count; a++)
{
locked[pairs[a].winner][pairs[a].loser] = true;
//Loser detector
for (int i = 0; i < pair_count; i++)
{
for (int j = 0; j < pair_count; j++) //Problems with pair_count // No
{
if (j != i)
{
if (locked[j][i] == true)
{
winning_candidate_present = 1;
j += pair_count;
}
else
{
winning_candidate_present = 0;
}
}
else
{
}
}
if (winning_candidate_present == 0)
{
lock_pair = 0;
if (lock_pair == 0)
{
locked[pairs[a].winner][pairs[a].loser] = true;
i += pair_count;
}
}
else
{
lock_pair = 1;
}
}
if (lock_pair == 1)
{
locked[pairs[a].winner][pairs[a].loser] = false;
}
else
{
}
}
//Locked is a list of victories in order
return;
}
int cycle_lead_second_storage[pair_count];
int index_for_second_storage;
int index_of_cycle_leads = 0;
int temp_index = 0;
locked[pairs[0].winner][pairs[0].loser] = true;
for (int a = 1; a < pair_count; a++)
{
locked[pairs[a].winner][pairs[a].loser] = true;
int cycle_leads[pair_count];
for (int i = 0; i < pair_count; i++)
{
cycle_leads[i] = 10;
}
int cycle_lead_position = 0;
for (int j = a + 1; j < pair_count; j++)
{
if (locked[pairs[a].loser][j] == true)
{
cycle_leads[cycle_lead_position] = j;
cycle_lead_position++;
}
else
{
//Do nothing
}
}
//Let's suppose no cycles have been made
if (cycle_leads[0] == 10)
{
//Do nothing - keep this locked
}
else
{
for (int x = 0; x < pair_count; x++)
{
cycle_lead_second_storage[x] = 10;
}
while (cycle_leads[index_of_cycle_leads] != 10)
{
for (int j = 0; j < pair_count;j++)
{
if (j == pairs[a].winner)
{
if (locked[cycle_leads[index_of_cycle_leads]][j] == true)
{
locked[pairs[a].winner][pairs[a].loser] = false;
cycle_leads[index_of_cycle_leads] = 10;
}
}
else if (locked[cycle_leads[index_of_cycle_leads]][j] == true)
{
cycle_lead_second_storage[index_for_second_storage] = j;
index_for_second_storage++;
}
else
{
//Do nothing
}
} //For loop
if (cycle_leads[index_of_cycle_leads + 1] == 10)
{
while (cycle_lead_second_storage[temp_index] != 10)
{
cycle_leads[temp_index] = cycle_lead_second_storage[temp_index];
temp_index++;
}
temp_index = 0;
index_for_second_storage = 0;
index_of_cycle_leads = 0;
} //While loop
}
}
}
//Does the loser beat the winner by beating other candidates who beat the winning candidate in a pair?
/*/

//
//What am I measuring here? I am measuring whether a cycle is created
//How can a cycle be measured? The absence of a cycle is when for all candidates, one candidate exists for whom locked[candidate_in_question][other_candidates] evals as true,
//while locked[all_other_candidates][candidate_in_question] evals as false
//Therefore if absence is true, the change may be made - if not made the change may not be made






// Print the winner of the election
//What to do - work on understanding what constitutes a victory - how is this measured?
//Winner only candidate in list of winners in pairs for whom locked [other][winner] is never true and whose position in pairs is higher than
//all others
//Am I going to solve this problem currently? No? Why? Because I don't have a concrete understanding of the problem. How will I achieve this?
//By drawing it on paper, reading and imagining how locked works and how a winner is decided in the Tideman problem
//What should I do in the meantime? Sleep
//The theory is wrong/is missing an idea thus I won't be able to solve
//What do I need to get a grasp on? The data structures themselves...


void print_winner(void)
{
int print_candidate_as_winner = 1;
for (int i = 0; i < candidate_count;i++)
{

    for (int j = 0; j < candidate_count; j++)
        {
        if (locked[j][i] == true)
           {
            print_candidate_as_winner = 0;
           }
        }
        if (print_candidate_as_winner == 1)
            {
                printf("%s\n",candidates[i]);
            }
        print_candidate_as_winner = 1;
}


////////Block 1 -
/*
//1.0 Create index for list of winners and storage array for winners
int index_for_list_of_winners_total = 0;

int list_of_winners_out_of_total_candidates_in_election[candidate_count];
//1.05 Empty this storage array
for (int empty = 0; empty < candidate_count; empty++)
{
list_of_winners_out_of_total_candidates_in_election[empty] = 10;
}
//1.1 / 1.2 - Create variable to record whether or not to add candidate

int should_this_winner_be_added = 0;
//Populate array with cases where locked evaluates as true
for (int winnerq = 0; winnerq < candidate_count; winnerq++)
{
for (int loserq = 0; loserq < candidate_count; loserq++)
{
//1.25 - Check that the winner does not already exist within the array of the list of winners
if (locked[winnerq][loserq] == true)
{
for (int is_this_winner_present = 0; is_this_winner_present < candidate_count; is_this_winner_present++)
{
if (list_of_winners_out_of_total_candidates_in_election[is_this_winner_present] == winnerq)
{
should_this_winner_be_added = 1;
}
}
// 1.3 Add winner if the winner is not in list
if (should_this_winner_be_added == 0)
{
list_of_winners_out_of_total_candidates_in_election[index_for_list_of_winners_total] = winnerq;
index_for_list_of_winners_total++;
}
should_this_winner_be_added = 0;
}
}
}
//1.3 - Print list of eligible candidates
for (int i = 0; i < candidate_count; i++)
{
//printf("%i",list_of_winners_out_of_total_candidates_in_election[i]);
}




//////END OF BLOCK 1

///////Block 2 - create variable to record whether to add candidate to list of untriumphed winners variable there are 2.0
int add_candidate_to_list_of_undefeated = 1;

///Create list of undefeated candidates 2.1
int undefeated_candidate_list[candidate_count];

//Create index variable to begin at start of the list
int index = 0;

///"Empty" array of undefeated candidates with 10 2.2
for (int i = 0; i < candidate_count; i++)
    {
        undefeated_candidate_list[i] = 10;
    }

/// - if candidate defeated, do not add to list 2.3
for (int i = 0; i < candidate_count; i++)
{
    for (int j = 0; j < candidate_count;j++)
    {
        //Number must not be ten as this is an empty space
        if (list_of_winners_out_of_total_candidates_in_election[i] != 10)
            {
                //If locked ... is true, candidate has been defeated
                if (locked[j][list_of_winners_out_of_total_candidates_in_election[i]])
                    {
                    //Add candidate is false
                    add_candidate_to_list_of_undefeated = 0;
                    }

            }
    }
    //Add candidate when not defeated
    if (add_candidate_to_list_of_undefeated == 1)
        {
            undefeated_candidate_list[index] = list_of_winners_out_of_total_candidates_in_election[i];
        }

    //Reset add_candidate_variable to true until proven false
    add_candidate_to_list_of_undefeated = 1;
}

//END OF BLOCK 2

//Block 3 - create undefeated winners count variable and list to store winners

int undefeated_winners_count = 0;

int victor_short_list[undefeated_winners_count];

//Count number of undefeated winners in list 3.05
while (undefeated_candidate_list[undefeated_winners_count] != 10)
    {
        undefeated_winners_count++;
    }

// 3.1 If = 1, print name of candidate from number in list
    if (undefeated_winners_count == 1)
        {
            printf("%s\n",candidates[undefeated_candidate_list[0]]);
        }


//3.1 If greater than 1, check againt pairs.winners
    else if (undefeated_winners_count > 1)
        {

//3.2 Create a list to store undefeated candidates




//3.2 If equal to pairs.winners print name of candidate from number which matches
    for (int i = 0; i < pair_count;i++)
        {
            for (int j = 0; j < undefeated_winners_count; j++)
                {
                if (pairs[i].winner == victor_short_list[j])
                    {
                        printf("%s\n", candidates[victor_short_list[j]]);
                        int final_winner = victor_short_list[j];
                        i += pair_count;
                    }
                }
        }
    } */
} //End of function

/*/Block 1
    -Create list to store candidates who have won - 1.0
    -Populate list with 10 - 1.05
    -Find those candidates who have won and are thus eligible for being a victor - 1.1
    -Cycle through locked - 1.2
    -Print this list of eligible candidates - 1.3

/*/
/*/
//Block 2
    -Eliminate from the list those who have lost - 2.0
    -Print this updated list of fewer candidates - 2.5

//Block 3
    -Check the size of the list - 3.0
    -If 1, print the candidate name by number 3.1
    -If greater than 1, print the candidate name according - 3.1
    to whom appears first in list of winners

//Block 4


//Block 5




/*/




/*/
int add_i = 0;
int add_j = 0;
int storage_array[candidate_count];
int index = 0;
for (int i = 0; i < candidate_count; i++) //Clearing storage_array
{
storage_array[i] = 10;
}
for (int i = 0; i < candidate_count; i++) //Going throuagh each candidate as a winner to establish if in locked graph
{
for (int j = 0; j < candidate_count; j++)
{
if (locked[i][j] == true) //Only including candidates in candidate graph
    {

    for (int a = 0; a < candidate_count; a++) //Adding i to candidate graph if not already in array
    {
    if (i == storage_array[a])
    {
    add_i = 1;
    }

    if (j == storage_array[a]) //Adding j to candidate graph if not already in array
    {
    add_j = 1;
    }
    }
if (add_j == 0)
{
storage_array[index] = j;
index++;
}
if (add_i == 0)
{
storage_array[index] = i;
index++;
}
    }
add_i = 0; //Resetting to 0, so that candidate numbers can be added by default until proved duplicates
add_j = 0;
} //List of candidates in graph - added//End of second for loop - j
} //End of first for loop - i
int a = 0;
int number_of_candidates_in_graph;
index = 0;
while (storage_array[a] != 10) //Exhausting list of candidates in candidate graph
{
number_of_candidates_in_graph++; //Counting number - which is 1 greater than array position
a++;
}
int storage_array_for_victor[number_of_candidates_in_graph];
int victory_number = number_of_candidates_in_graph - 1; //Excluding victorious candidate but counting all other candidates in locked graph
int number_of_candidates_beaten = 0; //Will count this number to see if matches victory number
int add_d = 0;
int d = 0;
index = 0;
int index2 = 0;
int add_q = 0;

while (storage_array[a] != 10) //Going through list of candidates - biggest loop
{

for (int i = 0; i < number_of_candidates_in_graph - 1; i++) //"Emptying" list for each new node in locked graph
{
    storage_array_for_victor[i] = 10;
}


while (storage_array[d] != 10) //What have I missed out here? Tracking the loser nodes and adding these to victory count - additional loop to establish unique win
{


if (locked[storage_array[a]][storage_array[d]] == true) //
{


for (int w = 0; w < sizeof(storage_array)/4; w++)
{


if (storage_array[d] == storage_array_for_victor[w]) //Detecting whether the number already exists in the victorious candidate array
{
add_d = 1; //If it does, victory not counted and loser not added to list
}

}

if (add_d == 0) //If unique, victory added
{
storage_array_for_victor[index] = storage_array[d];
number_of_candidates_beaten++;

for (int q = 0; q < sizeof(storage_array)/4; q++)
{


if (locked[storage_array_for_victor[index]][q] == true)
{

for (int p = 0; p < sizeof(storage_array)/4; p++)
{

if (storage_array_for_victor[p] == q)
{
add_q = 1;
}

}

if (add_q == 0) //Chain victory not already in list, therefore to be added
{
index2++;
storage_array_for_victor[index + index2] = q;
number_of_candidates_beaten++;
}

add_q = 0; //Resets q for next chain victory assessment
}//If index q locked (second degree loser)


} //End of chain victory assessment
index++; //Moves to next loser node - then checking whether further victories
add_d = 0;
} //End of d as loser sequence

 } //If index d locked (first degree loser)

} //End of a - d comparison
d = 0;
index = 0;
if (number_of_candidates_beaten >= victory_number)
{
//Print winning candidate number, as source
//printf("%i ",storage_array[a]);
printf("%s \n",candidates[storage_array[a]]);
int final_winner = storage_array[a];
storage_array[a] = 10;
} //End of print statement
a++;
} //End of a cycling
} //End of function brackets


//Problem diagnosis - as follows
/*/
/*/
/*/
/*
1. Print function - not printing name correctly or not printing candidate number correctly
2. Not updating
3. Try building the final function as a series of modules, then test each module
4. Use long names for each variable
5. Universalise by creating a function which can be deployed universally
*/



/*/

/*/
/*/
//To do -> figure out how to pass arguments and test my code using the Linux terminal
/*/
