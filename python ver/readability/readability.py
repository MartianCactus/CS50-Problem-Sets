def main():

    inp = input('Input: ')

    w = float(words(inp))
    l = float(letters(inp))
    s = float(sentences(inp))

    # Averaging letters and sentences per 100 words
    L = l*(100/w)
    S = s*(100/w)

    # Plugging into formula and rounding up
    index = 0.0588 * L - 0.296 * S - 15.8

    ind = int(round(index))

    # Printing grade level
    if ind >= 16:
        print('Grade 16+')
        return 0

    elif(ind < 1):
        print('Before Grade 1')
        return 0

    else:
        print('Grade ' + str(ind))
        return 0


# Function to calculate number of letters
def letters(a):

    count = 0

    for i in range(len(a)):
        if ord(a[i]) >= 65 and ord(a[i]) <= 90:
            count += 1

        if ord(a[i]) >= 97 and ord(a[i]) <= 122:
            count += 1

    return count


# Function to calculate number of words
def words(a):

    count = 0

    for i in range(len(a)):
        if a[i] == ' ':
            count += 1

    return count+1


# Function to calculate number of sentences
def sentences(a):

    count = 0

    for i in range(len(a)):
        if a[i] == '!' or a[i] == '?' or a[i] == '.':
            count += 1

    return count


if __name__ == "__main__":
    main()

