def break_words(stuff):
    """This function will break up words for us."""
    words = stuff.split(' ')#以space为标志分割字符串，并将字串输出给前面的变量words
    return words

def sort_words(words):
    """Sorts the words."""
    return sorted(words)#以alphabet的顺序把所给的字符串排序

def print_first_word(words):
    """Prints the first word after popping it off."""
    word = words.pop(0)#删去特定位置的字符，并把删除的值传递出去，注：默认为-1位即最后一位
    print(word)

def print_last_word(words):
    """Prints the last word after popping it off."""
    word = words.pop(-1)
    print(word)

def sort_sentence(sentence):
    """Takes in a full sentence and returns the sorted words."""
    words = break_words(sentence)
    return sort_words(words)

def print_first_and_last(sentence):
    """Prints the first and last words of the sentence."""
    words = break_words(sentence)
    print_first_word(words)
    print_last_word(words)

def print_first_and_last_sorted(sentence):
    """Sorts the words then prints the first and last one."""
    words = sort_sentence(sentence)
    print_first_word(words)
    print_last_word(words)

