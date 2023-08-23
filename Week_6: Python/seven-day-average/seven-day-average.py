import csv
import requests
import datetime


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    states_of_the_United_States = set()
    list_of_data = list(reader)
    final_date = (len(list_of_data) - 1)
    first_date_minus_fourteen_days =  final_date - (50 * 14)
    i = 0
    while i <= final_date:
        states_of_the_United_States.add(list_of_data[i]['state'])
        i += 1
    line_number = first_date_minus_fourteen_days
    covid_cases = {s:[] for s in states_of_the_United_States}
    while  first_date_minus_fourteen_days <= line_number <= final_date:
        state_of_relevance = list_of_data[line_number]['state']
        value_to_add_list = list_of_data[line_number]['cases']
        entry = (covid_cases[state_of_relevance])
        entry.append(value_to_add_list) #What could the issue be here?
        line_number += 1

    return covid_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for individual_state in states:
        if individual_state in new_cases:
            print(f"Valid state\n: {individual_state}")
            seven_day_average = 0
            first_week_average = 0
            rel_last_half = new_cases[individual_state]
            rel_last_half = rel_last_half[7:13]
            rel_first_half = new_cases[individual_state]
            rel_first_half = rel_first_half[0:6]
            for case_no_per_day in rel_last_half:
                seven_day_average += int(case_no_per_day)
            for case_no_per_day in rel_first_half:
                first_week_average += int(case_no_per_day)
            first_week_average /= 7
            seven_day_average /= 7
            if first_week_average != 0 and seven_day_average != 0:
                percentage_change = seven_day_average / first_week_average
                print(f"Percentage change in case numbers this week over last week: {percentage_change}\n")
            print(f"Average number of cases over last seven days: {seven_day_average}\n")




main()
