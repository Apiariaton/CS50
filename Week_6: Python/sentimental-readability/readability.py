# TODO
#Need to test this...


text = input("Enter the text for which you'd like a readability level")
text = text.split()
text_length = len(text)
#I need a test case: an example where the average number of letters per word is known
# Congratulations! Today is your day. You're off to Great Places! You're off and away!
# Grade Level 3
# 464.29 letters per 100 words (because 65 / 14 * 100 = 464.29)
#28.57 sentences per 100 words (because 4 / 14 * 100 = 28.57)

def compute_letters_per_word(text):
    average_letters_per_word = 0
    for word in text:
        average_letters_per_word += len(word)
    print(f"Total number of letters counted:{average_letters_per_word}")
    average_letters_per_word = average_letters_per_word / text_length #Is this a positive number?
    print(f"Total number of letters counted:{average_letters_per_word}")
    return ((average_letters_per_word * 100))

def sentences_per_text(text):
    average_sentences_per_text = 0
    for word in text:
        if word[len(word) - 1] in [".","!"]: #There is a problem here of some kind
            average_sentences_per_text += 1
    return ((average_sentences_per_text * (100/text_length)))


def Coleman_Liau_calculate(text):
    mean_no_sentences_in_text = sentences_per_text(text)
    print(f"Mean_no_sentences_per_text: {mean_no_sentences_in_text}\n")
    mean_no_letters_per_word = compute_letters_per_word(text)
    print(f"Mean_no_letters_per_text: {mean_no_letters_per_word}\n")
    CL_index = 0.0588 * mean_no_letters_per_word - 0.296 * mean_no_sentences_in_text - 15.8
    print(f"This text is Grade Level {CL_index}...")

Coleman_Liau_calculate(text)