import sys


def get_input():
    s = input("Text: ")
    return s


def count_letters(text):
    text = str(text)
    L = 0
    for letter in text:
        if letter.isalpha():
            L += 1
    return L


def count_sentences(text):
    S = 0
    text = str(text)
    for char in text:
        if char in [".", "!", "?"]:
            S += 1
    return S


def count_words(text):
    text = str(text)
    return len(text.split())


def main():
    text = get_input()
    W = count_words(text)
    L = count_letters(text) / W * 100
    S = count_sentences(text) / W * 100

    grade = 0.0588 * L - 0.296 * S - 15.8
    grade = round(grade)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {grade}")
    return


if __name__ == "__main__":
    main()
