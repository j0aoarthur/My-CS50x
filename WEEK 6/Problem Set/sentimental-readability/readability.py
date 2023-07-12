def letters(text):
    count_letters = 0
    for letter in text:
        if letter.isalpha():
            count_letters += 1

    return count_letters


text = input("Text: ").strip()

num_letters = letters(text)
num_words = text.count(" ") + 1

sentence_char = [".", "!", "?"]
num_sentences = sum(text.count(char) for char in sentence_char)

Letter_per_words = (num_letters / num_words) * 100
Sentences_per_words = (num_sentences / num_words) * 100

grade = 0.0588 * Letter_per_words - 0.296 * Sentences_per_words - 15.8

if grade > 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade:.0f}")
