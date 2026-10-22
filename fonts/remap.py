import fontforge

f = fontforge.open("waycat/fonts/Waycat.ttf")

awake = [f[ord(c)] for c in "ABCDE"]
sleep = [f[ord(c)] for c in "GHIJKLMN"]

for i, g in enumerate(awake):
    g.unicode = 0xE000 + i
for i, g in enumerate(sleep):
    g.unicode = 0xE010 + i

f.generate("WaycatPUA.ttf")