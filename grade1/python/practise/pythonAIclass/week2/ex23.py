import sys
script, encoding, error = sys.argv


def main(language_file,encoding,errors):
    line = language_file.readline()#readline自身会位移光标

    if line:
        print_line(line, encoding, errors)
        return main(language_file,encoding,errors)

def print_line(line , encoding ,errors):#
    next_lang = line.strip()
    raw_bytes = next_lang.encode(encoding, errors=errors)#encode 字符转字节
    cooked_string = raw_bytes.decode(encoding, errors=errors)#decode 字节转字符
    print(raw_bytes,"<==>",cooked_string)

languages = open("languages.txt",encoding='utf-8')

main(languages, encoding, error)