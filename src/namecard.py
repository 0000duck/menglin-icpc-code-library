# Used to remove duplicated names in my phone contacts

from collections import defaultdict
import codecs

infilename = r"d:\vim\b2.txt";
outfilename = r"d:\vim\b2_out.txt";

card = defaultdict(set)

fin = codecs.open(infilename, 'r', encoding = 'utf-8')
header = fin.readline()

firstline = fin.readline().split(',')

fin.seek(0)
for l in fin.readlines():
	x = l.split(',')
	if x[4] == '':
		name = x[3]
		phone = x[13]
		phone = phone.replace(u"+86", '')
		phone = phone.replace('-', '')
		if phone != '':
			card[name].add(phone)
fin.close()

fout = codecs.open(outfilename, 'w', encoding = 'utf-8')
fout.write(header)
cnt = 0
for key, val in card.iteritems():
	for x in val:
		firstline[3] = key
		firstline[13] = x
		fout.write(','.join(firstline));		
		cnt = cnt + 1

fout.close()

print cnt, "names in total"
