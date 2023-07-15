import sys
import pyfiglet
import random



font_list = pyfiglet.FigletFont.getFonts()

if len(sys.argv) > 2:
    i = 0
    for arg in sys.argv:
        print(f"Arg no. {i}: {sys.argv[i]}\n")
        i += 1
    if sys.argv[1] not in ["-f","--font"]:
        print("Invalid argument for font")
        sys.exit(1)
    elif sys.argv[2] not in font_list:
        print("Invalid font type")
        sys.exit(1)

def fontify():
     text = input("Enter your text to be fontified")
     if len(sys.argv) > 1:
        figlet_object = pyfiglet.Figlet(font=sys.argv[2])
     else:
        figlet_object = pyfiglet.Figlet(font=font_list[random.randint(0,len(font_list) - 1)])
     print(figlet_object.renderText(text))

fontify()