# Simulate a sports tournament

import csv
import sys
import random

# Number of simulations to run
N = 10000u


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []

    # TODO: Read teams into memory from file
    with open(sys.argv[1],"r") as file:
        list_of_teams_reader = csv.DictReader(file,fieldnames = ["team","rating"])
        for row in list_of_teams_reader:
            teams.append(row)
            if row['rating'] != "rating":
                row['rating'] = int(row['rating'])
        teams.pop(0)

    counts = {}
    for team in teams:
        key_for_counts = team["team"]
        counts[key_for_counts] = 0
    simulations = 0
    while simulations <= N:
        this_tournament_winner = simulate_tournament(teams) #Does simulate_tournament return a winner?
        counts[this_tournament_winner['team']] += 1
        simulations += 1
    # TODO: Simulate N tournaments and keep track of win counts

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability

def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    how_many_teams_left = simulate_round(teams) #What value is returned in winners?
    while len(how_many_teams_left) > 1:
        how_many_teams_left = simulate_round(how_many_teams_left) #Issue here is that the value is not being updated.


    #This is all fine...
    winning_team = how_many_teams_left[0]
    return winning_team


if __name__ == "__main__":
    main()
